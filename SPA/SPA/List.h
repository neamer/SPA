#pragma once

#include<iostream>

#include "Node.h"

template <class Type>
class List
{
public:
	virtual void Add(const Type& item) = 0;

	virtual Type Remove(const Type& item) = 0;

	virtual bool IsEmpty() const = 0;

	virtual Type& operator[](int index) = 0;

	virtual Type& Get(int index) = 0;

	virtual void Set(int index, const Type& item) = 0;

	virtual void Print(std::ostream& stream) = 0;

	virtual int Count() const = 0;

	virtual bool Contains(const Type& v) const = 0;

	virtual Type* ToArray() const = 0;

	friend std::ostream& operator<<(std::ostream& stream, List<Type>& list)
	{
		list.Print(stream);
		return stream;
	}
};

template <class Type>
class SeqList : public List<Type>
{
	Type* m_data;
	int m_counter;
	int m_max_size;

	bool IsFull() const
	{
		return m_counter == m_max_size;
	}

	void ShiftLeftFrom(int index)
	{
		for (size_t i = index; i < m_counter - 1; i++)
		{
			m_data[i] = m_data[i + 1];
		}
		m_counter--;
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

	bool OutOfBounds(int index) const
	{
		return index >= m_counter || index < 0;
	}

public:
	SeqList() :
		m_max_size(8),
		m_counter(0)
	{
		m_data = new Type[m_max_size];
	}

	virtual void Add(const Type& item) override
	{
		if (IsFull()) Expand();

		m_data[m_counter++] = item;
	}

	virtual Type Remove(const Type& item) override
	{
		if (IsEmpty()) throw std::exception("Unable to remove item from empty list!");

		for (size_t i = 0; i < m_counter; i++)
		{
			if (m_data[i] == item)
			{
				Type return_val = m_data[i];
				ShiftLeftFrom(i);
				return return_val;
			}
		}

		throw std::exception("Item was not found in the list!");
	}

	virtual bool IsEmpty() const override
	{
		return m_counter == 0;
	}

	virtual Type& operator[](int index) override
	{
		return Get(index);
	}

	virtual Type& Get(int index) override
	{
		if (OutOfBounds(index))
			throw std::exception("Error while accessing operator [], index was out of bounds!");

		return m_data[index];
	}

	virtual void Set(int index, const Type& item) override
	{
		Get(index) = item;
	}

	virtual void Print(std::ostream& stream) override
	{
		stream << "Sequential list object at " << this << std::endl;
		stream << "==========================================\n";
		for (size_t i = 0; i < m_counter; i++)
		{
			stream << "[" << i << "] = " << m_data[i] << std::endl;
		}
		stream << "==========================================\n";
	}

	virtual int Count() const override
	{
		return m_counter;
	}

	virtual bool Contains(const Type& item) const override
	{
		for (size_t i = 0; i < m_counter; i++)
		{
			if (m_data[i] == item)
				return true;
		}

		return false;
	}

	virtual Type* ToArray() const override
	{
		Type* result = new Type[m_counter];

		for (size_t i = 0; i < m_counter; i++)
		{
			result[i] = m_data[i];
		}

		return result;
	}

	friend std::ostream& operator<<(std::ostream& stream, SeqList<Type>& list)
	{
		list.Print(stream);
		return stream;
	}
};

template <class Type>
class LinkedList : public List<Type>
{
	Node<Type>* m_start;
	Node<Type>* m_end;
	int m_counter;

	bool OutOfBounds(int index) const
	{
		return index >= m_counter || index < 0;
	}

public:
	LinkedList() :
		m_counter(0),
		m_start(nullptr),
		m_end(nullptr)
	{}

	virtual void Add(const Type& item) override
	{
		if (IsEmpty())
		{
			m_start = new Node<Type>(item, nullptr);
			m_end = m_start;
		}
		else
		{
			m_end->Link = new Node<Type>(item, nullptr);
			m_end = m_end->Link;
		}

		m_counter++;
	}

	virtual Type Remove(const Type& item) override
	{
		if (IsEmpty()) throw std::exception("Unable to remove item from empty list!");

		if (m_start->Item == item)
		{
			Node<Type>* old_start = m_start;
			m_start = m_start->Link;

			Type return_val = old_start->Item;
			delete old_start;
			m_counter--;

			return return_val;
		}
		
		Node<Type>* traversal = m_start;

		while (traversal->Link != nullptr)
		{
			if (traversal->Link->Item == item)
			{
				Node<Type>* prev = traversal;
				Node<Type>* item_node = traversal->Link;

				prev->Link = item_node->Link;

				Type return_val = item_node->Item;
				delete item_node;
				m_counter--;

				return return_val;
			}
			traversal = traversal->Link;
		}

		throw std::exception("Item was not found in the list!");
	}

	virtual bool IsEmpty() const override
	{
		return m_start == nullptr;
	}

	virtual Type& operator[](int index) override
	{
		return Get(index);
	}

	virtual Type& Get(int index) override
	{
		if (OutOfBounds(index))
			throw std::exception("Error while accessing operator [], index was out of bounds!");

		Node<Type>* traversal = m_start;

		for (size_t i = 0; i < index; i++)
		{
			traversal = traversal->Link;
		}

		return traversal->Item;
	}

	virtual void Set(int index, const Type& item) override
	{
		Get(index) = item;
	}

	virtual void Print(std::ostream& stream) override
	{
		stream << "Linked list object at " << this << std::endl;
		stream << "======================================\n";
		for (size_t i = 0; i < m_counter; i++)
		{
			stream << "[" << i << "] = " << Get(i) << std::endl;
		}
		stream << "======================================\n";
	}

	virtual int Count() const override
	{
		return m_counter;
	}

	virtual bool Contains(const Type& item) const override
	{
		Node<Type>* traversal = m_start;

		for (size_t i = 0; i < m_counter; i++)
		{
			if (traversal->Item == item)
				return true;
			traversal = traversal->Link;
		}

		return false;
	}

	virtual Type* ToArray() const override
	{
		Type* result = new Type[m_counter];

		Node<Type>* traversal = m_start;

		for (size_t i = 0; i < m_counter; i++)
		{
			result[i] = traversal->Item;
			traversal = traversal->Link;
		}

		return result;
	}

	friend std::ostream& operator<<(std::ostream& stream, LinkedList<Type>& list)
	{
		list.Print(stream);
		return stream;
	}
};

void ListTest()
{
	List<int>* list = new SeqList<int>;
	List<int>* list2 = new LinkedList<int>;

	try
	{
		for (size_t i = 0; i < 10; i++)
		{
			list->Add(i);
			list2->Add(i);
		}

		std::cout << *list << std::endl;
		std::cout << *list2 << std::endl;

		for (size_t i = 0; i < 10; i++)
		{
			list->Remove(i);
			list2->Remove(i);
		}

		std::cout << *list << std::endl;
		std::cout << *list2 << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		std::system("pause");
	}

}