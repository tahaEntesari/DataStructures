#include <iostream>
using namespace std;

class node {
public:
    node * parent;
    long long int size;
    long long int rank;
    node(){
        this->parent=this;
        this->size=1;
        this->rank=0;
    }
};
class edge{
public:
    int value;
    int u,v;
    int initialPosition;
    edge(int value,int u, int v, int initialPosition){
        this->value=value;
        this->u=u;
        this->v=v;
        this->initialPosition=initialPosition;
    }
};

node* find(node* x){
    if(x->parent!=x) x->parent=find(x->parent);
    return x->parent;
}
void join(node* x, node* y){
    //First find the root of each group
    x=find(x);
    y=find(y);
    if(y==x) return;
    if(x->rank < y->rank) {
        x->parent=y;
        y->size+=x->size;
    }
    else{
        y->parent=x;
        if(x->rank == y->rank) (x->rank)++;
        x->size+=y->size;

    }
}
long long int size(node* x){
    x=find(x);
    return x->size;
}

// Merge Sort
void merge(edge **array, int l, int m, int r) {
    int i, j, k, nl, nr;
    //size of left and right sub-arrays
    nl = m-l+1; nr = r-m;
    edge *larr[nl], *rarr[nr];
    //fill left and right sub-arrays
    for(i = 0; i<nl; i++)
        larr[i] = array[l+i];
    for(j = 0; j<nr; j++)
        rarr[j] = array[m+1+j];
    i = 0; j = 0; k = l;
    //marge temp arrays to real array
    while(i < nl && j<nr) {
        if(larr[i]->value <= rarr[j]->value) {
            array[k] = larr[i];
            i++;
        }else{
            array[k] = rarr[j];
            j++;
        }
        k++;
    }
    while(i<nl) {       //extra element in left array
        array[k] = larr[i];
        i++; k++;
    }
    while(j<nr) {     //extra element in right array
        array[k] = rarr[j];
        j++; k++;
    }
    /*
    for (int n = 0; n <nl ; ++n) {
        delete(larr[n]);
    }
    for (int i1 = 0; i1 <nr ; ++i1) {
        delete(rarr[i1]);
    }
     */

}
void mergeSort(edge **array, int l, int r) {
    int m;
    if(l < r) {
        int m = l+(r-l)/2;
        // Sort first and second arrays
        mergeSort(array, l, m);
        mergeSort(array, m+1, r);
        merge(array, l, m, r);
    }
}

///////////////////////////////////
/*
void swap(edge *a, edge* b)
{
    edge *t = new edge(a->value,a->u,a->v,0);
    a->value=b->value;
    a->v=b->v;
    a->u=b->u;
    b->value=t->value;
    b->u=t->u;
    b->v=t->v;
}

int partition (edge **arr, int low, int high)
{
    int pivot = arr[high]->value;    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j]->value <= pivot)
        {
            i++;    // increment index of smaller element
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}


void quickSort(edge **arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
*/

int main() {
    int n,u,v,f;
    cin>>n;
    node** array=new node*[n];
    long long int results[n-1];
    for (int i = 0; i < n; ++i) {
        array[i]=new node;
    }
    edge** edges=new edge*[n-1];
    int originalweightarray[n-1];
    for (int i = 0; i <n-1 ; ++i) {
        cin>>u>>v>>f;
        originalweightarray[i]=f;
        edges[i]=new edge(f,u-1,v-1,i);
    }
    mergeSort(edges,0,n-2);
    //quickSort(edges,0,n-2);
    for (int j = 0; j <n-1 ; ++j) {
        results[edges[j]->initialPosition]=2*size(array[edges[j]->v])*size(array[edges[j]->u]);
        join(array[edges[j]->v],array[edges[j]->u]);
    }
    /*
    int temp;
    for (int k = 0; k <n-1 ; ++k) {
        temp=(n-1)/2;
        while(edges[temp]->value!=originalweightarray[k]) {
            //
            // cout<<edges[temp]->value<<" "<<originalweightarray[k]<<" "<<temp<<endl;
            if (edges[temp]->value > originalweightarray[k]) temp = temp / 2;
            else temp=(n-1+temp)/2;
        }
        cout<<results[temp]<<" ";
    }
     */
    for (int k = 0; k <n-1 ; ++k) {
        cout<<results[k]<<" ";
    }
    cout<<endl;
}