#include <iostream>

using namespace std;

template <class T>
class vector {
    private:
        int size, max;
        T *items;
        void expand(); // 5
    public:
        vector();
        vector(T);
        vector(const vector&);
        int getSize();
        ~vector();
        T at(int);
        bool insertItem(T, int);
        bool removeItem(int);
        T& operator[](int);
};

template <class T>
vector<T>::vector(const vector<T>& v) {
    size = v.size;
    max = v.max;
    items = new T[max];

    copy(v.items, v.items + size, items);
}

template <class T>
vector<T>::~vector(){
	delete[] items;
}

void deleteDuplicate( vector<int> given );
void deleteDuplicate( vector<string> given );
void isSorted( vector<int> given );
void isSorted( vector<string> given );

template <class T>
vector<T>::vector(T){
        max = 5;
        size = 0;
        items = new T[max];
    }

template <class T>
vector<T>::vector(){
        max = 5;
        size = 0;
        items = new T[max];
    }
    template <class T>
    int vector<T>::getSize(){
        return size;
    }

    template <class T>
    T vector<T>::at(int i){
        return items[i];
    }
    template <class T>
    bool vector<T>::insertItem( T element, int index ){
        if ( (index < 0) || (index > size) ){
            return false;
        } else {
            if (size == max) {
                expand();

            }

            for ( int i = index + 1; i < size; i++ ){
                items[i] = items[i - 1];
            }

            size += 1;

            items[index] = element;
        }
        return true;
    }

    template <class T>
    void vector<T>::expand() {
        T* itemsCopy = new T[max];
        for (int i = 0; i < size; i++) {
            itemsCopy[i] = items[i];
        }

        delete[] items;
        max += 5;
        items = new T[max];

        for (int i = 0; i < size; i++) {
            items[i] = itemsCopy[i];
        }

        delete[] itemsCopy;
    }

    template <class T>
    bool vector<T>::removeItem( int index ){
        if ( (index < 0) || (index > size) ){
            return false;
        } else{
            if (size == max) {
                expand();
            }

            for (int i = index; i < size - 1; i++ ){
                items[i] = items[i+1];
            }
            size--;
        }

        return true;
    }

    template <class T>
    T& vector<T>::operator[](int index){

         return items[index];
    }

    void isSorted( vector<int> given ){
        for (int i = 0; i < given.getSize() -1; i++){
            if ( given[i] > given[i+1]){
                cout<<"NO"<<endl;
                return;
            }
        }

        if ( given[0] == given[given.getSize() - 1]){
            cout<<"NO"<<endl;
        } else{
             cout<<"YES"<<endl;
        }

    }

    void isSorted( vector<string> given ){
        for (int i = 0; i < given.getSize() -1; i++){
            //if given[i] > given[i+1]
            if ( given[i].compare(given[i+1]) > 0){
                cout<<"NO"<<endl;
                return;
            }
        }

        if ( given[0].compare(given[given.getSize() - 1]) > 0){
            cout<<"NO"<<endl;
        } else{
             cout<<"YES"<<endl;
        }

    }

    template <class T>
    void display( vector<T> given ){
        for (int i = 0; i < given.getSize(); i++){
            cout<<given[i]<<" ";
        }

        cout<<endl;
    }

    void deleteDuplicate( vector<int> given ){

        for (int i = 0; i < given.getSize() - 1; i++){
            for (int j = i + 1; j < given.getSize(); j++){
                if ( given[i] == given[j] ){
                    given.removeItem(j);
                    j--;
                }
            }
        }

        display(given);

    }

    void deleteDuplicate( vector<string> given ){

        for (int i = 0; i < given.getSize() - 1; i++){
            for (int j = i + 1; j < given.getSize(); j++){
                if ( given[i].compare(given[j]) == 0 ){
                    given.removeItem(j);
                    j--;
                }
            }
        }

        display(given);

    }


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int numEls, x;
    int z; //for input ints
    string y; //for input string
    cin >> numEls;

    for (int j = 0; j < numEls; j++){
        cin >> x;

        if ( x == 2 ){
            //performs here arithmetic for string
            vector<string> a;

            //accepts 10 number of string
            for (int i = 0; i < 10; i++){
                cin >> y;
                a.insertItem(y, i);
            }

            isSorted(a);
            deleteDuplicate(a);
        } else{
            if (x == 1){
                //performs here arithmetic for string
                vector<int> a;

                //accepts 10 number of string
                for (int i = 0; i < 10; i++){
                    cin >> z;
                    a.insertItem(z, i);
                }

                isSorted(a);
                deleteDuplicate(a);
            }
        }
    }




    return 0;
}
