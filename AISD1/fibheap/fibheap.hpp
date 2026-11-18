#pragma once

#include <array>
#include <unordered_map>
#include <vector>

class Node {
private:
  int key;
  int height;
  bool marked;
  Node *parent;
  Node *child;
  Node *left;
  Node *right;

public:
  Node(const int key_, Node *parent_ = nullptr)
      : key(key_), parent(parent_), height(0), marked(false), child(nullptr),
        left(this), right(nullptr) {}

  const Node *GetLeft() const { return left; }
  const Node *GetRight() const { return right; }
  const Node *GetChild() const { return child; }
  const Node *GetParent() const { return parent; }

  Node *GetLeft() { return left; }
  Node *GetRight() { return right; }
  Node *GetChild() { return child; }
  Node *GetParent() { return parent; }

  void SetLeft(Node *p) { left = p; }
  void SetRight(Node *p) { right = p; }
  void SetChild(Node *p) { child = p; }
  void SetParent(Node *p) { parent = p; }

  const int GetKey() const { return key; }
  const int GetHeight() const { return height; }
  const bool Getmarked() const { return marked; }

  int GetKey() { return key; }
  int GetHeight() { return height; }
  bool GetMarked() { return marked; }

  void SetKey(int newKey) { key = newKey; }
  void IncreaseHeight() { height++; }
  void SetMarked(bool newMarked) { marked = newMarked; }

  void CutFromHeap() {
    parent = nullptr;
    child = nullptr;
    left = this;
    right = nullptr;
  };

  Node *Merge(Node *otherNode);
  void AddToEnd(Node *otherNode);

  ~Node() = default;
};

class FibHeap {
private:
  static constexpr int MAXDEPTH = 64;
  std::array<Node *, MAXDEPTH> depthArray;
  Node *maxKey;
  Node *head;

  void SetMaxKey(Node *newMax) { maxKey = newMax; }
  void SetHead(Node *newHead) { head = newHead; }
  void Consolidate();

public:
  FibHeap(const FibHeap &) = delete;
  FibHeap &operator=(const FibHeap &) = delete;
  FibHeap(Node *head_ = nullptr) : maxKey(head_), head(head_) {};

  static const int GetMaxDepth() { return MAXDEPTH; }

  const Node *GetMaxKey() const { return maxKey; }
  Node *GetMaxKey() { return maxKey; }

  const Node *GetHead() const { return head; }
  Node *GetHead() { return head; }

  void Union(FibHeap *otherHeap);
  Node *DeleteMax();
  //  void IncreaseKey(const int oldKey, const int newKey);

  void AddNode(Node *newNode);

  ~FibHeap();
};