
#include <iostream>
using namespace std;

void letsprintthistree(int *MaxLeftChild, int * MaxRighthChild, int* MinRightChild, int* ResultVector, int currentlyconsidering,
                       int *secondcosidering, int originaltreelength,int* counterforResultVector, int maxdata,bool *impossible){
    bool answer=false;
    while((*secondcosidering)<MaxLeftChild[currentlyconsidering]){
        (*secondcosidering)++;
        letsprintthistree(MaxLeftChild,  MaxRighthChild,  MinRightChild,  ResultVector,  *secondcosidering,
                          secondcosidering, originaltreelength, counterforResultVector, 1, impossible);
    }

    ResultVector[*counterforResultVector]=currentlyconsidering;
    (*counterforResultVector)++;
    if((*secondcosidering)>=MinRightChild[currentlyconsidering]) *impossible=true;
    while(MaxRighthChild[currentlyconsidering]>*secondcosidering){
        (*secondcosidering)++;
        letsprintthistree(MaxLeftChild,  MaxRighthChild,  MinRightChild,  ResultVector,  *secondcosidering,
                          secondcosidering, originaltreelength, counterforResultVector, 1,impossible);
    }
    /*
    if(maxdata==0 && *secondcosidering<originaltreelength-1){
        (*secondcosidering)++;
        answer=letsprintthistree(MaxLeftChild,  MaxRighthChild,  MinRightChild,  ResultVector,  *secondcosidering,
                                 secondcosidering, originaltreelength, counterforResultVector, 0);
    }
    */
}
void letsprintitasecondtime(int MaxLeftChild[], int  MaxRighthChild[], int MinRightChild[], int ResultVector[], int currentlyconsidering,
                            int *secondcosidering, int originaltreelength,int* counterforResultVector, int maxdata,bool *impossible){

    while((*secondcosidering)<MaxLeftChild[currentlyconsidering]){
        (*secondcosidering)++;
        letsprintitasecondtime(MaxLeftChild,  MaxRighthChild,  MinRightChild,  ResultVector,  *secondcosidering,
                          secondcosidering, originaltreelength, counterforResultVector, 1, impossible);
    }

    ResultVector[*counterforResultVector]=currentlyconsidering;
    (*counterforResultVector)++;
    if((*secondcosidering)>=MinRightChild[currentlyconsidering]) *impossible=true;
    while(MaxRighthChild[currentlyconsidering]>*secondcosidering){
        (*secondcosidering)++;
        letsprintitasecondtime(MaxLeftChild,  MaxRighthChild,  MinRightChild,  ResultVector,  *secondcosidering,
                          secondcosidering, originaltreelength, counterforResultVector, 1,impossible);
    }
    if(maxdata==0   ){
        while( *secondcosidering<originaltreelength-1 && !*impossible )  {
            (*secondcosidering)++;
            letsprintitasecondtime(MaxLeftChild, MaxRighthChild, MinRightChild, ResultVector, *secondcosidering,
                                   secondcosidering, originaltreelength, counterforResultVector, 0, impossible);
        }
    }
}

int main(){
    int n,c;
    cin>>n>>c;
    bool *impossible=new bool;
    *impossible=false;
    int MaxLeftChild[n],MaxRightChild[n],MinRightChild[n],ResultVector[n];
    for (int j = 0; j <n ; ++j) {
        MinRightChild[j] = n;
        MaxLeftChild[j]=-1;
        MaxRightChild[j]=-1;
        ResultVector[j]=-1;
    }
    string s;
    int temp1,temp2;
    for (int i = 0; i <c ; ++i) {
        cin>>temp1>>temp2>>s;
        temp1--;
        temp2--;
        if(temp2<=temp1) *impossible=true;
        if(s=="RIGHT"){

            MaxRightChild[temp1]=MaxRightChild[temp1]>temp2?MaxRightChild[temp1]:temp2;
            MinRightChild[temp1]=MinRightChild[temp1]>temp2?temp2:MinRightChild[temp1];
        } else {
            MaxLeftChild[temp1]=MaxLeftChild[temp1]<temp2?temp2:MaxLeftChild[temp1];
        }
    }
    int *resultcounter,*printcounter;
    resultcounter=new int;
    printcounter=new int;
    *resultcounter=0;
    *printcounter=0;
    if(!*impossible){
        letsprintitasecondtime(MaxLeftChild,MaxRightChild,MinRightChild,
                               ResultVector,0,printcounter,n,resultcounter,0,impossible);
        /*
        while(!*impossible){
            if(*printcounter<n-1){
                (*printcounter)++;
                letsprintitasecondtime(MaxLeftChild,MaxRightChild,MinRightChild,
                                       ResultVector,*printcounter,printcounter,n,resultcounter,0,impossible);
            } else break;
        }
         */
        if(*impossible) cout<<"IMPOSSIBLE";
        else
            for (int i = 0; i <n ; ++i) {
                cout<<ResultVector[i]+1<<" ";
            }
    } else {
        cout<<"IMPOSSIBLE";
    }
}

/*
int main() {
    int n,c;
    cin>>n>>c;
    bool *impossible=new bool;
    *impossible=false;
    int *MaxLeftChild=new int[n];
    int *MaxRightChild=new int[n];
    int *MinRightChild=new int[n];
    int *ResultVector=new int[n];
    for (int j = 0; j <n ; ++j) {
        MinRightChild[j] = n;
        MaxLeftChild[j]=-1;
        MaxRightChild[j]=-1;
        ResultVector[j]=-1;
    }
    string s;
    int temp1,temp2;
    for (int i = 0; i <c ; ++i) {
        cin>>temp1>>temp2>>s;
        temp1--;
        temp2--;
        if(s=="RIGHT"){
            if(temp2<=temp1) *impossible=true;
            MaxRightChild[temp1]=MaxRightChild[temp1]>temp2?MaxRightChild[temp1]:temp2;
            MinRightChild[temp1]=MinRightChild[temp1]>temp2?temp2:MinRightChild[temp1];
        } else {
            MaxLeftChild[temp1]=MaxLeftChild[temp1]<temp2?temp2:MaxLeftChild[temp1];
        }
    }

    if(*impossible) goto impp;
    int *printednumbers,*counterforResultVector;
    printednumbers=new int();
    counterforResultVector= new int();
    *printednumbers=*counterforResultVector=0;
    letsprintthistree(MaxLeftChild,  MaxRightChild,  MinRightChild,  ResultVector,  0,
                                  printednumbers, n, counterforResultVector, 0,impossible);
    impp:
    if(*impossible){
        cout<<"IMPOSSIBLE";
        return 0;
    }
    while(!*impossible) {
        if (*printednumbers < n - 1) {
            (*printednumbers)++;
             letsprintthistree(MaxLeftChild, MaxRightChild, MinRightChild, ResultVector, *printednumbers,
                                            printednumbers, n, counterforResultVector, 0,impossible);
            if(*impossible) goto impp;
        } else break;
    }
    if(*impossible) goto impp;
    for (int k = 0; k <n ; ++k) {
        cout<<ResultVector[k]+1<<" ";
    }
}
*/