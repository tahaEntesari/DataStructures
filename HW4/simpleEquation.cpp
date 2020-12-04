#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int modd=1000000007;

//Function from HW1
long long int mypower(int base,int exp){
    if (exp==1) return base;
    if (exp==0) return 1;
    long long int copy = base;
    int currentpower = 1;
    while (true) {
        currentpower *= 2;
        copy = (copy*copy)%modd;
        if (currentpower * 2 > exp)
            break;
    }
    return (copy*mypower(base,exp-currentpower))%modd;
}
bool checkresult(long long int a,long long int b,long long int c){
    /*
    a=a<0?a+modd:a;
    b=b<0?b+modd:b;
    c=c<0?c+modd:c;
     */
    return (a+b-c)%modd==0;
}

int main() {
    string s;
    cin>>s;
    int n=s.length();
    int lowerbound=ceil((double)n/3),upperbound=floor(n/2);
    auto *forwardWeight=new long long int[n]();
    forwardWeight[0]=s[0]-48;
    long long int a,b,c;
    for (int i = 1; i <n ; ++i) {
        forwardWeight[i]=(forwardWeight[i-1]*10%modd+s[i]-48)%modd;
    }
    for (int j = lowerbound; j <=upperbound ; ++j) {
        c=(forwardWeight[n-1]-(forwardWeight[n-j-1]*mypower(10,j))%modd)%modd;
        if(n-2*j<=0) goto three;
        one:
        // case 1: a and c are the same length
        a=forwardWeight[j-1];
        b=(forwardWeight[n-j-1]-(forwardWeight[j-1]*mypower(10,n-2*j))%modd)%modd;
        if(checkresult(a,b,c)){
            //cout<<"one happened";
            cout<<j<<" "<<n-2*j <<" "<<j;
            break;
        }
        two:
        //case 2: b and c are the same length
        a=forwardWeight[n-2*j-1];
        b=(forwardWeight[n-j-1]-(forwardWeight[n-2*j-1]*mypower(10,j))%modd)%modd;
        if(checkresult(a,b,c)){
            //cout<<"two happened";
            cout<<n-2*j<<" "<<j <<" "<<j;
            break;
        }
        three:
        if(n-2*j+1<=0) continue;
        //case 3: a is of length c-1
        a=forwardWeight[j-2];
        b=(forwardWeight[n-j-1]-(forwardWeight[j-2]*mypower(10,n-2*j+1))%modd)%modd;
        if(checkresult(a,b,c)){
            //cout<<"three happened";
            cout<<j-1<<" "<<n-2*j+1 <<" "<<j;
            break;
        }
        four:
        //case 4: b is of length c-1
        a=forwardWeight[n-2*j];
        b=(forwardWeight[n-j-1]-(forwardWeight[n-2*j]*mypower(10,j-1))%modd)%modd;
        if(checkresult(a,b,c)){
            //cout<<"four  happened";
            cout<<n-2*j+1<<" "<<j-1<<" "<<j;
            break;
        }
    }

}