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
	if (activity)  //�Ƿ�
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
	else  //����
	{
		if (type == producer)
		{
			str += "������";
			str += to_string(ID);
			str += "��������\r\n";

		}
		else
		{
			str += "������";
			str += to_string(ID);
			str += "��������\r\n";
		}
	}
	return str;
}

string process::produce()
{

	string str;

	str += "������";
	str += to_string(ID);
	str += "��������ջ�����\r\n";
	if (manage::empty.P(ID))  //�Ƿ��пջ�����
	{

		str += "������";
		str += to_string(ID);
		str += "������������ٽ���\r\n";
		if (manage::mutex.P(ID))  //�����ٽ���
		{
			str += "������";
			str += to_string(ID);
			str += "����ִ��\r\n";
			deleted = true;   //����ִ����� ��ʧ
			str += "������";
			str += to_string(ID);
			str += "ִ����ϣ�����\r\n";
			while (manage::full.count < 0)manage::full.V();  //��֤��һ���ܽ�����Ч��V����
			manage::full.V();
			manage::mutex.V();
		}
	}
	return str;
}

string process::consume()
{
	string str;

	str += "������";
	str += to_string(ID);
	str += "��������ǿջ�����\r\n";
	if (manage::full.P(ID))
	{
		str += "������";
		str += to_string(ID);
		str += "������������ٽ���\r\n";
		if (manage::mutex.P(ID))
		{
			str += "������";
			str += to_string(ID);
			str += "����ִ��\r\n";
			deleted = true; //����ִ�������ʧ
			str += "������";
			str += to_string(ID);
			str += "ִ����ϣ�����\r\n";
			while(manage::empty.count<0)manage::empty.V();  //��֤��һ���ܽ�����Ч��V����
			manage::empty.V();
			manage::mutex.V();
		}
	}
	return str;
}
