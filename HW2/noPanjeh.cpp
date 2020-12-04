#include <iostream>
#include <fstream>
using namespace std;
void MooooveIt(int arr[], int next[], int prev[], int currentPosition, int direction, int stepsize, int n){
    // Direction=0 means clockwise and 1 means counterclockwise
    int nn=currentPosition;
    if(currentPosition==next[nn]){
        cout<<arr[currentPosition]+1;
        return;
    }
    if(direction==0){
        for (int i = 0; i <stepsize ; ++i) nn=next[nn];
        next[prev[nn]]=next[nn];
        prev[next[nn]]=prev[nn];
        currentPosition=next[nn];
        direction=arr[currentPosition]%2==1?1:0;
        MooooveIt(arr,next,prev,currentPosition,direction,stepsize,n);
    }else{
        for (int i = 0; i <stepsize ; ++i) nn=prev[nn];
        next[prev[nn]]=next[nn];
        prev[next[nn]]=prev[nn];
        currentPosition=next[nn];
        direction=arr[currentPosition]%2==1?1:0;
        MooooveIt(arr,next,prev,currentPosition,direction,stepsize,n);
    }
}

int main() {
    int n,stepsize;
    cin>>n>>stepsize;
    int *prev,*arr,*next;
     prev=new int[n];
     arr=new int[n];
     next=new int[n];
    for (int i = 0; i <n ; ++i) {
        arr[i]=i;
        next[i]=i==n-1?0:i+1;
        prev[i]=i==0?n-1:i-1;
    }
    MooooveIt(arr,next,prev,0,0,stepsize,n);
}