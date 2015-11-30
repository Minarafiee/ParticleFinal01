#include "demoParticle.h"

//------------------------------------------------------------------
demoParticle::demoParticle(){
	attractPoints = NULL;
}

//------------------------------------------------------------------
void demoParticle::setMode(particleMode newMode){
	mode = newMode;
}

//------------------------------------------------------------------
void demoParticle::setAttractPoints( vector <ofPoint> * attract ){
	attractPoints = attract;
}

//------------------------------------------------------------------
void demoParticle::reset(){
	//the unique val allows us to set properties slightly differently for each particle
	uniqueVal = ofRandom(-10000, 10000);
	
	pos.x = ofRandomWidth();
	pos.y = ofRandomHeight();
	
	vel.x = ofRandom(0.001, 1);//the more the number the slower and vaster
	vel.y = ofRandom(1,0.001);
	
	frc   = ofPoint(0,0,0);
	
	scale = ofRandom(0.1, 0.1);
	
	if( mode == PARTICLE_MODE_NOISE ){
		drag  = ofRandom(0.97, 1.5);
		vel.y = fabs(vel.y) * 2.0; //make the particles all be going down
	}else{
		drag  = ofRandom(0.95, 1);//(0.95, 0.998)
	}
}


//------------------------------------------------------------------
void demoParticle::update(){

	//1 - APPLY THE FORCES BASED ON WHICH MODE WE ARE IN 
	
	if( mode == PARTICLE_MODE_ATTRACT ){
		ofPoint attractPt(ofGetMouseX(), ofGetMouseY());
		frc = attractPt-pos.y;
        
        
        // we get the attraction force/vector by looking at the mouse pos relative to our pos
		frc.normalize(); //by normalizing we disregard how close the particle is to the attraction point
		
		vel *= drag; //apply drag
		vel += frc * 0.1; //apply force
	}
     	
	
	//2 - UPDATE OUR POSITION
	
	pos += vel; 
	
	
	//3 - (optional) LIMIT THE PARTICLES TO STAY ON SCREEN
	//we could also pass in bounds to check - or alternatively do this at the ofApp level
	if( pos.x > ofGetWidth() ){
		pos.x = ofGetWidth();
		vel.x *= -2.0;
	}else if( pos.x < 0 ){
		pos.x = 0;
		vel.x *= -2.0;
	}
	if( pos.y > ofGetHeight() ){
		pos.y = ofGetHeight();
		vel.y *= -2.0;
	}
	else if( pos.y < 0 ){
		pos.y = 0;
		vel.y *= -2.0;
	}	
		
}

//------------------------------------------------------------------
void demoParticle::draw(){

	if( mode == PARTICLE_MODE_ATTRACT ){
		ofSetColor(255, 255, 255);
	}
		ofCircle(pos.x, pos.y, scale * 5.0);
}

