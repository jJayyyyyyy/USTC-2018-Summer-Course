package client;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.Socket;
import java.util.Scanner;

public class MySocketClient {
	private String host = "127.0.0.1";
	private int port = 8888;
	
	public MySocketClient() {		
	}
	
	public static void main(String[] args) {
		MySocketClient mySocketClient = new MySocketClient();
		mySocketClient.open();
	}

	private void open() {
		try {
			System.out.println("client opened --- ");
			Socket socket = new Socket(host, port);
			socket.setReuseAddress(true);
			
			Scanner in = new Scanner(System.in);
			for(int i = 0; i < 5; i++ ) {
				System.out.printf("msg to be sent: ");
				String msg = in.nextLine() + "\n";
				sendMsg(socket, msg);
				
				msg = readFromSocket(socket);
				System.out.printf("msg received: %s\n", msg);
				
				System.out.println("\n\n\n");
			}
			in.close();
			
			socket.close();
			System.out.println("client closed --- ");
		} catch (Exception e) {
		
		}
	}
	
	private void sendMsg(Socket socket, String msg) {
		try {
			byte[] byteMsg = msg.getBytes();
			OutputStream os = socket.getOutputStream();
			os.write(byteMsg);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	private String readFromSocket(Socket socket) {
		String msg = "";
		try {
			InputStream is = socket.getInputStream();
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
}
