//
//  FieldController.h
//  CinderFlow
//
//  Created by Hans Petter Eikemo on 7/6/10.
//

#include <boost/numeric/ublas/matrix.hpp>
#include "cinder/Vector.h"
#include "cinder/Color.h"
#include <list>


struct vectorCell {
    ci::Vec2f movement;
    ci::Vec2f change;
    vectorCell() : movement(0.0f,0.0f) , change(0.0f,0.0f) {};
};

struct particle {
    ci::Vec2f position;
    ci::Vec2f momentum;
    ci::ColorAf color;
    particle() : position(0.0f,0.0f) , momentum(0.0f,0.0f) {};

};


class FieldController {
public:
    FieldController();
    void setup();
    void draw();
	void drawDebug();

    void update();
    
    ci::Vec2f screenRatio;
    
    boost::numeric::ublas::matrix<vectorCell>  field;        
    std::list<particle>  particles;

};