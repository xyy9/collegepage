package com.example.a12_02_zenbo;

import androidx.appcompat.app.AppCompatActivity;

import com.asus.robotframework.API.RobotAPI;
import com.asus.robotframework.API.WheelLights;

import android.os.Bundle;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.util.Enumeration;




public class MainActivity extends AppCompatActivity {
    private TextView text;
    private Button btn_start, btn_close;
    private ServerSocket server;
    private int PORT;
    private boolean flag;
    private Socket client;
    private String ip;
    RobotAPI mRobotAPI;

    public static String getLocalIpAddress() {
        try {
            for (Enumeration<NetworkInterface>
                 en = NetworkInterface.getNetworkInterfaces(); en.hasMoreElements();) {
                NetworkInterface intf = en.nextElement();
                for (Enumeration<InetAddress> enumIpAddr = intf.getInetAddresses(); enumIpAddr.hasMoreElements();) {
                    InetAddress inetAddress = enumIpAddr.nextElement();
                    if (!inetAddress.isLoopbackAddress() && !inetAddress.isLinkLocalAddress()) {
                        return inetAddress.getHostAddress().toString();
                    }            }        }    }
        catch (SocketException ex) {
            Log.e("WifiPreferenceIpAddress", ex.toString());  }
        return null;}
    class ServerThread extends Thread {
        public void run() {

            try {
                PORT = 8888;
                server = new ServerSocket(PORT);
                ip = getLocalIpAddress();
            } catch (IOException e1) {
                e1.printStackTrace();        }
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    text.setText("Server: waiting for connection.\nip: "+ ip);
                }
            });
            while(flag) {
                try {
                    client = server.accept();


                } catch (IOException e) {
                    e.printStackTrace();    }
                Thread service = new Service(client);
                service.start();
                flag = false;
            }

        }
    }
    class Service extends Thread {
        private Socket socket;
        private String msg ="";
        public Service(Socket socket) {
            this.socket = socket;
        }

        public void run() {

            while(socket != null) {
                if(socket.isClosed())
                {
                    break;
                }
                try {
                    Message m = new Message();
                    BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream(), "UTF-8"));
                    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));

                    if((msg = in.readLine() )!= null){

                        if(msg.contains("forward"))
                        {
                            float x = (float)(0.3);
                            float y = (float) (0);
                            float th = (float) (0);
                            mRobotAPI.motion.moveBody(x, y, th);
                            msg = "";
                        }
                        else if(msg.contains("good"))
                        {
                            mRobotAPI.robot.speak("早安", 1 );
                            msg = "";
                        }

                    }
                    else
                    {
                        break;
                    }

                } catch(IOException e) {

                    e.printStackTrace();
                    try {
                        socket.close();
                    } catch (IOException ex) {
                        ex.printStackTrace();
                    }

                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                        }
                    });
                    break;}       }
        }

    }
    View.OnClickListener startOnclick = new View.OnClickListener() {
        @Override
        public void onClick(View v) {
            flag = true;
            ServerThread sthread = new ServerThread();
            sthread.start();
        }
    };
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mRobotAPI  = new RobotAPI(getApplicationContext());
        setContentView(R.layout.activity_main);
        text = findViewById(R.id.text);
        btn_start = findViewById(R.id.btn_start);
        btn_close = findViewById(R.id.btn_close);
        btn_start.setOnClickListener(startOnclick);

    }
}
