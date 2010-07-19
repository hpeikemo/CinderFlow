//
//  FieldController.cpp
//  CinderFlow
//
//  Created by Hans Petter Eikemo on 7/6/10.
//  Copyright 2010 Apt. All rights reserved.
//


#include "cinder/gl/gl.h"
#include "FieldController.h"
#include <stdio.h>
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/Rect.h"
#include <stdlib.h>
#include <math.h>
#include "cinder/Color.h"

using namespace ci;
using namespace ci::gl;
using namespace std;
using namespace boost::numeric::ublas;

unsigned fieldSize = 40;

struct sector { 
    int x, y;
    double a;
} neighbour[8];


FieldController::FieldController() {
    field = matrix<vectorCell>(fieldSize,fieldSize);
        
    double a=0;
    for (unsigned i=0; i<8; ++i) {    
        neighbour[i].a = a;
        neighbour[i].x = round(sin(a));
        neighbour[i].y = round(cos(a));
        a += M_PI_4;
    }    
    
};


void FieldController::setup() {
        
    for (unsigned i = 0; i < field.size1(); ++ i) {
        for (unsigned j = 0; j < field.size2(); ++ j) {
            field(i, j).movement = Rand::randVec2f();
            field(i, j).change *= 0;
        }        
    }
    
    //field(10,10).movement = Vec2f(1,0.3f);
        
    /**/
    for (float i = 0; i < field.size1(); i+= 0.5125f) {
        for (float j = 0; j < field.size2(); j+= 0.5125f) {
            particle p;
            Vec2f r = Rand::randVec2f() * 1.3f;
            Vec2f pos = Vec2f(i,j)+r;            
            p.position = pos;
            p.momentum *= 0;
            p.color = ColorAf(0.6f,0.6f,0.6f,0.7f);
            particles.push_back(p);            
        }
    } 
    /**/    
    
};

double angleDiff(double angle1, double angle2) {
    double diff = angle2 - angle1;
    while (diff < -M_PI) diff += M_PI*2;
    while (diff > M_PI) diff -= M_PI*2;
    return diff;
};

void FieldController::update() {
    
    unsigned s1 = field.size1();
    unsigned s2 = field.size2();
    
    for (unsigned i = 0; i < s1; ++ i) {
        for (unsigned j = 0; j < s2; ++ j) {
            Vec2f &movem = field(i, j).movement;
            double cellA = atan2(movem.y,movem.x); 
                        
            for (unsigned n=0; n<8; ++n) {                                    
                double diff = fabs( angleDiff(neighbour[n].a, cellA) );
                int ix = i+neighbour[n].x;
                int jy = j+neighbour[n].y;
                if (diff < 2.0f && ix < s1 && jy < s2 && jy >= 0 && ix >= 0)
                    field(ix,jy).change += movem * 0.05f * (2-diff)/2;
            }                                    
        }        
    }
    
    for (unsigned i = 0; i < field.size1 (); ++ i) {
        for (unsigned j = 0; j < field.size2 (); ++ j) {            
            Vec2f r = Rand::randVec2f() * 0.2f;            
            field(i, j).movement += field(i, j).change + r;
            field(i, j).movement.limit(1.0f);            
            field(i, j).change *= 0;
        }        
    }
    
    for( list<particle>::iterator p = particles.begin(); p != particles.end(); ++p ){
        int x = p->position.x;
        int y = p->position.y;
        
        if (x < s1 && y < s2 && x >= 0 && x >= 0) {
            Vec2f r = Rand::randVec2f() * 0.001f;
            p->momentum += field(x, y).movement*0.0002f+r;
            p->position += p->momentum;
            p->momentum *= 0.99;
        } else {
            particles.erase(p);
        }        
	}
    
}

void FieldController::draw() {

    Vec2i wSize = cinder::app::getWindowSize();
    screenRatio = wSize/Vec2f(fieldSize,fieldSize);    
            
    /*//
    enableAlphaBlending();
    glColor4f(0.0f, 0.0f, 0.0f, 0.0005f);
    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);    
    drawSolidRect( Rectf(0,0,wSize.x,wSize.y) );
    //*/
    
    /*//
    glColor3f( 0.0f, 0.2f, 0.2f );    
    for(unsigned i=0; i <= fieldSize; i++) {            
        drawLine( Vec2f(0,i), Vec2f(fieldSize,i) );
        drawLine( Vec2f(i,0), Vec2f(i,fieldSize) );
     }
    //*/
    /*//
    gl::clear( Color( 0.0f, 0.0f, 0.0f ) );
    glColor3f( 1.0f, 0.4f, 0.4f );
    for (unsigned i = 0; i < field.size1(); ++ i) {
        for (unsigned j = 0; j < field.size2(); ++ j) {
            Vec2f cellStart = Vec2f(i+0.5f,j+0.5f);
            Vec2f cellEnd = cellStart+ field(i, j).movement;         
            drawLine( cellStart * screenRatio, cellEnd * screenRatio );
        }        
     } 
     //*/
    
    //gl::clear( Color( 0.0f, 0.0f, 0.0f ) );

    
    glDepthMask( GL_FALSE );
	glDisable( GL_DEPTH_TEST );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE );    
    
    for( list<particle>::iterator p = particles.begin(); p != particles.end(); ++p ){
        p->color.a = 0.05f;
        glColor4f( p->color );        
//        if (p->momentum.length() > 0.0025f)
            gl::drawSolidCircle( p->position * screenRatio, 1.0f );
	}

};