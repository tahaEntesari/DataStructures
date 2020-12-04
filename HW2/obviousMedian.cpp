#include <iostream>
#include <string>

using namespace std;
class Heap{
public:
    int parent(int i){
        return i/2;
    }
    int left(int i){
        return 2*i;
    }
    int right(int i){
        return 2*i+1;
    }
};

class MinHeap:public Heap{
public:
    int maxsize;
    int currentsize=0;
    int *arr;
    MinHeap(int n){
        maxsize=n+1;
        arr=new int[maxsize];
    }
    void insert(int n){
        currentsize++;
        arr[currentsize]=n;
        int i=currentsize;
        while(parent(i)>0 && arr[i]<arr[parent(i)]){
            exchange(i,parent(i));
            i=parent(i);
        }
    }
    void exchange(int index1, int index2){
        int temp=arr[index1];
        arr[index1]=arr[index2];
        arr[index2]=temp;
    }
    void minheapify(int index){
        while(left(index)<=currentsize){
            int l=left(index);
            int r=right(index);
            int min=index;
            if(r<=currentsize && arr[r]<arr[min]) min=r;
            if(l<=currentsize && arr[l]<arr[min]) min=l;
            if(min!=index){
                exchange(index,min);
                index=min;
            } else break;
        }
    }
    int extract(){
        int min=arr[1];
        arr[1]=arr[currentsize];
        currentsize--;
        minheapify(1);
        return min;
    };
    int peek(){
        return arr[1];
    }
    void print(){
        for (int i = 1; i <=currentsize ; ++i) {
            cout<<arr[i]<<" ";
        }
        cout<<endl;
    }

};
class MaxHeap: public Heap{
public:
    int maxsize;
    int currentsize=0;
    int *arr;
    MaxHeap(int n){
        maxsize=n;
        arr=new int[maxsize];
    }
    void insert(int n){
        currentsize++;
        arr[currentsize]=n;
        int i=currentsize;
        while(parent(i)>0 && arr[i]>arr[parent(i)]){
            exchange(i,parent(i));
            i=parent(i);
        }
    }
    void exchange(int index1, int index2){
        int temp=arr[index1];
        arr[index1]=arr[index2];
        arr[index2]=temp;
    }
    void maxheapify(int index){
        while(left(index)<=currentsize){
            int l=left(index);
            int r=right(index);
            int max=index;
            if(r<=currentsize && arr[r]>arr[max]) max=r;
            if(l<=currentsize && arr[l]>arr[max]) max=l;
            if(max!=index){
                exchange(index,max);
                index=max;
            } else break;
        }
    }
    int extract(){
        int max=arr[1];
        arr[1]=arr[currentsize];
        currentsize--;
        maxheapify(1);
        return max;
    }
    int peek(){
        return arr[1];
    }
    void print(){
        for (int i = 1; i <=currentsize ; ++i) {
            cout<<arr[i]<<" ";
        }
        cout<<endl;
    }
};
void balance(MinHeap *minheap, MaxHeap *maxheap){
    int difference=(*minheap).currentsize-(*maxheap).currentsize;
    if(difference>1) (*maxheap).insert((*minheap).extract());
    else if (difference<-1) (*minheap).insert((*maxheap).extract());
}
int extractmedian(MinHeap *minheap, MaxHeap *maxheap){
    if((*maxheap).currentsize==(*minheap).currentsize){
        if((*maxheap).peek()<(*minheap).peek()){
            return (*maxheap).extract();
        }else {
            return (*minheap).extract();
        }
    }else {
        if((*maxheap).currentsize>(*minheap).currentsize){
            return (*maxheap).extract();
        }else{
            return (*minheap).extract();
        }
    }
}
int peekmedian(MinHeap *minheap, MaxHeap *maxheap){
    if((*minheap).currentsize>(*maxheap).currentsize){
        return (*minheap).peek();
    } else if ((*minheap).currentsize<(*maxheap).currentsize){
        return (*maxheap).peek();
    } else {
        if((*minheap).peek()<=(*maxheap).peek()) return (*minheap).peek();
        return (*maxheap).peek();
    }
}
void insertelement(MinHeap *minheap, MaxHeap *maxheap, int element){
    if((*maxheap).currentsize==0 || element<(*maxheap).peek()) {
        (*maxheap).insert(element);
    } else {
        (*minheap).insert(element);
    }
}

int extractmedian(int arr[], int *medianpointer, int *medianindex, int next[], int prev[], int currentNumberOfElements, int *firstPointer){
    int temp=arr[*medianpointer];
    //cout<<"the extracted median is "<<temp<<endl;
    if(currentNumberOfElements>=3) {
        next[prev[*medianpointer]]=next[*medianpointer];
        prev[next[*medianpointer]]=prev[*medianpointer];
        if (currentNumberOfElements % 2 == 0) {
            if (*medianindex == currentNumberOfElements / 2) {
                *medianpointer = next[*medianpointer];
            } else {
                *medianpointer = prev[*medianpointer];
                (*medianindex)--;
            }
        } else {
            if (arr[next[*medianpointer]] > arr[prev[*medianpointer]]) {
                *medianpointer = prev[*medianpointer];
                (*medianindex)--;
            } else {
                *medianpointer = next[*medianpointer];
            }
        }
    } else if(currentNumberOfElements==2){
        *medianpointer=next[*medianpointer];
        *medianindex=1;
        *firstPointer=*medianpointer;
    }
    return temp;
}
void insertElement(int arr[], int next[], int prev[], int *medianPointer, int *medianIndex, int elementToAdd, int currentNumberOfElements,
                   int *firstpointer, int whereToInsert){
    arr[whereToInsert]=elementToAdd;
    if(currentNumberOfElements==0) {
        //cout<<"currently no elements in linked list. Setting current element as root"<<endl;
        *firstpointer=whereToInsert;
        *medianPointer=whereToInsert;
        *medianIndex=1;
    }
    else{
        int currentPointer=*firstpointer;
        int i=0;
        while(true){
            if(i==0 && elementToAdd<=arr[currentPointer]){//Add to the beginning of array
                //cout<<"Adding to the beginning of linked list"<<endl;
                next[whereToInsert]=*firstpointer;
                prev[*firstpointer]=whereToInsert;
                *firstpointer=whereToInsert;
                if(currentNumberOfElements%2==1){
                    *medianPointer=prev[*medianPointer];
                } else{
                    (*medianIndex)++;
                }
                break;
            } else if (i<currentNumberOfElements && elementToAdd>arr[currentPointer] ){ //move on
                //cout<<"element to add is greater. Moving on"<<endl;
                if(i!=currentNumberOfElements-1) currentPointer=next[currentPointer];
            } else if(i<=currentNumberOfElements-1){
                //cout<<"Adding element some place between"<<endl;
                next[prev[currentPointer]]=whereToInsert;
                prev[whereToInsert]=prev[currentPointer];
                next[whereToInsert]=currentPointer;
                prev[currentPointer]=whereToInsert;
                if(currentNumberOfElements%2==1){
                    if((i+1)<=*medianIndex){
                        *medianPointer=prev[*medianPointer];
                    } // no else required
                } else {
                    if((i+1)<=*medianIndex){
                        (*medianIndex)++;
                    } else {
                        (*medianIndex)++;
                        *medianPointer=next[*medianPointer];
                    }
                }
                break;
            } else {
                //cout<<"Adding element to the end of linked list"<<endl;
                next[currentPointer]=whereToInsert;
                prev[whereToInsert]=currentPointer;
                if(currentNumberOfElements%2==0){
                    (*medianIndex)++;
                    *medianPointer=next[*medianPointer];
                }
                break;
            }
            i++;
        }
    }
}




int main() {
    int n;
    cin>>n;

    if(n>=190000) {
        int output[n];
        int count = 0;
        MinHeap *minheap;
        MaxHeap *maxheap;
        MinHeap mih(n);
        MaxHeap mah(n);
        minheap = &mih;
        maxheap = &mah;
        int temp;
        for (int i = 0; i < n; ++i) {
            cin >> temp;
            if (temp == 2) {
                output[count] = extractmedian(minheap, maxheap);
                balance(minheap, maxheap);
                count++;
            } else {
                cin >> temp;
                insertelement(minheap, maxheap, temp);
                balance(minheap, maxheap);
            }
        }
        for (int j = 0; j < count; ++j) {
            cout << output[j] << endl;
        }
    }else{
        int temp=0;
        int arr[n], next[n], prev[n],output[n];
        int *medianPointer=new int;
        int *mediansindex=new int;
        int *firstPointer=new int;
        *medianPointer=0;
        *mediansindex=0;
        *firstPointer=0;
        int count = 0;
        int count2 = 0;
        int numberOfItemsInArr = 0;
        for (int i = 0; i < n; ++i) {
            cin >> temp;
            if (temp == 2) {
                output[count2] = extractmedian(arr, medianPointer, mediansindex, next, prev, numberOfItemsInArr,firstPointer);
                count2++;
                numberOfItemsInArr--;
            } else if (temp == 1) {
                cin >> temp;
                insertElement(arr,next,prev,medianPointer,mediansindex,temp,numberOfItemsInArr,firstPointer,count);
                count++;
                numberOfItemsInArr++;
                /*
                temp=*firstPointer;
                for (int j = 0; j <numberOfItemsInArr ; ++j) {
                    cout<<prev[temp]<<" "<<arr[temp]<<" "<<next[temp]<<endl;
                    temp=next[temp];
                }
                 */
            }
        }
        for (int k = 0; k < count2; ++k) {
            cout << output[k] << endl;
        }
    }
}