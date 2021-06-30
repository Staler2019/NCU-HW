/**
 * @file lcs_v2_2xN.cpp
 * @author Staler2019 (github.com/Staler2019)
 * @brief LCS algorithm
 * @version 1
 * @date 2021-05-12
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string lcs(string &a, string &b)
{
    string ans;
    vector<vector<string>> matp(2, vector<string>(b.length() + 1, ""));

    for (int i = 0; i < a.length(); i++) {
        for (int j = 0; j < b.length(); j++) {
            if (b[j] == a[i]) {
                if (matp[(i + 1) % 2][j].length() >= matp[i % 2][j].length() + 1)
                    matp[(i + 1) % 2][j + 1] = matp[(i + 1) % 2][j];
                else
                    matp[(i + 1) % 2][j + 1] = matp[i % 2][j] + a[i];
            }
            else {
                if (matp[(i + 1) % 2][j].length() >= matp[i % 2][j + 1].length())
                    matp[(i + 1) % 2][j + 1] = matp[(i + 1) % 2][j];
                else
                    matp[(i + 1) % 2][j + 1] = matp[i % 2][j + 1];
            }
        }
    }

    return matp[a.length() % 2][b.length()];
}

int main()
{
    int n;
    cin >> n;
    while (n--) {
        string a, b, ans;
        cin >> a >> b;
        ans = lcs(a, b);
        cout << ans.length() << endl;
    }
}