package com.staler2019.iotsocket;

import android.os.Handler;
import android.util.Log;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

public class ServerThread extends Thread {

    private final ArrayList<Socket> clients = new ArrayList<>();
    private int connCount = 0;
    private ServerSocket serverSocket;
    private final int SERVER_PORT = Constant.SERVER_PORT;
    private Handler handler;

    // thread control
    @Override
    public void run() {
        try {

            serverSocket = new ServerSocket(SERVER_PORT);
            handlerSendMsg(MsgObj.NAME + " started.(" + ServerActivity.getIPAddress() + ":" + Integer.valueOf(SERVER_PORT) + ")");

            while (!serverSocket.isClosed()) {
                waitNewClient();
            }

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            handlerSendMsg("serverSocketClose");
        }
    }

    public void terminate() {
        try {

            handlerSendMsg("leaving...");
            leaveMsg();
            Thread.sleep(2000);
            serverSocket.close();

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void setHandler(Handler handler) {
        this.handler = handler;
    }
    // my functions
    private void waitNewClient() {
        try {

            Socket socket = serverSocket.accept();
            ++connCount;
            addNewClient(socket);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void addNewClient(final Socket socket) {
        new Thread(() -> {
            try {

                clients.add(socket);
                String ipPort = socket.getInetAddress().getHostAddress() + ":" + socket.getPort();
                BufferedReader br = new BufferedReader(new InputStreamReader((socket.getInputStream())));

                recvFirstMsg(br, ipPort);

                while (socket.isConnected()) {
                    if (!recvMsg(br)) {
                        break;
                    }
                }
            } catch (IOException e) {
                e.getStackTrace();
            } finally {
                clients.remove(socket);
                --connCount;
                Log.d("users amount", String.valueOf(connCount));
            }
        }).start();
    }
    // handler
    private void handlerSendMsg(String msg) {
        handler.sendMessage(handler.obtainMessage(0, msg));
    }
    // send msg
    public void sendMsg(String msg) {
        handlerSendMsg("You: " + msg);
        castMsg(MsgObj.NAME, msg);
        Log.d("SendMsg", msg);
    }

    private void castMsg(String name, String msg) {
        Socket[] clientArrays = new Socket[clients.size()];
        clients.toArray(clientArrays);

        for (Socket socket : clientArrays) {
            new Thread(() -> {
                try {

                    BufferedWriter bw;
                    bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
                    JSONObject writeObj = new JSONObject();
                    writeObj.put(MsgObj.LABEL_NAME, name);
                    writeObj.put(MsgObj.LABEL_MSG, msg);

                    bw.write(writeObj + "\n");
                    bw.flush();

                } catch (JSONException | IOException e) {
                    e.printStackTrace();
                }
            }).start();
        }
    }

    private void leaveMsg() {
        castMsg(MsgObj.NAME, "Server closed. Please press leave button.");
        Log.d("SendMsg", "Server closed. Please press leave button.");
    }
    // receive msg
    private boolean recvMsg(BufferedReader br) {
        try {
            String rl;
            rl = br.readLine();
            if (rl != null && !rl.equals("")) {
                JSONObject readObj = new JSONObject(rl);
                if (readObj.has(MsgObj.LABEL_ACTION)) {
                    if (readObj.getInt(MsgObj.LABEL_ACTION) == 1) {
                        sendMsg(readObj.getString(MsgObj.LABEL_NAME) + " has left.");
                        return false;
                    }
                }
                String name = readObj.getString(MsgObj.LABEL_NAME);
                String msg = readObj.getString(MsgObj.LABEL_MSG);

                handlerSendMsg(name + ": " + msg);
                castMsg(name, msg);
            }

        } catch (IOException | JSONException e) {
            e.printStackTrace();
        }
        return true;
    }

    private void recvFirstMsg(BufferedReader br, String ipPort) {
        while (true) {
            try {

                String rl = br.readLine();
                if (rl != null && !rl.equals("")) {
                    JSONObject readObj = new JSONObject(rl);
                    String name = readObj.getString(MsgObj.LABEL_NAME);

                    handlerSendMsg("\n" + name + "(" + ipPort + ") connected.\n");
                    handlerSendMsg(MsgObj.NAME + ": Welcome " + name + " join us!");
                    castMsg(MsgObj.NAME, "Welcome " + name + " join us!");
                    break;
                }

            } catch (IOException | JSONException e) {
                e.printStackTrace();
            }
        }
    }
}
