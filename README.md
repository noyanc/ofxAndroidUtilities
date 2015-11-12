# ofxAndroidUtilities
Some utilities and helper for openFrameworks-Android

This software is a Android addon for openFrameworks with MIT Licence. You can visit http://openframeworks.cc for more information about how to use openFrameworks and its addons.


PLEASE NOTE THAT THIS ADDON IS EXPERIMENTAL!
IT WOULD BE GREAT IF YOU CAN WRITE ME YOUR RESULT!
I tested this addon with Eclipse + oF080 + Android 5.0.1. If you use a different version of openFrameworks or any version with Android Studio or if you target a different Android Api; please let me know if this addon works or not.

I use a special installation of openFrameworks. If you use openFrameworks with the regular installation as described on the oF website, please let me know again if this works for you. Please report me your result, as I think to add further helpful methods into this addon.


OBJECTIVE:

This software provides some utilities from Android to native side.

USAGE:

Add the src part of the addon like regular ofx addons. Then add the srcJava/cc/openframeworks/jniaddons directory under your srcJava directory or under src/cc.openframeworks.jniaddons directory of the final project.

Then the rest is really very easy:

ofxAndroidUtilities ofxandroidutilities; (into ofApp.h)

ofxandroidutilities.getDeviceName(); (or any method) (into ofApp.cpp)
