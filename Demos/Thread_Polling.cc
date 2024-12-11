#include<iostream>
using namespace std;

vector<bool> threadStatus;
vector<int> jobID;
bool isDone = false;

void mainThreadFunction(){
	for(int i = 0; i < MAX; ++i){
		cout << "creates a new task" << endl;

		m_mutex.lock();

		unsigned int j;
		for(j=0;j<threadStatues.size();j++){
			if(!threadStatus.at(j)){
				break;
			}
		}
		if(){}
		else{}
	}
}

void threadCallback(int x, std::string str){
	while(!isDone){
		if(!threadStatus.at(x)){
			usleep(50);
			continue;
		}
		m_mutex.lock();
		cout <<"I am working on job " << jobID << endl;
		//processJob(jobID);
		threadStatus.at(i) = false;
		m_mutex.unlock();
	}
}

int main(){
	string str = "thread";

	for(int i = 0; i<10; i++){
		vts.push_back(thread(threadCallback, i, str));
	}
}
