package com.staler2019.zenbotest;

import android.os.Bundle;
import android.os.CountDownTimer;
import android.util.Log;
import android.view.View;

import com.asus.robotframework.API.RobotCallback;
import com.asus.robotframework.API.RobotCmdState;
import com.asus.robotframework.API.RobotCommand;
import com.asus.robotframework.API.RobotErrorCode;
import com.asus.robotframework.API.RobotFace;

import org.json.JSONObject;

public class MainActivity extends RobotActivity {

    CountDownTimer mCountDownTimer;
    private String[] FaceCandidateArray = {"INTERESTED", "DOUBTING", "PROUD", "DEFAULT", "HAPPY", "EXPECTING", "SHOCKED", "QUESTIONING", "IMPATIENT", "ACTIVE",
            "PLEASED", "HELPLESS", "SERIOUS", "WORRIED", "PRETENDING", "LAZY", "AWARE_RIGHT", "TIRED", "SHY", "INNOCENT",
            "SINGING", "AWARE_LEFT", "DEFAULT_STILL", "HIDEFACE"};
    private int counter = 0;

    public MainActivity() {
        super(robotCallback, robotListenCallback);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

//        getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_HIDDEN);

        robotAPI.robot.setExpression(RobotFace.INTERESTED);
        mCountDownTimer = new CountDownTimer(1000 * FaceCandidateArray.length * 2, 1000) {

            public void onTick(long millisUntilFinished) {
                set(FaceCandidateArray[counter]);
                counter++;
                if (counter == FaceCandidateArray.length)
                    counter = 0;
            }

            public void onFinish() {
            }

        };
        mCountDownTimer.start();
    }

    @Override
    protected void onPause() {
        super.onPause();

        mCountDownTimer.cancel();
    }

    @Override
    public void onWindowFocusChanged(boolean hasFocus) {

        if (hasFocus) {
            View decorView = getWindow().getDecorView();
            decorView.setSystemUiVisibility(View.SYSTEM_UI_FLAG_HIDE_NAVIGATION |
                    View.SYSTEM_UI_FLAG_FULLSCREEN |
                    View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY |
                    View.SYSTEM_UI_FLAG_LAYOUT_STABLE |
                    View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
            );
        }
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

    private void set(String SpinnerText) {
        if (SpinnerText.equals("INTERESTED")) {
            robotAPI.robot.setExpression(RobotFace.INTERESTED);
        } else if (SpinnerText.equals("DOUBTING")) {
            robotAPI.robot.setExpression(RobotFace.DOUBTING);
        } else if (SpinnerText.equals("PROUD")) {
            robotAPI.robot.setExpression(RobotFace.PROUD);
        } else if (SpinnerText.equals("DEFAULT")) {
            robotAPI.robot.setExpression(RobotFace.DEFAULT);
        } else if (SpinnerText.equals("HAPPY")) {
            robotAPI.robot.setExpression(RobotFace.HAPPY);
        } else if (SpinnerText.equals("EXPECTING")) {
            robotAPI.robot.setExpression(RobotFace.EXPECTING);
        } else if (SpinnerText.equals("SHOCKED")) {
            robotAPI.robot.setExpression(RobotFace.SHOCKED);
        } else if (SpinnerText.equals("QUESTIONING")) {
            robotAPI.robot.setExpression(RobotFace.QUESTIONING);
        } else if (SpinnerText.equals("IMPATIENT")) {
            robotAPI.robot.setExpression(RobotFace.IMPATIENT);
        } else if (SpinnerText.equals("ACTIVE")) {
            robotAPI.robot.setExpression(RobotFace.ACTIVE);
        } else if (SpinnerText.equals("PLEASED")) {
            robotAPI.robot.setExpression(RobotFace.PLEASED);
        } else if (SpinnerText.equals("HELPLESS")) {
            robotAPI.robot.setExpression(RobotFace.HELPLESS);
        } else if (SpinnerText.equals("SERIOUS")) {
            robotAPI.robot.setExpression(RobotFace.SERIOUS);
        } else if (SpinnerText.equals("WORRIED")) {
            robotAPI.robot.setExpression(RobotFace.WORRIED);
        } else if (SpinnerText.equals("PRETENDING")) {
            robotAPI.robot.setExpression(RobotFace.PRETENDING);
        } else if (SpinnerText.equals("LAZY")) {
            robotAPI.robot.setExpression(RobotFace.LAZY);
        } else if (SpinnerText.equals("AWARE_RIGHT")) {
            robotAPI.robot.setExpression(RobotFace.AWARE_RIGHT);
        } else if (SpinnerText.equals("TIRED")) {
            robotAPI.robot.setExpression(RobotFace.TIRED);
        } else if (SpinnerText.equals("SHY")) {
            robotAPI.robot.setExpression(RobotFace.SHY);
        } else if (SpinnerText.equals("INNOCENT")) {
            robotAPI.robot.setExpression(RobotFace.INNOCENT);
        } else if (SpinnerText.equals("SINGING")) {
            robotAPI.robot.setExpression(RobotFace.SINGING);
        } else if (SpinnerText.equals("AWARE_LEFT")) {
            robotAPI.robot.setExpression(RobotFace.AWARE_LEFT);
        } else if (SpinnerText.equals("DEFAULT_STILL")) {
            robotAPI.robot.setExpression(RobotFace.DEFAULT_STILL);
        } else if (SpinnerText.equals("HIDEFACE")) {
            robotAPI.robot.setExpression(RobotFace.HIDEFACE);
        }
    }
}

