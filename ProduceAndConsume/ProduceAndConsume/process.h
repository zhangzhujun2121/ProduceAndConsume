#pragma once
#include<string>
using namespace std;
class process;
//�����������߽���
class process
{
private:
	int ID;
	bool activity = true;
	int type;
public:
	bool deleted=false;
	process(int _type,int _ID);
	int getID();
	void sleep();
	void wakeup();
	string update();
	string consume();
	string produce();
};

