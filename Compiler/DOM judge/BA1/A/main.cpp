#include <bits/stdc++.h>

using namespace std;

/*
reg:
a+b
ba*c
*/

int main()
{
    string input;

    // '$' in the end
    while (cin >> input) {
        int index = 0;
        cerr << input << endl;

        if (input[index] == 'a') {
            index++;
            while ((input[index] == 'a') && (index < input.size() - 1)) {
                index++;
            }

            if (index != input.size() - 2) {
                cout << "NO" << endl;
            }
            else if (input[input.size() - 2] == 'b') { // index=input.size()-2 now
                cout << "YES s4" << endl;
            }
            else {
                cout << "NO" << endl;
            }
        }
        else if (input[index] == 'b') {
            index++;
            while ((input[index] == 'a') && (index < input.size() - 1)) {
                index++;
            }

            if (index != input.size() - 2) {
                if (index == input.size() - 1) {
                    cout << "YES s3" << endl;
                }
                else {
                    cout << "NO" << endl;
                }
            }
            else if (input[input.size() - 2] == 'c') { // index=input.size()-2 now
                cout << "YES s4" << endl;
            }
            else {
                cout << "NO" << endl;
            }
        }
        else {
            cout << "NO" << endl;
        }
    }
    return 0;
}