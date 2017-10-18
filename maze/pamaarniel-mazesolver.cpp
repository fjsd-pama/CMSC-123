/**
* Created by Jose Arniel J. Pama, 11/27/16
**/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <typeinfo>
#include <stack>
#include <queue>

using namespace std;

template <class T>
//myqueue is a class inheriting the property of an actual queue to replace names
//of methods (e.g. front() to top()), this is important in the class "agenda" later
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

//a square has a location [x, y] and a char representing it
//char could be '.' (an open space), 'o' (the origin), '#' (a wall), '*' (the exit)
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

//a maze has a 2D array of square, has a dimension [dimensionsRows, dimensionCols]
class maze{
public:
	square **themaze;
	int dimensionRows;
	int dimensionCols;
	square start; //where we assign the square 'o', the origin
	maze(square **, int, int);
	~maze();
	string tostring();
};

//constructs a maze given a row and column dimensions
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

//free the dynamically allocated memory
maze::~maze(){
	for (int i = 0; i < dimensionRows; i++){
		delete[] themaze[i]; //free each row
	}
	delete[] themaze;
}

//returns the string representation of "themaze"
string maze::tostring(){
	string result = "";
	
	for(int i = 0; i < dimensionRows; i++){
		for(int j = 0; j < dimensionCols; j++){
			result += themaze[i][j].ch;
		}

		result += "\n";
	}

	return result;
}


template <class T>
//two solutions (using a queue or a stack) must be provided
//agenda class acts a "wrapper" class to avoid two separate (and redundant) solutions
class agenda{
private:
    T *adt;
    int type; //1 for stack, 2 for queue
public:
    agenda();
    ~agenda(){delete adt;}
    void add(square); //add an item
    void remove(); //remove the top
    bool isempty(); //determines if empty
    int getsize(); //returns size
    square peek(); //returns the top
};

template <class T>
agenda<T>::agenda(){
    adt = new T();
    string t1 = typeid(*adt).name();
    string t2 = typeid(stack<square>).name();
    string t3 = typeid(myqueue<square>).name();
    
    if(t1.compare(t2)==0){
        type = 1;
    } else if(t1.compare(t3)==0){
        type = 2;
    }
};

template <class T>
void agenda<T>::add(square given){
    adt->push(given);
}

template <class T>
void agenda<T>::remove(){
    adt->pop();
}

template <class T>
bool agenda<T>::isempty(){
    return adt->empty();
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
//the class used for solving a maze
class mazesolver{
private:
    agenda<T> *a;
    maze *m;
    bool issafe(int, int);
    bool issolved; //initially false, changes to true when solved, used when writing solution to file

    //the private solve(...) method, to be used by the actual solve() called by the user
    bool solve(maze*, int, int, agenda<T>*);
public:
    mazesolver<T>(square **, int, int);
    ~mazesolver();
    void solve();
    void writesolution(char*);
};

template <class T>
//constructs a mazesolver given a 2D array of squares and its rows and columns dimensions
mazesolver<T>::mazesolver(square **given, int numRows, int numCols){
	a = new agenda<T>();
	m = new maze(given, numRows, numCols);
	issolved = false;
}

template <class T>
mazesolver<T>::~mazesolver(){
	delete a;
	delete m;
}

template <class T>
//determines if a location is safe (not a wall, not visited, and not out of bounds)
bool mazesolver<T>::issafe(int row, int col){
	if( (row >= 0 && row < (m->dimensionRows)) && (col >= 0 && col < (m->dimensionCols)) &&
		((m->themaze[row][col]).visited == false) ){
		return true;
	}

	return false;
}

template <class T>
void mazesolver<T>::solve(){
	(solve( m, (m->start).x, (m->start).y, a ));
}

template <class T>
bool mazesolver<T>::solve(maze* given, int currRow, int currCol, agenda<T>* a){
	stack<square> solution; //where we put our final path/solution

	solution.push(given->themaze[currRow][currCol]);
	a->add(given->themaze[currRow][currCol]);
	(given->themaze[currRow][currCol].visited) = true;

	square curr;
	//you solve here (it took me hours, mind you)
	while( !solution.empty() ){
		curr = solution.top();

		while(!a->isempty()){
			a->remove();
		}

		//solution finish, exit found
		if ( curr.ch == '*' ){
			issolved = true;
			break;
		}
		
		//checks left adjacent square, adds to "a" if safe
		if( issafe(curr.x, curr.y - 1) ){
			a->add(given->themaze[curr.x][curr.y - 1]);
		}

		//checks above adjacent square, adds to "a" if safe
		if( issafe(curr.x - 1, curr.y) ){
			a->add(given->themaze[curr.x - 1][curr.y]);
		}

		//checks right adjacent square, adds to "a" if safe
		if( issafe(curr.x, curr.y + 1) ){
			a->add(given->themaze[curr.x][curr.y + 1]);
		}

		//checks below adjacent square, adds to "a" if safe
		if( issafe(curr.x + 1, curr.y) ){
			a->add(given->themaze[curr.x + 1][curr.y]);
		}

		if(!a->isempty()){
			curr = a->peek();

			//push only the current top of "a" to the final solution, mark as visited
			(given->themaze[curr.x][curr.y]).visited = true;
			solution.push(curr);
		}else{

			//you backtrack here, but check first if the final solution is empty, else pop the latest top
			if(solution.empty()){
				break;
			}

			solution.pop();
		}
	}

	//if final solution is not empty, modify the given maze
	//replace '.' with 'x' if that location is specified in the final solution
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
//calls the "tostring()" method of maze "m" then write its result to the specified output file
void mazesolver<T>::writesolution(char* outputfile){
	ofstream file(outputfile, ios::app); //'app' for append
	if(issolved==true){
		file<<"Yey!"<<endl;
	}else{
		file<<"Pfft."<<endl;
	}
	file<<m->tostring();
	file<<endl;
	file.close();
}

//converts a given string to a 2D array of squares
square** stringToSquare2D(string given, int numRows, int numCols){
	square** result;
	result = new square*[numRows]; //alocate memory for rows
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
	char* opfile = "maze.out";
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
			square **currMaze; //stores the current maze, a 2D array of squares
			file>>dimensionRows;
			file>>dimensionCols;

			//read per row of the current maze and store each as a string
			for(int i = 0; i < dimensionRows; i++){
				string st;
				file>>st;
				strToConvertToSquare2D += st;
			}

			//convert string strToConvertToSquare2D to a 2D array of squares thru stringToSquare2D
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
