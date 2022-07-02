/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:50:18 by pweinsto          #+#    #+#             */
/*   Updated: 2022/07/02 16:54:01 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

# include <map>
# include "Node.hpp"
# include "pair.hpp"
//# include <iterator>	//just for testing
#include "iterator.hpp"
# include "less.hpp"
# include <iostream> //debugging
# include <typeinfo>

namespace ft
{
	template <class T, class Compare = ft::less<typename T::first_type>, /*class Alloc = std::allocator<T>,*/ class Node = ft::Node<T>, class Node_Alloc = std::allocator<Node> >
	class Binary_search_tree
	{
		public:
		typedef T	value_type;
		typedef Node node_type;
		typedef Node_Alloc node_alloc;
		typedef Compare	key_compare;
		typedef typename node_alloc::pointer	pointer;
		typedef typename node_alloc::const_pointer const_pointer;
		// typedef ft::bst_iterator<node_type, key_compare>	iterator;
		// typedef ft::bst_iterator<node_type, key_compare>	const_iterator;
		typedef ft::bst_iterator<bidirectional_iterator_tag, node_type, key_compare>	iterator;
		typedef ft::bst_const_iterator<bidirectional_iterator_tag, node_type, key_compare>	const_iterator;



		
		// typedef std::iterator<std::bidirectional_iterator_tag, value_type>	iterator;		//just for testing
		// typedef std::iterator<std::bidirectional_iterator_tag, value_type> const	const_iterator;	
		//typedef Alloc	allocator_type;
		
		



		
		// Binary_search_tree() : root(nullptr) {}
		// Binary_search_tree(Node *root) : root(root) {}
		Binary_search_tree(const node_alloc& node_alloc_init = node_alloc()) : _node_alloc(node_alloc_init)
		{
			_last_node = _node_alloc.allocate(1);
			// std::allocator<ft::Node<ft::pair<int, int> > >	test;
			// _last_node = test.allocate(1);
			_node_alloc.construct(_last_node, Node(_last_node, _last_node, _last_node));
			_size = 0;
		}
		//Binary_search_tree(const key_compare &comp, const allocator_type &alloc) : size(), 

		~Binary_search_tree()
		{
			_node_alloc.destroy(_last_node);
			_node_alloc.deallocate(_last_node, 1);
		}

		ft::pair<iterator, bool> insertPair(value_type to_insert)
		{
			Node	*new_node = _node_alloc.allocate(1);	//allocate the memory for to_insert
			Node	*prev_node = _last_node;
			Node	*start_node = _last_node->parent;

			bool	side = true;
			while (start_node != _last_node) 				//check if the BST already has a node, or if we already reached a leaf
			{
				int	curkey = start_node->value.first; 		// just int as keys. needs to be fixed
				if (curkey == to_insert.first) 				//check if a node with to_inserts key already excists
					return ft::make_pair(iterator(start_node, _last_node), false); //return the iterator of the already excisting node and flase for insertion not valid (failure)
				prev_node = start_node;						//save the current node as the previous node
				if (to_insert.first > curkey)				//check if the to_inserts key is bigger than the current key
				{
					side = true;							// true for right side
					start_node = start_node->right;			// update the start_node to start_nodes rightchild
				}
				else										//if the to_inserts key is samller than the current key
				{
					side = false;							// flase for left side
					start_node = start_node->left;			//update the start_node to start_nodes leftchild
				}
			}
			_node_alloc.construct(new_node, Node(to_insert, prev_node, _last_node, _last_node));//construct new_node with prev_node as parent and _last_node as it's childs

				if (prev_node == _last_node)				//check if new_node is the root
					_last_node->parent = new_node;			//update the root node in _last_node->parent
				else if (side == true)						//check if new_node is a rightchild
					prev_node->right = new_node;			//change the rightchild of new_nodes parent to new_node
				else										//if new_node is a leftchild
					prev_node->left = new_node;				//change the leftchild of new_nodes parent to new_node

				_last_node->left = _BST_get_lower_node(_last_node->parent); // update the lowest node in _last_node->left
				_last_node->right = _BST_get_higher_node(_last_node->parent);// update the highest node in _last_node->right
				//_last_node->value.second += 1;				//increase the size of the BST by one
				_size += 1;
				return ft::pair<iterator, bool>(iterator(new_node, _last_node), true);	//return the iterator of the new_node and true for success
		}

		void	removeByKey(value_type to_remove)
		{
			_removeByKey(_last_node->parent, to_remove);
		}
		
 

		node_type	*searchByKey(value_type to_remove)
		{
			node_type	*node = _last_node->parent;

			while (node != _last_node)
			{
				if (node->value.first == to_remove.first)
					return (node);
				if (node->value.first > to_remove.first)
					node = node->left;
				else
					node = node->right;
			}
			return node;
		}
		
		node_type	*_last_node;
		node_alloc	_node_alloc;
		size_t		_size;
		
		private:
		
		node_type	*_BST_get_lower_node(node_type *root)				// iterates until the most left node
		{
			while (root != _last_node && root->left != _last_node)
				root = root->left;
				return root;
		}

		node_type	*_BST_get_higher_node(node_type *root)			// iterates until the most right node
		{
			while (root != _last_node && root->right!= _last_node)
				root = root->right;
				return root;
		}

		

		void	_replaceNodeInParent(node_type *node, node_type *new_node)
		{
			if (node->parent != _last_node)		//check if to_remove is not the root
			{
				if (_last_node->parent == node)			//doesn't make sense to me right now (update the root in _last_node)
					_last_node->parent = new_node;
				
				if (node == node->parent->left)			//check if to_remove is a leftchild
					node->parent->left = new_node;		//change to_removes parents leftchild to new_node
				else
					node->parent->right = new_node;		//change to_removes parents rightchild to new_node
			}
			else										// if to_remove is the root
				_last_node->parent = new_node;			// update the root in _last_node->parent with new_node

			_last_node->left = _BST_get_lower_node(_last_node->parent); //assign the lowest node to _last_node->left
			_last_node->right = _BST_get_higher_node(_last_node->parent); //assign the highest node to _last_node->right
			//_last_node->value.second -= 1;
			_size -= 1;
			//std::cout << "type: " << typeid(_last_node->value.second).name() << std::endl;										//decrease the size of the BST by one

			new_node->parent = node->parent;			//change new_nodes parent to to_removes parent

			_node_alloc.destroy(node);				//destroy to_remove
			_node_alloc.deallocate(node, 1);		//deallocate to_remove
		}

		void	_replaceDoubleChildren(node_type *to_remove, node_type *new_node)
		{
			if (new_node->parent != _last_node)				// check if the successor is not the root
			{
				if (new_node->parent != to_remove)			// check if the parent of the successor is not to_remove
					new_node->parent->left = new_node->right; 	// change the left pointer of the parent of the successor to the right pointer of the successor
			}
			new_node->parent = to_remove->parent;			// change the parent of the successor to the parent of to_remove
			if (to_remove->left != new_node)				// I don't think thats necessary because to_remove-> left can never be new_node
				new_node->left = to_remove->left;			// change the left pointer of the successot to the left pointer of to_remove
			if (to_remove->right != new_node)				// i think this could be possible
				new_node->right = to_remove->right;
			
			if (to_remove->parent != _last_node) 			//check if to_remove is not the root
			{
				if (to_remove->parent->left == to_remove)	//check if to_remove is a leftchild
					to_remove->parent->left = new_node;		//change the to_remove parents leftchild to new_node
				else if (to_remove->parent->right == to_remove) // check if to_remove is a rightchild
					to_remove->parent->right = new_node;		//change the to_remove parents rightchild to new_node
			}
			else											// if to_remove is the root node
				_last_node->parent = new_node;				//update _last_node->parent with the new root node
			
			
			if (to_remove->left != _last_node && to_remove->left != new_node)	//check if to_remove has a leftchild and that it is not the successor
				to_remove->left->parent = new_node;								//change the to_removes leftchilds parent to the successor
			if (to_remove->right != _last_node && to_remove->right != new_node)	//check if to_remove has a rightchild and that it is not the successor
				to_remove->right->parent = new_node;
			

			if (to_remove->parent != _last_node)		//check if to_remove is not the root
			{
				to_remove->left = _last_node;			//I don't know why this is neccessary
				to_remove->right = _last_node;
				to_remove->parent = new_node;
			}

			_last_node->left = _BST_get_lower_node(_last_node->parent);		//get the lowest node and assign it to _last_node->left
			_last_node->right = _BST_get_higher_node(_last_node->parent);		//get the highest node and assign it to _last_node->right
			//last_node->value.second -= 1;										// decrease the size of the BST by one
			_size -= 1;
			_node_alloc.destroy(to_remove);					//destroy to_remove
			_node_alloc.deallocate(to_remove, 1);			//deallocate to_remove
		}
		

		void	_removeByKey(Node *node, value_type to_remove)
		{
			if (to_remove.first < node->value.first)			// recursive call to find the node to remove
			{
				_removeByKey(node->left, to_remove);
				return;
			}

			if (to_remove.first > node->value.first)
			{
				_removeByKey(node->right, to_remove);
				return;
			}
			
			if (node->left != _last_node && node->right != _last_node)		// if the found node is not a leafnode
			{
				Node	*successor = _BST_get_lower_node(node->right);		// find the successor of that node
				_replaceDoubleChildren(node, successor);					// replace the to_remove node with the successor node
				return;
			}
			else if (node->left != _last_node)		//if node has a leftchild but not a right child
				_replaceNodeInParent(node, node->left); // replace the to_remove node with the successor node
			else if (node->right != _last_node)		//if node has a rightchild but not a leftchild
				_replaceNodeInParent(node, node->right);	//replace the t-remove node with the successor node
			else									//if node is a leafnode
				_replaceNodeInParent(node, _last_node);	// remove to_remove
		}

		//node_type	*_root;

		//size_t	_size
	};
}

# endif