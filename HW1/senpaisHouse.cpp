#include <iostream>
#include <cmath>
using namespace std;
int submatrixsum(int **a, int **b, int A1, int A2, int B1, int B2, int m){
    int sum,temp,temp2;
    sum=0;
    for (int i = 0; i <m; ++i) {
        temp=0;
        temp2=0;
        for (int j = A1; j <=A2 ; ++j)  temp+=*(*(a+j)+i);
        for (int k = B1; k <=B2 ; ++k) temp2+=*(*(b+i)+k);
        sum+=temp*temp2;
    }
    return sum;
}
int sumofmatrix(int **c, int rowind1, int rowind2, int colind1, int colind2){
    int sum=0;
    for (int i = rowind1; i <=rowind2 ; ++i) for (int j = colind1; j <=colind2 ; ++j) sum+=*(*(c+i)+j);
    return sum;
}
void findwrong(int **a, int **b, int **c, int rowind1, int rowind2, int colind1, int colind2, int m){
    int sum1;
    int realsum1;
    if (colind1==colind2){
        if(rowind1==rowind2){
            cout<<rowind1+1<<" "<<colind1+1;
            return;
        }
        else{
            int rowmid;
            rowmid=(rowind1+rowind2)/2;
            realsum1=sumofmatrix(c,rowind1,rowmid,colind1,colind1);
            sum1=submatrixsum(a,b,rowind1,rowmid,colind1,colind1,m);
            if(sum1==realsum1) return findwrong(a,b,c,rowmid+1,rowind2,colind2,colind2,m);
            else return findwrong(a,b,c,rowind1,rowmid,colind2,colind2,m);
        }
    }
    int colmid;
    colmid=(colind1+colind2)/2;
    realsum1=sumofmatrix(c,rowind1,rowind2,colind1,colmid);
    sum1=submatrixsum(a,b,rowind1,rowind2,colind1,colmid,m);
    if(sum1==realsum1) return findwrong(a,b,c,rowind1,rowind2,colmid+1,colind2,m);
     else return findwrong(a,b,c,rowind1,rowind2,colind1,colmid,m);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m,r;
    cin >>n>>m>>r;
    int **A=new int*[n];
    int **B=new int*[m];
    int **C=new int*[n];
    for (int i1 = 0; i1 <n ; ++i1) {
        A[i1]=new int[m];
        C[i1]=new int[r];
    }
    for (int j1 = 0; j1 <m ; ++j1) {
        B[j1]=new int[r];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <m ; ++j) {
            cin>>A[i][j];
        }
    }
    for (int k = 0; k <m ; ++k) {
        for (int i = 0; i <r ; ++i) {
            cin>>B[k][i];
        }
    }
    for (int l = 0; l <n ; ++l) {
        for (int i = 0; i <r ; ++i) {
            cin>>C[l][i];
        }
    }
    findwrong(A,B,C,0,n-1,0,r-1,m);
}