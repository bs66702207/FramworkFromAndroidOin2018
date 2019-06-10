#include <iostream>
#include <stdlib.h>

using namespace std;

#define DEBUG_1 0
#define DEBUG_2 1

typedef struct Node {
	int data;
	struct Node *pNext;
} Node, *PNode;

PNode createList();
void traverse(PNode pHead);
bool isEmpty(PNode pHead);
int getLength(PNode pHead);
bool insert(PNode pHead, int pos, int val);//元素从第一个开始计算，第零个是head
bool del(PNode pHead, int pos);
PNode locate(PNode pHead, int value, int& point);
PNode get(PNode pHead, int index);

PNode createList() {
	int nodeCount = 0;
	int temp;
	PNode pHead = (PNode)malloc(sizeof(Node));
	PNode pTail = pHead;
	pTail->pNext = NULL;

	cout << "please input the count of SingleLinkList" << endl;
	cin >> nodeCount;
	cout << "the count = " << nodeCount << endl;

	for(int i=0; i<nodeCount; i++) {
		cout << "please input the " << i << " node's value.";
		cin >> temp;
		cout << "the " << i << " node's value = " << temp << endl;
		PNode pNew = (PNode)malloc(sizeof(Node));
		pNew->data = temp;
		//拼接Node
		pTail->pNext = pNew;
		pTail = pNew;
		pTail->pNext = NULL;
	}

	return pHead;
}

void traverse(PNode pHead) {
	cout << "the result of traverse is:" << endl;
	PNode p = pHead;
	while(p->pNext != NULL) {
		cout << p->pNext->data << ", ";
		p = p->pNext;
	}
	cout << endl;
}

bool isEmpty(PNode pHead) {
	if(pHead->pNext == NULL)
		return true;
	else
		return false;
}

int getLength(PNode pHead) {
	int length = 0;
	PNode p = pHead;
	while(p->pNext != NULL) {
		if(DEBUG_1) cout << length << endl;
		length++;
		p = p->pNext;
	}
	return length;
}

bool insert(PNode pHead, int pos, int val) {
	if(pos < 1 || pos > getLength(pHead))
		return false;
	PNode p = pHead;
	for(int i=1; i<pos; i++) {
		p = p->pNext;
	}
	PNode pnew = (PNode)(malloc(sizeof(struct Node)));
	pnew->data = val;
	pnew->pNext = p->pNext;//在pnew之前的node指向的节点交给pnew来指向
	p->pNext = pnew;//在pnew之前的node指向pnew
	return true;
}

bool del(PNode pHead, int pos) {
	if(pos < 1 || pos > getLength(pHead))
		return false;
	PNode p = pHead;
	for(int i=1; i<pos; i++) {
		if(DEBUG_2) cout << i << endl;
		p = p->pNext;
	}
	if(pos == getLength(pHead)) {
		free(p->pNext);
		p->pNext = NULL;
	} else {
		PNode temp = p->pNext->pNext;
		free(p->pNext);
		p->pNext = temp;
	}
	return true;
}

PNode locate(PNode pHead, int value, int& point) {
	PNode p = pHead->pNext;
	int i = 1;
	while(p != NULL && p->data != value) {
		p = p->pNext;
		i++;
	}
	point = i;
	return p;
}

PNode get(PNode pHead, int index) {
	PNode p = pHead;
	for(int i=1; i<=index; i++) {
		p = p->pNext;
	}
	return p;
}

int main() {
	PNode sNode;
	sNode = createList();
	traverse(sNode);
	cout << "isEmpty(sNode) = " << isEmpty(sNode) << endl;
	cout << "getLength(sNode) = " << getLength(sNode) << endl;
	insert(sNode, 1, 111);
	insert(sNode, 2, 222);
	insert(sNode, 3, 333);
	insert(sNode, 8, 888);
	traverse(sNode);
	//del(sNode, 13);
	//del(sNode, 1);
	del(sNode, 5);
	traverse(sNode);

	int point;
	locate(sNode, 888, point);
	cout << "point = " << point << endl;
	cout << "get(sNode, 7) = " << (get(sNode, 7))->data << endl;
	return 0;
}
