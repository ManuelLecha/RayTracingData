//
// Created by eudald on 4/2/20.
//

#include <QtCore/QTextStream>
#include <include/BaseMaterial.h>
#include <include/MaterialTexture.h>
#include <include/Cylinder.h>
#include "AnimationDataReader.h"

static Object *createDataObject(double x, double z, double s, double v, ObjectFactory::OBJECT_TYPES t);

AnimationDataReader::AnimationDataReader(Scene* s){
    scene = s;
    numProp = 0;
    scene_xlim = Range(s->pmin.x, s->pmax.x);
    scene_zlim = Range(s->pmin.z, s->pmax.z);
    double xlen = scene_xlim.max - scene_xlim.min;
    double zlen = scene_xlim.max - scene_xlim.min;
    double minLen = xlen < zlen ? xlen : zlen;
    //scene_slim = Range(minLen/128.0f,minLen/32.0f);
    scene_slim = Range(0, 5);

    propColors.push_back(vec3(((float)214)/255, ((float)39)/255, ((float)39)/255));
    propColors.push_back(vec3( 0.9,1,0.3 ));
}

void AnimationDataReader::readFile(QString fileName){
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        fileLineRead(line);
    }

    file.close();
}

void AnimationDataReader::fileLineRead(QString lineReaded){
    QStringList fields = lineReaded.split(",");
    for (auto &str : fields) str = str.trimmed();
    string d = fields[0].toStdString();

    std::cout << fields[0].toStdString() << std::endl;
    if (QString::compare("limits", fields[0], Qt::CaseInsensitive) == 0)
        limitsFound(fields);
    else if (QString::compare("base", fields[0], Qt::CaseInsensitive) == 0)
        baseFound(fields);
    else if (QString::compare("prop", fields[0], Qt::CaseInsensitive) == 0)
        propFound(fields);
    else if (QString::compare("object", fields[0], Qt::CaseInsensitive) == 0)
        objectFound(fields);
    else if (QString::compare("frame", fields[0], Qt::CaseInsensitive) == 0)
        frameFound(fields);
    else if (QString::compare("data", fields[0], Qt::CaseInsensitive) == 0)
        dataFound(fields);
    else
        std::cerr << "Element unknown" << fields[0].toStdString() << std::endl;
}

void AnimationDataReader::baseFound(QStringList fields){
//base plane nx ny nz d textura
    if (fields.size() != 7) {
        std::cerr << "Wrong base format" << std::endl;
        return;
    }
    std::cout << endl << fields[1].toStdString() << endl;
    if (QString::compare("plane", fields[1], Qt::CaseInsensitive) == 0) {
        // Fase 1: Cal fer un pla acotat i no un pla infinit. Les dimensions del pla acotat seran les dimensions de l'escena en x i z
        // DONE

        float xlength = scene->pmax.x - scene->pmin.x;
        float zlength = scene->pmax.z - scene->pmin.z;
        FittedPlane *o = new FittedPlane(vec3(0, -0.5, 0), vec3(0, 0, -zlength / 2),
                                         vec3(xlength / 2, 0, 0));

        o->setMaterial(new MaterialTexture(new Texture(fields[6]), o));

        FittedPlane *o2 = new FittedPlane(vec3(0, -1, 0), vec3(0, 0, -zlength),
                                         vec3(xlength, 0, 0));

        o2->setMaterial(new Lambertian(vec3( ((float)100)/255, ((float)127)/255, ((float)166)/255 )));

        scene->objects.push_back(o);
        //scene->objects.push_back(o2);
        scene->basePlane = o;
    }
}

void AnimationDataReader::limitsFound(QStringList fields){
    // limits xmin xmax zmin zmax
    if (fields.size() != 5) {
        std::cerr << "Wrong limits format" << std::endl;
        return;
    }
    // Fase 1: Cal guardar el limits del mapa per saber on mapejar les posicions dels objectes
    // DONE
    data_xlim = Range(fields[1].toDouble(), fields[2].toDouble());
    data_zlim = Range(fields[3].toDouble(), fields[4].toDouble());
}

void AnimationDataReader::propFound(QStringList fields){
    //prop numProp vmin vmax tipusGizmo
    if (fields.size() < 5) {
        std::cerr << "Wrong propietat format" << std::endl;
        return;
    }
    numProp++;
    propLims.push_back(Range(fields[2].toDouble(), fields[3].toDouble()));

    if (QString::compare("sphere", fields[4], Qt::CaseInsensitive) == 0) {
        props.push_back(ObjectFactory::OBJECT_TYPES::SPHERE);
    } else if (QString::compare("cylinder", fields[4], Qt::CaseInsensitive) == 0) {
        props.push_back(ObjectFactory::OBJECT_TYPES::CYLINDER);
    }else{
        std::cerr << "Element unknown" << fields[0].toStdString() << std::endl;
    }
}

void AnimationDataReader::objectFound(QStringList fields){
    //data id x z radium
    if (fields.size() != 5) {
        std::cerr << "Wrong object format" << std::endl;
        return;
    }

    float radium = fields[4].toDouble();

    for (int i = 0; i < numProp; i++) {
        DataTransform scene_transform = dataToVirtualTransform(
                DataTransform(fields[2].toDouble(), fields[3].toDouble(), 0), i);

        vec2 oPos(scene_transform.posX, scene_transform.posZ);
        if(numProp > 1){
            float angle = 2.0f*glm::pi<float>()/(float)numProp;
            vec2 dir(radium,0);
            glm::mat2x2 rot = glm::mat2x2( glm::cos(angle*i),glm::sin(angle*i),-glm::sin(angle*i),glm::cos(angle*i) );
            dir = rot*dir;
            oPos += dir;
        }

        Object *o;
        o = createDataObject(oPos.x, oPos.y,
                             1.0f, 1.0f,
                             props[i]);
        o->setMaterial(createMaterial(i));
        scene->objects.push_back(o);
        objectList.push_back(o);
    }
}

void AnimationDataReader::frameFound(QStringList fields){
    if (fields.size() != 1) {
        std::cerr << "Wrong frame format" << std::endl;
        return;
    }else{
        std::cout << "Frame found: " << frame_idx << std::endl;
        frame_idx++;
    }
}

void AnimationDataReader::dataFound(QStringList fields){
    if (fields.size() != 2+numProp) {
        std::cerr << "Wrong data format" << std::endl;
        return;
    }

    int dataId = fields[1].toInt()-1;
    for (int i = 0; i < numProp; i++){
        float dataS = fields[2+i].toDouble();
        double rs = (dataS - propLims[i].min) / (propLims[i].max - propLims[i].min);
        double scene_s = scene_slim.min + rs * (scene_slim.max - scene_slim.min);
        Animation a;
        a.frameIni = frame_idx-1;
        a.frameFinal = frame_idx-1;
        a.transf = new AnimationDataTG(scene_s);
        objectList[dataId*numProp + i]->addAnimation(a);
    }
}

DataTransform AnimationDataReader::dataToVirtualTransform(DataTransform data, int prop) {
    double rx = (data.posX - data_xlim.min) / (data_xlim.max - data_xlim.min);
    double rz = (data.posZ - data_zlim.min) / (data_zlim.max - data_zlim.min);
    Range propLim = propLims[prop];
    double rs = (data.scale - propLim.min) / (propLim.max - propLim.min);

    double scene_x = scene_xlim.min + rx * (scene_xlim.max - scene_xlim.min);
    double scene_z = scene_zlim.min + rz * (scene_zlim.max - scene_zlim.min);
    double scene_s = scene_slim.min + rs * (scene_slim.max - scene_slim.min);
    DataTransform vt = DataTransform(scene_x, scene_z, scene_s);
    return vt;
}


Object *createDataObject(double x, double z, double s, double v, ObjectFactory::OBJECT_TYPES t) {
    Object *o;
    switch (t) {
        case ObjectFactory::SPHERE:
            o = new Sphere(vec3(x, 0.0, z), s, v);
            break;
        case ObjectFactory::CYLINDER:
            o = new Cylinder(vec3(x, 0.0, z), 1.0, s, v);
            break;
    }
    return o;
}

Material* AnimationDataReader::createMaterial(int prop){
    Range propLim = propLims[prop];
    vec3 color = propColors[prop%propColors.size()];
    return new Metal(vec3(0,0,0), color, vec3(0.8,0.8,0.8), 100, vec3(0,0,0), 0.5);
}