#include "List.h"
#include "iostream"
#include "Constants.cpp"
using namespace std;

int max(int first, int second) {
	if (first > second) {
		return first;
	}
	return second;
}

Node* List::createSublist(int row, int** inputs, int variablesCount) {
	int i = 0;
	Node* list = nullptr;
	Node* prevPoly = nullptr;
	Node* head = list;
	while (i < variablesCount) {
		head = new Node();
		if (prevPoly != nullptr) {
			prevPoly->setDlink(head);
		}
		if (i == 0) {
			list = head;
		}
		head->setTag(HEAD);
		head->setVar(variables[i]);
		Node* data = new Node();
		data->setExp(inputs[row][variablesCount - i]);
		if (i == variablesCount - 1) {
			data->setTag(COEF);
			data->setCoef(inputs[row][0]);
			prevPoly = data;
			head->setLink(data);
			head = data->getDlink();
			break;
		}
		else {
			data->setTag(POLY);
		}
		prevPoly = data;
		head->setLink(data);
		head = data->getDlink();
		i++;
	}
	return list;
}

void List::createMainList(Node* baseList, int** inputs, int variablesCount, int sentencesCount) {
	for (int i = 1; i < sentencesCount; i++) {
		Node* secondaryList = createSublist(i, inputs, variablesCount);
		combine(baseList, secondaryList);
	}

}
void List::combine(Node* baseList, Node* secondaryList) {
	Node* p = baseList;
	Node* q = secondaryList;
	while (q != nullptr) {
		if (Node::areEqualNodes(p, q)) {
			if (p->getTag() == POLY && q->getTag() == POLY) {
				combine(p->getDlink(), q->getDlink());
			}
			Node* temp = q;
			q = q->getLink();
			delete temp;
		}
		else {
			if (p->getLink() != nullptr) {
				p = p->getLink();
			}
			else {
				p->setLink(q);
				break;
			}
		}
	}
}
List::List(int** matrix, int variablesCount, int sentencesCount) {
	Node* baseList = createSublist(0, matrix, variablesCount);
	createMainList(baseList, matrix, variablesCount, sentencesCount);
	head = baseList;
}
List::List(Node* head) {
	this->head = head;
}
Node* List::getHead()
{
	return head;
}
int List::findDepthRecursive(Node* list) {
	Node* q = list;
	int depth = 0;
	while (q) {
		if (q->getTag() == POLY) {
			int newDepth = findDepthRecursive(q->getDlink()) + 1;
			depth = max(depth, newDepth);
		}
		q = q->getLink();
	}
	return depth;
}
int List::findDepth() {
	Node* list = head;
	return findDepthRecursive(list);
}
Node* List::cloneListRecursive(Node* list) {
	Node* p = list;
	Node* head = p->getClone();
	Node* q = head;
	while (p) {
		int pTag = p->getTag();
		if (pTag == POLY) {
			Node* cloned = cloneListRecursive(p->getDlink());
			Node* clonedP = p->getClone();
			clonedP->setDlink(cloned);
			q->setLink(clonedP);
			q = q->getLink();
		}
		else if (pTag == COEF) {
			Node* cloned = p->getClone();
			q->setLink(cloned);
			q = q->getLink();
		}
		p = p->getLink();
	}
	return head;
}
List List::cloneList() {
	Node* list = head;
	return List(cloneListRecursive(list));
}
void List::printRecursive(Node* list) {
	Node* q = list;
	char var = q->getVar();
	while (q) {
		if (q->getTag() == POLY) {
			int qExp = q->getExp();
			if (qExp == 1) {
				cout << "+" << var << "( ";
			}
			else if (qExp != 0) {
				cout << "+" << var << "^" << qExp << "( ";
			}
			else {
				cout << "+( ";
			}
			printRecursive(q->getDlink());
			cout << ") ";
		}
		else if (q->getTag() != HEAD) {
			int qCoef = q->getCoef();
			int qExp = q->getExp();
			if (qCoef > 0) {
				if (qExp == 0) {
					cout << "+" << q->getCoef() << " ";
				}
				else if (qExp == 1) {
					cout << "+" << q->getCoef() << var << " ";
				}
				else {
					cout << "+" << qCoef << var << "^" << qExp << " ";
				}
			}
			else if (qCoef < 0) {
				if (q->getExp() == 0) {
					cout << q->getCoef() << " ";
				}
				else if (qExp == 1) {
					cout << q->getCoef() << var << " ";
				}
				else {
					cout << q->getCoef() << var << "^" << q->getExp() << " ";
				}
			}
		}
		q = q->getLink();
	}
}
void List::print()
{
	Node* list = head;
	printRecursive(list);
}
bool List::areSameList(Node* firstList, Node* secondList) {
	Node* p = firstList;
	Node* q = secondList;
	bool areEqual = false;
	while (p || q) {
		if (p == nullptr || q == nullptr) {
			return false;
		}
		int ptag = p->getTag();
		int qtag = q->getTag();
		if (qtag != ptag) {
			return false;
		}
		if (ptag == POLY) {
			areEqual = areSameList(p->getDlink(), q->getDlink()) && Node::areEqualNodes(p, q);
		}
		else if (ptag == COEF) {
			areEqual = Node::areEqualNodes(p, q);
		}
		if (p->getTag() != HEAD && q->getTag() != HEAD && !areEqual) return false;
		p = p->getLink();
		q = q->getLink();
	}
	return areEqual;
}

void List::multiplyByANumberRecursive(Node* list, int number) {
	Node* p = list;
	while (p) {
		int tag = p->getTag();
		if (tag == POLY) {
			multiplyByANumberRecursive(p->getDlink(), number);
		}
		else if (tag == COEF) {
			p->setCoef(p->getCoef() * number);
		}
		p = p->getLink();
	}
}
void List::multiplyByANumber(int number) {
	Node* list = head;
	multiplyByANumberRecursive(list, number);
}
bool List::checkIfExistsRecursive(Node* list, int coef, int* exps, int depth) {
	Node* p = list;
	Node* head = list;
	bool exists = false;
	while (p) {
		int pTag = p->getTag();
		if (pTag == POLY) {
			bool recExists = checkIfExistsRecursive(p->getDlink(), coef, exps, depth + 1);
			exists = head->getVar() == variables[depth] && p->getExp() == exps[depth] && recExists;
		}
		else if (pTag == COEF) {
			exists = p->getCoef() == coef && head->getVar() == variables[depth] && p->getExp() == exps[depth];
		}
		if (exists && pTag != HEAD) return true;
		p = p->getLink();
	}
	return exists;
}
bool List::checkIfExists(int coef, int* exps, int depth) {
	Node* list = head;
	return checkIfExistsRecursive(list, coef, exps, depth);
}
void List::deleteSublistRecursive(Node* list, int coef, int* exps, int depth) {
	Node* p = list;
	Node* head = list;
	Node* prev = NULL;
	while (p) {
		int pTag = p->getTag();
		if (pTag == POLY) {
			if (p->getExp() == exps[depth] && head->getVar() == variables[depth]) {
				deleteSublistRecursive(p->getDlink(), coef, exps, depth + 1);
			}
			if (p->getDlink()->getLink() == nullptr) {
				delete p->getDlink();
				p->setDlink(nullptr);
				prev->setLink(p->getLink());
				delete p;
				return;
			}
		}
		else if (pTag == COEF) {
			if (p->getCoef() == coef && p->getExp() == exps[depth] && head->getVar() == variables[depth]) {
				Node* q = head;
				prev->setLink(p->getLink());
				delete p;
				return;
			}
		}
		prev = p;
		p = p->getLink();
	}
}
void List::deleteSublist(int coef, int* exps, int depth) {
	Node* list = head;
	deleteSublistRecursive(list, coef, exps, depth);
}
int List::calculateRecursive(Node* list, int* values, int depth) {
	Node* p = list;
	int sum = 0;
	while (p) {
		int tag = p->getTag();
		if (tag == POLY) {
			int sublistSum = calculateRecursive(p->getDlink(), values, depth + 1);
			sum += pow(values[depth], p->getExp()) * sublistSum;
		}
		else if (tag == COEF) {
			int pExp = p->getExp();
			int pCoef = p->getCoef();
			int power = pow(values[depth], pExp);
			sum += power * pCoef;
		}
		p = p->getLink();
	}
	return sum;
}
int List::calculate(int* values) {
	Node* list = head;
	return calculateRecursive(list, values);
}

void List::calculateSumRecursive(Node* firstList, Node* secondaryList) {
	Node* q = secondaryList;
	while (q) {
		bool found = false;
		Node* temp = firstList;
		while (temp) { 
			if (Node::areEqualNodesExceptCoef(temp, q)) {
				found = true;
				if (q->getTag() == COEF) {
					temp->setCoef(temp->getCoef() + q->getCoef());
				}
				else if (q->getTag() == POLY && temp->getTag() == POLY) {
					calculateSumRecursive(temp->getDlink(), q->getDlink());
				}
				break;
			}
			temp = temp->getLink();
		}
		if (!found) {
			Node* newNode = q->getClone();
			if (q->getTag() == POLY && q->getDlink()) {
				Node* sublist = q->getDlink()->getClone();
				calculateSumRecursive(sublist, q->getDlink());
				newNode->setDlink(sublist);
			}
			Node* k = firstList;
			while (k->getLink() && k->getLink()->getExp() > newNode->getExp()) {
				k = k->getLink();
			}
			newNode->setLink(k->getLink());
			k->setLink(newNode);
		}
		q = q->getLink();
	}
}

Node* List::calculateSum(List firstList, List secondList) {
	Node* firstHead = firstList.cloneList().getHead();
	Node* secondHead = secondList.getHead();
	calculateSumRecursive(firstHead, secondHead);
	return firstHead;
}

void List::clearRecursive(Node* list) {
	Node* p = list;
	while (p) {
		int pTag = p->getTag();
		if (pTag == POLY) {
			clearRecursive(p->getDlink());
		}
		if (pTag != HEAD) {
			Node* temp = p;
			p = p->getLink();
			delete temp;
		}
		else {
			p = p->getLink();
		}
	}
	delete list;
}
void List::clear()
{
	Node* list = head;
	clearRecursive(list);
	head = nullptr;
}

//operators : 
List List::operator*(int coef)
{
	List result = this->cloneList();
	result.multiplyByANumber(coef);
	return result;
}

List List::operator+(List other)
{
	return List::calculateSum(this->cloneList(), other);
}
