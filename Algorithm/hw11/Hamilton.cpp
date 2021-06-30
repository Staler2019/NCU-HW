/**********************
 *Author: Staler2019  *
 *Problem:            *
 *Time:               *
 **********************/

/* 常用設定 -------------------------------------- */
#define SCHOOL

#ifndef SCHOOL // Using TDM-GCC
#include <immintrin.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <complex>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <thread>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#else
#include <bits/stdc++.h>
#endif // SCHOOL
using namespace std;

namespace PP // Self-defined namespace
{
#pragma GCC optimize("Ofast")

using namespace std;

#define _CRT_SECURE_NO_WARNINGS
/* 自定義名詞 ------------------------------------ */
#define Be return
#define AC 0
#define UNTIE_IO cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(0)
#define CASE                                                                                                           \
    int _C;                                                                                                            \
    cin >> _C;                                                                                                         \
    for (int CC = 0; CC < _C; CC++)
#define all(a) std::begin(a), std::end(a)
#define sum(a) (accumulate(all(a), 0ll))
#define mine(a) (*min_element(all(a)))
#define maxe(a) (*max_element(all(a)))
#define mini(a) (min_element(all(a)) - (a).begin())
#define maxi(a) (max_element(all(a)) - (a).begin())
#define lowb(a, x) (lower_bound(all(a), (x)) - (a).begin())
#define uppb(a, x) (upper_bound(all(a), (x)) - (a).begin())
#define autoit(container)                                                                                              \
    auto it = container.begin();                                                                                       \
    it != container.end();                                                                                             \
    it++
#define autorit(container)                                                                                             \
    auto it = container.rbegin();                                                                                      \
    it != container.rend();                                                                                            \
    it++
/* 自定義屬性 ------------------------------------ */
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define st first
#define nd second
#define endl '\n'
/* 自定義模板------------------------------------- */
#define TT1 template <class T>
#define TT1T2 template <class T1, class T2>
// begin template base

/*- FOR-LOOP -*/
#define FIA(a) for (auto &i : a)
#define FJA(a) for (auto &j : a)
#define FI(a) for (std::size_t i = 0; i < a; i++)
#define FJ(a) for (std::size_t j = 0; j < a; j++)
#define FK(a) for (std::size_t k = 0; k < a; k++)
/*- PAIR -*/
#define PT1T2 pair<T1, T2>
// OPERATOR
TT1T2 inline PT1T2 operator+(const PT1T2 &p1, const PT1T2 &p2)
{
    return PT1T2(p1.first + p2.first, p1.second + p2.second);
}
TT1T2 inline PT1T2 &operator+=(PT1T2 &p1, const PT1T2 &p2)
{
    p1.first += p2.first, p1.second += p2.second;
    return p1;
}
TT1T2 inline PT1T2 operator-(const PT1T2 &p1, const PT1T2 &p2)
{
    return PT1T2(p1.first - p2.first, p1.second - p2.second);
}
TT1T2 inline PT1T2 &operator-=(PT1T2 &p1, const PT1T2 &p2)
{
    p1.first -= p2.first, p1.second -= p2.second;
    return p1;
}
// IO
TT1T2 inline istream &operator>>(istream &is, PT1T2 &p)
{
    is >> p.first >> p.second;
    return is;
}
TT1T2 inline ostream &operator<<(ostream &os, const PT1T2 &p)
{
    os << p.first << p.second;
    return os;
}
#undef PT1T2 // pair<T1, T2>
/*- VECTOR -*/
#define VT1 vector<T>
// OPERATOR
TT1 inline VT1 &operator--(VT1 &v)
{
    FIA(v)
    i--;
    return v;
}
TT1 inline VT1 &operator++(VT1 &v)
{
    FIA(v)
    i++;
    return v;
}
// IO
TT1 inline istream &operator>>(istream &is, VT1 &v)
{
    FIA(v)
    is >> i;
    return is;
}
TT1 inline ostream &operator<<(ostream &os, const VT1 &v)
{
    FI(v.size())
    os << v[i] << " ";
    return os;
}
#undef VT1 // vector<T>

// end template base
#undef TT1
#undef TT1T2
/* 自定義型態 ------------------------------------ */
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
/* 自定義函式 ------------------------------------ */
#define isOdd(a) ((a & 1) ? true : false)
#define isDivided(a, b) ((a % b) ? false : true)
#define cer(args...) cerr << __PRETTY_FUNCTION__ << " - " << __LINE__ << "(" << #args << ") = " << args << endl
} // namespace PP

using namespace PP;

/* 程式碼 ---------------------------------------- */
/*- 定義 -*/
// #define STD_IN
// #define STD_OUT
// #define ERR_OUT
/*- 函式 -*/
bool hamilton(map<int, vector<int>> &graph, vector<int> accessed, int nowNode, int origin)
{
    accessed.push_back(nowNode);
    if (accessed.size() == (graph.size() + 1)) {
        cerr << accessed << endl;
        if (nowNode == origin)
            return true; // if found
        else
            return false;
    }

    bool b_accessed = false;
    for (int &i : graph[nowNode]) {
        if (std::find(accessed.begin() + 1, accessed.end(), i) == accessed.end()) {
            b_accessed = hamilton(graph, accessed, i, origin);
            if (b_accessed)
                return true;
        }
    }

    return false; // if not found
}
/*- 主程式 -*/
int Solving()
{
    CASE
    {
        int edges;
        cin >> edges;
        map<int, vector<int>> graph;
        for (int i = 0; i < edges; i++) {
            // read pair
            string p;
            cin >> p;
            size_t comma_pos = p.find(',');
            string str_a = p.substr(1, comma_pos - 1);
            string str_b = p.substr(comma_pos + 1, p.size() - comma_pos - 2);
            // cerr << str_a << " " << str_b << endl;

            // str_number to int
            int a = 0, b = 0;
            for (char &c : str_a) {
                a *= 10;
                a += c - '0';
            }
            for (char &c : str_b) {
                b *= 10;
                b += c - '0';
            }
            // cerr << a << " " << b << endl;

            // undirected graph
            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        // map<int, bool> access_template;
        // for (autoit(graph))
        //     access_template[it->st] = false;

        bool found = false;
        for (autoit(graph)) {
            vector<int> accessed;
            found = hamilton(graph, accessed, it->st, it->st);
            if (found)
                break;
        }

        if (found)
            cout << "True\n";
        else
            cout << "False\n";
    }
    Be AC; // End of code
}
int main()
{
    UNTIE_IO;
#ifdef STD_IN
    freopen("input.txt", "r", stdin);
#endif
#ifdef STD_OUT
    freopen("output.txt", "w", stdout);
#endif
#ifdef ERR_OUT
    freopen("output.log", "w", stderr);
#endif
    Be Solving();
}
