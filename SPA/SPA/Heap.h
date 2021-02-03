#pragma once

#include <iostream>

template<class Type>
class Heap {
	Type* m_data;
	int m_counter;
	int m_max_size;

protected:

	int GetParentIndex(int index) { return index > 1 ? index / 2 : -1; }

	int GetLeftChildIndex(int index) { return index * 2 <= m_counter ? index * 2 : -1; }

	int GetRightChildIndex(int index) { return index * 2 + 1 <= m_counter ? index * 2 + 1 : -1; }

	int GetRootIndex() { return 1; }

	void AddItemToEnd(const Type& item) { m_data[m_counter++] = item; }

	void Swap(int index1, int index2)
	{
		Type temp = m_data[index1];
		m_data[index1] = m_data[index2];
		m_data[index2] = temp;
	}

	void ReplaceRoot()
	{
		// zamjeni korijen sa zadnjim elementom i ukloni zadnji element

		m_data[GetRootIndex()] = m_data[Count() - 1];
		m_counter--;
	}

public:

	Heap(int max_size) :
		m_max_size(max_size),
		m_counter(1),
		m_data(new Type[max_size]) {}

	~Heap()
	{
		delete[] m_data;
	}

	virtual void Push(const Type& item) = 0;

	virtual Type Pop() = 0;

	virtual void Print(std::ostream& stream) = 0;

	Type& Peek() { return m_data[GetRootIndex()]; }

	virtual bool IsFull() { return m_counter == m_max_size; }
	bool IsEmpty() { return m_counter == 1; }

	int Count() { return m_counter; }
	int GetMaxSize() { return m_max_size; }
	Type& Get(int index) { return m_data[index]; }

	friend std::ostream& operator<<(std::ostream& stream, Heap<Type>& obj)
	{
		obj.Print(stream);
		return stream;
	}
};

template<class Type>
class MaxHeap : public Heap<Type> {

	void HeapifyUp();
	void HeapifyDown();

public:

	MaxHeap(int max_size) :
		Heap<Type>(max_size) {}

	virtual void Push(const Type& item) override
	{
		if (this->IsFull()) throw std::exception("Unable to Push item onto full heap!");

		this->AddItemToEnd(item);

		HeapifyUp();
	}

	virtual Type Pop() override
	{
		if (this->IsEmpty())throw std::exception("Unable to Pop item out of empty heap!");

		Type Popped = this->Get(this->GetRootIndex());
		this->ReplaceRoot();

		HeapifyDown();

		return Popped;
	}

	virtual void Print(std::ostream& stream) override
	{
		stream << "MaxHeap object at " << this << std::endl;
		stream << "===================================\n";
		for (size_t i = 1; i < this->Count(); i++)
		{
			stream << "[" << i << "] = " << this->Get(i) << std::endl;
		}
		stream << "===================================\n";
	}

	friend std::ostream& operator<<(std::ostream& stream, MaxHeap<Type>& obj) {

		obj.Print(stream);
		return stream;
	}
};

template<class Type>
void MaxHeap<Type>::HeapifyUp()
{
	/*
	preuredi maxi gomilu nakon dodavanja nove stavke
	*/

	// stavka koja je zadnja dodata se treba uporediti sa ostatkom gomile da bi se sacuvala konzistentost
	int item_index = this->Count() - 1;

	// variabla za koja ce se promjenuti u false ako se preuredjivanje gomile treba zavrsiti
	bool continue_to_heapify = true;

	while (continue_to_heapify)
	{
		int parent_index = this->GetParentIndex(item_index);

		// -1 je vrijednost koju koristimo da naznacimo da stavka nema roditelja
		if (parent_index != -1)
		{
			if (this->Get(parent_index) < this->Get(item_index))
			{
				// ako je stavka veca od roditelja vrsimo zamjenu
				this->Swap(parent_index, item_index);
				item_index = parent_index;
			}
			else
			{
				// ako stavka nije veca od roditelja pronasli smo njeno mjesto u gomili i prekidamo preuredjivanje
				continue_to_heapify = false;
			}
		}
		else
		{
			// ako stavka nema roditelja prekini preuredjivanje
			continue_to_heapify = false;
		}
	}
}

template<class Type>
void MaxHeap<Type>::HeapifyDown()
{
	/*
	preuredi maxi gomilu izbacivanja stavke u korijenu i stavljanja zadnje stavke u prazninu
	*/

	// stavka koja se sa zadnjeg mjesta prebacila u rupu na prvom mjestu se uporedjuje sa ostatkom hrpe
	int item_index = this->GetRootIndex();

	// variabla za koja ce se promjenuti u false ako se preuredjivanje gomile treba zavrsiti
	bool continue_to_heapify = true;

	while (continue_to_heapify)
	{
		int left_child_index = this->GetLeftChildIndex(item_index);
		int right_child_index = this->GetRightChildIndex(item_index);

		// -1 je vrijednost koju koristimo da naznacimo da stavka dijeteta
		if (right_child_index != -1)
		{
			// predpostavimo da lijevo djete stavke ima vecu vrijednost
			int index_of_greater_child = left_child_index;

			// ako je vrijednost desnog djeteta veca onda poredimo njega sa stavkom
			if (this->Get(left_child_index) < this->Get(right_child_index))
				index_of_greater_child = right_child_index;

			if (this->Get(item_index) < this->Get(index_of_greater_child))
			{
				// ako je stavka manja od djeteta vrsimo zamjenu
				this->Swap(index_of_greater_child, item_index);
				item_index = index_of_greater_child;
			}
			else
			{
				// ako stavka nije manja od djeteta sa vecom vrijednosti pronasli smo njeno mjesto u gomili i prekidamo preuredjivanje
				continue_to_heapify = false;
			}
		}
		else if (left_child_index != -1)
		{
			// posto stavka nema desnog djeteta nemoramo ga porediti sa lijevim
			if (this->Get(item_index) < this->Get(left_child_index))
			{
				// ako je stavka manja od djeteta vrsimo zamjenu
				this->Swap(left_child_index, item_index);
				item_index = left_child_index;
			}
			else
			{
				// ako stavka nije veca od roditelja pronasli smo njeno mjesto u gomili i prekidamo preuredjivanje
				continue_to_heapify = false;
			}
		}
		else
		{
			// ako stavka nema roditelja prekini preuredjivanje
			continue_to_heapify = false;
		}
	}
}

template<class Type>
class MinHeap : public Heap<Type> {

	void HeapifyUp();
	void HeapifyDown();

public:

	MinHeap(int max_size) :
		Heap<Type>(max_size) {}

	virtual void Push(const Type& item) override
	{
		if (this->IsFull()) throw std::exception("Unable to Push item onto full heap!");

		this->AddItemToEnd(item);

		HeapifyUp();
	}

	virtual Type Pop() override
	{
		if (this->IsEmpty())throw std::exception("Unable to Pop item out of empty heap!");

		Type Popped = this->Get(this->GetRootIndex());
		this->ReplaceRoot();

		HeapifyDown();

		return Popped;
	}

	virtual void Print(std::ostream& stream) override
	{
		stream << "MinHeap object at " << this << std::endl;
		stream << "===================================\n";
		for (size_t i = 1; i < this->Count(); i++)
		{
			stream << "[" << i << "] = " << this->Get(i) << std::endl;
		}
		stream << "===================================\n";
	}

	friend std::ostream& operator<<(std::ostream& stream, MinHeap<Type>& obj) {

		obj.Print(stream);
		return stream;
	}
};

template<class Type>
void MinHeap<Type>::HeapifyUp()
{
	/*
	preuredi mini gomilu nakon dodavanja nove stavke
	*/

	// stavka koja je zadnja dodata se treba uporediti sa ostatkom gomile da bi se sacuvala konzistentost
	int item_index = this->Count() - 1;

	// variabla za koja ce se promjenuti u false ako se preuredjivanje gomile treba zavrsiti
	bool continue_to_heapify = true;

	while (continue_to_heapify)
	{
		int parent_index = this->GetParentIndex(item_index);

		// -1 je vrijednost koju koristimo da naznacimo da stavka nema roditelja
		if (parent_index != -1)
		{
			if (this->Get(parent_index) > this->Get(item_index))
			{
				// ako je stavka manja od roditelja vrsimo zamjenu
				this->Swap(parent_index, item_index);
				item_index = parent_index;
			}
			else
			{
				// ako stavka nije manja od roditelja pronasli smo njeno mjesto u gomili i prekidamo preuredjivanje
				continue_to_heapify = false;
			}
		}
		else
		{
			// ako stavka nema roditelja prekini preuredjivanje
			continue_to_heapify = false;
		}
	}
}

template<class Type>
void MinHeap<Type>::HeapifyDown()
{
	/*
	preuredi mini gomilu izbacivanja stavke u korijenu i stavljanja zadnje stavke u prazninu
	*/

	// stavka koja se sa zadnjeg mjesta prebacila u rupu na prvom mjestu se uporedjuje sa ostatkom hrpe
	int item_index = this->GetRootIndex();

	// variabla za koja ce se promjenuti u false ako se preuredjivanje gomile treba zavrsiti
	bool continue_to_heapify = true;

	while (continue_to_heapify)
	{
		int left_child_index = this->GetLeftChildIndex(item_index);
		int right_child_index = this->GetRightChildIndex(item_index);

		// -1 je vrijednost koju koristimo da naznacimo da stavka dijeteta
		if (right_child_index != -1)
		{
			// predpostavimo da lijevo dijete stavke ima manju vrijednost
			int index_of_smaller_child = left_child_index;

			// ako je vrijednost desnog djeteta manja onda poredimo njega sa stavkom
			if (this->Get(left_child_index) > this->Get(right_child_index))
				index_of_smaller_child = right_child_index;

			if (this->Get(item_index) > this->Get(index_of_smaller_child))
			{
				// ako je stavka veca od djeteta vrsimo zamjenu
				this->Swap(index_of_smaller_child, item_index);
				item_index = index_of_smaller_child;
			}
			else
			{
				// ako stavka nije veca od djeteta sa manjom vrijednosti pronasli smo njeno mjesto u gomili i prekidamo preuredjivanje
				continue_to_heapify = false;
			}
		}
		else if (left_child_index != -1)
		{
			// posto stavka nema desnog djeteta ne moramo ga porediti sa lijevim
			if (this->Get(item_index) > this->Get(left_child_index))
			{
				// ako je stavka veca od djeteta vrsimo zamjenu
				this->Swap(left_child_index, item_index);
				item_index = left_child_index;
			}
			else
			{
				// ako stavka nije veca od djeteta pronasli smo njeno mjesto u gomili i prekidamo preuredjivanje
				continue_to_heapify = false;
			}
		}
		else
		{
			// ako stavka nema roditelja prekini preuredjivanje
			continue_to_heapify = false;
		}
	}
}

void TestHeap()
{
	Heap<int>* heap = new MaxHeap<int>(20);
	Heap<int>* heap2 = new MinHeap<int>(20);

	try
	{
		for (size_t i = 0; i < 10; i++)
		{
			heap->Push(i);
			heap2->Push(i);
		}

		std::cout << *heap << std::endl;
		std::cout << *heap2 << std::endl;

		for (size_t i = 0; i < 10; i++)
		{
			std::cout << "Max queue popped -> " << heap->Pop() << std::endl;
			std::cout << "Min queue popped -> " << heap2->Pop() << std::endl;
		}

		std::cout << *heap << std::endl;
		std::cout << *heap2 << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		std::system("pause");
	}
}