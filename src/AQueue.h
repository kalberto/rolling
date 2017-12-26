#pragma once
#include"Array.h"

template <class T>
class AQueue : public Array<T>
{
public:
	int m_front;
	int m_count;
	int index;
	AQueue(int p_size) : Array<T>(p_size)
	{
		m_front = 0;
		m_count = 0;
	}

	bool Enqueue(T p_data)
	{
		if (m_size != m_count)
		{
			m_array[(m_count + m_front) % m_size] = p_data;
			m_count++;
			return true;
		}
		return false;
	}

	void Dequeue()
	{
		if (m_count > 0)
		{
			m_count--;
			m_front++;
			if (m_front == m_size)
				m_front = 0;
		}
	}

	T Front()
	{
		return m_array[m_front];
	}

	T& operator[] (int p_index)
	{
		return m_array[(p_index + m_front) % m_size];
	}
};