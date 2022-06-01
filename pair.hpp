/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:29:25 by pweinsto          #+#    #+#             */
/*   Updated: 2022/06/01 17:12:15 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace	ft
{
	template <class T1, class T2>
	struct	pair
	{
		public:
		typedef T1	first_type;
		typedef T2	second_type;

		pair() : first(), second() {}
	
		template<class U, class V>
		pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}

		pair (const first_type& a, const second_type& b) : first(a), second(b) {}

		pair& operator= (const pair& pr)
		{
			this->first = pr.first;
			this->second = pr.second;
			return *this;
		}

		first_type	first;
		second_type	second;
	};
}

# endif