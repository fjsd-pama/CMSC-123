import java.io.*;

/**
 * Created by Jose Arniel J. Pama on 12/10/2016.
 */
public class OutputWriter implements Serializable{
    public static final String opfile = "mp4.out";
    protected boolean istoscreen;

    public OutputWriter(boolean istoscreen){
        this.istoscreen = istoscreen;
    }

    public void setIstoscreen(boolean istoscreen){
        this.istoscreen = istoscreen;
    }

    public void write(String towrite){
        try{
            File file = new File(opfile);
            BufferedWriter bw = new BufferedWriter(new FileWriter(file, true));
            bw.write(towrite);
            bw.newLine();

            if(istoscreen==true){
                System.out.println(towrite);
            }
            bw.close();
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}
