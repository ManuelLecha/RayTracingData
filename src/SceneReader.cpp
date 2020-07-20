#include "SceneReader.h"
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <include/ObjectFactory.h>
#include <include/LightPuntual.h>

SceneReader::SceneReader(Scene *s) {
    scene = s;

}

void SceneReader::readFile(QString fileName) {

    std::cout << fileName.toStdString() << std::endl;

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

// TODO: Fase 1: Cal afegir més tipus d'objectes
void SceneReader::fileLineRead(QString lineReaded) {
    QStringList fields = lineReaded.split(",");
    if (QString::compare("Sphere", fields[0], Qt::CaseInsensitive) == 0)
        sphereFound(fields);
    else if (QString::compare("Triangle", fields[0], Qt::CaseInsensitive) == 0)
        triangleFound(fields);
    else if (QString::compare("Cylinder", fields[0], Qt::CaseInsensitive) == 0)
        cylinderFound(fields);
    else if (QString::compare("brobject", fields[0], Qt::CaseInsensitive) == 0)
        BrObjectFound(fields);
    else if (QString::compare("Base", fields[0], Qt::CaseInsensitive) == 0)
        baseFound(fields);
    else if (QString::compare("LightP", fields[0], Qt::CaseInsensitive) == 0)
        lightFound(fields);
    else
        std::cerr << "Element unknown" << std::endl;
}

void SceneReader::lightFound(QStringList fields) {
    if (fields.size() != 16) {
        std::cerr << "Wrong sphere format" << std::endl;
        return;
    }
    LightPuntual *light = new LightPuntual(
            vec3(fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble()),
            vec3(fields[4].toDouble(), fields[5].toDouble(), fields[6].toDouble()),
            vec3(fields[7].toDouble(), fields[8].toDouble(), fields[9].toDouble()),
            vec3(fields[10].toDouble(), fields[11].toDouble(), fields[12].toDouble()),
            fields[13].toDouble(), fields[14].toDouble(), fields[15].toDouble());
    scene->lights.push_back(light);
}

void SceneReader::sphereFound(QStringList fields) {
    if (fields.size() != 20) {
        std::cerr << "Wrong sphere format" << std::endl;
        return;
    }
    Object *o;
    ObjectFactory::OBJECT_TYPES objType = ObjectFactory::OBJECT_TYPES::SPHERE;
    ObjectFactory::OBJECT_MATERIALS objMaterials = ObjectFactory::getMaterialFromText(fields[15].toStdString());
    double values[18]{
            fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble(),
            fields[4].toDouble(), fields[5].toDouble(), fields[6].toDouble(),
            fields[7].toDouble(), fields[8].toDouble(), fields[9].toDouble(),
            fields[10].toDouble(), fields[11].toDouble(), fields[12].toDouble(),
            fields[13].toDouble(), fields[14].toDouble(), fields[16].toDouble(),
            fields[17].toDouble(), fields[18].toDouble(), fields[19].toDouble()
    };
    o = ObjectFactory::getInstance()->createObject(objType, objMaterials, values);
    scene->objects.push_back(o);
}

void SceneReader::triangleFound(QStringList fields) {
    if (fields.size() != 25) {
        std::cerr << "Wrong triangle format" << std::endl;
        return;
    }
    Object *o;
    ObjectFactory::OBJECT_TYPES objType = ObjectFactory::OBJECT_TYPES::TRIANGLE;
    ObjectFactory::OBJECT_MATERIALS objMaterials = ObjectFactory::getMaterialFromText(fields[20].toStdString());
    double values[23]{
            fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble(),
            fields[4].toDouble(), fields[5].toDouble(), fields[6].toDouble(),
            fields[7].toDouble(), fields[8].toDouble(), fields[9].toDouble(),
            fields[10].toDouble(), fields[11].toDouble(), fields[12].toDouble(),
            fields[13].toDouble(), fields[14].toDouble(), fields[15].toDouble(),
            fields[16].toDouble(), fields[17].toDouble(), fields[18].toDouble(),
            fields[19].toDouble(), fields[21].toDouble(), fields[22].toDouble(),
            fields[23].toDouble(), fields[24].toDouble()
    };
    o = ObjectFactory::getInstance()->createObject(objType, objMaterials, values);
    scene->objects.push_back(o);
}

void SceneReader::cylinderFound(QStringList fields) {
    if (fields.size() != 21) {
        std::cerr << "Wrong cylinder format" << std::endl;
        return;
    }
    Object *o;
    ObjectFactory::OBJECT_TYPES objType = ObjectFactory::OBJECT_TYPES::CYLINDER;
    ObjectFactory::OBJECT_MATERIALS objMaterials = ObjectFactory::getMaterialFromText(fields[16].toStdString());
    double values[19]{
            fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble(),
            fields[4].toDouble(), fields[5].toDouble(), fields[6].toDouble(),
            fields[7].toDouble(), fields[8].toDouble(), fields[9].toDouble(),
            fields[10].toDouble(), fields[11].toDouble(), fields[12].toDouble(),
            fields[13].toDouble(), fields[14].toDouble(), fields[15].toDouble(),
            fields[17].toDouble(), fields[18].toDouble(), fields[19].toDouble(),
            fields[20].toDouble()
    };
    o = ObjectFactory::getInstance()->createObject(objType, objMaterials, values);
    scene->objects.push_back(o);
}

// Exemple de base:
// Base,  plane,  0.0,  1.0,  0.0,  -0.5,
void SceneReader::baseFound(QStringList fields) {
    if (fields.size() != 22) {
        std::cerr << "Wrong base format" << std::endl;
        return;
    }
    // TODO Fase 1: Cal fer un pla acotat i no un pla infinit. Les dimensions del pla acotat seran les dimensions de l'escena en x i z
    Object *o;
    ObjectFactory::OBJECT_TYPES objType;
    if (QString::compare("plane", fields[1], Qt::CaseInsensitive) == 0)
        objType = ObjectFactory::OBJECT_TYPES::PLANE;
    else if (QString::compare("sphere", fields[1], Qt::CaseInsensitive) == 0)
        objType = ObjectFactory::OBJECT_TYPES::SPHERE;

    ObjectFactory::OBJECT_MATERIALS objMaterials = ObjectFactory::getMaterialFromText(fields[16].toStdString());
    double values[18]{
            fields[2].toDouble(), fields[3].toDouble(), fields[4].toDouble(),
            fields[5].toDouble(), fields[6].toDouble(), fields[7].toDouble(),
            fields[8].toDouble(), fields[9].toDouble(), fields[10].toDouble(),
            fields[11].toDouble(), fields[12].toDouble(), fields[13].toDouble(),
            fields[14].toDouble(), fields[15].toDouble(), fields[18].toDouble(),
            fields[19].toDouble(), fields[20].toDouble(), fields[21].toDouble()
    };
    o = ObjectFactory::getInstance()->createObject(objType, objMaterials, values, fields[17]);
    scene->objects.push_back(o);
    // TODO Fase 4: llegir textura i afegir-la a l'objecte. Veure la classe Texture
}

void SceneReader::BrObjectFound(QStringList fields) {

    // TODO Fase 1: Per incloure BrObjecte
    //  Es suposa que serà una linia del fitxer de l'estil

    if (fields.size() != 21) {
        std::cerr << "Wrong brObject format" << std::endl;
        return;
    }
    Object *o;
    ObjectFactory::OBJECT_TYPES objType = ObjectFactory::OBJECT_TYPES::BROBJECT;
    ObjectFactory::OBJECT_MATERIALS objMaterials = ObjectFactory::getMaterialFromText(fields[16].toStdString());
    double values[18]{
            fields[2].toDouble(), fields[3].toDouble(), fields[4].toDouble(),
            fields[5].toDouble(), fields[6].toDouble(), fields[7].toDouble(),
            fields[8].toDouble(), fields[9].toDouble(), fields[10].toDouble(),
            fields[11].toDouble(), fields[12].toDouble(), fields[13].toDouble(),
            fields[14].toDouble(), fields[15].toDouble(), fields[17].toDouble(),
            fields[18].toDouble(), fields[19].toDouble(), fields[20].toDouble()
    };
    o = ObjectFactory::getInstance()->createObject(objType, objMaterials, values, fields[1]);
    scene->objects.push_back(o);
}
