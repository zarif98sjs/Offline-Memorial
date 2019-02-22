import java.io.*;
import java.net.*;
import java.util.StringTokenizer;
import java.util.Vector;

public class Main {

    static Vector<WorkerThread> track = new Vector<>();
    public static int workerThreadCount = 0;

    public static void main(String argv[]) throws Exception {

        FileWriter fww = new FileWriter("src/LoggedUser.txt");
        fww.close();


        ServerSocket welcomeSocket = new ServerSocket(6788);
        int id = 1;
        while (true) {
            Socket connectionSocket = welcomeSocket.accept();

            DataInputStream dis = new DataInputStream(connectionSocket.getInputStream());
            DataOutputStream dos = new DataOutputStream(connectionSocket.getOutputStream());

            WorkerThread wt = new WorkerThread(connectionSocket, id, dis, dos);
            Thread t = new Thread(wt);
            track.add(wt);
            t.start();
            workerThreadCount++;
            System.out.println("Client [" + id + "] is now connected. No. of worker threads = " + workerThreadCount);
            id++;
        }
    }
}

class WorkerThread implements Runnable {
    private Socket connectionSocket;
    private int id = 0;
    private String UserName;
    private boolean isLoggedin;
    private boolean isAdmin;
    final DataInputStream dis;
    final DataOutputStream dos;

    public String getUserName() {
        return UserName;
    }
    public void setUserName(String userName) {
        UserName = userName;
    }

    public boolean isLoggedin() {
        return isLoggedin;
    }

    public void setLoggedin(boolean loggedin) {
        isLoggedin = loggedin;
    }

    public Socket getConnectionSocket() {
        return connectionSocket;
    }

    public void setConnectionSocket(Socket connectionSocket) {
        this.connectionSocket = connectionSocket;
    }

    public WorkerThread(Socket s, int id, DataInputStream dis, DataOutputStream dos) {
        this.connectionSocket = s;
        this.id = id;
        this.dis = dis;
        this.dos = dos;
        this.isLoggedin = false;
        this.isAdmin = false;
    }

    public void run() {

        LMessage lm = null;
        SMessage sm = null;
        BMessage bm = new BMessage();
        CMessage cm = new CMessage();

        try {
            sm= new SMessage();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        try {
            lm = new LMessage();
        } catch (IOException e) {
            e.printStackTrace();
        }
        while (true) {
            String textFromClient;
            String textFromServer;
            String c_msg=null;
            try {
                textFromClient = dis.readUTF();
                StringTokenizer st1 = new StringTokenizer(textFromClient,"##|\\\n");
                String[] check_ara = new String[10];
                int cnt=0;
                while(st1.hasMoreTokens())
                {
                    check_ara[cnt++]=st1.nextToken();
                }
                String ta=check_ara[1];
                String tb=check_ara[2];
                String tc=check_ara[3];
                String td=check_ara[4];
                if(check_ara[0].equals("L"))
                {
                    lm.setUserName(ta);
                    lm.setPass(tb);
                    lm.setType(tc);

                    int val = lm.Login();
                    if(val==1)
                    {
                        textFromServer = "Login Successful" + "##" + ta + '\n';
                        UserName=ta;
                        isLoggedin=true;
                        if(tc.equals("admin"))
                            isAdmin=true;
                    }
                    else if(isLoggedin==true)
                    {
                        textFromServer = "YOU ARE ALREDY LOGGED IN" + '\n';
                    }
                    else
                    {
                        textFromServer = "Authentication Error" + '\n';
                    }

                    dos.writeUTF(textFromServer);
                    dos.flush();
                }
                else if(check_ara[0].equals("S") && isLoggedin==true)
                {
                    textFromServer = check_ara[2] + "##"+check_ara[1] + '\n';
                    if(check_ara[1].equals("logout"))
                    {
                        sm.setMsg(check_ara[2]);
                        sm.logout(UserName);

                        isLoggedin=false;

                        dos.writeUTF(textFromServer);
                        dos.flush();

                    }
                    if(check_ara[1].equals("show"))
                    {
                        sm.setMsg(check_ara[2]);
                        sm.show(this);

                    }
                }
                else if(check_ara[0].equals("B") && isLoggedin==true)
                {
                    if(isAdmin==true)
                    {
                        String br_msg = this.UserName +": " + check_ara[1]+'\n';
                        bm.setMsg(br_msg);
                        bm.broadcast(this);
                    }
                    else
                    {
                        String msg = "You are not admin. Your message can't be send to other clients\n\n";
                        this.dos.writeUTF(msg);
                    }
                }
                else if(check_ara[0].equals("C") && isLoggedin==true)
                {
                    String reciever = check_ara[1];
                    c_msg = check_ara[2];
                    String file_name = check_ara[3];
                    String file_size = check_ara[4];

                    if(file_name==null)
                        file_name="null";
                    cm.setReceiver(reciever);
                    cm.setMsg(c_msg);
                    cm.setFile_name(file_name);
                    cm.receive_file(dis,file_size);
                    cm.send(this);
                }

            } catch (Exception e) {
                //System.out.println("noooooooooooooo");
            }
        }

    }
}