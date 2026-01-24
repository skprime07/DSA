/*
 Problem: Accounts Merge

 Approach:
 - Each account is treated as a node
 - Emails are mapped to account indices
 - If two accounts share an email, union them using DSU
 - Finally, collect emails belonging to the same parent account
 - Sort emails and attach account holder's name

 Time Complexity: O(N * M * α(N))
 Space Complexity: O(N * M)
*/

class DisjointSet {
public:
    vector<int> parent, rank, size;
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        size.resize(n, 1);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }
    // Union by size
    void unionBySize(int u, int v) {
        int pu = findUPar(u);
        int pv = findUPar(v);
        if (pu == pv) return;

        if (size[pu] < size[pv]) {
            parent[pu] = pv;
            size[pv] += size[pu];
        } else {
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        DisjointSet ds(n);
        unordered_map<string, int> emailToAccount;
        // Step 1: Union accounts having common emails
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < accounts[i].size(); j++) {
                string email = accounts[i][j];
                if (emailToAccount.find(email) == emailToAccount.end()) {
                    emailToAccount[email] = i;
                } else {
                    ds.unionBySize(i, emailToAccount[email]);
                }
            }
        }
        // Step 2: Group emails by parent account
        vector<vector<string>> mergedEmails(n);
        for (auto &it : emailToAccount) {
            string email = it.first;
            int parent = ds.findUPar(it.second);
            mergedEmails[parent].push_back(email);
        }
        // Step 3: Build final answer
       vector<vector<string>> result;
        for (int i = 0; i < n; i++) {
            if (mergedEmails[i].empty()) continue;
            sort(mergedEmails[i].begin(), mergedEmails[i].end());
            vector<string> account;
            account.push_back(accounts[i][0]);  // account name
            for (auto &email : mergedEmails[i])
                account.push_back(email);
            result.push_back(account);
        }
        sort(result.begin(), result.end());
        return result;
    }
};
