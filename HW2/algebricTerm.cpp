#include <iostream>
#include <string>

using namespace std;

/* In the operator stack:
 * 1:+
 * 2:-
 * 3:*
 * 4:(
 */

int modd=1000000007;

void makeStacks(string s,int numberStack[], int operatorStack[], int *numbercount, int *operatorstackcount){
    long long int temp1,temp2;
    int currentoperator,secondoperator;
    *numbercount=0;
    *operatorstackcount=0;
    int i=0;
    int numberfirstindex,numbersecondindex;
    while (i<s.length()) {
        numberfirstindex=-1;
        while (isdigit(s[i]) && i<s.length()){
            if(numberfirstindex==-1) numberfirstindex=i;
            numbersecondindex=i;
            i++;
        }
        if(numberfirstindex!=-1) {
            numbersecondindex = numbersecondindex - numberfirstindex + 1;
            numberStack[*numbercount] = stoi(s.substr(numberfirstindex, numbersecondindex));
            //cout<<numberStack[*numbercount]<<endl;
            (*numbercount)++;
        }
        if(!isdigit(s[i]) && i<s.length()){
            if(s[i]=='+') {
                operatorStack[*operatorstackcount]=1;
                (*operatorstackcount)++;
            }
            else if(s[i]=='-') {
                operatorStack[*operatorstackcount]=2;
                (*operatorstackcount)++;
            }
            else if(s[i]=='*') {
                operatorStack[*operatorstackcount]=3;
                (*operatorstackcount)++;
            }
            else if(s[i]=='(') {
                operatorStack[*operatorstackcount]=4;
                (*operatorstackcount)++;
            }

            else if(s[i]==')') {
                if(operatorStack[*operatorstackcount-1]==4) goto label;
                while(operatorStack[*operatorstackcount-1]!=4) {
                    temp1 = numberStack[*numbercount - 1];
                    temp2 = numberStack[*numbercount - 2];
                    currentoperator = operatorStack[*operatorstackcount - 1];
                    secondoperator= operatorStack[*operatorstackcount - 2];


                    if(secondoperator==1) {
                        label2:
                        (*numbercount) -= 2;
                        (*operatorstackcount) -= 1;
                        if (currentoperator == 1) temp1 = (temp1 + temp2) % modd;
                        else if (currentoperator == 2) temp1 = (temp2 - temp1) % modd;
                        else if (currentoperator == 3) temp1 = (temp1 * temp2) % modd;
                        //cout << temp1 << endl;
                        numberStack[*numbercount] = (int) temp1;
                        (*numbercount)++;
                    } else if (secondoperator==2) {
                        temp2=-temp2;
                        operatorStack[*operatorstackcount-2]=1;
                        (*numbercount) -= 2;
                        (*operatorstackcount) -= 1;
                        if (currentoperator == 1) temp1 = (temp1 + temp2) % modd;
                        else if (currentoperator == 2) temp1 = (temp2 - temp1) % modd;
                        else if (currentoperator == 3) temp1 = (temp1 * temp2) % modd;
                        //cout << temp1 << endl;
                        numberStack[*numbercount] = (int) temp1;
                        (*numbercount)++;
                    } else if(secondoperator==3){
                        temp1=numberStack[*numbercount-3];
                        temp1=(temp1*temp2)%modd;
                        numberStack[*numbercount-3]=(int)temp1;
                        numberStack[*numbercount-2]=numberStack[*numbercount-1];
                        operatorStack[*operatorstackcount-2]=operatorStack[*operatorstackcount-1];
                        (*numbercount)--;
                        (*operatorstackcount)--;
                    } else goto label2;




                    /*
                    *numbercount -= 2;
                    (*operatorstackcount)--;
                    if (currentoperator == 1) temp1 = (temp1 + temp2) % modd;
                    else if (currentoperator == 2) temp1 = (temp2 - temp1) % modd;
                    else if (currentoperator == 3) temp1 = (temp1 * temp2) % modd;
                    numberStack[*numbercount] = (int)temp1;
                    (*numbercount)++;
                     */
                }
                label:
                (*operatorstackcount)--;
            }
            i++;
            //cout<<operatorStack[*operatorstackcount-1]<<endl;
        }
    }
}
int main() {
    string s;
    cin>>s;
    string temp;
    int n=s.length();
    int operatorstack[n], numberstack[n];
    int *numbercount=new int;
    int *operatorstackcount=new int;
    makeStacks(s,numberstack,operatorstack,numbercount,operatorstackcount);
    long long int temp1,temp2;
    int currentoperator,secondoperator;
    /*
    for (int i = 0; i <*numbercount ; ++i) {
        cout<<numberstack[i]<<" ";
    }
    cout<<endl;
    for (int i = 0; i <*operatorstackcount ; ++i) {
        cout<<operatorstack[i]<<" ";
    }
    cout<<endl;
    //cout<<numberstack[*numbercount-2]<<endl;

     */
    while(*numbercount!=1){
        temp1=numberstack[*numbercount-1];
        temp2=numberstack[*numbercount-2];
        //cout<<*numbercount<<" "<<temp1<<" "<<temp2<<" ";
        currentoperator=operatorstack[*operatorstackcount-1];
        secondoperator=operatorstack[*operatorstackcount-2];
        if(secondoperator==1) {
            label2:
            (*numbercount) -= 2;
            (*operatorstackcount) -= 1;
            if (currentoperator == 1) temp1 = (temp1 + temp2) % modd;
            else if (currentoperator == 2) temp1 = (temp2 - temp1) % modd;
            else if (currentoperator == 3) temp1 = (temp1 * temp2) % modd;
            //cout << temp1 << endl;
            numberstack[*numbercount] = (int) temp1;
            (*numbercount)++;
        } else if (secondoperator==2) {
            temp2=-temp2;
            operatorstack[*operatorstackcount-2]=1;
            (*numbercount) -= 2;
            (*operatorstackcount) -= 1;
            if (currentoperator == 1) temp1 = (temp1 + temp2) % modd;
            else if (currentoperator == 2) temp1 = (temp2 - temp1) % modd;
            else if (currentoperator == 3) temp1 = (temp1 * temp2) % modd;
            //cout << temp1 << endl;
            numberstack[*numbercount] = (int) temp1;
            (*numbercount)++;
        } else if(secondoperator==3){
            temp1=numberstack[*numbercount-3];
            temp1=(temp1*temp2)%modd;
            numberstack[*numbercount-3]=(int)temp1;
            numberstack[*numbercount-2]=numberstack[*numbercount-1];
            operatorstack[*operatorstackcount-2]=operatorstack[*operatorstackcount-1];
            (*numbercount)--;
            (*operatorstackcount)--;
        } else goto label2;

    }
    int result=numberstack[*numbercount-1]%modd;
    result=result<0?result+modd:result;
    cout<<result;


}