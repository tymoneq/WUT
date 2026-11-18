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

  // 1. Wstawienie pierwszych 18 elementów
  std::vector<int> batch1 = {14, 88, 3,  47, 62, 19, 95, 5,  31,
                             74, 28, 53, 11, 82, 40, 67, 23, 91};

  std::cout << ">>> Etap 1: Dodanie 18 elementow:\n";
  for (int val : batch1) {
    heap.AddNode(new Node(val));
  }
  PrintHeap(heap);

  // 2. Seria 3 usunięć:
  // Po 1. DeleteMax zostaje 17 elem. -> drzewa o wysokościach: h=0, h=4
  // Po 2. DeleteMax zostaje 16 elem. -> jedno drzewo: h=4
  // Po 3. DeleteMax zostaje 15 elem. -> 4 drzewa różnych rozmiarów: h=0, h=1, h=2, h=3
  std::cout << ">>> Etap 2: 3x DeleteMax (dojscie do 15 elementow -> h=0,1,2,3):\n";
  for (int i = 0; i < 3; ++i) {
    RemoveAndPrintMax(heap);
  }

  // 3. Dorzucenie kolejnych 6 elementów w trakcie działania (razem 24 utworzone, 21 w kopcu)
  std::vector<int> batch2 = {50, 12, 99, 34, 71, 8};
  std::cout << ">>> Etap 3: Dodanie 6 nowych elementow (50, 12, 99, 34, 71, 8):\n";
  for (int val : batch2) {
    heap.AddNode(new Node(val));
  }
  PrintHeap(heap);

  // Jedno DeleteMax (zostaje 20 elem. -> drzewa h=2 oraz h=4)
  RemoveAndPrintMax(heap);

  // 4. Stworzenie drugiego kopca z ostatnich 6 elementów (łącznie 30 elementów) i scalenie (Union)
  FibHeap extraHeap;
  std::vector<int> batch3 = {60, 17, 85, 42, 9, 77};
  std::cout << ">>> Etap 4: Budowa drugiego kopca z 6 elementow i jedno DeleteMax:\n";
  for (int val : batch3) {
    extraHeap.AddNode(new Node(val));
  }
  Node *extraMax = extraHeap.DeleteMax(); // zostaje 5 elem. -> drzewa h=0 oraz h=2
  std::cout << ">>> Usunieto max z extraHeap: " << extraMax->GetKey() << "\n";
  delete extraMax;
  PrintHeap(extraHeap);

  std::cout << ">>> Etap 5: Union obu kopcow (25 elementow, mieszanka wysokosci):\n";
  heap.Union(&extraHeap);
  PrintHeap(heap);

  // 5. Kolejne aktualizacje: usunięcie 2 elementów (23 elem. -> h=0, h=1, h=2, h=4),
  // a następnie opróżnienie całego kopca z podglądem każdego kroku
  std::cout << ">>> Etap 6: Stopniowe oproznianie calego kopca:\n";
  while (heap.GetMaxKey() != nullptr) {
    RemoveAndPrintMax(heap);
  }

  return 0;
}