#include <iostream>

#include <iostream>
#define MAX 20

using namespace std;


class array{
    private:
        int items[MAX];
        int size;
    public:
        array();
        array(int);
        int getSize();
        int at(int);
        bool insertItem(int, int);
        bool removeItem(int);
        int operator[](int);
};

array::array(){
        size = 0;
    }

    array::array(int n){
        size = MAX;

        for(int i=0; i<size; i++)
            items[i] = n;
    }

    int array::getSize(){
        return size;
    }

    int array::at(int i){
        return items[i];
    }

    bool array::insertItem( int element, int index ){
        if ( (index < 0) || (index > size) || (size == MAX) ){
            return false;
        } else{
            size += 1;
            for ( int i = index + 1; i < size; i++ ){
                items[i] = items[i - 1];
            }

            items[index] = element;
            return true;
        }
    }

    bool array::removeItem( int index ){
        if ( (index < 0) || (index > size) || (size == MAX) ){
            return false;
        } else{
            for (int i = index; i < size - 1; i++ ){
                items[i] = items[i+1];
            }
            size--;

            return true;
        }
    }


    int array::operator[](int index){
        return items[index];
    }

    void isSorted( array given ){
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

    void display( array given ){
        for (int i = 0; i < given.getSize(); i++){
            cout<<given[i]<<" ";
        }

        cout<<endl;
    }

    void deleteDuplicate( array given ){

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
        array a;
        for (int j = 0; j < 10; j++){
            cin >> x;
            a.insertItem(x, j);
        }

        isSorted(a);
        deleteDuplicate(a);
    }

    return 0;
}
