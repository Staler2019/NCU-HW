#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define all(a) std::begin(a), std::end(a)
#define pb push_back
#define mp make_pair
#define st first
#define nd second

bool stringCompare(pair<string, char> p1, pair<string, char> p2)
{
    int s1 = p1.st.length(), s2 = p2.st.length();
    if (s1 < s2)
        return true;
    else
        return (p1.first.compare(p2.first) < 0);
}

void huffmanCoding(string &str)
{
    // v2
    map<char, int> charCounter;
    for (int i = 0; i < str.length(); i++) // O(nlog(n)) char &c : str
        charCounter[str[i]]++;

    map<char, string> codeArray;
    priority_queue<pair<int, vector<char>>, vector<pair<int, vector<char>>>, greater<pair<int, vector<char>>>>
        tree; // (total_index, char_in_str)
    for (map<char, int>::const_iterator it = charCounter.begin(); it != charCounter.end();
         it++) { // autoit(charCounter)
        codeArray[it->st] = "";
        tree.push(mp(it->nd, vector<char>({it->st})));
    }

    while (tree.size() > 1) {
        pair<int, vector<char>> p1 = tree.top();
        tree.pop();
        pair<int, vector<char>> p2 = tree.top();
        tree.pop();

        if (p1.st > p2.st)
            swap(p1, p2);
        for (int i = 0; i < p1.nd.size(); i++)
            codeArray[p1.nd[i]] = "0" + codeArray[p1.nd[i]];
        for (int i = 0; i < p2.nd.size(); i++)
            codeArray[p2.nd[i]] = "1" + codeArray[p2.nd[i]];

        p1.st += p2.st;
        p1.nd.insert(p1.nd.end(), all(p2.nd));
        tree.push(p1);
    }

    vector<pair<string, char>> printMap;
    for (vector<char>::const_iterator it = tree.top().nd.begin(); it != tree.top().nd.end(); it++)
        printMap.pb(mp(codeArray[*it], *it));
    sort(all(printMap), stringCompare);
    for (int i = 0; i < printMap.size(); i++)
        cout << printMap[i].nd << ":" << printMap[i].st << endl;

    // v1: wrong alg
    // map<int, vector<pair<char, string>>> tree; // (total_index,(char_in_str, 01_coding))

    // map<char, int> charCounter;
    // for (char &c : str) // O(nlog(n))
    //     charCounter[c]++;

    // for (autoit(charCounter)) { // O(nlog(n))
    //     tree[it->nd].pb(mp(it->st, ""));
    // }

    // printTree(tree);
    // cerr << "---startle---\n";

    // while (tree.size() > 1) {
    //     auto it = tree.begin();
    //     auto first = mp(it->st, it->nd);
    //     tree.erase(it);
    //     it = tree.begin();
    //     auto second = mp(it->st, it->nd);
    //     tree.erase(it);

    //     // decision
    //     if (first.st > second.st)
    //         swap(first, second);
    //     for (autoit(first.nd))
    //         it->nd = "0" + it->nd;
    //     for (autoit(second.nd))
    //         it->nd = "1" + it->nd;

    //     // combine
    //     first.st += second.st;
    //     first.nd.insert(first.nd.end(), all(second.nd));
    //     tree[first.st] = first.nd;
    //     printTree(tree);
    //     cerr << "-------------" << endl;
    // }

    // // print
    // vector<pair<string, char>> printMap;
    // for (autoit(tree.begin()->nd))
    //     printMap.pb(mp(it->nd, it->st));
    // sort(all(printMap), stringCompare);
    // for (autoit(printMap))
    //     cout << it->nd << ":" << it->st << endl;
}
/*- 主程式 -*/
int Solving()
{
    string str;
    cin >> str;

    huffmanCoding(str);

    return 0; // End of code
}
int main()
{
    cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(0);
    return Solving();
}
