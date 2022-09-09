#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());
	ofRunApp( new ofApp());

}

/*
	Particles color - change by pressing "t"
	Pause simulation - pressing "p"
	Increase velocity - pressing "d"
	Decrease velocity - pressing "a"
	
	Magnifying quad
		-left click draws area
		-right click removes area
		-any particle entering will be tripled its size
*/
