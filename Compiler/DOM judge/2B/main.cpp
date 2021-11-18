#include <bits/stdc++.h>
using namespace std;

map<char, string> nonterminal;
map<char, set<char>> first;

// tools
void printRules()
{
    for (auto it = nonterminal.begin(); it != nonterminal.end(); it++) {
        cout << it->first << " " << it->second << endl;
    }
}

void printFirsts()
{
    for (auto it1 = first.begin(); it1 != first.end(); it1++) {
        cout << it1->first << " ";
        for (auto it2 = it1->second.begin(); it2 != it1->second.end(); it2++)
            cout << *it2;

        cout << endl;
    }
}

bool isTerminal(char c)
{
    if ((c >= 'a' && c <= 'z') || c == ';' || c == '$')
        return true;
    return false;
}

// funcs
void inputRules()
{
    while (1) {
        string nont, rule;
        cin >> nont;
        if (nont == "END_OF_GRAMMAR")
            break;
        else if (nont.length() > 1) {
            cerr << nont << ": error length: " << nont.length() << endl;
            exit(0);
        }
        cin.get(); // get a blank
        cin >> rule;
        nonterminal[nont[0]] = rule;
    }
}

set<char> getFirstSet(char c)
{
    cerr << c << "--";
    if (isTerminal(c)) {
        cerr << c;
        return set<char>({c}); // different from getTerminalSet directly to exit(0)
    }
    else { // nonterminal
        if (first.find(c) != first.end())
            return first[c];
        else { // this nonterminal not find in "first" map
            string &str = nonterminal[c];
            set<char> tmp;
            for (auto it = str.begin();;) {
                do {
                    cerr << *it;
                    set<char> foundSet = getFirstSet(*it);
                    it++;
                    if (*it == '|' || it == str.end()) { // production not found here
                        it--;
                        tmp.insert(foundSet.begin(), foundSet.end());
                        break;
                    }
                    else {
                        if (foundSet.find(';') != foundSet.end()) {
                            // it--; // continue the it counter
                            foundSet.erase(';');
                            tmp.insert(foundSet.begin(), foundSet.end());
                        }
                        else { // ';' not found in this set, end production
                            it--;
                            tmp.insert(foundSet.begin(), foundSet.end());
                            break;
                        }
                    }
                } while (1);
                it = find(it, str.end(), '|');
                if (it == str.end())
                    break;
                it++;
                cerr << "\t";
            }
            first[c] = tmp;
            return tmp;
        }
    }
}

void makeFirstSet()
{
    for (auto it = nonterminal.begin(); it != nonterminal.end(); it++) {
        getFirstSet(it->first);
        cerr << endl;
    }
    printFirsts();
    cout << "END_OF_FIRST\n";
}

int main()
{
    inputRules();
    makeFirstSet();
    return 0;
}