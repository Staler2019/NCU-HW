package com.staler2019.iotsocket;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class ClientMsgActivity extends AppCompatActivity {

    Button btn_cLea;
    Button btn_cSend;
    EditText et_cSendMsg;
    TextView tv_cShowMsgName;
    TextView tv_cShowMsg;
    ClientThread clientThread;
    MsgObj msgObj;
    String serverIP;
    int serverPort;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_client_msg);

        initViewElement();
        getIntentMsg();
        btn_cLea.setOnClickListener(view -> toMainActivity());
        btn_cSend.setOnClickListener(view -> {
            String writeLine = et_cSendMsg.getText().toString();
            if(!writeLine.equals("")) {
                clientThread.sendMsg(writeLine);
                et_cSendMsg.setText("");
            }
        });
        clientThread = new ClientThread(serverIP, serverPort);
        clientThread.start();
        clientThread.setHandler(mhandler);
    }

    private void initViewElement() {
        btn_cLea = (Button) findViewById(R.id.btn_cLea);
        btn_cSend = (Button) findViewById(R.id.btn_cSend);
        et_cSendMsg = (EditText) findViewById(R.id.et_cSendMsg);
        tv_cShowMsgName = (TextView) findViewById(R.id.tv_cShowMsgName);
        tv_cShowMsg = (TextView) findViewById(R.id.tv_cShowMsg);
    }

    private void getIntentMsg() {
        Intent it = this.getIntent();
        if (it != null) {
            Bundle bundle = it.getExtras();
            if (bundle != null) {
                String clientName = bundle.getString("clientName");
                serverIP = bundle.getString("serverIP");
                serverPort = Integer.parseInt(bundle.getString("serverPort"));
                if (clientName != null && !clientName.equals("")) {
                    String showMsgName = "Hi~ " + clientName;
                    tv_cShowMsgName.setText(showMsgName);
                    msgObj = new MsgObj(clientName);
                }
                // TODO. ERROR CHECKING
            }
        }
    }

    private void toMainActivity() {
        clientThread.terminate();

        Intent it = new Intent();
        it.setClass(ClientMsgActivity.this, MainActivity.class);
        startActivity(it);
    }
    // handler
    private final Handler mhandler = new Handler(Looper.getMainLooper()) {
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            Log.d("Receive", msg.obj.toString() + "\n");
            tv_cShowMsg.append(msg.obj.toString() + "\n");
        }
    };
}