package sample;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;

import java.io.*;
import java.net.Socket;
import java.net.URL;
import java.util.ResourceBundle;
import java.util.StringTokenizer;

public class Controller implements Initializable {

    public static String UserName;
    private String textToServer;
    private String file_name;
    private long file_size;
    private File file = null;

    private Socket clientSocket=null;
    private DataInputStream dis=null;
    private DataOutputStream dos=null;

    @FXML private TextArea ta;

    @FXML private Button lbtn;
    @FXML private Button sbtn;
    @FXML private Button bbtn;
    @FXML private Button cbtn;

    @FXML private TextField l1;
    @FXML private PasswordField l2;
    @FXML private TextField l3;
    @FXML private TextField s1;
    @FXML private TextField s2;
    @FXML private TextField b1;
    @FXML private TextField c1;
    @FXML private TextField c2;
    @FXML private TextField c3;

    String[] check_ara = new String[10];

    public Controller() throws IOException {

    }
    @Override
    public void initialize(URL location, ResourceBundle resources) {

        try{
            clientSocket = new Socket("localhost", 6788);
            dis = new DataInputStream(clientSocket.getInputStream());
            dos = new DataOutputStream(clientSocket.getOutputStream());
        }catch(Exception e){
            System.out.println("Problem in connecting server, Exiting Main");
            System.exit(1);
        }

        lbtn.setOnAction(event -> {

            textToServer = "L"+"##"+l1.getText()+"##"+l2.getText()+"##"+l3.getText();

            try {
                dos.writeUTF(textToServer);
            } catch (IOException e) {
                e.printStackTrace();
            }

        });

        sbtn.setOnAction(event -> {
            textToServer = "S"+"##"+s1.getText()+"##"+s2.getText();
            try {
                dos.writeUTF(textToServer);
            } catch (IOException e) {
                e.printStackTrace();
            }
        });

        bbtn.setOnAction(event -> {
            textToServer = "B"+"##"+b1.getText();
            try {
                dos.writeUTF(textToServer);
            } catch (IOException e) {
                e.printStackTrace();
            }
        });

        cbtn.setOnAction(event -> {

            file_name = c3.getText();
            file = new File(file_name);
            file_size = file.length();

            textToServer = "C"+"##"+c1.getText()+"##"+c2.getText()+"##"+c3.getText()+"##"+file_size;
            send_file();
        });

        Thread listenFromServer = new Thread(new Runnable() {
            @Override
            public void run() {

                while (true)
                {
                    try {
                        String modif = dis.readUTF();
                        check_ara[1]="qq";

                        StringTokenizer st1 = new StringTokenizer(modif,"##|\\\n");
                        int cnt=0;
                        while(st1.hasMoreTokens())
                        {
                            String temp = st1.nextToken();
                            check_ara[cnt++]=temp;
                        }
                        String t1 = check_ara[0];
                        String t2 = check_ara[1];
                        String t3 = check_ara[2];
                        String t4 = check_ara[3];
                        String temp = "Message : " + t1+'\n';

                        if(!t2.equals("logout"))
                            ta.appendText(temp);
                        if(t1.equals("Login Successful"))
                        {
                            UserName=t2;
                            //System.out.println(UserName);
                            ta.appendText("Welcome "+UserName+'\n'+'\n');
                        }
                        if(t1.equals("Showing..."))
                        {
                            t2=t2.replaceAll(",","\n");
                            ta.appendText("Already logged users :\n");
                            ta.appendText(t2+"\n");
                        }
                        if(t2.equals("logout"))
                        {
                            System.out.println("Client Logged Out. Exiting...\n");
                            System.exit(1);
                        }
                        if(t2.equals("DL"))
                        {
                            download_file(t4,t3);
                        }
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }

            }
        });

        listenFromServer.start();
    }

    public void send_file()
    {
        try {
            dos.writeUTF(textToServer);
            String temp;
            FileInputStream fis = null;
            try {
                fis = new FileInputStream(file);
            } catch (FileNotFoundException e) {
                //e.printStackTrace();
            }
            BufferedInputStream bis = new BufferedInputStream(fis);
            OutputStream os = clientSocket.getOutputStream();
            byte[] contents;

            if(file_name!="null")
            {
                long current = 0;

                while(current!=file_size){
                    int size = 10000;
                    if(file_size - current >= size)
                        current += size;
                    else{
                        size = (int)(file_size - current);
                        current = file_size;
                    }
                    contents = new byte[size];
                    bis.read(contents, 0, size);
                    dos.write(contents);
                }
                os.flush();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void download_file(String str,String name)
    {
        try
        {
            int filesize = Integer.parseInt(str);
            byte[] contents = new byte[10000];

            if(filesize!=0)
            {
                FileOutputStream fos = new FileOutputStream("new_downloaded "+name);
                BufferedOutputStream bos = new BufferedOutputStream(fos);

                int bytesRead = 0;
                int total=0;

                while(total!=filesize)
                {
                    bytesRead=dis.read(contents);
                    total+=bytesRead;
                    bos.write(contents, 0, bytesRead);
                }
                bos.flush();
            }
        }
        catch(Exception e)
        {
            System.err.println("Could not transfer file.");
        }
    }
}