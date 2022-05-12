#include <iostream>
using namespace std;
template <typename T>
class Deque
{
    public:
        T *arr;
        int arr_size;
        int curr_size;
        int f;
        int r;
        Deque()
        {
            arr = new T[4];
            f = -1;
            r = -1;
            arr_size = 4;
            curr_size = 0;
        }
        Deque(int n, T x)
        {
            arr = new T[n];
            for(int i=0;i<n;i++)
            {
                arr[i] = x;
            }
            f = 0;
            r = n-1;
            arr_size = n;
            curr_size = n;
        }
        void push_back(T x)
        {
            if(f==(r+1)%arr_size)
            {
                T* temp = new T[2*arr_size];
                int i=f;
                int j=0;
                while(i!=r)
                {
                   temp[j] = arr[i];
                   i = (i+1)%arr_size;
                   j++; 
                }
                temp[j] = arr[r];
                f = 0;
                r = j;
                delete arr;
                arr = temp;
                arr_size = 2*arr_size;
                r = (r+1)%arr_size;
            }
            else if(f==-1)
            {
                f=0;
                r=0;
            }
            else
            {
                r = (r+1)%arr_size;
            }
            arr[r] = x;
            curr_size++;
        }
        void pop_back()
        {
            if(f==-1)
            {
                cout<<"Deque is Empty!!!";
                return;
            }
            else if(f==r)
            {
                f = -1;
                r = -1;
            }                   
            else if(r==0)
                r = arr_size-1;
            else
                r -=1;
            curr_size--;
        }
        void push_front(T x)
        {
            if(f==(r+1)%arr_size)
            {
                T* temp = new T[2*arr_size];
                int i=f;
                int j=0;
                while(i!=r)
                {
                   temp[j] = arr[i];
                   i = (i+1)%arr_size;
                   j++; 
                }
                temp[j] = arr[r];
                f = 0;
                r = j;
                delete arr;
                arr = temp;
                arr_size = 2*arr_size;
                if(f>0)
                    f-=1;
                else
                    f = arr_size-1;
            }
            else if(f==-1)
            {
                f=0;
                r=0;
            }
            else
            {
                if(f>0)
                    f-=1;
                else
                    f = arr_size-1;
            }
            arr[f] = x;
            curr_size++;
        }
        void pop_front()
        {
            if(f==-1)
            {
                cout<<"Deque is Empty!!!";
                return;
            }
            else if(f==r)
            {
                f = -1;
                r = -1;
            }
            else if(f==curr_size-1)
                f = 0;
            else
                f +=1;
            curr_size--;
        }
        T front()
        {
            if(f==-1)
            {
                static T t;
                cout<<"Deque is Empty!!!";
                return t;
            }
            return arr[f];
        }
        T back()
        {
            if(f==-1)
            {
                static T t;
                cout<<"Deque is Empty!!!";
                return t;
            }
            return arr[r];
        }
        bool empty()
        {
            if(f==-1)
                return true;
            return false;
        }
        int size()
        {
            return curr_size;
        }
        void resize(int x, T d)
        {
            T* temp = new T[x];
            if(f==-1)
            {
                for(int i=0;i<x;i++)
                    temp[i] = d;
            }
            else
            {
                int i=f;
                int j=0;
                while(i!=r && j<x)
                {
                   temp[j] = arr[i];
                   i = (i+1)%arr_size;
                   j++; 
                }
                if(curr_size<=x)
                    temp[j++] = arr[r];
                while(j<x)
                    temp[j++] = d;
            }
            f = 0;
            r = x-1;
            delete arr;
            arr = temp;
            curr_size = x;
        }
        void clear()
        {
            f =-1;
            r =-1;
        }
        T &operator[](int n)
        {
            static T t;
            if(n>=size())
                return t;
            else if(f<=r)
                return arr[f+n];
            else
                return arr[(f+n)%arr_size];
            return t;
        }
        void display()
        {
            if(f==-1)
            {
                cout<<"Queue is Empty!!!!"<<endl;
            }
            else
            {
                int i=f;
                while(i!=r)
                {
                    cout<<arr[i]<<" ";
                    i = (i+1)%arr_size;
                }
                cout<<arr[r]<<endl;
            }
        }
};
int main()
{
    Deque<double> d(8,5);
    cout<<d.f<<" "<<d.r<<endl;
    d.push_front(5);
    d.push_front(8.52);
    d.push_front(980.2);
    d.push_front(5);
    d.push_front(8.52);
    d.push_front(980.2);
    d.push_front(6);
    d.display();
    cout<<d.f<<" "<<d.r<<endl;
    d.push_front(50.2);
    d.push_back(50.265);
    d.push_back(50.2545);
    cout<<d.size()<<endl;
    for(int i=0;i<d.size();i++)
        cout<<d[i]<<" ";
    cout<<endl;
    cout<<d[1]<<endl;
    d.resize(12,6);
    d.display();
    d[1] +=5;
    
    d.display();
    d.resize(3,5);

    cout<<d.front()<<endl;
    cout<<d.back()<<endl;
    cout<<d[0]<<endl;
  
    d.clear();
    d.display();
}