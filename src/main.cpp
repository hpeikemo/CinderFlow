//
//  main.cpp
//  CinderFlow
//
//  Created by Hans Petter Eikemo on 7/6/10.
//  Copyright 2010 Apt. All rights reserved.
//

#include "main.h"
#include "FieldController.h"
#include "cinder/rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

FieldController field;

void Main::prepareSettings( Settings* settings ) {
    settings->setFullScreen( true );
}

void Main::setup() {
    gl::clear( Color( 0.0f, 0.0f, 0.0f ) );
}

Vec2f emitPosition;
bool emitting;

void Main::mouseDrag( MouseEvent event ) {	
    emitPosition = event.getPos();
}

void Main::mouseDown( MouseEvent event ) {	
    emitPosition = event.getPos();
    emitting = true;
}

void Main::mouseUp( MouseEvent event ) {	
    emitting = false;
}


void Main::draw() {
    gl::setMatricesWindow( getWindowSize() );
    
    if (emitting) { 
        for (unsigned i = 0;i < 2; ++i) {
            Vec2f r = Rand::randVec2f() * 0.05f;
            particle p;
            p.position = (emitPosition)/field.screenRatio ;
            p.momentum = r;        	        
            field.particles.push_back(p);            
        }
    }
    
    field.draw();
}


CINDER_APP_BASIC( Main, RendererGl );
