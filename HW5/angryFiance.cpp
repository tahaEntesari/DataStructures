#include <iostream>
using namespace std;
class node {
public:
    node * parent;
    int size;
    int rank;
    node(){
        this->parent=this;
        this->size=1;
        this->rank=0;
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
int size(node* x){
    x=find(x);
    return x->size;
}
int main() {
    int n,m;
    cin>>n>>m;
    int temp,x,y;
    node** array=new node*[n];
    for (int i = 0; i < n; ++i) {
        array[i]=new node;
    }
    for (int j = 0; j <m ; ++j) {
        cin>>temp;
        switch (temp){
            case 1://join
                cin>>x>>y;
                join(array[x-1],array[y-1]);
                break;
            case 2://return size
                cin>>x;
                cout<<size(array[x-1])<<"\n";
                break;
        }
    }
    cout<<endl;
}