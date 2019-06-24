#include <iostream>

using namespace std;

struct Node {
	int value;
	struct Node* left;
	struct Node* right;
	Node(int data) : value(data), left(nullptr), right(nullptr) {};
};

void PreOrder(Node* head) {
	if(head == nullptr) return;
	cout << head->value << " ";
	PreOrder(head->left);
	PreOrder(head->right);
}


void InOrder(Node* head) {
	if(head == nullptr) return;
	InOrder(head->left);
	cout << head->value << " ";
	InOrder(head->right);
}

void PosOrder(Node* head) {
	if(head == nullptr) return;
	PosOrder(head->left);
	PosOrder(head->right);
	cout << head->value << " ";
}

/*
   1
 2   3
4 5
*/

int main() {
	Node* n1 = new Node(1);
	Node* n2 = new Node(2);
	Node* n3 = new Node(3);
	Node* n4 = new Node(4);
	Node* n5 = new Node(5);
	n1->left = n2;
	n1->right = n3;
	n2->left = n4;
	n2->right = n5;
	PreOrder(n1);
	cout << endl;
	InOrder(n1);
	cout << endl;
	PosOrder(n1);
	cout << endl;
	delete n1;
	delete n2;
	delete n3;
	delete n4;
	delete n5;
    return 0;
}
