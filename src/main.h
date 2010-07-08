//
//  main.h
//  CinderFlow
//
//  Created by Hans Petter Eikemo on 7/6/10.
//  Copyright 2010 Apt. All rights reserved.
//

#include "cinder/app/AppBasic.h"

using namespace ci;
using namespace ci::app;

class Main : public ci::app::AppBasic {
public:
	void prepareSettings( Settings *settings );
    void setup();
	void draw();    
	void mouseDown( MouseEvent event );
	void mouseUp( MouseEvent event );
    void mouseDrag( MouseEvent event );
};

