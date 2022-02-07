package com.staler2019.zenboreadmcs_data_andremotecontrolcell;

import android.net.InetAddresses;
import android.os.Handler;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

public class ClientThread extends Thread {

    private final String serverIP;
    private final int serverPort;
    private Socket clientSocket;
    private static BufferedWriter bw;

    ClientThread(String serverIP, int serverPort) {
        this.serverIP = serverIP;
        this.serverPort = serverPort;
    }

    @Override
    public void run() {
        try {

            InetAddress _serverIP = InetAddress.getByName(serverIP);
            clientSocket = new Socket(_serverIP, serverPort);
            bw = new BufferedWriter(new OutputStreamWriter(clientSocket.getOutputStream()));

            while (clientSocket.isConnected());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void sendMsg(String msg) {
        new Thread(() -> {

            try {
                JSONObject jsonObj = new JSONObject();
                jsonObj.put("Command", msg);

                bw.write(jsonObj+"\n");
                bw.flush();

            } catch (JSONException | IOException e) {
                e.printStackTrace();
            }

        }).start();
    }
}
