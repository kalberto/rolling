#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

template<class T>
class DListNode;
template<class T>
class DlinkedList;
template<class T>
class DListInterator;

template<class T>
class DListNode
{
public:
	T m_data;
	DListNode<T>* m_next;
	DListNode<T>* m_previous;


	DListNode()
	{
		m_next = 0;
		m_previous = 0;
	}

	void InsertAfter(T p_data)
	{
		DListNode<T>* newnode;
		newnode = new DListNode();
		newnode->m_data = p_data;
		newnode->m_next = m_next;

		newnode->m_previous = this;
		m_next = newnode;
		if (newnode->m_next != 0)
			newnode->m_next->m_previous = newnode;

	}

	void InsertBefore(T p_data)
	{
		DListNode<T>* newnode;
		newnode = new DListNode();
		newnode->m_data = p_data;
		newnode->m_previous = m_previous;
		m_previous->m_next = newnode;
		newnode->m_next = this;
		m_previous = newnode;
	}

	void Draw(DListNode<T>* inicial)
	{
		DListNode<int>* itr = inicial;
		while (itr != 0)
		{
			std::cout << itr->m_data << std::endl;
			itr = itr->m_next;
		}
		std::cout << std::endl;
	}

};


template<class T>
class DlinkedList
{
public:
	DListNode<T>* m_head;
	DListNode<T>* m_tail;
	int m_count;

	DlinkedList()
	{
		m_head = 0;
		m_tail = 0;
		m_count = 0;

	}
	~DlinkedList()
	{
		DListNode<T>* itr;
		itr = m_head;
		DListNode<T>* next;
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
			m_head = m_tail = new DListNode<T>();
			m_head->m_data = p_data;

		}
		else
		{
			m_tail->InsertAfter(p_data);
			m_tail = m_tail->m_next;
		}
		m_count++;
	}

	void Prepend(T p_data)
	{
		if (m_head == 0)
		{
			m_head = m_tail = new DListNode<T>();
			m_head->m_data = p_data;

		}
		else
		{
			m_head->InsertAfter(p_data);
			m_head = m_head->m_previous;
		}
		m_count++;
	}

	void Remove(DListInterator<T>& p_interator)
	{
		DListNode<T>* node = m_head;

		if (p_interator.m_list != this)
			return;
		if (p_interator.m_node == 0)
			return;
		if (p_interator.m_node == m_head)
		{
			p_interator.Forth();
			RemoveHead();
		}
		else if (p_interator.m_node == m_tail)
		{
			RemoveTail();
		}
		else
		{
			while (node->m_next != p_interator.m_node)
			{
				node = node->m_next;
			}
			p_interator.Forth();

			delete node->m_next;
			node->m_next = p_interator.m_node;
			p_interator.m_node->m_previous = node;

		}
		m_count--;
	}

	void RemoveHead()
	{
		if (m_head != 0)
		{
			if (m_tail != m_tail)
			{
				m_head = m_head->m_next;
				delete m_head->m_previous;
				m_head->m_previous = 0;

				if (m_head == 0)
					m_tail = 0;
			}
			else
			{
				delete m_head;
				m_head = 0;
			}
			m_count--;
		}
	}

	void RemoveTail()
	{
		if (m_tail != 0)
		{
			if (m_tail != m_head)
			{
				m_tail = m_tail->m_previous;
				delete m_tail->m_next;
				m_tail->m_next = 0;
				m_count--;
			}
			else
			{
				RemoveHead();

			}

		}

	}

	void Draw(DlinkedList<T>* list)
	{
		Draw(list->m_head);
	}
	void Draw(DListNode<T>* inicial)
	{
		DListNode<int>* itr = inicial;
		while (itr != 0)
		{
			std::cout << itr->m_data << std::endl;
			itr = itr->m_next;
		}
		std::cout << std::endl;
	}

	DListInterator<T> GetInterator()
	{
		return DListInterator<T>(this, m_head);
	}

	void Insert(DListInterator<T> p_interator, T p_data)
	{
		if (p_interator.m_list != this)
			return;

		if (p_interator.m_node != 0)
		{
			p_interator.m_node->InsertAfter(p_data);

			m_count++;
		}
		else
		{
			Append(p_data);
		}
	}
};


template<class T>
class DListInterator
{
public:
	DlinkedList<T>* m_list;
	DListNode<T>* m_node;

	DListInterator(DlinkedList<T>* p_list = 0, DListNode<T>* p_node = 0)
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