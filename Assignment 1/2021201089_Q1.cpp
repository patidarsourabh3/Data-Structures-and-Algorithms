/*
Input format:
First line will contain a number from (1-4)
1 - for Exponentition
2 - for factorial
3 - for gcd
4 - for calcultor
if the number entered in first line is 
1 then enter 2 number to calculate (x^y)
2 then enter a number to calculate its factorial
3 then enter 2 number to calculate their Greatest common divisor(GCD)
4 then enter a expression containing number and (+/-/*) and get the value of expression

Output format:
Single string corresponding to one of the four operation
*/
#include <iostream>
#include <string>
using namespace std;
string multiply(string a, string b)
{
    int x =a.length();
    int y =b.length();
    int ans[x+y+1];
    int k=0;
    for(int i=0;i<=x+y;i++)
        ans[i]=0;
    for(int i=y-1;i>=0;i--)
    {
        k=y-i-1;
        for(int j=x-1;j>=0;j--)
        {
            ans[k]+= ((a[j]-'0')*(b[i]-'0'));
            k++;
        }
    }
    for(int i=0;i<x+y;i++)
    {
        if(ans[i]>=10)
        {
            ans[i+1] = ans[i+1] + ans[i]/10;
            ans[i]=ans[i]%10;
        }
    }
    int i=x+y-1;
    while(i>=0&&ans[i]==0)
        i--;
    string res ="";
    for(;i>=0;i--)
        res+= ans[i]+'0';
    if(res.length()==0)
        return "0";
    return res;
}
string convertToString(int x)
{
    string res="";
    while(x)
    {
        res += ((x%10)+'0');
        x=x/10;
    }
    string ans ="";
    for(int i=res.size()-1;i>=0;i--)
        ans +=res[i];
    return ans;
}
int convertToInt(string x)
{
    int res=0;
    for(int i=0;i<x.length();i++)
    {
        res = res*10 + (x[i]-'0');
    }
    return res;
}
string factorial(string a)
{
    string res="1";
    int n = convertToInt(a);
    for(int i=2;i<=n;i++)
    {
        string s = convertToString(i);
        res=multiply(res,s);
    }
    return res;
}
string add(string a, string b)
{
    int x =a.length();
    int y =b.length();
    int ans[x+y+1];
    for(int i=0;i<=x+y;i++)
        ans[i]=0;
    int i= x-1;
    int j= y-1;
    int k=0;
    while(i>=0&&j>=0)
    {
        ans[k] = ((a[i]-'0')+(b[j]-'0'));
        i--;
        j--;
        k++;
    }
    while(i>=0)
    {
        ans[k]=(a[i]-'0');
        i--;
        k++;
    }
    while(j>=0)
    {
        ans[k]=(b[j]-'0');
        j--;
        k++;
    }
    for(int i=0;i<x+y;i++)
    {
        if(ans[i]>=10)
        {
            ans[i+1] = ans[i+1] + ans[i]/10;
            ans[i]=ans[i]%10;
        }
    }
    i=x+y-1;
    while(i>=0&&ans[i]==0)
        i--;
    string res ="";
    for(;i>=0;i--)
        res+= ans[i]+'0';
    if(res.length()==0)
        return "0";
    return res;
}
string subtract(string a, string b)
{
    int x =a.length();
    int y =b.length();
    int ans[x+y+1];
    for(int i=0;i<=x+y;i++)
        ans[i]=0;
    int i= x-1;
    int j= y-1;
    int k=0;
    while(i>=0&&j>=0)
    {
        ans[k] = ((a[i]-'0')-(b[j]-'0'));
        i--;
        j--;
        k++;
    }
    while(i>=0)
    {
        ans[k]=(a[i]-'0');
        i--;
        k++;
    }
    while(j>=0)
    {
        ans[k]=(b[j]-'0');
        j--;
        k++;
    }
    for(int i=0;i<x+y;i++)
    {
        if(ans[i]<0)
        {
            ans[i+1] = ans[i+1] -1;
            ans[i]=ans[i]+10;
        }
    }
    i=x+y-1;
    while(i>=0&&ans[i]==0)
        i--;
    string res ="";
    for(;i>=0;i--)
        res+= ans[i]+'0';
    if(res.length()==0)
        return "0";
    return res;
}
string calculator(string str)
{
    string op1 ="";
    string op2 ="";
    int i=0;
    string str2 ="";
    while(i<str.length())
    {
        if(op1.length()==0)
        {
            while(str[i]>='0'&&str[i]<='9')
            {
                op1+=str[i];
                i++;
            }
        }
        char sign = str[i++];
        if(sign=='+' || sign=='-')
        {
            str2 += op1;
            str2+=sign;
            op1 = "";
            op2 = "";
        }
        if(sign=='*'||sign=='x')
        {
            while(str[i]>='0'&&str[i]<='9')
            {
                op2+=str[i];
                i++;
            }
            op1 = multiply(op1,op2);
            op2 ="";
        }
    }
    str2+=op1;
    i=0;
    op1="";
    op2="";
    while(i<str2.length()&&str2[i]>='0'&&str2[i]<='9')
    {
        op1 += str2[i];
        i++;
    }
    char sign = str2[i++];
    while(i<str2.length())
    {
        while(str2[i]>='0'&&str2[i]<='9')
        {
            op2+=str2[i];
            i++;
        }
        if(sign=='+')
        {
            op1 = add(op1,op2);
            op2 ="";
        }
        if(sign=='-')
        {
            op1 = subtract(op1,op2);
            op2 ="";
        }
        sign = str2[i++];
    }
    return op1;
}
string Exponentiation(string a, long long int b)
{
    string res ="1";
    while(b)
    {
        if(b%2==1)
            res = multiply(res,a);
        b=b>>1;
        a = multiply(a,a);
    }
    return res;
}
string mod(string a, string b)
{
    if(a.length()<b.length())
        return a;
    if(a.length()==b.length()&&a<b)
        return a;
    int i=b.length();
    string str = a.substr(0,b.length());
    if(str<b)
        str +=a[i++];
    while(str.length()>b.length())
        str = subtract(str,b);
    if(str.length()==b.length())
    {
        while(str.length()==b.length()&&str>=b)
            str = subtract(str,b);
    }
    while(i<a.length())
    {
        if(str.length()<=b.length())
            str+=a[i++];
        while(str.length()>b.length())
            str = subtract(str,b);
        if(str.length()==b.length())
        {
            while(str.length()==b.length()&&str>=b)
                str = subtract(str,b);
        }
    }
    int j=0;
    while(str[j]=='0'&&str.length()>1)
    {
        str.erase(0,1);
    }
    return str;
}
string gcd(string a, string b)
{
    if(a=="0")
        return b;
    return gcd(mod(b,a), a);
}
int main()
{
    int ch;
    string a,b;
    long long int c;
    cin>>ch;
    switch(ch)
    {
        case 1: cin>>a>>c;
                cout<<Exponentiation(a,c)<<endl;
                break;
        case 2: cin>>a;
                cout<<factorial(a)<<endl;
                break;
        case 3: cin>>a>>b;
                cout<<gcd(a,b)<<endl;
                break;
        case 4: 
                cin>>a;
                cout<<calculator(a)<<endl;
                break;   
    }
    return 0;
}
