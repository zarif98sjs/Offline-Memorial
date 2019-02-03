import java.io.*;

public class CMessage {

    String receiver;
    String msg;
    String file_name;

    public String getReceiver() {
        return receiver;
    }

    public void setReceiver(String receiver) {
        this.receiver = receiver;
    }

    public String getMsg() {
        return msg;
    }

    public void setMsg(String msg) {
        this.msg = msg;
    }

    public String getFile_name() {
        return file_name;
    }

    public void setFile_name(String file_name) {
        this.file_name = file_name;
    }

    public void receive_file(DataInputStream dis,String file_size)
    {
        try
        {
            int filesize = Integer.parseInt(file_size);
            byte[] contents = new byte[10000];

            if(filesize!=0)
            {
                FileOutputStream fos = new FileOutputStream(file_name);
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


    public void send(WorkerThread cur) throws IOException {

        boolean user_found = false;

        for(WorkerThread w:Main.track)
        {

            if(w.getUserName().equals(receiver))
            {
                if(w.isLoggedin()==true)
                {
                    user_found = true;

                    String temp;
                    File file = new File(file_name);
                    FileInputStream fis = null;
                    try {
                        fis = new FileInputStream(file);
                        cur.dos.writeUTF("Message and File sent successfully to "+w.getUserName()+"##");
                        cur.dos.flush();
                    } catch (FileNotFoundException e) {
                        //e.printStackTrace();
                        if(file_name=="null")
                        {
                            temp=cur.getUserName() + ": " +msg+'\n';
                            w.dos.writeUTF(temp);
                            w.dos.flush();
                            cur.dos.writeUTF("Message sent to "+w.getUserName()+'\n');
                            cur.dos.flush();
                            //System.out.println("hereeeee");
                        }
                        else
                        {
                            cur.dos.writeUTF("File not found. "+"Message sent to "+w.getUserName()+"##");
                            cur.dos.flush();
                        }

                    }
                    BufferedInputStream bis = new BufferedInputStream(fis);
                    OutputStream os = cur.getConnectionSocket().getOutputStream();
                    byte[] contents;
                    long fileLength = file.length();

                    if(file_name!="null")
                    {
                        temp= cur.getUserName() + ": " +msg + "##" + "DL" + "##" + file_name + "##" + String.valueOf(fileLength) + '\n';
                        w.dos.writeUTF(temp);

                        w.dos.flush();

                        long current = 0;

                        while(current!=fileLength){
                            int size = 10000;
                            if(fileLength - current >= size)
                                current += size;
                            else{
                                size = (int)(fileLength - current);
                                current = fileLength;
                            }
                            contents = new byte[size];
                            bis.read(contents, 0, size);
                            w.dos.write(contents);
                        }
                        os.flush();

                    }
                }

                break;
            }
        }

        if(user_found==false)
        {
            cur.dos.writeUTF("The Reciever is not looged in the Server\n");
            cur.dos.flush();
        }

    }

}
