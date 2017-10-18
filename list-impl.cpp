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
        ~list();
        list& operator=(const list<T>&);

        bool insert(T,int);
        T get(int);
        int getSize(){return size;}
        bool remove(int);
        bool set(T,int);
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
    if ( position >= 0 && position < size ){
        int x = 0;
        node<T> *tmp = head;
        while ( x < position  ){
            tmp = tmp->next;
            x++;
        }

        return tmp->item;
    } else{
        throw 123; //"POSITION OUT OF BOUNDS"
    }

}

template <class T>
    bool list<T>::set( T element, int position ){
        if ( (position < 0) || (position > size) ){
            return false;
        } else {
            int x = 0;

            node<T> *tmp = head;
            while ( x < position ){
                tmp = tmp->next;
                x++;
            }

            tmp->item = element;
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
                node<T> *headBefore = head;
                head = head->next;
                delete headBefore;
            } else if (position == (size - 1)){
                int p = 0;
                node<T> *tmp = head;
                while ( p < (size - 2)){
                    tmp = tmp->next;
                    p++;
                }

                node<T> *tailBefore = tail;
                tmp->next = NULL;
                tail = tmp;
                delete tailBefore;
            }else{
                //in between head and tail
                node<T> *tmp = head;
                while ( x < (position - 1) ){
                    tmp = tmp->next;
                    x++;
                }
                node<T> *tempAfter = tmp->next;
                tmp->next = tempAfter->next;
                tempAfter->next = NULL;
                delete tempAfter;
            }

            size--;
        }
        return true;
    }


    void display( list<int> given ){

        for (int i = 0; i < given.getSize(); i++){
            cout<<given.get(i)<<" ";

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
        } else{
            cin >> x;

            try{
               cout<<a.get(x)<<endl;
            } catch( int err ){
                if ( err == 123 ){
                    cout<<"POSITION OUT OF BOUNDS\n";
                }
            }

        }
    }

    return 0;
}
