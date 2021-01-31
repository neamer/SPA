#pragma once

#include "Node.h"

template <class Type>
class List
{
public:
	virtual void Add(const Type& item) = 0;

	//virtual Type Remove(const Type& item) = 0;

	//virtual bool IsEmpty() = 0;

	//virtual Type& operator[](int index) = 0;

	//virtual Type& Get(int index) = 0;

	//virtual void Set(int index, const Type& item) = 0;

	//virtual int Count() = 0;

	//virtual bool Contains(const Type& v) = 0;

	//virtual Type* ToArray() = 0;
};

template <class Type>
class SequentialList : public List<Type>
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
			m_data[i] = new_data[i];
		}

		m_max_size *= 2;

		delete[] m_data;
		m_data = new_data;
	}

public:
	SequentialList() :
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

	//virtual Type Remove(const Type& item) = 0;

	//virtual bool IsEmpty() = 0;

	//virtual Type& operator[](int index) = 0;

	//virtual Type& Get(int index) = 0;

	//virtual void Set(int index, const Type& item) = 0;

	//virtual int Count() = 0;

	//virtual bool Contains(const Type& v) = 0;

	//virtual Type* ToArray() = 0;
};

void TestListInt()
{
	List<int>* list = new SequentialList<int>;

	for (size_t i = 0; i < 10; i++)
	{
		list->Add(i);
	}
}