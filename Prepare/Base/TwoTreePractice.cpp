#include <iostream>
#include <stack>

using namespace std;

struct Node {
	int value;
	struct Node* left;
	struct Node* right;
	Node(int data) : value(data), left(nullptr), right(nullptr) {};
};

void PreOrder(Node* root) {
    stack<Node*> s;
    while(root != NULL || !s.empty()) {
        while(root != NULL) {
            cout << "PreOrder: " << root->value << endl;
            s.push(root);
            root = root->left;
        }
        if(!s.empty()) {
            root = s.top();
            s.pop();
            root = root->right;
        }
    }
}

void InOrder(Node* root) {
    stack<Node*> s;
    while(root != NULL || !s.empty()) {
        while(root != NULL) {
            s.push(root);
            root = root->left;
        }
        if(!s.empty()) {
            root = s.top();
            cout << "InOrder: " << root->value << endl;
            s.pop();
            root = root->right;
        }
    }
}

void PosOrder(Node* root) {
    stack<Node*> sNode;
    stack<int> sInt;
    int count = 1;//flag
    while(root != NULL || !sNode.empty()) {
        while(root != NULL) {
            sNode.push(root);
            sInt.push(0);
            root = root->left;
        }

        while(!sNode.empty() && sInt.top() == count) {
            sInt.pop();
            cout << "PosOrder: " << sNode.top()->value << endl;
            sNode.pop();
        }

        if(!sNode.empty()) {
            sInt.pop();
            sInt.push(1);
            root = sNode.top();
            root = root->right;
        }
    }
}

/*
      1
   2     3
 4   5
8 9 6 7
*/
/*
PreOrder: 1
PreOrder: 2
PreOrder: 4
PreOrder: 8
PreOrder: 9
PreOrder: 5
PreOrder: 6
PreOrder: 7
PreOrder: 3

InOrder: 8
InOrder: 4
InOrder: 9
InOrder: 2
InOrder: 6
InOrder: 5
InOrder: 7
InOrder: 1
InOrder: 3

PosOrder: 8
PosOrder: 9
PosOrder: 4
PosOrder: 6
PosOrder: 7
PosOrder: 5
PosOrder: 2
PosOrder: 3
PosOrder: 1
*/
int main() {
	Node* n1 = new Node(1);
	Node* n2 = new Node(2);
	Node* n3 = new Node(3);
	Node* n4 = new Node(4);
	Node* n5 = new Node(5);
	Node* n6 = new Node(6);
	Node* n7 = new Node(7);
	Node* n8 = new Node(8);
	Node* n9 = new Node(9);
	n1->left = n2;
	n1->right = n3;
	n2->left = n4;
	n2->right = n5;
	n5->left = n6;
	n5->right = n7;
    n4->left = n8;
    n4->right = n9;

    PreOrder(n1);
	cout << "--------------------" << endl << endl;

	InOrder(n1);
	cout << "--------------------" << endl << endl;

	PosOrder(n1);
	cout << "--------------------" << endl << endl;
	delete n1;
	delete n2;
	delete n3;
	delete n4;
	delete n5;
	delete n6;
	delete n7;
	delete n8;
	delete n9;
    return 0;
}
