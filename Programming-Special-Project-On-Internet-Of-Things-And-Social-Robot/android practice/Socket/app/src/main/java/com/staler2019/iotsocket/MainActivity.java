package com.staler2019.iotsocket;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

    Button btn_server;
    Button btn_client;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initViewElement();
        btn_server.setOnClickListener(view -> toServerActivity());
        btn_client.setOnClickListener(view -> toClientActivity());
    }

    private void initViewElement(){
        btn_server = (Button) findViewById(R.id.btn_server);
        btn_client = (Button) findViewById(R.id.btn_client);
    }

    private void toServerActivity(){
        Intent it = new Intent();
        it.setClass(MainActivity.this, ServerActivity.class);
        startActivity(it);
    }

    private void toClientActivity(){
        Intent it = new Intent();
        it.setClass(MainActivity.this, ClientActivity.class);
        startActivity(it);
    }
}