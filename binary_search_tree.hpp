/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:50:18 by pweinsto          #+#    #+#             */
/*   Updated: 2022/06/04 18:05:04 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

# include <map>
# include "Node.hpp"
# include "pair.hpp"

namespace ft
{
	template <class T, class Compare = std::less<typename T::first_type>, /*class Alloc = std::allocator<T>,*/ class Node = ft::Node<T>, class Node_alloc = std::allocator<Node> >
	class Binary_search_tree
	{
		public:
		typedef T	value_type;
		typedef Node node_type;
		typedef Node_Alloc node_alloc;
		typedef Compare	key_compare;
		typedef ft::bidirectional_iterator	iterator
		typedef Alloc	allocator_type;
		
		



		
		// Binary_search_tree() : root(nullptr) {}
		// Binary_search_tree(Node *root) : root(root) {}
		Binary_search_tree(const node_alloc& node_alloc_init = node_alloc()) : _node_alloc(node_alloc_init)
		{
			_last_node = _node_alloc.allocate(1);
			_node_alloc.construct(_last_node, Node(_last_node, _last_node, _last_node));
		}
		//Binary_search_tree(const key_compare &comp, const allocator_type &alloc) : size(), 

		~Binary_search_tree()
		{
			_node_alloc.destroy(_last_node);
			_node_alloc.deallocate(_last_node, 1);
		}

		ft::pair<iterator, bool> insertPair(value_type to_insert)
		{
			Node	*new_node = _node_alloc.allocate(1);
			Node	*prev_node = _last_node;
			Node	*start_node = _last_node->parent;

			bool	side = true;
			while (start_node != _last_node)
			{
				int	curkey = start_node->value.first; // just int as keys. needs to be fixed
				if (curkey == to_insert.first)
					return ft::pair<iterator, bool>(iterator(start_node, _last_node), false);
				prev_node = start_node;
				if (to_insert.first > curkey)
				{
					side = true;
					start_node = start_node->right;
				}
				else
				{
					side = false;
					start_node = start_node->left;
				}
			}
			_node_alloc.construct(new_node, Node(to_insert, prev_node, _last_node, _last_node));

				if (prev_node == _last_node)
					_last_node->parent = new_node;
				else if (side == true)
					prev_node->right = new_node;
				else
					prev_node->left = new_node;

				_last_node->left = _BST_get_lower_node(_last_node->parent);
				_last_node->right = _BST_get_higher_node(_last_node->parent);
				_last_node->value.first += 1;
				return ft::pair<iterator, bool>(iterator(new_node, _last_node), true);
		}
		
		private:


		node_type	*_BST_get_lower_node(node_type *root)
		{
			while (root != _last_node && root->left != _last_node)
				root = root->left;
				return root;
		}

		node_type	*_BST_get_higher_node(node_type *root)
		{
			while (root != _last_node && root->right!= _last_node)
				root = root->right;
				return root;
		}

		node_type	*_root;
		node_type	*_last_node;
		node_alloc	_node_alloc;
		size_t	_size
	};
}

# endif