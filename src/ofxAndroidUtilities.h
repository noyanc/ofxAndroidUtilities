/*
 * ofxAndroidUtilities.h
 *
 *  Created on: Nov 12, 2015
 *      Author: R.Noyan Culum
 *      Company: Nitra Oyun Yazilim Ltd. Sti., Istanbul / Turkey
 *      Email: info@nitragames.com
 *      Web: http://www.nitragames.com
 *
 *      This software is a MIT Licenced Android addon for openFrameworks.
 *      You can visit http://openframeworks.cc for more information
 *      about how to use openFrameworks and its addons.
 *
 *
 *		PLEASE NOTE THAT THIS ADDON IS EXPERIMENTAL!
 *		IT WOULD BE GREAT IF YOU CAN WRITE ME YOUR RESULT!
 *      I tested this addon with Eclipse + oF080 + Android 5.0.1. If you use a different version
 *      of openFrameworks or any version with Android Studio or if you target a different Android
 *      Api; please let me know if this addon works or not.
 *
 *      I use a special installation of openFrameworks. If you use openFrameworks with the regular
 *      installation as described on the oF website, please let me know again if this works for you.
 *
 *      Please report me your result, as I think to add further helpful methods into this addon.
 *
 *
 *		OBJECTIVE:
 *      This software provides some utilities from Android to native side.
 *
 *      USAGE:
 *      Add the src part of the addon like regular ofx addons.
 *      Then add the srcJava/cc/openframeworks/jniaddons directory under your srcJava directory
 *      or under src/cc.openframeworks.jniaddons directory of the final project.
 *
 *      Then the rest is really very simple.
 *      ofxAndroidUtilities ofxandroidutilities; (in the ofApp.h)
 *      ofxandroidutilities.getDeviceName(); (or any method) (in the ofApp.cpp)
 */


#ifndef OFXANDROIDUTILITIES_H_
#define OFXANDROIDUTILITIES_H_


#include "ofMain.h"
#include "ofxAndroid.h"


class ofxAndroidUtilities {
public:
	ofxAndroidUtilities();
	~ofxAndroidUtilities();

	//Device properties
	std::string getDeviceName();
	int getAndroidApiLevel();
	long getTotalRAMSize();
	long getFreeRAMSize();
	std::string getRealExternalStorageDirectory();
	std::string getAppDataDirectory();

	//App properties
	std::string getPackageName();
	std::string getInstallerPackage();

	//Internet utilities
	void visitURL(std::string url);
	std::string loadURL(std::string url);
	void saveURL(std::string url, std::string fileName);
	void sendEmail(std::string toEmailAddress, std::string subject, std::string message);

	//Storage utilities
	std::string getUserPrefs();
	void setUserPrefs(std::string prefStr);

	//Localisation utilities
	std::string getCountrySim();
	std::string getCountryLocale();
	std::string getDisplayLanguage();
	std::string getLanguage();
	std::string getISO3Language();


	//Various
	jclass getJavaClass(std::string javaClassName);



private:
	jclass thisJava;
	std::string getValueStr(const char* javaMethodName);
};




#endif /* OFXANDROIDUTILITIES_H_ */
