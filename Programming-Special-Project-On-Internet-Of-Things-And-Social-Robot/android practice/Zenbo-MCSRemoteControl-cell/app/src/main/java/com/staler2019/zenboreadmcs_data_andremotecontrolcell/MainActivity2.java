package com.staler2019.zenboreadmcs_data_andremotecontrolcell;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity2 extends AppCompatActivity {

    TextView tv_title;
    Button btn_temp;
    Button btn_humid;

    String serverIP;
    ClientThread clientThread;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);

        initViewElement();
        getIntentMsg();
        clientThread = new ClientThread(serverIP, Constant.SERVER_PORT);
        clientThread.start();
        btn_temp.setOnClickListener(view -> ClientThread.sendMsg("temperature"));
        btn_humid.setOnClickListener(view -> ClientThread.sendMsg("humidity"));
    }

    private void initViewElement(){
        tv_title = findViewById(R.id.tv_title);
        btn_temp = findViewById(R.id.btn_temp);
        btn_humid = findViewById(R.id.btn_humid);
    }

    private void getIntentMsg() {
        Intent it = this.getIntent();
        if(it!=null){
            Bundle bundle = it.getExtras();
            if(bundle!=null){
                serverIP = bundle.getString("IP");
            }
        }
    }
}