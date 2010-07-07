//
//  main.cpp
//  CinderFlow
//
//  Created by Hans Petter Eikemo on 7/6/10.
//  Copyright 2010 Apt. All rights reserved.
//

#include "main.h"
#include "FieldController.h"

using namespace ci;
using namespace ci::app;
using namespace std;

FieldController field;

void Main::prepareSettings( Settings* settings ) {
    
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
	gl::clear( Color( 0.8f, 0.8f, 0.8f ) );
	glColor3f( 0.4f, 0.4f, 0.4f );
    
    if (emitting) {        
        particle p;
        p.position = emitPosition/10;
        p.momentum *= 0;        	        
        field.particles.push_back(p);
    }
    
    field.draw();
}


CINDER_APP_BASIC( Main, RendererGl );
