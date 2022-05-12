#include <iostream>
#include <string> 
#include <stdlib.h>
#include <stdio.h>
using namespace std;
int f=1;
template <typename T>
class Node
{
    public:
        T data;
        int height;
        int count;
        Node<T> *left;
        Node<T> *right;
        Node<T>()
        {
            data = 0;
            left = NULL;
            right = NULL;
            height = 0;
            count = 0;
        }
        Node<T>(T key)
        {
            data = key;
            left = NULL;
            right = NULL;
            height = 1;
            count = 1;
        }
};
template <typename T>
class AVLTree
{
    public:
        Node<T> *root;
        AVLTree()
        {
            root=NULL;
        }
        int height(Node<T> *temp)
        {
            if(temp==NULL)
                return 0;
            return temp->height;
        }
        int balanceFactor(Node<T> *temp) 
        {
            if (temp == NULL)
                return -1;
            return height(temp->left) - height(temp->right);
        } 
        Node<T>* lRotate(Node<T> *temp)
        {
            Node<T> *t = temp->right;
            Node<T> *t2 = t->left;
            
            t->left = temp;
            temp->right = t2;
            temp->height =  1 + max(height(temp->left), height(temp->right));
            t->height =  1 + max(height(t->left), height(t->right));
            return t;
        }
        Node<T>* rRotate(Node<T> *temp)
        {
            Node<T> *t = temp->left;
            Node<T> *t2 = t->right;
            
            t->right = temp;
            temp->left = t2;
            temp->height =  1 + max(height(temp->left), height(temp->right));
            t->height =  1 + max(height(t->left), height(t->right));

            return t;
        }
        Node<T>* insertion(Node<T> *root, T key)
        {
            if(root==NULL)
            {
                Node<T> *temp = new Node<T>(key);
                root = temp;
                return root;
            }
            else if(root->data >key)
                root->left = insertion(root->left,key);
            else if(root->data <key)
                root->right = insertion(root->right,key);
            else
            {
                root->count = root->count + 1;
                return root;
            }
            root->height =  1 + max(height(root->left), height(root->right));
            int bf = balanceFactor(root);
            if(bf>1 && key<root->left->data)
                return rRotate(root);
            if(bf<-1 && key>root->right->data)
                return lRotate(root);
            if(bf>1 && key>root->left->data)
            {
                root->left = lRotate(root->left);
                return rRotate(root);
            }
            if(bf<-1 && key<root->right->data)
            {
                root->right = rRotate(root->right);
                return lRotate(root);
            }

            return root;
        }
        Node<T>* minValueNode(Node<T> *temp)
        {
            Node<T> *t = temp;
            while(t->left!=NULL)
                t = t->left;
            return t;

        }
        Node<T> *deletion(Node<T> *root, T x)
        {
            if(root==NULL)
                return NULL;
            else if(root->data > x)
                root->left = deletion(root->left,x);
            else if(root->data < x)
                root->right = deletion(root->right,x);
            else
            {
                if(root->count > 1)
                {
                    root->count -=1;
                }
                else
                {
                    if(root->left == NULL)
                    {
                        Node<T> *temp = root->right;
                        delete root;
                        return temp;
                    } 
                    else if(root->right == NULL)
                    {
                        Node<T> *temp = root->left;
                        delete root;
                        return temp;
                    }
                    else
                    {
                        Node<T> *temp = minValueNode(root->right);
                        root->data = temp->data;
                        root->count = temp->count;
                        temp->count = 1;
                        root->right = deletion(root->right,root->data);
                    }
                }
            }
            root->height =  1 + max(height(root->left), height(root->right));
            int bf = balanceFactor(root);
            if(bf>1 && balanceFactor(root->left)>=0)
                return rRotate(root);
            if(bf<-1 && balanceFactor(root->right)<=0)
                return lRotate(root);
            if(bf>1 && balanceFactor(root->left)<0)
            {
                root->left = lRotate(root->left);
                return rRotate(root);
            }
            if(bf<-1 && balanceFactor(root->right)>0)
            {
                root->right = rRotate(root->right);
                return lRotate(root);
            }

            return root;

        }
        bool search(Node<T> *root, T x)
        {
            if(root==NULL)
                return false;
            if(root->data == x)
                return true;
            else if(root->data > x)
                return search(root->left,x);   
            else
                return search(root->right,x);
        }
        int count_occurences_of_element(Node<T> *root,T x)
        {
            if(root==NULL)
                return 0;
            if(root->data == x)
                return root->count;
            else if(root->data > x)
                return count_occurences_of_element(root->left,x);   
            else
                return count_occurences_of_element(root->right,x);
        }

        void preOrder(Node<T> *root)
        {
            if(root != NULL)
            {
                cout << root->data <<"("<<root->count<<") ";
                preOrder(root->left);
                preOrder(root->right);
            }
        }
        Node<T> *lower_bound(Node<T> *root, T x)
        {
            if(root==NULL)
                return root;
            if((root->data >=x && root->left== NULL) ||(root->data >=x && root->left->data < x))
                return root;
            else if(root->data>x)
                return lower_bound(root->left,x);
            else
                return lower_bound(root->right,x);
        }
        Node<T> *upper_bound(Node<T> *root, T x)
        {
            if(root==NULL)
                return root;
            if(root->data < x)
            {
                Node<T> *k = upper_bound(root->right, x);
                if(k==NULL)
                    return root;
                else
                    return k;
            }
            else if(root->data >x)
                return upper_bound(root->left,x);
            return 0;
        }
        Node<T> *closet(Node<T> *root, T x) 
        {

            Node<T>* x1 = lower_bound(root,x);
            Node<T>* x2 = upper_bound(root,x);
            if(x1==NULL)
                return x2;
            if(x2==NULL)
                return x1;

            if(abs(x2->data - x)>abs(x1->data -x))
                return x1;
            else
                return x2;
        }
        void kthlargest(Node<T> *root,int k,int &c)
        {
            if(root==NULL || c>=k)
                return;
            kthlargest(root->right, k, c);
            c = c + root->count;
            if(c>=k&&f==1)
            {
                cout<<root->data<<endl;
                f=0;
                return;
            }
            kthlargest(root->left, k, c);
        }
        int count_value_in_range(Node<T> *root,T l, T r)
        {
            if(root==NULL)
                return 0;
            if(root->data >=l && root->data <=r)
            {
                return root->count + count_value_in_range(root->left,l,r) + count_value_in_range(root->right,l,r);
            }
            else if(root->data<l)
                return count_value_in_range(root->right,l,r);
            else
                return count_value_in_range(root->left,l,r);
        }
};
int main()
{
    AVLTree<string> *t = new AVLTree<string>();
    t->root = t->insertion(t->root,"ab");
    t->root = t->insertion(t->root,"cd");
    t->root = t->insertion(t->root,"cd");
    t->root = t->insertion(t->root,"es");
    t->root = t->insertion(t->root,"ds");
    t->root = t->insertion(t->root,"ds");            
    t->root = t->insertion(t->root,"fs"); 
    t->preOrder(t->root);
    cout<<endl;
    cout<<t->search(t->root,"abc")<<endl;
    cout<<t->count_occurences_of_element(t->root,"ds")<<endl;
    cout<<t->count_value_in_range(t->root,"a","f")<<endl;
    int c = 0;
    t->kthlargest(t->root,7,c);
    //cout<<(t->closet(t->root,"a"))->data<<endl;
    Node<string> *lbound = t->lower_bound(t->root,"fse");
    if(lbound!=NULL)
        cout<<lbound->data<<endl;
    else
        cout<<"-1"<<endl;
    Node<string> *ubound = t->upper_bound(t->root,"dse");
    if(ubound!=NULL)
        cout<<ubound->data<<endl;
    else
        cout<<"-1"<<endl;
    
}
