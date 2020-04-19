#include "List.h"

#include <stdlib.h>
#include <malloc.h>

struct Node{
    ElementType Element;
    Postion Next;
} Node;

List MakeEmpty(List L)
{
    PtrToNode temp;
    PtrToNode p;
    p=L;
    L=NULL;
    while(p!=NULL){
        temp=p;
        p=p->Next;
        free(temp);
    }
    return L;
}

int IsEmpty(List L)
{
    return L==NULL;
}

int IsList(Postion P)
{
    return P==NULL;
}

Postion Find(ElementType x, List L)
{
    Postion p=L;
    while(L!=NULL&&p->Element!=x){
        p=p->Next;
    }
    return p;
}

void Delete(ElementType x, List L){
    PtrToNode p=L;
    PtrToNode ret=NULL;
    PtrToNode temp;
    while(p!=NULL)
    {
        ret=FindPrevious(x, p);
        if(ret->Next!=NULL){
            temp=ret->Next;
            ret->Next=temp->Next;
            free(temp);
        }
        p=ret;
    }
}

// 这个函数假设有头节点
Postion FindPrevious(ElementType x, List L)
{
    PtrToNode ptr=L;
    while(ptr->Next!=NULL){
        if(ptr->Next->Element==x)
            return ptr;
    }

    return NULL;
}

void Insert(ElementType x, Postion p){
    PtrToNode temp=(PtrToNode)malloc(sizeof(struct Node));
    temp->Element=x;
    temp->Next=p->Next;
    p->Next=temp;
}

void DeleteList(List L)
{
    PtrToNode ptr=L->Next;
    L=NULL;
    PtrToNode temp;
    while(ptr!=NULL){
        temp=ptr;
        ptr=temp->Next;
        free(temp);
    }
}

// 剩下的函数略
