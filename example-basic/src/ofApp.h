#pragma once

#include "ofMain.h"
#include "ofxQuadtree.h"

class ComplexObject {
    
    public:
    
        ComplexObject(ofVec2f p) {
            position = p;
        }
    
        ofVec2f position;
    
        // ------ EVERY CLASS NEEDS THESE TWO FUNCTIONS TO WORK WITH THIS ADDON ------
        float getXPos() {
            return position.x;
        }
        float getYPos() {
            return position.y;
        }
        // ------ EVERY CLASS NEEDS THESE TWO FUNCTIONS TO WORK WITH THIS ADDON ------
    
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofxQuadtree<ComplexObject> quadtree;
		
};
