#include<iostream>
#include<vector>
using namespace std;

void getseq(const id, , , vector<int>& color){



}


void send(int v,int id){
	unit16_t datalen = 3 * _nLEDs[id] + 2 ;
	char buf[dataLen] = {0};



}


bool sendtostrip(int id, vector<int>& color){
	if( id > 4 ) return false;
	if( color.size() > 3 * id + 2 ) return false;
	for(i=0;i<color.size();i++)
		send(color[i],id);
        return 1;  
}

