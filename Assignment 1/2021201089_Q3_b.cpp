/*
Input format :

First Line will contain two integers from (1-3)
first value for selecting operations
1 - to add two sparse matrices
2 - to Multiply two sparse matrices
3 - to find transpose of a sparse matrix
second value for selecting datatype
1 - for integer datatype
2 - for float datatype
3 - for double datatype

1 or 2 Matrix(depending on operation) in triplet form (row column value)
first line of each matrix will contain 3 values (max_row_size max_col_size max_no_of_non-zero_values)
Output format :
sparse matrix1
sparse matrix2 (only if operation is additon or multipication)
ans matrix  

all the matrix will be displayed in triplet form
(row column value)

first line of each matrix is (max_row_size max_col_size max_no_of_non-zero_values)
for second line onwards (row_position col_position value_at_M[row][col])
*/
#include<iostream>
using namespace std;
template <typename T>
struct Node
{
    int row;
    int col;
    T value;
    Node *next;
};
template <typename T>
void printSparse(Node<T> *M)
{
    cout<<"row\t\tcolumn\t\tvalue\n";
    while(M)
    {
        cout<<M->row<<"\t\t"<<M->col<<"\t\t"<<M->value<<endl;
        M=M->next;
    }
}
template <typename T>
Node<T> *readSparse()
{
    int m,n,t;
    T v;
    cin>>m>>n>>t;
    Node<T> *head = new Node<T>;
    head->row = m;
    head->col = n;
    head->value = t;
    head->next = NULL;
    Node<T> *last;
    last = head;
    for(int i=1;i<=t;i++)
    {
        Node<T> *temp = new Node<T>;
        cin>>m>>n>>v;
        temp->row = m;
        temp->col = n;
        temp->value = v;
        last->next = temp;
        temp->next = NULL;
        last = temp;
    }
    return head;
}
template <typename T>
Node<T> *transposeSparse(Node<T> *A)
{
    int c=0;
    Node<T> *head = new Node<T>;
    head->row = A->col;
    head->col = A->row;
    head->value = A->value;
    head->next = NULL;
    Node<T> *last = head;
    while(c<=A->col)
    {
        Node<T> *temp = A->next;
        while(temp)
        {
            if(temp->col==c)
            {
                 Node<T> *t = new Node<T>;
                 t->row = temp->col;
                 t->col = temp->row;
                 t->value = temp->value;
                 t->next = NULL;
                 last->next = t;
                 last = t;
            }
            temp=temp->next;
        }
        c++;
    }
    return head;
}
template <typename T>
Node<T> *addSparse(Node<T> *A, Node<T> *B)
{
    Node<T> *head = new Node<T>;
    head->row = A->row;
    head->col = A->col;
    Node<T> *last = head;  
    A=A->next;
    B=B->next;
    int k=0;
    while(A&&B)
    {
        if(A->row<B->row)
        {
            Node<T> *temp = new Node<T>;
            temp->row = A->row;
            temp->col = A->col;
            temp->value = A->value;
            temp->next = NULL;
            A=A->next;
            last->next = temp;
            last = temp;
            k++;
        }
        else if(A->row>B->row)
        {
            Node<T> *temp = new Node<T>;
            temp->row = B->row;
            temp->col = B->col;
            temp->value = B->value;
            temp->next = NULL;
            B=B->next;
            last->next = temp;
            last = temp;
            k++;
        }
        else if(A->col<B->col)
        {
            Node<T> *temp = new Node<T>;
            temp->row = A->row;
            temp->col = A->col;
            temp->value = A->value;
            temp->next = NULL;
            A=A->next;
            last->next = temp;
            last = temp;
            k++;
        }
        else if(A->col>B->col)
        {
            Node<T> *temp = new Node<T>;
            temp->row = B->row;
            temp->col = B->col;
            temp->value = B->value;
            temp->next = NULL;
            B=B->next;
            last->next = temp;
            last = temp;
            k++;
        }
        else
        {
            Node<T> *temp = new Node<T>;
            temp->row = B->row;
            temp->col = B->col;
            temp->value = A->value + B->value;
            temp->next = NULL;
            A=A->next;
            B=B->next;
            last->next = temp;
            last = temp;
            k++;
        }
    }
    while(A)
    {
        Node<T> *temp = new Node<T>;
        temp->row = A->row;
        temp->col = A->col;
        temp->value = A->value;
        temp->next = NULL;
        A=A->next;
        last->next = temp;
        last = temp;
        k++;
    }
    while(B)
    {
        Node<T> *temp = new Node<T>;
        temp->row = B->row;
        temp->col = B->col;
        temp->value = B->value;
        temp->next = NULL;
        B=B->next;
        last->next = temp;
        last = temp;
        k++;
    }
    head->value = k ;
    return head;
}
template <typename T>
Node<T> *mulSparse(Node<T> *A, Node<T> *B)
{
    Node<T> *head = new Node<T>;
    head->row = A->row;
    head->col = B->col;
    head->next = NULL;
    Node<T> *last = head;
    int k=0;
    Node<T> *a = A->next;
    while(a)
    {
        Node<T> *b = B->next;
        while(b)
        {
            if(a->col == b->row)
            {
                Node<T> *trav = head;
                int f=1;
                while(trav->next)
                {
                    if(trav->row==a->row && trav->col==b->col)
                    {
                        trav->value += (a->value) * (b->value) ;
                        f=0;
                        break;
                    }
                    trav=trav->next;
                }
                if(f==1&&trav->row==a->row && trav->col==b->col)
                {
                    trav->value += (a->value) * (b->value) ;
                    f=0;
                }
                if(f)
                {
                    Node<T> *temp = new Node<T>;
                    temp->row = a->row;
                    temp->col = b->col;
                    temp->value = (a->value) * (b->value) ;
                    temp->next = NULL;
                    trav->next = temp;
                    k++;
                }
                
            }
            b=b->next;
        }
        a=a->next;
    }
    head->value = k;
    head = transposeSparse<T>(head);
    head = transposeSparse<T>(head);
    return head;
}
int main()
{
    int ch,dtype;
    cin>>ch>>dtype;
    if(ch==1)
    {
        if(dtype==1)
        {
            Node<int> *A,*B,*C;
            A = readSparse<int>();
            B = readSparse<int>();
            printSparse<int>(A);
            printSparse<int>(B);
            C = addSparse<int>(A,B);        
            printSparse<int>(C);
        }
        if(dtype==2)
        {
            Node<float> *A,*B,*C;
            A = readSparse<float>();
            B = readSparse<float>();
            printSparse<float>(A);
            printSparse<float>(B);
            C = addSparse<float>(A,B);      
            printSparse<float>(C);
        }
        if(dtype==3)
        {
            Node<double> *A,*B,*C;
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
            Node<int> *A,*B,*C;
            A = readSparse<int>();
            B = readSparse<int>();
            printSparse<int>(A);
            printSparse<int>(B);
            C = mulSparse<int>(A,B);
            printSparse<int>(C);
        }
        if(dtype==2)
        {
            Node<float> *A,*B,*C;
            A = readSparse<float>();
            B = readSparse<float>();
            printSparse<float>(A);
            printSparse<float>(B);
            C = mulSparse<float>(A,B);      
            printSparse<float>(C);
        }
        if(dtype==3)
        {
            Node<double> *A,*B,*C;
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
            Node<int> *A,*C;;
            A = readSparse<int>();
            printSparse<int>(A);
            C = transposeSparse<int>(A);
            printSparse<int>(C);
        }
        if(dtype==2)
        {
            Node<float> *A,*B,*C;
            A = readSparse<float>();
            printSparse<float>(A);
            C = transposeSparse<float>(A);      
            printSparse<float>(C);
        }
        if(dtype==3)
        {
            Node<double> *A,*C;
            A = readSparse<double>();
            printSparse<double>(A);
            C = transposeSparse<double>(A);     
            printSparse<double>(C);
        }

    }   
    return 0;
}