package com.example.yanchunlan.socketprocess;

/**
 * Author: Ycl
 * Data: 2018/4/11 21:24
 * Desc:
 */

public class Watcher {
    static {
        System.loadLibrary("native-lib");
    }
    public native void createWatcher(String userId);
    public native void connectMonitor();
}
