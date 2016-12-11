import java.io.Serializable;
import java.util.ArrayList;

/**
 * Created by Jose Arniel J. Pama on 12/9/2016.
 */
public class GeneralTree implements Serializable {
    private GTNode root;
    protected OutputWriter outputwriter = new OutputWriter(false);

    public GeneralTree(){
        root = null;
    }

    public GTNode getroot(){
        return root;
    }

    public boolean insert(FileDescriptor fd, String parentname){
        if(getroot()==null){
            this.root = new GTNode(fd);
            return true;
        }

        if(parentname.compareTo(root.item.name)==0){
            return root.addchild(fd);
        }

        return addnewnode(getroot(), parentname, fd);
    }

    private boolean addnewnode(GTNode given, String parentname, FileDescriptor fd){
        if(given==null){
            return false;
        }

        if( (given.item.name).compareTo(parentname)==0
                && (given.item.isdir==true) ){
            return given.addchild(fd);
        }

        for(int i = 0; i < given.children.size(); i++){
            return addnewnode(given.children.get(i), parentname, fd);
        }

        return false;
    }

    public boolean remove(String item, String parentname){
        if(root==null){
            return false;
        }

        if( (root.item.name).compareTo(item)==0 ){
            root = null;
            outputwriter.write("removed: " + item);
            return true;
        }

        if(parentname.compareTo(getroot().item.name) == 0){
            outputwriter.write("removed: " + item);
            return getroot().removechild(item);
        }

        return removethisitem(getroot(), parentname, item);
    }

    private boolean removethisitem(GTNode given, String parentname, String item){
        if(given==null){
            return false;
        }


        if( (given.item.name).compareTo(parentname)==0 ){
            outputwriter.write("removed: " + item);
            given.removechild(item);
        }

        for(int i = 0; i < given.children.size(); i++){
            return removethisitem(given.children.get(i), parentname, item);
        }

        return false;
    }

    public GTNode search(String item, String parentname){
        if(root==null){
            return null;
        }

        if( (getroot().item.name).compareTo(parentname)==0 ){
            outputwriter.write("searched: " + item);
            return getroot().searchchild(item);
        }

        if(parentname.compareTo(getroot().item.name) == 0){
            return getroot().searchchild(item);
        }

        return searchthisitem(getroot(), parentname, item);
    }

    private GTNode searchthisitem(GTNode given, String parentname, String item){
        if( (given.item.name).compareTo(parentname)==0 ){
            outputwriter.write("searched: " + item);
            return given.searchchild(item);
        }

        for(int i = 0; i < given.children.size(); i++){
            return searchthisitem(given.children.get(i), parentname, item);
        }

        return null;
    }

    public ArrayList<GTNode> searchitems(ArrayList<GTNode> result, String item){
        if(root==null){
            return result;
        }

        if( (root.item.name).compareTo(item)==0 ){
            result.add(root);
        }

        return searchsameitems(result, getroot(), item);
    }

    private ArrayList<GTNode> searchsameitems(ArrayList<GTNode> result, GTNode given, String item){
        if( (given.item.name).compareTo(item)==0 ){
            result.add(given);
        }

        for(int i = 0; i < given.children.size(); i++){
            searchsameitems(result, given.children.get(i), item);
        }

        return result;
    }

    public void displaytree(){
        if(root==null){
            outputwriter.write("The directory is empty.");
        }else{
            outputwriter.write("THE DIRECTORY HAS: ");
            displaytree(getroot());
        }
    }

    public void displaytree(GTNode given){
        if( given != null ){
            outputwriter.write(given.item.toString());
        }else{
            return;
        }

        for(int i = 0; i < given.children.size(); i++){
            displaytree(given.children.get(i));
        }
    }

    public void displaytree(GTNode given, String filetype){
        if( given != null ){
            //item must not be a directory in this case
            if( (given.item.name).contains(filetype) && (given.item.isdir==false) ){
                outputwriter.write("\t" + given.item.toString());
            }
        }else{
            return;
        }

        for(int i = 0; i < given.children.size(); i++){
            displaytree(given.children.get(i), filetype);
        }
    }
}
