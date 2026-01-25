/*
 Problem: Implement Queue using Stacks

 Concept:
 - Use two stacks:
     s1 → for push operations
     s2 → for pop / peek operations

 Lazy Transfer:
 - Only when s2 is empty, move all elements from s1 to s2
 - This reverses order and exposes front element

 Amortized Time Complexity:
   push() → O(1)
   pop()  → O(1)
   peek() → O(1)

 Worst case pop/peek: O(N)
 Space Complexity: O(N)
*/

class MyQueue {
private:
    stack<int> s1, s2;

public:
    MyQueue() {}
    void push(int x) {
        s1.push(x);
    }
    int pop() {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }

        int val = s2.top();
        s2.pop();
        return val;
    }
    // Get front element
    int peek() {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        return s2.top();
    }
    bool empty() {
        return s1.empty() && s2.empty();
    }
};
