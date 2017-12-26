#pragma once
#include"DlinkedList.h"
#include"Array.h"

template <class KT, class DT>
class HashEntry
{
public:
	KT m_key;
	DT m_data;
};

template <class KT, class DT>
class HashTable
{
public:
	typedef HashEntry<KT, DT> Entry;
	int m_size;
	int m_count;
	Array<DlinkedList<Entry>> m_table;
	unsigned long int(*m_hash)(KT);

	HashTable(int p_size, unsigned long int(*p_hash)(KT)) : m_table(p_size)
	{
		m_size = p_size;
		m_hash = p_hash;
		m_count = 0;
	}

	void Insert(KT p_key, DT p_data)
	{
		Entry entry;
		entry.m_data = p_data;
		entry.m_key = p_key;
		int index = m_hash(p_key) % m_size;
		m_table[index].Append(entry);
		m_count++;
	}

	Entry* Find(KT p_key)
	{
		int index = m_hash(p_key) % m_size;
		DListInterator<Entry> itr = m_table[index].GetInterator();
		while (itr.Valide())
		{
			if (itr.Item().m_key == p_key)
				return &(itr.Item());
			itr.Forth();

		}
		return 0;
	}

	bool Remove(KT p_key)
	{
		int index = m_hash(p_key) % m_size;
		DListInterator<Entry> itr = m_table[index].GetInterator();
		while (itr.Valide())
		{
			if (itr.Item().m_key == p_key)
			{
				m_table[index].Remove(itr);
				m_count--;
				return true;
			}
			itr.Forth();

		}
		return false;

	}


};