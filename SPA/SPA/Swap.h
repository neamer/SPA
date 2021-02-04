#pragma once

template<class Type>
void Swap(Type& item1, Type& item2)
{
	Type temp = item1;
	item1 = item2;
	item2 = temp;
}

template<class Type>
void Swap(Type* item1, Type* item2)
{
	Type temp = *item1;
	*item1 = *item2;
	*item2 = temp;
}