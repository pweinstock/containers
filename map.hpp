/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:14:03 by pweinsto          #+#    #+#             */
/*   Updated: 2022/06/01 18:09:52 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAO_H

# include "pair.hpp"
# include <memory>
# include <functional>

namespace	ft
{
	template < class Key, class T, class Compare = less<Key>, class Alloc = allocator<pair<const Key,T> > >
	class map
	{
		typedef Key	key_type;
		typedef T	mapped_type;
		typedef pair<const key_type, mapped_type>	value_type;
		typedef Compare	key_compare;
		
		
	};
	
}

# endif