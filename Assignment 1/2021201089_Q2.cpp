/*
Input format :
First Line contains value 1 or 2
1 for LRU and 2 for LFU
From second line to last second line each line will contain 
1 k - it will create an LRU/LFU of capacity k based on choice from first line
2 k - it will call get function and will print value corresponding to key k return by get function
3 k v- it will call set function and will store/update key-value pair in LRU/LFU
Last Line will contain value 4 (for termination of code)
*/
#include<iostream>
#include<unordered_map>
using namespace std;
class LRUCache
{
public:
    class Node
    {
        public:
        int key;
        int value;
        Node *next;
        Node *prev;

        Node(int k, int v)
        {
            key = k;
            value = v;
        }
    };
    Node *start = new Node(-1,-1);
    Node *end = new Node(-1,-1);
    void display()
    {
        Node *temp = start->next;
        while(temp!=end)
        {
            cout<<temp->key<<" "<<temp->value<<endl;
            temp = temp->next;
        }
    }
    void insert_node(Node *t)
    {
        t->next = start->next;
        t->prev = start;
        start->next = t;
        t->next->prev =t;
    }
    void delete_node(Node *t)
    {
        t->prev->next = t->next;
        t->next->prev = t->prev;
    }
    int capacity;
    unordered_map<int, Node*> mp;
    LRUCache(int c)
    {
        capacity = c;
        start->next = end;
        end->prev = start;
    }
    int get(int key)
    {
        if(mp.find(key)==mp.end())
            return -1;
        Node *temp = mp[key];
        int ans = temp->value;
        delete_node(temp);
        insert_node(temp);
        mp[key] = start->next;
        return ans;
    }
    void set(int key, int value)
    {
        if(capacity==0)
            return;
        if(mp.find(key)!=mp.end())
        {
            Node *temp = mp[key];
            mp.erase(key);
            delete_node(temp);
        }
        else
        {
            if(mp.size()==capacity)
            {
                mp.erase(end->prev->key);
                delete_node(end->prev);
            }
        }
        Node *t = new Node(key,value);
        insert_node(t);
        mp[key] = start->next;
    }
};
class LFUCache {
public:
    class Node
    {
        public:
        int key;
        int value;
        int freq;
        Node *next;
        Node *prev;
        Node(int k, int v, int f)
        {
            key = k;
            value = v;
            freq = f;
        }
    };
    Node *start = new Node(-1,-1,0);
    Node *end = new Node(-1,-1,0);
    unordered_map<int, Node*> mp;
    int capacity;
    void display()
    {
        Node *t = start->next;
        while(t!=end)
        {
            cout<<t->key<<" "<<t->value<<" "<<t->freq<<endl;
            t = t->next;
        }
    }
    void delete_node(Node *t)
    {
        t->prev->next = t->next;
        t->next->prev = t->prev;
    }
    void insert_node(Node *t)
    {   
        Node *temp = start->next;
        while(temp!=end->next)
        {
            if(t->freq >= temp->freq)
            {
                temp->prev->next = t;
                t->next = temp;
                t->prev = temp->prev;
                temp->prev = t;
                break;
            }
            temp = temp->next;
        }
    }
    LFUCache(int c)
    {
        capacity = c;
        start->next = end;
        end->prev = start;
        start->prev = NULL;
        end->next = NULL;
    }
    int get(int key)
    {
        if(mp.find(key)==mp.end())
            return -1;

        Node *temp = mp[key];
        delete_node(temp);
        temp->freq = temp->freq + 1;
        insert_node(temp);       
        return temp->value;
    }
    void set(int key, int value)
    {
        if(capacity==0)
            return;
        int x = 1;
        if(mp.find(key)!=mp.end())
        {
            Node *temp = mp[key];
            x = temp->freq +  1;
            mp.erase(temp->key);
            delete_node(temp);
        }
        else
        {
            if(mp.size()>=capacity)
            {
                mp.erase(end->prev->key);
                delete_node(end->prev);
            }
        }
        Node *t = new Node(key,value,x);
        insert_node(t);
        mp[key] = t;
    }
};

int main()
{
    int ch,ch2;
    int k,v;
    cin>>ch;
    if(ch==1)
    {
        LRUCache *l = NULL;
        do
        {
            cin>>ch2;
            if(ch2==1)
            {
                cin>>k;
                l = new LRUCache(k);
            }   
            if(ch2==2)
            {
                cin>>k;
                cout<<l->get(k)<<endl;
            }
            if(ch2==3)
            {
                cin>>k>>v;
                l->set(k,v);
            }
        }while(ch2!=4);
        //l->display();
    }
    if(ch==2)
    {
        LFUCache *l = NULL;
        do
        {
            cin>>ch2;
            if(ch2==1)
            {
                cin>>k;
                l = new LFUCache(k);
            }   
            if(ch2==2)
            {
                cin>>k;
                cout<<l->get(k)<<endl;
            }
            if(ch2==3)
            {
                cin>>k>>v;
                l->set(k,v);
            }
        }while(ch2!=4);
        //l->display();
    }
    return 0;
}

