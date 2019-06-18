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
    //借助栈，先序遍历，根 左 右，根在第一次访问时，获取数据
    stack<Node*> s;
    while(root!= NULL || !s.empty()) {
        //根打印的时机是 NO.1
        if(root == NULL) cout << "PreOrder debug 1: " << "null" << endl;
        while(root!= NULL) {
            cout << "PreOrder: " << root->value << endl;
            s.push(root);
            root = root->left;
        }
        if(!s.empty()) {
            root = s.top();
            s.pop();
            cout << "PreOrder debug 2: " << root->value << endl;
            root = root->right;
        }
    }
}


void InOrder(Node* root) {
}

void PosOrder(Node* root) {
}

/*
      1
   2     3
 4   5
8 9 6 7
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
