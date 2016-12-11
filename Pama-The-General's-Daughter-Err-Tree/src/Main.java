import java.io.*;
import java.util.Scanner;

public class Main {
    private static final String gtfile = "MyGTFileNavigation.ser";
    private static final String opfile = "mp4.in";

    public static void main(String[] args){
        GTFileNavigation gfn = new GTFileNavigation();

        //DESERIALIZE
        FileInputStream fis = null;
        ObjectInputStream ois;
        try{
            File fin = new File(gtfile);
            if(fin.length()==0){
                /*//file is empty
                System.err.println("FILE IS EMPTY");*/
                fin.createNewFile();
            }

            fis = new FileInputStream(fin);
            ois = new ObjectInputStream(fis);
            gfn = (GTFileNavigation) ois.readObject();
            ois.close();
        }catch (IOException e){
            e.printStackTrace();
        }catch (ClassNotFoundException e){
            e.printStackTrace();
        }finally{
            try{
                fis.close();
            }catch (IOException e){
                e.printStackTrace();
            }
        }

        //reads inputs from mp4.in and do their corresponding operations
        BufferedReader br = null;
        try{
            String currline;

            br = new BufferedReader(new FileReader(opfile));

            while( (currline = br.readLine())!= null ){
                gfn.setOutputwriterIsToScreen(false);
                gfn.operate(currline);
            }
        }catch(IOException e){
            e.printStackTrace();
        }finally{
            try{
                if(br != null) br.close();
            }catch(IOException e){
                e.printStackTrace();
            }
        }

        //accepts input from user
        System.out.println("\n==FILE NAVIGATION PROTOTYPE==");
        System.out.println("You have the following options: ");
        System.out.println("\ndirectory commands...");
        System.out.println("    create a dir -> mkdir <directory name> ");
        System.out.println("    remove a dir -> rmdir <directory name> ");
        System.out.println("   display a dir -> ls ");
        System.out.println("  go to a subdir -> cd <directory name> ");
        System.out.println("  go to upperdir -> cd .. ");
        System.out.println("\nfile commands...");
        System.out.println("   create a file -> > <file name> ");
        System.out.println("     edit a file -> >> <file name> ");
        System.out.println("                 -> edit <file name> ");
        System.out.println("   remove file/s -> rm <file name> ");
        System.out.println("   rename a file -> rn <file name> <new filename> ");
        System.out.println("     copy a file -> cp <file name> <destination> ");
        System.out.println("     move a file -> mv <file name> <new directory> ");
        System.out.println("     show a file -> show <file name> ");
        System.out.println("      create dir -> mkdir <directory name> ");
        System.out.println("path of dir/file -> whereis <dir/file name> ");
        System.out.println("TO EXIT, ENTER: -123");
        Scanner sc = new Scanner(System.in);
        String scanned = "";

        while(true){
            System.out.print("Enter command: ");

            if( (scanned = sc.nextLine()).equals("-123") ){
                break;
            }
            gfn.setOutputwriterIsToScreen(true);
            gfn.operate(scanned);
        }

        //SERIALIZE
        FileOutputStream fos = null;
        ObjectOutputStream oos;
        try{
            File fout = new File(gtfile);
            fos = new FileOutputStream(fout);
            oos = new ObjectOutputStream(fos);
            oos.writeObject(gfn);
            oos.close();
        }catch (IOException e){
            e.printStackTrace();
        }finally{
            try{
                fos.close();
            }catch (IOException e){
                e.printStackTrace();
            }
        }
    }
}
