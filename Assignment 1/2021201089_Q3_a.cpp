#include<iostream>
using namespace std;
template <typename T>
T **readSparse()
{
    int m,n,t;
    cin>>m>>n>>t;
    T **M = new T*[t+1];
    for(int i=0;i<=t;i++)
    {
        M[i] = new T[3];
    }
    M[0][0] = m;
    M[0][1] = n;
    M[0][2] = t;    
    for(int i=1;i<=M[0][2];i++)
    {
        cin>>M[i][0]>>M[i][1]>>M[i][2];
    }
    return M;
}
template <typename T>
void printSparse(T **M)
{
    int t = M[0][2];
    cout<<"row\t column\t value\n";
    for(int i=0;i<=t;i++)
    {
        cout<<M[i][0]<<"\t\t"<<M[i][1]<<"\t\t"<<M[i][2]<<endl;
    }
}
template <typename T>
T **transposeSparse(T **A)
{
    int t = A[0][2];
    T **C = new T*[t+1];
    for(int i=0;i<=t;i++)
    {
        C[i] = new T[3];
    }
    int X[t+1];
    int I[t+1];
    int n = A[0][1];
    for(int i=0;i<=n;i++)
        X[i]=0;
    for(int i=1;i<=t;i++)
    {   
        int p = A[i][1];
        X[p] = X[p]+1;
    }
    I[0] = 1;
    for(int i=1;i<=n;i++)
    {
        I[i] = I[i-1] + X[i-1];
    }
    C[0][0] = A[0][1];
    C[0][1] = A[0][0];
    C[0][2] = A[0][2];
    for(int i=1;i<=A[0][2];i++)
    {
        int p =A[i][1];
        C[I[p]][0] = A[i][1];
        C[I[p]][1] = A[i][0];
        C[I[p]][2] = A[i][2];
        I[p]+=1;
    }
    return C;
}
template <typename T>  
T **addSparse(T **A, T **B)
{
    int t1 = A[0][2];
    int t2 = B[0][2];
    T **C = new T*[t1+t2+1];
    for(int i=0;i<=t1+t2;i++)
    {
        C[i] = new T[3];
    }
    int i,j,k;
    i=j=k=1;
    C[0][0] = A[0][0];
    C[0][1] = A[0][1];  
    while(i<=t1&&j<=t2)
    {
        if(A[i][0]<B[j][0])
        {
            C[k][0]=A[i][0];
            C[k][1]=A[i][1];
            C[k][2]=A[i][2];
            i++;
            k++;
        }
        else if(A[i][0]>B[j][0])
        {
            C[k][0]=B[j][0];
            C[k][1]=B[j][1];
            C[k][2]=B[j][2];
            j++;
            k++;
        }
        else if(A[i][1]<B[j][1])
        {
            C[k][0]=A[i][0];
            C[k][1]=A[i][1];
            C[k][2]=A[i][2];
            i++;
            k++;
        }
        else if(A[i][1]>B[j][1])
        {
            C[k][0]=B[j][0];
            C[k][1]=B[j][1];
            C[k][2]=B[j][2];
            j++;
            k++;
        }
        else
        {
            C[k][0]=B[j][0];
            C[k][1]=B[j][1];
            C[k][2]=A[i][2] + B[j][2];
            i++;
            j++;
            k++;
        }
    }
    while(i<=t1)
    {
        C[k][0]=A[i][0];
        C[k][1]=A[i][1];
        C[k][2]=A[i][2];
        i++;
        k++;
    }
    while(j<=t2)
    {
        C[k][0]=B[j][0];
        C[k][1]=B[j][1];
        C[k][2]=B[j][2];
        j++;
        k++;

    }
    C[0][2] = k-1;
    return C;
}
template <typename T>  
T **mulSparse(T **A, T **B)
{
    int m = A[0][1];
    int n = B[0][0];
    int present[m][n];
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            present[i][j] = 0;
        }
    }
    T **C = new T*[(m*n)+1];
    for(int i=0;i<=(m*n)+1;i++)
    {
        C[i] = new T[3];
    }
    int k=1;
    C[0][0] = A[0][0];
    C[0][1] = B[0][1];
    int t1 = A[0][2];
    int t2 = B[0][2];
    for(int i=1;i<=t1;i++)
    {
        for(int j=1;j<=t2;j++)
        {
            if(A[i][1]==B[j][0])
            {
                int p = A[i][0];
                int q = B[j][1];
                if(present[p][q]!=0)
                    C[present[p][q]][2] += (A[i][2] * B[j][2]);
                else
                {
                    int a=k;
                    for(a = k;a>1;a--)
                    {
                        if(C[a-1][0]>p)
                        {
                            C[a][0] = C[a-1][0];
                            C[a][1] = C[a-1][1];
                            C[a][2] = C[a-1][2];
                        }
                        else if(C[a-1][0]==p&&C[k-1][1]>q)
                        {
                            C[a][0] = C[a-1][0];
                            C[a][1] = C[a-1][1];
                            C[a][2] = C[a-1][2];
                        }
                        else
                            break;
                    }
                    C[a][0] = p;
                    C[a][1] = q;
                    C[a][2] = A[i][2] * B[j][2];
                    present[p][q] = a;
                    k++;
                }
            }
        }
    }
    C[0][2] = k-1;
    return C;
}
int main()
{
    int ch,dtype;
    cin>>ch>>dtype;
    if(ch==1)
    {
        if(dtype==1)
        {
            int **A,**B,**C;
            A = readSparse<int>();
            B = readSparse<int>();
            printSparse<int>(A);
            printSparse<int>(B);
            C = addSparse<int>(A,B);        
            printSparse<int>(C);
        }
        if(dtype==2)
        {
            float **A,**B,**C;
            A = readSparse<float>();
            B = readSparse<float>();
            printSparse<float>(A);
            printSparse<float>(B);
            C = addSparse<float>(A,B);      
            printSparse<float>(C);
        }
        if(dtype==3)
        {
            double **A,**B,**C;
            A = readSparse<double>();
            B = readSparse<double>();
            printSparse<double>(A);
            printSparse<double>(B);
            C = addSparse<double>(A,B);     
            printSparse<double>(C);

        }
    } 
    if(ch==2)
    {
        if(dtype==1)
        {
            int **A,**B,**C;
            A = readSparse<int>();
            B = readSparse<int>();
            printSparse<int>(A);
            printSparse<int>(B);
            C = mulSparse<int>(A,B);
            printSparse<int>(C);
        }
        if(dtype==2)
        {
            float **A,**B,**C;
            A = readSparse<float>();
            B = readSparse<float>();
            printSparse<float>(A);
            printSparse<float>(B);
            C = mulSparse<float>(A,B);      
            printSparse<float>(C);
        }
        if(dtype==3)
        {
            double **A,**B,**C;
            A = readSparse<double>();
            B = readSparse<double>();
            printSparse<double>(A);
            printSparse<double>(B);
            C = mulSparse<double>(A,B);     
            printSparse<double>(C);

        }
    }
    if(ch==3)
    {
        if(dtype==1)
        {
            int **A,**C;
            A = readSparse<int>();
            printSparse<int>(A);
            C = transposeSparse<int>(A);
            printSparse<int>(C);
        }
        if(dtype==2)
        {
            float **A,**C;
            A = readSparse<float>();
            printSparse<float>(A);
            C = transposeSparse<float>(A);      
            printSparse<float>(C);
        }
        if(dtype==3)
        {
            double **A,**B,**C;
            A = readSparse<double>();
            printSparse<double>(A);
            C = transposeSparse<double>(A);     
            printSparse<double>(C);
        }

    }   
    return 0;
}