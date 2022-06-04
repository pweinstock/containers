/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:14:03 by pweinsto          #+#    #+#             */
/*   Updated: 2022/06/03 12:46:43 by pweinsto         ###   ########.fr       */
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
		
		
	};
	
}

# endif