package com.staler2019.zenboreadmcs_dataandremotecontrol;

import android.os.Handler;
import android.util.Log;

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
                handler.sendMessage(handler.obtainMessage(0, "{\"Status\":\"Connected\"}"));
                br = new BufferedReader(new InputStreamReader(client.getInputStream()));
                while (client.isConnected()) {
                    recvMsg();
                }
                Log.d("Client", "trying to reconnect.");
            }

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            Log.d("ServerSocket: ", "ServerSocket shutting down!");
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
}
