#include <iomanip>
//  tree_extra.hpp
//  Name: J.Brandon Van Philips
//  Assignment number: 3
//  Assignment: Binary tree
//  Date last modified: 
//  Honor statement: I have neither given nor received any unauthorized help on this assignment.

// Draws the binary tree rooted at t.  
// Parameter link is a symbol to print in front of the node to
// which t points indicating the direction of the branch leading 
// to the node.
// Parameter depth is proportional to depth of the node to which p
// points.	  
template <typename T>
static void draw(Node<T> *t, char link, int depth=0) {
	if(t)
	{
		draw(t->right, '/', depth + 4);
		std::cout << std::setw(depth*2) << link << '[' << t->data << ']' << "\n";
		draw(t->left, '\\', depth + 4);
	}

}


// Frees up the space held by the nodes in a binary tree 
// rooted at t.
template <typename T>
void dispose(Node<T> *t) {
  

	if(t->right)
	{
		dispose(t->right);
	}
	if (t->left)
	{
		dispose(t->left);
	}
	delete t;

}


// Builds a binary tree from preorder and inorder traversals.
// Parameter pre_begin is an iterator to the beginning of the
// preorder traveral sequence.
// Parameter pre_end is an iterator to the end of the preorder 
// traveral sequence.
// Parameter in_begin is an iterator to the beginning of the
// inorder traveral sequence.
// Parameter in_end is an iterator to the end of the inorder
// traveral sequence.
// Returns a pointer to the root of the newly created binary tree.
template <typename T>
static Node<T> *build_tree(typename std::vector<T>::const_iterator pre_begin, 
                           typename std::vector<T>::const_iterator pre_end,
                           typename std::vector<T>::const_iterator in_begin, 
                           typename std::vector<T>::const_iterator in_end)
{
	Node<T> *root = nullptr;
	if (in_begin != in_end)
	{
		auto data = *pre_begin;
		auto place = pre_begin;
		
		Node<T> *left = nullptr;
		Node<T> *right = nullptr;
		for(;place!=pre_end;place++)
		{ 
			if (*pre_begin == data)
			{
				left = build_tree<T>(
					pre_begin + 1,
					std::find(pre_begin, pre_end, *((std::find(in_begin, in_end, *pre_begin) - 1))),
					in_begin,
					std::find(in_begin, in_end, *pre_begin));

				right = build_tree<T>(std::find(pre_begin, pre_end, *(std::find(in_begin, in_end, *pre_begin) - 1)) + 1, pre_end, std::find(in_begin, in_end, *pre_begin) + 1, in_end);
			}
		}
		root = new Node<T>(data, left, right);
	}
	return root;


}
