//
// Created by eudald on 4/2/20.
//

#ifndef RAYDATA_ANIMATIONDATAREADER_H
#define RAYDATA_ANIMATIONDATAREADER_H


#include "Scene.h"
#include "DataReader.h"
#include "Metal.h"
#include "TG.h"
#include "Object.h"


class AnimationDataTG: public TG{
public:
    AnimationDataTG(float v){
        value = v;
    }
    float value;
};


class AnimationDataReader {
public:
    AnimationDataReader(Scene* s);
    void readFile(QString fileName);
private:
    void fileLineRead(QString lineReaded);
    void baseFound(QStringList list);
    void limitsFound(QStringList list);
    void propFound(QStringList list);
    void objectFound(QStringList list);
    void frameFound(QStringList list);
    void dataFound(QStringList list);
    DataTransform dataToVirtualTransform(DataTransform data, int prop);
    Material* createMaterial(int prop);

    Scene *scene;
    vector<Object*> objectList;

    int frame_idx = 0;
    Range data_xlim;
    Range data_zlim;
    int numProp;
    vector<ObjectFactory::OBJECT_TYPES> props;
    vector<Range> propLims;
    vector<vec3> propColors;
    vector<float> scales;

    Range scene_xlim;
    Range scene_zlim;
    Range scene_slim;

    vec3 defaultPlaneColor = vec3(0.2, 0.2, 1.0);
};


#endif //RAYDATA_ANIMATIONDATAREADER_H
