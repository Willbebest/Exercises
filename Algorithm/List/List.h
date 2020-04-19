#ifndef LIST_H
#define LIST_H

struct Node;
typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Postion;
typedef int ElementType;


List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Postion P, List L);
Postion Find(ElementType x, List L);
void Delete(ElementType x, List L);
Postion FindPrevious(ElementType x, List L);
void Insert(ElementType x, List L, Postion P);
void DeleteList(List L);
Postion Header(List L);
Postion First(List L);
Postion Advance(Postion P);
ElementType Retrieve(Postion P);

#endif
