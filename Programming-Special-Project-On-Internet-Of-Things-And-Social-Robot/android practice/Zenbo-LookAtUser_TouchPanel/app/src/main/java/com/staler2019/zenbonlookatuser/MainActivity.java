package com.staler2019.zenbonlookatuser;

import static java.net.NetworkInterface.getNetworkInterfaces;

import androidx.appcompat.app.AppCompatActivity;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;
import android.widget.TextView;

import com.asus.robotframework.API.MotionControl.*;
import com.asus.robotframework.API.RobotCallback;
import com.asus.robotframework.API.RobotCmdState;
import com.asus.robotframework.API.RobotCommand;
import com.asus.robotframework.API.RobotErrorCode;
import com.asus.robotframework.API.Utility;
import com.asus.robotframework.API.WheelLights;

import org.json.JSONException;
import org.json.JSONObject;

import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.Enumeration;
import java.util.Objects;

public class MainActivity extends RobotActivity {

    // ui
//    TextView show_ip;
    TextView tv_va0; // mTextView_capacity_touch_value0
    TextView tv_va1; // mTextView_capacity_touch_value1

    // socket
//    ServerThread serverThread;
//    private final Handler mhandler = new Handler(Looper.getMainLooper()) {
//        @Override
//        public void handleMessage(Message msg) {
//            super.handleMessage(msg);
//            Log.d("Receive", msg.obj.toString() + "\n");
//            try {
//                JSONObject recvObj = new JSONObject(msg.obj.toString());
////                show_ip.append("\nreceived" + msg.obj.toString());
//                handlerHeadMotion(recvObj);
//            } catch (JSONException e) {
//                e.printStackTrace();
//            }
//        }
//    };

    // zenbo
    public static final int TYPE_CAPACITY_TOUCH = Utility.SensorType.CAPACITY_TOUCH;

    // android
    private SensorManager mSensorManager;
    private Sensor mSensorCapacityTouch;
    // listener - TYPE_CAPACITY_TOUCH
    SensorEventListener listenerCapacityTouch = new SensorEventListener() {
        @Override
        public void onSensorChanged(SensorEvent sensorEvent) {
            tv_va0.setText(("kind of touching:" + String.valueOf(sensorEvent.values[0])));
            tv_va1.setText(("duration secs:" + String.valueOf(sensorEvent.values[1])));
        }

        @Override
        public void onAccuracyChanged(Sensor sensor, int acc) {
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initViewElement();
        initSensorElement();
//        serverThread = new ServerThread();
//        serverThread.start();
//        serverThread.setHandler(mhandler);
    }

    // my fun
    private void handlerHeadMotion(JSONObject jsonObj) {
        try {
            if (jsonObj.has("look")) {
                if (jsonObj.getString("look").equals(("look"))) {
                    robotAPI.utility.lookAtUser(0);
//                    show_ip.append("\nlooked");
                }

            }
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    private String getIPAddress() throws SocketException {
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
//        show_ip = findViewById(R.id.ip);
        tv_va0 = findViewById(R.id.tv_va0);
        tv_va1 = findViewById(R.id.tv_va1);

//        try {
//
//            show_ip.setText((getIPAddress() + ":12345"));
//
//        } catch (SocketException e) {
//            e.printStackTrace();
//        }
    }

    private void initSensorElement() {
        // sensor manager
        mSensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
        // sensors
        mSensorCapacityTouch = mSensorManager.getDefaultSensor(TYPE_CAPACITY_TOUCH);
    }

    @Override
    protected void onResume() {

        super.onResume();
        mSensorManager.registerListener(listenerCapacityTouch, mSensorCapacityTouch, SensorManager.SENSOR_DELAY_UI);
    }

    // setting
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