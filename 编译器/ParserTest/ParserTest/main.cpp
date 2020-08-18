#include <iostream>
#include <sstream>

using namespace std;

string token[1000];
string ter[1000];
int n = 0;
int p = 0;
bool x = true;

void scanner();
void parser();
void stmts();
void stmt();
void primary();
void primary_tail();

int main()
{
    scanner();
    parser();
    return 0;
}

void scanner(){
    string str;
    bool id = false;
    while(cin >> str){
        int l = str.length();
        for(int i = 0 ;i < l;i++){
            if(str[i] == '.'){
                id = false;
                token[n+i] = "DOT";
                ter[n+i] = str[i];
            }
            else if(str[i] == '('){
                id = false;
                token[n+i] = "LBR";
                ter[n+i] = str[i];
            }
            else if(str[i] == ')'){
                id = false;
                token[n+i] = "RBR";
                ter[n+i] = str[i];
            }
            else if(str[i] == '"'){
                id = false;
                token[n+i] = "STRLIT";
                ter[n+i] = str[i];
                i++;
                while(i<l){
                    n--;
                    ter[n+i] += str[i];
                    if(str[i] == '"'){
                        break;
                    }
                    i++;
                    if(i == l){
                        x = false;
                    }
                }
            }
            else{   //ID
                if(id){
                    if(!(str[i]=='_' || (str[i]>='A'&&str[i]<='Z') || (str[i]>='a'&&str[i]<='z') || (str[i]>='0'&&str[i]<='9'))){
                        x = false;
                    }
                    n--;
                    ter[n+i] += str[i];
                }
                else{
                    if(!(str[i]=='_' || (str[i]>='A'&&str[i]<='Z') || (str[i]>='a'&&str[i]<='z'))){
                        x = false;
                    }
                    token[n+i] = "ID";
                    ter[n+i] = str[i];
                }
                id = true;
            }
        }
        n += l;
    }
}

void parser(){
    stmts();
    if(x){
        for(int i = 0;i < n;i++){
            cout << token[i] << " " << ter[i] << "\n";
        }
    }
    else{
        cout << "invalid input";
    }
}

void stmts(){//->stmt stmts|e
    if(token[p] == "ID" || token[p] == "STRLIT"){
        stmt();
        stmts();
    }
    else{

    }
}

void stmt(){//->primary|STRLIT|e
    if(token[p] == "ID"){
        primary();
    }
    else if(token[p] == "STRLIT"){
        p++;
    }
    else{

    }
}

void primary(){//ID primary_tail
    if(token[p] == "ID"){
        p++;
        primary_tail();
    }
    else{
        x = false;
    }
}
void primary_tail(){//DOT ID primary_tail|LBR stmt RBR primary_tail|e
    if(token[p] == "DOT"){
        p++;
        if(token[p] == "ID"){
            p++;
            primary_tail();
        }
        else{
            x = false;
        }
    }
    else if(token[p] == "LBR"){
        p++;
        stmt();
        if(token[p] == "RBR"){
            p++;
            primary_tail();
        }
        else{
            x = false;
        }
    }
    else{

    }
}
