#include <iostream>
#include <bitset>
using namespace std;
int myhash(int x, int i, int m){
    int h1=x % m;
    h1=h1<0?h1+m:h1;
    int h2=x%(m-1);
    h2=h2<0?h2+m:h2+1;
    int h3=(h1+i*h2)%m;
    h3=h3<0?h3+m:h3;
    return h3;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q,m,k;
    cin>>q>>m>>k;
    bool *bloomfilter=new bool[m]();

    int temp,flag,min,temp2;
    for (int i = 0; i <q ; ++i) {
        cin>>temp;
        if(temp==1){
            cin>>temp;
            min=-2;
            for (int j = 0; j <k ; ++j) {
                temp2=myhash(temp,j,m)-1;
                if(!bloomfilter[temp2] && (min==-2||temp2<min)) min=temp2;
                bloomfilter[temp2]=true;
            }
            cout<<min+1<<"\n";
        } else {
            flag=1;
            cin>>temp;
            for (int j = 0; j <k ; ++j) {
                if(bloomfilter[myhash(temp,j,m)-1]==0){
                    flag = 0;
                    break;
                }
            }
            if(flag == 1) cout<<"Y\n";
            else cout<<"N\n";

        }
    }
    cout<<endl;


}