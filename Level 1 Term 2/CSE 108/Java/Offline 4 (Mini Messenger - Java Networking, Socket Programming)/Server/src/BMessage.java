import java.io.IOException;

public class BMessage {

    String msg;

    public String getMsg() {
        return msg;
    }

    public void setMsg(String msg) {
        this.msg = msg;
    }

    public void broadcast(WorkerThread cur) throws IOException {

        for(WorkerThread w:Main.track)
        {

            if(w.getUserName().equals(cur.getUserName()))
            {
                String temp = "You have Successfully send the message\n\n";
                w.dos.writeUTF(temp);
            }
            else
            {
                w.dos.writeUTF(msg);
            }
        }
    }
}
