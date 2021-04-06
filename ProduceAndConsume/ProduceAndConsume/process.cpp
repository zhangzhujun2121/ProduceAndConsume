#pragma once
#include "pch.h"
#include "manage.h"
#include"process.h"
#include<string>
process::process(int _type, int _ID)
{
	type = _type;
	ID = _ID;
}

int process::getID()
{
	return ID;
}

void process::sleep()
{
	activity = false;
}

void process::wakeup()
{
	activity = true;
}

string process::update()
{
	string str;
	if (activity)  //是否活动
	{
		if (type == producer)
		{
			str += produce();
			
		}
		else
		{
			str += consume();
		}
	}
	else  //休眠
	{
		if (type == producer)
		{
			str += "生产者";
			str += to_string(ID);
			str += "正在休眠\r\n";

		}
		else
		{
			str += "消费者";
			str += to_string(ID);
			str += "正在休眠\r\n";
		}
	}
	return str;
}

string process::produce()
{

	string str;

	str += "生产者";
	str += to_string(ID);
	str += "正在申请空缓冲区\r\n";
	if (manage::empty.P(ID))  //是否有空缓存区
	{

		str += "生产者";
		str += to_string(ID);
		str += "正在申请进入临界区\r\n";
		if (manage::mutex.P(ID))  //申请临界区
		{
			str += "生产者";
			str += to_string(ID);
			str += "正在执行\r\n";
			deleted = true;   //生产执行完毕 消失
			str += "生产者";
			str += to_string(ID);
			str += "执行完毕！！！\r\n";
			while (manage::full.count < 0)manage::full.V();  //保证下一次能进行有效的V操作
			manage::full.V();
			manage::mutex.V();
		}
	}
	return str;
}

string process::consume()
{
	string str;

	str += "消费者";
	str += to_string(ID);
	str += "正在申请非空缓冲区\r\n";
	if (manage::full.P(ID))
	{
		str += "消费者";
		str += to_string(ID);
		str += "正在申请进入临界区\r\n";
		if (manage::mutex.P(ID))
		{
			str += "消费者";
			str += to_string(ID);
			str += "正在执行\r\n";
			deleted = true; //消费执行完毕消失
			str += "消费者";
			str += to_string(ID);
			str += "执行完毕！！！\r\n";
			while(manage::empty.count<0)manage::empty.V();  //保证下一次能进行有效的V操作
			manage::empty.V();
			manage::mutex.V();
		}
	}
	return str;
}
