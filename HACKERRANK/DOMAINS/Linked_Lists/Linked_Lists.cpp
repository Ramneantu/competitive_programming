#include <iostream>

using namespace std;

struct Node{
  int data;
  struct Node *next;
  struct Node *prev;
};

/*
  Print elements of a linked list on console
  head pointer input could be NULL as well for empty list.
*/
void Print(Node *head)
{
    Node *list = head;
    while(list != NULL){
        cout << list->data << endl;
        list = list->next;
    }
}

/*
  Insert Node at the end of a linked list
  head pointer input could be NULL as well for empty list.
*/
Node* Insert_at_tail(Node *head,int data)
{
    Node *list = head;
    Node *node = new Node;
    node->next = NULL;
    node->data = data;
    if(list){
        while(list->next) list = list->next;
        list->next = node;
    }
    else{
        head = node;
    }
   return head;
}

/*
  Insert Node at the begining of a linked list
  Initially head pointer argument could be NULL for empty list
return back the pointer to the head of the linked list in the below method.
*/
Node* Insert_at_head(Node *head,int data)
{
    Node *node = new Node;
    node->next = NULL;
    node->data = data;
    if(head)
        node->next = head;
    head = node;
    return head;
}

/*
  Insert Node at a given position in a linked list
  head can be NULL
  First element in the linked list is at position 0
*/
Node* InsertNth(Node *head, int data, int position)
{
    Node *node = new Node;
    node->next = NULL;
    node->data = data;

    Node *list = head;
    if(!list)
        head = node;
    else{
        if(position == 0){
            node->next = head;
            head = node;
        }
        else{
            while(list->next && position > 1){
                list = list->next;
                position--;
            }
            node->next = list->next;
            list->next = node;
        }
    }
    return head;
}


/*
  Delete Node at a given position in a linked list.
*/
Node* Delete(Node *head, int position)
{
    Node *list;
    if(!head)
        return head;
    if(position == 0){
        list = head->next;
        delete head;
        head = list;
    }
    else{
        list = head;
        while(list->next && position > 1){
            list = list->next;
            position--;
        }
        Node *tmp = list->next;
        list->next = tmp->next;
        delete tmp;
    }
    return head;
}

/*
  Print elements of a linked list in reverse order as standard output
  head pointer could be NULL as well for empty list.
*/
void ReversePrint(Node *head)
{
    if(!head)
        return;
    ReversePrint(head->next);
    cout << head->data << endl;
}

/*
  Reverse a linked list and return pointer to the head
  The input list will have at least one element.
*/
Node* Reverse(Node *head)
{
    if(!head->next)
        return head;
    Node *node = Reverse(head->next);
    head->next->next = head;
    head->next = NULL;
    return node;
}


/*
  Compare two linked lists A and B
  Return 1 if they are identical and 0 if they are not.
*/
int CompareLists(Node *headA, Node* headB)
{
    if(!headA && !headB)
        return 1;
    if((headA && !headB) || (!headA && headB))
        return 0;
    return CompareLists(headA->next, headB->next) && headA->data == headB->data;
}

/*
  Merge two sorted lists A and B as one linked list.
*/
Node* MergeLists(Node *headA, Node* headB)
{
    if(!headA)
        return headB;
    if(!headB)
        return headA;
    if(!headA && !headB)
        return NULL;
    if(headA->data > headB->data){
        headB->next = MergeLists(headA, headB->next);
        return headB;
    }
    else{
        headA->next = MergeLists(headA->next, headB);
        return headA;
    }
}

/*
  Get Nth element from the end in a linked list of integers
  Number of elements in the list will always be greater than N.
*/
int GetNode(Node *head,int positionFromTail)
{
    int n = 0;
    Node *list = head;
    while(list){
        n++;
        list = list->next;
    }
    list = head;
    while(list && --n != positionFromTail){
        list = list->next;
    }
    return list->data;
}


/*
  Remove all duplicate elements from a sorted linked list.
*/
Node* RemoveDuplicates(Node *head)
{
    if(!head)
        return NULL;
    if(!head->next)
        return head;
    Node *list = RemoveDuplicates(head->next);
    if(head->data == list->data){
        head->next = list->next;
        delete list;
    }
    return head;
}

/*
Detect a cycle in a linked list. Note that the head pointer may be 'NULL' if the list is empty.
*/
bool has_cycle(Node* head) {
    if(!head)
        return 0;
    Node *turtle = head;
    Node *rabbit;
    if(head->next && head->next->next)
        rabbit = head->next->next;
    else
        return 0;
    while(turtle->next && rabbit->next->next){
        if(rabbit == turtle)
            return 1;
        turtle = turtle->next;
        rabbit = rabbit->next->next;
    }
    return 0;
}


/*
   Find merge point of two linked lists.
*/
int FindMergeNode(Node *headA, Node *headB)
{
    // sync lists
    Node *listA = headA;
    Node *listB = headB;
    int ctA, ctB;
    ctA = 0;
    while(listA){
        ctA++;
        listA = listA->next;
    }
    ctB = 0;
    while(listB){
        ctB++;
        listB = listB->next;
    }
    if(ctA>ctB){
        listA = headA;
        listB = headB;
        while(ctA-->ctB){
            listA = listA->next;
        }
    }
    else{
        listA = headA;
        listB = headB;
        while(ctB-->ctA){
            listB = listB->next;
        }
    }
    while(listA != listB){
        listA = listA->next;
        listB = listB->next;
    }
    return listA->data;
}


/*
    Insert Node in a doubly sorted linked list
    After each insertion, the list should be sorted.
*/
Node* SortedInsert(Node *head,int data)
{
    Node *node = new Node;
    node->data = data;
    node->prev = node->next = NULL;
    if(!head)
        return node;

    Node *list = head;
    while(list->next && list->data < data)
        list = list->next;
    if(list->data < data){
        node->prev = list;
        node->next = list->next;
        if(list->next)
            list->next->prev = node;
        list->next = node;
    }
    else{
       if(!list->prev){
           node->next = head;
           head->prev = node;
           head = node;
       }
        else{
            node->prev = list->prev;
            node->next = list;
            node->prev->next = node;
            list->prev = node;
        }
    }
    return head;
}


/*
   Reverse a doubly linked list, input list may also be empty.
*/
Node* Reverse_Double_Linked_List(Node* head)
{
    if(!head)
        return NULL;
    if(!head->next){
        head->prev = NULL;
        return head;
    }
    Node *node = Reverse(head->next);
    head->next->next = head;
    head->prev = head->next;
    head->next = NULL;
    return node;
}


int main(){


  return 0;
}
