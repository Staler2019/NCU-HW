package com.staler2019.zenboreadmcs_data_andremotecontrolcell;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    TextView tv_ip;
    EditText et_ip;
    Button btn_conn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initShowElement();
        btn_conn.setOnClickListener(View -> toMainActivity2());
    }

    private void initShowElement(){
        tv_ip = findViewById(R.id.tv_ip);
        et_ip = findViewById(R.id.et_ip);
        btn_conn = findViewById(R.id.btn_conn);
    }

    private void toMainActivity2(){
        Bundle bundle = new Bundle();
        bundle.putString("IP",et_ip.getText().toString());

        Intent it = new Intent();
        it.putExtras(bundle);
        it.setClass(MainActivity.this,MainActivity2.class);
        startActivity(it);
    }
}