//
//  main.h
//  CinderFlow
//
//  Created by Hans Petter Eikemo on 7/6/10.
//  Copyright 2010 Apt. All rights reserved.
//

#include "cinder/app/AppBasic.h"

class Main : public ci::app::AppBasic {
public:
	void prepareSettings( Settings *settings );
	void draw();    
};
