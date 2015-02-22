/*
 * Derek Prince
 * Assignment 5
 * CU - Boulder
 * CSCI 2270 - Algorithms and Datastructures - Rhonda Hoenigman
 * Binary Search Tree
*/

#include<iostream>
#include<fstream>
#include<string>
#include"MovieTree.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;



int main(int argc, char* argv[])
{
	MovieTree* database = new MovieTree;
	std::ifstream in_file;
	if(argc >= 1)
		in_file.open(argv[1]);

	if (in_file.is_open())
	{
		int rating, year, quantity;
		string title, buffer;
		while (!in_file.eof())
		{
			getline(in_file, buffer, ',');
			rating = stoi(buffer);
			getline(in_file, buffer, ',');
			title = buffer;
			getline(in_file, buffer, ',');
			year = stoi(buffer);
			getline(in_file, buffer);
			quantity = stoi(buffer);
			database->addRawNode(rating, title, year, quantity);
		}
	}
	else
	{
		cout << argv[1] << "----File was not found. Check local directory for" << argv[1] << "----" << endl;
		return 0;
		//could also -> while(!in_file.is_open()) {...requent new input... open()}
	}
	in_file.close();

	int select = -1;
	while (select != 4)
	{
		string title;
		cout << "======Main Menu======" << endl
			<< "1. Find a Movie" << endl
			<< "2. Rent a Movie" << endl
			<< "3. Print Inventory" << endl
			<< "4. Quit" << endl
			<< "======================" << endl;
		cin >> select;
		switch (select)
		{
		case 1:
			cout << "Movie title: ";
			cin >> title;
			database->search(title);
			break;
		case 2:
			cout << "Movie title: ";
			cin >> title;
			database->rentMovie(title);
			break;
		case 3:
			database->inorder_walk();
			break;
		default:
			cout << "That was not an option" << endl;
			break;
		}
	}





	return 0;
}