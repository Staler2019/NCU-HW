package com.staler2019.zenboremotecontrolproject;

import android.util.Log;
import android.os.Handler;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

public class ServerThread extends Thread {

    ServerSocket serverSocket;
    int serverPort = Constant.SERVER_PORT;
    Socket client;
    BufferedReader br;
    Handler handler;

    @Override
    public void run() {
        try {
            serverSocket = new ServerSocket(serverPort);
            while (!serverSocket.isClosed()) {
                client = serverSocket.accept();

                new Thread(() -> {
                    try {
                        handler.sendMessage(handler.obtainMessage(1, "status: connected"));
                        br = new BufferedReader(new InputStreamReader((client.getInputStream())));
                        while (client.isConnected()) {
                            recvMsg();
                        }
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }).start();

                Log.d("Client disconnect", "trying to reconnect.");
                handler.sendMessage(handler.obtainMessage(1, "status: disconnected"));
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            Log.d("ServerSocket", "ServerSocket shutting down");
        }

    }

    private void recvMsg() {
        try {
            String rl;
            rl = br.readLine();
            if (rl != null && !rl.equals("")) {
                handler.sendMessage(handler.obtainMessage(0, rl));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void setHandler(Handler handler) {
        this.handler = handler;
    }

//    public void terminate() {
//        try {
//            serverSocket.close();
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//    }
}
