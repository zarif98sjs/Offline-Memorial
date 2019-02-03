package sample;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.collections.transformation.SortedList;
import javafx.fxml.FXML;

import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.shape.*;
import javafx.stage.FileChooser;
import org.omg.PortableInterceptor.INACTIVE;

import java.io.File;
import java.io.FileNotFoundException;
import java.nio.channels.FileChannel;
import java.util.Scanner;

public class Controller {

    @FXML
    private Button bt1;
    @FXML
    private TableView<WordCount> table;
    @FXML
    private TableColumn<WordCount,String> wordd;
    @FXML
    private TableColumn<WordCount, Integer> count;

    File f1;

    public void file_chooser() throws FileNotFoundException {
        FileChooser fc = new FileChooser();
        fc.getExtensionFilters().add(new FileChooser.ExtensionFilter("Text File","*.txt"));
        f1 = fc.showOpenDialog(null);
    }

    public void update_table() throws FileNotFoundException {
        if(f1!=null)
        {
            ObservableList<WordCount> list = FXCollections.observableArrayList();

            Scanner text_scanner = new Scanner(f1);
            text_scanner.useDelimiter("[^A-Za-z0-9]+");
            while (text_scanner.hasNext())
            {
                String word = text_scanner.next();
                word = word.toLowerCase();
                //System.out.println(word);

                list.add(new WordCount(word,1));
            }

            for(int i=0;i<list.size();i++)
            {
                //System.out.println(list.get(i).getWord());

                String tw1 = list.get(i).getWord();
                int tc1 = list.get(i).getCount();

                if(tc1==-1)
                    continue;

                for(int j=i+1;j<list.size();j++)
                {
                    String tw2 = list.get(j).getWord();

                    if(tw1.equals(tw2))
                    {
                        //System.out.println("DHUKSEEEEE");
                        tc1++;
                        list.set(i,new WordCount(tw1,tc1));
                        //System.out.println(tw1+"------"+tc1);
                        list.set(j,new WordCount(tw2,-1));
                    }
                }
            }

            ObservableList<WordCount> final_list = FXCollections.observableArrayList();

            for(int i=0;i<list.size();i++)
            {
                String tw1 = list.get(i).getWord();
                int tc1 = list.get(i).getCount();

                if(tc1!=-1)
                {
                    final_list.add(list.get(i));
                    //System.out.println(list.get(i));
                }
            }

            wordd.setCellValueFactory(new PropertyValueFactory<WordCount,String>("Word"));
            count.setCellValueFactory(new PropertyValueFactory<WordCount,Integer>("Count"));
            table.setItems(final_list);

        }

        else
        {
            System.out.println("File is not valid");

        }

    }


}
