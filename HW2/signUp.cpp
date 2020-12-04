#include <iostream>
using namespace std;


int AddtoQueue(int **queues, int *lastindofeachsubqueue, int elementtoadd, int *queuesaddedto){
    static int numberofsubqueues=0;
    static int count=0;
    for (int i = 0; i <=numberofsubqueues; ++i) {
        if (lastindofeachsubqueue[i]==-1){
            queues[i][0]=elementtoadd;
            lastindofeachsubqueue[i]++;
            numberofsubqueues++;
            queuesaddedto[count]=i+1;
            count++;
            return numberofsubqueues;
        }
        if(queues[i][lastindofeachsubqueue[i]]<=elementtoadd){
            queues[i][lastindofeachsubqueue[i]+1]=elementtoadd;
            lastindofeachsubqueue[i]++;
            queuesaddedto[count]=i+1;
            count++;
            return numberofsubqueues;
        }
    }
}

void MovefromQueue(int **queues, int *lastindofeachsubqueue, int numberofqueues,int n){
    int min;
    int whichqueue;
    for (int k = 0; k <n ; ++k) {
        min = 2000000000;
        for (int i = 0; i < numberofqueues; ++i) {
            if (lastindofeachsubqueue[i]>=0 && queues[i][0] < min) {
                min = queues[i][0];
                whichqueue = i;
            }
        }
        lastindofeachsubqueue[whichqueue]--;
        for (int j = 0; j <= lastindofeachsubqueue[whichqueue]; ++j) queues[whichqueue][j] = queues[whichqueue][j + 1];
        cout<<2<<" "<<whichqueue+1<<endl;
    }
}
int makeQueue(int a[], int dim){
    int startpointer=0;
    int endpointer=0;
    int numberofsubqueues=0;
    int startindices[dim], endindices[dim];
    int sorted[dim];
    int whereDoesEachBelong[dim];
    int j,key;
    for (int i = 0; i <dim; ++i) {
        // Performing insertion sort
        whereDoesEachBelong[i]=numberofsubqueues;
        sorted[i]=a[i];
        key = sorted[i];
        j = i - 1;
        while (j >= 0 && sorted[j] > key){
            sorted[j + 1] = sorted[j];
            j = j - 1;
        }
        sorted[j + 1] = key;


        // Finding the sub-Queues
        if (a[i]<=a[i+1]){
            endpointer+=1;
        } else {
            startindices[numberofsubqueues]=startpointer;
            endindices[numberofsubqueues]=endpointer;
            startpointer=endpointer+1;
            endpointer++;
            numberofsubqueues++;
        }
    }
    for (int k = 0; k <dim ; ++k) {
        cout<< sorted[k] << " "<< whereDoesEachBelong[k]<<endl;
    }



    return numberofsubqueues;
}
int main() {
    int n, numberofqueues;
    cin>>n;
    int elementToAdd;
    int **queues=new int*[n];
    int *lastindexofeachsubqueue=new int[n];
    int *queuesaddedto=new int[n];

    for (int j = 0; j <n ; ++j) {
        lastindexofeachsubqueue[j]=-1;
        queues[j]=new int[n];
    }
    for (int i = 0; i <n ; ++i) {
        cin>>elementToAdd;
        numberofqueues=AddtoQueue(queues,lastindexofeachsubqueue,elementToAdd,queuesaddedto);
    }
    cout<<numberofqueues<<" "<<2*n<<endl;
    for (int k = 0; k <n ; ++k) {
        cout<<1<<" "<<queuesaddedto[k]<<endl;
    }
    MovefromQueue(queues,lastindexofeachsubqueue,numberofqueues,n);



}