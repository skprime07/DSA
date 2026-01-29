/*
Problem: LeetCode 901 – Online Stock Span

Approach:
- Use a monotonic decreasing stack storing pairs:
    {price, span}
- For each incoming price:
    → Initialize span = 1
    → While stack top price <= current price:
        - Add its span to current span
        - Pop it (since current price dominates it)
    → Push {current price, total span}
- Return span.

Idea:
Each element is pushed and popped at most once → efficient.

Time Complexity: O(N) amortized
Space Complexity: O(N)
*/

class StockSpanner {
private:
    // Stack stores: {stock price, span}
    stack<pair<int, int>> st;
public:
    StockSpanner() {
        // Empty constructor
    }
    int next(int price) {
        int span = 1;
        // Merge previous smaller or equal prices
        while (!st.empty() && st.top().first <= price) {
            span += st.top().second;   // accumulate spans of popped ones
            st.pop();
        }
        // Push current price with computed span
        st.push({price, span});
        return span;
    }
};

