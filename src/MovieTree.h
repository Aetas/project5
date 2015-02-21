#ifndef MOVIETREE_H
#define MOVIETREE_H

struct MovieNode{
    int ranking;
    string title;
    int year;
    int quantity;
};

class MovieTree
{
    public:
        MovieTree();
        virtual ~MovieTree();
        void printMovieInventory();
        void addMovieNode(int, string, int, int);
        MovieNode* searchMovieTree(string);
        void rentMovie(string);
    protected:
    private:
        MovieNode *root;
};

#endif // MOVIETREE_H
