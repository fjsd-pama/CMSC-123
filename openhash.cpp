#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

class hashtable {
private:
      int maxsize;
      vector<string> map[1024];
      int type; //1=for Horner's, 2=for ELF
      int size;
public:
      hashtable(int);
      int insert(string);
      int search(string);
      int hashfx(unsigned int);
      unsigned int hashcode1(string); //Horner's rule
      unsigned int hashcode2(string); //UNIX ELF's hash
};

int hashtable::hashfx(unsigned int x){
    int z = 60147, d = 10, w = 31;
    int theMod = 1 << w, thediv = 2 << (w - d); // for long lang
    return (((z * x) % theMod) >> w - d);
}

unsigned int hashtable::hashcode1(string st){
    unsigned int h = 0;
    int len = st.length();
    for (int i = 0; i < len; i++){
        h = 31*h + st[i];
    }

    return h;
}

unsigned int hashtable::hashcode2(string st){
    unsigned int h = 0, high, i = 0;
    while( st[i] != '\0' ){
        h = (h << 4) + st[i++];
        if(high = (h & 0xF0000000)){
            h ^= high >> 24;
        }
        h &= ~high;
    }

    return h;
}

hashtable::hashtable(int type) {
      this->type = type;
      maxsize = 1024;
      size = 0;
      /*map = new vector<string>*[maxsize];
      for (int i = 0; i < maxsize; i++){
            map[i] = new vector<string>;
      }*/
}

int hashtable::insert(string st){
    unsigned int val = 0;
    if(type==1){
        val = hashcode1(st);
    }else{
        val = hashcode2(st);
    }

    int hash = hashfx(val);
    //int op = 1;
    if(size == maxsize){
        return 1;
    }

    //insert
    (map[hash]).push_back(st);
    size++;
    return map[hash].size();
}

//returns the number of probings done before the item is found
int hashtable::search(string st){
    unsigned int val = 0;
    if(type==1){
        val = hashcode1(st);
    }else{
        val = hashcode2(st);
    }

    int hash = hashfx(val);
    int op = 1;

    vector<string> v = map[hash];
    for(int i = 0; i < v.size(); i++){
        string curr = v[i];
        if( curr.compare(st) == 0 ){
            return op;
        }
        op++;
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
        hashtable a(1), b(2);

        for(int j = 0; j < numitems; j++){
            string curritem;
            cin>>curritem;
            int res = a.insert(curritem);
            b.insert(curritem);
            cout<< res <<" ";
        }
        //cout<<endl;

        string curritem;
        cin>>curritem;
        int res = a.search(curritem);
        cout<< res <<" ";
        res = b.search(curritem);
        cout<< res <<endl;
    }

    return 0;
}
