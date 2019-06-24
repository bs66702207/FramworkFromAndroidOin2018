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

/*
      1
   2     3
 4   5
8 9 6 7
*/

/**
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

/**
后序是左、右、中，计数栈就是0和1的标记，为了出栈判断用的
1) 1 2 4 8 入sNode，0 0 0 0 入sInt
2) 8->left == null，8->right == null, sInt{0 0 0 1}，所以8出栈，此时sNode{1 2 4} sInt{0 0 0}
3)继续遍历右节点，栈顶4->right == 9，9入栈，sNode{1 2 4 9}，sInt{0 0 1 0}，因为9没有左孩子，也没有右孩子，sInt{0 0 1 1}，所以9出栈，此时sNode{1 2 4}，sInt{0 0 1}，然后4出栈，此时sNode{1 2} sInt{0 0}
4) 继续遍历右节点，栈顶2->right == 5，5入栈，sNode{1 2 5}，sInt{0 1 0}，5->left == 6，所以sNode{1 2 5 6}，sInt{0 1 0 0}，由于6没有左右孩子，sNode{1 2 5 6}，sInt{0 1 0 1}，6出栈，sNode{1 2 5}，sInt{0 1 0}
5) 继续遍历右节点，5->right == 7，sNode{1 2 5 7}，sInt{0 1 1 0}，7没有左右孩子，所以7出栈，5出栈，2出栈，此时sNode{1}，sInt{0}
6) 继续遍历右节点，sNode{1}，sInt{1}，1->right == 3，sNode{1 3}，sInt{1 0}，由于3没有左右孩子，3出栈，最后1出栈
*/

void PosOrder(Node* root) {
    //节点栈
    stack<Node*> sNode;
    //计数栈
    stack<int> sInt;
    //标志位
    int count = 1;
    //开始一撇
    while(root != NULL || !sNode.empty()) {
        while(root != NULL) {
            //1. root第一次被访问，同步计数栈为0;
            sNode.push(root);
            sInt.push(0);
            root = root->left;
        }
        //栈元素不为null，并且计数栈栈顶元素为1，此时是第三次被访问到，
        while(!sNode.empty() && sInt.top() == count) {
            //计数栈元素移除
            sInt.pop();
            //获取遍历元素
            cout << "PosOrder: " << sNode.top()->value << endl;
            sNode.pop();
        }
        //准备遍历右节点
        if(!sNode.empty()) {
            //2. root被pop时，是第二次被访问到，同步计数栈为1
            sInt.pop();//移除元素0
            sInt.push(1);
            //查看栈顶元素(但不移除)回到节点
            root = sNode.top();
            //准备一捺
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
