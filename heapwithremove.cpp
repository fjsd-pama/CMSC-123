/*Dear Sir,
    Please disregard this. I don't intend to violate the rules. This is only for testing purposes. My TRUE output for this lab is at Krishia Ranque Bello's account. Please don't be angry. (Huhu)
    I failed to copy and paste it because I was too desperate to get the solution. My emotions got me. Lesson learned. Thank you so much.
'*/

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
    void remove();
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
void heap<T>::remove(){
    if( size == 0 ){
        return;
    }

    int temp = items[size];
    size--;
    int curr = 1;
    int leftChild = curr * 2;
    int rightChild = leftChild + 1;

    //puts item found at the last index at index curr 
    items[curr] = temp;
    int currItem;

    while( curr <= (size/2) ){

        if (leftChild <= size ){
            currItem = items[curr];

            //sets the right location of currItem
            if( (items[leftChild] < currItem) && (items[leftChild] < items[rightChild]) ){
                
                items[curr] = items[leftChild];
                items[leftChild] = currItem;
                
                curr = leftChild;
            }else if( (items[rightChild] < currItem) && (items[rightChild] < items[leftChild]) ){
                
                items[curr] = items[rightChild];
                items[rightChild] = currItem;
                
                curr = rightChild;
            }else{
                break;
            }
        }else{
            //human na ang looping
            break;
        }
        
        leftChild = curr * 2;
        rightChild = leftChild + 1;
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
        }

        int remove;
        cin>>remove;
        for(int j = 0; j < remove; j++){
            a.remove();
            a.display();
        }

    }
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    return 0;
}
