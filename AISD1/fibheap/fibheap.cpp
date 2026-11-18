#include "fibheap.hpp"
#include <stack>

Node *Node::Merge(Node *otherNode) {
  Node *p = this;
  if (otherNode->GetKey() > this->GetKey()) {
    otherNode->SetRight(p->GetRight());
    p->SetRight(nullptr);
    std::swap(p, otherNode);
  }

  p->IncreaseHeight();
  p->AddToEnd(otherNode);
  return p;
}

void Node::AddToEnd(Node *otherNode) {
  otherNode->SetParent(this);
  otherNode->SetRight(nullptr);

  if (GetChild() != nullptr) {
    Node *tail = GetChild()->GetLeft();
    GetChild()->GetLeft()->SetRight(otherNode);
    otherNode->SetLeft(tail);
    GetChild()->SetLeft(otherNode);
  } else {
    SetChild(otherNode);
    otherNode->SetLeft(otherNode);
  }
}

FibHeap::~FibHeap() {
  std::stack<Node *> freeStack;

  while (head != nullptr) {
    freeStack.push(head);
    head = head->GetRight();
  }
  while (!freeStack.empty()) {
    Node *currentNode = freeStack.top();
    freeStack.pop();

    Node *child = currentNode->GetChild();
    while (child != nullptr) {
      freeStack.push(child);
      child = child->GetRight();
    }

    delete currentNode;
  }
}

void FibHeap::Union(FibHeap *otherHeap) {

  if (otherHeap == nullptr || otherHeap == this ||
      otherHeap->GetHead() == nullptr)
    return;
  if (GetHead() == nullptr) {
    SetHead(otherHeap->GetHead());
    SetMaxKey(otherHeap->GetMaxKey());
    otherHeap->SetHead(nullptr);
    otherHeap->SetMaxKey(nullptr);
    return;
  }

  if (otherHeap->GetMaxKey()->GetKey() > this->GetMaxKey()->GetKey()) {
    this->SetMaxKey(otherHeap->GetMaxKey());
  }

  Node *thisTail = this->GetHead()->GetLeft();
  Node *otherTail = otherHeap->GetHead()->GetLeft();

  //  przepinanie wskaźników
  this->GetHead()->SetLeft(otherTail);
  thisTail->SetRight(otherHeap->GetHead());
  otherHeap->GetHead()->SetLeft(thisTail);

  otherHeap->SetHead(nullptr);
  otherHeap->SetMaxKey(nullptr);

  return;
}
void FibHeap::AddNode(Node *newNode) {

  if (newNode == nullptr)
    return;

  if (head == nullptr) {
    newNode->SetLeft(newNode);
    newNode->SetRight(nullptr);
    SetHead(newNode);
    SetMaxKey(newNode);
    return;
  }

  if (newNode->GetKey() > this->GetMaxKey()->GetKey()) {
    this->SetMaxKey(newNode);
  }

  Node *thisTail = this->GetHead()->GetLeft();
  this->GetHead()->SetLeft(newNode);
  thisTail->SetRight(newNode);
  newNode->SetLeft(thisTail);

  return;
}

Node *FibHeap::DeleteMax() {
  Node *oldMax = this->GetMaxKey();

  if (oldMax == nullptr || GetHead() == nullptr)
    return nullptr;

  Node *child = oldMax->GetChild();
  while (child != nullptr) {
    Node *nextChild = child->GetRight();
    child->SetRight(nullptr);
    child->SetLeft(child);
    child->SetParent(nullptr);
    AddNode(child);
    child = nextChild;
  }

  if (oldMax == head && oldMax->GetRight() == nullptr) {
    SetHead(nullptr);
    SetMaxKey(nullptr);
    oldMax->CutFromHeap();
    return oldMax;
  }

  Node *leftNode = oldMax->GetLeft();
  Node *rightNode = oldMax->GetRight();

  if (oldMax == head) {
    SetHead(rightNode);
    rightNode->SetLeft(
        leftNode); // nowy head->left musi wskazywać na ogon listy!
  } else {
    leftNode->SetRight(rightNode);
    if (rightNode != nullptr) {
      rightNode->SetLeft(leftNode);
    } else {
      head->SetLeft(leftNode); // oldMax był ogonem listy
    }
  }

  oldMax->CutFromHeap();
  this->Consolidate();

  return oldMax;
}

void FibHeap::Consolidate() {

  depthArray.fill(nullptr);
  Node *currentNode = this->GetHead();

  while (currentNode != nullptr) {
    while (depthArray[currentNode->GetHeight()] != nullptr) {
      Node *nodeToMerge = depthArray[currentNode->GetHeight()];
      Node *nodeToMerge2 = currentNode;
      depthArray[currentNode->GetHeight()] = nullptr;

      currentNode = nodeToMerge2->Merge(nodeToMerge);
    }
    depthArray[currentNode->GetHeight()] = currentNode;
    currentNode = currentNode->GetRight();
  }

  SetHead(nullptr);
  SetMaxKey(nullptr);

  for (size_t i = 0; i < GetMaxDepth(); i++) {
    if (head == nullptr && depthArray[i] != nullptr) {
      depthArray[i]->SetLeft(depthArray[i]);
      depthArray[i]->SetRight(nullptr);
      depthArray[i]->SetParent(nullptr);

      SetHead(depthArray[i]);
      SetMaxKey(depthArray[i]);

      continue;
    }
    if (depthArray[i] != nullptr) {
      depthArray[i]->SetLeft(depthArray[i]);
      depthArray[i]->SetRight(nullptr);
      depthArray[i]->SetParent(nullptr);
      AddNode(depthArray[i]);
    }
  }
}