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

// ���̹���
static class manage
{
private:

	static vector<process*> vec;

public:
	
	static int N; //�ź�������
	static Semaphore empty; //�ջ�����  N
	static Semaphore full;  //��������  0
	static Semaphore mutex; //�����ź���
	static void creatProcess(int _type,int _ID);  //��������߻���������
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