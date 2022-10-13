#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	
	int num = 1500;
	p.assign(num, Particle());
	currentMode = PARTICLE_MODE_ATTRACT;

	currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse"; 

	resetParticles();

	/*
		gui - init
	*/
	Button* colorToggle = new Button();

	colorToggle->setColor(ofColor::lightGray);
	colorToggle->setPosition(10, ofGetHeight() - 70);
	colorToggle->setDimensions(150, 50);
	colorToggle->setText("Current Color: ", ofColor::black, 5, 15);
	buttons.push_back(colorToggle);

	Button* pauseAndPlay = new Button();
	pauseAndPlay->setColor(ofColor::lightGray);
	pauseAndPlay->setPosition(170, ofGetHeight() - 70);
	pauseAndPlay->setDimensions(100, 50);
	pauseAndPlay->setListeners([](Button& b){}, [](Button& b){
		if(b.hasToggled())
			b.changeTextString("in-play");
		else
			b.changeTextString("in-pause");
	});
	pauseAndPlay->setText("in-pause", ofColor::black, 5, 15);
	buttons.push_back(pauseAndPlay);

	Button* increaseVel = new Button();
	increaseVel->setColor(ofColor::lightGray);
	increaseVel->setPosition(280, ofGetHeight() - 70);
	increaseVel->setDimensions(100, 50);
	increaseVel->setListeners([](Button& b){}, [](Button& b){
		//increment speed
	});
	increaseVel->setText("increment\nspeed", ofColor::black, 5, 15);
	buttons.push_back(increaseVel);

	Button* decreaseVel = new Button();
	decreaseVel->setColor(ofColor::lightGray);
	decreaseVel->setPosition(390, ofGetHeight() - 70);
	decreaseVel->setDimensions(100, 50);
	decreaseVel->setListeners([](Button& b){}, [](Button& b){
		//decrease speed
	});
	decreaseVel->setText("decrease\nspeed", ofColor::black, 5, 15);
	buttons.push_back(decreaseVel);

	Button* recordKs = new Button();
	recordKs->setColor(ofColor::lightGray);
	recordKs->setPosition(500, ofGetHeight() - 70);
	recordKs->setDimensions(100, 50);
	recordKs->setListeners([](Button& b){}, [](Button& b){
		//start recording
		if(b.hasToggled())
			b.changeTextString("record: on");
		else
			b.changeTextString("record: off");
	});
	recordKs->setText("record: off", ofColor::black, 5, 15);
	buttons.push_back(recordKs);

	Button* replayKs = new Button();
	replayKs->setColor(ofColor::lightGray);
	replayKs->setPosition(610, ofGetHeight() - 70);
	replayKs->setDimensions(100, 50);
	replayKs->setListeners([](Button& b){}, [](Button& b){
		//start replay
		if(b.hasToggled())
			b.changeTextString("replay: on");
		else
			b.changeTextString("replay: off");
	});
	replayKs->setText("replay: off", ofColor::black, 5, 15);
	buttons.push_back(replayKs);

	Button* pauseRepl = new Button();
	pauseRepl->setColor(ofColor::lightGray);
	pauseRepl->setPosition(720, ofGetHeight() - 70);
	pauseRepl->setDimensions(100, 50);
	pauseRepl->setListeners([](Button& b){}, [](Button& b){
		//start replay
		if(b.hasToggled())
			b.changeTextString("replay\nplaying");
		else
			b.changeTextString("replay\npause");
	});
	pauseRepl->setText("replay\npause", ofColor::black, 5, 15);
	buttons.push_back(pauseRepl);

	Button* selectEnabled = new Button();
	selectEnabled->setColor(ofColor::lightGray);
	selectEnabled->setPosition(830, ofGetHeight() - 70);
	selectEnabled->setDimensions(100, 50);
	selectEnabled->setListeners([](Button& b){}, [](Button& b){
		//toggle magnify select
		if(b.hasToggled())
			b.changeTextString("select\ndisabled");
		else
			b.changeTextString("select\nenabled");
	});
	selectEnabled->setText("select\nenabled", ofColor::black, 5, 15);
	buttons.push_back(selectEnabled);

}

void testFunc(Button& b) {

}

void ofApp::exit() {
	for (unsigned int i = 0; i < buttons.size(); i++)
		delete buttons[i];
	buttons.clear();
}

//--------------------------------------------------------------
void ofApp::resetParticles(){

	//these are the attraction points used in the fourth demo 
	attractPoints.clear();
	for(int i = 0; i < 4; i++){
		attractPoints.push_back( glm::vec3( ofMap(i, 0, 4, 100, ofGetWidth()-100) , ofRandom(100, ofGetHeight()-100) , 0) );
	}
	
	attractPointsWithMovement = attractPoints;
	
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);		
		p[i].setAttractPoints(&attractPointsWithMovement);;
		p[i].reset();
	}	
}

//--------------------------------------------------------------
void ofApp::update(){
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);
		p[i].update();
	}
	
	//lets add a bit of movement to the attract points
	for(unsigned int i = 0; i < attractPointsWithMovement.size(); i++){
		attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
		attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
	}

	magnifier.update();
	for (unsigned int i = 0; i < buttons.size(); i++)
		buttons[i]->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));

	for(unsigned int i = 0; i < p.size(); i++){
		magnifier.magnifyParticle(&p[i]);
		p[i].draw();
	}
	
	ofSetColor(190);
	if( currentMode == PARTICLE_MODE_NEAREST_POINTS ){
		for(unsigned int i = 0; i < attractPoints.size(); i++){
			ofNoFill();
			ofDrawCircle(attractPointsWithMovement[i], 10);
			ofFill();
			ofDrawCircle(attractPointsWithMovement[i], 4);
		}
	}

	magnifier.draw();

	ofSetColor(230);	
	ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode.", 10, 20);


	ofDrawBitmapString("Mag position " + std::to_string(magnifier.getPosition().x) + ", " + std::to_string(magnifier.getPosition().y), 10, 100);
	ofDrawBitmapString("Mag sacale " + std::to_string(magnifier.getScale().x) + ", " + std::to_string(magnifier.getScale().y), 10, 120);

	for (unsigned int i = 0; i < buttons.size(); i++)
		buttons[i]->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if( key == '1'){
		currentMode = PARTICLE_MODE_ATTRACT;
		currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse"; 		
	}
	if( key == '2'){
		currentMode = PARTICLE_MODE_REPEL;
		currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse"; 				
	}
	if( key == '3'){
		currentMode = PARTICLE_MODE_NEAREST_POINTS;
		currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS:"; 						
	}
	if( key == '4'){
		currentMode = PARTICLE_MODE_NOISE;
		currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation"; 						
		resetParticles();
	}	
		
	if( key == ' ' ){
		resetParticles();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	magnifier.loadDraggedPosition(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	magnifier.loadInitialPosition(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	magnifier.reset(button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
	
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
