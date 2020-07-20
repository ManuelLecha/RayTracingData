#include "DataReader.h"
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <sstream>
#include <include/ObjectFactory.h>
#include <include/MaterialTexture.h>
#include "Cylinder.h"
#include "Triangle.h"
#include "BaseMaterial.h"
#include "MaterialTexture.h"


static bool file_exists (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}


static Object *createDataObject(double x, double z, double s, double v, ObjectFactory::OBJECT_TYPES t);


DataReader::DataReader(Scene *s) {
    scene = s;
    numProp = 0;
    scene_xlim = Range(s->pmin.x, s->pmax.x);
    scene_zlim = Range(s->pmin.z, s->pmax.z);
    double xlen = scene_xlim.max - scene_xlim.min;
    double zlen = scene_xlim.max - scene_xlim.min;
    double minLen = xlen < zlen ? xlen : zlen;
    //scene_slim = Range(minLen/128.0f,minLen/32.0f);
    scene_slim = Range(0.5, 5);

}

void DataReader::readFile(QString fileName) {
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

// Fase 1: Cal afegir més tipus d'objectes
// DONE
void DataReader::fileLineRead(QString lineReaded) {

    QStringList fields = lineReaded.split(",");
    for (auto &str : fields) str = str.trimmed();

    std::cout << fields[0].toStdString() << std::endl;
    if (QString::compare("limits", fields[0], Qt::CaseInsensitive) == 0)
        limitsFound(fields);
    else if (QString::compare("base", fields[0], Qt::CaseInsensitive) == 0)
        baseFound(fields);
    else if (QString::compare("prop", fields[0], Qt::CaseInsensitive) == 0)
        propFound(fields);
    else if (QString::compare("data", fields[0], Qt::CaseInsensitive) == 0)
        dataFound(fields);
    else
        std::cerr << "Element unknown" << fields[0].toStdString() << std::endl;
}

void DataReader::baseFound(QStringList fields) {
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
        FittedPlane *o = new FittedPlane(vec3(0, fields[5].toDouble(), 0), vec3(0, 0, zlength / 2),
                                         -vec3(xlength / 2, 0, 0));
        if(file_exists(fields[6].toStdString())){
            o->setMaterial(new MaterialTexture(new Texture(fields[6]), o));
        }else{
            o->setMaterial(new BaseMaterial(defaultPlaneColor));
        }

        scene->objects.push_back(o);
        scene->basePlane = o;
        // TODO Fase 4: llegir textura i afegir-la a l'objecte. Veure la classe Texture
    }
    // TODO: Fase 3: Si cal instanciar una esfera com objecte base i no un pla, cal afegir aqui un else
}

void DataReader::limitsFound(QStringList fields) {
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

void DataReader::propFound(QStringList fields) {
    //prop numProp vmin vmax tipusGizmo templateId
    if (fields.size() < 5) {
        std::cerr << "Wrong propietat format" << std::endl;
        return;
    }
    numProp++;
    //  Fase 1: Cal guardar els valors per a poder escalar els objectes i el tipus de
    //  gizmo de totes les propietats (SPHERE, BR_OBJ, CILINDRE...)
    //  DONE
    propLims.push_back(Range(fields[2].toDouble(), fields[3].toDouble()));
    if (fields.size() == 6) {
        propMatId.push_back(fields[5].toInt());
    } else {
        propMatId.push_back(defaultMatId);
    }

    cout << fields[4].toStdString() << endl;
    if (QString::compare("sphere", fields[4], Qt::CaseInsensitive) == 0) {
        props.push_back(ObjectFactory::OBJECT_TYPES::SPHERE);
    } else if (QString::compare("cylinder", fields[4], Qt::CaseInsensitive) == 0) {
        props.push_back(ObjectFactory::OBJECT_TYPES::CYLINDER);
    } else if (QString::compare("br_object", fields[4], Qt::CaseInsensitive) == 0) {
        props.push_back(ObjectFactory::OBJECT_TYPES::BROBJECT);
    } else if (QString::compare("triangle", fields[4], Qt::CaseInsensitive) == 0) {
        props.push_back(ObjectFactory::OBJECT_TYPES::TRIANGLE);
    }else{
        std::cerr << "Element unknown" << fields[0].toStdString() << std::endl;
    }

    // Fase 2: Aquesta valors minim i maxim tambe serviran per mapejar el material des de la paleta
    // DONE

}


void DataReader::dataFound(QStringList fields) {
    //data x z valor1 valor2...
    if (fields.size() != (numProp + 3)) {
        std::cerr << "Wrong data format" << std::endl;
        return;
    }
    float maxSize = 2;

    for (int i = 0; i < numProp; i++){
        float dataS = fields[3+i].toDouble();
        Range propLim = propLims[i];
        dataS = (dataS - propLim.min) / (propLim.max - propLim.min);
        dataS = scene_slim.min + dataS * (scene_slim.max - scene_slim.min);
        if(props[i] == ObjectFactory::SPHERE && dataS > maxSize)maxSize=dataS;
    }

    for (int i = 0; i < numProp; i++) {
        // TODO Fase 1: Cal colocar els objectes al seu lloc del mon virtual, escalats segons el valor i
        //  amb el seu color corresponent segons el seu ColorMap.
        //  DONE


        DataTransform scene_transform = dataToVirtualTransform(
                DataTransform(fields[1].toDouble(), fields[2].toDouble(), fields[3 + i].toDouble()), i);

        vec2 oPos(scene_transform.posX, scene_transform.posZ);
        if(numProp > 1){
            float angle = 2.0f*glm::pi<float>()/(float)numProp;
            vec2 dir(maxSize,0);
            glm::mat2x2 rot = glm::mat2x2( glm::cos(angle*i),glm::sin(angle*i),-glm::sin(angle*i),glm::cos(angle*i) );
            dir = rot*dir;
            oPos += dir;
        }

        Object *o;
        o = createDataObject(oPos.x, oPos.y,
                             scene_transform.scale, 1.0f,
                             props[i]);
        o->setMaterial(createMaterial(fields[3 + i].toDouble(), i));
        scene->objects.push_back(o);
    }
}

DataTransform DataReader::dataToVirtualTransform(DataTransform data, int prop) {
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

Material *DataReader::createMaterial(double value, int prop) {
    Range propLim = propLims[prop];
    double r = (value - propLim.min) / (propLim.max - propLim.min);
    vec3 color = dataTemplate.getColor(prop, value);
    return dataTemplate.getMaterial(propMatId[prop], color);
}

Object *createDataObject(double x, double z, double s, double v, ObjectFactory::OBJECT_TYPES t) {
    Object *o;
    switch (t) {
        case ObjectFactory::SPHERE:
            o = new Sphere(vec3(x, 0.0, z), s, v);
            break;
        case ObjectFactory::TRIANGLE: {
            vec3 v1 = vec3(0, 1.5, 0);
            vec3 v2 = vec3(-0.866025404, 0.0, 0);
            vec3 v3 = vec3(0.866025404, 0.0, 0);
            Triangle *t = new Triangle(v1, v2, v3, v);
            t->translate(vec3(x, 0, z));
            t->scale(s);
            o = t;
            break;
        }
        case ObjectFactory::CYLINDER:
            o = new Cylinder(vec3(x, 0.0, z), 1.0, s, v);
            break;
        case ObjectFactory::BROBJECT:
            break;
        default:
            o = new Sphere(vec3(x, 0.0, z), s, v);
            break;
    }
    return o;
}
