/*
 * ofxAndroidUtilities.cpp
 *
 *  Created on: Nov 12, 2015
 *      Author: R.Noyan Culum
 *      Company: Nitra Oyun Yazilim Ltd. Sti., Istanbul / Turkey
 *      Email: info@nitragames.com
 *      Web: http://www.nitragames.com
 *
 */


#include "ofxAndroidUtilities.h"

//Below null definition added here only because sometime my Eclipse CDT can not resolve NULL.
#ifndef NULL
#define NULL   ((void *) 0)
#endif



ofxAndroidUtilities::ofxAndroidUtilities() {
	//First of all, we get the java class of our addon
	thisJava = getJavaClass("cc/openframeworks/ofxaddons/OFXAndroidUtilities");
}


ofxAndroidUtilities::~ofxAndroidUtilities() {
}


std::string ofxAndroidUtilities::getDeviceName() {
	//we get here, the brand and model name of the device. The returned string is something like "Samsung Galaxy S6"
	//Altought device name patterns are device dependent, this should work for most of the devices.
	return getValueStr("getDeviceName");
}


int ofxAndroidUtilities::getAndroidApiLevel() {
	//we get the api level of the device
	return ofGetJNIEnv()->CallStaticIntMethod(thisJava, ofGetJNIEnv()->GetStaticMethodID(thisJava, "getAndroidApiLevel", "()I"));
}


long ofxAndroidUtilities::getRAMSizeTotal() {
	//Total RAM size assigned to this app by Android OS
	return ofGetJNIEnv()->CallStaticLongMethod(thisJava, ofGetJNIEnv()->GetStaticMethodID(thisJava, "getTotalRAMSize", "()J"));
}


long ofxAndroidUtilities::getRAMSizeFree() {
	//Free Android RAM size
	return ofGetJNIEnv()->CallStaticLongMethod(thisJava, ofGetJNIEnv()->GetStaticMethodID(thisJava, "getFreeRAMSize", "()J"));
}


std::string ofxAndroidUtilities::getRealExternalStorageDirectory() {
	//We get real external storage directory from OFAndroid.
	return getValueStr("getRealExternalStorageDirectory");
}


std::string ofxAndroidUtilities::getAppDataDirectory() {
	//We get real external storage directory from OFAndroid.
	return getValueStr("getAppDataDirectory");
}


std::string ofxAndroidUtilities::getPackageName() {
	//We get package name of our app
	return getValueStr("getPackageName");
}


std::string ofxAndroidUtilities::getInstallerPackage() {
	//The market from where our app is installed to this device: Play Store, Amazon, a third party market or "terminal"(direct install)
	return getValueStr("getInstallerPackage");
}


long ofxAndroidUtilities::getRAMSizeUsed() {
	//Android RAM size we used
	return ofGetJNIEnv()->CallStaticLongMethod(thisJava, ofGetJNIEnv()->GetStaticMethodID(thisJava, "getUsedRAMSize", "()J"));
}


void ofxAndroidUtilities::openURL(std::string url) {
	//This method opens an url in the browser of Android. When he press back button, he returns to our app
	jstring jStringParam = ofGetJNIEnv()->NewStringUTF(url.c_str());
	ofGetJNIEnv()->CallStaticVoidMethod(thisJava, ofGetJNIEnv()->GetStaticMethodID(thisJava, "openURL", "(Ljava/lang/String;)V"), jStringParam);
	ofGetJNIEnv()->DeleteLocalRef(jStringParam);
}


std::string ofxAndroidUtilities::loadURL(std::string url) {
	//Reading an url into a string. Useful for reading remote data.
	jstring jStringParam = ofGetJNIEnv()->NewStringUTF(url.c_str());
	jmethodID midCallBack = ofGetJNIEnv()->GetStaticMethodID(thisJava, "loadURL", "(Ljava/lang/String;)Ljava/lang/String;");
	jstring resultJNIStr = (jstring)ofGetJNIEnv()->CallStaticObjectMethod(thisJava, midCallBack, jStringParam);
	unsigned char* iscopy = NULL;
	const char *resultCStr = ofGetJNIEnv()->GetStringUTFChars(resultJNIStr, iscopy);
	std::string resultStr(resultCStr);
	ofGetJNIEnv()->ReleaseStringUTFChars(resultJNIStr, resultCStr);
	ofGetJNIEnv()->DeleteLocalRef(jStringParam);
	return resultStr;
}


void ofxAndroidUtilities::saveURL(std::string url, std::string fileName) {
	//This method saves an url to a file. Mainly for text data such as html, xml, txt, vs..
	//Useful for saving the data in Java side without transferring it via jni pipes.
	//Then you can open the saved file in the C++ side when it is needed.
	jstring jStringParam1 = ofGetJNIEnv()->NewStringUTF(url.c_str());
	jstring jStringParam2 = ofGetJNIEnv()->NewStringUTF(fileName.c_str());
	jmethodID midCallBack = ofGetJNIEnv()->GetStaticMethodID(thisJava, "saveURL", "(Ljava/lang/String;Ljava/lang/String;)V");
	ofGetJNIEnv()->CallStaticVoidMethod(thisJava, midCallBack, jStringParam1, jStringParam2);
	ofGetJNIEnv()->DeleteLocalRef(jStringParam1);
	ofGetJNIEnv()->DeleteLocalRef(jStringParam2);
}


void ofxAndroidUtilities::downloadURL(std::string url, std::string fileName) {
	//This method saves an url to a file. Mainly for binary data.
	//Useful for saving the data in Java side without transferring it via jni pipes.
	//Then you can open the saved file in the C++ side when it is needed.
	jstring jStringParam1 = ofGetJNIEnv()->NewStringUTF(url.c_str());
	jstring jStringParam2 = ofGetJNIEnv()->NewStringUTF(fileName.c_str());
	jmethodID midCallBack = ofGetJNIEnv()->GetStaticMethodID(thisJava, "downloadURL", "(Ljava/lang/String;Ljava/lang/String;)V");
	ofGetJNIEnv()->CallStaticVoidMethod(thisJava, midCallBack, jStringParam1, jStringParam2);
	ofGetJNIEnv()->DeleteLocalRef(jStringParam1);
	ofGetJNIEnv()->DeleteLocalRef(jStringParam2);
}


void ofxAndroidUtilities::sendEmail(std::string toEmailAddress, std::string subject, std::string message) {
	//This method opens the email client chooser of Android, then sends the email via the choosen client.
	jstring jStringParam1 = ofGetJNIEnv()->NewStringUTF(toEmailAddress.c_str());
	jstring jStringParam2 = ofGetJNIEnv()->NewStringUTF(subject.c_str());
	jstring jStringParam3 = ofGetJNIEnv()->NewStringUTF(message.c_str());
	ofGetJNIEnv()->CallStaticVoidMethod(thisJava, ofGetJNIEnv()->GetStaticMethodID(thisJava, "sendEmail", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V"), jStringParam1, jStringParam2, jStringParam3);
	ofGetJNIEnv()->DeleteLocalRef(jStringParam1);
	ofGetJNIEnv()->DeleteLocalRef(jStringParam2);
	ofGetJNIEnv()->DeleteLocalRef(jStringParam3);
}


std::string ofxAndroidUtilities::getSharedPreferences(std::string key, std::string defValue) {
	//This method reads a value from Shared Preferences.
	//Visit http://developer.android.com/guide/topics/data/data-storage.html for more information about Shared Preferances
	jstring jStringParam1 = ofGetJNIEnv()->NewStringUTF(key.c_str());
	jstring jStringParam2 = ofGetJNIEnv()->NewStringUTF(defValue.c_str());
	jmethodID midCallBack = ofGetJNIEnv()->GetStaticMethodID(thisJava, "getSharedPreferences", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;");
	jstring resultJNIStr = (jstring)ofGetJNIEnv()->CallStaticObjectMethod(thisJava, midCallBack, jStringParam1, jStringParam2);
	unsigned char* iscopy = NULL;
	const char *resultCStr = ofGetJNIEnv()->GetStringUTFChars(resultJNIStr, iscopy);
	std::string resultStr(resultCStr);
	ofGetJNIEnv()->ReleaseStringUTFChars(resultJNIStr, resultCStr);
	ofGetJNIEnv()->DeleteLocalRef(jStringParam1);
	ofGetJNIEnv()->DeleteLocalRef(jStringParam2);
	ofGetJNIEnv()->DeleteLocalRef(resultJNIStr);
	return resultStr;
}


void ofxAndroidUtilities::setSharedPreferences(std::string key, std::string value) {
	//This method saves a value into Shared Preferences.
	jstring jStringParam1 = ofGetJNIEnv()->NewStringUTF(key.c_str());
	jstring jStringParam2 = ofGetJNIEnv()->NewStringUTF(value.c_str());
	ofGetJNIEnv()->CallStaticVoidMethod(thisJava, ofGetJNIEnv()->GetStaticMethodID(thisJava, "setSharedPreferences", "(Ljava/lang/String;)V"), jStringParam1, jStringParam2);
	ofGetJNIEnv()->DeleteLocalRef(jStringParam1);
	ofGetJNIEnv()->DeleteLocalRef(jStringParam2);
}


std::string ofxAndroidUtilities::getCountrySim() {
	//This method returns the country of the simcard in ISO format
	return getValueStr("getCountrySim");
}


std::string ofxAndroidUtilities::getCountryLocale() {
	//This method returns the country code of the user
	return getValueStr("getCountryLocale");
}


std::string ofxAndroidUtilities::getDisplayLanguage() {
	//This method returns the display language
	return getValueStr("getDisplayLanguage");
}


std::string ofxAndroidUtilities::getLanguage() {
	//This method returns the code of the language
	return getValueStr("getLanguage");
}


std::string ofxAndroidUtilities::getISO3Language() {
	//This method returns the language in the ISO3 format
	return getValueStr("getISO3Language");
}


jclass ofxAndroidUtilities::getJavaClass(std::string javaClassName) {
	//This function return the jclass of any given Java class.
	//The parameter javaClassName should be in "com/myproject/example/classname" pattern!
	char *javaclassname = new char[javaClassName.size()+1];
	strcpy(javaclassname, javaClassName.c_str());
    jclass tmp = ofGetJNIEnv()->FindClass(javaclassname);
    return (jclass)ofGetJNIEnv()->NewGlobalRef(tmp);
}


std::string ofxAndroidUtilities::getValueStr(const char* javaMethodName) {
	//A common method for getting strings from Java functions. util for some of the above methods.
	jmethodID midCallBack = ofGetJNIEnv()->GetStaticMethodID(thisJava, javaMethodName, "()Ljava/lang/String;");
	jstring resultJNIStr = (jstring)ofGetJNIEnv()->CallStaticObjectMethod(thisJava, midCallBack);
	jboolean *iscopy = NULL;
	const char *resultCStr = ofGetJNIEnv()->GetStringUTFChars(resultJNIStr, iscopy);
	std::string resultStr(resultCStr);
	ofGetJNIEnv()->ReleaseStringUTFChars(resultJNIStr, resultCStr);
	return resultStr;
}
