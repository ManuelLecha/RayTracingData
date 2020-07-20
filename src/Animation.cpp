#include "Animation.h"

Animable::Animable() {

}

Animable::~Animable() {

}

void Animable::addAnimation(Animation anim) {
    animFrames.push_back(anim);
}

void Animable::update(int nframe) {
    int indx = -1;
    for(int i = 0; i < animFrames.size(); i++){
        if( nframe >= animFrames[i].frameIni && nframe <= animFrames[i].frameFinal ){
            indx = i;
            break;
        }
    }
    if(indx!=-1) aplicaTG(animFrames[indx].transf);
}
