#ifndef DATAREADER_H
#define DATAREADER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <vector>
#include "glm/glm.hpp"
#include "Scene.h"
#include "ObjectFactory.h"
#include "ColorMapStatic.h"
#include "DataTemplate.h"

struct Range {
    double min;
    double max;

    Range(double min, double max) {
        this->min = min;
        this->max = max;
    }

    Range() {
        this->min = 0;
        this->max = 0;
    }
};

struct DataTransform {
    double posX, posZ;
    double scale;

    DataTransform() {
        this->posX = 0;
        this->posZ = 0;
        this->scale = 0;
    }

    DataTransform(double posX, double posZ, double scale) {
        this->posX = posX;
        this->posZ = posZ;
        this->scale = scale;
    }
};

class DataReader {
public:
    explicit DataReader();

    DataReader(Scene *s);

    void readFile(QString fileName);

protected:
    virtual void fileLineRead(QString lineReaded);

    Scene *scene;

    void baseFound(QStringList list);

    void limitsFound(QStringList list);

    void propFound(QStringList list);

    void dataFound(QStringList list);

private:
    DataTransform dataToVirtualTransform(DataTransform datam, int prop);

    Material *createMaterial(double value, int prop);

    DataTemplate dataTemplate;

private:
    Range data_xlim;
    Range data_zlim;
    int numProp;
    vector<ObjectFactory::OBJECT_TYPES> props;
    vector<Range> propLims;

    vector<int> propMatId;

    int defaultMatId = 1;

    Range scene_xlim;
    Range scene_zlim;
    Range scene_slim;

    vec3 defaultPlaneColor = vec3(0.2, 0.2, 1.0);
};


#endif // DataReader_H
