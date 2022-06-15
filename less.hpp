/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:35:05 by pweinsto          #+#    #+#             */
/*   Updated: 2022/06/13 17:38:06 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LESS_HPP
# define LESS_HPP

# include "binary_function.hpp"

namespace	ft
{
	template <class T> struct less : ft::binary_function <T,T,bool>
	{
		bool operator() (const T& x, const T& y) const
		{
			return x<y;
		}
	};
}

# endif
