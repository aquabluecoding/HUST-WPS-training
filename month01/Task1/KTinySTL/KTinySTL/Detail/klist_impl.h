#ifndef _LIST_IMPL_H_
#define _LIST_IMPL_H_

namespace TinySTL
{
	namespace Detail
	{
		template<class T>
		listIterator<T>& listIterator<T>::operator++()
		{
			p = p->next;
			return *this;
		}
		template<class T>
		listIterator<T> listIterator<T>::operator++(int)
		{
			auto res = *this;
			++*this;
			return res;
		}
		template<class T>
		listIterator<T>& listIterator<T>::operator --()
		{
			p = p->prev;
			return *this;
		}
		template<class T>
		listIterator<T> listIterator<T>::operator --(int)
		{
			auto res = *this;
			--*this;
			return res;
		}
		template<class T>
		bool operator ==(const listIterator<T>& lhs, const listIterator<T>& rhs)
		{
			return lhs.p == rhs.p;
		}
		template<class T>
		bool operator !=(const listIterator<T>& lhs, const listIterator<T>& rhs)
		{
			return !(lhs == rhs);
		}
	}//end of Detail namespace

	template<class T>
	void KList<T>::insert_aux(iterator position, size_type n, const T& val, std::true_type)
	{
		for (auto i = n; i != 0; --i)
		{
			position = insert(position, val);
		}
	}
	template<class T>
	template<class InputIterator>
	void KList<T>::insert_aux(iterator position, InputIterator first, InputIterator last, std::false_type)
	{
		for (--last; first != last; --last)
		{
			position = insert(position, *last);
		}
		insert(position, *last);
	}
	template<class T>
	typename KList<T>::nodePtr KList<T>::newNode(const T& val = T())
	{
		nodePtr res = nodeAllocator::allocate();
		nodeAllocator::construct(res, Detail::node<T>(val, nullptr, nullptr, this));
		return res;
	}
	template<class T>
	void KList<T>::deleteNode(nodePtr p)
	{
		p->prev = p->next = nullptr;
		nodeAllocator::destroy(p);
		nodeAllocator::deallocate(p);
	}
	template<class T>
	void KList<T>::ctorAux(size_type n, const value_type& val, std::true_type)
	{
		head.p = newNode();//add a dummy node
		tail.p = head.p;
		while (n--)
			push_back(val);
	}
	template<class T>
	template <class InputIterator>
	void KList<T>::ctorAux(InputIterator first, InputIterator last, std::false_type)
	{
		head.p = newNode();//add a dummy node
		tail.p = head.p;
		for (; first != last; ++first)
			push_back(*first);
	}
	template<class T>
	typename KList<T>::size_type KList<T>::size()const
	{
		size_type length = 0;
		for (auto h = head; h != tail; ++h)
			++length;
		return length;
	}
	template<class T>
	KList<T>::KList()
	{
		head.p = newNode();//add a dummy node
		tail.p = head.p;
	}
	template<class T>
	KList<T>::KList(size_type n, const value_type& val = value_type())
	{
		ctorAux(n, val, std::is_integral<value_type>());
	}
	template<class T>
	template <class InputIterator>
	KList<T>::KList(InputIterator first, InputIterator last)
	{
		ctorAux(first, last, std::is_integral<InputIterator>());
	}
	template<class T>
	KList<T>::KList(const KList& l)
	{
		head.p = newNode();//add a dummy node
		tail.p = head.p;
		for (auto node = l.head.p; node != l.tail.p; node = node->next)
			push_back(node->data);
	}
	template<class T>
	KList<T>& KList<T>::operator = (const KList& l)
	{
		if (this != &l)
			KList(l).swap(*this);
		return *this;
	}
	template<class T>
	KList<T>::~KList()
	{
		for (; head != tail;)
		{
			auto temp = head++;
			//bug fix
			nodeAllocator::destroy(temp.p);
			nodeAllocator::deallocate(temp.p);
		}
		nodeAllocator::deallocate(tail.p);
	}
	template<class T>
	void KList<T>::push_front(const value_type& val)
	{
		auto node = newNode(val);
		head.p->prev = node;
		node->next = head.p;
		head.p = node;
	}
	template<class T>
	void KList<T>::pop_front()
	{
		auto oldNode = head.p;
		head.p = oldNode->next;
		head.p->prev = nullptr;
		deleteNode(oldNode);
	}
	template<class T>
	void KList<T>::push_back(const value_type& val)
	{
		auto node = newNode();
		(tail.p)->data = val;
		(tail.p)->next = node;
		node->prev = tail.p;
		tail.p = node;
	}
	template<class T>
	void KList<T>::pop_back()
	{
		auto newTail = tail.p->prev;
		newTail->next = nullptr;
		deleteNode(tail.p);
		tail.p = newTail;
	}
	template<class T>
	typename KList<T>::iterator KList<T>::insert(iterator position, const value_type& val)
	{
		if (position == begin())
		{
			push_front(val);
			return begin();
		}else if (position == end())
		{
			auto ret = position;
			push_back(val);
			return ret;
		}
		auto node = newNode(val);
		auto prev = position.p->prev;
		node->next = position.p;
		node->prev = prev;
		prev->next = node;
		position.p->prev = node;
		return iterator(node);
	}
	template<class T>
	void KList<T>::insert(iterator position, size_type n, const value_type& val)
	{
		insert_aux(position, n, val, typename std::is_integral<InputIterator>::type());
	}
	template<class T>
	template <class InputIterator>
	void KList<T>::insert(iterator position, InputIterator first, InputIterator last)
	{
		insert_aux(position, first, last, typename std::is_integral<InputIterator>::type());
	}
	template<class T>
	typename KList<T>::iterator KList<T>::erase(iterator position)
	{
		if (position == head)
		{
			pop_front();
			return head;
		}
		else
		{
			auto prev = position.p->prev;
			prev->next = position.p->next;
			position.p->next->prev = prev;
			deleteNode(position.p);
			return iterator(prev->next);
		}
	}
	template<class T>
	typename KList<T>::iterator KList<T>::erase(iterator first, iterator last)
	{
		typename KList<T>::iterator res;
		for (; first != last;)
		{
			auto temp = first++;
			res = erase(temp);
		}
		return res;
	}
	template<class T>
	void KList<T>::clear(){ erase(begin(), end()); }
	template<class T>
	typename KList<T>::iterator KList<T>::begin(){ return head; }
	template<class T>
	typename KList<T>::iterator KList<T>::end(){ return tail; }
	template<class T>
	typename KList<T>::const_iterator KList<T>::changeIteratorToConstIterator(iterator& it)const
	{
		using nodeP = Detail::node<const T>*;
		auto temp = (KList<const T>*const)this;
		auto ptr = it.p;
		Detail::node<const T> node(ptr->data, (nodeP)(ptr->prev), (nodeP)(ptr->next), temp);
		return const_iterator(&node);
	}
	template<class T>
	typename KList<T>::const_iterator KList<T>::begin()const
	{
		auto temp = (KList*const)this;
		return changeIteratorToConstIterator(temp->head);
	}
	template<class T>
	typename KList<T>::const_iterator KList<T>::end()const
	{
		auto temp = (KList*const)this;
		return changeIteratorToConstIterator(temp->tail);
	}
	template<class T>
	typename KList<T>::reverse_iterator KList<T>::rbegin()
	{
		return reverse_iterator(tail);
	}
	template<class T>
	typename KList<T>::reverse_iterator KList<T>::rend()
	{
		return reverse_iterator(head);
	}
	template<class T>
	void KList<T>::reverse()
	{//²ÉÓÃÎ²²å·¨
		if (empty() || head.p->next == tail.p) return;
		auto curNode = head.p;
		head.p = tail.p->prev;
		head.p->prev = nullptr;
		do{
			auto nextNode = curNode->next;
			curNode->next = head.p->next;
			head.p->next->prev = curNode;
			head.p->next = curNode;
			curNode->prev = head.p;
			curNode = nextNode;
		} while (curNode != head.p);
	}
	template<class T>
	void KList<T>::remove(const value_type& val)
	{
		for (auto it = begin(); it != end();)
		{
			if (*it == val)
				it = erase(it);
			else
				++it;
		}
	}
	template<class T>
	template <class Predicate>
	void KList<T>::remove_if(Predicate pred)
	{
		for (auto it = begin(); it != end();)
		{
			if (pred(*it))
				it = erase(it);
			else
				++it;
		}
	}
	template<class T>
	void KList<T>::swap(KList& x)
	{
		TinySTL::swap(head.p, x.head.p);
		TinySTL::swap(tail.p, x.tail.p);
	}
	template<class T>
	void swap(KList<T>& x, KList<T>& y) { x.swap(y); }
	template<class T>
	void KList<T>::unique()
	{
		nodePtr curNode = head.p;
		while (curNode != tail.p)
		{
			nodePtr nextNode = curNode->next;
			if (curNode->data == nextNode->data)
			{
				if (nextNode == tail.p)
				{
					curNode->next = nullptr;
					tail.p = curNode;
				}
				else
				{
					curNode->next = nextNode->next;
					nextNode->next->prev = curNode;
				}
				deleteNode(nextNode);
			}
			else
				curNode = nextNode;
		}
	}
	template<class T>
	template <class BinaryPredicate>
	void KList<T>::unique(BinaryPredicate binary_pred)
	{
		nodePtr curNode = head.p;
		while (curNode != tail.p)
		{
			nodePtr nextNode = curNode->next;
			if (binary_pred(curNode->data, nextNode->data))
			{
				if (nextNode == tail.p)
				{
					curNode->next = nullptr;
					tail.p = curNode;
				}
				else
				{
					curNode->next = nextNode->next;
					nextNode->next->prev = curNode;
				}
				deleteNode(nextNode);
			}
			else
				curNode = nextNode;
		}
	}
	template<class T>
	void KList<T>::splice(iterator position, KList& x)
	{
		this->insert(position, x.begin(), x.end());
		x.head.p = x.tail.p;
	}
	template<class T>
	void KList<T>::splice(iterator position, KList& x, iterator first, iterator last)
	{
		if (first.p == last.p) return;
		auto tailNode = last.p->prev;
		if (x.head.p == first.p)
		{
			x.head.p = last.p;
			x.head.p->prev = nullptr;
		}
		else
		{
			first.p->prev->next = last.p;
			last.p->prev = first.p->prev;
		}
		if (position.p == head.p)
		{
			first.p->prev = nullptr;
			tailNode->next = head.p;
			head.p->prev = tailNode;
			head.p = first.p;
		}
		else
		{
			position.p->prev->next = first.p;
			first.p->prev = position.p->prev;
			tailNode->next = position.p;
			position.p->prev = tailNode;
		}
	}
	template<class T>
	void KList<T>::splice(iterator position, KList& x, iterator i)
	{
		auto next = i;
		this->splice(position, x, i, ++next);
	}
	template<class T>
	void KList<T>::merge(KList& x)
	{
		auto it1 = begin(), it2 = x.begin();
		while (it1 != end() && it2 != x.end())
		{
			if (*it1 <= *it2)
				++it1;
			else
			{
				auto temp = it2++;
				this->splice(it1, x, temp);
			}
		}
		if (it1 == end())
		{
			this->splice(it1, x, it2, x.end());
		}
	}
	template<class T>
	template <class Compare>
	void KList<T>::merge(KList& x, Compare comp)
	{
		auto it1 = begin(), it2 = x.begin();
		while (it1 != end() && it2 != x.end())
		{
			if (comp(*it2, *it1))
			{
				auto temp = it2++;
				this->splice(it1, x, temp);
			}
			else
				++it1;
		}
		if (it1 == end()){
			this->splice(it1, x, it2, x.end());
		}
	}
	template <class T>
	bool operator== (const KList<T>& lhs, const KList<T>& rhs)
	{
		auto node1 = lhs.head.p, node2 = rhs.head.p;
		for (; node1 != lhs.tail.p && node2 != rhs.tail.p; node1 = node1->next, node2 = node2->next)
		{
			if (node1->data != node2->data)
				break;
		}
		if (node1 == lhs.tail.p && node2 == rhs.tail.p)
			return true;
		return false;
	}
	template <class T>
	bool operator!= (const KList<T>& lhs, const KList<T>& rhs)
	{
		return !(lhs == rhs);
	}
	template<class T>
	void KList<T>::sort()
	{
		sort(TinySTL::less<T>());
	}
	template<class T>
	template <class Compare>
	void KList<T>::sort(Compare comp)
	{
		if (empty() || head.p->next == tail.p)
			return;

		KList carry;
		KList counter[64];
		int fill = 0;
		while (!empty())
		{
			carry.splice(carry.begin(), *this, begin());
			int i = 0;
			while (i < fill && !counter[i].empty())
			{
				counter[i].merge(carry, comp);
				carry.swap(counter[i++]);
			}
			carry.swap(counter[i]);
			if (i == fill)
				++fill;
		}
		for (int i = 0; i != fill; ++i)
		{
			counter[i].merge(counter[i - 1], comp);
		}
		swap(counter[fill - 1]);
	}
}

#endif