#include <iostream>

using namespace std;

int main()
{
    string str;
    string token[1000];
    bool num = false;
    int n = 0;
    while(cin >> str){
        int l = str.length();
        for(int i = 0 ;i < l;i++){
            if(str[i] == '+'){
                num = false;
                token[n+i] = "PLUS";
            }
            else if(str[i] == '-'){
                num = false;
                token[n+i] = "MINUS";
            }
            else if(str[i] == '*'){
                num = false;
                token[n+i] = "MUL";
            }
            else if(str[i] == '/'){
                num = false;
                token[n+i] = "DIV";
            }
            else if(str[i] == '('){
                num = false;
                token[n+i] = "LPR";
            }
            else if(str[i] == ')'){
                num = false;
                token[n+i] = "RPR";
            }
            else{
                string s;
                s = str[i];
                if(num){
                    n--;
                    token[n+i] += str[i];
                }
                else{
                    token[n+i] = "NUM " + s;
                }
                num = true;
            }
        }
        n += l;
    }
    for(int i = 0;i < n;i++){
        cout << token[i] << "\n";
    }
    return 0;
}
