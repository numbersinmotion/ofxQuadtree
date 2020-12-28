#pragma once

#include "ofMain.h"

template<class Node>
class ofxQuadtreeNode {
    
    public:
    
        ofxQuadtreeNode(const ofRectangle& rect, int maximumItems);
        ~ofxQuadtreeNode();
    
        bool put(shared_ptr<Node> pt);
        vector<shared_ptr<Node>>& get(const ofRectangle& rect, vector<shared_ptr<Node>>& vector);
    
    private:
    
        void split();
        ofxQuadtreeNode* getChild(float x, float y);
        bool hasChildren();
    
        enum Regions {NORTHWEST = 0, NORTHEAST = 1, SOUTHEAST = 2, SOUTHWEST = 3};
        vector<shared_ptr<Node>> items;
        array<ofxQuadtreeNode*, 4>* children;
        unsigned int maxItems;
        ofRectangle bounds;
        float minSize;
    
};

template<class Node>
ofxQuadtreeNode<Node>::ofxQuadtreeNode(const ofRectangle& rect, int maximumItems) {
    children = nullptr;
    maxItems = maximumItems;
    bounds = rect;
    minSize = 0.0001;
}

template<class Node>
ofxQuadtreeNode<Node>::~ofxQuadtreeNode() {
    if (children != nullptr) {
        for (const auto& child :* children) {
            delete child;
        }
        delete children;
        children = nullptr;
    }
}

template<class Node>
bool ofxQuadtreeNode<Node>::hasChildren() {
    return children != nullptr;
}

template<class Node>
void ofxQuadtreeNode<Node>::split() {
    if (bounds.getWidth() < minSize && bounds.getHeight() < minSize) {
        return;
    }
    float halfWidth = static_cast<float>(bounds.getWidth() / 2.0);
    float halfHeight = static_cast<float>(bounds.getHeight() / 2.0);
    children = new array<ofxQuadtreeNode*, 4>;
    (*children)[NORTHWEST] = new ofxQuadtreeNode(ofRectangle(bounds.x            , bounds.y             , halfWidth, halfHeight), maxItems);
    (*children)[NORTHEAST] = new ofxQuadtreeNode(ofRectangle(bounds.x + halfWidth, bounds.y             , halfWidth, halfHeight), maxItems);
    (*children)[SOUTHEAST] = new ofxQuadtreeNode(ofRectangle(bounds.x + halfWidth, bounds.y + halfHeight, halfWidth, halfHeight), maxItems);
    (*children)[SOUTHWEST] = new ofxQuadtreeNode(ofRectangle(bounds.x            , bounds.y + halfHeight, halfWidth, halfHeight), maxItems);
    for (auto item : items) {
        put(item);
    }
    items.clear();
}

template<class Node>
ofxQuadtreeNode<Node>* ofxQuadtreeNode<Node>::getChild(float x, float y) {
    if (bounds.inside(x, y)) {
        if (children != nullptr) {
            for (ofxQuadtreeNode<Node>* child :* children) {
                if (child->bounds.inside(x, y)) return child->getChild(x, y);
            }
        } else {
            return this;  // no children, x, y here...
        }
    }
    return nullptr;
}

template<class Node>
bool ofxQuadtreeNode<Node>::put(shared_ptr<Node> pt) {
    if (children == nullptr) {
        items.push_back(pt);
        if (items.size() > maxItems) split();
        return true;
    } else {
        ofxQuadtreeNode* node = getChild(pt->getXPos(), pt->getYPos());
        if (node != nullptr) {
            return node->put(pt);
        }
    }
    return false;
}

template<class Node>
vector<shared_ptr<Node>>& ofxQuadtreeNode<Node>::get(const ofRectangle& rect, vector<shared_ptr<Node>>& vector) {
    if (children == nullptr) {
        for (shared_ptr<Node> pt : items) {
            if (rect.inside(pt->getXPos(), pt->getYPos())) {
                vector.push_back(pt);
            }
        }
    } else {
        for (ofxQuadtreeNode* child :* children) {
            if (child->bounds.intersects(rect)) {
                child->get(rect, vector);
            }
        }
    }
    return vector;
}
