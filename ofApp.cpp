#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();

	int span = 2;

	for (int z = 0; z >= -60; z -= 10) {

		for (int x = -330; x <= 330; x += span) {

			for (int y = -330; y <= 330; y += span) {

				auto noise_value = ofNoise(x * 0.00085, y * 0.00085, z * 0.002 + ofGetFrameNum() * 0.02);
				if (noise_value < 0.48 || noise_value > 0.52) { continue; }

				this->mesh.addVertex(glm::vec3(x, y, 0));
				this->mesh.addVertex(glm::vec3(x + span, y, 0));
				this->mesh.addVertex(glm::vec3(x + span, y + span, 0));
				this->mesh.addVertex(glm::vec3(x, y + span, 0));

				this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 4); this->mesh.addIndex(this->mesh.getNumVertices() - 3);
				this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 2); this->mesh.addIndex(this->mesh.getNumVertices() - 3);

				ofColor color;
				color.setHsb(ofMap(z, 0, -60, 0, 255), 200, 255);
				for (int i = 0; i < 4; i++) { this->mesh.addColor(color); }
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);
	ofRotateX(180);

	this->mesh.draw();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}