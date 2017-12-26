#pragma once
#include"DlinkedList.h"
template <class T>
class LQueue : public DlinkedList<T>
{
public:
	void Enqueue(T p_data)
	{
		Append(p_data);
	}

	void Dequeue()
	{
		RemoveHead();
	}

	T Front()
	{
		return m_head->m_data;
	}

};