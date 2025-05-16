#pragma once
#include "Node.h"

// Generalized list, which can be created using a Matrix read from the input file 
class List
{
private:

	Node* head;
	//Initializing the list
	Node* createSublist(int row, int** inputs, int variablesCount);
	
	void createMainList(Node* baseList, int** matrix,
		int variablesCount, int sentencesCount);
	void combine(Node* baseList, Node* sublist);

	//Recursive methods
	void printRecursive(Node* list);
	int findDepthRecursive(Node* list);
	bool checkIfExistsRecursive(Node* list, int coef, int* exps, int depth = 0);
	void deleteSublistRecursive(Node* list, int coef, int* exps, int depth = 0);
	void multiplyByANumberRecursive(Node* list, int number);
	int calculateRecursive(Node* list, int* values, int depth = 0);
	Node* cloneListRecursive(Node* list);
	void clearRecursive(Node* list);

	//Static
	static void calculateSumRecursive(Node* firstList, Node* secondList);

public:
	//Constructors
	List(int** matrix, int variablesCount, int sentencesCount);
	List(Node* head);
	//Getters
	Node* getHead();

	//Methods
	List cloneList();
	int findDepth();
	void print();
	void multiplyByANumber(int number);
	bool checkIfExists(int coef, int* exps, int depth = 0);
	void deleteSublist(int coef, int* exps, int depth = 0);
	int calculate(int* values);
	void clear();

	//Static
	static bool areSameList(Node* firstList, Node* secondList);
	static Node* calculateSum(List firstList, List secondList);

	//operators
	List operator*(int coef);
	List operator+(List other);
};

