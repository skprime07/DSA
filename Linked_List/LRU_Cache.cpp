/*
Problem: LeetCode 146 – LRU Cache

Approach:
- Use HashMap + Doubly Linked List.
- HashMap: key → Node (O(1) access)
- Doubly Linked List:
    → Most Recently Used near head
    → Least Recently Used near tail

Operations:
GET(key):
    - If key not present → return -1
    - Else move node to head and return value

PUT(key, value):
    - If key exists → update value + move to head
    - Else:
        → Create new node
        → Add to head
        → If capacity exceeded:
            remove node just before tail (LRU)

Dummy head & tail simplify edge cases.

Time Complexity:
GET → O(1)
PUT → O(1)

Space Complexity: O(N)
*/

struct Node {
    int key, value;
    Node* prev;
    Node* next;

    Node(int _key, int _value) {
        key = _key;
        value = _value;
        prev = next = nullptr;
    }
};

class LRUCache {
private:
    int capacity;
    unordered_map<int, Node*> cache;
    Node* head;
    Node* tail;

    // Insert node right after head (Most Recently Used)
    void addToHead(Node* node) {
        node->next = head->next;
        node->prev = head;

        head->next->prev = node;
        head->next = node;
    }

    // Remove node from linked list
    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    // Move existing node to head
    void moveToHead(Node* node) {
        removeNode(node);
        addToHead(node);
    }

    // Remove Least Recently Used node
    Node* removeTail() {
        Node* node = tail->prev;
        removeNode(node);
        return node;
    }

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        // Dummy nodes
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (cache.find(key) == cache.end())
            return -1;

        Node* node = cache[key];
        // Mark as recently used
        moveToHead(node);
        return node->value;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            // Update existing key
            Node* node = cache[key];
            node->value = value;
            moveToHead(node);
        } else {
            // Insert new key
            Node* newNode = new Node(key, value);
            cache[key] = newNode;
            addToHead(newNode);

            // Remove LRU if capacity exceeded
            if (cache.size() > capacity) {
                Node* tailNode = removeTail();
                cache.erase(tailNode->key);
                delete tailNode;
            }
        }
    }
};
