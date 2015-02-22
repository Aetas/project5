#include<iostream>
#include<string>
#include "MovieTree.h"

//******************
//-FREEEEEBIRD-
//******************

std::ostream& operator<<(std::ostream& os, MovieNode* n)
{
	os << n->ranking << " " << n->title << " " << n->year << " " << n->quantity << std::endl;
	return os;
}

//******************
//-MOVIE_NODE-
//******************
MovieNode::MovieNode()
{
	parent = nullptr;
	title = "";
	year = -1;
	quantity = -1;
	ranking = -1;
	left = nullptr;
	right = nullptr;
}

MovieNode::MovieNode(int rating, std::string ttl, int yr, int qtty)
{
	parent = nullptr;
	title = ttl;
	year = yr;
	quantity = qtty;
	ranking = rating;
	left = nullptr;
	right = nullptr;
}

MovieNode::MovieNode(MovieNode* p, int rating, std::string ttl, int yr, int qtty)
{
	parent = p;
	title = ttl;
	year = yr;
	quantity = qtty;
	ranking = rating;
	left = nullptr;
	right = nullptr;
}

MovieNode::~MovieNode()
{

}

//******************
//-END MOVIE_NODE-
//******************



//******************
//-MOVIE_TREE
//******************

MovieTree::MovieTree()
{
	root = nullptr;
}

MovieTree::~MovieTree()
{

}

void MovieTree::addRawNode(int rank, std::string ttl, int yr, int qtty)
{
	MovieNode* n = new MovieNode(rank, ttl, yr, qtty);
	insert(n);
}

void MovieTree::rentMovie(std::string ttl)
{
	MovieNode* n = search(ttl);
	n->quantity--;
	std::cout << n;
}

MovieNode* MovieTree::search(std::string ttl)
{
	MovieNode* n = root;
	if (n == nullptr || n->title == ttl)
		return n;
	if (strcmp(ttl.c_str(), n->title.c_str()) < 0)
		return search(n->left, ttl);
	else
		return search(n->right, ttl);
}

MovieNode* MovieTree::search(MovieNode* n, std::string ttl)
{
	if (n == nullptr || n->title == ttl)
		return n;
	if (strcmp(ttl.c_str(), n->title.c_str()) < 0)
		return search(n->left, ttl);
	else
		return search(n->right, ttl);
}

MovieNode* MovieTree::iterative_search(std::string ttl)
{
	MovieNode* n = root;
	while (n != nullptr && ttl != n->title)
	{
		if (strcmp(ttl.c_str(), n->title.c_str()) < 0)
			n = n->left;
		else
			n = n->right;
	}
	return n;
}

void MovieTree::inorder_walk()
{
	MovieNode* n = root;
	if (n != nullptr)
	{
		inorder_walk(n->left);
		std::cout << n;
		inorder_walk(n->right);
	}
}

void MovieTree::inorder_walk(MovieNode* n)
{
	if (n != nullptr)
	{
		inorder_walk(n->left);
		std::cout << n;
		inorder_walk(n->right);
	}
}

//minimum from root (whole tree)
MovieNode* MovieTree::minimum()
{
	MovieNode* n = root;
	while (n->left != nullptr)
		n = n->left;
	return n;
}

//minimum for specified tree (sub-tree)
MovieNode* MovieTree::minimum(MovieNode* n)
{
	while (n->left != nullptr)
		n = n->left;
	return n;
}

//max from root (whole tree)
MovieNode* MovieTree::maximum()	
{
	MovieNode* n = root;
	while (n->right != nullptr)
		n = n->right;
	return n;
}

//max from specified tree (sub-tree)
MovieNode* MovieTree::maximum(MovieNode* n)
{
	while (n->right != nullptr)
		n = n->right;
	return n;
}

MovieNode* MovieTree::successor(MovieNode* n)
{
	if (n->right != nullptr)
		return minimum(n);
	MovieNode* trail = n->parent;	//trailing pointer
	while (trail != nullptr && n == trail->right)		//so long as trail is pointing at something and ascending the tree, n will be larger so long as it is on the right
	{
		n = trail;
		trail = trail->parent;	//could just as easily have been "trail = n->get_parent();"
	}
	return trail;
}

MovieNode* MovieTree::predecessor(MovieNode* n)
{
	if (n->right != nullptr)
		return maximum(n);
	MovieNode* trail = n->parent;	//trailing pointer
	while (trail != nullptr && n == trail->left)		//same as successor, but looking at the other side of the tree for mirrored result
	{
		n = trail;
		trail = trail->parent;	//could just as easily have been "trail = n->get_parent();"
	}
	return trail;
}

//global insert from root
void MovieTree::insert(MovieNode* new_node)
{
	MovieNode* n = root;
	MovieNode* trail = nullptr;
	while (n != nullptr)	//if the tree is not empty, find the new node's sub tree
	{
		trail = n;			//trailing pointer
		if (strcmp(new_node->title.c_str(), n->title.c_str()) < 0)
			n = n->left;	//if the new key is smaller, go left
		else
			n = n->right;
	}
	new_node->parent = trail;
	if (trail == nullptr)
		root = new_node;
	else if (strcmp(new_node->title.c_str(), trail->title.c_str()) < 0)
		trail->left = new_node;
	else
		trail->right = new_node;
}

//insert that starts in a specified sub tree
void MovieTree::insert(MovieNode* start, MovieNode* new_node)
{
	MovieNode* n = start;
	MovieNode* trail = nullptr;
	while (n != nullptr)	//if the tree is not empty, find the new node's sub tree
	{
		trail = n;			//trailing pointer
		if (strcmp(new_node->title.c_str(), n->title.c_str()) < 0)
			n = n->left;	//if the new key is smaller, go left
		else
			n = n->right;
	}
	new_node->parent = trail;
	if (trail == nullptr)
		root = new_node;
	else if (strcmp(new_node->title.c_str(), trail->title.c_str()) < 0)
		trail->left = new_node;
	else
		trail->right = new_node;
}

void MovieTree::transplant(MovieNode* u, MovieNode* v)
{
	if (u->parent == nullptr)
		root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	if (v != nullptr)
		v->parent = u->parent;
}

void MovieTree::delete_node(MovieNode* del_node)	//holy buttshit, Batman
{
	if (del_node->left == nullptr)
		transplant(del_node, del_node->right);
	else if (del_node->right == nullptr)
		transplant(del_node, del_node->left);
	else
	{
		MovieNode* trail = minimum(del_node->right);
		if (trail->parent != del_node)
		{
			transplant(trail, trail->right);
			trail->right = del_node->right;
			trail->parent->right = trail;	//since the delete node was just set to trail, this is setting the newly aquired tree to see trail as parent
		}
		transplant(del_node, trail);
		trail->left = del_node->left;
		trail->left->parent = trail;
	}
}

//******************
//-END MOVIE_TREE
//******************