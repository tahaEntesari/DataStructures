/* Author: Prakhar Jain */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define RED		1
#define BLACK	2

struct node {
    int key;
    int height;
    int maxheightinfront;
    struct node *left, *right, *p;
    int color;
};

typedef struct node *NODEPTR;
struct node NIL;
NODEPTR NILPTR = &NIL;

void inorder(NODEPTR x) {
    if (x != NILPTR) {
        inorder(x->left);
        printf("%d ", x->key);
        inorder(x->right);
    }
}

NODEPTR search(NODEPTR root, int k,int * answer) {
    if (root == NILPTR|| root->key==k) {
        *answer = (*answer) > root->maxheightinfront ? *answer : root->maxheightinfront;
        return root;
    }
    if (k < root->key) {
        return search(root->left, k, answer);
    }
    else {
        *answer=(*answer)>root->maxheightinfront?*answer:root->maxheightinfront;
        return search(root->right, k,answer);
    }
}

void leftrotate(NODEPTR *treeroot, NODEPTR x) {
    NODEPTR y = x->right;
    x->right = y->left;
    if (y->left != NILPTR)
        y->left->p = x;
    y->p = x->p;
    if (x->p == NILPTR)
        *treeroot = y;
    else if (x->p->left == x)
        x->p->left = y;
    else
        x->p->right = y;
    y->left = x;
    x->p = y;

}

void rightrotate(NODEPTR *treeroot, NODEPTR y) {
    NODEPTR x = y->left;
    y->left = x->right;
    if (x->right != NILPTR)
        x->right->p = y;
    x->p = y->p;
    if (y->p == NILPTR)
        *treeroot = x;
    else if (y->p->left == y)
        y->p->left = x;
    else
        y->p->right = x;
    x->right = y;
    y->p = x;

}

void rbinsertfixup(NODEPTR *treeroot, NODEPTR z) {
    while (z->p->color == RED) {
        if (z->p == z->p->p->left) {
            NODEPTR y = z->p->p->right;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else {
                if (z == z->p->right) {
                    z = z->p;
                    leftrotate(treeroot,z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                rightrotate(treeroot,z->p->p);
            }
        }
        else {
            NODEPTR y = z->p->p->left;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else {
                if (z == z->p->left) {
                    z = z->p;
                    rightrotate(treeroot,z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                leftrotate(treeroot,z->p->p);
            }
        }
    }
    (*treeroot)->color = BLACK;
}

void rbinsert(NODEPTR *treeroot, int z, int height) {
    NODEPTR Z = (NODEPTR) malloc(sizeof(struct node));
    Z->key = z;
    Z->height=height;
    Z->maxheightinfront=0;
    NODEPTR y = NILPTR;
    NODEPTR x = *treeroot;
    while (x != NILPTR) {
        y = x;
        if (Z->key < x->key) {
            x->maxheightinfront=x->maxheightinfront>height?x->maxheightinfront:height;
            x = x->left;

        }
        else {
            Z->maxheightinfront=Z->maxheightinfront>x->height?Z->maxheightinfront:x->height;
            Z->maxheightinfront=Z->maxheightinfront>x->maxheightinfront?Z->maxheightinfront:x->maxheightinfront;
            x = x->right;

        }
    }
    Z->p = y;
    if (y == NILPTR)
        *treeroot = Z;
    else if (Z->key < y->key)
        y->left = Z;
    else
        y->right = Z;
    Z->left = NILPTR;
    Z->right = NILPTR;
    Z->color = RED;
    rbinsertfixup(treeroot,Z);
}


int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    NIL.left = NIL.right = NIL.p = NILPTR;
    NIL.color = BLACK;
    NODEPTR tree = NILPTR;
    int numberofq, location, height;
    char c;
    cin >> numberofq;
    NODEPTR temp;
    int *answer=new int;
    for (int i = 0; i < numberofq; ++i) {
        cin >> c;
        if (c == '+') {
            cin >> location >> height;
            rbinsert(&tree, location, height);
        } else if (c == '?') {
            *answer=0;
            cin >> location;
            temp = search(tree, location,answer);
            if (temp == NILPTR)
                cout << "I'M SORRY TOQROL :(\n";
            else {
                if (*answer > temp->height) cout << "NO\n";
                else cout << "YES\n";
            }
        }
    }
    cout << endl;

}
