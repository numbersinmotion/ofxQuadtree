#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);
    
    quadtree = ofxQuadtree<ComplexObject>(ofRectangle(0, 0, ofGetWidth(), ofGetHeight()), 4);
    
    for (int i = 0; i < 10000; i++) {
        ComplexObject tmp(ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())));
        quadtree.put(make_shared<ComplexObject>(tmp));
    }

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    vector<shared_ptr<ComplexObject>> found = quadtree.get(ofRectangle(mouseX - 100, mouseY - 100, 200, 200));
    for (int i = 0; i < found.size(); i++) {
        shared_ptr<ComplexObject> tmp = found[i];
        ofDrawCircle(tmp->getXPos(), tmp->getYPos(), 1);
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
