//
//  ParticleSystem.h
//  CinderFlow
//
//  Created by Hans Petter Eikemo on 7/20/10.
//

#include "cinder/Vector.h"
#include "cinder/Color.h"

struct vectorCell {
    ci::Vec2f movement;
    ci::Vec2f change;
    vectorCell() : movement(0.0f,0.0f) , change(0.0f,0.0f) {};
};

struct particle {
    ci::Vec2f position;
    ci::Vec2f momentum;
    ci::ColorAf color;
    particle() : position(0.0f,0.0f) , momentum(0.0f,0.0f) {};
    
};

struct emitter {
    ci::Vec2f position;
    ci::ColorAf color;
    int timeToLive;
    unsigned emitRate;
};