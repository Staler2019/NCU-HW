#include <bits/stdc++.h>
using namespace std;

namespace Lexical_Detail {
using namespace std;
// primary definition
regex separator("[\t\n\r]");
regex letter("[a-z]");
regex digit("[0-9]");
// token definition
regex number("0|[1-9][0-9]*|-[1-9][0-9]*");
regex ID("[a-z]([a-z]|[0-9]|-)*");
regex bool_val("#t|#f");
} // namespace Lexical_Detail

using namespace Lexical_Detail;

int main()
{
}