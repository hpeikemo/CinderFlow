//
//  FieldController.h
//  CinderFlow
//
//  Created by Hans Petter Eikemo on 7/6/10.
//  Copyright 2010 Apt. All rights reserved.
//

#include <boost/numeric/ublas/matrix.hpp>
#include "cinder/Vector.h"
#include <list>

using namespace boost::numeric::ublas;
using namespace std;

struct vectorCell {
    ci::Vec2f movement;
    ci::Vec2f change;
};

struct particle {
    ci::Vec2f position;
    ci::Vec2f momentum;
};


class FieldController {
public:
    FieldController();
    void draw();
    void update();
    
    ci::Vec2f screenRatio;
    
    matrix<vectorCell>  field;        
    list<particle>  particles;

};