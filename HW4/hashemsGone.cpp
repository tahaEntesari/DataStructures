#include <iostream>
#include <cmath>
using namespace std;
struct node{
    int value;
    node **next;
    node **prev;
    node(int key,int maxheight){
        this->value=key;
        next=new node*[maxheight];
        prev=new node*[maxheight];
        for (int i = 0; i <maxheight ; ++i) {
            next[i]= nullptr;
            prev[i]= nullptr;
        }
    }
};
class skiplist {
public:
    int maxheight;
    node* firstguard;
    node* lastguard;
    skiplist(int maxheight){
        this->maxheight=maxheight;
        this->firstguard=new node(-1000000007,this->maxheight);
        this->lastguard=new node(1000000007,this->maxheight);
        for (int i = 0; i <maxheight ; ++i) {
            this->firstguard->next[i]=this->lastguard;
            this->lastguard->prev[i]=this->firstguard;
        }
    }
    void insert(int value,int numberoflevels){
        int count=numberoflevels-1;
        node* current=this->firstguard;
        node* newnode=new node(value,this->maxheight);
        while(count>=0){
            while(value>current->value) current=current->next[count];
            newnode->next[count]=current;
            newnode->prev[count]=current->prev[count];
            current->prev[count]=newnode;
            newnode->prev[count]->next[count]=newnode;
            current=newnode->prev[count];
            count--;
        }
    }
    //might wanna delete the node after pointers are done
    void remove(int value,int currentmaxheight){
        //first let's find the node
        node *current=findexistingnode(value,currentmaxheight);
        for (int i = 0; i <currentmaxheight ; ++i) {
            if(current->next[i]== nullptr) break;
            current->next[i]->prev[i]=current->prev[i];
            current->prev[i]->next[i]=current->next[i];
        }
    }

    node* findexistingnode(int value, int currentmaxheight){
        int count=currentmaxheight-1;
        node *current=this->firstguard;
        while(count>>0 && current->next[count]==this->lastguard) count--;
        bool condition;
        while(true){

            condition=current->value<value;
            if(condition){
                here:
                if(current->next[count]->value<=value) current=current->next[count];
                else {
                    count--;
                    goto here;
                }
            }
            if(current->value==value) break;
        }

        return current;
    }

    //check validity
    // check the case when the given node to search for is smaller than everyone
    int findnode(int value, int currentmaxheight){
        int length=0;
        node* current=this->firstguard;
        int count=currentmaxheight-1;
        bool condition;
        while(count>=0&&current->next[count]==this->lastguard) count--;
        if (count==-1) return -1;
        while (true){
            if(count<0) return -1;
            condition=current->value<value;
            if(condition){
                if(current->next[count]->value<=value){
                    current=current->next[count];
                    length++;
                }else{
                    count--;
                    length++;
                }
            } else if (current->value==value && count!=0) {
                count--;
                length++;
            }
            if(current->value==value && count==0) return length;
            if(count==0 && current->value<value && current->next[0]->value>value) return -1;
        }
    }
    void print(int maxcurrentheight){
        int count=maxcurrentheight-1;
        node* current;
        while(this->firstguard->next[count]==this->lastguard) count--;
        while(count>=0){
            current=this->firstguard->next[count];
            while(current!=this->lastguard){
                cout<<'\t'<<current->value<<" ";
                current=current->next[count];
            }
            cout<<'\n';
            count--;
        }

    }

};

int main(){
    /*
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
     */
    int q;
    cin>>q;
    int maxheightofinput=1;
    int maxpossibleheight=floor(2*log(q));
    auto jumplist=new skiplist(maxpossibleheight);
    int x,k;
    for (int i = 0; i <q ; ++i) {
        cin>>x;
        switch(x){
            case 1:
                cin>>x;
                jumplist->remove(x,maxheightofinput);
                break;
            case 2:
                cin>>x>>k;
                maxheightofinput=maxheightofinput>k?maxheightofinput:k;
                //if(maxheightofinput>maxpossibleheight) while(true);
                jumplist->insert(x,k);

                break;
            case 3:
                cin>>x;
                cout<<jumplist->findnode(x,maxheightofinput)<<"\n";
                break;
        }
        //jumplist->print(maxheightofinput);

    }
    cout<<endl;
}