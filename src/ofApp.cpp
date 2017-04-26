#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
//    fileImage.load("line.jpg");
//    fileImage.load("ball.jpg");
    fileImage.load("mm1.jpg");
    
    gradImgX.allocate(500,588);
    gradImgY.allocate(500,588);
    
    fbo.allocate(500, 588);
    
    gui.setup();
    gui.setPosition(770, 10);
    gui.add(vectorSize.setup("Vector Size", 5, 0.1, 20));
    gui.add(matrixSize.setup("Matrix Size", 3, 1, 31));
    gui.add(animate.setup("Animate", true));    
}

//--------------------------------------------------------------
void ofApp::update(){
    counter += 0.01;
    if(counter > TWO_PI){
        counter = 0;
    }
    scaleSize = ofMap(sin(counter),-1,1,0.5,1);
    fbo.begin();
    ofEnableSmoothing();
    ofBackground(255);
    ofSetColor(255);
    ofPushMatrix();
        if(animate){
            ofTranslate(ofGetMouseX(), ofGetMouseY());
        } else {
            ofTranslate(500/2, 588/2);
        }
        fileImage.setAnchorPercent(0.5, 0.5);
        if(animate){
            ofScale(scaleSize, scaleSize);
        }
        fileImage.draw(0,0);
    ofPopMatrix();
    fbo.end();
    
    fbo.readToPixels(pix);
    pix.setImageType(OF_IMAGE_GRAYSCALE);
    colorImage.setFromPixels(pix);
    colorImage.blurGaussian(5);
    if(matrixSize % 2 == 0){
        matrixSize = matrixSize + 1;
    }
    cvSobel(colorImage.getCvImage(), gradImgX.getCvImage(), 1, 0, matrixSize);
    cvSobel(colorImage.getCvImage(), gradImgY.getCvImage(), 0, 1, matrixSize);
    
    gradPixX = gradImgX.getPixelsAsFloats();
    gradPixY = gradImgY.getPixelsAsFloats();
    
    gradImgX.flagImageChanged();
    gradImgY.flagImageChanged();
    
    if(ofGetMouseX() < 500 && ofGetMouseY() < 588){
        ofHideCursor();
    } else {
        ofShowCursor();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    ofSetColor(255, 50);
    colorImage.draw(5,5);
    
    ofPushMatrix();
        ofScale(0.5, 0.5);
        gradImgX.draw(515*2, 0);
        gradImgY.draw(515*2, 588.0 + 20);
    ofPopMatrix();
    
    ofSetColor(5,255);
    
    for (int y=0; y<588; y+=5) {
        for (int x=0; x<500; x+=5) {
            float pixX = gradPixX[ x + 500 * y ];
            float pixY = gradPixY[ x + 500 * y ];
            ofVec2f pixVec = ofVec2f(pixX, pixY);
            pixVec = pixVec/vectorSize;
            ofDrawLine(x+10, y+10, x+10+pixVec.x, y+10+pixVec.y);
        }
    }
    gui.draw();
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
