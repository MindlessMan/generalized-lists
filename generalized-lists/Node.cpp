#include "Node.h"
Node::Node() {
	variable = ' ';
	coef = 0;
	exp = 0;
	tag = 0;
	link = dlink = nullptr;
}
void Node::setLink(Node* link) {
	this->link = link;
}
Node* Node::getLink() {
	return this->link;
}
void Node::setDlink(Node* dlink) {
	this->dlink = dlink;
}
Node* Node::getDlink() {
	return this->dlink;
}
void Node::setExp(int exp) {
	this->exp = exp;
}
int Node::getExp() {
	return this->exp;
}
void Node::setVar(char variable) {
	this->variable = variable;
}
char Node::getVar() {
	return this->variable;
}
void Node::setCoef(float coef) {
	this->coef = coef;
}
float Node::getCoef() {
	return this->coef;
}
void Node::setTag(int tag) {
	this->tag = tag;
}
int Node::getTag() {
	return this->tag;
}
Node* Node::getClone() {
	Node* clone = new Node();
	clone->setVar(this->getVar());
	clone->setCoef(this->getCoef());
	clone->setExp(this->getExp());
	clone->setTag(this->getTag());
	clone->setLink(nullptr);
	clone->setDlink(nullptr);
	return clone;
}

bool Node::areEqualNodes(Node* q, Node* p) {
	return p->getExp() == q->getExp() && p->getCoef()
		== q->getCoef() && p->getVar() == q->getVar() &&
		p->getTag() == q->getTag();
}
bool Node::areEqualNodesExceptCoef(Node* q, Node* p) {
	return p->getExp() == q->getExp() && p->getVar() == q->getVar() &&
		p->getTag() == q->getTag();
}
