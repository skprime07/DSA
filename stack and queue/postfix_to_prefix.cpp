/*
 Problem: Postfix to Prefix Conversion

 Approach:
 - Traverse postfix expression from left to right
 - For every operand → push to stack
 - For every operator:
     → pop two operands
     → form "operator + op1 + op2"
     → push back to stack

 Time Complexity: O(N)
 Space Complexity: O(N)
*/

#include <bits/stdc++.h>
using namespace std;
string postfixToPrefix(string postfix) {
    stack<string> s;
    int n = postfix.size();
    for (int i = 0; i < n; i++) {
        char c = postfix[i];
        // Operand
        if (isalnum(c)) {
            s.push(string(1, c));
        }
        // Operator
        else {
            string op2 = s.top(); s.pop();
            string op1 = s.top(); s.pop();
            s.push(c + op1 + op2);
        }
    }
    return s.top();
}
