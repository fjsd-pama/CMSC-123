#include <iostream>
using namespace std;
template <class T>
class node{
    public:
        T item;
        node<T> *next;
        node();
        node(T);
};
//default constructor
template <class T>
node<T>::node(){
    item = 0;
    next = NULL;
}
//overloaded
template <class T>
node<T>::node(T given){
    item = given;
    next = NULL;
}
template <class T>
class list{
    private:
        int size;
        node<T> *head,*tail;
    public:
        list();
        list(const list<T>&);
        list& operator=(const list<T>&);
       
        bool insert(T,int);
        T get(int); //return node at that pos??
        int getSize(){return size;
};

template <class T>
list<T>::list(){
    size = 0;
    head = NULL;
    tail = NULL;
}

template <class T>
list<T>::list(const list<T>& l){
    size = 0;
    head = NULL;
    tail = NULL;
    int pos = 0;
    for(node<T>*tmp=l.head;tmp!=NULL;tmp=tmp->next){
       insert(tmp->item, pos++);
    }
}

template <class T>
bool list<T>::insert( T element, int position ){
    if ( (position < 0) || (position > size) ){
        return false;
    } else {
        int x = 0;
        node<T> *el = new node<T>(element);
        
        if (size == 0){
            head = el;
            tail = el;
        } else if (position == 0){
            el->next = head;
            head = el;
        } else if (position == size){
            tail->next = el;
            tail = el;
        }else{
            node<T> *tmp = head;
            while ( x < (position - 1) ){
                tmp = tmp->next;
                x++;
            }
            el->next = tmp->next;
            tmp->next = el;
         
        }
        
        size += 1;
    }
    return true;
}

template <class T>
T list<T>::get(int position){
    int x = 0;
    node<T> *tmp = head;
    while ( x < position  ){
        tmp = tmp->next;
        x++;
    }
    return tmp->item;
}

void display( list<int> given ){
       
    for (int i = 0; i < given.getSize(); i++){
        cout<<given.get(i)<<" ";
    }
    cout<<endl;
}


int main() {
    int numTest; //number of test cases
    int x; //position
    int y; //element to insert
    
    cin >> numTest;
    list<int> a;
    for (int i = 0; i < numTest; i++) {
        cin >> x;
        cin >> y;
        a.insert(y, x);
        display(a);
       
    }
    return 0;
}
