#include <iostream>

using namespace std;
class vector {
    private:
        int size, max;
        int *items;
        void expand(); // 5
    public:
        vector();
        int getSize();
        int at(int);
        bool insertItem(int, int);
        bool removeItem(int);
        int& operator[](int);


};


vector::vector(){
        max = 5;
        size = 0;
        items = new int[max];
    }

    int vector::getSize(){
        return size;
    }

    int vector::at(int i){
        return items[i];
    }

    bool vector::insertItem( int element, int index ){
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

    void vector::expand() {
        int* itemsCopy = new int[max];
        for (int i = 0; i < size; i++) {
            itemsCopy[i] = items[i];
        }

        delete[] items;
        max += 5;
        items = new int[max];

        for (int i = 0; i < size; i++) {
            items[i] = itemsCopy[i];
        }

        delete[] itemsCopy;
    }


    bool vector::removeItem( int index ){
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


    int& vector::operator[](int index){
        return items[index];
    }

    void isSorted( vector given ){
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

    void display( vector given ){
        for (int i = 0; i < given.getSize(); i++){
            cout<<given[i]<<" ";
        }

        cout<<endl;
    }

    void deleteDuplicate( vector given ){

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


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int numEls, x;
    cin >> numEls;

    for (int i = 0; i < numEls; i++){
        vector a;
        for (int j = 0; j < 10; j++){
            cin >> x;
            a.insertItem(x, j);
        }

        isSorted(a);
        deleteDuplicate(a);
    }

    return 0;
}
