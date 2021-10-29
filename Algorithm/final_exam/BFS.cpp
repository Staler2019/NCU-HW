#include <bits/stdc++.h>

using namespace std;
using VII = std::vector<vector<int>>;
using VI = std::vector<int>;

struct Point {
    int x = 0;
    int y = 0;
    Point(int x, int y) : x(x), y(y){};
};

// int arr[3][3] = {{2, 0, 3}, {1, 8, 4}, {7, 6, 5}};
void printArr(VII &arr)
{
    for (int j = 0; j < 3; j++) {
        cout << arr[j][0];
        for (int i = 1; i < 3; i++) {
            cout << " " << arr[j][i];
        }
        cout << endl;
    }
}

Point find0(VII &nowPoint)
{
    int x, y;
    for (x = 0; x < 3; x++)
        for (y = 0; y < 3; y++)
            if (nowPoint[x][y] == 0)
                return Point(x, y);
}

// v1: I just write to dfs
// bool bfs(VII &nowPuzzle, VII &resultPuzzle, map<VII, bool> &gone)
// {
//     Point blank = find0(nowPuzzle);

//     // dfs
//     printArr(nowPuzzle);
//     if (nowPuzzle == resultPuzzle)
//         return true;

//     // up
//     if (blank.x > 0) {
//         VII tmp_vii = nowPuzzle;
//         swap(tmp_vii[blank.x][blank.y], tmp_vii[blank.x - 1][blank.y]);
//         if (gone.find(tmp_vii) != gone.end()) {
//             gone[tmp_vii] = 1;
//             if (bfs(tmp_vii, resultPuzzle, gone))
//                 return true;
//         }
//     }
//     // right
//     if (blank.y < 2) {
//         VII tmp_vii = nowPuzzle;
//         swap(tmp_vii[blank.x][blank.y], tmp_vii[blank.x][blank.y + 1]);
//         if (gone.find(tmp_vii) != gone.end()) {
//             gone[tmp_vii] = 1;
//             if (bfs(tmp_vii, resultPuzzle, gone))
//                 return true;
//         }
//     }
//     // down
//     if (blank.x < 2) {
//         VII tmp_vii = nowPuzzle;
//         swap(tmp_vii[blank.x][blank.y], tmp_vii[blank.x + 1][blank.y]);
//         if (gone.find(tmp_vii) != gone.end()) {
//             gone[tmp_vii] = 1;
//             if (bfs(tmp_vii, resultPuzzle, gone))
//                 return true;
//         }
//     }
//     // left
//     if (blank.y > 0) {
//         VII tmp_vii = nowPuzzle;
//         swap(tmp_vii[blank.x][blank.y], tmp_vii[blank.x][blank.y - 1]);
//         if (gone.find(tmp_vii) != gone.end()) {
//             gone[tmp_vii] = 1;
//             if (bfs(tmp_vii, resultPuzzle, gone))
//                 return true;
//         }
//     }

//     return false;
// }

void bfsForward(queue<VII> &Q, VII &now, vector<VII> &accessed)
{
    Point blank = find0(now);
    // up
    if (blank.x > 0) {
        VII tmp = now;
        swap(tmp[blank.x][blank.y], tmp[blank.x - 1][blank.y]);
        if (find(accessed.begin(), accessed.end(), tmp) == accessed.end()) {
            Q.emplace(tmp);
            accessed.push_back(tmp);
        }
    }
    // right
    if (blank.y < 2) {
        VII tmp = now;
        swap(tmp[blank.x][blank.y], tmp[blank.x][blank.y + 1]);
        if (find(accessed.begin(), accessed.end(), tmp) == accessed.end()) {
            Q.emplace(tmp);
            accessed.push_back(tmp);
        }
    }
    // down
    if (blank.x < 2) {
        VII tmp = now;
        swap(tmp[blank.x][blank.y], tmp[blank.x + 1][blank.y]);
        if (find(accessed.begin(), accessed.end(), tmp) == accessed.end()) {
            Q.emplace(tmp);
            accessed.push_back(tmp);
        }
    }
    // left
    if (blank.y > 0) {
        VII tmp = now;
        swap(tmp[blank.x][blank.y], tmp[blank.x][blank.y - 1]);
        if (find(accessed.begin(), accessed.end(), tmp) == accessed.end()) {
            Q.emplace(tmp);
            accessed.push_back(tmp);
        }
    }
}

void bfs(VII &nowPuzzle, VII &resultPuzzle)
{
    queue<VII> readyQueue;
    vector<VII> accessed;

    readyQueue.emplace(nowPuzzle);
    accessed.push_back(nowPuzzle);

    while (readyQueue.size() != 0) {
        VII now = readyQueue.front();
        readyQueue.pop();
        printArr(now);
        if (now == resultPuzzle)
            break;
        bfsForward(readyQueue, now, accessed);
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.log", "w", stderr);
    // freopen("output.txt", "w", stdout);
    VII nowPuzzle(3, VI(3)), resultPuzzle(3, VI(3));
    // cin
    for (VI &vi : nowPuzzle)
        for (int &i : vi)
            cin >> i;
    for (VI &vi : resultPuzzle)
        for (int &i : vi)
            cin >> i;

    // print now
    // printArr(nowPuzzle);
    bfs(nowPuzzle, resultPuzzle);
    return 0;
}