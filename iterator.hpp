/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:42:01 by pweinsto          #+#    #+#             */
/*   Updated: 2022/05/25 17:10:10 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include "iterator_traits.hpp"

namespace	ft
{
	//struct	random_access_iterator_tag {};

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
		typedef Iterator													iterator_type;
		typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
		typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
		typedef typename iterator_traits<iterator_type>::pointer			pointer;
		typedef typename iterator_traits<iterator_type>::reference			reference;

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
	
}

# endif