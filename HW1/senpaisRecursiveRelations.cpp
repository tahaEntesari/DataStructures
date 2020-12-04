#include <iostream>
using namespace std;

int modd=1000000007;
void matrixMultonethree(int ***a,int count, int **b, int **output, int dim){
    int temp;
    for (int i = 0; i <dim ; ++i) for (int j = 0; j <dim ; ++j) {
            temp=0;
            for (int k = 0; k <dim ; ++k) {
                temp=(temp+((long long int)a[count][i][k]*(long long int)b[k][j]%modd))%modd;
            }
            output[i][j]=temp;
        }
}
void matrixpower3star(int ***a, int count, int dim){
    int temp;
    for (int i = 0; i <dim ; ++i) for (int j = 0; j <dim ; ++j) {
            temp=0;
            for (int k = 0; k <dim ; ++k) {
                temp=(temp+((long long int)a[count][i][k]*(long long int)a[count][k][j]%modd))%modd;
            }
            a[count+1][i][j]=temp;
        }
}
void Letscalculatethepowers(int **A,int vector[],int dim, long long int * powertocal){
    long long int currentPower=1;
    int count=0;
    int **result=new int*[dim];
    int **temp=new int*[dim];
    auto ***powersOfA=new int **[60];
    for (int i = 0; i <60 ; ++i) {
        powersOfA[i]=new int*[dim];
        for (int j = 0; j <dim ; ++j) {
            powersOfA[i][j]=new int[dim];
            result[j]=new int[dim];
            temp[j]=new int[dim];
        }
    }
    for (int k = 0; k <dim ; ++k) {
        for (int i = 0; i <dim ; ++i) {
            powersOfA[0][k][i]=A[k][i];
            result[k][i]=k==i?1:0;
        }
    }

    while (2*currentPower<=*powertocal){
        matrixpower3star(powersOfA,count,dim);
        count++;
        currentPower*=2;
    }
    currentPower=1;
    count=0;
    while(2*currentPower<=*powertocal){
        currentPower*=2;
        count++;
        if(2*currentPower>*powertocal){
            matrixMultonethree(powersOfA,count,result,temp,dim);
            for (int i = 0; i <dim ; ++i) for (int j = 0; j <dim ; ++j) result[i][j]=temp[i][j];
            count=0;
            *powertocal-=currentPower;
            currentPower=1;
        }
    }
    if (*powertocal==1){
        matrixMultonethree(powersOfA,0,result,temp,dim);
    } else {
        for (int i = 0; i <dim ; ++i) {
            for (int j = 0; j <dim ; ++j) {
                temp[i][j]=result[i][j];
            }
        }
    }
    count=0;
    for (int i = 0; i <dim ; ++i) {
        count=(count+(((long long int)temp[i][0]*(long long int)vector[i])%modd))%modd;
    }
    count=count<0?count+modd:count;
    cout<<count;
}

int main() {
    long long int n;
    int t;
    cin >> n >> t;
    int a0;
    int a[t],f[t];
    cin>>a0;
    for (int i = 0; i <t ; ++i) cin>>a[i];
    for (int j = 0; j <t ; ++j) cin>>f[t-j-1];
    if (n<t) {
        cout<<f[t-1-n];
        return 0;
    } else {
        auto *powertocal=new long long int;
        *powertocal=n-t+1;
        int vector[t+1];
        int **A=new int*[t+1];
        for (int i = 0; i <=t; ++i) {
            A[i]=new int[t+1];
            for (int j = 0; j <=t ; ++j) {
                A[i][j]=0;
            }
        }
        for (int i = 0; i <=t ; ++i) {
            vector[i]=i<t?f[i]:a0;
            for (int j = 0; j <=t; ++j) {
                if(i==0 && j<t){
                    A[j][0]=a[j];
                }
                if(j==i+1&&i<t-1&&j<t){
                    A[i][j]=1;
                }
            }
        }
        A[t][0]=1;
        A[t][t]=1;
        Letscalculatethepowers(A, vector, t + 1, powertocal);
    }
}