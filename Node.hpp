/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:03:23 by pweinsto          #+#    #+#             */
/*   Updated: 2022/06/04 12:59:35 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

namespace ft
{
	enum	color
	{
		RED,
		BLACK
	};

	template<class T>
	class Node
	{
		typedef T	value_type;

		value_type	value;
		Node		*left;
		Node		*right;
		Node		*parents;

		Node() : value(), left(nullptr), right(nullptr), parents(nullptr) {}
		Node(Node *left, Node *right, Node *parents) : value(), left(left), right(right), parents(parents) {}
		Node(value_type value, Node *left, Node *right, Node *parents) : value(value), left(left), right(right), parents(parents) {}
		Node(Node &copy) : value(copy.value), left(copy.left), right(copy.right), parents(copy.parents) {}
		~Node() {}
		
	};
	
}

# endif