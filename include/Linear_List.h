#pragma once
#include <iostream>

//реализуем циклический список с головой
template <class ValType = int>
class List
{
protected:
	//реализуем внутреннюю структуру ЗВЕНО
	struct Node
	{
		ValType data;
		Node* next;

		Node() { data = 0; next = NULL;  }	//поле next переопределяется в конструкторе списка и при создании новых звеньев в списке
		Node(ValType tmp) { data = tmp; next = NULL; }
	};

public:
	//реализуем внутренний вспомогательный класс итератор
	class iterator
	{
	private:
		Node* current;	//текущий
	public:
		iterator() { current = NULL; }
		iterator(Node* tmp) : current(tmp) {}
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

		Node*& operator *()
		{
			return current;
		}

		Node* operator ->()
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
	Node* head;
	int count;

public:
	List()	//конструктор по умолчанию
	{
		head = new Node();	//только создаём голову
		head->next = head;
		count = 0;
	}
	List(ValType tmp)		//конструктор с параметром
	{
		head = new Node();				//создали голову
		head->next = new Node(tmp);	//и затем элемент через конструктор звена с параметром
		head->next->next = head;
		count = 1;
	}
	~List()
	{
		//или через итератор - пример далее, функция clear
		Node *p = head->next, *tmp;
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
	/*iterator end() { 
		iterator tmp(head);
		while (tmp->next != head) ++tmp;
		return tmp;
	}*/

	void insert(const ValType& DataTmp, int position=1);		//вставка элемента типа ValType на определённую позицию за O(n), если она существует в списке или является следующей после конца списка
	void insert(const ValType& DataTmp, Node* position);	//вставка элемента после некоторого элемента, на который получили указатель, за O(1)
	void erase (int position);	//удаление некоторого звена с заданной позицией за O(n)
	void erase(Node* position);	//удаление звена после некоторого звена, на который получили указатель, за O(1)
	void Print();		//распечатка массива
	bool search(ValType);		//проверка наличия элемента (хотя бы одного) в списке
	bool empty() { return (head->next == head); }	//проверка на пустоту		//или return (count==0)
	ValType front();	//возвращает первое значение в списке (сразу за головой)
	void clear();	//очистка списка (останется только голова)
	int GetCount() { return count; }	//возвращает количество элементов (звеньев) в списке
};

template <class ValType>		//вставка элемента типа ValType на определённую позицию, если она существует в списке или является следующей после конца списка
void List<ValType>::insert(const ValType& DataTmp, int position=1)
{
	if (position == 1)
	{
		Node* tmp = new Node(DataTmp);
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
		Node* tmp = new Node(DataTmp);
		tmp->next = it->next;
		it->next = tmp;
		count++;
	}
	else throw "Incorrect position";
}

//вставка нового звена списка будет производиться ПОСЛЕ звена position
template <class ValType>
void List<ValType>::insert(const ValType& DataTmp, Node* position)
{
	Node* tmp = new Node(DataTmp);
	tmp->next = position->next;
	position->next = tmp;
	count++;
}

template <class ValType>
void List<ValType>::erase(int position)
{
	if (position == 1)
	{
		Node* tmp = head->next;
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
		Node* tmp = it->next;
		it->next = tmp->next;
		delete tmp;
		count--;
	}
	else throw "Incorrect position";
}

template <class ValType>
void List<ValType>::erase(Node* position)
{
	if (position->next != head)
	{
		Node* tmp = position->next;
		position->next = tmp->next;
		delete tmp;
		count--;
	}
	else throw "Pointer to last Node";
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
		return (head->next->data);	//у следующего за головой звена возвращаем поле data
	else throw "List is empty";
}

template <class ValType>
void List<ValType>::clear()
{
	while (!empty())
		erase(1);
	count = 0;
}