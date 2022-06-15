/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:33:16 by pweinsto          #+#    #+#             */
/*   Updated: 2022/06/14 15:36:37 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISTANCE_HPP
# define DISTANCE_HPP

# include "iterator_traits.hpp"

namespace	ft
{
	template<class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type distance (InputIterator first, InputIterator last)
	{
		typename ft::iterator_traits<InputIterator>::difference_type result = 0;
		while (first != last)
		{
			first++;
			result++;
		}
		return (result);
	}
}

# endif