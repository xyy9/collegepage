#include <iostream>
#include<string>

using namespace std;

int first_set[26][30] = {0};
//[][0] = nonterminal,[][1] = $,[][2] = ;,[][3-28] = a-z
int num = 0;
string right_non[26];

//$-36
//;-59
//A-Z-65-90
//a-z-97-122

void updata();
void print_output();

int main()
{
    char non_t;
    string str;
    while(cin >> non_t >> str){
        if(str == "ND_OF_GRAMMAR"){
            break;
        }
        first_set[num][0] = non_t-'A';
        right_non[non_t-'A'] = str;
        num++;
    }
    bool t = true;
    while(t){
        t = false;
        for(int k = 0;k<num;k++){
            if(right_non[first_set[k][0]] != ""){
                t = true;
                break;
            }
        }
        updata();
    }
    print_output();
    return 0;
}

void updata(){
    for(int k = 0;k < num;k++){
        string str = right_non[first_set[k][0]];
        int pos = 0;
        for(int i = 0;i < str.length();i++){
            pos = str.find("|",i);
            if(pos != str.npos){
                if(str[i]>='a'&&str[i]<='z'){
                    first_set[k][str[i]-94] = 1;
                    str = str.substr(0,i) + str.substr(pos+1,str.length()-pos-1);
                }
                else if(str[i]=='$'){
                    first_set[k][1] = 1;
                    str = str.substr(0,i) + str.substr(pos+1,str.length()-pos-1);
                }
                else if(str[i]==';'){
                    first_set[k][2] = 1;
                    str = str.substr(0,i) + str.substr(pos+1,str.length()-pos-1);
                }
                else{
                    int n = 0;
                    for(;n<num;n++){
                        if(first_set[n][0] == str[i]-'A' && right_non[first_set[n][0]] == ""){
                            for(int m = 3;m<30;m++){
                                if(first_set[n][m] == 1){
                                    first_set[k][m] = 1;
                                }
                            }
                            if(first_set[n][2] == 1){
                                if(str.length() == 1){
                                    first_set[k][2] = 1;
                                }
                                str = str.substr(0,i) + str.substr(i+1,str.length()-1-i);
                            }
                            else if(first_set[n][1] == 1){
                                if(str.length() == 1){
                                    first_set[k][1] = 1;
                                }
                                str = str.substr(0,i) + str.substr(i+1,str.length()-1-i);
                            }
                            else{
                                str = str.substr(0,i) + str.substr(pos+1,str.length()-pos-1);
                            }
                            break;
                        }
                    }
                    if(n == num){
                        i += pos+1;
                    }
                }
                i--;
            }
            else{
                if(str[i]>='a'&&str[i]<='z'){
                    first_set[k][str[i]-94] = 1;
                }
                else if(str[i]=='$'){
                    first_set[k][1] = 1;
                }
                else if(str[i]==';'){
                    first_set[k][2] = 1;
                }
                else{
                    for(int n = 0;n<num;n++){
                        if(first_set[n][0] == str[i]-'A' && right_non[first_set[n][0]] == ""){
                            for(int m = 3;m<30;m++){
                                if(first_set[n][m] == 1){
                                    first_set[k][m] = 1;
                                }
                            }
                            if(first_set[n][2] == 1){
                                if(str.length() == 1){
                                    first_set[k][2] = 1;
                                }
                                str = str.substr(0,i) + str.substr(i+1,str.length()-i-1);
                            }
                            else if(first_set[n][1] == 1){
                                if(str.length() == 1){
                                    first_set[k][1] = 1;
                                }
                                str = str.substr(0,i) + str.substr(i+1,str.length()-i-1);
                            }
                            else{
                                str = "";
                            }
                            break;
                        }
                    }
                    break;
                }
                if(i-1>0){
                    str = str.substr(0,i-1);
                }
                else{
                    str = "";
                }
            }
        }
        right_non[first_set[k][0]] = str;
    }
}

void print_output(){
    for(int n = 0; n < 26; n++){
        for(int k = 0;k < num; k++){
            if(first_set[k][0] == n){
                cout << (char)(first_set[k][0]+'A') << " ";
                for(int m = 1;m<30;m++){
                    if(first_set[k][m] == 1){
                        if(m == 1){
                            cout << "$";
                        }
                        else if(m == 2){
                            cout << ";";
                        }
                        else{
                            cout << (char)(m+94);
                        }
                    }
                }
                cout <<endl;
            }
        }
    }
    cout << "END_OF_FIRST" <<endl;
}
