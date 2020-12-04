#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
class typicalnode{
public:
    int value;
    vector<typicalnode*> neighbours;
    typicalnode(int value){
        this->value=value;
    }
    void addchild(typicalnode* child){
        this->neighbours.push_back(child);
    }
};
class treenode{
public:
    int treesize;
    int parent;
    vector<int> children;
    treenode(int parent){
        this->parent=parent;
        this->treesize=0;
    }
    void addchild(int child){
        this->children.push_back(child);
    }
    void set_treesize(int treesize){
        this->treesize=treesize;
    }
};
void calculatesubtreesize(treenode **array, int n){
    for (int i = n-1; i >0 ; --i) {
        for(auto it = array[i]->children.begin(); it != array[i]->children.end(); it++){
            array[i]->treesize+=array[*it]->treesize;
        }
        (array[i]->treesize)++;
    }
    array[0]->treesize=n;
}
int lca(treenode **array, int n, int nodea, int nodeb,int depth[],int **parents){ //Be careful of +1 in node numberings
    nodea--;
    nodeb--;
    //First set the node with the greater depth as nodea
    if(depth[nodea]<depth[nodeb]) swap(nodea,nodeb);
    //Now lets find the first power of 2 for which that number is greater than the depth of nodea
    int power=1,amount=2;
    while(amount<depth[nodea]) {
        amount*=2;
        power++;
    }
    int i=power;
    while(depth[nodea]-amount<depth[nodeb]){
        nodea=parents[nodea][i];
        amount/=2;
        i--;
        if(i==0) break;
    }
    if(nodea==nodeb) return nodea;
    for(i=power;i>=0;i--){
        if(parents[nodea][i]!=-1 && parents[nodea][i]!=parents[nodeb][i]){
            nodea=parents[nodea][i];
            nodeb=parents[nodeb][i];
        }
    }
    return parents[nodea][0];


}
int secondLCA(int *depth,int nodea,int nodeb, int **parents){
    int p=nodea-1,q=nodeb-1;
    if(p==0 || q==0) return 0;
    int tmp, log, i;
    if (depth[p] < depth[q])
        tmp = p, p = q, q = tmp;
    log = 1;
    while (1) {
        int next = log + 1;
        if ((1 << next) > depth[p])
            break;
        log++;
    }
    for (i = log; i >= 0; i--)
        if (depth[p] - (1 << i) >= depth[q])
            p = parents[p][i];
    if (p == q)
        return p;
    for (i = log; i >= 0; i--)
        if (parents[p][i] != -1 && parents[p][i] != parents[q][i])
            p = parents[p][i], q = parents[q][i];
    return parents[p][0];
    /*
    nodea--;
    nodeb--;
    //First set the node with the greater depth as nodea
    if(depth[nodea]<depth[nodeb]) swap(nodea,nodeb);
    //Now lets find the first power of 2 for which that number is greater than the depth of nodea
    int power=0;
    int amount=1;
    while(amount*2<=depth[nodea]){
        power++;
        amount*=2;
    }
    int i=power,temp=amount;
    for (i = power; i >= 0; i--) {
        if (depth[nodea] - temp >= depth[nodeb])
            nodea = parents[nodea][i];
        temp/=2;
    }

    if (nodea == nodeb)
        return nodea;
    for (i = power; i >= 0; i--)
        if (parents[nodea][i] != -1 && parents[nodea][i] != parents[nodeb][i])
            nodea = parents[nodea][i], nodeb = parents[nodeb][i];
    return parents[nodea][0];
     */
}
int getdistance(int nodea, int nodeb, int **parents, int* depth){
    int lca=secondLCA(depth,nodea,nodeb,parents);
    //cout<<lca<<"lcaaaaaaaaaaaaaaaaaaaaa\n";
    return depth[nodea-1]+depth[nodeb-1]-2*depth[lca];
}
int findspecificancestor(int node, int level, int **parents, int *depth){
    if(level==0) return node;
    level--;
    int power=0;
    int amount=1;
    while(amount*2<=depth[node]){
        power++;
        amount*=2;
    }
    int i=power,temp=amount;
    for(;i>=0;i--){
        if(amount<=level){
            node=parents[node][i];
            level-=amount;
        }
        amount/=2;
    }
    return parents[node][0];
}
int numberofcities(int nodea, int nodeb, int *depth, int **parents, int n,treenode **array){
    if(depth[nodea]<depth[nodeb]) swap(nodea,nodeb);
    int lca=secondLCA(depth,nodea,nodeb,parents);
    int a_distance=getdistance(nodea,lca+1,parents,depth);
    int b_distance=getdistance(nodeb,lca+1,parents,depth);
    if(a_distance==b_distance){
        return n-(array[findspecificancestor(nodea,a_distance-1,parents,depth)]->treesize +
                array[findspecificancestor(nodeb,b_distance-1,parents,depth)]->treesize);
    } else {
        int halfway=getdistance(nodea,nodeb,parents,depth)/2;
        return array[findspecificancestor(nodea,halfway,parents,depth)]->treesize+
                array[findspecificancestor(nodea,halfway-1,parents,depth)]->treesize;
    }
}
int main() {
    int n,m;
    cin>>n;
    int parent,a,b;
    int ceillog=ceil(log(n));
    int depth[n];
    depth[0]=0;
    int **parents=new int*[n];
    for (int i1 = 0; i1 < n; ++i1) {
        parents[i1]=new int[ceillog];
        for (int i = 0; i <ceillog ; ++i) {
            parents[i1][i]=-1;
        }
    }
    //for (int k = 0; k <ceillog ; ++k) parents[0][k]=-1;

    treenode** array=new treenode*[n];
    array[0]=new treenode(0);
    for (int i = 1; i <n ; ++i) {
        cin>>parent;
        array[i]=new treenode(parent-1);
        array[parent-1]->addchild(i);
        parents[i][0]=parent-1;
        depth[i]=depth[parent-1]+1;
    }
    calculatesubtreesize(array,n);
    for (int i = 1; i <n ; ++i) {
        for (int j = 1; j <ceillog ; ++j) {
            if(parents[i][j-1]!=-1) parents[i][j]=parents[parents[i][j-1]][j-1];
        }
    }
    //cout<<secondLCA(depth,1,3,parents)+1;
    //*
    cin>>m;
    int distance;
    for (int j = 0; j <m ; ++j) {
        cin>>a>>b;
        if(a==b) {
            cout<<n<<"\n";
            continue;
        }
        distance=getdistance(a,b,parents,depth);
        //cout<<distance<<"****\n";
        if(distance%2==1 || distance-2*(distance/2)!=0){
            //cout<<"here\n";
            cout<<0<<"\n";
        } else cout<<numberofcities(a,b,depth,parents,n,array)<<"\n";
    }
    //*/
}