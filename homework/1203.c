#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    int data;
    int count;
    struct Node *llink;
    struct Node *rlink;
}Node,*Tree;

Node *SearchInsert(Tree *root,int x){
    if (*root == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = x;
        newNode->count = 1;
        newNode->llink = NULL;
        newNode->rlink = NULL;
        *root = newNode;
        return newNode;
    }

    Node *p=*root;//Node *p; p=*root
    Node *parent=NULL;

    while(p!=NULL){
        if(p->data==x){
            p->count++;
            return p;
        }
        parent=p;
        if(p->data>x)
            p=p->llink;
        else
            p=p->rlink;
    }

    Node* newNode=(Node*)malloc(sizeof(Node));
    newNode->count=1;
    newNode->data=x;
    newNode->llink=NULL;
    newNode->rlink=NULL;

    if(parent->data>x)
        parent->llink=newNode;
    else
        parent->rlink=newNode;
    
    return newNode;
}

