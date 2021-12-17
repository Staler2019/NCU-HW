#include <bits/stdc++.h>

using namespace std;

char start_symbol;
map<char, vector<string>> rules;
map<char, set<char>> firsts;
map<char, set<char>> follows;
set<char> terminal;

// tools
const vector<string> strlit(const string &str,
                            const string &token)
{
    vector<string> result;

    string::size_type begin, end;
    begin = 0;
    end = str.find(token);

    while (end != string::npos) {
        if ((end - begin) != 0) {
            result.push_back(
                str.substr(begin, end - begin));
        }
        begin = end + token.size();
        end = str.find(token, begin);
    }

    if (begin != str.length()) {
        result.push_back(str.substr(begin));
    }

    return result;
}
bool isTerminal(const char c)
{
    if (terminal.find(c) != terminal.end())
        return true;
    return false;
}
bool isNont(const char c)
{
    return !isTerminal(c);
}
void printFollowSet()
{
    for (auto &i : follows) {
        cout << i.first << " ";
        for (auto &j : i.second) {
            cout << j;
        }
        cout << endl;
    }
}
void printTerminals()
{
    cerr << "---terminals---\n";
    for (auto &i : terminal) {
        cerr << i;
    }
    cerr << "\n---end---" << endl;
}
void printRules()
{
    cerr << "---rules---\n";
    for (auto &i : rules) {
        cerr << i.first << " ";
        for (auto &j : i.second) {
            cerr << j << "|";
        }
        cerr << "\b" << endl;
    }
    cerr << "---end---" << endl;
}
void printFirstSet()
{
    cerr << "---firstsets---\n";
    for (auto &i : firsts) {
        cerr << i.first << " ";
        for (auto &j : i.second) {
            cerr << j;
        }
        cerr << endl;
    }
    cerr << "---end---" << endl;
}
set<char> getFirst(const char c)
{
    if (isTerminal(c)) {
        return set<char>({c});
    }
    return firsts[c];
}

// normal funcs
void initTerminals() // ok
{
    terminal.insert(';');
    terminal.insert('$');
    for (char c = 'a'; c <= 'z'; c++)
        terminal.insert(c);
}
void inputRule() // ok
{
    bool is_first = true;
    while (true) {
        string lhs;
        string rhs;
        vector<string> rhs_lit;

        cin >> lhs;
        if (lhs.length() != 1) // END_OF_GRAMMAR
            return;
        cin >> rhs;

        if (is_first) {
            start_symbol = lhs[0];
            is_first = false;
        }
        rhs_lit = strlit(rhs, "|");
        rules[lhs[0]] = rhs_lit;
    }
}
void inputFirstSet() // ok
{
    while (true) {
        string lhs;
        string rhs;
        set<char> rhs_set;

        cin >> lhs;
        if (lhs.length() != 1) // END_OF_FIRST_SET
            return;
        cin >> rhs;

        rhs_set.insert(rhs.begin(), rhs.end());
        firsts[lhs[0]] = rhs_set;
    }
}
void inputToFollow(const char target,
                   const set<char> &inputThing)
{
    if (follows.find(target) == follows.end()) { // not find
        follows[target] = inputThing;
    }
    else {
        follows[target].insert(inputThing.begin(),
                               inputThing.end());
    }
}
void makeFollowSet()
{
    map<char, set<char>> his_follows;
    follows[start_symbol] = set<char>({'$'}); // ok
    do {
        cerr << "---start---" << endl;
        his_follows = follows;

        for (auto &R : rules) {
            auto &A = R.first;
            for (auto &proc :
                 R.second) { // each production rule
                for (int i = 0; i < proc.length(); i++) {
                    auto &B = proc[i];
                    if (isNont(B)) {
                        cerr << "nont--" << B << endl;
                        for (int j = i + 1;
                             j < proc.length(); j++) {
                            auto &C = proc[j];
                            cerr << "\t" << C << endl;
                            bool hasLambda = false;
                            auto tmp_set = getFirst(C);
                            if (tmp_set.find(';') !=
                                tmp_set.end()) {
                                hasLambda = true;
                                tmp_set.erase(';');
                            }
                            inputToFollow(B, tmp_set);
                            if (!hasLambda)
                                break; // go next B
                        }
                        //
                        bool everyHasLambda = true;
                        for (int j = i + 1;
                             j < proc.length() &&
                             everyHasLambda;
                             j++) {
                            auto &C = proc[j];
                            cerr << "---3rd---" << C
                                 << endl;
                            if (firsts[C].find(';') ==
                                firsts[C]
                                    .end()) { // not found
                                everyHasLambda = false;
                            }
                        }
                        if (everyHasLambda) {
                            inputToFollow(B, follows[A]);
                        }
                    }
                }
            }
        }
    } while (his_follows != follows);
}

int main()
{
    initTerminals();
    inputRule();
    inputFirstSet();
    // printRules();
    // printFirstSet();
    // printTerminals();
    makeFollowSet();
    printFollowSet();

    return 0;
}