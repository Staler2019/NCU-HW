package com.staler2019.iotsocket;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class ServerMsgActivity extends AppCompatActivity {

    Button btn_lea;
    Button btn_send;
    EditText et_sendMsg;
    TextView tv_showMsgName;
    TextView tv_showMsg;
    ServerThread serverThread;
    MsgObj msgObj;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_server_msg);

        initViewElement();
        getIntentMsg();
        serverThread = new ServerThread();
        serverThread.start();
        serverThread.setHandler(mhandler);
        btn_lea.setOnClickListener(view -> toMainActivity());
        btn_send.setOnClickListener(view -> {
            String writeLine = et_sendMsg.getText().toString();
            if (!writeLine.equals("")) {
                serverThread.sendMsg(writeLine);
                et_sendMsg.setText("");
            }
        });
    }

    private void initViewElement() {
        btn_lea = (Button) findViewById(R.id.btn_lea);
        btn_send = (Button) findViewById(R.id.btn_send);
        et_sendMsg = (EditText) findViewById(R.id.et_sendMsg);
        tv_showMsgName = (TextView) findViewById(R.id.tv_showMsgName);
        tv_showMsg = (TextView) findViewById(R.id.tv_showMsg);
    }

    private void toMainActivity() {
        serverThread.terminate();

        Intent it = new Intent();
        it.setClass(ServerMsgActivity.this, MainActivity.class);
        startActivity(it);
    }

    private void getIntentMsg() {
        Intent it = this.getIntent();
        if (it != null) {
            Bundle bundle = it.getExtras();
            if (bundle != null) {
                String serverName = bundle.getString("serverName");
                if (serverName != null && !serverName.equals("")) {
                    String showMsgName = "Hi~ " + serverName;
                    tv_showMsgName.setText(showMsgName);
                    msgObj = new MsgObj(serverName);
                }
                // TODO. ERROR CHECKING
            }
        }
    }
    // handler
    private final Handler mhandler = new Handler(Looper.getMainLooper()) {
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            Log.d("Receive", msg.obj.toString() + "\n");
            tv_showMsg.append(msg.obj.toString() + "\n");
        }
    };
}