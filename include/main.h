//
//  main.h
//  CinderFlow
//
//  Created by Hans Petter Eikemo on 7/6/10.
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
};
