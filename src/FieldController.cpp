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
#include "cinder/Rand.h"
#include <stdlib.h>
#include <math.h>

using namespace ci;
using namespace ci::gl;
using namespace std;

unsigned fieldSize = 50;

FieldController::FieldController() {    
    field = matrix<vectorCell>(fieldSize,fieldSize);
    
    for (unsigned i = 0; i < field.size1(); ++ i) {
        for (unsigned j = 0; j < field.size2(); ++ j) {
            field(i, j).movement = Vec2f(-1.0f+(rand()%200)/100.0f,-1.0f+(rand()%200)/100.0f);
//            field(i, j).movement *= 0;

            field(i, j).change = Vec2f(0.0f,0.0f);
        }        
    }
    
    
    for (float i = 0; i < field.size1(); i+= 1.0f) {
        for (float j = 0; j < field.size2(); j+= 1.0f) {
            particle p;
            Vec2f pos = Vec2f(i,j);            
            p.position = pos;
            p.momentum *= 0;        	        
            particles.push_back(p);            
        }
    }
    
    
    field(2,2).movement = Vec2f(1.0f,0.3f); 
                
    //field(0,0).movement = Vec2f(2,1);
    
};


double angleDiff(double angle1, double angle2) {
    double diff = angle2 - angle1;
    while (diff < -M_PI) diff += M_PI*2;
    while (diff > M_PI) diff -= M_PI*2;
    return diff;
}


void FieldController::draw() {
    
    //ITERATE:
    
    unsigned s1 = field.size1();
    unsigned s2 = field.size2();
    
    for (unsigned i = 0; i < s1; ++ i) {
        for (unsigned j = 0; j < s2; ++ j) {
            Vec2f &movem = field(i, j).movement;
            double cellA = atan2(movem.x,movem.y); //HMM, burde vel egentlig være y,x men det gir feil sammenligning..
            
            
            for (double a=0; a<M_PI*2; a += M_PI_4) {
                int x = round(sin(a));
                int y = round(cos(a));
                double diff = fabs( angleDiff(a, cellA) );
                int ix = i+x;
                int jy = j+y;
                if (diff < 2.0f && ix < s1 && jy < s2 && jy >= 0 && ix >= 0)
                    field(i+x,j+y).change += movem * 0.05f * (2-diff)/2;
            }                                    
        }        
    }
    
    for (unsigned i = 0; i < field.size1 (); ++ i) {
        for (unsigned j = 0; j < field.size2 (); ++ j) {
//            field(i, j).movement *= 0.99f;
            
            Vec2f r = Rand::randVec2f() * 0.1f;
            
            field(i, j).movement += field(i, j).change + r;
            field(i, j).movement.limit(1.0f);            
            field(i, j).change *= 0;
        }        
    }
    
    for( list<particle>::iterator p = particles.begin(); p != particles.end(); ++p ){
        int x = p->position.x;
        int y = p->position.y;
        
        if (x < s1 && y < s2 && x >= 0 && x >= 0) {
            p->momentum += field(x, y).movement * 0.01f;
        }                
        p->position += p->momentum;
        p->momentum *= 0.5;        
	}
    
    
    //DRAW:

    //    scale( Vec3f(400/fieldSize,400/fieldSize,400/fieldSize) );
    
    
    scale( Vec3f(10,10,10) );    
    translate( Vec2f(1,1) );    
    
    glColor3f( 0.4f, 0.4f, 0.4f );
    
    for(unsigned i=0; i <= fieldSize; i++) {            
      //  drawLine( Vec2f(0,i), Vec2f(fieldSize,i) );
     //   drawLine( Vec2f(i,0), Vec2f(i,fieldSize) );
    }
        
    glColor3f( 1.0f, 0.4f, 0.4f );

    for (unsigned i = 0; i < field.size1(); ++ i) {
        for (unsigned j = 0; j < field.size2(); ++ j) {
            Vec2f cellStart = Vec2f(i+0.5f,j+0.5f);
            Vec2f cellEnd = cellStart+ field(i, j).movement;
         //   drawVector( cellStart, cellEnd );
            drawLine( cellStart, cellEnd );
        }        
    }
    
    
    glColor4f( 0.1f, 0.1f, 0.3f , 0.3f ); 
    
    for( list<particle>::iterator p = particles.begin(); p != particles.end(); ++p ){
        gl::drawSolidCircle( p->position, 1.0f ); 
        cout << p->position << "\n";
	}
    

    


};