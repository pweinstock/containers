/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:42:01 by pweinsto          #+#    #+#             */
/*   Updated: 2022/06/24 17:26:35 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include "iterator_traits.hpp"
# include "binary_search_tree.hpp"

namespace	ft
{
	//struct	random_access_iterator_tag {};
	struct	bidirectional_iterator_tag {};

	template <class Iterator/*class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&*/>
	class vector_iterator
	{
		// public:
		// typedef T			value_type;
		// typedef Distance	difference_type;
		// typedef Pointer		pointer;
		// typedef Reference	reference;
		// typedef Category	iterator_category;
		public:
		typedef Iterator														iterator_type;
		typedef typename ft::iterator_traits<iterator_type>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<iterator_type>::value_type			value_type;
		//typedef typename ft::iterator_traits<iterator_type>::difference_type	difference_type;
		typedef ptrdiff_t														difference_type;
		typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
		typedef typename ft::iterator_traits<iterator_type>::reference			reference;
	

		vector_iterator() {}
		vector_iterator(const vector_iterator &copy) : _ptr(copy._ptr) {}
		vector_iterator(iterator_type ptr) : _ptr(ptr) {}
		template <typename iter>
		vector_iterator(const vector_iterator<iter>& i): _ptr(i.base()) {}
		virtual ~vector_iterator() {}

		const iterator_type	&base() const
		{
			return _ptr;
		}

		vector_iterator	&operator=(pointer ptr)
		{
			_ptr = ptr;
			return *this;
		}
		vector_iterator	&operator=(const vector_iterator &copy)
		{
			_ptr = copy._ptr;
			return *this;
		}
		vector_iterator	&operator+=(difference_type n)
		{
			_ptr += n;
			return *this;
		}
		vector_iterator	&operator-=(difference_type n)
		{
			_ptr -= n;
			return *this;
		}

		reference	operator*() const
		{
			return *_ptr;
		}
		pointer		operator->() const
		{
			return	&(operator*());
		}
		reference	operator[](const difference_type i)
		{
			return	_ptr[i];
		}

		vector_iterator	&operator++()
		{
			_ptr++;
			return *this;
		}
		vector_iterator operator++(int)
		{
			vector_iterator	tmp = *this;
			*this = ++*this;
			return tmp;
		}
		vector_iterator	&operator--()
		{
			_ptr--;
			return *this;
		}
		vector_iterator	operator--(int)
		{
			vector_iterator	tmp = *this;
			*this = --*this;
			return tmp;
		}

		friend vector_iterator	operator+(const vector_iterator &it, difference_type n)
		{
			return vector_iterator(it._ptr + n);
		}
		friend vector_iterator	operator+(difference_type n, const vector_iterator &it)
		{
			return vector_iterator(it._ptr + n);
		}
		template <class lhs, class rhs>
		friend difference_type operator+(const vector_iterator<lhs> &a, const vector_iterator<rhs> &b)
		{
			return a._ptr + b._ptr;
		}
		friend vector_iterator	operator-(const vector_iterator &it, difference_type n)
		{
			return vector_iterator(it._ptr - n);
		}
		friend vector_iterator	operator-(difference_type n, const vector_iterator &it)
		{
			return vector_iterator(it._ptr - n);
		}
		template <class lhs, class rhs>
		friend difference_type operator-(const vector_iterator<lhs> &a, const vector_iterator<rhs> &b)
		{
			return a._ptr - b._ptr;
		}
		template <class lhs, class rhs>
		friend bool	operator==(const vector_iterator<lhs> &l, const vector_iterator<rhs> &r)
		{
			return l._ptr == r._ptr;
		}
		template <class lhs, class rhs>
		friend bool	operator!=(const vector_iterator<lhs> &l, const vector_iterator<rhs> &r)
		{
			return l._ptr != r._ptr;
		}
		template <class lhs, class rhs>
		friend bool	operator<(const vector_iterator<lhs> &l, const vector_iterator<rhs> &r)
		{
			return l._ptr < r._ptr;
		}
		template <class lhs, class rhs>
		friend bool	operator<=(const vector_iterator<lhs> &l, const vector_iterator<rhs> &r)
		{
			return l._ptr <= r._ptr;
		}
		template <class lhs, class rhs>
		friend bool	operator>(const vector_iterator<lhs> &l, const vector_iterator<rhs> &r)
		{
			return l._ptr > r._ptr;
		}
		template <class lhs, class rhs>
		friend bool	operator>=(const vector_iterator<lhs> &l, const vector_iterator<rhs> &r)
		{
			return l._ptr >= r._ptr;
		}
		
		private:
		iterator_type/*T*/	_ptr;
	};
	
	//template <class Iterator, class Compare>
	template <class Category, class T, class Compare, class not_const_T = T>
	class bst_iterator
	{
		public:
		// typedef Iterator														iterator_type;
		// typedef Compare															key_compare;
		// //typedef typename ft::iterator_traits<iterator_type>::iterator_category	iterator_category;
		// typedef typename ft::bidirectional_iterator_tag							iterator_category;
		// typedef typename ft::iterator_traits<iterator_type>::value_type			value_type;
		// typedef typename ft::iterator_traits<iterator_type>::difference_type	difference_type;
		// typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
		// typedef typename ft::iterator_traits<iterator_type>::reference			reference;
		typedef T	iterator_type; // node_type
		typedef typename T::value_type				value_type;
		//typedef typename not_const_T::Node			Node;
		//typedef typename T::key_type				key_type;
		//typedef typename T::mapped_type				mapped_type;
		typedef Compare								key_compare;
		typedef value_type							*pointer;
		typedef value_type							&reference;
		typedef ptrdiff_t							difference_type;
		typedef Category							iterator_category;

		

		bst_iterator() {}
		bst_iterator(const bst_iterator &copy, iterator_type *last_node) : _ptr(copy._ptr), _last_node(last_node) {}
		bst_iterator(iterator_type *ptr, iterator_type *last_node) : _ptr(ptr), _last_node(last_node) {}
		template <typename iter>
		bst_iterator(const bst_iterator<iterator_category, iter, key_compare>& i, iterator_type *last_node): _ptr(i.base()), _last_node(last_node) {}
		virtual ~bst_iterator() {}

		const iterator_type	&base() const
		{
			return _ptr;
		}

		bst_iterator	&operator=(pointer ptr)
		{
			_ptr = ptr;
			return *this;
		}
		bst_iterator	&operator=(const bst_iterator &copy)
		{
			_ptr = copy._ptr;
			return *this;
		}

		template <class lhs, class rhs>
		friend bool	operator==(const bst_iterator<iterator_category, lhs, key_compare> &l, const bst_iterator<iterator_category, rhs, key_compare> &r)
		{
			return l._ptr == r._ptr;
		}
		template <class lhs, class rhs>
		friend bool	operator!=(const bst_iterator<iterator_category, lhs, key_compare> &l, const bst_iterator<iterator_category, rhs, key_compare> &r)
		{
			return l._ptr != r._ptr;
		}

		reference	operator*() const
		{
			return *_ptr->value;
		}
		pointer		operator->() const
		{
			return	&(operator*());
		}

		bst_iterator	&operator++()
		{
			if (_ptr->right != _last_node)
			{
				_ptr =_BST_get_lower_node(_ptr->right);
				return *this;
			}
			else if (_ptr->parent != _last_node)
			{
				//key_type key = _ptr->value.first;
				iterator_type	*tmp = _ptr->parent;
				while (tmp != _last_node && _key_comp(tmp->value.first, _ptr->value.first))
					tmp = tmp->parent;
				if (tmp != _last_node)
				{
					_ptr = tmp;
					return *this;
				}
				_ptr = _last_node->right;
				return *this;
			}

		bst_iterator operator++(int)
		{
			bst_iterator	tmp = *this;
			*this = ++*this;
			return tmp;
		}

		bst_iterator	&operator--()
		{
			if (_ptr == _last_node->right)
			{
				_ptr = _ptr->parent;
				return *this;
			}
			else if (_ptr->left != _last_node)
			{
				_ptr =_BST_get_higher_node(_ptr->left);
				return *this;
			}
			else if (_ptr->parent != _last_node)
			{
				//key_type key = _ptr->value.first;
				iterator_type	*tmp = _ptr->parent;
				while (tmp != _last_node && _key_comp(tmp->value.first, _ptr->value.first))
					tmp = tmp->parent;
				if (tmp != _last_node)
				{
					_ptr = tmp;
					return *this;
				}
			}
			else
			{}
			return *this;
		}

		bst_iterator	operator--(int)
		{
			bst_iterator	tmp = *this;
			*this = --*this;
			return tmp;
		}

		private:
		
		iterator_type	*_BST_get_lower_node(iterator_type *root)				// iterates until the most left node
		{
			while (root != _last_node && root->left != _last_node)
				root = root->left;
				return root;
		}

		iterator_type	*_BST_get_higher_node(iterator_type *root)			// iterates until the most right node
		{
			while (root != _last_node && root->right!= _last_node)
				root = root->right;
				return root;
		}
		
		iterator_type/*T*/	*_ptr;
		iterator_type		* _last_node;
		key_compare			_key_comp;
	};
}

# endif