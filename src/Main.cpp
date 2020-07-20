#include "Main.h"
#include "CustomOnlineScene.h"


// Metode principal del programa


int main(int argc, char **argv) {

    cout << "Init..." << endl;
    Q_INIT_RESOURCE(resources);
    CustomOnlineScene sfac;
    //Fase 0: Canviant fitxer d'esferes
    //Controller *controller = new Controller("://resources/spheres2.txt", SceneFactory::VIRTUAL, RenderFactory::ONLINE);
    //Controller *controller = new Controller("://resources/spheres2.txt", SceneFactory::VIRTUAL, RenderFactory::ONLINE);
    // Fase 1 carregar dades del fitxer de dades
    //Controller *controller = new Controller(":/resources/data0.txt", SceneFactory::DATA, RenderFactory::ONLINE);
    /* FASE 2   Proba en entorn controlat*/
    //Controller *controller = new Controller("://resources/mixTandC.txt", SceneFactory::VIRTUAL, RenderFactory::ONLINE);
    //Controller *controller = new Controller(RenderFactory::ONLINE);
    //FASE 3
    //Controller *controller = new Controller("://resources/mixTandC.txt", SceneFactory::VIRTUAL, RenderFactory::IMAGE);
    //Controller *controller = new Controller("://resources/mixTandC.txt", SceneFactory::VIRTUAL, RenderFactory::ONLINE);

    //Controller *controller = new Controller(RenderFactory::IMAGE);
    //controller->start(argc, argv);
    //sfac.startScene1(argc, argv, 0);
    //sfac.startScene1(argc, argv, 1);
    sfac.startScene1(argc, argv, 2);
    //sfac.startScene2(argc, argv);
    //sfac.startScene3(argc, argv);
}


