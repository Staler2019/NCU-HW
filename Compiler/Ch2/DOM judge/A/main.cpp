#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

bool expressionFlag = false;
bool CFGFlag = false;

struct Terminal {
    string terminalName;
    string token;
    Terminal(string terminal_name, string token_name) : terminalName(terminal_name), token(token_name){};
};

class CheckCFG { // lambda return ending index
  private:
    vector<Terminal> vter;
    bool flag = false; // errorFlag
    bool program()     // getCFGFlag
    {
        cerr << "cerr: prog" << endl;
        // stmts
        int tmpIndex = this->stmts(0);
        if (this->flag || tmpIndex != this->vter.size())
            return true;
        return false;
    }
    int stmts(int index) // TODO below is undone
    {
        cerr << "cerr: stmts" << endl;
        if (index == this->vter.size()) // lambda: no tokens in queue
            return index;

        // stmt stmts
        int tmpIndex = stmt(index);
        if (tmpIndex == index) // lambda: stmt() == lambda
            return index;

        return stmts(tmpIndex);
    }
    int stmt(int index) // no -1 return value
    {
        cerr << "cerr: stmt" << endl;
        if (index == this->vter.size()) // lambda: no tokens in queue
            return index;

        // check type
        // primary
        int tmpIndex = primary(index);
        if (tmpIndex != index)
            return tmpIndex;

        // STRLIT
        // tmpIndex = index;
        if (this->vter[tmpIndex].terminalName == "STRLIT")
            return tmpIndex + 1;

        // lambda
        return index;
    }
    int primary(int index)
    {
        cerr << "cerr: primary" << endl;
        // ID primary_tail
        if (this->vter[index].terminalName == "ID")
            return primary_tail(index + 1);
        else
            return index; // not primary
    }
    int primary_tail(int index)
    {
        cerr << "cerr: primary_tail" << endl;
        if (index == this->vter.size()) // lambda: no tokens in queue
            return index;

        // DOT ID primary_tail
        if (this->vter[index].terminalName == "DOT") {
            // check
            if (this->vter[index + 1].terminalName == "ID")
                return this->primary_tail(index + 2);
            else {
                this->flag = true; // CFG error
                return index;
            }
        }

        // LBR stmt RBR primary_tail
        else if (this->vter[index].terminalName == "LBR") {
            int tmpIndex = this->stmt(index + 1);
            if (this->vter[tmpIndex].terminalName == "RBR") {
                return this->primary_tail(tmpIndex + 1);
            }
            else {
                this->flag = true; // CFG error
                return index;
            }
        }
        else
            return index; // lambda
    }

  public:
    CheckCFG(vector<Terminal> &vecTermin) : vter(vecTermin){};
    bool getCFGFlag()
    {
        return this->program();
    }
};

vector<string> split(string &str)
{
    vector<string> tokens;

    tokens.push_back("");
    for (int i = 0; (i < str.length()) && !expressionFlag; i++) {
        switch (str[i]) {
        case '.':
        case '(':
        case ')': {
            if (tokens.back() == "")
                tokens.back() += str[i];
            else {
                string tmpStr(1, str[i]);
                tokens.emplace_back(tmpStr);
            }
            tokens.push_back("");
            break;
        }
        case '"': {
            string tmpStr;
            while (i < str.length() - 1 && str[++i] != '"')
                tmpStr += str[i];
            tmpStr = '"' + tmpStr + '"';
            if (tokens.back() == "")
                tokens.back() = tmpStr;
            else
                tokens.emplace_back(tmpStr);

            if (i == str.length() - 1 && str[i] != '"')
                expressionFlag = true;
            else
                tokens.push_back("");
            break;
        }
        case ' ':
        case '\n':
        case '\r':
            break;
        default:
            if (tokens.back() == "") { // ID front
                if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || str[i] == '_')
                    tokens.back() += str[i];
                else
                    expressionFlag = true;
            }
            else { // ID from the 2nd
                if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || str[i] == '_' ||
                    (str[i] >= '0' && str[i] <= '9'))
                    tokens.back() += str[i];
                else
                    expressionFlag = true;
            }
            break;
        }
    }
    if (tokens.back() == "")
        tokens.pop_back();
    // cerr << "err: " << tokens.size() << endl;
    return tokens;
}

void rewrite(string &token, vector<Terminal> &vter)
{
    switch (token[0]) {
    case '.':
        vter.emplace_back("DOT", token);
        break;
    case '(':
        vter.emplace_back("LBR", token);
        break;
    case ')':
        vter.emplace_back("RBR", token);
        break;
    case '"':
        vter.emplace_back("STRLIT", token);
        break;
    default: // ID
        vter.emplace_back("ID", token);
        break;
    }
}

void printTerminal(Terminal &ter)
{
    cout << ter.terminalName << " " << ter.token << endl;
}

int main()
{
    // freopen("C:/Users/abcd1/Downloads/110HW1_B1.in", "r", stdin);
    // freopen("output.txt", "w", stderr);
    expressionFlag = false;
    CFGFlag = false;

    vector<string> output;
    while (!cin.eof()) {
        string input;
        getline(cin, input);
        vector<string> tokens = split(input);

        // cerr
        // for (int i = 0; i < tokens.size(); i++)
        //     cout << tokens[i] << endl;
        // cout << expressionFlag << endl;

        // regular expression
        if (expressionFlag) {
            cout << "invalid input" << endl;
            return 0;
        }
        vector<Terminal> vecTermin;
        for (int i = 0; i < tokens.size(); i++)
            rewrite(tokens[i], vecTermin);
        cerr << "cerr: RE ok" << endl;

        // CFG
        CheckCFG cfg(vecTermin);
        CFGFlag = cfg.getCFGFlag();
        if (CFGFlag) {
            cout << "invalid input" << endl;
            return 0;
        }
        for (int i = 0; i < tokens.size(); i++)
            printTerminal(vecTermin[i]);
    }

    return 0;
}