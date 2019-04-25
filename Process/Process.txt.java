//三种查看UID的方法
//1
M01_AE:/ # dumpsys package com.android.car | grep userId                                                                                                              
    userId=1000
    userId=1000
//2
M01_AE:/ # ps -A | grep com.android.car
system        7657   518 4384568  59860 SyS_epoll_wait 705fe9150c S com.android.car
M01_AE:/ # cat /proc/7657/status | grep Uid
Uid:	1000	1000	1000	1000
//3
M01_AE:/ # cat /data/system/packages.xml | grep com.android.car
    <package name="com.android.car" codePath="/system/priv-app/CarService" nativeLibraryPath="/system/priv-app/CarService/lib" primaryCpuAbi="arm64-v8a" publicFlags="940064333" privateFlags="8" ft="16a52ab6f40" it="16a4be92238" ut="16a52ab6f40" version="27" sharedUserId="1000" isOrphaned="true">

//代码路径 
//frameworks/base/core/java/android/os/Process.java
//system/core/libcutils/sched_policy.cpp

public static final int ROOT_UID = 0;
public static final int SYSTEM_UID = 1000;
public static final int PHONE_UID = 1001;
public static final int SHELL_UID = 2000;
public static final int LOG_UID = 1007;
public static final int WIFI_UID = 1010;
public static final int MEDIA_UID = 1013;
public static final int DRM_UID = 1019;
public static final int VPN_UID = 1016;
public static final int KEYSTORE_UID = 1017;
public static final int NFC_UID = 1027;
public static final int BLUETOOTH_UID = 1002;
public static final int MEDIA_RW_GID = 1023;
public static final int PACKAGE_INFO_GID = 1032;
public static final int SHARED_RELRO_UID = 1037;
public static final int AUDIOSERVER_UID = 1041;
public static final int CAMERASERVER_UID = 1047;
public static final int WEBVIEW_ZYGOTE_UID = 1051;
public static final int OTA_UPDATE_UID = 1061;
public static final int NOBODY_UID = 9999;
public static final int FIRST_APPLICATION_UID = 10000;
public static final int LAST_APPLICATION_UID = 19999;
public static final int FIRST_ISOLATED_UID = 99000;
public static final int LAST_ISOLATED_UID = 99999;
public static final int SHARED_USER_GID = 9997;
public static final int FIRST_APPLICATION_CACHE_GID = 20000;
public static final int LAST_APPLICATION_CACHE_GID = 29999;

