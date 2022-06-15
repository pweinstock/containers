/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:14:03 by pweinsto          #+#    #+#             */
/*   Updated: 2022/06/15 13:53:23 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "pair.hpp"
# include <memory>
# include <functional>
# include "binary_function.hpp"
# include "less.hpp"
# include "enable_if.hpp"
# include "is_integral.hpp"
# include <iterator>		//just for testing
# include "binary_search_tree.hpp"
# include "reverse_iterator.hpp"
# include "distance.hpp"

namespace	ft
{
	template < class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
		public:
		typedef Key	key_type;
		typedef T	mapped_type;
		typedef ft::pair<const key_type, mapped_type>	value_type;
		typedef Compare	key_compare;

		//template <class Key, class T, class Compare, class Alloc>
		class	value_compare : ft::binary_function<value_type, value_type, bool>
		{
			friend class map<key_type, mapped_type, key_compare, Alloc>;
			protected :
				Compare	comp;
				value_compare (Compare c) : comp(c) {}
			public:
				//typedef bool		result_type;
				//typedef value_type	first_argument_type;
				//typedef value_type	second_argument_type;
				bool operator() (const value_type& x, const value_type& y) const
				{
					return comp(x.first, y.first);
				}

		};
		
		//typedef	value_compare;
		typedef Alloc																			allocator_type;
		typedef typename allocator_type::reference												reference;
		typedef typename allocator_type::const_reference										const_reference;
		typedef typename allocator_type::pointer												pointer;
		typedef typename allocator_type::const_pointer											const_pointer;
		typedef typename ft::Binary_search_tree<value_type, key_compare>::iterator				iterator;
		typedef typename ft::Binary_search_tree<value_type, key_compare>::const_iterator		const_iterator;
		typedef typename ft::reverse_iterator<iterator>											reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>									const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type 						difference_type;
		typedef size_t																			size_type;
		
		explicit	map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(comp), _bst() {}

		template <class InputIterator>
		map	(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = NULL) : _alloc(alloc), _comp(comp), _bst()
		{
			this->inster(first, last);
		}

		map	(const map& x) : _alloc(x._alloc), _comp(x._comp), _bst()
		{
			this->insert(x.begin(), x.end());
		}

		~map()
		{
			this->clear();
		}

		map&	operator= (const map& x)
		{
			if(&x == this)
				return *this;
			this->clear();
			this->insert(x.begin(), x.end());
			return *this;
		}

		iterator	begin()
		{
			return iterator(_bst._last_node->left/*, _bst._last_node*/);
		}

		const_iterator	begin() const
		{
			return const_iterator(_bst._last_node->left/*, _bst._last_node*/);
		}

		iterator	end()
		{
			return iterator(_bst._last_node->right/*, _bst._last_node*/);
		}

		const_iterator	end() const
		{
			return const_iterator(_bst._last_node->right/*, _bst._last_node*/);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(this->end());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(this->end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(this->begin());
		}
		
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(this->begin());
		}

		bool empty() const
		{
			return (_bst._last_node->parent == _bst.last_node);
		}

		size_type size() const
		{
			return _bst._last_node->value.first;
		}

		size_type max_size() const
		{
			return _bst.max_size();
		}

		mapped_type& operator[] (const key_type& k)
		{
			if (this->find(k) == this->end())
				this->insert(ft::make_pair(k, mapped_type()));
			return *(this->find(k)).second;
		}

		pair<iterator,bool> insert (const value_type& val)
		{
			return _bst.insertPair(val);
		}

		iterator insert (iterator position, const value_type& val)
		{
			(void)position;
			return _bst.insertPair(val).first;
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = NULL)
		{
			//bool	is_valid;
			difference_type	n = ft::distance(first - last);
			while(n--)
				this->insert(*(first++));
		}

		void erase (iterator position)
		{
			this->erase((*position).first);
		}

		size_type erase (const key_type& k)
		{
			if (this->find(k) == this->end())
				return 0;
			_bst.removeByKey(ft::make_pair(k, mapped_type()));
			return(1);
		}

		void erase (iterator first, iterator last)
		{
			while (first != last)
				this->erase((*(first++)).first);
		}

		void swap (map& x)
		{
			_bst.swap(x._bst);
		}

		void clear()
		{
			this->erase(this->begin(), this->end());
		}

		key_compare key_comp() const
		{
			return key_compare();
		}

		value_compare value_comp() const
		{
			return value_compare(key_compare());
		}

		iterator find (const key_type& k)
		{
			return iterator(_bst.searchByKey(ft::make_pair(k, mapped_type())), _bst._last_node);
		}

		const_iterator find (const key_type& k) const
		{
			return const_iterator(_bst.searchByKey(ft::make_pair(k, mapped_type())), _bst._last_node);
		}

		size_type count (const key_type& k) const
		{
			const_iterator	begin = this->begin();
			const_iterator	end = this->end();
			while (begin != end)
				if (*(begin++).first == k)
					return 1;
			return 0;
		}

		iterator lower_bound (const key_type& k)
		{
			const_iterator	begin = this->begin();
			const_iterator	end = this->end();
			while (begin != end)
			{
				if (_comp(*(begin()).first, k) == false)
					break;
				begin++;
			}
			return begin;
		}

		const_iterator lower_bound (const key_type& k) const
		{
			return const_iterator(this->lower_bound(k));
		}

		iterator upper_bound (const key_type& k)
		{
			const_iterator	begin = this->begin();
			const_iterator	end = this->end();
			while (begin != end)
			{
				if (_comp(k, (*begin).first))
					break;
				begin++;
			}
			return begin;
		}

		const_iterator upper_bound (const key_type& k) const
		{
			return const_iterator(this->upper_bound(k));
		}

		pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{
			return ft::make_pair(this->lower_bound(k), this->upper_bound(k));
		}

		pair<iterator,iterator> equal_range (const key_type& k)
		{
			return ft::make_pair(this->lower_bound(k), this->upper_bound(k));
		}

		private:
		
		allocator_type							_alloc;
		Compare									_comp;
		Binary_search_tree<value_type, Compare>	_bst;
	};
	
}

# endif