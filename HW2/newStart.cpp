#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin>>n;
    int a[n];
    for (int i = 0; i <n ; ++i) cin>>a[i];
    int indices[2][n];
    for (int j = 0; j <n ; ++j) {
        indices[0][j]=-1;
        indices[1][j]=n;
    }
    int j;
    for (int k = 1; k <n ; ++k) {
        j=k-1;
        while(j>=0){
            if (a[k]>a[j]){
                indices[0][k]=j;
                break;
            } else if(j>0) {
                j=indices[0][j];
            } else{
                break;
            }
        }
    }
    for (int k = n-2; k >=0 ; --k) {
        j=k+1;
        while(j<n){
            if(a[k]>a[j]){
                indices[1][k]=j;
                break;
            } else if(j<n-1){
                j=indices[1][j];
            } else break;
        }
    }
    for (int l = 0; l <n ; ++l) {
        indices[0][l]=indices[0][l]==-1?0:indices[0][l]+1;
        indices[1][l]=indices[1][l]==n?0:indices[1][l]+1;
        cout<<indices[0][l]<<" "<<indices[1][l]<<"\n";
    }
}