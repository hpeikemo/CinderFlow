//
//  main.h
//  CinderFlow
//
//  Created by Hans Petter Eikemo on 7/6/10.
//  Copyright 2010. All rights reserved.
//

#include "cinder/app/AppBasic.h"

class Main : public ci::app::AppBasic {
public:
	void prepareSettings( ci::app::AppBasic::Settings *settings );
    void setup();
	void update(); 
	void draw();    
    void keyDown( ci::app::KeyEvent event );
	void mouseDown( ci::app::MouseEvent event );
	void mouseUp( ci::app::MouseEvent event );
    void mouseDrag( ci::app::MouseEvent event );
};
