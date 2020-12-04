#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n,m;
    cin>>n>>m;
    unordered_set<string> dictionary;
    string temp,temp2;
    for (int i = 0; i <n ; ++i) {
        cin>>temp;
        dictionary.insert(temp);
    }
    auto itr=dictionary.end();
    int flag;
    for (int j = 0; j <m ; ++j) {
        cin>>temp;
        flag=0;
        for (int i = 0; i <temp.length() ; ++i) {
            temp2=temp;
            flag=0;
            if(temp[i]=='a'){
                temp2[i]='b';
                itr = dictionary.find(temp2);
                if(itr!=dictionary.end()) {
                    flag = 1;
                    break;
                }
                temp2[i]='c';
                itr = dictionary.find(temp2);
                if(itr!=dictionary.end()) {
                    flag = 1;
                    break;
                }
             } else if(temp2[i]=='b') {
                temp2[i]='a';
                itr = dictionary.find(temp2);
                if(itr!=dictionary.end()) {
                    flag = 1;
                    break;
                }
                temp2[i]='c';
                itr = dictionary.find(temp2);
                if(itr!=dictionary.end()) {
                    flag = 1;
                    break;
                }
            } else {
                temp2[i]='a';
                itr = dictionary.find(temp2);
                if(itr!=dictionary.end()) {
                    flag = 1;
                    break;
                }
                temp2[i]='b';
                itr = dictionary.find(temp2);
                if(itr!=dictionary.end()) {
                    flag = 1;
                    break;
                }
            }
        }
        if(flag==1) cout<<"YES\n";
        else cout<<"NO\n";

    }
    cout<<endl;

}