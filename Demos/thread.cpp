#include <iostream>
#include <string>
#include<thread>
using namespace std;

void thread_function(int n, string s){
	for(int i =0; i<n; i++){
		//cout<< i <<"thread fucntion Executing " << s <<endl; //not atomic
		printf("%d thread function Executing %s \n",i,s.c_str());

	}
}

int main(){
	std::thread threadObj(thread_function, 100, "happily!");
	for(int i = 0; i<10; i++){
		printf("Display from MainThread\n");
		//std::cout << "Display from MainThread" << std::endl;
	}
	threadObj.join();
	std::cout << "Exit from MainThread" << std::endl;
	return 0;
}
