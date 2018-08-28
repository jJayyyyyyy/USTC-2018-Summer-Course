package server;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

public class MySocketServer {
	private String host = "127.0.0.1";
	private int port = 8888;
	public ServerSocket serverSocket;
	
	public MySocketServer() {
		try {
			serverSocket = new ServerSocket(port, 5, InetAddress.getByName(host));
			serverSocket.setReuseAddress(true);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
		MySocketServer mySocketServer = new MySocketServer();
		mySocketServer.serve();
		mySocketServer.close();
	}

	private void serve() {
		try {
			System.out.println("server opened --- ");

			Socket clientsocket = serverSocket.accept();
			for( int i = 0; i < 5; i++ ) {
				String msg = readFromSocket(clientsocket);
				System.out.printf("msg received: %s\n", msg);
				
				msg = msg.toUpperCase() + "\n";;
				System.out.printf("msg to be sent: %s", msg);
				sendResponse(clientsocket, msg);
				
				System.out.println("\n\n\n");
			}
			clientsocket.close();
			System.out.println("server closed --- ");
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private String readFromSocket(Socket clientsocket) {
		String msg = "";
		try {
			InputStream is = clientsocket.getInputStream();
			InputStreamReader isReader = new InputStreamReader(is);
			BufferedReader bufReader = new BufferedReader(isReader);
			
			String line = "";
			line = bufReader.readLine();
			msg += line;
		} catch (Exception e) {
			e.printStackTrace();
		}
		return msg;
	}
	
	private void sendResponse(Socket clientsocket, String msg) {
		try {
			byte[] byteMsg = msg.getBytes();
			OutputStream os = clientsocket.getOutputStream();
			os.write(byteMsg);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void close() {
		try {
			serverSocket.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}	
}
