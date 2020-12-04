#include <iostream>
#include <string>

using namespace std;
#define CHAR_SIZE 26
class relationGraph{
public:
    int **relations;
    relationGraph(){
        relations=new int*[26];
        for (int i = 0; i <26 ; ++i) this->relations[i]=new int[26];
    }
    ~relationGraph(){
        for (int i = 0; i <26 ; ++i) {
            free(this->relations[i]);
        }
        free(this->relations);
    }
    void insertToRelations(int i, int j){// a directed edge from i to j
        this->relations[i][j]=1;
    }
    int ** returnrelationsmatrix(){
        return this->relations;
    }
    void copyfrommatrix(int **matrix){
        for (int i = 0; i <26 ; ++i) {
            for (int j = 0; j <26 ; ++j) {
                this->relations[i][j]=matrix[i][j];
            }
        }
    }
    bool hascycle(){
        int didthematrixchange=0;
        for (int i = 0; i <26 ; ++i) {
            for (int j = 0; j <26 ; ++j) {
                for (int k = 0; k <26 ; ++k) {
                    if(this->relations[i][j]==1 && this->relations[j][k]==1 && this->relations[i][k]==0){
                        this->relations[i][k]=1;
                        if(i==k) return true;
                        didthematrixchange=1;
                    }
                }
            }
        }
        if(didthematrixchange==1) return this->hascycle();
        for (int l = 0; l <26 ; ++l) {
            if(this->relations[l][l]==1) return true;
        }
        return  false;
    }

};

// A Class representing a Trie node
class Trie
{
public:
    bool isLeaf;
    Trie* character[CHAR_SIZE];

    // Constructor
    Trie(){
        this->isLeaf = false;
        for (int i = 0; i < CHAR_SIZE; i++)
            this->character[i] = nullptr;
    }
    void insert(string key){
        // start from root node
        Trie* curr = this;
        for (char i : key){
            // create a new node if path doesn't exists
            if (curr->character[i-97] == nullptr)
                curr->character[i-97] = new Trie();
            // go to next node
            curr = curr->character[i-97];
        }
        // mark current node as leaf
        curr->isLeaf = true;
    }
    void insertfromcharstar(char* string){
        Trie* curr=this;
        for (int i = 0; string[i]!='\0' ; ++i) {
            if (curr->character[string[i]-97] == nullptr)
                curr->character[string[i]-97] = new Trie();
            // go to next node
            curr = curr->character[string[i]-97];
        }
        // mark current node as leaf
        curr->isLeaf = true;
    }
    void print(){
        Trie* curr=this;
        for (int i = 0; i <26 ; ++i) {
            if(curr->character[i]!= nullptr){
                cout<<char(i+97);
            }
        }
    }

};
int* findSiblingsInAGivenLevel(Trie* trie){
    int *siblings=new int[CHAR_SIZE];
    int count=0;
    for (int i = 0; i <CHAR_SIZE ; ++i) {
        if(trie->character[i]!=nullptr) {
            siblings[i]=1;
            count++;
        }
    }
    return siblings;
}
void letsdothis(Trie *trie, relationGraph* originalgraph, int maxstringlenth, int* currentword,int currentwordcount){
    relationGraph *copiedgraph=new relationGraph;
    int *copiedcurrentword=new int[maxstringlenth];
    int *currentlevelsiblings=findSiblingsInAGivenLevel(trie);
    for (int k = 0; k <currentwordcount ; ++k) {
        copiedcurrentword[k]=currentword[k];
    }
    if(trie->isLeaf){

    }

    if(!trie->isLeaf) {
        for (int i = 0; i < 26; ++i) {
            if (trie->character[i] == nullptr) continue;
            copiedgraph->copyfrommatrix(originalgraph->returnrelationsmatrix());
            for (int j = 0; j < 26; ++j) {
                if (j == i) continue;
                if (currentlevelsiblings[j] == 1) copiedgraph->insertToRelations(i, j);
            }
            currentword[currentwordcount] = i;
            letsdothis(trie->character[i], copiedgraph, maxstringlenth, currentword, currentwordcount + 1);
        }
        delete(copiedgraph);
    } else{
        if(!copiedgraph->hascycle()){
            for (int i = 0; i <currentwordcount ; ++i) {
                cout<<char(copiedcurrentword[i]+97);
            }
            cout<<"\n";
        }
        delete(copiedgraph);
    }
}
void letsdothisasecondtime(Trie* trie, relationGraph* originalgraph, int prevflag, Trie *currentrelations, string currentword, string  answerstrings[],int *numberofsuchwords){
    auto *copiedgraph=new relationGraph();
    copiedgraph->copyfrommatrix(originalgraph->returnrelationsmatrix());
    if(prevflag!=27){
        for (int i = 0; i <26 ; ++i) {
            if(i==prevflag) continue;
            if(currentrelations->character[i]!=nullptr) copiedgraph->insertToRelations(prevflag,i);
        }
        currentword+=(char(prevflag+97));
    }
    if(!trie->isLeaf){
        for (int i = 0; i <26 ; ++i) {
            if(trie->character[i]!= nullptr){
                letsdothisasecondtime(trie->character[i],copiedgraph,i,trie,currentword,answerstrings,numberofsuchwords);
            }
        }
    } else{
        if(!copiedgraph->hascycle()){
            answerstrings[*numberofsuchwords]=currentword;
            //answertrie->insert(currentword);
            (*numberofsuchwords)++;
        }
    }
    delete(copiedgraph);
}


void letsdothisathirdtime(Trie* trie, relationGraph* originalgraph,int maxstringlength, int prevflag, Trie *currentrelations, char* currentword,int currentstringlenth, string  answerstrings[],int *numberofsuchwords){
    auto *copiedgraph=new relationGraph();
    copiedgraph->copyfrommatrix(originalgraph->returnrelationsmatrix());
    char *copiedcurrentword=new char[maxstringlength];
    for (int j = 0; j <currentstringlenth ; ++j) {
        copiedcurrentword[j]=currentword[j];
    }
    if(prevflag!=27){
        for (int i = 0; i <26 ; ++i) {
            if(i==prevflag) continue;
            if(currentrelations->character[i]!=nullptr) copiedgraph->insertToRelations(prevflag,i);
        }
        copiedcurrentword[currentstringlenth]=char(prevflag+97);
        currentstringlenth++;
    }
    if(!trie->isLeaf){
        for (int i = 0; i <26 ; ++i) {
            if(trie->character[i]!= nullptr){
                letsdothisathirdtime(trie->character[i],copiedgraph,maxstringlength,i,trie,copiedcurrentword,currentstringlenth,answerstrings,numberofsuchwords);
            }
        }
    } else{
        if(!copiedgraph->hascycle()){
            answerstrings[*numberofsuchwords]=string(copiedcurrentword);
            (*numberofsuchwords)++;
        }
    }
    delete(copiedgraph);
    delete[](copiedcurrentword);
}


// C++ implementation of Trie Data Structure
int main(){

    Trie* trie=new Trie();
    //auto answertrie= new Trie();
    int m;
    cin>>m;
    string answerstrings[m];
    string currentword;

    int maxstringlength=0;
    int *numberofsuchwords=new int;
    *numberofsuchwords=0;
    char* helpmeee=new char[100000];
    for (int j = 0; j <m ; ++j) {
        cin>>helpmeee;
        trie->insertfromcharstar(helpmeee);
        /*
        string s;
        cin>>s;
        trie->insert(s);
        maxstringlength=s.length()>maxstringlength?s.length():maxstringlength;
         */
    }

    auto* initialemptymatrix=new relationGraph();
    letsdothisasecondtime(trie,initialemptymatrix,27,trie,"",answerstrings,numberofsuchwords);
    //char*dumdum=new char[maxstringlength];
    //letsdothisathirdtime(trie,initialemptymatrix,maxstringlength,27,trie,dumdum,0,answerstrings,numberofsuchwords);

    cout<<*numberofsuchwords<<"\n";
    for (int i = 0; i <*numberofsuchwords ; ++i) {
        cout<<answerstrings[i]<<"\n";
    }
    cout<<endl;


     /*
    int *currentword=new int[maxstringlength];
    letsdothis(trie,initialemptymatrix,maxstringlength,currentword,0);
     */

}