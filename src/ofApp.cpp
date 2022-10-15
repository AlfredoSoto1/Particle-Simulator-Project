#include "ofApp.h"

#include <iostream>

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(true);

	int num = 1500;
	p.assign(num, Particle());
	currentMode = PARTICLE_MODE_ATTRACT;

	currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
	currentColorState = "Color state Red";

	resetParticles();

	colorCycles = new ofColor[3];
	colorCycles[0] = ofColor::red;
	colorCycles[1] = ofColor::green;
	colorCycles[2] = ofColor::blue;
}

void ofApp::exit() {
	delete[] colorCycles;
}

//--------------------------------------------------------------
void ofApp::resetParticles() {
	// these are the attraction points used in the fourth demo
	attractPoints.clear();
	for (int i = 0; i < 4; i++) {
		attractPoints.push_back(glm::vec3(ofMap(i, 0, 4, 100, ofGetWidth() - 100), ofRandom(100, ofGetHeight() - 100), 0));
	}

	attractPointsWithMovement = attractPoints;

	for (unsigned int i = 0; i < p.size(); i++) {
		p[i].setMode(currentMode);
		p[i].setAttractPoints(&attractPointsWithMovement);
		p[i].reset();
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	/*
		replay
	*/
	if (recorder.getCurrentPlayBackKey() == '1') {
		currentMode = PARTICLE_MODE_ATTRACT;
		currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
		replayColor = recorder.getCurrentPlayBackColor();
		recorder.freeCurrentPlayBackKey();
	}
	if (recorder.getCurrentPlayBackKey() == '2') {
		currentMode = PARTICLE_MODE_REPEL;
		currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse";
		replayColor = recorder.getCurrentPlayBackColor();
		recorder.freeCurrentPlayBackKey();
	}
	if (recorder.getCurrentPlayBackKey() == '3') {
		currentMode = PARTICLE_MODE_NEAREST_POINTS;
		currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS:";
		replayColor = recorder.getCurrentPlayBackColor();
		recorder.freeCurrentPlayBackKey();
	}

	if (recorder.getCurrentPlayBackKey() == '4') {
		currentMode = PARTICLE_MODE_NOISE;
		currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation";
		resetParticles();
		replayColor = recorder.getCurrentPlayBackColor();
		recorder.freeCurrentPlayBackKey();
	}
	if (recorder.getCurrentPlayBackKey() == ' ') {
		resetParticles();
		replayColor = recorder.getCurrentPlayBackColor();
		recorder.freeCurrentPlayBackKey();
	}
	if (recorder.getCurrentPlayBackKey() == 's') {
		stop = !stop;
		replayColor = recorder.getCurrentPlayBackColor();
		recorder.freeCurrentPlayBackKey();
	}
	if (recorder.getCurrentPlayBackKey() == 'd') {
		replayVelocityFactor = replayVelocityFactor * 2.0;
		recorder.freeCurrentPlayBackKey();
	}
	if (recorder.getCurrentPlayBackKey() == 'a') {
		replayVelocityFactor = replayVelocityFactor / 2.0;
		recorder.freeCurrentPlayBackKey();
	}

	if (recorder.getCurrentPlayBackKey() == 't') {
		replayColor = recorder.getCurrentPlayBackColor();
		recorder.freeCurrentPlayBackKey();
	}

	recorder.update();
	magnifier.update();

	for (unsigned int i = 0; i < p.size(); i++) {
		if(recorder.isOnReplay())
			p[i].color = replayColor;
		else
			p[i].color = colorCycles[colorState];

		p[i].setMode(currentMode);
		if (!stop) {
			if(recorder.isOnReplay())
				p[i].velocityFactor = replayVelocityFactor;
			else
				p[i].velocityFactor = increaseVelocityFactor;
			p[i].update();
		}
	}

	// lets add a bit of movement to the attract points
	for (unsigned int i = 0; i < attractPointsWithMovement.size(); i++) {
		attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
		attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackgroundGradient(ofColor(60, 60, 60), ofColor(10, 10, 10));

	for (unsigned int i = 0; i < p.size(); i++) {
		magnifier.magnifyParticle(&p[i]);
		p[i].draw();
	}

	ofSetColor(190);
	if (currentMode == PARTICLE_MODE_NEAREST_POINTS) {
		for (unsigned int i = 0; i < attractPoints.size(); i++) {
			ofNoFill();
			ofDrawCircle(attractPointsWithMovement[i], 10);
			ofFill();
			ofDrawCircle(attractPointsWithMovement[i], 4);
		}
	}

	magnifier.draw();
	recorder.draw();

	ofSetColor(230);
	ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode.", 10, 20);

	// ofDrawBitmapString("Mag position " + std::to_string(magnifier.getPosition().x) + ", " + std::to_string(magnifier.getPosition().y), 10, 100);
	// ofDrawBitmapString("Mag sacale " + std::to_string(magnifier.getScale().x) + ", " + std::to_string(magnifier.getScale().y), 10, 120);
	ofDrawBitmapString(currentColorState, 10, 200);

	string framePrint =  "Time to render: " + std::to_string(frameDif) + "ms";
	ofDrawBitmapString(framePrint, 10, 150);

	frameDif = ofGetSystemTimeMillis() - lastFrame;
	lastFrame = ofGetSystemTimeMillis();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	if (key == '1' && !recorder.isOnReplay()) {
		currentMode = PARTICLE_MODE_ATTRACT;
		currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
		recorder.record(key, colorCycles[colorState]);
	}
	if (key == '2' && !recorder.isOnReplay()) {
		currentMode = PARTICLE_MODE_REPEL;
		currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse";
		recorder.record(key, colorCycles[colorState]);
	}
	if (key == '3' && !recorder.isOnReplay()) {
		currentMode = PARTICLE_MODE_NEAREST_POINTS;
		currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS:";
		recorder.record(key, colorCycles[colorState]);
	}
	if (key == '4' && !recorder.isOnReplay()) {
		currentMode = PARTICLE_MODE_NOISE;
		currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation";
		resetParticles();
		recorder.record(key, colorCycles[colorState]);
	}

	if (key == ' ' && !recorder.isOnReplay()) {
		resetParticles();
		recorder.record(key, colorCycles[colorState]);
	}

	// Pauses the particles

	// Pauses the particles

	// Pauses the particles
	if (key == 's' && !recorder.isOnReplay()) {
		stop = !stop;
		recorder.record(key, colorCycles[colorState]);
	}

	// Increase the velocity of particles

	// Increases the velocity of particles
	if (key == 'd' && !recorder.isOnReplay())
	{
		increaseVelocityFactor = increaseVelocityFactor * 2;
		recorder.record(key, colorCycles[colorState]);
	}

	// Decreases the velocity of particles
	if (key == 'a' && !recorder.isOnReplay())
	{
		increaseVelocityFactor = increaseVelocityFactor / 2;
		recorder.record(key, colorCycles[colorState]);
	}

	// Toggles color of particles from: red -> green -> blue and returns to red after blue
	if (key == 't' && !recorder.isOnReplay()) {
		colorState = (colorState + 1) % maxColorStates;
		switch (colorState) {
		case 0:
			currentColorState = "Color state Red";
			colorCycles[0] = ofColor::red;
			break;
		case 1:
			currentColorState = "Color state Green";
			colorCycles[1] = ofColor::green;
			break;
		case 2:
			currentColorState = "Color state Blue";
			colorCycles[2] = ofColor::blue;
			break;
		}
		recorder.record(key, colorCycles[colorState]);
	}

	// Records the key presses
	if (key == 'r' && !recorder.isRecording() && !recorder.isOnReplay()) {
		recorder.startRecording();
	}
	else if (key == 'r') {
		recorder.stopRecording();
	}

	// Replay the key presses
	if (key == 'p' && !recorder.isOnReplay()) {
		recorder.replay();
	}
	if (key == 'c' && recorder.isOnReplay()) {
		recorder.endReplay();
		replayVelocityFactor = increaseVelocityFactor;
	}

	if(key == 'l') {
		magnifier.toggleOnSelect();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
	magnifier.loadDraggedPosition(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	magnifier.loadInitialPosition(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
	magnifier.reset(button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
