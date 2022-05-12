#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <ctime>
#include <string>
#include <map>
#include<iomanip>
using namespace std;

class MinHeap
{
    vector<pair<long long,int>> heap;
    public:
        void heapify(long long i)
        {
            long long l = 2*i + 1;
            long long r = 2*i + 2;
            long long m = -1;
            if(l<heap.size() && heap[l].first<heap[i].first) 
                m = l; 
            else
                m = i;
            if(r<heap.size() && heap[r].first<heap[m].first)
                m = r;
            if(m!=i)
            {
                swap(heap[i], heap[m]);
                heapify(m);
            }
        }

        long long parent(long long i)
        {
            if(i%2==0) 
                return (i/2)-1;
            return (i/2);
        }
        void balance()
        {
            long long index = heap.size()-1;
            long long pindex = parent(index);        
            while(pindex >= 0 && heap[pindex].first > heap[index].first)
            {
                swap(heap[pindex], heap[index]);
                index = pindex;
                pindex = parent(index);
            }
        }

        void push(pair<long long,int> item)
        {
            heap.push_back(item);
            balance();
        }
        pair<long long, int> pop()
        {
            long long minimum = heap[0].first;
            int chunkId = heap[0].second;
            swap(heap[0], heap[heap.size()-1]);
            heap.pop_back();
            heapify(0);
            return {minimum,chunkId};
        }
};

long long getFileSize(string inputfile)
{
    ifstream file(inputfile);
    string data = "";
    long long count = 0;
    while(getline(file, data,',')) 
        count++;
    return count;
}

void merge(long long a[], long long l, long long mid, long long r)
{
    long long s1 = mid-l+1;
    long long s2 = r-mid;

    long long X[s1];
    long long Y[s2];
    for(long long i=0;i<s1;i++)
        X[i] = a[i+l];
    for(long long int i=0;i<s2;i++)
        Y[i] = a[i+mid+1];

    long long i=0,j=0,k=l;
    while(i<s1&&j<s2)
    {
        if(X[i]<=Y[j])
            a[k++] = X[i++];
        else
            a[k++] = Y[j++];
    }
    while(i<s1)
        a[k++] = X[i++];
    while(j<s2)
        a[k++] = Y[j++];
}

void mergeSort(long long a[], long long l, long long r)
{
    if(l<r)
    {
        long long mid = l + (r-l)/2;
        mergeSort(a,l,mid);
        mergeSort(a,mid+1,r);
        merge(a,l,mid,r);
    }
}

vector<long long> sortChunk(vector<long long> v)
{
    int n = v.size();
    long long a[n];
    for(int i=0;i<n;i++)
        a[i] = v[i];
    mergeSort(a, 0, n-1);
    v.clear();
    for(int i=0; i<n; i++) 
        v.push_back(a[i]);
    return v;
}

int process_inputfile(string inputfile, long long filesize, long long chunk_size, int chunks)
{
    ifstream file(inputfile);
    string data = "";
    int count = 0;
    int nfiles = 0;
    vector<long long> v;
   
    while(getline(file, data,','))
    {
        long long number = stoll(data, nullptr, 10); 
        v.push_back(number);
        count++;
        if(count == chunk_size)
        {
            vector<long long> temp = sortChunk(v);
            
            FILE* cf = fopen(to_string(nfiles).c_str(), "w");
            
            for(auto it : temp)
            {
                fprintf(cf, "%lld ", it);
            }
            fclose(cf);
            nfiles++;
            count = 0;
            v.clear();
        }
    }
    
    if(v.size()!=0)
    {
        vector<long long> temp = sortChunk(v);
        FILE* cf = fopen(to_string(nfiles).c_str(), "w");
        for(auto it : temp)
        {
            fprintf(cf, "%lld ", it);
        }
        fclose(cf);
        nfiles++;
        count = 0;
        v.clear();
    }
    
    return nfiles;
}

void mergeAllfiles(string outputfile, int k)
{
    MinHeap hp;
    pair<long long, int> a[k];
    int fc = 0;
    FILE* fp = fopen(outputfile.c_str(), "w");

    if(fp)
    {
        FILE* temp[k];
        for(int i=0; i<k; i++)
        {
            string fn = to_string(i);
            temp[i] = fopen(fn.c_str(), "r");
        }
        for(int i=0; i<k; i++)
        {
            if(fscanf(temp[i], "%lld ", &a[i].first) != EOF)
                a[i].second = i;
            else 
                break;
        }

        for(int i=0; i<k; i++)
        {
            hp.push(a[i]);
        }
        int ct = 1;
        while(fc!=k)
        {
            pair<long long, int> item = hp.pop();
            long long num = item.first;
            int chunkId = item.second;
            fprintf(fp, "%lld,", num);
            ct++;
            pair<long long, int> newItem;
            if(fscanf(temp[chunkId], "%lld ", &newItem.first)==1)
            {
                newItem.second = chunkId;
                hp.push(newItem);
            }
            else 
                fc += 1;
        }

        for(int i=0; i<k; i++)
        { 
            fclose(temp[i]);
            remove(to_string(i).c_str());
        }
        fclose(fp);
    }
    else
    {
        cout<<"Error in opening Output file !!!!!!!!!"<<endl;
    }
}
int main(int argc, char *argv[])
{
    if(argc!=3)
    {
    	cout<<"Invalid Arguments";
    	exit(0);
    }
    string inputfile = argv[1];
    string outputfile = argv[2];
    long long filesize = getFileSize(inputfile);
    long long chunk_size;
    chunk_size = 100000;
    int chunks = filesize/chunk_size;
    if(filesize%chunk_size!=0)
        chunks++;
    int k = process_inputfile(inputfile,filesize,chunk_size,chunks);
    mergeAllfiles(outputfile,k);
    return 0;
}




