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
    enum { SIZE = 10 };// размер множества по умолчанию
    int array_size = 0;// храним размер множества
    int cur_size = 0;
    Type *items = NULL;// элементы множества
public:
    explicit Set(); //конструктор, создающий множество размером по умолчанию
    Set(Type t);//конструктор с параметрами
    ~Set() //деструктор
    { 
        delete[] items;
        cout << "Destroying succeeded" << endl;
    }
    void isempty(); //проверка на пустоту
    bool push(Type item); //добавление элемента в множество
    bool pop(Type item); //удаление элемента из множества
    void get_size(); //размер множества
    bool is_in_set(Type item); //принадлежность элемента множеству
    friend istream& operator >> (istream& is, Set<Type>& s) //перегрузка оператора ввода
    {
        Type tmp; //временная переменная для ввода
        int n = 0;
        cout << "How much elements do you want to add? "<< endl;
        is >> n; //пользователь вводит сколько элементов ввести
        if (n > 0)
        {
            for (int i = 0; i < n; i++)
            {
                cout << "Enter " << i << " element: ";
                is >> tmp; //считываем с консоли переменную для записи 
                s.push(tmp); //записываем в множество
            }
        }
        else
        {
            cout << "Wrong input! "<< endl; //если неверный ввод
        }
        return is;
    }
    friend ostream& operator << (ostream& os, const Set<Type>& s) //перегузка оператора вывода
    {
        if (s.cur_size == 0) //если в множестве нет элементов
        {
            os << "Your set is empty" << endl;
            return os;
        }
        else //если элементы есть, то выводим их
        {
            os << "Your set:" << endl;
            for (int i = 0; i < s.cur_size; i++) //проходимся циклом по всем элементам множества 
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
Set<Type>::Set() //конструктор по умолчанию
{
    items = new Type[SIZE]; //выделяем память на количество элементов по умолчанию
    array_size = SIZE; //записываем на сколько элементов выделена память
}
template <class Type>
Set<Type>::Set(Type t)//конструктор с параметами 
{
    items = new Type[1]; //выделяем память на 1 элемент
    array_size = 1; //записываем на сколько элементов выделена память
    push(t); //записываем элемент в множество
}
template <class Type>
bool Set<Type>::push(Type item) //добавление элементов в множество
{
    for (int i = 0; i < cur_size; i++) //проверяем нет ли значения уже в множестве
    {
        if (items[i] == item)// если есть, то не добавляем второй раз
        {
            cout << "Element " << item << " is already in the set" << endl;
            return false;
        }
    }
    if (cur_size < array_size) //если памяти достаточно, то не перевыделяем, а просто записываем
    {
        items[cur_size] = item; //записываем элемент в множество
        cur_size++; //увеличиваем переменную количества элементов в множестве
        return true;
    }
    else
    {
        Type* tmp = NULL; //создаем временную переменную
        int numTmp = cur_size + 10; //перевыделяем память не при добавлении 1 элемента, а для 10 штук
        tmp = new Type[numTmp]; //выделяем память для временной переменной, чтобы скопиовать туда существующее множество
        for (int i = 0; i < cur_size; i++)
        {
            tmp[i] = items[i]; //копируем данные со старого массива
        }
        tmp[cur_size] = item; //записываем элемент в временное множество
        delete[] items; //чистим память
        items = tmp; //присваиваем 
        cur_size++; //увеличиваем переменную количества элементов в множестве
        array_size += 10; //увеличиваем переменную объема выделенной памяти в множестве
        return true;
    }
}
template <class Type>
bool Set<Type>::pop(Type item) //удаление элемента из множества
{
    bool flag = 0;
    for (int i = 0; i < cur_size; i++)
    {
        if (items[i] == item) //если запрашевыемый для удаления элемент есть в множестве, то сдвигаем и удаляем
        {
            for (int j = i + 1; j < cur_size; j++)
                items[j - 1] = items[j];
            cur_size--; //уменьшаем переменную количества элементов в множестве
            flag = 1; //флаг того, что запррашиваемый для удаления элемент найден в множестве 
            break;
        }
    }
    if (((array_size - cur_size) > 10) && (flag)) //если свободной памяти больше, чем на 10 элементов, то перевыделяем
    {
        Type* tmp = NULL; //создаем временную переменную
        int numTmp = array_size - 10; //перевыделяем память не при добавлении 1 элемента, а для 10 штук
        tmp = new Type[numTmp]; //выделяем память для временной переменной, чтобы скопиовать туда существующее множество
        for (int i = 0; i < cur_size; i++)
        {
            tmp[i] = items[i]; //копируем данные со старого массива
        }
        delete[] items; //чистим память
        items = tmp; //присваиваем
        array_size -= 10; //увеличиваем переменную объема выделенной памяти в множестве
        return true;
    }
    //если запрашевыемого элемента нет в множестве
    if (!flag)
    {
        cout << "\nThere is no element " << item << " in your set, unable to delete" << endl;
        return false;
    }
}
template <class Type>
void Set<Type>::isempty() //проверка на пустоту множества
{
    if (cur_size == 0) //проверяем сколько элементов там лежит
    {
        cout << "\nYour set is empty " << endl;
    }
    else
    {
        cout << "\nYour set is NOT empty " << endl;
    }
}
template <class Type>
void Set<Type>::get_size() //размер множества
{
    //выводим размер множества
    cout << "\nSet size: " << cur_size << " elements" << endl;
}
template <class Type>
bool Set<Type>::is_in_set(Type item) //принадлежность к множеству
{
    for (int i = 0; i < cur_size; i++)
    {
        if (items[i] == item) //если найден элемент, выводим соответсвующее сообщение
        {
            cout << "\nElement " << item << " found in the set!" << endl;
            return true;
        }
    }
    cout << "\nThere is no element " << item << " in the set" << endl;
    return false;
}