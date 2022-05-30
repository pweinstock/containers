/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:49:34 by pweinsto          #+#    #+#             */
/*   Updated: 2022/05/27 18:09:43 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <stdexcept>
# include <algorithm>
//# include <iterator>
# include "iterator.hpp"
# include "reverse_iterator.hpp"
# include "lexicographical_compare.hpp"
# include "is_integral.hpp"
# include "enable_if.hpp"
//# include <type_traits>

//#include <iostream>

namespace	ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:

		//Member types

		typedef T																value_type;
		typedef Alloc															allocator_type;
		typedef typename allocator_type::reference								reference;
		typedef typename allocator_type::const_reference						const_reference;
		typedef typename allocator_type::pointer								pointer;
		typedef typename allocator_type::const_pointer							const_pointer;
		// typedef vector_iterator<random_access_iterator_tag, const value_type,
		// 						ptrdiff_t, const T*, const T&>					const_iterator;
		// typedef vector_iterator<random_access_iterator_tag, value_type>			iterator;
		typedef vector_iterator<pointer>										iterator;
		typedef vector_iterator<const_pointer>									const_iterator;
		typedef reverse_iterator<const_iterator>								const_reverse_iterator;
		typedef reverse_iterator<iterator>										reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type				difference_type;
		typedef typename allocator_type::size_type								size_type;

		//Member functions

		explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _initial_element(NULL), _capacity(0), _size(0)
		{
		}

		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		{
			_alloc = alloc;
			_capacity = n;
			_size = n,
			_initial_element = _alloc.allocate(n);
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_initial_element + i, val);
		}

		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = NULL)
		{
			size_type	i = 0;
			_alloc = alloc;
			//_capacity = last.base() - first.base();
			_size = 0;
			InputIterator temp = first;
			while (temp != last)
			{
				++temp;
				++_size;
			}
			_capacity = _size;
			//_size = _capacity,
			_initial_element = _alloc.allocate(_capacity);
			for (InputIterator it = first; it != last; it++, i++)
				_alloc.construct(_initial_element + i, *it);
		}

		vector (const vector& x)
		{
			_alloc = x._alloc;
			_size = x._size;
			_capacity = x._capacity;
			_initial_element = _alloc.allocate(x._capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_initial_element + i, x._initial_element[i]);
		}

		~vector()
		{
			_alloc.deallocate(_initial_element, this->capacity());
		}
		
		vector& operator= (const vector& x)
		{
			this->clear();
			_alloc.deallocate(_initial_element, this->capacity());
			_initial_element = _alloc.allocate(x._capacity);
			for (size_type i = 0; i <= x._capacity; i++)
				_alloc.construct(_initial_element + i, x[i]);
			_capacity = x._capacity;
			_size = x._size;
			return *this;
		}

		//Iterators
		iterator begin()
		{
			return iterator(_initial_element);
		}

		const_iterator begin() const
		{
			//std::cout << "test" << std::endl;
			return const_iterator(_initial_element);
		}

		iterator end()
		{
			return iterator(_initial_element + _size);
		}

		const_iterator end() const
		{
			return const_iterator(_initial_element + _size);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(_initial_element + _size);
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(_initial_element + _size);
		}

		reverse_iterator rend()
		{
			return reverse_iterator(_initial_element);
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(_initial_element);
		}

		
		//Capacity
		size_type	size() const
		{
			return _size;
		}

		size_type max_size() const
		{
			return	_alloc.max_size();
		}

		void resize (size_type n, value_type val = value_type())
		{
			pointer	tmp = _alloc.allocate(n);
			for (size_t i = 0; i < n && i < _size; i++)
			{
				_alloc.construct(tmp + i, _initial_element[i]);
				_alloc.destroy(_initial_element + i);
			}
			for (size_t i = _size; i < n; i++)
				_alloc.construct(tmp + i, val);
			for (size_t i = n; i < _size; i++)
				_alloc.destroy(_initial_element + i);
			_alloc.deallocate(_initial_element, _capacity);
			_initial_element = tmp;
			_capacity = n;
			_size = n;
		}

		size_type	capacity() const
		{
			return _capacity;
		}

		bool empty() const
		{
			return _size == 0;
		}

		void reserve (size_type n)
		{
			if (n <= _capacity)
				return ;
			pointer	tmp = _alloc.allocate(n);
			for (size_t i = 0; i < _size; i++)
			{
				_alloc.construct(tmp + i, _initial_element[i]);
				_alloc.destroy(_initial_element + i);
			}
			_alloc.deallocate(_initial_element, _capacity);
			_initial_element = tmp;
			_capacity = n;
		}

		//Element Access
		reference operator[] (size_type n)
		{
			return _initial_element[n];
		}

		const_reference operator[] (size_type n) const
		{
			return _initial_element[n];
		}

		reference at (size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("Out of Range error: vector");
			else
				return _initial_element[n];
		}

		const_reference at (size_type n) const
		{
			if (n >= _size)
				throw std::out_of_range("Out of Range error: vector");
			else
				return _initial_element[n];
		}

		reference front()
		{
			return	_initial_element[0];
		}

		const_reference front() const
		{
			return	_initial_element[0];
		}

		reference back()
		{
			return	_initial_element[_size - 1];
		}

		const_reference back() const
		{
			return	_initial_element[_size - 1];
		}

		//Modifiers
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
		{
			//size_type	n = last - first;
			size_type	n = 0;
			InputIterator temp = first;
			while (temp != last)
			{
				++temp;
				++n;
			}
			if (n > _capacity)
			{
				this->clear();
				_alloc.deallocate(_initial_element, _capacity);
				_initial_element = _alloc.allocate(n);
				for (size_type i = 0; i < n; i++ , first++)
					_alloc.construct(_initial_element + i, *(first /*+ i*/));
				_capacity = n;
			}
			else
			{
				for (size_type i = 0; i < std::max(_size, n); i++, first++)
				{
					if ( i < _size)
						_alloc.destroy(_initial_element + i);
					if (i < n)
						_alloc.construct(_initial_element + i, *(first /*+ i*/));
				}
			}
			_size = n;
		}

		void assign (size_type n, const value_type& val)
		{
			if (n > _capacity)
			{
				this->clear();
				_alloc.deallocate(_initial_element, _capacity);
				_initial_element = _alloc.allocate(n);
				for (size_type i = 0; i < n; i++)
					_alloc.construct(_initial_element + i, val);
				_capacity = n;
			}
			else
			{
				for (size_type i = 0; i < std::max(_size, n); i++)
				{
					if ( i < _size)
						_alloc.destroy(_initial_element + i);
					if (i < n)
						_alloc.construct(_initial_element + i, val);
				}
			}
			_size = n;
		}

		void push_back (const value_type& val)
		{
			if (!_initial_element)
			{
				_initial_element = _alloc.allocate(1);
				_capacity = 1;
			}
			else if (_size >= _capacity)
				this->reserve(_capacity * 2);
			_alloc.construct(_initial_element + _size, val);
			_size += 1;
		}

		void pop_back()
		{
			_size -= 1;
			_alloc.destroy(_initial_element + _size);
		}

		iterator insert (iterator position, const value_type& val)
		{
			// //std::cout << "test: " << position.base() << std::endl;
			// size_type	start = position - this->begin();
			// //if (position.base() < _initial_element && position.base() > _initial_element + size())
			// if (_size >= _capacity)
			// 	this->reserve(_capacity * 2);
			// for (size_type i = _size; i > start; i--)
			// {
			// 	//std::cout << "p: " << _initial_element + i - 1 << std::endl;
			// 	//std::cout << "i: " << i << std::endl;
			// 	//std::cout << "before: " << *(_initial_element + i - 1) << " " << *(_initial_element + i) << std::endl;
			// 	_alloc.construct(_initial_element + i, *(_initial_element + i - 1));
			// 	_alloc.destroy(_initial_element + i - 1);
			// 	//std::cout << "after: " << *(_initial_element + i - 1) << " " << *(_initial_element + i) << std::endl;
			// }
			// 	//_alloc.construct(position.base(), val);
			// 	_alloc.construct(_initial_element + start, val);
			// 	_size += 1;
			// 	return position;
			
			this->insert(position, 1, val);
			return position;

		}

		void insert (iterator position, size_type n, const value_type& val)
		{
			size_type	start = position - this->begin();
			if (_size + n > _capacity && _size + n < _capacity * 2)
				this->reserve(_capacity * 2);
			else
				this->reserve(_size + n);
			
			for (size_type i = _size; i >= start ; i--)
			{
				_alloc.construct(_initial_element + i + n, *(_initial_element + i));
				_alloc.destroy(_initial_element + i);
				if (i == 0)
					break;
			}
			
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_initial_element + start + i, val);
		 	_size += n;
		}

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
		{
			size_type	start = position - this->begin();
			size_type	n = 0;
			InputIterator temp = first;
				while (temp != last)
				{
					++temp;
					++n;
				}
			//size_type	n = last - first;
			if (_size + n > _capacity && _size + n < _capacity * 2)
				this->reserve(_capacity * 2);
			else
				this->reserve(_size + n);
			for (size_type i = _size; i >= start ; i--)
			{
				_alloc.construct(_initial_element + i + n, *(_initial_element + i));
				_alloc.destroy(_initial_element + i);
				if (i == 0)
					break;
			}
			InputIterator	it = first;
			for (size_type i = 0; i < n; i++, it++)
				_alloc.construct(_initial_element + start + i, *it);
			_size += n;
		}
		
		void clear()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_initial_element + i);
			_size = 0;
		}

		iterator erase (iterator position)
		{
			size_type	start = position - this->begin();
			_alloc.destroy(_initial_element + start);
			for (size_type i = start; i <= _size; i++)
			{
				_alloc.construct(_initial_element + i, _initial_element[i+1]);
				_alloc.destroy(_initial_element + i + 1);
			}
			_size -= 1;
			return position;
		}

		iterator erase (iterator first, iterator last)
		{
			size_type	start = first - this->begin();
			size_type	n = last - first;
			for (size_type i = 0; i < n; i++)
			{
				_alloc.destroy(_initial_element + start + i);
			}
			for (size_type i = 0; i < _size - start - n; i++)
			{
				_alloc.construct(_initial_element + start + i, _initial_element[start + i + n]);
				_alloc.destroy(_initial_element + start + i + n);
			}
			_size -= n;
			return _initial_element + start;
		}

		void swap (vector& x)
		{
			allocator_type	tmp_alloc = _alloc;
			pointer			tmp_initial_element = _initial_element;
			size_type		tmp_capacity = _capacity;
			size_type		tmp_size = _size;

			_alloc = x._alloc;
			_initial_element = x._initial_element;
			_capacity = x._capacity;
			_size = x._size;

			x._alloc = tmp_alloc;
			x._initial_element = tmp_initial_element;
			x._capacity = tmp_capacity;
			x._size = tmp_size;
		}

		private:
		allocator_type	_alloc;
		pointer			_initial_element;
		size_type		_capacity;
		size_type		_size;
	};
	
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		typedef typename Alloc::size_type		size_type;
		if (lhs.size() != rhs.size())
			return false;
		for (size_type i = 0; i < lhs.size() && i < rhs.size(); i++)
		{
			if (lhs[i] != rhs[i])
				return false;
		}
		return true;
	}
	
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs == rhs);
	}
	
	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return rhs < lhs;
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs < rhs);
	}
	
}

# endif