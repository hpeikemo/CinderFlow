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
#include <stdio.h>
#include <OpenGL/OpenGL.h>

using namespace ci;
using namespace ci::app;
using namespace std;

Timer timer;

FieldController field;

void Main::prepareSettings( Settings* settings ) {
    settings->setFullScreen( true );
    settings->setFrameRate( 90.0f );
}

void Main::setup() {
    field.setup();
    gl::clear( Color( 0.0f, 0.0f, 0.0f ) );
}

void Main::keyDown( KeyEvent event ) {
	if( event.getChar() == 'f' )
		setFullScreen( ! isFullScreen() );
}

Vec2f emitPosition;
ColorAf currentColor;
bool emitting;

void Main::mouseDown( MouseEvent event ) {	
    emitPosition = event.getPos();
    currentColor = ColorAf(Rand::randFloat(),Rand::randFloat(),Rand::randFloat(),0.8f);
    emitting = true;
}

void Main::mouseDrag( MouseEvent event ) {	
    emitPosition = event.getPos();
}

void Main::mouseUp( MouseEvent event ) {	
    emitting = false;
}

void Main::update() {
    timer.start();
    field.update();
    timer.stop();
    //cout << "update in "<< timer.getSeconds() << "\n";
}

void Main::draw() {
    timer.start();
    
    gl::setMatricesWindow( getWindowSize() );
    
    if (emitting) { 
        for (unsigned i = 0;i < 2; ++i) {
            Vec2f r = Rand::randVec2f() * 0.002f;
            particle p;
            p.position = (emitPosition)/field.screenRatio ;
            p.momentum = r;   
            p.color = currentColor;
            field.particles.push_back(p);            
        }
    }
    
    field.draw();
    
    timer.stop();
    //cout << "draw in "<< timer.getSeconds() << "\n";

}

CINDER_APP_BASIC( Main, RendererGl );


/*
 if( mSaveFrames ){
 writeImage( getHomeDirectory() + "HodginParticleRedux_" + toString( mCounter ) + ".png", copyWindowSurface() );
 }
 
 */