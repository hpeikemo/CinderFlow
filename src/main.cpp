//
//  main.cpp
//  CinderFlow
//
//  Created by Hans Petter Eikemo on 7/6/10.
//  Copyright 2010. All rights reserved.
//

#include "main.h"
#include "FieldController.h"
#include "cinder/Rand.h"
#include "cinder/Color.h"
#include "cinder/Timer.h"
#include "cinder/ImageIo.h"
#include "cinder/utilities.h"
#include <stdio.h>
#include <list.h>
#include <OpenGL/OpenGL.h>

using namespace ci;
using namespace ci::app;
using namespace std;



//Globals:
Timer timer;
FieldController field;
bool debugMode;


//Screenshots:
unsigned screenCount;
void writeScreenshot() {
    char num[5];
    sprintf(num, "%05i", screenCount );    
    writeImage( getHomeDirectory() + "output/flow_" + num + ".png", copyWindowSurface() );    
    ++screenCount;
}


//Emitters:
struct emitter {
    Vec2f position;
    ColorAf color;
    int timeToLive;
    unsigned emitRate;
};


ColorAf getColor() {
//    return ColorAf(Rand::randFloat(),Rand::randFloat(),Rand::randFloat(),0.8f); //Random color;
    if ( (rand() % 2) == 1) {
        return ColorAf(0.0f,0.2f,0.3f,0.5f);    
        
    } else {
        return ColorAf(0.3f,0.2f,0.0f,0.5f);            
        
    }
    
    
}

list<emitter> emitters;
void createEmitter(Vec2f pos, unsigned ttl=70) {
    emitter e;
    e.position = pos;
    e.color = getColor();
    e.emitRate = 1+rand()%9;
    e.timeToLive = ttl;
    emitters.push_back(e);    
}

void updateEmitters() {
    for( list<emitter>::iterator em = emitters.begin(); em != emitters.end(); ++em ){
        for (unsigned i = 0;i < em->emitRate; ++i) {
            Vec2f r = Rand::randVec2f() * 0.06f;
            particle p;
            p.position = (em->position)/field.screenRatio ;
            p.momentum = r;
            p.color = em->color;
            field.particles.push_back(p);            
        }
        --em->timeToLive;
        if (em->timeToLive < 1)
            emitters.erase(em);
    }
}


//Main impl:

void Main::prepareSettings( Settings* settings ) {
//    settings->setFullScreen( true );
    settings->setWindowSize( 1280 , 720 );
    settings->setFrameRate( 30.0f );
}

void Main::setup() {
    field.setup();
    gl::clear( Color( 0.0f, 0.0f, 0.0f ) );
}

void Main::keyDown( KeyEvent event ) {
	if( event.getChar() == 'f' ) {
        setFullScreen( ! isFullScreen() );
        gl::clear( Color( 0.0f, 0.0f, 0.0f ) );
    }
    if( event.getChar() == 'd' ) { 
        debugMode = !debugMode;
    }
        
}

void Main::mouseDown( MouseEvent event ) {	
    createEmitter(event.getPos());        
}

/*
void Main::mouseDrag( MouseEvent event ) {
    mouseEmitter->position = event.getPos();
    mouseEmitter->timeToLive = 1000;
}

void Main::mouseUp( MouseEvent event ) {	
    mouseEmitter->timeToLive = 0;
}
*/

void Main::update() {
    timer.start();

    field.update();
    updateEmitters();

    timer.stop();
    //cout << "update in "<< timer.getSeconds() << "\n";
    
    if (field.particles.size() < 10000 && Rand::randFloat() > 0.9f) {
        Vec2i wSize = getWindowSize();
        Vec2f pos = wSize/2 + (Rand::randVec2f() * 50);
        createEmitter( pos, 400 * Rand::randFloat() );
        cout << field.particles.size() << " particles" << endl;
    }
        
}


void Main::draw() {
    timer.start();
    
    gl::setMatricesWindow( getWindowSize() );
            
    if (debugMode) {
        field.drawDebug();
    } else {
        field.draw();
    }
        
    
    timer.stop();
    //cout << "draw in "<< timer.getSeconds() << "\n";
    //  writeScreenshot();
}

CINDER_APP_BASIC( Main, RendererGl );
