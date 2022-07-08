/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:03:23 by pweinsto          #+#    #+#             */
/*   Updated: 2022/07/04 12:45:27 by pweinsto         ###   ########.fr       */
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
		public:
		typedef T	value_type;

		value_type	value;
		Node		*parent;
		Node		*left;
		Node		*right;

		Node() : value(), parent(nullptr) ,left(nullptr), right(nullptr) {}
		Node(Node *parent = nullptr, Node *left = nullptr, Node *right = nullptr) : value(), parent(parent), left(left), right(right) {}
		Node(const value_type value, Node *parent = nullptr, Node *left = nullptr, Node *right = nullptr) : value(value), parent(parent), left(left), right(right) {}
		//Node(Node &copy) : value(copy.value), parent(copy.parent), left(copy.left), right(copy.right) {}
		~Node() {}

		Node &operator=(Node& nd)
 		{
 			// if (nd == *this)
 			// 	return (*this);
		
 			this->value = nd.value;
 			this->parent = nd.parent;
 			this->left = nd.left;
 			this->right = nd.right;
		
 			return (*this);
 		}
	};
	
}

# endif