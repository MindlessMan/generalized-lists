
#include <iostream>
#include <fstream>
#include "string"
#include "Node.h"
#include "List.h"
#include "Constants.cpp"

using namespace std;

void clearConsole() {
	system("cls");
}

void sortMatrix(int column, int sentencesCount, int** inputs) {
	//Sort based on the last column, DEC
	for (int i = 0; i < sentencesCount; i++) {
		for (int j = 0; j < sentencesCount; j++) {
			if (inputs[i][column - 1] > inputs[j][column - 1]) {
				int* temp = new int[column];
				for (int k = 0; k < column; k++) {
					temp[k] = inputs[i][k];
				}
				for (int k = 0; k < column; k++) {
					inputs[i][k] = inputs[j][k];
				}
				for (int k = 0; k < column; k++) {
					inputs[j][k] = temp[k];
				}
			}
		}
	}
}

void initializeMatrix(int sentencesCount, int variablesCount, int**& inputs) {
	inputs = new int* [sentencesCount];
	for (int i = 0; i < sentencesCount; i++) {
		inputs[i] = new int[variablesCount + 1];
	}
}

void writeIntoMatrix(ifstream& file, int**& inputs, int& variablesCount, int& sentencesCount) {

	if (!file) {
		cerr << "cannot open file.";
		exit(-1);
	}
	string input1;
	getline(file >> ws, input1, '\t');
	variablesCount = stoi(input1);
	getline(file >> ws, input1, '\n');
	sentencesCount = stoi(input1);
	initializeMatrix(sentencesCount, variablesCount, inputs);

	for (int i = 0; i < sentencesCount; i++) {
		for (int j = 0; j < variablesCount + 1; j++) {
			char differ;
			if (j == variablesCount) {
				differ = '\n';
			}
			else {
				differ = '\t';
			}
			getline(file >> ws, input1, differ);
			inputs[i][j] = stoi(input1);
		}
	}

}

void readFile(int**& inputs, int**& inputs2, int& variablesCount,
	int& sentencesCount, int& variablesCount2, int& sentencesCount2) {

	ifstream file("input.txt");
	writeIntoMatrix(file, inputs, variablesCount, sentencesCount);
	writeIntoMatrix(file, inputs2, variablesCount2, sentencesCount2);
	file.close();

	sortMatrix(variablesCount + 1, sentencesCount, inputs);
	sortMatrix(variablesCount2 + 1, sentencesCount2, inputs2);
};
void printMatrix(int** matrix, int column, int row) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			cout << matrix[i][j] << '\t';
		}
		cout << endl;
	}
}
void printMenu() {
	cout << "1 - Print the list " << endl;
	cout << "2 - Print the list depth " << endl;
	cout << "3 - Check if it exists " << endl;
	cout << "4 - Delete sublist " << endl;
	cout << "5 - Multiply by a number " << endl;
	cout << "6 - Calculate value " << endl;
	cout << "7 - Check equality " << endl;
	cout << "8 - Calculate sum " << endl;
	cout << "9 - Clone the list " << endl;
	cout << "10 - Close the app " << endl;
}

int main()
{
	int** inputs = nullptr, ** inputs2;
	int variablesCount1, sentencesCount1, variablesCount2, sentencesCount2;

	readFile(inputs, inputs2, variablesCount1, sentencesCount1, variablesCount2, sentencesCount2);
	List list = List(inputs, variablesCount1, sentencesCount1);
	List secondList = List(inputs2, variablesCount2, sentencesCount2);

	printMenu();
	cout << endl << endl;

	while (true) {
		int command;
		cin >> command;
		switch (command)
		{
		case 1:
		{
			clearConsole();
			list.print();
			cout << endl << endl;
			printMenu();
			break;
		}
		case 2:
		{
			clearConsole();
			cout << "The depth is equal to " << list.findDepth() << endl << endl;
			printMenu();
			break;
		}
		case 3: {
			int* exps = new int[variablesCount1];
			int coef;
			clearConsole();
			cout << "Please enter a valid number as coef : " << endl;
			cin >> coef;
			for (int i = 0; i < variablesCount1; i++) {
				cout << "Please enter the exp for " << variables[i] << " : " << endl;
				cin >> exps[i];
			}
			clearConsole();
			bool result = list.checkIfExists(coef, exps);
			result ? cout << "Yes, it does exist!" << endl << endl : cout << "No, it dosent exist" << endl << endl;
			printMenu();
			break;
		}
		case 4:
		{
			int* exps = new int[variablesCount1];
			int coef;
			clearConsole();
			cout << "Please enter a valid number as coef : " << endl;
			cin >> coef;
			for (int i = 0; i < variablesCount1; i++) {
				cout << "Please enter the exp for " << variables[i] << " : " << endl;
				cin >> exps[i];
			}
			clearConsole();
			bool result, doesItExist = list.checkIfExists(coef, exps);
			if (!doesItExist) {
				result = false;
			}
			else {
				result = true;
				list.deleteSublist(coef, exps);
			}
			result ? cout << "it was Deleted successfully!" << endl << endl : cout << "it was Not found!" << endl << endl;
			printMenu();
			break;
		}
		case 5: {
			int coef;
			clearConsole();
			cout << "Please enter a valid number as coef : " << endl;
			cin >> coef;
			clearConsole();
			list.multiplyByANumber(coef);
			cout << "Multiplication was successfull." << endl << endl;
			printMenu();
			break;
		}
		case 6: {
			int* exps = new int[variablesCount1];
			clearConsole();
			for (int i = 0; i < variablesCount1; i++) {
				cout << "Please enter the exp for " << variables[i] << " : " << endl;
				cin >> exps[i];
			}
			clearConsole();
			cout << list.calculate(exps) << endl << endl;
			printMenu();
			break;
		}
		case 7: {
			bool result = List::areSameList(list.getHead(), secondList.getHead());
			clearConsole();
			if (result) {
				cout << "The lists are equal!";
			}
			else {
				cout << "The lists are NOT equal!";
			}
			cout << endl << endl;
			printMenu();
			break;
		}
		case 8: {
			List result = List::calculateSum(list.getHead(), secondList.getHead());
			clearConsole();
			result.print();
			result.clear();
			cout << endl << endl;
			printMenu();
			break;
		}
		case 9: {
			clearConsole();
			List cloned = list.cloneList();
			cloned.print();
			cout << endl << endl;
			printMenu();
			cloned.clear();
			break;
		}
		case 10: {
			exit(0);
		}
		default:
			break;
		}
	}
}
