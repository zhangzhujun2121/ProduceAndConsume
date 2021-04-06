#pragma once
#include<vector>
#include"process.h"
#include<queue>
#include<string>
#include<iostream>
using namespace std;
#define producer 1
#define consumer  2

static class manage;
struct Semaphore;

// 进程管理
static class manage
{
private:

	static vector<process*> vec;

public:
	
	static int N; //信号量个数
	static Semaphore empty; //空缓存区  N
	static Semaphore full;  //满缓存区  0
	static Semaphore mutex; //互斥信号量
	static void creatProcess(int _type,int _ID);  //添加消费者或者生产者
	static void sleep(int ID); 
	static void wakeup(int ID);
	static string update();
};

struct Semaphore
{
	int count;
	queue<int> qu;
	Semaphore(int n)
	{
		count = n;
	}
	bool P(int id)   
	{
		count--;  
		if (count < 0)  
		{
			qu.push(id);
			manage::sleep(id);
			return false;
		}
		return true;
	}
	void V()
	{
		count++;
		if (count <= 0) 
		{
			manage::wakeup(qu.front());
			qu.pop();
		}
	}
};