//
//  FieldController.h
//  CinderFlow
//
//  Created by Hans Petter Eikemo on 7/6/10.
//  Copyright 2010 Apt. All rights reserved.
//

#include <boost/numeric/ublas/matrix.hpp>
#include "cinder/Vector.h"

using namespace boost::numeric::ublas;

struct vectorCell {
    ci::Vec2f movement;
    ci::Vec2f change;
};


class FieldController {
public:
    FieldController();
    void draw();
    void update();        
    
    matrix<vectorCell> field;
};