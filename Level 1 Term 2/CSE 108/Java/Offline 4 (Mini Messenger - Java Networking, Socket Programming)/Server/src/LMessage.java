import java.io.*;
import java.net.Socket;
import java.util.Scanner;
import java.util.StringTokenizer;

public class LMessage {

    String UserName;
    String pass;
    String type;

    public String getUserName() {
        return UserName;
    }

    public void setUserName(String userName) {
        UserName = userName;
    }

    public String getPass() {
        return pass;
    }

    public void setPass(String pass) {
        this.pass = pass;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public static String[][] log_ara = new String[6][4];

    public LMessage() throws IOException {

        try {
            FileReader file = new FileReader("src\\User.txt");
            Scanner scanner = new Scanner(file);

            int ix=0;
            int cnt=0;
            while (scanner.hasNextLine()) {

                String str = scanner.nextLine();
                StringTokenizer st1 = new StringTokenizer(str,"##");
                while(st1.hasMoreTokens())
                {
                    log_ara[ix][cnt++]=st1.nextToken();
                }

                if(cnt==3)
                {
                    cnt=0;
                    ix++;
                }
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    public int Login() throws IOException {

        BufferedWriter bw = new BufferedWriter(new FileWriter("src\\LoggedUser.txt",true));

        String success="HOY NAY";

        for(int i=0;i<6;i++)
        {
            if(log_ara[i][0].equals(UserName) && log_ara[i][1].equals(pass) && log_ara[i][2].equals(type))
            {

                if(log_ara[i][3]==null)
                {
                    success="LOGIN SUCCESSFUL";
                    String temp = log_ara[i][0];
                    log_ara[i][3]="hoise";
                    bw.write(temp+"\n");
                    bw.flush();
                    bw.close();
                    return 1;
                }
                else
                {
                    success="YOU ARE ALREADY LOGGED IN";
                }
                break;
            }
        }
        if(success.equals("HOY NAY"))
            return 0;
        else
            return -1;

    }
}
