// package tcpsocket;

//
import java.io.*;
import java.net.*;

class TCPServer {

    public static void main (String args[]) throws Exception {
				
        	 ServerSocket serverSocket = new ServerSocket(9000);
		 // waits for a new connection. Accepts connetion from multiple clients
		 while (true) 
		 {
			 System.out.println("Esperando conexão na porta 9000");
                 	 Socket s = serverSocket.accept();
			 System.out.println("Conexão estabelecida de " + s.getInetAddress());
			 
			 // create a BufferedReader object to read strings from
			 // the socket. (read strings FROM CLIENT)
			 BufferedReader br = new BufferedReader(new InputStreamReader(s.getInputStream()));
			 String input = br.readLine();
			 
			 //create output stream to write to/send TO CLINET
                         DataOutputStream output = new DataOutputStream(s.getOutputStream());
			 
			 output.writeBytes(input.toUpperCase() + "\n");
			 // close current connection
			 s.close();
		 }
    }
}
