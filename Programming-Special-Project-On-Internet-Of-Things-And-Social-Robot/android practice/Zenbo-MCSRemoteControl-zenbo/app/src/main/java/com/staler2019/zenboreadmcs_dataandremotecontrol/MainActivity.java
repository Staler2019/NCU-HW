package com.staler2019.zenboreadmcs_dataandremotecontrol;

import static java.net.NetworkInterface.getNetworkInterfaces;

import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;
import android.widget.Button;
import android.widget.TextView;

import com.asus.robotframework.API.RobotCallback;
import com.asus.robotframework.API.RobotCmdState;
import com.asus.robotframework.API.RobotCommand;
import com.asus.robotframework.API.RobotErrorCode;
import com.asus.robotframework.API.RobotFace;

import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.net.URL;
import java.util.Enumeration;
import java.util.Objects;

public class MainActivity extends RobotActivity {

    TextView tv_msg;
    Button btn_test;

    // socket
    ServerThread serverThread;
    private final Handler mhandler = new Handler(Looper.getMainLooper()) {
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            String recvStr = msg.obj.toString();
            Log.d("Receive", recvStr + "\n");
            tv_msg.setText((recvStr + "\n"));
            new Thread(() -> {
                try {
                    runOnUiThread(() -> {
                        tv_msg.append("start threading...");
                    });
                    JSONObject recvObj = new JSONObject(recvStr);
                    handleJSONObj(recvObj);
                } catch (Exception e) {
                    e.printStackTrace();
                    runOnUiThread(()->{
                        tv_msg.append("\n"+e.toString());
                    });
                }
            }).start();
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // MY CODE START 1
        initViewElement();
        serverThread = new ServerThread();
        serverThread.start();
        serverThread.setHandler(mhandler);
    }

    // MY CODE START 2
    public void handleJSONObj(JSONObject jsonObj) throws Exception {

        if (jsonObj.has("Command")) {
            runOnUiThread(() -> {
                tv_msg.append("in command");
            });
            String command = jsonObj.getString("Command");
            String data;
            String sent;
            if (command.equals("temperature")) {
                data = getMCSData(Constant.TEMP_CHANNEL_ID);
                sent = "The weather today is " + data + "Celsius degree ";
            } else if (command.equals("humidity")) {
                data = getMCSData(Constant.HUMID_CHANNEL_ID);
                sent = "The humidity now is " + data + "% ";
            } else {
                Log.e("Command", "there's no \"" + command + "\".\n");
                throw new IllegalStateException("There's no \"" + command + "\".");
            }

            robotAPI.robot.setExpression(RobotFace.HAPPY, sent);
            robotAPI.utility.lookAtUser(0);
            runOnUiThread(() -> {
                tv_msg.append(data);
            });
        } else {
            runOnUiThread(() -> {

                tv_msg.append("not a command");
            });
            Log.e("Received", "there's no such command");
        }
    }

    private String getMCSData(String datachannel_id) throws Exception {
        // limit=1 read 1 data
        String urlPath = "http://" + Constant.MCS_SERVER + "/api/devices/" + Constant.MCS_DEVICE_ID + "/datachannels/" + datachannel_id + "/datapoints?limit=1";

        URL url = new URL(urlPath);
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();

        connection.setRequestMethod("GET");
        connection.setRequestProperty("deviceKey", Constant.MCS_DEVICE_KEY);
        connection.setDoInput(true);

        BufferedReader bR = new BufferedReader(new InputStreamReader(connection.getInputStream()));
        String line;
        StringBuilder responseStrBuilder = new StringBuilder();

        while ((line = bR.readLine()) != null) {
            responseStrBuilder.append(line);
        }
        bR.close();

        JSONObject jsonPost = new JSONObject(responseStrBuilder.toString());
        JSONObject object = (JSONObject) jsonPost.getJSONArray("data").get(0);
        return (String) object.getJSONObject("values").getString("value");
    }

    private static String getIPAddress() throws SocketException {
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

    private void initViewElement() {
        tv_msg = findViewById(R.id.tv_msg);
        btn_test = findViewById(R.id.btn_test);

        try {
            tv_msg.setText(("IP: " + getIPAddress()));
        } catch (SocketException e) {
            e.printStackTrace();
        }

        btn_test.setOnClickListener(view -> {
            new Thread(() -> {
                try {
                    String command = "{\"Command\":\"temperature\"}";
                    JSONObject recvObj = new JSONObject(command);
                    handleJSONObj(recvObj);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }).start();
        });
    }

    // EXTENDS SETTINGS
    public MainActivity() {
        super(robotCallback, robotListenCallback);
    }

    public static RobotCallback robotCallback = new RobotCallback() {
        @Override
        public void onResult(int cmd, int serial, RobotErrorCode err_code, Bundle result) {
            super.onResult(cmd, serial, err_code, result);

            Log.d("RobotDevSample", "onResult:"
                    + RobotCommand.getRobotCommand(cmd).name()
                    + ", serial:" + serial + ", err_code:" + err_code
                    + ", result:" + result.getString("RESULT"));
        }

        @Override
        public void onStateChange(int cmd, int serial, RobotErrorCode err_code, RobotCmdState state) {
            super.onStateChange(cmd, serial, err_code, state);
        }

        @Override
        public void initComplete() {
            super.initComplete();

        }
    };

    public static RobotCallback.Listen robotListenCallback = new RobotCallback.Listen() {
        @Override
        public void onFinishRegister() {

        }

        @Override
        public void onVoiceDetect(JSONObject jsonObject) {

        }

        @Override
        public void onSpeakComplete(String s, String s1) {

        }

        @Override
        public void onEventUserUtterance(JSONObject jsonObject) {

        }

        @Override
        public void onResult(JSONObject jsonObject) {

        }

        @Override
        public void onRetry(JSONObject jsonObject) {

        }
    };
}