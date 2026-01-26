/*
 Problem: Prefix to Infix Conversion

 Approach:
 - Traverse prefix expression from right to left
 - For every operand → push to stack
 - For every operator:
     → pop two operands
     → form "(op1 operator op2)"
     → push back to stack

 Time Complexity: O(N)
 Space Complexity: O(N)
*/

#include <bits/stdc++.h>
using namespace std;
string prefixToInfix(string prefix) {
    stack<string> s;
    int n = prefix.size();
    // Traverse prefix expression from right to left
    for (int i = n - 1; i >= 0; i--) {
        char c = prefix[i];
        // Operand
        if (isalnum(c)) {
            s.push(string(1, c));
        }
        // Operator
        else {
            string op1 = s.top(); s.pop();
            string op2 = s.top(); s.pop();
            s.push("(" + op1 + c + op2 + ")");
        }
    }
    return s.top();
}
