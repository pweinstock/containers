/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:14:03 by pweinsto          #+#    #+#             */
/*   Updated: 2022/06/10 19:19:52 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "pair.hpp"
# include <memory>
# include <functional>

namespace	ft
{
	template < class Key, class T, class Compare = less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class map
	{
		typedef Key	key_type;
		typedef T	mapped_type;
		typedef pair<const key_type, mapped_type>	value_type;
		typedef Compare	key_compare;
		typedef	value_compare;
		typedef Alloc	allocator_type;
		typedef allocator_type::reference	reference;
		typedef allocator_type::const_reference	const_reference;
		typedef allocator_type::pointer	pointer;
		typedef allocator_type::const_pointer	const_pointer;
		
		explicit	map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(comp), _bst() {}

		template <class InputIterator>
		map	(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(comp), _bst()
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
			return iterator(_bst._last_node->left, _bst._last_node)
		}

		const_iterator	begin() const
		{
			return const_iterator(_bst._last_node->left, _bst._last_node)
		}

		iterator	end()
		{
			return iterator(_bst._last_node->right, _bst._last_node)
		}

		const_iterator	end() const
		{
			return const_iterator(_bst._last_node->right, _bst._last_node)
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
			return (_bst._last_node->parent == _last_node);
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

		

		private:
		
		allocator_type							_alloc;
		Compare									_comp;
		Binary_search_tree<value_type, Compare>	_bst;
	};
	
}

# endif