//
//  FieldController.h
//  CinderFlow
//
//  Created by Hans Petter Eikemo on 7/6/10.
//  Copyright 2010 Apt. All rights reserved.
//

#include <boost/numeric/ublas/matrix.hpp>
#include "cinder/Vector.h"
#include "cinder/Color.h"
#include <list>

struct vectorCell {
    ci::Vec2f movement;
    ci::Vec2f change;
};

struct particle {
    ci::Vec2f position;
    ci::Vec2f momentum;
    ci::ColorAf color;
};


class FieldController {
public:
    FieldController();
    void setup();
    void draw();
    void update();
    
    ci::Vec2f screenRatio;
    
    boost::numeric::ublas::matrix<vectorCell>  field;        
    std::list<particle>  particles;

};