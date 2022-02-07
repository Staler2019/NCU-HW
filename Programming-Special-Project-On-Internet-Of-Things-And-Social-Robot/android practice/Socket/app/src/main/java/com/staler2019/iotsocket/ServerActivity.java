package com.staler2019.iotsocket;

import static java.net.NetworkInterface.getNetworkInterfaces;

import android.content.Intent;
import android.util.Log;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;

import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.Enumeration;
import java.util.Objects;

public class ServerActivity extends AppCompatActivity {

    TextView tv_showNameTag;
    TextView tv_IP;
    EditText et_inputName;
    Button btn_conn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_server);

        initViewElement();
        try {
            String ipMsg = "Your IP\n" + getIPAddress() + "\n";
            tv_IP.setText(ipMsg);
        } catch (SocketException e) {
            e.printStackTrace();
        }
        btn_conn.setOnClickListener(view -> toServerMsgActivity());
    }

    private void initViewElement() {
        tv_showNameTag = (TextView) findViewById(R.id.tv_showNameTag);
        tv_IP = (TextView) findViewById(R.id.tv_IP);
        et_inputName = (EditText) findViewById(R.id.et_inputName);
        btn_conn = (Button) findViewById(R.id.btn_conn);
    }

    private void toServerMsgActivity() {
        Bundle bundle = new Bundle();
        bundle.putString("serverName", et_inputName.getText().toString());

        Intent it = new Intent();
        it.putExtras(bundle);
        it.setClass(ServerActivity.this, ServerMsgActivity.class);
        startActivity(it);
    }
    // my function
    public static String getIPAddress() throws SocketException {
        StringBuilder IFCONFIG = new StringBuilder();
        Enumeration<NetworkInterface> en = getNetworkInterfaces();
        while (en.hasMoreElements()) {
            NetworkInterface intf = en.nextElement();
            Enumeration<InetAddress> enumIpAddr = intf.getInetAddresses();
            while (enumIpAddr.hasMoreElements()) {
                InetAddress inetAddress = enumIpAddr.nextElement();
                if (!inetAddress.isLoopbackAddress() && !inetAddress.isLinkLocalAddress() && inetAddress.isSiteLocalAddress()) {
                    IFCONFIG.append(Objects.requireNonNull(inetAddress.getHostAddress()));
                }
            }
        }
        Log.d("SERVER_IP", IFCONFIG.toString());
        return IFCONFIG.toString();
    }
}