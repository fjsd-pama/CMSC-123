#include <iostream>
#include <cmath>
using namespace std;
class hashtable {
private:
      int **map;
      int size;
      int maxsize;
public:
      hashtable();
      ~hashtable();
      int insert(int);
      int search(int);
      int hashfx(int);
};

int hashtable::hashfx(int x){
    int z = 60147, d = 9, w = 16;
    int theMod = 1 << w, thediv = 2 << (w - d); // for long lang
    return (((z * x) % theMod) >> w - d);
}
hashtable::hashtable() {
      maxsize = 512;
      size = 0;
      map = new int*[maxsize];
      for (int i = 0; i < maxsize; i++){
            map[i] = NULL;
      }
}

hashtable::~hashtable(){
      for (int i = 0; i < maxsize; i++){
            if(map[i] != NULL){
                  delete map[i];
            }
      }

      delete[] map;
}

//returns the number of probings done before the item is found
int hashtable::search(int key){
      int hash = hashfx(key);
      int op = 0;
     if( hash > (pow(2, 16)-1) ){
         return 0;
     }

      while ( *(map[hash]) != key ){
          hash = (hash + 1) % maxsize;
          op++;
      }

      return op;
}

int hashtable::insert(int key){
      int hash = hashfx(key);
      int op = 0;
      if(size == maxsize){
          return 0;
      }

      if( hash < (pow(2, 16)-1) ){
          while (map[hash] != NULL){
          
            hash = (hash + 1) % maxsize;
            op++;
          }

      
           //insert
           map[hash] = new int(key);
           size++;
           return op;
      }
      return op;
}

using namespace std;
int main() {
    int cases;
   
    cin >> cases;
    
    for(int i = 0; i < cases; i++){
        int numitems;
        cin>>numitems;
        hashtable a;
        
        for(int j = 0; j < numitems; j++){
            int curritem;
            cin>>curritem;
            int res = a.insert(curritem);
            cout<< res <<" ";
            
        }
        cout<<endl;
        int curritem;
        cin>>curritem;
        int res = a.search(curritem);
        cout<< res <<endl;
    }
    return 0;
}