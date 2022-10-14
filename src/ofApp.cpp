#include "ofApp.h"

#include <iostream>

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetVerticalSync(true);

	int num = 1500;
	p.assign(num, Particle());
	currentMode = PARTICLE_MODE_ATTRACT;

	currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
	currentColorState = "Color state Red";

	resetParticles();

	// ofFpsCounter
}

//--------------------------------------------------------------
void ofApp::resetParticles()
{
	if (hasResetedParticles)
		return;
	// these are the attraction points used in the fourth demo
	attractPoints.clear();
	for (int i = 0; i < 4; i++)
	{
		attractPoints.push_back(glm::vec3(ofMap(i, 0, 4, 100, ofGetWidth() - 100), ofRandom(100, ofGetHeight() - 100), 0));
	}

	attractPointsWithMovement = attractPoints;

	for (unsigned int i = 0; i < p.size(); i++)
	{
		p[i].setMode(currentMode);
		p[i].setAttractPoints(&attractPointsWithMovement);
		;
		p[i].reset();
	}
	hasResetedParticles = true;
}

//--------------------------------------------------------------
void ofApp::update()
{

	for (unsigned int i = 0; i < p.size(); i++)
	{
		switch (this->colorState)
		{
		case 0:
			p[i].particleColor.r = 1.0;
			p[i].particleColor.g = 0.0;
			p[i].particleColor.b = 0.0;
			break;
		case 1:
			p[i].particleColor.r = 0.0;
			p[i].particleColor.g = 1.0;
			p[i].particleColor.b = 0.0;
			break;
		case 2:
			p[i].particleColor.r = 0.0;
			p[i].particleColor.g = 0.0;
			p[i].particleColor.b = 1.0;
			break;
		}
		p[i].setMode(currentMode);
		if (stop == false)
		{
			p[i].update();
		}
	}

	// lets add a bit of movement to the attract points
	for (unsigned int i = 0; i < attractPointsWithMovement.size(); i++)
	{
		attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
		attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
	}
	magnifier.update();

	/*
		replay
	*/
	if (recorder.getCurrentPlayBackKey() == '1')
	{
		currentMode = PARTICLE_MODE_ATTRACT;
		currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
	}
	if (recorder.getCurrentPlayBackKey() == '2')
	{
		currentMode = PARTICLE_MODE_REPEL;
		currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse";
	}
	if (recorder.getCurrentPlayBackKey() == '3')
	{
		currentMode = PARTICLE_MODE_NEAREST_POINTS;
		currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS:";
	}

	if (recorder.getCurrentPlayBackKey() == '4')
	{
		currentMode = PARTICLE_MODE_NOISE;
		currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation";
		resetParticles();
	}
	else if (recorder.getCurrentPlayBackKey() == ' ')
	{
		resetParticles();
	}
	else
	{
		hasResetedParticles = false;
	}
	if (recorder.getCurrentPlayBackKey() == 's')
	{
		stop = !stop;
	}
	if (recorder.getCurrentPlayBackKey() == 'd')
	{
		for (unsigned int i = 0; i < p.size(); i++)
		{
			p[i].vel.x = p[i].vel.x * 2;
			p[i].vel.y = p[i].vel.y * 2;
		}
	}
	if (recorder.getCurrentPlayBackKey() == 'a')
	{
		for (unsigned int i = 0; i < p.size(); i++)
		{
			p[i].vel.x = p[i].vel.x / 2;
			p[i].vel.y = p[i].vel.y / 2;
		}
	}
	if (recorder.getCurrentPlayBackKey() == 't')
	{
		// if (!this->colorToggleFlag)
		// {
		this->colorState = (this->colorState + 1) % this->maxColorStates;
		this->colorToggleFlag = true;

		switch (this->colorState)
		{
		case 0:
			currentColorState = "Color state Red";
			break;
		case 1:
			currentColorState = "Color state Green";
			break;
		case 2:
			currentColorState = "Color state Blue";
			break;
		}
		// }
	}
	// else
	// {
	// 	this->colorToggleFlag = false;
	// }

	recorder.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackgroundGradient(ofColor(60, 60, 60), ofColor(10, 10, 10));

	for (unsigned int i = 0; i < p.size(); i++)
	{
		magnifier.magnifyParticle(&p[i]);
		p[i].draw();
	}

	ofSetColor(190);
	if (currentMode == PARTICLE_MODE_NEAREST_POINTS)
	{
		for (unsigned int i = 0; i < attractPoints.size(); i++)
		{
			ofNoFill();
			ofDrawCircle(attractPointsWithMovement[i], 10);
			ofFill();
			ofDrawCircle(attractPointsWithMovement[i], 4);
		}
	}

	magnifier.draw();

	ofSetColor(230);
	ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode.", 10, 20);

	recorder.draw();

	string str = recorder.isRecording() ? "true" : "false";
	ofDrawBitmapString("\n\nIs Recording: " + str, 10, 60);

	string str1 = recorder.isOnReplay() ? "true" : "false";
	ofDrawBitmapString("\n\nIs Replaying: " + str1, 10, 100);

	ofDrawBitmapString("\n\nIs Recorded keys: " + std::to_string(recorder.getRecordedKeysCount()), 10, 130);

	ofDrawBitmapString("Mag position " + std::to_string(magnifier.getPosition().x) + ", " + std::to_string(magnifier.getPosition().y), 10, 100);
	ofDrawBitmapString("Mag sacale " + std::to_string(magnifier.getScale().x) + ", " + std::to_string(magnifier.getScale().y), 10, 120);
	ofDrawBitmapString(currentColorState, 10, 200);

	string framePrint = "Time to render: " + std::to_string(frameDif) + "ms";
	ofDrawBitmapString(framePrint, 10, 150);

	frameDif = ofGetSystemTimeMillis() - lastFrame;
	lastFrame = ofGetSystemTimeMillis();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

	if (key == '1' && !recorder.isOnReplay())
	{
		currentMode = PARTICLE_MODE_ATTRACT;
		currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
		recorder.record(key);
	}
	if (key == '2' && !recorder.isOnReplay())
	{
		currentMode = PARTICLE_MODE_REPEL;
		currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse";
		recorder.record(key);
	}
	if (key == '3' && !recorder.isOnReplay())
	{
		currentMode = PARTICLE_MODE_NEAREST_POINTS;
		currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS:";
		recorder.record(key);
	}
	if (key == '4' && !recorder.isOnReplay())
	{
		currentMode = PARTICLE_MODE_NOISE;
		currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation";
		resetParticles();
		recorder.record(key);
	}

	if (key == ' ' && !recorder.isOnReplay())
	{
		resetParticles();
		recorder.record(key);
	}

	// Pauses the particles
	if (key == 's' && !recorder.isRecording())
	{
		stop = !stop;
		recorder.record(key);
	}

	// Increase the velocity of particles
	if (key == 'd' && !recorder.isOnReplay())
	{
		for (unsigned int i = 0; i < p.size(); i++)
		{
			p[i].vel.x = p[i].vel.x * 2;
			p[i].vel.y = p[i].vel.y * 2;
		}
		recorder.record(key);
	}

	// Decreases the velocity of particles
	if (key == 'a' && !recorder.isOnReplay())
	{
		for (unsigned int i = 0; i < p.size(); i++)
		{
			p[i].vel.x = p[i].vel.x / 2;
			p[i].vel.y = p[i].vel.y / 2;
		}
		recorder.record(key);
	}

	// Toggles color of particles from: red -> green -> blue and returns to red after blue
	if (key == 't' && !recorder.isOnReplay())
	{
		// if (!this->colorToggleFlag)
		//{
		this->colorState = (this->colorState + 1) % this->maxColorStates;
		this->colorToggleFlag = true;

		switch (this->colorState)
		{
		case 0:
			currentColorState = "Color state Red";
			break;
		case 1:
			currentColorState = "Color state Green";
			break;
		case 2:
			currentColorState = "Color state Blue";
			break;
		}
		//}
		recorder.record(key);
	}
	// else
	// {
	// 	this->colorToggleFlag = false;
	// }

	// Records the key presses
	if (key == 'r' && !recorder.isRecording())
	{
		recorder.startRecording();
	}
	else if (key == 'r')
	{
		recorder.stopRecording();
	}

	// Replay the key presses
	if (key == 'p' && !recorder.isOnReplay())
	{
		recorder.replay();
	}
	if (key == 'c' && recorder.isOnReplay())
	{
		recorder.endReplay();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	this->colorToggleFlag = false;
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
