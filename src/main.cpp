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
#include <OpenGL/OpenGL.h>

using namespace ci;
using namespace ci::app;
using namespace std;


unsigned screenCount;
void writeScreenshot() {
    writeImage( getHomeDirectory() + "output/flow_" + toString( screenCount ) + ".png", copyWindowSurface() );    
    ++screenCount;
}


Timer timer;

FieldController field;

void Main::prepareSettings( Settings* settings ) {
//    settings->setFullScreen( true );
    settings->setWindowSize( 620, 460 );
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
        for (unsigned i = 0;i < 6; ++i) {
            Vec2f r = Rand::randVec2f() * 0.01f;
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
//  writeScreenshot();
}

CINDER_APP_BASIC( Main, RendererGl );
