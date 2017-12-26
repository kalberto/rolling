#ifndef SLINKEDLIST_H
#define SLINKEDLIST_H

template<class T>
class SListNode;
template<class T>
class SlinkedList;
template<class T>
class SListInterator;

template<class T>
class SListNode
{
public:
	T m_data;
	SListNode<T>* m_next;

	SListNode()
	{
		m_next = 0;
	}

	void InsertAfter(T p_data)
	{
		SListNode<T>* newnode;
		newnode = new SListNode();
		newnode->m_data = p_data;
		newnode->m_next = m_next;
		m_next = newnode;
	}

	void Draw(SListNode<T>* inicial)
	{
		SListNode<int>* itr = inicial;
		while (itr != 0)
		{
			std::cout << itr->m_data << std::endl;
			itr = itr->m_next;
		}
		std::cout << std::endl;
	}
};


template<class T>
class SlinkedList
{
public:
	SListNode<T>* m_head;
	SListNode<T>* m_tail;
	int m_count;

	SlinkedList()
	{
		m_head = 0;
		m_tail = 0;
		m_count = 0;

	}
	~SlinkedList()
	{
		SListNode<T>* itr;
		itr = m_head;
		SListNode<T>* next;
		while (itr != 0)
		{
			next = itr->m_next;
			delete itr;
			itr = next;
		}

	}

	void Append(T p_data)
	{
		if (m_head == 0)
		{
			m_head = m_tail = new SListNode<T>();
			m_head->m_data = p_data;

		}
		else
		{
			m_tail->InsertAfter(p_data);
			m_tail = m_tail->m_next;
		}

	}

	void Prepend(T p_data)
	{
		SListNode<T>* newnode;
		newnode = new SListNode<T>();
		newnode->m_data = p_data;
		newnode->m_next = m_head;
		m_head = newnode;

		if (m_tail == 0)
			m_tail = m_head;

		m_count++;
	}

	void Remove(SListInterator<T>& p_interator)
	{
		SListNode<T>* node = m_head;

		if (p_interator.m_list != this)
			return;
		if (p_interator.m_node == 0)
			return;
		if (p_interator.m_node == m_head)
		{
			p_interator.Forth()
				RemoveHead();
		}
		else
		{
			while (node->m_next != p_interator.m_node)
			{
				node = node->m_next;
			}
			p_interator.Forth();
			if (node->m_next == m_tail)
			{
				m_tail = node;
			}
			delete node->m_next;
			node->m_next = p_interator.m_node;
		}
		m_count--;
	}

	void RemoveHead()
	{
		SListNode<T>* node = 0;
		if (m_head != 0)
		{
			node = m_head->m_next;
			delete m_head;
			m_head = node;

			if (m_head == 0)
				m_tail = 0;

			m_count--;
		}
	}

	void RemoveTail()
	{
		SListNode<T>* node = m_head;

		if (m_head != 0)
		{
			if (m_head == m_tail)
			{
				RemoveHead();
			}

			else
			{
				while (node->m_next != m_tail)
				{
					node = node->m_next;
				}
				m_tail = node;
				delete node->m_next;
				node->m_next = 0;
				m_count--;
			}
		}
	}

	void Draw(SlinkedList<T>* list)
	{
		Draw(list->m_head);
	}
	void Draw(SListNode<T>* inicial)
	{
		SListNode<int>* itr = inicial;
		while (itr != 0)
		{
			std::cout << itr->m_data << std::endl;
			itr = itr->m_next;
		}
		std::cout << std::endl;
	}

	SListInterator<T> GetInterator()
	{
		return SListInterator<T>(this, m_head);
	}

	void Insert(SListInterator<T> p_interator, T p_data)
	{
		if (p_interator.m_list != this)
			return;

		if (p_interator.m_node != 0)
		{
			p_interator.m_node->InsertAfter(p_data);

			if (p_interator.m_node == m_tail)
			{
				m_tail = p_interator.m_node->m_next;
			}
			m_count++;
		}
		else
		{
			Append(p_data);
		}
	}

};


template<class T>
class SListInterator
{
public:
	SlinkedList<T>* m_list;
	SListNode<T>* m_node;

	SListInterator(SlinkedList<T>* p_list = 0, SListNode<T>* p_node = 0)
	{
		m_list = p_list;
		m_node = p_node;
	}

	void Start()
	{
		if (m_list != 0)
		{
			m_node == m_list->m_head;
		}
	}

	void Forth()
	{
		if (m_node != 0)
		{
			m_node = m_node->m_next;
		}
	}

	T& Item()
	{
		return m_node->m_data;
	}

	bool Valide()
	{
		return m_node != 0;
	}

};


#endif