#include<iostream>
#include<vector>
#include<sstream> 
using namespace std;
#define MAX 100019
template <class K, class V>
class Node
{
    public:
        K key;
        V value;
        Node<K,V> *next;
        Node(K k,V v)
        {
            key = k;
            value = v;
            next = NULL;
        }
};
template <class K, class V>
class unorderedMap
{
    public:
        Node<K,V> *hash[MAX];
        unorderedMap()
        {
            for(int i=0;i<=MAX;i++)
            {
                hash[i] = NULL;
            }
        }
        int Hash(K k)
        {
            ostringstream os;
            os << k;
            string s =os.str();
            int h=0;
            for(int i=0;i<s.size();i++)
            {
                h = (h*256 + s[i])%MAX;
            }
            return h;
        }
        void insert(K k,V v)
        {
            int x = Hash(k);
            //cout<<x<<" ";
            if(hash[x]==NULL)
            {
                Node<K,V> *temp = new Node<K,V>(k,v);
                hash[x] = temp;
            }
            else
            {
                Node<K,V> *temp = hash[x];
                while(temp->next!=NULL)
                {
                    if(temp->key==k)
                    {
                        temp->value = v;
                        return;
                    }
                    temp=temp->next;
                }
                if(temp->key==k)
                {
                    temp->value = v;
                    return;
                }
                Node<K,V> *newNode = new Node<K,V>(k,v);
                temp->next = newNode;
            }
        }
        void erase(K k)
        {
            int x = Hash(k);
            if(hash[x]!=NULL)
            {
                Node<K,V> *temp = hash[x];
                if(temp->key==k)
                {
                    hash[x] = hash[x]->next;
                    delete temp;
                }
                else
                {
                    while(temp->next!=NULL)
                    {
                        if(temp->next->key==k)
                        {
                            Node<K,V> *d = temp->next;
                            temp->next = d->next;
                            delete d;
                            break;
                        }
                        temp=temp->next;
                    }
                }
            }
        }
        bool find(K k)
        {
            int x = Hash(k);
            if(hash[x]==NULL)
                return false;
            Node<K,V> *temp = hash[x];
            while(temp!=NULL)
            {
                if(temp->key==k)
                    return true;
                temp=temp->next;
            }
            return false;
        }
        void display()
        {
            for(int i=0;i<MAX;i++)
            {
                if(hash[i])
                    cout<<hash[i]->key<<" "<<hash[i]->value<<endl;
            }
        }
        V &operator[] (const K k)
        {
            int x = Hash(k);
            if(hash[x]!=NULL)
            {
                Node<K,V> *temp = hash[x];
                while(temp!=NULL)
                {
                    if(temp->key==k)
                        return temp->value;
                    temp=temp->next;
                }
            }
            static V t;
            this->insert(k,t);
            return t;
        }
        
        
};
template<typename K>
vector<int> distinct_element(vector<K> v, int k)
{
    vector<int> ans;
    int d=0;
    int z;
    if(k<=v.size())
    {
        unorderedMap<K,int> mp2;
        for(int i=0;i<k;i++)
        {
            if(mp2[v[i]]==0)
                d++;
            mp2[v[i]]+=1;
        }
        ans.push_back(d);
        for(int i=k;i<v.size();i++)
        {
            if(mp2[v[i-k]]==1)
                d--;
            mp2[v[i-k]]-=1;
            if(mp2[v[i]]==0)
                d++;
            mp2[v[i]]+=1;
            ans.push_back(d);
        }
    }
    return ans;
}
int main()
{
    unorderedMap<string,string> mp;
    mp.insert("fasf","2");
    mp.insert("ds","3");
    cout<<mp["ds"]<<endl;
    /*
    mp.insert("fassfdsff","afss");
    mp.insert("fassdwsff","afss");
    mp.insert("fasdfsf","afsaa");
    mp.display();
    cout<<mp["ds"]<<endl;
    cout<<mp.find("fasdfsf")<<endl;
    mp.erase("fasf");
    mp.display();*/
    vector<char> v = {'c','d','d','d','c','d'};
    vector<int> ans = distinct_element(v,2);
    for(auto i: ans)
        cout<<i<<" ";
    cout<<endl<<mp["52"]<<endl;
    return 0;
}
