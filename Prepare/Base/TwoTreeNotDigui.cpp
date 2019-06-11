#include <iostream>
#include <stack>

using namespace std;

struct Node {
	int value;
	struct Node* left;
	struct Node* right;
	Node(int data) : value(data), left(nullptr), right(nullptr) {};
};

#if 1
//left root right
//中序代码段(i)
Node* p = root; //p指向树根
stack<Node*> s; //STL中的栈
//一直遍历到左子树最下边，边遍历边保存根节点到栈中
while(p) {
    s.push(p);
    p = p->lchild;
}
//保存一路走过的根节点的理由是: 中序遍历的需要，遍历完左子树后，需要借助根节点进入右子树。代码走到这里，指针p为空，此时无非两种情况:
//情况一: 最近上一次保存的p是叶子节点
//情况二: 最近上一次保存的是叶子节点，但是它没有左孩子

//仔细想想，二叉树的左子树，最下边是不是上图两种情况？不管怎样，此时都要出栈，并访问该节点。这个节点就是中序序列的第一个节点。根据我们的思维，代码应该是这样:
p = s.top();
s.pop();
cout << p->data;

//我们的思维接着走，两图情形不同得区别对待:
//1.情况一
//访问的是一个左孩子，按中序遍历顺序，接下来应访问它的根节点。也就是另一个节点，高兴的是它已被保存在栈中。我们只需和上一步一样的代码:
p = s.top();
s.pop();
cout << p->data;
//左孩子和根都访问完了，接着就是右孩子了，对吧。接下来只需一句代码: p=p->rchild; 在右子树中，又会新一轮的代码段(i)、代码段(ii)……直到栈空且p空。

//2.情况二
//由于没有左孩子，根节点就是中序序列中第一个，然后直接是进入右子树: p=p->rchild; 在右子树中，又会新一轮的代码段(i)、代码段(ii)……直到栈空且p空。
//思维到这里，似乎很不清晰，真的要区分吗？根据图a接下来的代码段(ii)这样的:
p = s.top();
s.pop();
cout << p->data;
p = s.top();
s.pop();
cout << p->data;
p = p->rchild;


#endif

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
	//PreOrder(n1);
	//cout << endl;
	//InOrder(n1);
	//cout << endl;
	//PosOrder(n1);
	//cout << endl;
	delete n1;
	delete n2;
	delete n3;
	delete n4;
	delete n5;
    return 0;
}
