package com.steven.ndk35.sort;

/**
 * Description:
 * Data：8/28/2018-4:43 PM
 *
 * @author yanzhiwen
 */
public class SortUtils {

    static {
        System.loadLibrary("native-lib");
    }

    public static native String sort();

}
