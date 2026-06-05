#pragma once
#include "Hash.hpp"

#include <array>
#include <cstddef>
template <typename K, typename V> struct KeyValuePair {
  K key;
  V value;
  KeyValuePair *next;

  KeyValuePair(const K &key_, const V &value_)
      : key(key_), value(value_), next(nullptr) {};
};

template <typename K, typename V, int Capacity = 128> class Dictionary {
protected:
  std::array<KeyValuePair<K, V> *, Capacity> table;

public:
  Dictionary() {
    for (size_t i = 0; i < Capacity; i++)
      table[i] = nullptr;
  }
  ~Dictionary() {
    for (size_t i = 0; i < Capacity; i++) {
      KeyValuePair<K, V> *next = table[i];
      while (next->next != nullptr) {
        KeyValuePair<K, V> *prev = next;
        next = next->next;
        delete prev;
      }
      table[i] = nullptr;
    }
  }

  size_t hash(const K &key) const;
  void insert(const K &key, const V &value);
};

template <typename K, typename V, int Capacity>
size_t Dictionary<K, V, Capacity>::hash(const K &key) const {
  static Hash<K> hasher;
  return hasher(key) % Capacity;
}

template <typename K, typename V, int Capacity>
void Dictionary<K, V, Capacity>::insert(const K &key, const V &value) {

  size_t hash_ = hash(key);
  KeyValuePair<K, V> *new_key_value = new KeyValuePair<K, V>(key, value);

  if (table[hash_] == nullptr)
    table[hash_] = new_key_value;
  else {
    KeyValuePair<K, V> *current_node = table[hash_];
    while (current_node->next != nullptr) {
      current_node = current_node->next;
    }
    current_node->next = new_key_value;
  }
}
