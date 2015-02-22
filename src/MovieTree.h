#ifndef MOVIETREE_H
#define MOVIETREE_H

#include<string>

/*struct*/class MovieNode
{
public:
	MovieNode();
	MovieNode(int rank, std::string ttl, int yr, int qtty);
	MovieNode(MovieNode* p, int rank, std::string ttl, int yr, int qtty);
	virtual ~MovieNode();
	friend std::ostream& operator<<(std::ostream& os, MovieNode* n);

	MovieNode* parent;
	MovieNode* left;
	MovieNode* right;
    int ranking;
    std::string title;
    int year;
    int quantity;
};


class MovieTree
{
public:
	MovieTree();
	virtual ~MovieTree();

	void addRawNode(int, std::string, int, int);
	void rentMovie(std::string);

	void inorder_walk();			//external call to root
	void inorder_walk(MovieNode*);	//internal reccursive call
	MovieNode* search(std::string);				//finds node with the passed key
	MovieNode* search(MovieNode*, std::string);	//recursive, and sub-tree version of search 
	MovieNode* iterative_search(std::string);	//while version of search, non-recursive
	MovieNode* minimum();					//find min
	MovieNode* minimum(MovieNode*);			//find min of specified sub-tree
	MovieNode* maximum();					//find max
	MovieNode* maximum(MovieNode*);			//find max of specified sub-node
	MovieNode* successor(MovieNode*);		//next incriment
	MovieNode* predecessor(MovieNode*);		//next smaller
	void insert(MovieNode*);				//adds a new node
	void insert(MovieNode*, MovieNode*);	//adds a new node to a specified sub tree
	void transplant(MovieNode*, MovieNode*);//switches dangling trees on a parent
	void delete_node(MovieNode*);			//removes a node

private:
	MovieNode *root;

};

#endif // MOVIETREE_H
