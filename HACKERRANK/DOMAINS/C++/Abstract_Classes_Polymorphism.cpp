#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{

   protected:
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

class LRUCache : public Cache {
    public:
        LRUCache(int l) : Cache() {
            cp = l;
            head = nullptr;
            tail = nullptr;
        }

        void set(int key, int value)
        {
            if(cp <= 0)
                return;
            if(mp.size() == 0){
                Node *node = new Node(key, value);
                insert_into_head(node);
                mp.insert(make_pair(key, node));
            }
            else if(mp.find(key) != mp.end()){
                auto node = mp[key];
                node->value = value;
                insert_into_head(node);
            }
            else if(mp.size() < cp){
                Node *node = new Node(key, value);
                insert_into_head(node);
                mp.insert(make_pair(key, node));
            }
            else if(mp.size() == cp){
                auto it = tail;
                mp.erase(it->key);
                delete_node(it);
                delete it;
                Node *node = new Node(key, value);
                insert_into_head(node);
                mp.insert(make_pair(key, node));
            }
        }

        int get(int key)
        {
            if(mp.find(key) != mp.end()){
                insert_into_head(mp[key]);
                return mp[key]->value;
            }
            return -1;
        }

    private:
        void insert_into_head(Node *node){
            if(!node) return;

            //  remove node from double linked list.
            delete_node(node);

            // insert node into front.
            node->next = head;
            node->prev = nullptr;
            if(head)
                head->prev = node;
            else
                tail = node;
            head = node;
        }

        void delete_node(Node *node){
            if(!node) return;

            Node *p = node->prev;
            Node *n = node->next;

            if(p)
                p->next = n;
            else
                head = n;
            if(n)
                n->prev = p;
            else
                tail = p;
            node->prev = node->next = nullptr;
        }
};

int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      }
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
