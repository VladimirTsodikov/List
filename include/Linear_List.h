#pragma once
#include <iostream>

//реализуем циклический список с головой
template <class ValType = int>
class List
{
protected:
	//реализуем внутреннюю структуру ЗВЕНО
	template <class ValType = int>
	struct Node
	{
		ValType data;
		Node<ValType>* next;

		Node() { data = 0; next = NULL;  }	//поле next переопределяется в конструкторе списка и при создании новых звеньев в списке
		Node(ValType tmp) { data = tmp; next = NULL; }
	};

public:
	//реализуем внутренний вспомогательный класс итератор
	class iterator
	{
	private:
		Node<ValType>* current;	//текущий
	public:
		iterator() { current = NULL; }
		iterator(Node<ValType>* tmp) : current(tmp) {}
		iterator(const iterator& iter) { current = iter.current; }

		iterator& operator =(const iterator& other)
		{
			if (this != &other)
				current = other.current;
			return *this;
		}

		iterator& operator ++()		//префиксный ++
		{
			current = current->next;
			return *this;
		}

		Node<ValType>*& operator *()
		{
			return current;
		}

		Node<ValType>* operator ->()
		{
			return current;
		}

		bool operator ==(iterator other)
		{
			return (current == other.current);
		}

		bool operator !=(iterator other)
		{
			return (current != other.current);
		}
	};

protected:
	Node<ValType>* head;
	int count;

public:
	List()	//конструктор по умолчанию
	{
		head = new Node<ValType>();	//только создаём голову
		head->next = head;
		count = 0;
	}
	List(ValType tmp)		//конструктор с параметром
	{
		head = new Node<ValType>();				//создали голову
		head->next = new Node<ValType>(tmp);	//и затем элемент через конструктор звена с параметром
		head->next->next = head;
		count = 1;
	}
	~List()
	{
		//или через итератор - пример далее, функция clear
		Node<ValType> *p = head->next, *tmp;
		while (p != head)
		{
			tmp = p->next;
			delete p;
			p = tmp;
		}
		delete head;
	}

	//функции для удобной работы с циклами
	iterator begin() { iterator tmp(head->next); return tmp; }
	iterator end() { iterator tmp(head); return tmp; }

	void insert(ValType, int position=1);		//вставка элемента типа ValType на определённую позицию, если она существует в списке или является следующей после конца списка
	void erase (int);	//удаление некоторого звена
	void Print();		//распечатка массива
	bool search(ValType);		//проверка наличия элемента (хотя бы одного) в списке
	bool empty() { return (head->next == head); }	//проверка на пустоту
	ValType front();	//возвращает первое значение в списке (сразу за головой)
	void clear();	//очистка списка (останется только голова)
	int GetCount() { return count; }	//возвращает количество элементов (звеньев) в списке
};

template <class ValType>		//вставка элемента типа ValType на определённую позицию, если она существует в списке или является следующей после конца списка
void List<ValType>::insert(ValType DataTmp, int position=1)
{
	if (position == 1)
	{
		Node<ValType>* tmp = new Node<ValType>(DataTmp);
		tmp->next = head->next;
		head->next = tmp;
		count++;
	}
	else if (position > 1 && position <= count + 1)
	{
		int i = 1;
		List<ValType>::iterator it = begin();
		while (i < position - 1)
		{
			++it;
			i++;
		}
		Node<ValType>* tmp = new Node<ValType>(DataTmp);
		tmp->next = it->next;
		it->next = tmp;
		count++;
	}
	else throw "Incorrect position";
}

template <class ValType>
void List<ValType>::erase(int position)
{
	if (position == 1)
	{
		Node<ValType>* tmp = head->next;
		head->next = tmp->next;
		delete tmp;
		count--;
	}
	else if (position > 1 && position <= count)
	{
		int i = 1;
		List<ValType>::iterator it = begin();
		while (i < position - 1)
		{
			++it;
			i++;
		}
		Node<ValType>* tmp = it->next;
		it->next = tmp->next;
		delete tmp;
		count--;
	}
	else throw "Incorrect position";
}

template <class ValType>
void List<ValType>::Print()
{
	/*Node<ValType>* p = head->next;
	while (p != head)
	{
		std::cout << p->data << std::endl;
		p = p->next;
	}*/
	for (List<ValType>::iterator it = begin(); it != end(); ++it)
		std::cout << it->data << std::endl;
}
template <class ValType>
bool List<ValType>::search(ValType Search_Value)
{
	bool flg = false;
	List<ValType>::iterator it = begin();
	while (it != end())
	{
		if (it->data == Search_Value)
		{
			flg = true; 
			break;
		}	
		else ++it;
	}
	return flg;
}

template <class ValType>
ValType List<ValType>::front()
{
	if (!empty())
		return (head->next->data);	//у следуюзего за головой звена возвращаем поле data
	else throw "List is empty";
}

template <class ValType>
void List<ValType>::clear()
{
	while (!empty())
		erase(1);
	count = 0;
}