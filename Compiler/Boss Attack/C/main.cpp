#include <bits/stdc++.h>

using namespace std;

/*
token types:

TAG_OPEN
TAG_NAME
TAG_EQUALS
HTML_TEXT
DOUBLE_QUOTE_STRING
SINGLE_QUOTE_STRING
TAG_CLOSE
htmlContent
TAG_OPEN_SLASH
TAG_NAME
TAG_CLOSE
*/

struct Token {
    string type = "";
    string value = "";

    Token(string type, string value) : type(type), value(value){};
};

stack<int> mode; // tag
vector<Token> token_stream, fin_token_stream;
int parserIndex = 0;

void calledError() // TODO. Undone
{
    cerr << "error" << endl;
    cout << "invalid" << endl;
    exit(0);
}

void html_lexer(string &str) // append tokens to token_stream
{
    int index = 0;

    while (index < str.length()) {
        cerr << "index: " << index << endl;
        if (mode.size() == 2)
            calledError();

        switch (str[index]) {
        case '<':
            if (str[index + 1] == '/')
                token_stream.emplace_back("TAG_OPEN_SLASH", "</");
            else
                token_stream.emplace_back("TAG_OPEN", "<");

            mode.push(1);

            break;
        case '>':
            token_stream.emplace_back("TAG_CLOSE", ">");

            mode.pop();

            break;
        case '=':
            token_stream.emplace_back("TAG_EQUALS", "=");

            break;
        default:
            if (mode.size()) {
                if (str[index] == ' ') {
                    token_stream.emplace_back("", "");
                    break;
                }
                else if (str[index] == '\'') {
                    index++;
                    if (index >= str.length())
                        calledError();

                    string makeSin = "";

                    while (str[index] != '\'') {
                        cerr << str[index];
                        makeSin += str[index];
                        index++;
                        if (index >= str.length())
                            calledError();
                    }
                    cerr << endl;

                    token_stream.emplace_back("SINGLE_QUOTE_STRING", makeSin);
                }
                else if (str[index] == '"') {
                    index++;
                    if (index >= str.length())
                        calledError();

                    string makeDou = "";

                    while (str[index] != '"') {
                        makeDou += str[index];
                        cerr << str[index];
                        index++;
                        if (index >= str.length())
                            calledError();
                    }
                    cerr << endl;

                    token_stream.emplace_back("DOUBLE_QUOTE_STRING", makeDou);
                }
                else if ((str[index] >= 'a' && str[index] <= 'z') || (str[index] >= 'A' && str[index] <= 'Z') ||
                         (str[index] >= '0' && str[index] <= '9')) {
                    if (token_stream.back().type == "TAG_NAME")
                        token_stream.back().value += str[index];
                    else {
                        string tmp = "";
                        tmp += str[index];
                        token_stream.emplace_back("TAG_NAME", tmp);
                    }
                }
            }
            else {
                if (token_stream.back().type == "HTML_TEXT")
                    token_stream.back().value += str[index];
                else if (str[index] == ' ') // token 間空白忽略
                    break;                  // break switch
                else {
                    string tmp = "";
                    tmp += str[index];
                    token_stream.emplace_back("HTML_TEXT", tmp);
                }
            }

            break;
        }

        index++;
    }
}

void printTokenStream()
{
    for (int i = 0; i < token_stream.size(); i++) {
        if (token_stream[i].type != "") {
            fin_token_stream.push_back(token_stream[i]);
            // cout << token_stream[i].type << " " << token_stream[i].value << endl;
        }
    }
}

// --- parser ---
void html_parser();

void htmlDocument();
void htmlElement();
void htmlContent();
void htmlAttributeList();
void htmlAttribute();
void htmlChardata();
void attribute();

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // freopen("output.log", "w", stderr);

    string line_put;

    while (!cin.eof()) {
        getline(cin, line_put);
        cerr << "reading" << endl;
        cerr << line_put << endl;
        html_lexer(line_put);
    }
    cerr << "done_lexer" << endl;
    printTokenStream();

    fin_token_stream.emplace_back("$", "$");

    html_parser();
    cout << "valid" << endl;

    return 0;
}

void html_parser()
{
    htmlDocument();
}

#define NOWTOKENTYPE fin_token_stream[parserIndex].type
#define NOWTOKENTYPENEXT fin_token_stream[parserIndex++].type

void htmlDocument()
{
    if (NOWTOKENTYPE == "TAG_OPEN") {
        htmlElement();
        htmlDocument();
        if (NOWTOKENTYPE != "$")
            calledError();
        cout << "htmlDocument" << endl;
    }
}
void htmlElement()
{
    if (NOWTOKEN TYPENEXT != "TAG_OPEN")
        calledError();
    if (NOWTOKENTYPENEXT != "TAG_NAME")
        calledError();
    htmlAttributeList();
    if (NOWTOKENTYPENEXT != "TAG_CLOSE")
        calledError();
    htmlContent();
    if (NOWTOKENTYPENEXT != "TAG_OPEN_SLASH")
        calledError();
    if (NOWTOKENTYPENEXT != "TAG_NAME")
        calledError();
    if (NOWTOKENTYPENEXT != "TAG_CLOSE")
        calledError();
    cout << "htmlElement" << endl;
}
void htmlContent()
{
    if (NOWTOKENTYPE == "HTML_TEXT") {
        htmlChardata();
        htmlContent();
        cout << "htmlContent" << endl;
    }
    else if (NOWTOKENTYPE == "TAG_OPEN") {
        htmlElement();
        htmlContent();
        cout << "htmlContent" << endl;
    }
}
void htmlAttributeList()
{
    if (NOWTOKENTYPE == "TAG_NAME") {
        htmlAttribute();
        htmlAttributeList();
        cout << "htmlAttributeList" << endl;
    }
}
void htmlAttribute()
{
    if (NOWTOKENTYPENEXT != "TAG_NAME")
        calledError();
    if (NOWTOKENTYPENEXT != "TAG_EQUALS")
        calledError();
    attribute();
    cout << "htmlAttribute" << endl;
}
void htmlChardata()
{
    if (NOWTOKENTYPENEXT != "HTML_TEXT")
        calledError();
    cout << "htmlCharData" << endl;
}
void attribute()
{
    if ((NOWTOKENTYPE != "DOUBLE_QUOTE_STRING") && (NOWTOKENTYPE != "SINGLE_QUOTE_STRING"))
        calledError();
    parserIndex++;
    cout << "attribute" << endl;
}

#undef NOWTOKENTYPE
#undef NOWTOKENTYPENEXT