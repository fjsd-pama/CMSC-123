import java.io.Serializable;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * Created by Jose Arniel J. Pama on 12/9/2016.
 */
public class FileDescriptor implements Serializable {
    protected String name;
    protected boolean isdir;
    protected String datecreated;
    public String content;
    protected boolean ismodified;
    protected String datemodified;

    public FileDescriptor(){
        name = "";
        datecreated = "";
        datemodified = "";
        content = "";
    }

    public FileDescriptor(String name){
        this(name, false); //set isdir as false by default
    }

    public FileDescriptor(String name, boolean isdir){
        this.name = name;
        this.isdir = isdir;
        this.ismodified = false;
        //for setting the time and date this file is created
        Date date = new Date();
        SimpleDateFormat sdf = new SimpleDateFormat("E yyyy.MM.dd 'at' hh:mm:ss a zzz");

        datecreated = sdf.format(date);
    }

    public void modifydate(){
        Date date = new Date();
        SimpleDateFormat sdf = new SimpleDateFormat("E yyyy.MM.dd 'at' hh:mm:ss a zzz");
        datemodified = sdf.format(date);
        this.ismodified = true;
    }

    public String toString(){
        String res = "";
        if(isdir==true){
            res += "Dir: ";
        } else{
            res += "File: ";
        }

        res += name + "\n";
        res += "\t\tDate Created: " + datecreated;

        if(ismodified==true){
            res += "\n\t\tDate Modified: " + datemodified;
        }
        return res;
    }
}
