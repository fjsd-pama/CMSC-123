#include <iostream>

using namespace std;

template <class T>
class node{
    public:
        T item;
        node<T> *next, *prev;
        node();
        node(T);
};

//default constructor
template <class T>
node<T>::node(){
    next = NULL;
    prev = NULL;
}

//overloaded
template <class T>
node<T>::node(T given){
    item = given;
    next = NULL;
    prev = NULL;
}

template <class T>
class list{
//iterator struct
    public:
        struct iterator{
            node<T>* pointer;
            iterator& operator++(int){pointer = pointer->next; return (*this);}
            T operator*(){return pointer->item;}
            bool operator!=(const iterator& it){return pointer!=it.pointer;}
        };

    private:
        int size;
        node<T> *head,*tail;
        iterator iter;
    public:
        list();
        list(const list<T>&);
        ~list();
        list& operator=(const list<T>&);

        bool insert(T,int);
        T get(int);
        int getSize(){return size;}
        bool remove(int);
        bool set(T,int);
        iterator begin(){iter.pointer = head; return iter;}
        iterator end(){iter.pointer = tail->next; return iter;}
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
list<T>::~list(){
    while ( size > 0 ){
        remove(0);
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
                head->prev = NULL;
                head->next = NULL;
                tail = head;
            } else if (position == 0){
                head->prev = el;
                el->next = head;
                el->prev = NULL;
                head = el;
            } else if (position == size){
                el->prev = tail;
                el->next = NULL;
                tail->next = el;
                tail = el;
            }else{
                node<T> *tmp = head;
                while ( x <= (position - 1) ){
                    tmp = tmp->next;
                    x++;
                }

                el->prev = tmp->prev;
                el->next = tmp;
                (tmp->prev)->next = el;
                tmp->prev = el;

            }

            size += 1;
        }
        return true;
    }

template <class T>
T list<T>::get(int position){
    if ( position >= 0 && position < size ){
        int mid = size / 2;

        if ( position > mid  ){
            int x = size - 1;
            node<T> *tmp = tail;
            while ( x > mid && (x > position ) ){
                tmp = tmp->prev;
                x--;
            }

            return tmp->item;
        } else{
            int x = 0;
            node<T> *tmp = head;
            while ( x <= mid && (x < position )){
                tmp = tmp->next;
                x++;
            }

            return tmp->item;
        }
    } else{
        throw 123; //"POSITION OUT OF BOUNDS"
    }

}

template <class T>
    bool list<T>::set( T element, int position ){
        if ( (position < 0) || (position > size) ){
            return false;
        } else {
            int mid = size / 2;

            if ( position > mid ){
                int x = size - 1;
                node<T> *tmp = tail;
                while ( (x > mid) && (x > position ) ){
                    tmp = tmp->prev;
                    x--;
                }

                tmp->item = element;
            } else{
                int x = 0;
                node<T> *tmp = head;
                while ( x <= mid && (x < position ) ){
                    tmp = tmp->next;
                    x++;
                }

                tmp->item = element;
            }
        }
        return true;
    }

template <class T>
    bool list<T>::remove( int position ){
        if ( (position < 0) || (position >= size) ){
            return false;
        } else {
            int x = 0;

            if (size == 0){
                //do nothing
            } else if (position == 0){
                node<T> *del = head;
                head = head->next;
                if (head != NULL){
                    head->prev = NULL;
                }

                del->next = NULL;
                delete del;

            } else if (position == (size - 1)){
                node<T> *del = tail;
                node<T> *tmp = tail->prev;
                del->next = NULL;
                tmp->next = NULL;
                tail = tmp;
                delete del;

            }else{
                //in between head and tail
                node<T> *tmp = head;
                while ( x <= position ){
                    tmp = tmp->next;
                    x++;
                }

                node<T> *del = tmp->prev;
                tmp->prev = del->prev;
                (del->prev)->next = tmp;
                delete del;
            }

            size--;
        }
        return true;
    }


    void display( list<int> l ){
        if ( l.getSize() == 0 ){
            //do nothing
        } else{
            for (list<int>::iterator i = l.begin(); i!=l.end(); i++){
                cout << *i << " ";
            }

            /*for (int i = 0; i < l.getSize(); i++){
                cout<<l.get(i)<<" ";

            }*/
        }
        cout<<endl;
    }

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int numTest;
    int firstNumInLine;
    int x; //arg 1
    int y; //arg 2

    cin >> numTest;
    list<int> a;
    for (int i = 0; i < numTest; i++) {
        cin >> firstNumInLine;
        if ( firstNumInLine == 1 ){
            cin >> x;
            cin >> y;
            a.insert(y, x);
            display(a);
        } else if ( firstNumInLine == 2 ){
            cin >> x;
            a.remove(x);
            display(a);
        } else if (firstNumInLine == 3){
            cin >> x;

            try{
               cout<<a.get(x)<<endl;
            } catch( int err ){
                if ( err == 123 ){
                    cout<<"POSITION OUT OF BOUNDS\n";
                }
            }

        } else{
            cin >> x;
            cin >> y;
            a.set(y, x);
            display(a);
        }
    }

    return 0;
}
