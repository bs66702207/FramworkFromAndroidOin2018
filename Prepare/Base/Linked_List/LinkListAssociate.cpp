#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <iostream>

using namespace std;

typedef struct Node {
    int val;
	struct Node *next;
} Node, *pNode;

Node *l = NULL;
Node *l1 = NULL;
Node *l2 = NULL;

void init() {

    Node *tmp;
    Node *h, *h1, *h2;

    l = (Node*)malloc(sizeof(Node));
    l1 = (Node*)malloc(sizeof(Node));
    l2 = (Node*)malloc(sizeof(Node));

    l->next = NULL;
    l1->next = NULL;
    l2->next = NULL;
    l->val = 990;
    l1->val = 991;
    l2->val = 992;
    h = l;
    h1 = l1;
    h2 = l2;
    

    for(int i=0; i<5; i++) {
        //printf("i=%d\n", i);
        tmp = (Node*)malloc(sizeof(Node));
        tmp->next = NULL;
        tmp->val = i;
        h->next = tmp;
        h = tmp;
    }

#if 1
    h = l;
    while(h != NULL) {
        printf("%d ", h->val);
        h = h->next;
    }
    printf("\n");
#endif

    for(int i=5; i<10; i++) {
        tmp = (Node*)malloc(sizeof(Node));
        tmp->next = NULL;
        tmp->val = i;
        h1->next = tmp;
        h1 = tmp;
    }

#if 1
    h1 = l1;
    while(h1 != NULL) {
        printf("%d ", h1->val);
        tmp = h1;
        h1 = h1->next;
    }
    printf("\n");
    tmp->next = l;
#endif

    for(int i=10; i<16; i++) {
        tmp = (Node*)malloc(sizeof(Node));
        tmp->next = NULL;
        tmp->val = i;
        h2->next = tmp;
        h2 = tmp;
    }
    

#if 1
    h2 = l2;
    while(h2 != NULL) {
        printf("%d ", h2->val);
        tmp = h2;
        h2 = h2->next;
    }
    printf("\n");
    tmp->next = l;
#endif

    h1 = l1;
    while(h1 != NULL) {
        printf("%d ", h1->val);
        h1 = h1->next;
    }
    printf("\n");
    h2 = l2;
    while(h2 != NULL) {
        printf("%d ", h2->val);
        h2 = h2->next;
    }
    printf("\n");

}

bool isAssociateByStack() {
    stack<Node*> s1;
    stack<Node*> s2;
    Node *h1, *h2;
    h1 = l1;
    h2 = l2;

    Node* thisNode;

    while(h1 != NULL) {
    //    cout << h1->val << endl;
        s1.push(h1);
        h1 = h1->next;
    }
    while(h2 != NULL) {
    //    cout << h2->val << endl;
        s2.push(h2);
        h2 = h2->next;
    }

    while(!s1.empty() && !s2.empty()) {
        thisNode = s1.top();
        s1.pop();
        s2.pop();
        if(s1.top() != s2.top()) {
            printf("%p, %p\n", l, thisNode);
            break;
        }
    }
}

void isAssociateByDiffLen() {
    Node *p1, *p2;
    p1 = l1;
    p2 = l2;
    int len1 = 0;
    int len2 = 0;
    
    while(p1->next!=NULL) {
        p1 = p1->next;
        len1++;
    }
    while(p2->next!=NULL) {
        p2 = p2->next;
        len2++;
    }

    printf("len1 = %d, len2 = %d\n", len1, len2);
    if(p1 != p2) {
        printf("not Associate!\n");
        return;
    }
    int diff = abs(len1 - len2);
    if(len1 > len2) {
        p1 = l1;
        p2 = l2;
    } else {
        p1 = l2;
        p2 = l1;
    }
    for(int i=0; i<diff; i++)
    {
        p1 = p1->next;
    }
    while(p1 != p2)
    {
        p1 = p1->next;
        p2 = p2->next;
    }
    printf("%p, %p, %p\n", l, p1, p2);
}

int main()
{
    init();
    isAssociateByStack();
    isAssociateByDiffLen();

    return 0;
}
