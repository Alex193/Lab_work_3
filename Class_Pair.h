#pragma once
#include <iostream>
using namespace std;
class Pair
{
private:
	int int_num; //�������� ������������� ���������� 
	double double_num; //�������� ���������� ���� double
public:
	explicit Pair() : int_num(0), double_num(0) {} //����������� ��� ����������
	Pair(const int a, const double b) //����������� � �����������
	{
		int_num = a;
		double_num = b;
	}
	friend istream& operator>> (istream& in, Pair& numbers) //���������� ���������� �����
	{
		cout << "���� ����� ������ Pair" << endl;
		cout << "������� ����� �����: ";
		in >> numbers.int_num; //��������� ����� �����
		cout << "������� ������������ �����: ";
		in >> numbers.double_num; //��������� ������������ �����
		return in;
	}
	friend ostream& operator<< (ostream& out, const Pair& numbers) //���������� ���������� ������
	{
		out << numbers.int_num << ":" << numbers.double_num;
		return out;
	}
	bool operator== (const Pair& numbers) const //���������� ���������� ��������� ==
	{
		return (int_num == numbers.int_num) && (double_num == numbers.double_num);
	}
	bool operator!= (const Pair& numbers) const //���������� ���������� ��������� !=
	{
		return !((int_num == numbers.int_num) && (double_num == numbers.double_num));
	}
	Pair& operator= (const Pair& numbers) //���������� ���������� ������������
	{
		if (this == &numbers) //���� �������� �����, ���������� �������
		{
			return *this;
		}
		int_num = numbers.int_num;
		double_num = numbers.double_num;
		return *this;
	}
	~Pair() {}
};
