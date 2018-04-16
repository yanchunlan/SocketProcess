package com.example.yanchunlan.socketprocess;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        startService(new Intent(this, ProcessService.class));

    }

    /**
     * 客户端
     * 1.等待连接
     * 2.读取消息
     */
    private void SocketClient() {
        try {
            /**
             * 客户端
             * 1.等待连接
             * 2.读取消息
             */
            Socket socket = new Socket("192.168.1.115", 5209);
            // input
            InputStream inputStream = socket.getInputStream();
            BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
            String line = reader.readLine();
            System.out.print("line" + line);
            inputStream.close();

            //or write message
            OutputStream outputStream = socket.getOutputStream();
            outputStream.write("message".getBytes("UTF-8"));
            outputStream.close();

            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    /**
     * 服务端
     * 1. 创建ServerSocket对象并绑定监听端口
     * 2. 通过accept()方法监听客户端的请求
     * 3. 建立连接后，通过输入输出流读取客户端发生的请求信息
     * 4. 通过输入流向客户端发送请求信息
     * 5. 关闭连接
     */
    private void SocketServer() {
        try {
            /**
             * 服务端
             * 1. 创建ServerSocket对象并绑定监听端口
             * 2. 通过accept()方法监听客户端的请求
             * 3. 建立连接后，通过输入输出流读取客户端发生的请求信息
             * 4. 通过输入流向客户端发送请求信息
             * 5. 关闭连接
             */
            ServerSocket server = new ServerSocket(5209);
            Socket socket = server.accept();

            // input
            InputStream inputStream = socket.getInputStream();
            BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
            String line = reader.readLine();
            System.out.print("line" + line);

            inputStream.close();

            socket.close();
            server.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
