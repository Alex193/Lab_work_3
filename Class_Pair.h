#pragma once
#include <iostream>
using namespace std;
class Pair
{
private:
	int int_num; //îáúÿâèëè öåëî÷èñëåííóþ ïåðåìåííóþ 
	double double_num; //îáúÿâèëè ïåðåìåííóþ òèïà double
public:
	explicit Pair() : int_num(0), double_num(0) {} //êîíñòðóêòîð áåç ïàðàìåòðîâ
	Pair(const int a, const double b) //êîíñòðóêòîð ñ ïàðàìåòðàìè
	{
		int_num = a;
		double_num = b;
	}
	friend istream& operator>> (istream& in, Pair& numbers) //ïåðåãðóçêà îïðåðàòîðà ââîäà
	{
		cout << "Ââîä ÷èñåë êëàññà Pair" << endl;
		cout << "Ââåäèòå ÖÅËÎÅ ÷èñëî: ";
		in >> numbers.int_num; //ñ÷èòûâàåì öåëîå ÷èñëî
		cout << "Ââåäèòå ÂÅÙÅÑÒÂÅÍÍÎÅ ÷èñëî: ";
		in >> numbers.double_num; //ñ÷èòûâàåì âåùåñòâåííîå ÷èñëî
		return in;
	}
	friend ostream& operator<< (ostream& out, const Pair& numbers) //ïåðåãðóçêà îïðåðàòîðà âûâîäà
	{
		out << numbers.int_num << ":" << numbers.double_num;
		return out;
	}
	bool operator== (const Pair& numbers) const //ïåðåãðóçêà îïðåðàòîðà ñðàâíåíèÿ ==
	{
		return (int_num == numbers.int_num) && (double_num == numbers.double_num);
	}
	bool operator!= (const Pair& numbers) const //ïåðåãðóçêà îïðåðàòîðà ñðàâíåíèÿ !=
	{
		return !((int_num == numbers.int_num) && (double_num == numbers.double_num));
	}
	Pair& operator= (const Pair& numbers) //ïåðåãðóçêà îïåðåàòîðà ïðèñâàèâàíèÿ
	{
		if (this == &numbers) //åñëè ýëåìåíòû ðàâíû, âîçâðàùàåì òåêóùèé
		{
			return *this;
		}
		int_num = numbers.int_num;
		double_num = numbers.double_num;
		return *this;
	}
	~Pair() { }
};
