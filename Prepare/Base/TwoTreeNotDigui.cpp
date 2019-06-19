#include <iostream>
#include <stack>

using namespace std;

struct Node {
	int value;
	struct Node* left;
	struct Node* right;
	Node(int data) : value(data), left(nullptr), right(nullptr) {};
};

/**
按照人之路径，将节点压栈，此为一撇，直至节点是null，于是我们将节点出栈，找到“人”的连接点，完成一捺。
当然如果“捺”上面逻辑复杂，那么还是要走人之路径的。
什么时候结束操作？当最右节点完成出栈操作，栈中没有数据，就是程序遍历完毕。

*/

void PreOrder_debugversion(Node* root) {
    //借助栈，先序遍历，根 左 右，根在第一次访问时，获取数据
    stack<Node*> s;
    int tmp = -1;
    while(root!= NULL || !s.empty()) {
        //根打印的时机是 NO.1
        if(root == NULL) cout << "PreOrder "<< tmp << "->right: " << "null" << endl;
            else if(tmp != -1) cout << "PreOrder "<< tmp << "->right: " << root->value << endl;
        while(root!= NULL) {
            cout << "PreOrder push: " << root->value << " - result." << endl;
            s.push(root);
            tmp = root->value;
            root = root->left;
            if(root == NULL) cout << "PreOrder "<< tmp << "->left: " << "null" << endl;
        }
        if(!s.empty()) {
            root = s.top();
            s.pop();
            cout << "PreOrder pop: " << root->value << endl;
            tmp = root->value;
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

/**
先序，中-左-右，通过log观察规律，是按照某种方式不停的重复，直到全部遍历完毕
1. 顺序将节点一个个顺序按照“指向左孩子”方式入栈
2. 当一个节点的左孩子为null时，需要弹一次栈
3. 判断右孩子，如果为null时，继续弹栈; 如果右孩子不为null，则入栈，回到1的方式继续入栈
PreOrder push: 1 - result.
PreOrder push: 2 - result.
PreOrder push: 4 - result.
PreOrder push: 8 - result.
PreOrder 8->left: null
PreOrder pop: 8
PreOrder 8->right: null
PreOrder pop: 4
PreOrder 4->right: 9
PreOrder push: 9 - result.
PreOrder 9->left: null
PreOrder pop: 9
PreOrder 9->right: null
PreOrder pop: 2
PreOrder 2->right: 5
PreOrder push: 5 - result.
PreOrder push: 6 - result.
PreOrder 6->left: null
PreOrder pop: 6
PreOrder 6->right: null
PreOrder pop: 5
PreOrder 5->right: 7
PreOrder push: 7 - result.
PreOrder 7->left: null
PreOrder pop: 7
PreOrder 7->right: null
PreOrder pop: 1
PreOrder 1->right: 3
PreOrder push: 3 - result.
PreOrder 3->left: null
PreOrder pop: 3

*/

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

/*
      1
   2     3
 4   5
8 9 6 7
*/

/**
InOrder: 8
InOrder: 4
InOrder: 9
InOrder: 2
InOrder: 6
InOrder: 5
InOrder: 7
InOrder: 1
InOrder: 3
*/

/**
有了先序的经验，这次就不加入debug log了，中序是左、中、右，
还是先压栈
1 2 4 8
到了8之后，8->left == null，所以要弹出来，由于8->right == null，所以要继续弹，
弹出4，4->right有值，所以先入栈9，但是9也没有左孩子了，所以需要弹出来9，9也没有右孩子，所以还需要弹
弹出2，2有的右孩子是5，入栈5，入栈6，弹出6，弹出5，然后是入栈7再弹出7，
弹出1，入栈3，弹出3，结束。
*/

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
	PreOrder_debugversion(n1);
	cout << "--------------------" << endl << endl;
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
