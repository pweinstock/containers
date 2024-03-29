/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:29:14 by pweinsto          #+#    #+#             */
/*   Updated: 2022/07/06 12:48:43 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"
# include "iterator.hpp"
#include <iostream>

namespace	ft
{
	template <class Iterator>
	class reverse_iterator
	{
		public:
		typedef Iterator													iterator_type;
		typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
		typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
		typedef typename iterator_traits<iterator_type>::pointer			pointer;
		typedef typename iterator_traits<iterator_type>::reference			reference;

		reverse_iterator() {}
		explicit reverse_iterator(iterator_type it) : _it(it) {}
		template<class Iter>
		reverse_iterator (const reverse_iterator<Iter> &rev_it) : _it(rev_it.base()) {}

		template< class U >
		reverse_iterator& operator=( const reverse_iterator<U>& other )
		{
			_it = other.base();
			return *this;
		}
		
		iterator_type	base() const
		{
			return _it;
		}

		reference	operator*() const
		{
			iterator_type	tmp = _it;
			return *(--tmp);		// for vector maybe *--tmp;
		}

		pointer		operator->() const
		{
			return &(operator*());
		}

		reverse_iterator	&operator+=(difference_type n)
		{
			_it -= n;
			return *this;
		}
		reverse_iterator	&operator-=(difference_type n)
		{
			_it += n;
			return *this;
		}

		reference	operator[](difference_type n)
		{
			return _it[-n-1];
		}
		
		reverse_iterator	&operator++()
		{
			--_it;
			return *this;
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator	tmp = *this;
			--_it;
			return tmp;
		}
		reverse_iterator	&operator--()
		{
			++_it;
			return *this;
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator	tmp = *this;
			++_it;
			return tmp;
		}

		reverse_iterator	operator+(difference_type n)
		{
			return reverse_iterator(_it - n);
		}
		// friend reverse_iterator	operator+(difference_type n, const reverse_iterator &it)
		// {
		// 	return reverse_iterator(n - it._it);
		// }
		reverse_iterator	operator-(difference_type n)
		{
			return reverse_iterator(_it + n);
		}
		// template <class lhs, class rhs>
		// friend difference_type operator-(const reverse_iterator<lhs> &a, const reverse_iterator<rhs> &b)
		// {
		// 	return b._it - a._it;
		// }

		private:
		iterator_type	_it;
	};
	
	template< class Iterator1, class Iterator2 >
	bool operator==( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() == rhs.base();
	}
	
	template< class Iterator1, class Iterator2 >
	bool operator!=( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() != rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator<( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() > rhs.base();
	}
	
	template< class Iterator1, class Iterator2 >
	bool operator<=( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() >= rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator>( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() < rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator>=( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() <= rhs.base();
	}
}


# endif