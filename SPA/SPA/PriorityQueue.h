#pragma once

#include <iostream>

#include "Node.h";

template <class Type>
class PriorityQueue
{
public:
	virtual void Push(Type item) = 0;
	virtual Type Pop() = 0;
	virtual Type& Peek() = 0;
	virtual bool IsEmpty() = 0;
	virtual void Print(std::ostream& stream) = 0;

	friend std::ostream& operator<<(std::ostream& stream, PriorityQueue<Type>& obj)
	{
		obj.Print(stream);
		return stream;
	}
};

template <class Type>
class SeqPriorityQueue : public PriorityQueue<Type>
{
	/*
		Sekvencijalni prioritetni red ćemo koristiti kao primjer
		nesortiranog prioritetnog reda. Kada je red nesortiran
		to znači da će funkcija dodavanja biti u konstantnom
		vremenu jer nam nije bitno gdje dodajemo element.
		U suprotnom, element koji se treba ukloniti iz reda
		nam nije poznat i moramo pregledati sadrzaj reda da
		ga nađemo.

		SeqPriorityQueue::Push(item) - O(1)
		SeqPriorityQueue::Pop(item) - O(n)
	*/

	Type* m_data;
	int m_counter;
	int m_max_size;

	bool IsFull() const
	{
		return m_counter == m_max_size;
	}

	void Expand()
	{
		Type* new_data = new Type[int(m_max_size * 2)];

		for (size_t i = 0; i < m_max_size; i++)
		{
			new_data[i] = m_data[i];
		}

		m_max_size *= 2;

		delete[] m_data;
		m_data = new_data;
	}

public:

	SeqPriorityQueue() :
		m_counter(0),
		m_max_size(8)
	{
		m_data = new Type[m_max_size];
	}

	virtual void Push(Type item) override
	{
		if (IsFull()) Expand();

		m_data[m_counter++] = item;
	}

	virtual Type Pop() override
	{
		if (IsEmpty()) throw std::exception("Unable to pop item from empty priority queue!");

		Type max_item = m_data[0];
		int max_index = 0;

		for (size_t i = 0; i < m_counter; i++)
		{
			if (max_item < m_data[i])
			{
				max_item = m_data[i];
				max_index = i;
			}
		}

		Type return_val = max_item;
		m_data[max_index] = m_data[m_counter - 1];
		m_counter--;

		return return_val;
	}

	virtual Type& Peek() override
	{
		if (IsEmpty()) throw std::exception("Unable to pop item from empty priority queue!");

		Type& lowest_item = m_data[0];

		for (size_t i = 0; i < m_counter; i++)
		{
			if (lowest_item > m_data[i])
			{
				lowest_item = m_data[i];
			}
		}

		return lowest_item;
	}

	virtual bool IsEmpty() override
	{
		return m_counter == 0;
	}

	virtual void Print(std::ostream& stream) override
	{
		stream << "Sequential Pr. Queue object at " << this << std::endl;
		stream << "=======================================START\n";
		for (int i = 0; i < m_counter; i++)
		{
			stream << m_data[i] << std::endl;
		}
		stream << "=======================================END\n";
	}

	friend std::ostream& operator<<(std::ostream& stream, SeqPriorityQueue<Type>& obj)
	{
		obj.Print(stream);
		return stream;
	}
};

template <class Type>
class LinkedPriorityQueue : public PriorityQueue<Type>
{
	/*
		Povezanu reprezentaciju ćemo koristiti da uradimo
		sortiranu implementaciju. Pošto ne znamo na koje mjesto
		dodajemo novi element on se odvija u linearnom vremenu.
		Ali u ovom slučaju je prvi element uvijek element sa
		najvećim prioritetom tako da se uklanjanje odvija u
		konstantnom vremenu.

		SeqPriorityQueue::Push(item) - O(n)
		SeqPriorityQueue::Pop(item) - O(1)
	*/

	Node<Type>* m_start;
	int m_counter;

public:

	LinkedPriorityQueue() :
		m_counter(0),
		m_start(nullptr)
	{}

	virtual void Push(Type item) override
	{
		if (m_start == nullptr)
		{
			m_start = new Node<Type>(item, nullptr);
			m_counter++;
		}
		else
		{
			if (m_start->Item < item)
			{
				m_start = new Node<Type>(item, m_start);
				m_counter++;
				return;
			}

			Node<Type>* traversal = m_start;


			while (traversal->Link != nullptr)
			{
				if (traversal->Link->Item < item)
				{
					traversal->Link = new Node<Type>(item, traversal->Link);
					m_counter++;
					return;
				}
				traversal = traversal->Link;
			}

			m_counter++;
			traversal->Link = new Node<Type>(item, nullptr);
		}
	}

	virtual Type Pop() override
	{
		if (IsEmpty()) throw std::exception("Unable to pop item from empty priority queue!");

		Node<Type>* popped_node = m_start;
		Type popped_item = popped_node->Item;

		m_start = m_start->Link;
		delete popped_node;
		m_counter--;

		return popped_item;
	}

	virtual Type& Peek() override
	{
		if (IsEmpty()) throw std::exception("Unable to peek item from empty priority queue!");

		return m_start->Item;
	}

	virtual bool IsEmpty() override
	{
		return m_start == nullptr;
	}

	virtual void Print(std::ostream& stream) override
	{
		stream << "Linked Pr. Queue object at " << this << std::endl;
		stream << "=====================================START\n";

		Node<Type>* traversal = m_start;

		while (traversal != nullptr)
		{
			stream << traversal->Item << std::endl;
			traversal = traversal->Link;
		}

		stream << "=====================================END\n";
	}

	friend std::ostream& operator<<(std::ostream& stream, LinkedPriorityQueue<Type>& obj)
	{
		obj.Print(stream);
		return stream;
	}
};

void TestPriorityQueue()
{
	PriorityQueue<int>* queue = new SeqPriorityQueue<int>;
	PriorityQueue<int>* queue2 = new LinkedPriorityQueue<int>;

	try
	{
		for (size_t i = 0; i < 10; i++)
		{
			queue->Push(i);
			queue2->Push(i);
		}

		std::cout << *queue << std::endl;
		std::cout << *queue2 << std::endl;

		for (size_t i = 0; i < 10; i++)
		{
			std::cout << "Sequential queue popped -> " << queue->Pop() << std::endl;
			std::cout << "Linked queue popped -> " << queue2->Pop() << std::endl;
		}

		std::cout << *queue << std::endl;
		std::cout << *queue2 << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		std::system("pause");
	}
}