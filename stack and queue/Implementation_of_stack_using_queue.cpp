/*
 Problem: Implement Stack using Queues

 Concept:
 - Use a single queue
 - On every push:
     → Insert element
     → Rotate previous elements behind it
 - This keeps the newest element always at front
 - So pop() and top() become O(1)

 Time Complexity:
   push()  → O(N)
   pop()   → O(1)
   top()   → O(1)
   empty()→ O(1)

 Space Complexity: O(N)
*/

class MyStack {
private:
    queue<int> q;
public:
    MyStack() {}
    // Push element onto stack
    void push(int x) {
        q.push(x);
        // Rotate previous elements
        int sz = q.size();
        while (sz-- > 1) {
            q.push(q.front());
            q.pop();
        }
    }
    int pop() {
        int val = q.front();
        q.pop();
        return val;
    }
    int top() {
        return q.front();
    }
    bool empty() {
        return q.empty();
    }
};
