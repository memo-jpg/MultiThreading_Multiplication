#include<iostream>
#include<thread>
#include<>
using namespace std::placeholders;

class Application{
private:
	//

public:
	void mainTask(){
		std::cout << "Do Some handshaking " << std::endl;
			//Acquire the lock
		std::unique_lock<std::mutex> mlock(m_mutex);
			//Start waiting for the Condition Variable to get signaled
			//Wait() will internally release the Lock and make the thread to block
			//As soon as CV get signaled, resume the thread and
			//again acquire the Lock. Then check if condition is met or not
			//If condition is met then continue else again go in wait
		m_condVar.wait(mlock, std::bind(&Application::isDataLoaded, this));


	}

}; //end of class Application
 


int main(){

}
