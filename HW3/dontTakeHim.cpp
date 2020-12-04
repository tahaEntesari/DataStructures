#include <iostream>
#include <bitset>
using namespace std;

class MyTrie{
public:
    MyTrie* character[2];
    MyTrie(){
        this->character[1]=nullptr;
        this->character[0]=nullptr;
    }
    void insert(string bitstring){
        char temp=bitstring[0];
        if(bitstring.length()!=1) {
            if (temp == '0') {
                if(this->character[0]== nullptr) {
                    this->character[0] = new MyTrie();
                    this->character[0]->insert(bitstring.substr(1));
                } else {
                    this->character[0]->insert(bitstring.substr(1));
                }
            } else if (temp == '1') {
                if(this->character[1]== nullptr) {
                    this->character[1] = new MyTrie();
                    this->character[1]->insert(bitstring.substr(1));
                } else {
                    this->character[1]->insert(bitstring.substr(1));
                }
            }
        } else{
            if (temp == '0') {
                this->character[0] = new MyTrie();
            } else if (temp == '1') {
                this->character[1] = new MyTrie();
            }
        }
    }
    void findmaxsubjecttoxor(string currentXor, char *answer,int count, int onlymaxwithoutxor){
        if(onlymaxwithoutxor==0) {
            if (currentXor[0] == '0' && this->character[1] != nullptr) {
                answer[count]='1';
                count++;
                bool mycondition=(this->character[1]->character[0]== nullptr) &&(this->character[1]->character[1]== nullptr);
                if(mycondition== true) return;
                this->character[1]->findmaxsubjecttoxor(currentXor.substr(1), answer,count ,onlymaxwithoutxor);
            } else if (currentXor[0] == '0' && this->character[0] != nullptr) {
                answer[count]='0';
                count++;
                bool mycondition=(this->character[0]->character[0]== nullptr) &&(this->character[0]->character[1]== nullptr);
                if(mycondition== true) return;
                this->character[0]->findmaxsubjecttoxor(currentXor.substr(1), answer,count ,onlymaxwithoutxor);
            } else if (currentXor[0] == '1' && this->character[0] != nullptr) {
                answer[count]='1';
                count++;
                bool mycondition=(this->character[0]->character[0]== nullptr) &&(this->character[0]->character[1]== nullptr);
                if(mycondition== true) return;
                this->character[0]->findmaxsubjecttoxor(currentXor.substr(1), answer,count ,onlymaxwithoutxor);
            } else if (currentXor[0] == '1' && this->character[1] != nullptr) {
                answer[count]='0';
                count++;
                bool mycondition=(this->character[1]->character[0]== nullptr) &&(this->character[1]->character[1]== nullptr);
                if(mycondition== true) return;
                this->character[1]->findmaxsubjecttoxor(currentXor.substr(1), answer,count ,onlymaxwithoutxor);
            }

        } else{
            if(this->character[1]!= nullptr){
                answer[count]='1';
                count++;
                bool mycondition=(this->character[1]->character[0]== nullptr) &&(this->character[1]->character[1]== nullptr);
                if(mycondition== true) return;
                this->character[1]->findmaxsubjecttoxor(currentXor, answer,count ,onlymaxwithoutxor);
            }else if(this->character[0]!= nullptr){
                answer[count]='0';
                count++;
                bool mycondition=(this->character[0]->character[0]== nullptr) &&(this->character[0]->character[1]== nullptr);
                if(mycondition== true) return;
                this->character[0]->findmaxsubjecttoxor(currentXor, answer,count ,onlymaxwithoutxor);
            }
        }
    }

};

int main(){

    bitset<30> mybit(0);
    char *answer=new char[32];
    MyTrie* trie;
    trie=new MyTrie();
    trie->insert(mybit.to_string());
    int currentXor=-1;
    int n,temp;
    cin >>n;

    for (int i = 0; i <n ; ++i) {
        cin>>temp;
        if(temp==1){
            cin>>temp;
            temp=currentXor==-1?temp:temp^currentXor;
            mybit=temp;
            trie->insert(mybit.to_string());
        } else if(temp==2){
            cin>>temp;
            currentXor=currentXor==-1?temp:currentXor^temp;
        } else if(temp==3){
            mybit=currentXor;
            int whattodo=currentXor==-1?1:0;
            trie->findmaxsubjecttoxor(mybit.to_string(),answer,0,whattodo);
            bitset<30> finals(answer);
            cout<<finals.to_ulong()<<endl;
        }
    }


}

