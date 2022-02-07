package com.staler2019.zenboremotecontrolproject;
// motion, wheelLight
/* light: mode,
0.setBrightness
1.setColor
2.startBlinking
3.startBreathing
4.startCharging
5.startMarquee
6.turnOff
 */

import static java.net.NetworkInterface.getNetworkInterfaces;

import androidx.appcompat.app.AppCompatActivity;

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
import com.asus.robotframework.API.WheelLights;

import org.json.JSONException;
import org.json.JSONObject;
import org.w3c.dom.Text;

import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.Enumeration;
import java.util.Objects;

public class MainActivity extends RobotActivity {

    // MY VAR
    TextView tv_showIP;
    int color = 0x00ff00;
    int bright = 10;
    ServerThread serverThread;
    private final Handler mhandler = new Handler(Looper.getMainLooper()) {
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            Log.d("Receive", msg.obj.toString() + "\n");
            tv_showIP.setText(msg.obj.toString() + "\n");
            if (msg.what == 0) {
                try {
                    JSONObject recvObj = new JSONObject(msg.obj.toString()); // TODO. what is the receiving code
                    handlerLightMotion(recvObj);
                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        // MY CODE START 1
        tv_showIP = (TextView) findViewById(R.id.tv_showIP);
        try {
            tv_showIP.setText((getIPAddress() + String.valueOf(Constant.SERVER_PORT)));
        } catch (SocketException e) {
            e.printStackTrace();
        }

        serverThread = new ServerThread();
        serverThread.start();
        serverThread.setHandler(mhandler);
    }

    // MY CODE START 2
    private void handlerLightMotion(JSONObject jsonObj) {
        try {
            if (jsonObj.has("Light")) {
                int light = jsonObj.getInt("Light");
                switch (light) {
                    case 0://.setBrightness TODO.?? error
                        bright = jsonObj.getInt("Brightness");
                        robotAPI.wheelLights.setBrightness(WheelLights.Lights.SYNC_BOTH, 0xff, bright);
                        break;
                    case 1://.setColor TODO.?? error
                        color = jsonObj.getInt("Color");
                        robotAPI.wheelLights.setColor(WheelLights.Lights.SYNC_BOTH, 0xff, color);
                        break;
                    case 2://.startBlinking
                        robotAPI.wheelLights.turnOff(WheelLights.Lights.SYNC_BOTH, 0xff);
                        robotAPI.wheelLights.setColor(WheelLights.Lights.SYNC_BOTH, 0xff, color);
                        robotAPI.wheelLights.setBrightness(WheelLights.Lights.SYNC_BOTH, 0xff, bright);
                        robotAPI.wheelLights.startBlinking(WheelLights.Lights.SYNC_BOTH, 0xff, 30, 10, 5);
                        break;
                    case 3://.startBreathing
                        robotAPI.wheelLights.turnOff(WheelLights.Lights.SYNC_BOTH, 0xff);
                        robotAPI.wheelLights.setColor(WheelLights.Lights.SYNC_BOTH, 0xff, color);
                        robotAPI.wheelLights.setBrightness(WheelLights.Lights.SYNC_BOTH, 0xff, bright);
                        robotAPI.wheelLights.startBreathing(WheelLights.Lights.SYNC_BOTH, 0xff, 20, 10, 0);
                        break;
                    case 4://.startCharging
                        robotAPI.wheelLights.turnOff(WheelLights.Lights.SYNC_BOTH, 0xff);
                        robotAPI.wheelLights.setColor(WheelLights.Lights.SYNC_BOTH, 0xff, color);
                        robotAPI.wheelLights.setBrightness(WheelLights.Lights.SYNC_BOTH, 0xff, bright);
                        robotAPI.wheelLights.startCharging(WheelLights.Lights.SYNC_BOTH, 0, 1, WheelLights.Direction.DIRECTION_FORWARD, 20);
                        break;
                    case 5://.startMarquee
                        robotAPI.wheelLights.turnOff(WheelLights.Lights.SYNC_BOTH, 0xff);
                        robotAPI.wheelLights.setBrightness(WheelLights.Lights.SYNC_BOTH, 0xff, bright * 2); // TODO.?? error
                        robotAPI.wheelLights.startMarquee(WheelLights.Lights.SYNC_BOTH, WheelLights.Direction.DIRECTION_FORWARD, 40, 20, 3);
                        break;
                    case 6://.turnOff
                        robotAPI.wheelLights.turnOff(WheelLights.Lights.SYNC_BOTH, 0xff);
                        break;
                    default:
                        Log.d("Receive Light", "number out of range");
                        break;
                }
            }

            if (jsonObj.has("Motion")) {
                int motion = jsonObj.getInt("Motion");
                switch (motion) {
                    case 0:
                        robotAPI.motion.remoteControlBody(Direction.Body.FORWARD);
                        break;
                    case 1:
                        robotAPI.motion.remoteControlBody(Direction.Body.BACKWARD);
                        break;
                    case 2:
                        robotAPI.motion.remoteControlBody(Direction.Body.TURN_RIGHT);
                        break;
                    case 3:
                        robotAPI.motion.remoteControlBody(Direction.Body.TURN_LEFT);
                        break;
                    case 4:
                        robotAPI.motion.remoteControlBody(Direction.Body.STOP);
                        break;
                    default:
                        Log.d("Receive Motion", "number out of range");
                        break;
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

    // DEFAULT SETTINGS
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