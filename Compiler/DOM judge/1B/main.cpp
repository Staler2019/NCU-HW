#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

vector<string> split(string &str)
{
    vector<string> tokens;

    tokens.push_back("");
    for (int i = 0; i < str.length(); i++) {
        switch (str[i]) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
            if (tokens.back() == "")
                tokens.back() += str[i];
            else {
                string tmpStr(1, str[i]);
                tokens.emplace_back(tmpStr);
            }
            tokens.push_back("");
        case ' ':
        case '\n':
        case '\r':
            break;
        default:
            tokens.back() += str[i];
            break;
        }
    }
    if (tokens.back() == "")
        tokens.pop_back();
    // cerr << "err: " << tokens.size() << endl;
    return tokens;
}

void rewrite(string &token, vector<string> &output)
{
    switch (token[0]) {
    case '+':
        // cout << "PLUS";
        output.push_back("PLUS");
        break;
    case '-':
        // cout << "MINUS";
        output.push_back("MINUS");
        break;
    case '*':
        // cout << "MUL";
        output.push_back("MUL");
        break;
    case '/':
        // cout << "DIV";
        output.push_back("DIV");
        break;
    case '(':
        // cout << "LPR";
        output.push_back("LPR");
        break;
    case ')':
        // cout << "RPR";
        output.push_back("RPR");
        break;
    default: // num
        // cout << "NUM " << token;
        string tmpStr = "NUM " + token;
        output.push_back(tmpStr);
        break;
    }

    // cout << endl;
}

int main()
{
    // freopen("C:/Users/abcd1/Downloads/110HW1_B1.in", "r", stdin);
    // freopen("output.txt", "w", stdout);

    vector<string> output;
    while (!cin.eof()) {
        string input;
        cin >> input;
        vector<string> tokens = split(input);
        for (int i = 0; i < tokens.size(); i++)
            rewrite(tokens[i], output);
        // cout << tokens[i] << endl;
    }

    for (int i = 0; i < output.size(); i++)
        cout << output[i] << endl;

    return 0;
}