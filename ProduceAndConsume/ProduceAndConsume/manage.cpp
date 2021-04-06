#pragma once
#include "pch.h"
#include "manage.h"

void manage::creatProcess(int _type,int _ID)
{
	process* tmp = new process(_type,_ID);
	vec.push_back(tmp);
}

void manage::sleep(int ID)
{
	for (auto it : vec)
	{
		if (it->getID() == ID)
		{
			it->sleep();
		}
	}
}

void manage::wakeup(int ID)
{
	for (auto it : vec)
	{
		if (it->getID() == ID)
		{
			it->wakeup();
		}
	}
}

string manage::update()
{
	string str;
	std::string s;
	for (auto it = vec.begin(); it != vec.end();)
	{
		if ((*it)->deleted)  //已经执行完毕的 删除
		{
			delete(*it);
			it=vec.erase(it);  
			
		}
		else
		{
			s=(*it)->update();
			str += s;
			it++;
		}
	}
	return str;
}
