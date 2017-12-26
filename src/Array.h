#ifndef ARRAY_H
#define ARRAY_H

template<class T>
class Array
{
public:
	T* m_array;
	int m_size;

	Array(int p_size)
	{
		m_array = new T[p_size];
		m_size = p_size;
	}

	~Array()
	{
		if (m_array != 0)
		{
			delete[] m_array;
		}
		m_array = 0;
	}

	void Resize(int p_size)
	{
		T *newarray = new T[p_size];
		if (newarray == 0)
		{
			return;
		}
		int min;
		if (p_size < m_size)
			min = p_size;
		else
			min = m_size;

		for (int i = 0; i < min; i++)
		{
			newarray[i] = m_array[i];
		}
		m_size = p_size;
		if (m_array != 0)
		{
			delete[] m_array;
		}
		m_array = newarray;
	}

	T& operator[](int p_i)
	{
		return m_array[p_i];
	}

	operator T*()
	{
		return m_array;
	}

	void Insert(T p_item, int p_i)
	{
		for (int i = m_size - 1; i > p_i; i--)
		{
			m_array[i] = m_array[i - 1];
		}
		m_array[p_i] = p_item;
	}

	void Remove(int p_i)
	{
		for (int i = p_i + 1; i < m_size; i++)
		{
			m_array[i - 1] = m_array[i];
		}
	}

	int Size()
	{
		return m_size;
	}


protected:


};



#endif