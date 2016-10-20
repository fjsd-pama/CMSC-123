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
class stack{
    private:
        int size;
        node<T> *top;
    public:
        stack();
        stack(const stack<T>&);
        ~stack();
        stack& operator=(const stack<T>&);

        void push(T);
        T peek();
        int getSize(){return size;}
        bool pop();
        void display();
};

template <class T>
stack<T>::stack(){
    size = 0;
    top = NULL;
}

// pabali sa queue!
template <class T>
stack<T>::stack(const stack<T>& l){
    size = 0;
    top = NULL;
//    for(node<T>*tmp=l.top; tmp!=NULL; tmp=tmp->next){
//       push(tmp->item);
//    }
    int y = l.size;
    while (y > 0) {
        node<T>*tmp = l.top;
        int x = 0;
        while (x < (y - 1)) { // kuwangan lang ug minus 1!
            tmp = tmp->next;
            x++;
        }
        push(tmp->item);
        y--;
    }
}

template <class T>
stack<T>::~stack(){
    while ( size > 0 ){
        pop();
    }
}


template <class T>
    void stack<T>::push( T element ){

        node<T> *el = new node<T>(element);

        if (size == 0){
            top = el;
        } else {
            el->next = top;
            top = el;
        }

        size++;

    }

template <class T>
   bool stack<T>::pop(){


        if (size == 0){
            return false;
        } else {
            node<T> *del = top;
            top = top->next;
            del->next = NULL;
            delete del;
        }


        size--;
       return true;

    }

template <class T>
T stack<T>::peek(){
    if ( size != 0 ){
         return top->item;
    } else{
        throw 123; //empty stack!
    }

}

template <class T>
void stack<T>::display(){

    for(node<T>*tmp=top;tmp!=NULL;tmp=tmp->next){
       cout<<tmp->item<<" ";
    }

    cout<<endl;
}



void display(stack<int> given) {
    given.display();
}

int main() {
    int numTest;
    int firstNumInLine;
    int x; //arg 1
    int y; //arg 2

    cin >> numTest;
    stack<int> a;
    for (int i = 0; i < numTest; i++) {
        cin >> firstNumInLine;
        if ( firstNumInLine == 1 ){
            cin >> x;
            a.push(x);
            a.display();
        } else if ( firstNumInLine == 2 ){
            a.pop();
            a.display();
        } else if (firstNumInLine == 3){
            try{
               cout<<a.peek()<<endl;
            } catch( int err ){
                if ( err == 123 ){
                    cout<<"stack is empty.\n";
                }
            }

        } else {
            a.display();
        }
    }

    //display(a); // for stack copy constructor...

}
