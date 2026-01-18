/*
 Problem: Word Ladder
 Platform: LeetCode
 Link: https://leetcode.com/problems/word-ladder/

 Approach:
 - Use Breadth First Search (BFS) to find the shortest transformation
 - Each level of BFS represents one transformation
 - For each word, change one character at a time ('a' to 'z')
 - Use a set to ensure words are used only once

 Time Complexity: O(N * L * 26)
   where N = number of words, L = length of each word
 Space Complexity: O(N)
*/

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dictionary(wordList.begin(), wordList.end());
        if (dictionary.find(endWord) == dictionary.end())
            return 0;

        queue<pair<string, int>> q;
        q.push({beginWord, 1});
        dictionary.erase(beginWord);
        while (!q.empty()) {
            string word = q.front().first;
            int steps = q.front().second;
            q.pop();

            if (word == endWord)
                return steps;

            for (int i = 0; i < word.length(); i++) {
                char originalChar = word[i];

                for (char ch = 'a'; ch <= 'z'; ch++) {
                    word[i] = ch;

                    if (dictionary.find(word) != dictionary.end()) {
                        dictionary.erase(word);
                        q.push({word, steps + 1});
                    }
                }
                word[i] = originalChar;
            }
        }

        return 0;
    }
};
