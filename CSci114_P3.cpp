//Guillermo Prado
//execute program by typing into command line:
	// ./a [int] [int] [int]
//the integers entered represent the size of the matrices to be

//By default, the strings are set for 'A.txt' & 'B.txt'
	//If you want to pass files in with different names, change the according strings.

//compile with 'g++ -pthread program_name.cpp'
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<thread>
#include<mutex>
using namespace std;

int a,b,c;
mutex mt;

void readIn(vector<vector<int>>&matrix, string &text){ //takes in a 2-D Array, and the textFile
	mt.lock();
	ifstream inFile(text);
	int i=0, j=0;
	while(!inFile.eof()){
		//Reading each line one at a time.
		string s;
		getline(inFile, s); 
		if(!inFile) break;
		if(j >= matrix[i].size()){ i++; j= 0;} //when reach the end of the line (should corrrelate with the file)
								   //set row back to beginning
		for(int k = 0; k < s.size(); k += 2){	
		matrix[i][j] = s[k] - '0'; //char -> integer 
		j++;
		}
	}	
	inFile.close(); 	
	mt.unlock();
}

void printMatrix(vector<vector<int>>&s, int &size1, int &size2){
	for(int i=0; i < size1; i++){
		for(int j=0; j < size2; j++){
			cout << s[i][j] << " ";
		}
		cout << endl;
	}

}

void matrixMult(vector<vector<int>>&A, vector<vector<int>>&B, vector<vector<int>>&C, int col, int row){
	mt.lock();
	int rowA = A.size(), rowB = B.size();
	int colA = A[0].size(), colB = B[0].size();

	if(colA != rowB) throw std::invalid_argument("Matricies cannot be multiplied: columns of Matrix A MUST be EQUAL to rows of Matrix B");

	//
	for(int k = 0; k < colA; k++){
		C[col][row] += A[col][k] * B[k][row];
	}

	mt.unlock();

}

int main(int argc, char* argv[]){
	a = atoi(argv[1]),b = atoi(argv[2]),c = atoi(argv[3]);

	vector<vector<int>> matrixA(a, vector<int> (b)); //same as making array[a][b] 
	vector<vector<int>> matrixB(b,vector<int>(c));; //array[b][c]
	vector<vector<int>> matrixC(a, vector<int>(c)); //array[a][c]
	string A = "A.txt", B = "B.txt";
	
	thread threadObj(readIn, std::ref(matrixA), std::ref(A)); //creates a thread to read in 'A.txt'
	thread threadObj2(readIn, std::ref(matrixB), std::ref(B)); //creates a thread to read in 'B.txt'

	threadObj.join();
	threadObj2.join();


//Multi-thread Matrix Multiply
	thread myThread[a][c];
	for(int i = 0; i < a; i++){
		for(int j = 0; j < c; j++){
			myThread[i][j] = thread( matrixMult, ref(matrixA), ref(matrixB), ref(matrixC),i, j ); 
		}
	}
	//Join threads to ensure all threads complete before proceeding
	for(int i = 0; i < a; i++){
		for(int j = 0; j < c; j++){
			myThread[i][j].join(); 
		}
	}

	printMatrix(matrixC, a, c);

}
