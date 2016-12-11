import java.io.Serializable;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * Created by Jose Arniel J. Pama on 12/9/2016.
 * Disclaimer: This file navigation system does not provide allowance for relative and absolute paths.
 * It doesn't not allow something like: mkdir cmsc/cmsc11. It only allows the user to create/edit/remove/rename/move
 * files or directories in the current directory.
 */
public class GTFileNavigation implements Serializable{
    private GeneralTree files;
    private GTNode currentdir;
    private OutputWriter outputwriter = new OutputWriter(false);

    GTFileNavigation(){
        this("root");
    }

    GTFileNavigation(String rootname){
        files = new GeneralTree();
        FileDescriptor root = new FileDescriptor(rootname, true);
        files.insert(root, "");
        currentdir = files.getroot();
    }

    public void setOutputwriterIsToScreen(boolean isToScreen){
        outputwriter.setIstoscreen(isToScreen);
    }

    //does the operation when reading from a file or accepting user input
    public void operate(String op){
        String[] words = op.split(" ");
        if((words.length == 2)){
            String firstcmd = words[0];
            if(firstcmd.contains("mkdir")){
                makedir(words[1]);
            }else if(firstcmd.contains("rmdir")){
                removeDir(words[1]);
            }else if(firstcmd.contains("ls")){
                if(words[1].contains("*")){
                    //int find = words[1].indexOf("*");
                    displayCurrentDir(words[1]);
                }else{
                    String st = '"' + op + '"' + " :syntax is invalid";
                    outputwriter.write(st);
                }
            }else if(firstcmd.contains("cd")){
                if(words[1].compareTo("..")==0){
                    gotoUpperDir();
                }else{
                    changedir(words[1]);
                }
            }else if(firstcmd.contains(">>")){
                editfile(words[1], false);
            }else if(firstcmd.contains(">")){
                createfile(words[1]);
            }else if(firstcmd.contains("edit")){
                editfile(words[1], false);
            }else if(firstcmd.contains("rm")){
                deletefile(words[1]);
            }else if(firstcmd.contains("show")){
                showcontent(words[1]);
            }else if(firstcmd.contains("whereis")){
                whereis(words[1]);
            }else{
                String st = '"' + op + '"' + " :syntax is invalid";
                outputwriter.write(st);
            }
        }else if(words.length==3){
            String firstcmd = words[0];
            if(firstcmd.contains("rn")){
                renamefile(words[1], words[2]);
            }else if(firstcmd.contains("mv")){
                movefile(words[1], words[2]);
            }else if(firstcmd.contains("cp")){
                copyfile(words[1], words[2]);
            }else{
                String st = '"' + op + '"' + " :syntax is invalid";
                outputwriter.write(st);
            }
        }else{
            if(words[0].contains("ls")){
                if(words.length==1){
                    displayCurrentDir("");
                }
            }else{
                String st = '"' + op + '"' + " :syntax is invalid";
                outputwriter.write(st);
            }
        }
    }

    //checks if a file name has invalid characters
    public boolean hasInvalidChars(String name){
        char[] chArr = name.toCharArray();
        for(char ch: chArr){
            if( (ch == '/') || (ch == '\\') || (ch == '*') || (ch == ':') || (ch == '?')){
                return true;
            }
            if( (ch == '"') || (ch == '<') || (ch == '>') || (ch == '|')){
                return true;
            }
        }
        return false;
    }

    //make a directory under the current directory
    public void makedir(String name){
        if( hasInvalidChars(name) ){
            String st = "mkdir: " + name + " has invalid syntax";
            outputwriter.write(st);
        } else{
            FileDescriptor dirToAdd = new FileDescriptor(name, true);
            boolean res;

            currentdir.setOutputwriterIsToScreen(outputwriter.istoscreen);
            res = currentdir.addchild(dirToAdd);
            if(res==true){
                String st = "mkdir: " + dirToAdd.name + " was added.";
                outputwriter.write(st);
            }else{
                String st = "mkdir: " + dirToAdd.name + " was not successfully added.";
                outputwriter.write(st);
            }
        }
    }
    //make sure this command doesn't apply to files
    public void removeDir(String name){
        GTNode toremove = currentdir.searchchild(name);
        boolean res = false;
        if(toremove!=null){
            if(toremove.item.isdir==true){
                currentdir.setOutputwriterIsToScreen(outputwriter.istoscreen);
                res = currentdir.removechild(name);

                if(res==true){
                    String st = "rmdir: " + name + " was removed.";
                    outputwriter.write(st);
                }else{
                    String st = "rmdir: " + name + ": there is no such directory.";
                    outputwriter.write(st);
                }
            }else{
                String st = "rmdir: cannot remove, " + name + " is a file";
                outputwriter.write(st);
            }
        }
    }
    public void changedir(String newdir){
        if(hasInvalidChars(newdir)){
            outputwriter.write("cd: " + newdir + " has invalid syntax");
        }
        currentdir.setOutputwriterIsToScreen(outputwriter.istoscreen);
        GTNode res = currentdir.searchchild(newdir);
        if(res!=null){
            //make sure res gtnode is a directory, not a file
            if(res.item.isdir==true){
                currentdir = res;
                String st = "cd: " + newdir + " is the current directory.";
                outputwriter.write(st);
            }else{
                String st = "cd: " + newdir + " is a file, cannot go there";
                outputwriter.write(st);
            }
        }else{
            String st = "cd: " + newdir + ": there is no such directory in " + currentdir.item.name;
            outputwriter.write(st);
        }
    }
    public void gotoUpperDir(){
        if(currentdir.parent!=null){
            currentdir = currentdir.parent;
            String st = "cd ..: " + currentdir.item.name + " is the  current directory.";
            outputwriter.write(st);
        }else{
            String st = "cd ..: no further upper directories!\n" + "\t" + currentdir.item.name + " is still the  current directory.";
            outputwriter.write(st);
        }
    }

    public void createfile(String name){
        if( hasInvalidChars(name) ){
            String st = "> : " + name + " has invalid syntax";
            outputwriter.write(st);
        }else{
            FileDescriptor dirToAdd = new FileDescriptor(name, false);
            boolean res;

            currentdir.setOutputwriterIsToScreen(outputwriter.istoscreen);
            res = currentdir.addchild(dirToAdd);
            if(res==true){
                String st = "> : " + dirToAdd.name + " was added.";
                outputwriter.write(st);
                editfile(name, true);
            }else{
                String st = "> : " + dirToAdd.name + " was not successfully added.";
                outputwriter.write(st);
            }
        }
    }
    //edits a file, and modify the time modified after edit
    public void editfile(String name, boolean isnew){
        currentdir.setOutputwriterIsToScreen(outputwriter.istoscreen);
        GTNode res = currentdir.searchchild(name);
        if(res!=null){
            //make sure res gtnode is a file, not a directory
            if(res.item.isdir==false){
                String appendtocontent = "";
                String content = "";
                String st = "You are currently editing the content of " + res.item.name + "...\n";
                st += "\tType anything.\n";
                st += "\tPress ENTER, and type exit code 's@v3' to save.";
                System.out.println(st);

                if(isnew==false){
                    content = res.item.content;
                    System.out.println(content);
                }

                Scanner sc = new Scanner(System.in);

                while( sc.hasNextLine() ){
                    appendtocontent += sc.nextLine();

                    if((appendtocontent).contains("s@v3")==true){
                        break;
                    }
                }

                if(isnew==false){
                    res.item.modifydate();
                }

                int lastIndex = appendtocontent.indexOf("s@v3");
                res.item.content = content + appendtocontent.substring(0, lastIndex);

                System.out.println("Done editing!");
                outputwriter.write(res.item.toString());
            }else{
                String st = name + " is a directory, cannot go there";
                outputwriter.write(st);
            }
        }else{
            createfile(name);
        }
    }
    public void deletefile(String name){
        currentdir.setOutputwriterIsToScreen(outputwriter.istoscreen);
        GTNode toremove = currentdir.searchchild(name);
        boolean res = false;
        if(toremove!=null){
            if(toremove.item.isdir==false){
                currentdir.setOutputwriterIsToScreen(outputwriter.istoscreen);
                res = currentdir.removechild(name);

                if(res==true){
                    String st = "rm: " + name + " was removed.";
                    outputwriter.write(st);
                }else{
                    String st = "rm: " + name + ": there is no such file.";
                    outputwriter.write(st);
                }
            }else{
                String st = "rm: cannot remove, " + name + " is a directory";
                outputwriter.write(st);
            }
        }
    }
    public void movefile(String name, String dest){
        currentdir.setOutputwriterIsToScreen(outputwriter.istoscreen);
        GTNode res = currentdir.searchchild(dest);
        if(res==null){
            renamefile(name, dest); //if destination is nonexistent, simply rename the directory
        }else{
            //make sure your destination is a directory
            if(res.item.isdir==true){
                res.setOutputwriterIsToScreen(outputwriter.istoscreen);
                GTNode ftm = res.searchchild(name);

                res.setOutputwriterIsToScreen(outputwriter.istoscreen);
                //if fileToMove already exists in the destination, delete the file there and replace
                if(ftm!=null){
                    res.removechild(name);
                }

                GTNode fileToMove = currentdir.searchchild(name);
                if(fileToMove!=null){
                    res.addchild(fileToMove);
                    currentdir.removechild(name);
                    outputwriter.write("mv: " + name +" has been moved to " + dest);
                }else{
                    outputwriter.write("mv: " + name +" :no such directory");
                }
            }else{
                outputwriter.write("mv: cannot move" + name +", " + dest + " is a file");
            }
        }
    }
    public void renamefile(String name, String newname){
        if( hasInvalidChars(newname) ){
            String st = "rn: " + newname + " has invalid syntax";
            outputwriter.write(st);
        }else {
            currentdir.setOutputwriterIsToScreen(outputwriter.istoscreen);
            GTNode res = currentdir.searchchild(name);
            GTNode nn = currentdir.searchchild(newname);
            if (nn == null) {
                if (res != null) {
                    String st = "rn: " + res.item.name + " has been renamed to " + newname;
                    outputwriter.write(st);
                    res.item.name = newname;
                } else {
                    String st = "rn: " + name + ": there is no such file/directory.";
                    outputwriter.write(st);
                }
            } else {
                String st = "rn: " + newname + ": name already exists in the directory";
                outputwriter.write(st);
            }
        }
    }
    public void copyfile(String name, String copytoname){
        if( hasInvalidChars(copytoname) ){
            outputwriter.write("cp: " + copytoname + " has invalid syntax");
            return;
        }

        currentdir.setOutputwriterIsToScreen(outputwriter.istoscreen);
        GTNode orig = currentdir.searchchild(name);
        GTNode copy = currentdir.searchchild(copytoname);

        if(orig!=null){
            if(copy==null){
                FileDescriptor cf = new FileDescriptor(copytoname, orig.item.isdir);
                cf.datecreated = orig.item.datecreated;
                cf.content = orig.item.content;
                cf.ismodified = orig.item.ismodified;
                cf.datemodified = orig.item.datemodified;
                copy = new GTNode(cf);
                copy.setChildren(orig.children);

                currentdir.setOutputwriterIsToScreen(outputwriter.istoscreen);
                boolean res = currentdir.addchild(copy);
                if(res==true){
                    outputwriter.write("cp: we have created a new file " + "'" + copytoname +"'" + " and have copied " + name + " successfully");
                }
            }else{
                copy.item.datecreated = orig.item.datecreated;
                copy.item.content = orig.item.content;
                copy.item.ismodified = orig.item.ismodified;
                copy.item.datemodified = orig.item.datemodified;
                for(int i = 0; i < orig.children.size(); i++){
                    boolean res = copy.addchild(orig.children.get(i));
                    if(res==false){
                        outputwriter.write("cp: some contents of " + name + " already exist in " + copytoname);
                        return;
                    }
                }
                outputwriter.write("cp: contents of " + name + " has been copied to " + copytoname);
            }
        }else{
            outputwriter.write("cp: " + name + ": there is no such file/directory.");
        }
    }
    //applicable for a directory only, not files
    //accepts "" or strings like "*.doc", these are strings typed after the ls command
    public void displayCurrentDir(String wildcardcmd){
        //wildcarcmd accepts "" for ls command alone without regex strings
        if(wildcardcmd==""){
            currentdir.setOutputwriterIsToScreen(outputwriter.istoscreen);
            currentdir.displaychildren();
        }else{
            int len = wildcardcmd.length();
            if(len > 1 && wildcardcmd.charAt(0)=='*'){
                wildcardcmd = wildcardcmd.substring(1, len);
                files.outputwriter.setIstoscreen(outputwriter.istoscreen);
                files.displaytree(currentdir, wildcardcmd);
            }else{
                outputwriter.write("ls: command " + wildcardcmd + " is invalid");
            }
        }
    }
    //applicable only for files
    public void showcontent(String name){
        currentdir.setOutputwriterIsToScreen(outputwriter.istoscreen);
        GTNode res = currentdir.searchchild(name);
        if(res!=null){
            //make sure that it is a file
            if(res.item.isdir==false){
                outputwriter.write("show: " + name + "\nCONTENT: ");
                outputwriter.write(res.item.content);
            }else{
                outputwriter.write("show: " + res.item.name + " is a directory, cannot show content");
            }
        }else{
            outputwriter.write("show: " + name + ": there is no such file.");
        }
    }

    public void whereis(String name){
        //if there are multiple entries found, display all
        ArrayList<GTNode> res = new ArrayList<>();
        res = files.searchitems(res, name);
        GTNode curr;
        if(res.isEmpty()){
            outputwriter.write("whereis: no paths with " + name + " exists");
        }else{
            outputwriter.write("whereis: paths with " + name + " are:");
            for(int i = 0; i < res.size(); i++){
                curr = res.get(i);
                outputwriter.write(curr.parentspath());
                outputwriter.write("\t" + curr.item.toString());
            }
        }
    }
}
