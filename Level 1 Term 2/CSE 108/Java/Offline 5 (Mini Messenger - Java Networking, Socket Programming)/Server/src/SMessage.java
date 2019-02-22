import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class SMessage {

    String msg;

    public String getMsg() {
        return msg;
    }

    public void setMsg(String msg) {
        this.msg = msg;
    }

    public String[][] ara = new String[6][2];

    public void init() throws FileNotFoundException {
        FileReader fr = null;
        fr = new FileReader("src\\LoggedUser.txt");
        Scanner scanner = new Scanner(fr);

        int ix = 0;

        while (scanner.hasNextLine()) {
            ara[ix][0] = scanner.nextLine();
            ara[ix][1] = "logged";
            ix++;
        }

    }

    public SMessage() throws FileNotFoundException {

        init();
    }


    public void logout(String UserName) throws IOException {

        init();


        int ix=0;
        while (ara[ix][0]!=null)
        {
            if(UserName.equals(ara[ix][0]))
            {
                ara[ix][1]="out";
                System.out.println("Message from "+UserName+" : "+msg);
                System.out.println(ara[ix][0] + " has logged out");
                break;
            }
            ix++;
        }

        for(int i=0;i<6;i++)
        {
            if(LMessage.log_ara[i][0].equals(UserName))
            {
                LMessage.log_ara[i][3]=null;
            }
        }

        FileWriter fw = new FileWriter("src\\LoggedUser.txt");

        for(int i=0;i<6;i++)
        {
            if(ara[i][1]=="logged")
            {
                fw.write(ara[i][0]+'\n');
                fw.flush();
            }
        }

        fw.close();

    }

    public void show(WorkerThread cur) throws IOException {
        FileReader fr = null;
        String temp = new String();
        try {
            fr = new FileReader("src\\LoggedUser.txt");
            Scanner scanner = new Scanner(fr);
            temp+=("Showing...##");
            while (scanner.hasNext()) {
                String str = scanner.next();
                temp+=(str+",");
                System.out.println(str);

            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        System.out.println("Message from "+cur.getUserName()+" : "+msg);

        cur.dos.writeUTF(temp);
        cur.dos.flush();
    }

}
