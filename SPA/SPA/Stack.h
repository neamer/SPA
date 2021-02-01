#pragma once

#include <iostream>

#include "Node.h"

template <class Type>
class Stack
{
public:
	virtual void Push(const Type& item) = 0;

	virtual Type Pop(const Type& item) = 0;

	virtual Type& Peek() = 0;

	virtual bool IsEmpty() const = 0;

	virtual void Print(std::ostream& stream) = 0;

	virtual int Count() const = 0;

	virtual bool Contains(const Type& item) const = 0;

	friend std::ostream& operator<<(std::ostream& stream, Stack<Type>& list)
	{
		list.Print(stream);
		return stream;
	}
};

template <class Type>
class SeqStack : public Stack<Type>
{
	Type* m_data;
	int m_counter;
	int m_max_size;

	bool IsFull() const
	{
		return m_counter == m_max_size;
	}

	void Expand()
	{
		Type* new_data = new Type[m_max_size * 2];

		for (size_t i = 0; i < m_max_size; i++)
		{
			new_data[i] = m_data[i];
		}

		m_max_size *= 2;

		delete[] m_data;
		m_data = new_data;
	}

public:

	SeqStack() :
		m_counter(0),
		m_max_size(8)
	{
		m_data = new Type[m_max_size];
	}

	virtual void Push(const Type& item) override
	{
		if (IsFull()) Expand();

		m_data[m_counter++] = item;
	}

	virtual Type Pop(const Type& item) override
	{
		if (IsEmpty()) 
			throw std::exception("Unable to pop item from empty stack");

		return m_data[(m_counter--) - 1];
	}

	virtual Type& Peek() override
	{
		return m_data[m_counter - 1];
	}

	virtual bool IsEmpty() const override
	{
		return m_counter == 0;
	}

	virtual void Print(std::ostream& stream) override
	{
		stream << "Sequential Queue object at " << this << std::endl;
		stream << "=======================================TOP\n";
		for (int i = m_counter - 1; i >= 0; i--)
		{
			stream << m_data[i] << std::endl;
		}
		stream << "=======================================BOTTOM\n";
	}

	virtual int Count() const
	{
		return m_counter;
	}

	virtual bool Contains(const Type& item) const
	{
		for (size_t i = 0; i < m_counter; i++)
		{
			if (m_data[i] == item)
				return true;
		}

		return false;
	}

	friend std::ostream& operator<<(std::ostream& stream, SeqStack<Type>& list)
	{
		list.Print(stream);
		return stream;
	}
};

template <class Type>
class LinkedStack : public Stack<Type>
{
	Node<Type>* m_start;
	int m_counter;

public:

	LinkedStack() :
		m_counter(0),
		m_start(nullptr)
	{}

	virtual void Push(const Type& item) override
	{
		if (IsEmpty())
			m_start = new Node<Type>(item, nullptr);
		else
			m_start = new Node<Type>(item, m_start);

		m_counter++;
	}

	virtual Type Pop(const Type& item) override
	{
		if (IsEmpty())
			throw std::exception("Unable to pop item from empty stack");

		Node<Type>* popped_node = m_start;
		Type popped_item = m_start->Item;

		m_start = m_start->Link;
		m_counter--;
		delete popped_node;

		return popped_item;
	}

	virtual Type& Peek() override
	{
		return m_start->Item;
	}

	virtual bool IsEmpty() const override
	{
		return m_start == nullptr;
	}

	virtual void Print(std::ostream& stream) override
	{
		stream << "Linked stack object at " << this << std::endl;
		stream << "====================================TOP\n";

		Node<Type>* traversal = m_start;

		while (traversal != nullptr)
		{
			stream << traversal->Item << std::endl;
			traversal = traversal->Link;
		}
		
		stream << "====================================BOTTOM\n";
	}

	virtual int Count() const
	{
		return m_counter;
	}

	virtual bool Contains(const Type& item) const
	{
		Node<Type>* traversal = m_start;

		while (traversal != nullptr)
		{
			if (traversal->Item == item)
				return true;
			traversal = traversal->Link;
		}

		return false;
	}

	friend std::ostream& operator<<(std::ostream& stream, LinkedStack<Type>& list)
	{
		list.Print(stream);
		return stream;
	}
};

void TestStack()
{
	Stack<int>* stack = new SeqStack<int>;
	Stack<int>* stack2 = new LinkedStack<int>;

	try
	{
		for (size_t i = 0; i < 10; i++)
		{
			stack->Push(i);
			stack2->Push(i);
		}

		std::cout << *stack << std::endl;
		std::cout << *stack2 << std::endl;

		for (size_t i = 0; i < 10; i++)
		{
			stack->Pop(i);
			stack2->Pop(i);
		}

		std::cout << *stack << std::endl;
		std::cout << *stack2 << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		std::system("pause");
	}

}