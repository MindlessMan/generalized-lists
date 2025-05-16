#pragma once
class Node {
private:
	char variable;
	float coef;
	int exp;
	int tag;
	Node* link;
	Node* dlink;
public:
	Node();
	void setLink(Node* link);
	Node* getLink();
	void setDlink(Node* dlink);
	Node* getDlink();
	void setExp(int exp);
	int getExp();
	void setVar(char variable);
	char getVar();
	void setCoef(float coef);
	float getCoef();
	void setTag(int tag);
	int getTag();
	Node* getClone();
	static bool areEqualNodes(Node* first, Node* second);
	static bool areEqualNodesExceptCoef(Node* q, Node* p);
};