import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by Jose Arniel J. Pama on 12/9/2016.
 */
public class GTNode implements Serializable {
    protected FileDescriptor item;
    protected  GTNode parent;
    protected List<GTNode> children;

    private OutputWriter outputwriter = new OutputWriter(false);

    public GTNode(){
        parent = null;
        this.children = new ArrayList<>();

    }

    public GTNode(FileDescriptor file){
        this();
        this.item = file;
    }

    public void setChildren(List<GTNode> children){
        this.children = children;
    }

    public void setOutputwriterIsToScreen(boolean isToScreen){
        outputwriter.setIstoscreen(isToScreen);
    }

    public boolean addchild(FileDescriptor child){
        GTNode gn = new GTNode(child);
        return this.addchild(gn);
    }

    public boolean addchild(GTNode child){
        if( children.isEmpty() ){
            child.parent = this;
            children.add(child);
            return true;
        }else{
            for(int i = 0; i < children.size(); i++){
                GTNode curr = children.get(i);
                if((curr.item.name).compareTo(child.item.name)==0){
                    String st = curr.item.name + ": file already exists";
                    outputwriter.write(st);
                    return false;
                }
            }

            child.parent = this;
            children.add(child);
            return true;
        }
    }

    public boolean removechild(String childname){
        for(int i = 0; i < children.size(); i++){
            GTNode curr = children.get(i);
            if((curr.item.name).compareTo(childname)==0){
                children.remove(curr);
                return true;
            }
        }

        return false;

    }

    public void displaychildren(){
        if(children.isEmpty()){
            String st = this.item.name + " has: empty.";
            outputwriter.write(st);
        }else{
            String st = this.item.name + " has: ";
            outputwriter.write(st);
            for(int i = 0; i < children.size(); i++){
                GTNode curr = children.get(i);
                outputwriter.write("\t" + curr.item.toString());
            }
        }
    }

    public GTNode searchchild(String childname){
        for(int i = 0; i < children.size(); i++){
            GTNode curr = children.get(i);
            if((curr.item.name).compareTo(childname)==0){
                return curr;
            }
        }

        return null;
    }

    public String parentspath(){
        String res = "";
        GTNode tmp = this.parent;
        if(tmp==null){
            String st = "this node is empty, no possible parents!";
            outputwriter.write(st);
        }else{
            while(tmp != null){
                res = "/" + (tmp.item.name) + res;
                tmp = tmp.parent;
            }
        }

        res = res + "/" + this.item.name; //ex. dir /hello/how
        return "Path: " + res;
    }
}
