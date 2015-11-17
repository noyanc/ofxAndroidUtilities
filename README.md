# ofxAndroidUtilities
Some utilities and helpers for openFrameworks-Android

This software is an openFrameworks-Android addon with MIT Licence. You can visit http://openframeworks.cc for more information about how to use openFrameworks and its addons.


USAGE:

Copy the OFXAndroidUtilities.java file to the directory srcJava/cc/openframeworks/ofxaddons of your project. And add the src part of the addon like regular ofx addons.

Then the rest is easier:

ofApp.h:
ofxAndroidUtilities ofxandroidutilities;

ofApp.cpp:
ofxandroidutilities.getDeviceName(); (or any method)
