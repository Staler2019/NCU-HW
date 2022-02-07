package com.staler2019.iotsocket;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class ClientActivity extends AppCompatActivity {

    EditText et_cPort;
    EditText et_cIP;
    EditText et_cName;
    TextView tv_cPort;
    TextView tv_cIP;
    TextView tv_cName;
    Button btn_cConn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_client);

        initViewElement();
        btn_cConn.setOnClickListener(view -> toClientMsgActivity());
    }

    private void initViewElement() {
        et_cPort = (EditText)findViewById(R.id.et_cPort);
        et_cIP = (EditText) findViewById(R.id.et_cIP);
        et_cName = (EditText) findViewById(R.id.et_cName);
        tv_cPort = (TextView) findViewById(R.id.tv_cPort);
        tv_cIP = (TextView) findViewById(R.id.tv_cIP);
        tv_cName = (TextView) findViewById(R.id.tv_cName);
        btn_cConn = (Button) findViewById(R.id.btn_cConn);

        et_cPort.setText(String.valueOf(Constant.SERVER_PORT));
    }

    private void toClientMsgActivity() {
        Bundle bundle = new Bundle();
        bundle.putString("clientName", et_cName.getText().toString());
        bundle.putString("serverIP", et_cIP.getText().toString());
        bundle.putString("serverPort", et_cPort.getText().toString());

        Intent it = new Intent();
        it.putExtras(bundle);
        it.setClass(ClientActivity.this,ClientMsgActivity.class);
        startActivity(it);
    }
}