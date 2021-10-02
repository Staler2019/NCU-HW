#include <iostream>
#include <vector>
using namespace std;
string str,ans;
vector <pair<string,int> > tokenStr;
int cnt=0;
void error();
void dot();
void lbr();
void rbr();
void ID(int);
void strlit(int);
void primary_tail();
void primary();
void stmt();
void stmts();
int main()
{
    bool invaild=false;
    while(!cin.eof()){
        string tmp;
        cin>>tmp;
        str+=tmp+" ";
    }
    str+="$";
    for(unsigned int i=0;i<str.length()&&!invaild;i++){
        if((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z')||str[i]=='_'){
            tokenStr.push_back(make_pair("ID",i));
            for(;(str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z')||(str[i]>='0'&&str[i]<='9')||str[i]=='_';i++);
        }
        switch(str[i]){
        case '"':
            tokenStr.push_back(make_pair("STRLIT",i++));
            for(;str[i]!='"'&&str[i]!='$';i++);
            if(str[i]!='"'){
                error();
            }
            break;
            case '(':
                tokenStr.push_back(make_pair("LBR",0));
                break;
            case ')':
                tokenStr.push_back(make_pair("RBR",0));
                break;
            case '.':
                tokenStr.push_back(make_pair("DOT",0));
                break;
            case '$':
                tokenStr.push_back(make_pair("$",0));
                break;
            case ' ':
                break;
            default:
                error();
        }
    }
    /*for(int i=0;i<tokenStr.size();i++){
        cout<<tokenStr[i].first<<" ";
    }*/
    stmts();
    cout<<ans;





    /*for(unsigned int i=0;i<str.length()&&!invaild;i++){
        if((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z')||str[i]=='_'){
            id+=str[i];
        }else if(str[i]>='0'&&str[i]<='9'){
            if(id==""){
                invaild=true;
            }else{
                id+=str[i];
            }
        }else{
            if(id!=""){
                ans+="ID "+id+"\n";
                id="";
            }
            switch(str[i]){
            case '"':
                ans=ans+"STRLIT "+str[i];
                do{
                    i++;
                    ans+=str[i];
                    if(i>=str.length()){
                        invaild=true;
                        break;
                    }
                }while(str[i]!='"');
                ans+="\n";
                break;
            case '(':
                ans+="LBR (\n";
                break;
            case ')':
                ans+="RBR )\n";
                break;
            case '.':
                ans+="DOT .\n";
                break;
            case ' ':
                break;
            default:
                invaild=true;
            }
        }

    }
    if(id!=""){
        ans+="ID "+id+"\n";
        id="";
    }
    if(invaild){
        cout<<"invalid input\n";
    }else{
        cout<<ans;
    }*/
}

void error(){
     cout<<"invalid input\n";
     exit(0);
}

void dot(){
    cnt++;
    ans+="DOT .\n";
}

void lbr(){
    cnt++;
    ans+="LBR (\n";
}

void rbr(){
    cnt++;
    ans+="RBR )\n";
}

void ID(){
    ans+="ID ";
    int i=tokenStr[cnt].second;
    for(;(str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z')||(str[i]>='0'&&str[i]<='9')||str[i]=='_';i++)
        ans+=str[i];
    ans+='\n';
    cnt++;
    //cout<<ans<<endl;
}

void strlit(){
    ans+="STRLIT ";
    int i=tokenStr[cnt].second;
    do{
        ans+=str[i++];
    }while(str[i]!='"');
    ans+=str[i];
    ans+='\n';
    cnt++;
}

void primary_tail(){
    //cout<<tokenStr[cnt].first;
    if(tokenStr[cnt].first=="DOT"){
        dot();
        ID();
        primary_tail();
    }else if(tokenStr[cnt].first=="LBR"){
        lbr();
        stmt();
        rbr();
        primary_tail();
    }else if(tokenStr[cnt].first!="$"&&tokenStr[cnt].first!="ID"&&tokenStr[cnt].first!="STRLIT"){
        error();
    }
}

void primary(){
    ID();
    primary_tail();
}

void stmt(){
    if(tokenStr[cnt].first=="ID"){
        primary();
        primary_tail();
    }else if(tokenStr[cnt].first=="STRLIT"){
        strlit();
    }else if(tokenStr[cnt].first!="RBR"){
        error();
    }
}

void stmts(){
    if(tokenStr[cnt].first=="STRLIT"||tokenStr[cnt].first=="ID"){
        stmt();
        stmts();
    }

}


