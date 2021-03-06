#include "Controller.h"

Controller::Controller(QString fileName, SceneFactory::SCENE_FACTORIES s, RenderFactory::RENDER_TYPES rt) {


    // ETAPA 1: Coonstrucció de l'escena
    // Pot ser una escena virtual (no provinent de dades)
    // O pot ser una escena que prové de dades geolocalitzades (Visualization Mapping)
    // S'usa un Abstract Factory per a construir l'escena, la camera
    //  Fase 2: crear les llums i pasar-les a l'escena
    //  RESPOSTA: Millor que ho fagi cada scene factory
    SceneFactory *scFac = createFactory(s);
    Scene *scene;
    scene = scFac->createScene(fileName);
    Camera *camera;
    camera = scFac->createCamera();

    // Es crea aqui només un ColorMap
    //   Fase 2: Cal tenir en compte tants ColorMaps com numero de propietats, en el cas que el fitxer de dades en
    //  tingui més d'una. On es pot fer això millor?
    //  Resposta: aixo es fa a DataReader.

    //ColorMap *colorMap = scFac->createColorMap(ColorMapStatic::ColorMapType::COLOR_MAP_TYPE_INFERNO);
    //scene->setMaterials(colorMap);

    //  Fase 1: Cal posar les dimensions de l'escena virtual usant setDimensions de la classe Scene
    //  RESPOSTA: Millor que ho fagi cada scene factory


    // ETAPA 2: Inicialitzacio del Rendering
    // usa un Factory Template per a construir el tipus de render
    render = RenderFactory::getInstance()->getRender(rt);
    render->setScene(scene);
    render->setCamera(camera);

}

Controller::Controller(RenderFactory::RENDER_TYPES rt) {


    // ETAPA 1: Coonstrucció de l'escena
    // Pot ser una escena virtual (no provinent de dades)
    // O pot ser una escena que prové de dades geolocalitzades (Visualization Mapping)
    // S'usa un Abstract Factory per a construir l'escena, la camera
    // Fase 2: crear les llums i pasar-les a l'escena
    SceneFactoryVirtual *scFac = new SceneFactoryVirtual();
    Scene *scene;
    scene = scFac->createScene();
    Camera *camera;
    camera = scFac->createCamera();

    // Fase 2: Cal tenir en compte tants ColorMaps com numero de propietats, en el cas que el fitxer de dades en
    //  tingui més d'una. On es pot fer això millor?
    // AIXO ES GESTIONA A DATAREADER. AQUI NO ES FA RES


    //  Fase 1: Cal posar les dimensions de l'escena virtual usant setDimensions de la classe Scene
    //Aixo es gestiona a cada scenefactory


    // ETAPA 2: Inicialitzacio del Rendering
    // usa un Factory Template per a construir el tipus de render
    render = RenderFactory::getInstance()->getRender(rt);
    render->setScene(scene);
    render->setCamera(camera);

}

void Controller::start(int argc, char **argv) {
    // ETAPA 2: Activació del Rendering
    render->startRendering(argc, argv);
}

SceneFactory *Controller::createFactory(SceneFactory::SCENE_FACTORIES factory) {
    if (factory == SceneFactory::SCENE_FACTORIES::VIRTUAL) {
        return new SceneFactoryVirtual();
    } else if (factory == SceneFactory::SCENE_FACTORIES::DATA) {
        return new SceneFactoryData();
    }
    return nullptr;
}
