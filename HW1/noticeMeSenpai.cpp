#include <iostream>
#include <cmath>

using namespace std;

int n;
int calculatecertainindex(const int a[], int index){
    long long int b=1;
    for (int i = 0; i < n; ++i) {
        if(i==index) continue;
        b= b * (long long int) a[i] % a[index];
    }
    return (int) b;
}
int returnapeak2(int a[],int findex, int lindex){
    int midpone;
    int midmone;
    if (findex==lindex) return findex;
    int mid=ceil((findex+lindex)/2.0);
    midpone=mid==lindex?lindex:mid+1;
    midmone=mid-1;
    int midamount=calculatecertainindex(a,mid);
    int midmoneamount=calculatecertainindex(a,midmone);
    if (midmoneamount>=midamount) return returnapeak2(a,findex,mid-1);
    int midponeamount=calculatecertainindex(a,midpone);
    if (midponeamount>=midamount) return returnapeak2(a,midpone,lindex);
    else return mid;
}
int main() {
    cin >> n;
    int A [n];
    for (int i = 0; i <n ; ++i) {
        cin >> A[i];
    }
    cout<<returnapeak2(A,0,n-1)+1;
    return 0;
}