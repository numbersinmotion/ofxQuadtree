#pragma once

#include "ofMain.h"
#include "ofxQuadtreeNode.h"

template<class Node>
class ofxQuadtree {
    
    public:
    
        ofxQuadtree();
        ofxQuadtree(const ofRectangle& rect, int maxItems = 1);
    
        bool put(shared_ptr<Node> pt);
        vector<shared_ptr<Node>> get(const ofRectangle& rect);
        void clear();
    
    private:
    
        ofxQuadtreeNode<Node>* top;
    
};

template<class Node>
ofxQuadtree<Node>::ofxQuadtree() {
    delete top;
    top = nullptr;
}

template<class Node>
ofxQuadtree<Node>::ofxQuadtree(const ofRectangle& rect, int maxItems) {
    top = new ofxQuadtreeNode<Node>(rect, maxItems);
}

template<class Node>
bool ofxQuadtree<Node>::put(shared_ptr<Node> pt) {
    return top->put(pt);
}

template<class Node>
vector<shared_ptr<Node>> ofxQuadtree<Node>::get(const ofRectangle& rect) {
    vector<shared_ptr<Node>> tempVec;
    return top->get(rect, tempVec);
}

template<class Node>
void ofxQuadtree<Node>::clear() {
    delete top;
    top = nullptr;
}
