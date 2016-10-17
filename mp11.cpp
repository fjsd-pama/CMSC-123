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
class queue{
    private:
        int size;
        node<T> *front,*rear;
    public:
        queue();
        queue(const queue<T>&);
        ~queue();
        queue& operator=(const queue<T>&);

        void enqueue(int);
        T getFront();
        T getRear();
        int getSize(){return size;}
        bool dequeue();
        void display();
};

template <class T>
queue<T>::queue(){
    size = 0;
    front = NULL;
    rear = NULL;
}

template <class T>
queue<T>::queue(const queue<T>& l){
    size = 0;
    front = NULL;
    rear = NULL;
    int pos = 0;
    for(node<T>*tmp=l.front;tmp!=NULL;tmp=tmp->next){
       enqueue(tmp->item);
    }
}

template <class T>
queue<T>::~queue(){
    while ( size > 0 ){
        dequeue();
    }
}


template <class T>
    void queue<T>::enqueue( int element ){

        node<T> *el = new node<T>(element);

        if (size == 0){
            front = el;
            rear = el;
        } else {
            rear->next = el;
            rear = el;
        }

        size++;

    }

template <class T>
   bool queue<T>::dequeue(){


        if (size == 0){
            return false;
        } else {
            node<T> *del = front;
            front = front->next;
            delete del;
        }


        size--;
       return true;

    }

template <class T>
T queue<T>::getFront(){
    if ( size != 0 ){
         return front->item;
    } else{
        throw 123; //empty queue!
    }

}

template <class T>
T queue<T>::getRear(){
    if ( size != 0 ){
         return rear->item;
    } else{
        throw 123; //empty queue!
    }

}

template <class T>
void queue<T>::display(){

    for(node<T>*tmp=front;tmp!=NULL;tmp=tmp->next){
       cout<<tmp->item<<" ";
    }

    cout<<endl;
}



int main() {
    int numTest;
    int firstNumInLine;
    int x; //arg 1
    int y; //arg 2

    cin >> numTest;
    queue<int> a;
    for (int i = 0; i < numTest; i++) {
        cin >> firstNumInLine;
        if ( firstNumInLine == 1 ){
            cin >> x;
            a.enqueue(x);
            a.display();
        } else if ( firstNumInLine == 2 ){
            a.dequeue();
            a.display();
        } else if (firstNumInLine == 3){

            try{
               cout<<a.getFront()<<endl;
            } catch( int err ){
                if ( err == 123 ){
                    cout<<"queue is empty.\n";
                }
            }

        } else if (firstNumInLine == 4) {

           try{
               cout<<a.getRear()<<endl;
            } catch( int err ){
                if ( err == 123 ){
                    cout<<"queue is empty.\n";
                }
            }
        } else {
            a.display();
        }
    }

}
