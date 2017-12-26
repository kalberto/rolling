#pragma once
#include"DlinkedList.h"
#include"Array.h"
template<class T>
class LStack : public DlinkedList<T>
{
public:
	void Push(T p_data)
	{
		Append(p_data);
	}

	void Pop()
	{
		RemoveTail();
	}

	T top()
	{
		return m_tail->m_data;
	}

	int Count()
	{
		return m_count;
	}

};