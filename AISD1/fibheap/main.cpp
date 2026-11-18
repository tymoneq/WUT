#include "fibheap.hpp"
#include <iostream>
#include <string>
#include <vector>

void PrintSubtree(const Node *node, const Node *maxNode,
                  const std::string &prefix, bool isLast) {
  if (node == nullptr)
    return;

  std::cout << prefix << (isLast ? "└── " : "├── ") << node->GetKey()
            << " (h=" << node->GetHeight() << ")";

  if (node == maxNode) {
    std::cout << " [MAX]";
  }
  std::cout << "\n";

  const Node *child = node->GetChild();
  while (child != nullptr) {
    const Node *nextChild = child->GetRight();
    PrintSubtree(child, maxNode, prefix + (isLast ? "    " : "│   "),
                 nextChild == nullptr);
    child = nextChild;
  }
}

void PrintHeap(const FibHeap &heap) {
  std::cout << "=== FibHeap ===\n";
  const Node *curr = heap.GetHead();
  if (curr == nullptr) {
    std::cout << "(pusty)\n\n";
    return;
  }

  const Node *maxNode = heap.GetMaxKey();
  while (curr != nullptr) {
    const Node *nextRoot = curr->GetRight();
    PrintSubtree(curr, maxNode, "", nextRoot == nullptr);
    curr = nextRoot;
  }
  std::cout << "\n";
}

void RemoveAndPrintMax(FibHeap &heap) {
  Node *maxNode = heap.DeleteMax();
  if (maxNode != nullptr) {
    std::cout << ">>> Usunieto max: " << maxNode->GetKey() << "\n";
    delete maxNode;
    PrintHeap(heap);
  }
}

int main() {
  FibHeap heap;

  std::vector<int> values = {10, 4, 25, 7, 30, 15, 42, 3, 18, 2137};

  std::cout << "Dodawanie elementow:\n";
  for (int val : values) {
    heap.AddNode(new Node(val));
  }
  PrintHeap(heap);

  // Usunięcie 4 największych elementów z podglądem po każdym kroku
  for (int i = 0; i < 4; ++i) {
    RemoveAndPrintMax(heap);
  }

  std::cout << ">>> Dodanie nowych elementow (50, 12):\n";
  heap.AddNode(new Node(50));
  heap.AddNode(new Node(12));
  PrintHeap(heap);

  // Opróżnienie reszty kopca z podglądem po każdym usunięciu
  std::cout << "Oproznianie reszty kopca:\n";
  while (heap.GetMaxKey() != nullptr) {
    RemoveAndPrintMax(heap);
  }

  return 0;
}