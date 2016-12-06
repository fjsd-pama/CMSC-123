#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <typeinfo>
#include <stack>
#include <queue>

using namespace std;

template <class T>
class myqueue {
private:
	queue<T> a;
public:
	myqueue(){ };
	void push(T item){ a.push(item); }
    void pop(){ a.pop(); }
    bool empty(){ return a.empty(); }
    int size(){ return a.size(); }
    T top(){ return a.front(); }
};

class square{
public:
	char ch;
	int x; //row
	int y; //column
	bool visited;
	square(char, int, int);
	square();
};

square::square(){
	square(NULL, 0, 0);
}
square::square(char sq, int row, int col){
	ch = sq;
	x = row;
	y = col;
	if(sq == '#'){ visited = true; } //mark wall as visited by default
	else{ visited = false; }
};

class maze{
public:
	square **themaze;
	int dimensionRows;
	int dimensionCols;
	square start;
	maze(square **, int, int);
	~maze();
	string tostring();
};

maze::maze(square **given, int numRows, int numCols){
	themaze = new square*[numRows]; //allocates mememory for n rows

	for (int i = 0; i < numRows; i++){
		themaze[i] = new square[numCols]; //allocating m elements for each row
	}

	//copies given to the themaze
	for(int i = 0; i < numRows; i++){
		for(int j = 0; j < numCols; j++){
			themaze[i][j] = given[i][j];
			if( given[i][j].ch == 'o' ){
				start = given[i][j]; //assign start square to this, to be used later
			}
		}
	}

	dimensionRows = numRows;
	dimensionCols = numCols;
}

maze::~maze(){
	//free the dynamically allocated memory
	for (int i = 0; i < dimensionRows; i++){
		delete[] themaze[i]; //for each row
	}
	delete[] themaze;	
}

string maze::tostring(){
	string result = "";
	//copies given to the themaze
	for(int i = 0; i < dimensionRows; i++){
		for(int j = 0; j < dimensionCols; j++){
			result += themaze[i][j].ch;
		}

		result += "\n";
	}

	return result;
}


template <class T>
class agenda{
private:
    T *adt;
    int type; //1 for stack, 2 for queue
public:
    agenda();
    ~agenda(){delete adt;}
    void add(square);
    void remove();
    bool isempty();
    int getsize();
    square peek();
};

template <class T>
agenda<T>::agenda(){
    adt = new T();
    string t1 = typeid(*adt).name();
    string t2 = typeid(stack<square>).name();
    string t3 = typeid(myqueue<square>).name();
    
    //cout<<t1<<endl<<t2<<endl<<t3;
    if(t1.compare(t2)==0){
        type = 1;
    } else if(t1.compare(t3)==0){
        type = 2;
    }
};

template <class T>
void agenda<T>::add(square given){
    adt->push(given); //stack and queue same function names in libraries
}

template <class T>
void agenda<T>::remove(){
    adt->pop();
}

template <class T>
bool agenda<T>::isempty(){
    return adt->empty(); //stack and queue same function names in libraries
}

template <class T>
square agenda<T>::peek(){
    return adt->top();
}

template <class T>
int agenda<T>::getsize(){
    return adt->size();
}

template <class T>
class mazesolver{
private:
    agenda<T> *a;
    maze *m;
    bool issafe(int, int);
    bool solve(maze*, int, int, agenda<T>*);
public:
    mazesolver<T>(square **, int, int);
    ~mazesolver();
    void solve();
    void writesolution(char*);
};

template <class T>
mazesolver<T>::mazesolver(square **given, int numRows, int numCols){
	a = new agenda<T>();
	m = new maze(given, numRows, numCols);
}

template <class T>
mazesolver<T>::~mazesolver(){
	delete a;
	delete m;
}

template <class T>
bool mazesolver<T>::issafe(int row, int col){
	//determines if that location is safe
	if( (row >= 0 && row < (m->dimensionRows)) && (col >= 0 && col < (m->dimensionCols)) &&
		((m->themaze[row][col]).visited == false) ){
		cout<<"safe  "<<"x: "<<row<<" y: "<<col<<endl;
		return true;
	}

	cout<<"!safe  "<<"x: "<<row<<" y: "<<col<<endl;
	return false;
}

template <class T>
void mazesolver<T>::solve(){
	(solve( m, (m->start).x, (m->start).y, a ));
	/*if( !(solve( m, (m->start).x, (m->start).y, a )) ){
		//if not solved, write original maze
	}else{
		 

	}

	cout<<endl;*/
}


/*template <class T>*/
/*bool mazesolver<T>::solve(maze* given, int currRow, int currCol, agenda<T>* &a){
	if ( given->themaze[currRow][currCol].ch == '*' ){ return true; } //solution finish, exit found

	if (issafe(currRow, currCol) == true){
		//cout<<"add:"<<given->themaze[currRow][currCol].ch;
		a->add( given->themaze[currRow][currCol] ); //add square to agenda a
		//cout<<"x: "<<currRow<<"y: "<<currCol<<endl;
		//cout<<"visited";
		(given->themaze[currRow][currCol]).visited = true; //set current square to visited
		

		if(solve(given, currRow, currCol - 1, a)){ return true; } //left
		else if(solve(given, currRow - 1, currCol, a)){ return true; } //up
		else if(solve(given, currRow, currCol + 1, a)){ return true; } //right
		else if(solve(given, currRow + 1, currCol, a)){ return true; } //down

		//make sure that a is not empty before removing/popping
		/*else if (a->isempty()){
			//cout<<"empty";
			return false;
		}else{
			//cout<<"remove";
			square curr = a->peek();
			//(given->themaze[curr.x][curr.y]).visited = false;
			a->remove();
			/*if (a->getsize() > 0){ //make sure it's not empty
				square curr = a->peek();
				solve(m, curr.x, curr.y, a);
			}
		}*/
		/*(given->themaze[currRow][currCol]).visited = false;
		return false;
	}

	return false;
}*/


template <class T>
bool mazesolver<T>::solve(maze* given, int currRow, int currCol, agenda<T>* a){
	stack<square> solution;
	solution.push(given->themaze[currRow][currCol]);
	a->add(given->themaze[currRow][currCol]);
	(given->themaze[currRow][currCol].visited) = true;

	square curr;
	while( !solution.empty() ){
		//bool hasadded = false;
		//curr = a->peek();
		curr = solution.top();

		while(!a->isempty()){
			/*square really = a->peek();
			// cout<<really.x<<" " <<really.y;
			(given->themaze[really.x][really.y]).visited = false;*/
			a->remove();
		}

		//solution finish, exit found
		if ( curr.ch == '*' ){
			break;
		}
		
		if( issafe(curr.x, curr.y - 1) ){

			cout<<"left";
			a->add(given->themaze[curr.x][curr.y - 1]);
			//(given->themaze[curr.x][curr.y - 1]).visited = true;
		}

		if( issafe(curr.x - 1, curr.y) ){
			cout<<"up";
			a->add(given->themaze[curr.x - 1][curr.y]);
			//(given->themaze[curr.x - 1][curr.y]).visited = true;
		}

		if( issafe(curr.x, curr.y + 1) ){
			cout<<"right";
			a->add(given->themaze[curr.x][curr.y + 1]);
			//(given->themaze[curr.x][curr.y + 1]).visited = true;
		}

		if( issafe(curr.x + 1, curr.y) ){
			cout<<"down";
			a->add(given->themaze[curr.x + 1][curr.y]);
			//(given->themaze[curr.x + 1][curr.y]).visited = true;
		}

		if(!a->isempty()){
			curr = a->peek();
			(given->themaze[curr.x][curr.y]).visited = true;
			solution.push(curr);
			cout<<"pushed";
		}else{
			if(solution.empty()){
				break;
			}

			solution.pop();
			/*curr = solution.top();
			a->add(curr);*/
		}
	}

	if( !solution.empty() ){
		while(!solution.empty()){
			curr = solution.top();
			solution.pop();
			if(curr.ch == '.'){
				(given->themaze[curr.x][curr.y]).ch = 'x';
			}
		}
	}
}

template <class T>
void mazesolver<T>::writesolution(char* outputfile){
	ofstream file(outputfile, ios::app); //'app' for append
	file<<m->tostring();
	file.close();
}

square** stringToSquare2D(string given, int numRows, int numCols){
	square** result;
	result = new square*[numRows]; //alocate mem for rows
	char curr;
	int row, col, type;
	int index = 0; //index where a char is found in the given

	for(int i = 0; i < numRows; i++){
		result[i] = new square[numCols];
		for(int j = 0; j < numCols; j++){
			curr = given[index++];
			row = i; col = j;
			result[i][j] = square(curr, row, col);
		}
	}

	return result;
}

int main(){
	char* ipfile = "maze.in"; //could be modified acc. to name of file
	char* opfile = "maze2.out";
	ifstream file(ipfile);

	if(file.is_open()){
		int numcases; //number of test cases
		int casesFlag = 0; //for checking the num of testcases finished

		file>>numcases;

		//do while test cases aren't finished and file is not at the end
		while(!file.eof() && casesFlag < numcases){
			int dimensionRows; //dimesions of the current maze
			int dimensionCols;
			string strToConvertToSquare2D; //stores all the rows of the current maze
			square **currMaze; //stores the current maze, a 2D array of pointers to a square
			file>>dimensionRows;
			file>>dimensionCols;

			//read per row of the current maze as a string
			for(int i = 0; i < dimensionRows; i++){
				string st;
				file>>st;
				strToConvertToSquare2D += st;
			}

			//convert strToConvertToSquare2D to a 2D array of square pointers thru stringToSquare2D
			currMaze = stringToSquare2D(strToConvertToSquare2D, dimensionRows, dimensionCols);

			//initialize a mazesolver depending to a template specified
			mazesolver< stack<square> > ms(currMaze, dimensionRows, dimensionCols);
			ms.solve();
			ms.writesolution(opfile);
			mazesolver< myqueue<square> > qs(currMaze, dimensionRows, dimensionCols);
			qs.solve();
			qs.writesolution(opfile);
			casesFlag++;
		}
		file.close();
	}
	return 0;
}