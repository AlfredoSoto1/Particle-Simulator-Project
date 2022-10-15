#pragma once

#include "ofMain.h"
#include "Recorder.h"
#include "Particle.h"
#include "magnifier.h"
class ofApp : public ofBaseApp
{

public:
	void setup();
	void update();
	void draw();
	void exit();
	void resetParticles();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	bool stop = false; //Determine when the particles are paused
	float increaseVelocityFactor = 1; //Variable used to duplicate or decrease particle velocity 
	float replayVelocityFactor = 1;

	uint64_t lastFrame;
	uint64_t frameDif;
	uint64_t lastTime;
	unsigned int frameCount;

	particleMode currentMode;
	string currentColorState;
	string currentModeStr;

	ofColor* colorCycles;
	int colorState = 0; // 0 = red, 1 = green, 2 = blue
	int lastColorState = 0;
	const int maxColorStates = 3;

	vector<Particle> p;
	vector<glm::vec3> attractPoints;
	vector<glm::vec3> attractPointsWithMovement;

	glm::vec3 generalParticleColor = glm::vec3(1.0);

	Magnifier magnifier;
	Recorder recorder;
	ofColor replayColor;
};
