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

void Main::draw() {
    gl::setMatricesWindow( getWindowSize() );
	gl::clear( Color( 0.8f, 0.8f, 0.8f ) );
	glColor3f( 0.4f, 0.4f, 0.4f );
    
    field.draw();
}


CINDER_APP_BASIC( Main, RendererGl );
