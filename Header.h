#pragma once
#define CRT_CECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <set>
#include <vector>
#include <string>
using namespace std;
template <class Type>
class Set
{
private: 
    enum { SIZE = 10 };// ������ ��������� �� ���������
    int array_size = 0;// ������ ������ ���������
    int cur_size = 0;
    Type *items = NULL;// �������� ���������
public:
    explicit Set(); //�����������, ��������� ��������� �������� �� ���������
    Set(Type t);//����������� � �����������
    ~Set() //����������
    { 
        delete[] items;
        cout << "Destroying succeeded" << endl;
    }
    void isempty(); //�������� �� �������
    bool push(Type item); //���������� �������� � ���������
    bool pop(Type item); //�������� �������� �� ���������
    void get_size(); //������ ���������
    bool is_in_set(Type item); //�������������� �������� ���������
    friend istream& operator >> (istream& is, Set<Type>& s) //���������� ��������� �����
    {
        Type tmp; //��������� ���������� ��� �����
        int n = 0;
        cout << "How much elements do you want to add? "<< endl;
        is >> n; //������������ ������ ������� ��������� ������
        if (n > 0)
        {
            for (int i = 0; i < n; i++)
            {
                cout << "Enter " << i << " element: ";
                is >> tmp; //��������� � ������� ���������� ��� ������ 
                s.push(tmp); //���������� � ���������
            }
        }
        else
        {
            cout << "Wrong input! "<< endl; //���� �������� ����
        }
        return is;
    }
    friend ostream& operator << (ostream& os, const Set<Type>& s) //��������� ��������� ������
    {
        if (s.cur_size == 0) //���� � ��������� ��� ���������
        {
            os << "Your set is empty" << endl;
            return os;
        }
        else //���� �������� ����, �� ������� ��
        {
            os << "Your set:" << endl;
            for (int i = 0; i < s.cur_size; i++) //���������� ������ �� ���� ��������� ��������� 
            {
                cout << s.items[i] << " ";
            }
            cout << "\n";
            return os;
        }
    }
    Set<Type>& operator=(const Set<Type>& s)
    {
        delete[] items;
        array_size = s.array_size;
        cur_size = s.cur_size;
        items = new Type[array_size];
        for (int i = 0; i < cur_size; i++)
        {
            items[i] = s.items[i];
        }
        return *this;
    }
};
template <class Type>
Set<Type>::Set() //����������� �� ���������
{
    items = new Type[SIZE]; //�������� ������ �� ���������� ��������� �� ���������
    array_size = SIZE; //���������� �� ������� ��������� �������� ������
}
template <class Type>
Set<Type>::Set(Type t)//����������� � ���������� 
{
    items = new Type[1]; //�������� ������ �� 1 �������
    array_size = 1; //���������� �� ������� ��������� �������� ������
    push(t); //���������� ������� � ���������
}
template <class Type>
bool Set<Type>::push(Type item) //���������� ��������� � ���������
{
    for (int i = 0; i < cur_size; i++) //��������� ��� �� �������� ��� � ���������
    {
        if (items[i] == item)// ���� ����, �� �� ��������� ������ ���
        {
            cout << "Element " << item << " is already in the set" << endl;
            return false;
        }
    }
    if (cur_size < array_size) //���� ������ ����������, �� �� ������������, � ������ ����������
    {
        items[cur_size] = item; //���������� ������� � ���������
        cur_size++; //����������� ���������� ���������� ��������� � ���������
        return true;
    }
    else
    {
        Type* tmp = NULL; //������� ��������� ����������
        int numTmp = cur_size + 10; //������������ ������ �� ��� ���������� 1 ��������, � ��� 10 ����
        tmp = new Type[numTmp]; //�������� ������ ��� ��������� ����������, ����� ���������� ���� ������������ ���������
        for (int i = 0; i < cur_size; i++)
        {
            tmp[i] = items[i]; //�������� ������ �� ������� �������
        }
        tmp[cur_size] = item; //���������� ������� � ��������� ���������
        delete[] items; //������ ������
        items = tmp; //����������� 
        cur_size++; //����������� ���������� ���������� ��������� � ���������
        array_size += 10; //����������� ���������� ������ ���������� ������ � ���������
        return true;
    }
}
template <class Type>
bool Set<Type>::pop(Type item) //�������� �������� �� ���������
{
    bool flag = 0;
    for (int i = 0; i < cur_size; i++)
    {
        if (items[i] == item) //���� ������������� ��� �������� ������� ���� � ���������, �� �������� � �������
        {
            for (int j = i + 1; j < cur_size; j++)
                items[j - 1] = items[j];
            cur_size--; //��������� ���������� ���������� ��������� � ���������
            flag = 1; //���� ����, ��� �������������� ��� �������� ������� ������ � ��������� 
            break;
        }
    }
    if (((array_size - cur_size) > 10) && (flag)) //���� ��������� ������ ������, ��� �� 10 ���������, �� ������������
    {
        Type* tmp = NULL; //������� ��������� ����������
        int numTmp = array_size - 10; //������������ ������ �� ��� ���������� 1 ��������, � ��� 10 ����
        tmp = new Type[numTmp]; //�������� ������ ��� ��������� ����������, ����� ���������� ���� ������������ ���������
        for (int i = 0; i < cur_size; i++)
        {
            tmp[i] = items[i]; //�������� ������ �� ������� �������
        }
        delete[] items; //������ ������
        items = tmp; //�����������
        array_size -= 10; //����������� ���������� ������ ���������� ������ � ���������
        return true;
    }
    //���� �������������� �������� ��� � ���������
    if (!flag)
    {
        cout << "\nThere is no element " << item << " in your set, unable to delete" << endl;
        return false;
    }
}
template <class Type>
void Set<Type>::isempty() //�������� �� ������� ���������
{
    if (cur_size == 0) //��������� ������� ��������� ��� �����
    {
        cout << "\nYour set is empty " << endl;
    }
    else
    {
        cout << "\nYour set is NOT empty " << endl;
    }
}
template <class Type>
void Set<Type>::get_size() //������ ���������
{
    //������� ������ ���������
    cout << "\nSet size: " << cur_size << " elements" << endl;
}
template <class Type>
bool Set<Type>::is_in_set(Type item) //�������������� � ���������
{
    for (int i = 0; i < cur_size; i++)
    {
        if (items[i] == item) //���� ������ �������, ������� �������������� ���������
        {
            cout << "\nElement " << item << " found in the set!" << endl;
            return true;
        }
    }
    cout << "\nThere is no element " << item << " in the set" << endl;
    return false;
}