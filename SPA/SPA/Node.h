#pragma once

template <class Type>
struct Node
{
	Type Item;
	Node<Type>* Link;

	Node(const Type& item, Node<Type>* link) :
		Item(item),
		Link(link) {}
};