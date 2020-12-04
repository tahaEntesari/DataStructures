#include <iostream>
#include <algorithm>
#include <random>
#include <time.h>
using namespace std;


void randompermutation (int n,vector<int> &myvector) {
    srand ( time(0) );
    // using built-in random generator:
    random_shuffle ( myvector.begin(), myvector.end() );
    // print out content:
}
void inserttograph(int ** graph, int u, int v){
    if(graph[0][u]!=0) graph[1][u]=v;
    else graph[0][u]=v;
    if(graph[0][v]!=0) graph[1][v]=u;
    else graph[0][v]=u;
}

bool checkpermutationvalidity(int**graph, vector<int> myvector, int m){
    for (auto it=myvector.begin(); it!=myvector.end()-1; ++it){
        if(graph[0][*(it)]==*(it+1) || graph[1][*(it)]==*(it+1)) return false;
    }
    return  true;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m;
    cin>>n>>m;
    int **graph=new int*[2];
    graph[0]=new int[n]();
    graph[1]=new int[n]();
    int u,v;
    for (int i = 0; i <m ; ++i) {
        cin>>u>>v;
        inserttograph(graph,u-1,v-1);
    }
    vector<int> myvector;
    for (int i=0; i<n; ++i) myvector.push_back(i);
    here:
    randompermutation(n,myvector);
    if (!checkpermutationvalidity(graph,myvector,m)) goto here;
    myvector.push_back(myvector[0]);
    int count=0;
    for (auto it=myvector.begin(); it!=myvector.end(); it++){
        cout<<*(it)+1<<" "<<*(it+1)+1<<"\n";
        count++;
        if(count==m) break;
    }


    cout << endl;


}