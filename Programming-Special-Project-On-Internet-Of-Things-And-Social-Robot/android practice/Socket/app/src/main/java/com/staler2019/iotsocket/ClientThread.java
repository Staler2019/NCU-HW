package com.staler2019.iotsocket;

import android.os.Handler;
import android.util.Log;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.InetAddress;
import java.net.Socket;

public class ClientThread extends Thread {

    private final String serverIP;
    private final int serverPort;
    private Handler handler;
    private Socket clientSocket;
    private BufferedReader br;
    private BufferedWriter bw;
    // thread control
    ClientThread(String serverIP, int serverPort) {
        this.serverIP = serverIP;
        this.serverPort = serverPort;
    }

    @Override
    public void run() {
        try {

            InetAddress _serverIP = InetAddress.getByName(serverIP);
            clientSocket = new Socket(_serverIP, serverPort);
            handlerSendMsg("Hi! " + MsgObj.NAME);

            bw = new BufferedWriter(new OutputStreamWriter(clientSocket.getOutputStream()));
            br = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

            sendHelloMsg();

            while (clientSocket.isConnected()) {
                recvMsg();
            }

        } catch (Exception e) {
            e.printStackTrace();
            Log.d("socket connection", "Client: " + e.toString());
        } finally {
            handlerSendMsg("Socket disconnected!");
        }
    }

    public void setHandler(Handler handler) {
        this.handler = handler;
    }

    public void terminate() {
        try {
            leaveMsg();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    // handler
    private void handlerSendMsg(String msg) {
        handler.sendMessage(handler.obtainMessage(0, msg));
    }
    // send msg
    public void sendMsg(String msg) {
        handlerSendMsg("You: " + msg);
        new Thread(() -> {
            try {

                JSONObject writeObj = new JSONObject();
                writeObj.put(MsgObj.LABEL_NAME, MsgObj.NAME);
                writeObj.put(MsgObj.LABEL_MSG, msg);

                bw.write(writeObj + "\n");
                bw.flush();

            } catch (JSONException | IOException e) {
                e.printStackTrace();
            }
            Log.d("SendMsg", msg);
        }).start();
    }

    private void sendHelloMsg() {
        new Thread(() -> {
            try {

                JSONObject writeObj = new JSONObject();
                writeObj.put(MsgObj.LABEL_NAME, MsgObj.NAME);
                writeObj.put(MsgObj.LABEL_MSG, "say hello to server");

                bw.write(writeObj + "\n");
                bw.flush();

            } catch (JSONException | IOException e) {
                e.printStackTrace();
            }
            Log.d("SendHelloMsg", "say hello to server");
        }).start();
    }

    private void leaveMsg(){
        new Thread(() -> {
            try {

                JSONObject writeObj = new JSONObject();
                writeObj.put(MsgObj.LABEL_NAME, MsgObj.NAME);
                writeObj.put(MsgObj.LABEL_MSG, "leave the chat");
                writeObj.put(MsgObj.LABEL_ACTION, 1);

                bw.write(writeObj + "\n");
                bw.flush();

                bw.close();
                br.close();
                clientSocket.close();

            } catch (JSONException | IOException e) {
                e.printStackTrace();
            }
            Log.d("SendLeaveMsg", "leave the chat");
        }).start();
    }
    // recv msg
    private void recvMsg() {
        try {

            String rl = br.readLine();
            if (rl != null && !rl.equals("")) {
                JSONObject readObj = new JSONObject(rl);
                String name = readObj.getString(MsgObj.LABEL_NAME);
                String msg = readObj.getString(MsgObj.LABEL_MSG);

                if (!name.equals(MsgObj.NAME)) {
                    handlerSendMsg(name + ": " + msg);
                }
            }

        } catch (IOException | JSONException e) {
            e.printStackTrace();
        }
    }
}