#pragma once

/*
 *  ofxOpenNI2Grabber.h
 *
 *  Created by jason van cleave on 2/28/13.
 *
 */
#include "ofMain.h"
#include <OpenNI.h>
#include "ofxOpenNI2GrabberUtils.h"

class ofxOpenNI2Grabber: public ofThread
{
public:
	struct Settings;
	
	ofxOpenNI2Grabber();
	bool setup(Settings _settings);
	void readFrame();
	void draw();
	bool close();
	
	openni::Device device;
	const char* deviceURI;

	openni::VideoStream depth;
	openni::VideoMode depthVideoMode;
	openni::VideoFrameRef depthFrame;
	int depthWidth;
	int depthHeight;
	
	openni::VideoStream color;
	openni::VideoMode colorVideoMode;
	openni::VideoFrameRef colorFrame;
	int colorWidth;
	int colorHeight;
	
	openni::VideoStream**		streams;
	ofTexture depthTexture;
	ofPixels depthPixels[2];
	ofPixels* backDepthPixels;
	ofPixels* currentDepthPixels;
	
	// depth raw
	ofShortPixels depthRawPixels[2];
	ofShortPixels* backDepthRawPixels;
	ofShortPixels* currentDepthRawPixels;
	
	// rgb
	ofTexture rgbTexture;
	ofPixels rgbPixels[2];
	ofPixels* backRGBPixels;
	ofPixels* currentRGBPixels;
	
	void generateDepthPixels();
	bool isReady;
	
	float	deviceMaxDepth;
	
	bool isKinect;

	const openni::VideoMode* findMode(openni::Device& device, openni::SensorType sensorType);
	void allocateDepthBuffers();
	void allocateDepthRawBuffers();
	void allocateColorBuffers();
	struct Settings {
		int		width;					// camera width
		int		height;					// camera height
		int		fps;					// camera fps
		bool	doDepth;				// use Depth camera
		bool	doColor;				// use RGB camera
		openni::PixelFormat depthPixelFormat; //PIXEL_FORMAT_DEPTH_1_MM, PIXEL_FORMAT_DEPTH_100_UM, PIXEL_FORMAT_SHIFT_9_2, PIXEL_FORMAT_SHIFT_9_3
		openni::PixelFormat colorPixelFormat; //PIXEL_FORMAT_RGB888, PIXEL_FORMAT_YUV422, PIXEL_FORMAT_GRAY8, PIXEL_FORMAT_GRAY16, PIXEL_FORMAT_JPEG
		bool isKinect;
		
		Settings();
	};
	Settings 			settings;
protected:
	void threadedFunction();
	
	
};