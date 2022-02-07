package com.example.dlt;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import java.io.IOException;
import java.net.Socket;
import java.util.HashMap;
import com.google.gson.GsonBuilder;

import java.io.PrintWriter;
import java.io.BufferedWriter;
import java.io.OutputStreamWriter;

public class MainActivity extends AppCompatActivity {

    String SERVER_IP = "10.50.2.9";
    int SERVER_PORT = 8002;
    Socket socket;
    PrintWriter out;

    String prop = null;
    String clothes = null;
    String foreground = "anywheredoor.png";
    String mask = null;
    String background = "down.jpg";

    int flag_background = 0;
    String[] background_name = {"down.jpg","gym.jpg","playground.jpg","room.jpg","theater.jpg","treewalk.jpg","up.jpg","worldend.jpg"};
    int flag_foreground = 0;
    String[] foreground_name = {null,"anywheredoor.png","box.png","catbus.png","fatcat.png","fire.png","newbed.png","zenbo1.png","椰子.png"};
    int flag_clothes = 0;
    String[] clothes_name = {null,"Hakuho_body.png","howl.png","kingdress.png","mom.png","skelon_bond.png","sport_clothes.png","vest.png","whitesuit.png"};
    int flag_prop = 0;
    String[] prop_name = {null,"babyball.png","banana.png","baseball.png","gun.png","microphone.png","people1.png","pudding.png","watermelon.png"};
    int flag_mask = 0;
    String[] mask_name = {null,"5566.png","deer.png","gdchen.png","kitty.png","mask6.png","pika.png","zihat.png","無臉男.png"};


    Button btn_background;
    Button btn_foreground;
    Button btn_clothes;
    Button btn_props;
    Button btn_mask;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initViewElement();
        connect();
        SendMessage(setMaterialMsg());

        btn_background.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                background = background_name[flag_background];
                if(flag_background<background_name.length-1){
                    flag_background++;
                }
                else{
                    flag_background=0;
                }
                SendMessage(setMaterialMsg());
            }
        });

        btn_foreground.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                foreground = foreground_name[flag_foreground];
                if(flag_foreground<foreground_name.length-1){
                    flag_foreground++;
                }
                else{
                    flag_foreground=0;
                }
                SendMessage(setMaterialMsg());
            }
        });

        btn_clothes.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                clothes = clothes_name[flag_clothes];
                if(flag_clothes<clothes_name.length-1){
                    flag_clothes++;
                }
                else{
                    flag_clothes=0;
                }
                SendMessage(setMaterialMsg());
            }
        });

        btn_props.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                prop = prop_name[flag_prop];
                if(flag_prop<prop_name.length-1){
                    flag_prop++;
                }
                else{
                    flag_prop=0;
                }
                SendMessage(setMaterialMsg());
            }
        });

        btn_mask.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mask = mask_name[flag_mask];
                if(flag_mask<mask_name.length-1){
                    flag_mask++;
                }
                else{
                    flag_mask=0;
                }
                SendMessage(setMaterialMsg());
            }
        });

    }

    public void initViewElement(){
        btn_background = (Button) findViewById(R.id.btn_background);
        btn_foreground = (Button) findViewById(R.id.btn_foreground);
        btn_clothes = (Button) findViewById(R.id.btn_clothes);
        btn_props = (Button) findViewById(R.id.btn_props);
        btn_mask = (Button) findViewById(R.id.btn_mask);
    }

    public void connect(){
        Runnable runnable = (Runnable) () -> {
            try {
                socket = new Socket(SERVER_IP, SERVER_PORT);
                System.out.println("Connect Success");
            } catch (IOException e) {
                e.printStackTrace();
            }
        };
        Thread thread1 = new Thread(runnable);
        thread1.start();
    }

    public void SendMessage(final String msg)
    {
        Runnable runnable2 = (Runnable) () -> {
            try {
                if(socket.isConnected()) {
                    out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())), true);
                    out.println(msg);
                    Log.d("socket", msg);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        };
        Thread thread2 = new Thread(runnable2);
        thread2.start();
    }

    private String setMaterialMsg(){
        HashMap<String, Object> attribute =new HashMap<String, Object>();
        attribute.put("instruction","Scene");
        HashMap<String, Object> materials = new HashMap<String, Object>();
        materials.put("background",background==null?null:background);
        materials.put("foreground",foreground==null?null:foreground);
        materials.put("prop",prop==null?null:prop);
        materials.put("clothes",clothes==null?null:clothes);
        materials.put("mask",mask==null?null:mask);
        materials.put("shift_x",80.0);
        materials.put("shift_y",80.0);
        materials.put("scale",1.0);
        materials.put("puppet",null);
        attribute.put("material",materials);
        Log.e("hahatest",new GsonBuilder().create().toJson(attribute));
        return new GsonBuilder().create().toJson(attribute);
    }
}