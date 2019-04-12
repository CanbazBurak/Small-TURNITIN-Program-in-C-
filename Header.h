#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include<string>

using namespace std;
template<class T>
struct node
{
	T info;
	node<T> *link;
};

template<class T>
class LinkList
{
public:
	node<T>  *head, *last;
	int count;

	LinkList();
	~LinkList();
	bool emptyList();
	int lenght();
	T back();
	T front();
	void destroyList();
	node<T> *search(T &);
	void insertFirst(T &);
	void insertLast(T &);
	void deleteNode(T &);



	friend ostream& operator<<(ostream& os, LinkList<T> &val)
	{
		node<T> *p = val.head;
		while (p != NULL)
		{
			os << p->info << endl;
			p = p->link;
		}

		return os;
	}
};


template<class T>
LinkList<T>::LinkList()
{
	head = last = NULL;
	count = 0;
}

template<class T>
LinkList<T>::~LinkList()
{
	destroyList();
}

template<class T>
bool LinkList<T>::emptyList()
{
	return head == NULL;
}

template<class T>
int LinkList<T>::lenght()
{
	return count;
}

template<class T>
T LinkList<T>::back()
{
	assert(last != NULL);
	return last->info;
}

template<class T>
T LinkList<T>::front()
{
	assert(head != NULL);
	return head->info;
}

template<class T>
void LinkList<T>::destroyList()
{
	node<T> *p;
	while (head != NULL)
	{
		p = head;
		head = head->link;
		delete p;
	}
	last = NULL;
	count = 0;
}

template<class T>
node<T>* LinkList<T>::search(T & val)
{
	bool found = false;
	node<T> *p = head;
	while (p != NULL && !found)
	{
		if (p->info == val)
			found = true;
		else
			p = p->link;
	}
	return p;
}


template<class T>
void LinkList<T>::insertFirst(T & val)
{
	node<T> *p = new node<T>;
	p->info = val;
	p->link = head;
	head = p;
	count++;
	if (last == NULL)
	{
		last = p;
	}
}

template<class T>
void LinkList<T>::insertLast(T & val)
{
	node<T> *p = new node<T>;
	p->info = val;
	p->link = NULL;
	if (head != NULL)
	{
		last->link = p;
		last = p;
	}
	else
		head = last = p;
	count++;

}
template<class T>
void LinkList<T>::deleteNode(T & val)
{
	node<T> *p, *q;
	bool found = false;
	if (head == NULL)
	{
		cerr << "List is empty";
	}
	else
	{
		if (head->info == val)
		{
			p = head;
			head = head->link;
			delete p;
			count--;
			if (head == NULL)
				last = NULL;
		}
		else
		{
			p = head;
			q = head->link;
			while (q != NULL && !found)
			{
				if (q->info == val)
					found = true;
				else
				{
					p = q;
					q = q->link;
				}
			}
			if (found)
			{
				p->link = q->link;
				count--;
				if (q == last)
				{
					last = p;
				}
				delete q;
			}
		}
	}
}
