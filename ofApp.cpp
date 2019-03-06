#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	this->locations.clear();

	int radius = 300;
	float noise_seed_x, noise_seed_y;
	for (int i = 0; i < 3; i++) {

		noise_seed_x = ofRandom(1000);
		noise_seed_y = ofRandom(1000);
		for (int deg = 0; deg < 360; deg += 5) {

			auto point = glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0);
			auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_x, ofGetFrameNum() * 0.001), 0, 1, -PI, PI), glm::vec3(1, 0, 0));
			auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_y, ofGetFrameNum() * 0.001), 0, 1, -PI, PI), glm::vec3(0, 1, 0));

			this->locations.push_back(glm::vec4(point, 0) * rotation_x * rotation_y);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (auto& location : this->locations) {

		ofSetColor(255);
		ofDrawSphere(location, 5);
		for (auto& other : this->locations) {

			float distance = glm::distance(location, other);
			if (distance < 120) {

				ofSetColor(255, ofMap(distance, 100, 120, 239, 0));
				ofDrawLine(location, other);
			}
		}
	}
	
	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}