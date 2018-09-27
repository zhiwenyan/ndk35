package com.steven.ndk35;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

import com.steven.ndk35.sort.SortUtils;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        SortUtils.sort();
    }
}
