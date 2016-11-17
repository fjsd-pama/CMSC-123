#include <iostream>
#include <array>

using namespace std;

template <class T>
class heap{
public:
    int size;
    int max;
    T *items;
    heap(int);
    ~heap();
    void insert(T);
    void display();
};

template <class T>
heap<T>::heap(int n){
    size = 0;
    max = n + 1;
    items = new int[max];
}
template <class T>
heap<T>::~heap(){
    delete[] items;
}

template <class T>
void heap<T>::insert(T item){
    if( size == max ){
        return;
    }

    items[++size] = item;
    int current = size;
    int parent = current/2;

    while( parent > 0 && (item <= items[parent]) ){
        T temp = items[parent];
        items[parent] = item;
        items[current] = temp;
        current = parent;
        parent = current/2;
    }
}

template <class T>
void heap<T>::display(){
    for(int i = 1; i <= size; i++){
        cout<<items[i] << " ";
    }

    cout<<endl;
}

using namespace std;
int main() {
    int testcases;
    int currItem;
    int size;

    cin>>testcases;
    for(int x = 0; x < testcases; x++){

        cin>>size;
        heap<int> a(size);

        for(int j = 0; j < size; j++ ){
            cin>>currItem;
            a.insert(currItem);
            a.display();
        }

    }
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    return 0;
}
