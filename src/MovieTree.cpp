#include<iostream>
#include<string>
#include "MovieTree.h"

//******************
//-FREEEEEBIRD-
//******************

std::ostream& operator<<(std::ostream& os, MovieNode* n)
{
	os << "Movie: " << n->title << std::endl;
	return os;
}

//******************
//-MOVIE_NODE-
//******************
//default construct, never really used
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
//proper argument construct
MovieNode::MovieNode(int& rating, std::string& ttl, int& yr, int& qtty)
{
	parent = nullptr;
	title = ttl;
	year = yr;
	quantity = qtty;
	ranking = rating;
	left = nullptr;
	right = nullptr;
}

//destructor
MovieNode::~MovieNode()
{

}
//******************
//-END MOVIE_NODE-
//******************


//******************
//-MOVIE_TREE
//******************

//default construct
MovieTree::MovieTree()
{
	root = nullptr;
}

//default destructs
MovieTree::~MovieTree()
{
	void delete_tree(MovieNode*);
}

//used to pass raw data from main() into the MovieTree's domain, eliminating creation of objects in main. Keeps it tidy (to me)
void MovieTree::addRawNode(int& rank, std::string& ttl, int& yr, int& qtty)
{
	MovieNode* n = new MovieNode(rank, ttl, yr, qtty);	//creates real ndoe
	insert(n);	//finds the position it belongs in
}

//search for a movie by title (external)
MovieNode* MovieTree::search(std::string& ttl)
{
	MovieNode* n = root;	//start at root, this is the external call
	if (n == nullptr || n->title == ttl)	//basically, if the tree does not exist
		return n;
	if (ttl.compare(n->title) < 0)			//choose which branch ot go into and call self again to repeat
		return search(n->left, ttl);
	else
		return search(n->right, ttl);
}

//same as above but internal
MovieNode* MovieTree::search(MovieNode* n, std::string& ttl)
{
	if (n == nullptr || n->title == ttl)
		return n;
	if (ttl.compare(n->title) < 0)
		return search(n->left, ttl);
	else
		return search(n->right, ttl);
}

//a function a wrote for fun as prompted by the book. "This method is faster on most modern computers"
MovieNode* MovieTree::iterative_search(std::string& ttl)
{
	MovieNode* n = root;
	while (n != nullptr && ttl != n->title)	//instead of recursion calls, just while() it until it is found
	{
		if (ttl.compare(n->title) < 0)
			n = n->left;
		else
			n = n->right;
	}
	return n;
}

//external call to print entire tree
void MovieTree::inorder_walk()
{
	MovieNode* n = root;	//start at root
	if (n != nullptr || NULL)	//if there is still room to dive
	{
		inorder_walk(n->left);	//start small
		std::cout << n;			//custom ostream
		inorder_walk(n->right);	//then step down the large
	}
}

//same as above but internal
void MovieTree::inorder_walk(MovieNode* n)
{
	if (n != nullptr || NULL)
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
	while (n->left != nullptr || NULL)	//I don't think NULL is actually needed
		n = n->left;					//basically, just go left until you cant. That's the smallest
	return n;
}

//minimum for specified tree (sub-tree). same as above. Made for delete, really.
MovieNode* MovieTree::minimum(MovieNode* n)
{
	while (n->left != nullptr || NULL)
		n = n->left;
	return n;
}

//max from root (whole tree)
MovieNode* MovieTree::maximum()	
{
	MovieNode* n = root;		//mirror of minimum, as is the nature of binary
	while (n->right != nullptr)
		n = n->right;
	return n;
}

//max from specified tree (sub-tree). same as above. made for delete
MovieNode* MovieTree::maximum(MovieNode* n)
{
	while (n->right != nullptr || NULL)
		n = n->right;
	return n;
}

//find next largest in the tree
MovieNode* MovieTree::successor(MovieNode* n)
{
	if (n->right != nullptr || NULL)
		return minimum(n);			//if the right child is not empty, that is the successor
	MovieNode* trail = n->parent;	//trailing pointer
	while (trail != nullptr && n == trail->right)	//so long as trail is pointing at something and ascending the tree, n will be larger so long as it is on the right
	{
		n = trail;
		trail = trail->parent;	//could just as easily have been "trail = n->parent;"
	}
	return trail;
}

// find next smallest in tree
MovieNode* MovieTree::predecessor(MovieNode* n)
{
	if (n->left != nullptr || NULL)
		return maximum(n);			//if the left child exists, that is the predecessor
	MovieNode* trail = n->parent;	//trailing pointer
	while (trail != nullptr && n == trail->left)		//same as successor, but looking at the other side of the tree for mirrored result
	{
		n = trail;
		trail = trail->parent;	//could just as easily have been "trail = n->parent;"
	}
	return trail;
}

//global insert from root
void MovieTree::insert(MovieNode* new_node)
{
	MovieNode* n = root;	//start at root
	MovieNode* trail = nullptr;
	while (n != nullptr)	//if the tree is not empty, find the new node's sub tree
	{
		trail = n;			//trailing pointer
		if (new_node->title.compare(n->title) < 0)
			n = n->left;	//if the new key is smaller, go left
		else
			n = n->right;	//else go right
	}
	new_node->parent = trail;
	if (trail == nullptr)	//tree was not made, new node is root
		root = new_node;
	else if (new_node->title.compare(trail->title) < 0)
		trail->left = new_node;		//if smaller than parent, make left child
	else
		trail->right = new_node;	//if larger, makde right child
}

//insert that starts in a specified sub tree. Same as above. Used pretty much only for delete and transplant f()'s
void MovieTree::insert(MovieNode* start, MovieNode* new_node)
{
	MovieNode* n = start;
	MovieNode* trail = nullptr;
	while (n != nullptr)	//if the tree is not empty, find the new node's sub tree
	{
		trail = n;			//trailing pointer
		if (new_node->title.compare(n->title) < 0)
			n = n->left;	//if the new key is smaller, go left
		else
			n = n->right;
	}
	new_node->parent = trail;
	if (trail == nullptr)
		root = new_node;
	else if (new_node->title.compare(trail->title) < 0)
		trail->left = new_node;
	else
		trail->right = new_node;
}

//lets the delete() magic happen
void MovieTree::transplant(MovieNode* u, MovieNode* v)	//swaps u with v
{
	if (u->parent == nullptr)	//if u was root, make v new root
		root = v;
	else if (u == u->parent->left)	//if u is smaller than it's parent
		u->parent->left = v;		//set v to the left child of parent of u. Swap them at left, really
	else
		u->parent->right = v;		//otherwise swap them at right

	if (v != nullptr)				//reassign parents to double link
		v->parent = u->parent;
}

//maddening delete function
void MovieTree::delete_node(MovieNode* del_node)	//holy buttshit, Batman
{
	if (del_node->left == nullptr)					//if there is no left child
		transplant(del_node, del_node->right);		//swap left to right
	else if (del_node->right == nullptr)			//if there is no right child
		transplant(del_node, del_node->left);		//swap right to left
	else
	{
		MovieNode* temp = minimum(del_node->right);	//make temp the smallest node on the large branch of del_node
		if (temp->parent != del_node)				//if it is more than one chain down
		{
			transplant(temp, temp->right);			//swap temp and it's right branch
			temp->right = del_node->right;			//set right branch to del's right branch
			temp->parent->right = temp;				//set temp to the right child in it's tree
		}
		transplant(del_node, temp);					//now that it's always in the same form, transplant
		temp->left = del_node->left;				//aquire del_nodes left branch
		temp->left->parent = temp;					//replace del_node as the heir to the throne
	}
}

//deletes the whole tree network made in the movietree object. Independant from ~mov() to debug and use again
void MovieTree::delete_tree(MovieNode* rt)
{
	if (rt->left != NULL || rt->left != nullptr)		//find the extrema and work backwards from there
		delete_tree(rt->left);
	if (rt->right != NULL || rt->right != nullptr)
		delete_tree(rt->right);
	delete rt;
}
//******************
//-END MOVIE_TREE
//******************
