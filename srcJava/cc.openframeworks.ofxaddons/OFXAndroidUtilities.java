package cc.openframeworks.ofxaddons;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.RandomAccessFile;
import java.net.URL;
import java.util.Locale;

import android.app.ActivityManager;
import android.app.ActivityManager.MemoryInfo;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.net.Uri;
import android.os.Build;
import android.telephony.TelephonyManager;
import android.util.Log;


//Comments are available in the ofxAndroidUtilities.cpp file

public class OFXAndroidUtilities extends cc.openframeworks.OFAndroidObject{
	
	public OFXAndroidUtilities() {
	}
	
	
	private static String getDeviceName() {
		String manufacturer = Build.MANUFACTURER;
		String model = Build.MODEL;
		if (model.startsWith(manufacturer)) {
			return model;
		} else {
			return manufacturer + " " + model;
		}
	}
	
	
	private static int getAndroidApiLevel() {
		return android.os.Build.VERSION.SDK_INT;
	}

	
	private static long getTotalRAMSize() {
	    RandomAccessFile reader = null;
	    String load = null;
	    try {
	        reader = new RandomAccessFile("/proc/meminfo", "r");
	        load = reader.readLine();
	    } catch (IOException ex) {
	    } finally {
	    	try {
				reader.close();
			} catch (IOException e) {}
	    }
	    
	    String ramstr[] = load.split(" ");
	    long ramsize = 0;
	    for (int i=0; i<ramstr.length; i++) {
	    	long ramstrlong = 0;
	    	try {
		    	ramstrlong = Long.parseLong(ramstr[i]);
	    	} catch(Exception e) {}
	    	if (ramstrlong > ramsize) ramsize = ramstrlong;
	    }
	    
	    return ramsize;
	}
	
	
	private static long getFreeRAMSize() {
	    MemoryInfo mi = new MemoryInfo();
	    ActivityManager activityManager = (ActivityManager) activity.getSystemService(Context.ACTIVITY_SERVICE);
	    activityManager.getMemoryInfo(mi);
	    long availableRam = mi.availMem / 1024L;
	    return availableRam;
	}
	
	
	private static long getUsedRAMSize() {
		return getTotalRAMSize() - getFreeRAMSize(); 
	}
	

	private static String getRealExternalStorageDirectory() {
		return cc.openframeworks.OFAndroid.getRealExternalStorageDirectory();
	}
	
	
	private static String getAppDataDirectory() {
		return cc.openframeworks.OFAndroid.getAppDataDirectory();
	}
	

	private static String getPackageName() {
		return activity.getPackageName();
	}
	
	
	private static String getInstallerPackage() {
		String installerpackage = "";
		try {
			installerpackage = activity.getPackageManager().getInstallerPackageName(getPackageName());
		} catch(Exception e) {
			Log.e("OFXAndroidUtilities", "" + e);
			installerpackage = "";
		}
		if (installerpackage == null || installerpackage.equals("")) installerpackage = "terminal";
		return installerpackage;
	}
	
	
	private static void openURL(String url) {
		activity.startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse(url)));
	}
	

	private static String loadURL(String url) {
		String response = "";
		BufferedReader in = null;
		try {
		    URL pageurl = new URL(url);
		    in = new BufferedReader(new InputStreamReader(pageurl.openStream()));
		    int str;
		    StringBuilder sb = new StringBuilder(100);
		    while ((str = in.read()) != -1) {
		        sb.append((char)str);
		    }
		    response = sb.toString();
		} catch (Exception e) {
		    //response = "";
		} finally {
			if (in != null) {
			    try {
					in.close();
				} catch (IOException e) {}
			}
		}
		return response;
	}

	
	private static void saveURL(String url, String fileName) {
		BufferedReader in = null;
		FileOutputStream fos = null;
		try {
            File file = new File(fileName);
		    URL pageurl = new URL(url);
		    in = new BufferedReader(new InputStreamReader(pageurl.openStream()));
		    int str;
		    StringBuilder sb = new StringBuilder(100);
		    while ((str = in.read()) != -1) {
		        sb.append((char)str);
		    }
		    
            fos = new FileOutputStream(file);
            fos.write(sb.toString().getBytes());
		} catch (Exception e) {
		} finally {
			if (in != null) {
			    try {
					in.close();
				} catch (IOException e) {}
			}
			if (fos != null) {
			    try {
			    	fos.close();
				} catch (IOException e) {}
			}
		}
		
	}

	
	private void downloadURL(String downloadurl, String savepath) throws Exception {
		Log.i("OFXAndroidUtilities", "Downloading from " + downloadurl);
		URL url = new URL (downloadurl);
		InputStream input = url.openStream();
		try {
		    //The sdcard directory e.g. '/sdcard' can be used directly, or 
		    //more safely abstracted with getExternalStorageDirectory()
			Log.i("OFXAndroidUtilities", "Saving to " + savepath);
		    OutputStream output = new FileOutputStream (savepath);
		    try {
		        byte[] buffer = new byte[2048];
		        int bytesRead = 0;
		        while ((bytesRead = input.read(buffer, 0, buffer.length)) >= 0) {
		            output.write(buffer, 0, bytesRead);
		        }
		    } finally {
		        output.close();
		    }
		} finally {
		    input.close();
		}
	}
	
	
	private static void sendEmail(String toEmailAddress, String subject, String message) {
		if (toEmailAddress.equals("")) toEmailAddress = "info@nitragames.com";
		if (subject.equals("")) subject = "Taso in-game feedback";
		Intent email = new Intent(Intent.ACTION_SEND);
		email.putExtra(Intent.EXTRA_EMAIL, new String[]{toEmailAddress});		  
		email.putExtra(Intent.EXTRA_SUBJECT, subject);
		email.putExtra(Intent.EXTRA_TEXT, message);
		email.setType("message/rfc822");
		activity.startActivity(Intent.createChooser(email, "Choose an Email client :"));
	}

	
    private static String getSharedPreferences(String key, String defValue) {
        SharedPreferences sp = activity.getPreferences(Context.MODE_PRIVATE);
        return sp.getString(key, defValue);
    }


    private static void setSharedPreferences(String key, String value) {
        SharedPreferences.Editor spe = activity.getPreferences(Context.MODE_PRIVATE).edit();
        spe.putString(key, value);
        spe.commit();
    }


	private static String getCountrySim() {
		TelephonyManager tm = (TelephonyManager)activity.getSystemService(Context.TELEPHONY_SERVICE);
		return tm.getSimCountryIso();
	}
	
	
	private static String getCountryLocale() {
		return Locale.getDefault().getCountry();
	}
	
	
	private static String getDisplayLanguage() {
		return Locale.getDefault().getDisplayLanguage();
	}
	
	
	private static String getLanguage() {
		return Locale.getDefault().getLanguage();
	}
	
	
	private static String getISO3Language() {
		return Locale.getDefault().getISO3Language();
	}
	
	
	@Override
	protected void appPause() {
		// TODO Auto-generated method stub
		
	}

	@Override
	protected void appResume() {
		// TODO Auto-generated method stub
		
	}

	@Override
	protected void appStop() {
		// TODO Auto-generated method stub
		
	}
	
}
