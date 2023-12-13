#pragma once

#include <iostream>
using namespace std;

template <class T>
class MyStack
{
	T* data;
	int capacity;
	int topNum;
public:
	MyStack(int i = 50);
	bool push(T item);
	T top();
	void pop();
	int size();
	bool isEmpty();
	void clear();
	void print();
	~MyStack();
};

template <class T>
void MyStack<T>::print()
{
	for (int i = 0; i < topNum; i++)
	{
		if (i != 0)
		{
			cout << ", ";
		}
		cout << data[i];
	}
	cout << endl;
}
template <class T>
MyStack<T>::MyStack(int i)
{
	data = new T[i];
	capacity = i;
	topNum = 0;
}

template <class T>
MyStack<T>::~MyStack()
{
	topNum = 0;
	capacity = 0;
	delete[] data;
}

template <class T>
void MyStack<T>::clear()
{
	topNum = 0;
}

template <class T>
bool MyStack<T>::push(T item)
{
	if (topNum != capacity)
	{
		data[topNum] = item;
		topNum++;
		return true;
	}
	return false;
}

template <class  T>
T  MyStack<T>::top()
{
	if (topNum > 0)
	{
		return data[topNum - 1];
	}
	return 0;
}

template <class  T>
void  MyStack<T>::pop()
{
	
	if (topNum > 0)
	{
		topNum--;
	}
}

template <class T>
int MyStack<T>::size()
{
	return topNum;
}

template <class T>
bool MyStack<T>::isEmpty()
{
	cout<< topNum << endl;
	return topNum == 0;
}