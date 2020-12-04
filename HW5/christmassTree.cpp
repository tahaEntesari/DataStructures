#include <iostream>
using namespace std;
class treenode{
public:
    treenode* parent;
    treenode* left;
    treenode* right;
    int value;
    treenode(treenode* parent, treenode* left, treenode* right, int value){
        this->value=value;
        this->left=left;
        this->right=right;
        this->parent=parent;
    }
};
void splay(treenode* tosplay, int* zigzignumber, int* zigzagnumber){ // Consider the case when there is no parent present. **
    if(tosplay->parent!= nullptr) {
        int leftorright = 1; // 0 means left child. 1 means right.
        auto p=tosplay->parent;
        if (p->left != nullptr && p->left == tosplay) leftorright = 0;
        if (p->parent == nullptr) { //Zig
            if (leftorright == 0) {
                auto temp = tosplay->right;
                tosplay->right = p;
                p->parent = tosplay;
                tosplay->parent = nullptr;
                p->left = temp;
                if(p->left!= nullptr) p->left->parent=p;
            } else {
                auto temp = tosplay->left;
                tosplay->left = p;
                p->parent = tosplay;
                tosplay->parent = nullptr;
                p->right = temp;
                if(p->right!= nullptr) p->right->parent=p;
            }
        } else {
            int parentleftorright = 1; // 0 means that the parent is the left child of its parent.
            auto p = tosplay->parent;
            auto pp = p->parent;
            if (pp->left!= nullptr && pp->left == p) parentleftorright = 0;
            if (leftorright == parentleftorright) { //Zig-Zig
                (*zigzignumber)++;
                if (parentleftorright == 0) { // A left branch
                    //auto A=tosplay->left; // not necessary. stays the same.
                    auto B = tosplay->right;
                    auto C = p->right;
                    //auto D=pp->right; // not necessary. stays the same.
                    if (pp->parent != nullptr) {
                        if (pp->parent->left != nullptr && pp->parent->left == pp) {
                            pp->parent->left = tosplay;
                        } else {
                            pp->parent->right = tosplay;
                        }
                        tosplay->parent = pp->parent;
                        tosplay->right = p;
                        p->parent = tosplay;
                        p->right = pp;
                        pp->parent = p;
                        p->left = B;
                        if(B!= nullptr) B->parent = p;
                        pp->left = C;
                        if(C!= nullptr) C->parent = pp;
                    } else {
                        tosplay->parent = nullptr;
                        tosplay->right = p;
                        p->parent = tosplay;
                        p->right = pp;
                        pp->parent = p;
                        p->left = B;
                        if(B!=nullptr) B->parent = p;
                        pp->left = C;
                        if(C!=nullptr) C->parent = pp;
                    }
                } else { // A right branch
                    auto B = p->left;
                    auto C = tosplay->left;
                    if (pp->parent != nullptr) {
                        if (pp->parent->left != nullptr && pp->parent->left == pp) {
                            pp->parent->left = tosplay;
                        } else {
                            pp->parent->right = tosplay;
                        }
                        tosplay->parent = pp->parent;
                        tosplay->left = p;
                        p->parent = tosplay;
                        p->left = pp;
                        pp->parent = p;
                        p->right = C;
                        if(C!= nullptr) C->parent = p;
                        pp->right = B;
                        if(B!=nullptr) B->parent = pp;
                    } else {
                        tosplay->parent = nullptr;
                        tosplay->left = p;
                        p->parent = tosplay;
                        p->left = pp;
                        pp->parent = p;
                        p->right = C;
                        if(C!= nullptr) C->parent = p;
                        pp->right = B;
                        if(B!=nullptr) B->parent = pp;
                    }
                }
            } else { // Zig-Zag
                (*zigzagnumber)++;
                if (parentleftorright == 0) { //A left branch
                    auto B = tosplay->right;
                    auto A = tosplay->left;
                    if (pp->parent != nullptr) {
                        if (pp->parent->left != nullptr && pp->parent->left == pp) {
                            pp->parent->left = tosplay;
                        } else {
                            pp->parent->right = tosplay;
                        }
                        tosplay->parent = pp->parent;
                        tosplay->right = pp;
                        pp->parent = tosplay;
                        pp->left = B;
                        if(B!=nullptr) B->parent = pp;
                        tosplay->left = p;
                        p->parent = tosplay;
                        p->right = A;
                        if(A!=nullptr) A->parent = p;
                    } else {
                        tosplay->parent = nullptr;
                        tosplay->right = pp;
                        pp->parent = tosplay;
                        pp->left = B;
                        if(B!=nullptr) B->parent = pp;
                        tosplay->left = p;
                        p->parent = tosplay;
                        p->right = A;
                        if(A!=nullptr) A->parent = p;
                    }
                } else {
                    auto C = tosplay->left;
                    auto D = tosplay->right;
                    if (pp->parent != nullptr) {
                        if (pp->parent->left != nullptr && pp->parent->left == pp) {
                            pp->parent->left = tosplay;
                        } else {
                            pp->parent->right = tosplay;
                        }
                        tosplay->parent = pp->parent;
                        tosplay->right = p;
                        p->parent = tosplay;
                        tosplay->left = pp;
                        pp->parent = tosplay;
                        p->left = D;
                        if(D!=nullptr) D->parent = p;
                        pp->right = C;
                        if(C!=nullptr) C->parent = pp;
                    } else {
                        tosplay->parent = pp->parent;
                        tosplay->right = p;
                        p->parent = tosplay;
                        tosplay->left = pp;
                        pp->parent = tosplay;
                        p->left = D;
                        if(D!=nullptr) D->parent = p;
                        pp->right = C;
                        if(C!=nullptr) C->parent = pp;
                    }
                }
            }
            splay(tosplay,zigzignumber,zigzagnumber);
        }
    } else { //tosplay has no parent. Thus no splay is needed.
        return;
    }
}
// Currently only searches for the member but does not splay.
// If the element is not in the tree, it will return the element that the search has ended on.
treenode* search(treenode* root, int valuetosearch){
    if(root->value==valuetosearch) return root;
    else if(valuetosearch < root->value){
        if(root->left!= nullptr) return search(root->left,valuetosearch);
        return root;
    } else {
        if(root->right != nullptr) return search(root->right,valuetosearch);
        return root;
    }
}
treenode* maxelement(treenode* root){
    auto current=root;
    while(current->right!=nullptr) current=current->right;
    return current;
}
void printtree(treenode* root){

}
int main() {
    treenode* root;
    treenode* searchresult;
    treenode* tempnode;
    int m;
    cin>>m;
    int temp,x,numberOfNodes;
    numberOfNodes=0;
    int *zigzagnumber = new int;
    int *zigzignumber = new int;
    for (int i = 0; i <m ; ++i) {
        cin>>temp;
        *zigzagnumber=0;
        *zigzignumber=0;
        switch (temp){
            case 1: // Insert
                cin>>x;
                if(numberOfNodes==0) root=new treenode(nullptr,nullptr,nullptr,x);
                else{
                    searchresult=search(root,x);
                    splay(searchresult,zigzignumber,zigzagnumber);
                    if(x>searchresult->value){
                        searchresult->parent=new treenode(nullptr,searchresult,searchresult->right,x);
                        if(searchresult->right!= nullptr) {
                            searchresult->right->parent = searchresult->parent;
                            searchresult->right = nullptr;
                        }
                    } else {
                        searchresult->parent=new treenode(nullptr,searchresult->left,searchresult,x);
                        if(searchresult->left!= nullptr) {
                            searchresult->left->parent = searchresult->parent;
                            searchresult->left = nullptr;
                        }
                    }
                    root=searchresult->parent;
                }
                numberOfNodes++;
                break;
            case 2: // Delete
                cin>>x;
                searchresult=search(root,x);
                splay(searchresult,zigzignumber,zigzagnumber);
                if(searchresult->left!= nullptr) {
                    tempnode = maxelement(searchresult->left);
                    searchresult->left->parent= nullptr;
                    searchresult->left = nullptr;
                    splay(tempnode, zigzignumber, zigzagnumber);
                    tempnode->right = searchresult->right;
                    if(tempnode->right!= nullptr) tempnode->right->parent = tempnode;
                    root = tempnode;
                    root->parent= nullptr;
                } else {
                    root=searchresult->right;
                    if(root!= nullptr){
                        root->parent= nullptr;
                    }
                }
                numberOfNodes--;
                break;
            case 3: //Find
                cin>>x;
                searchresult=search(root,x);
                splay(searchresult,zigzignumber,zigzagnumber);
                root=searchresult;
                break;
        }
        cout<<*zigzignumber<<" "<<*zigzagnumber<<"\n";
    }
    cout<<endl;
}