#pragma once
#include "Hash.hpp"
#include <array>
#include <cstddef>
#include <iostream>
#include <optional>

template <typename K, typename V> struct KeyValuePair {
  K key;
  V value;
  KeyValuePair<K, V> *next;

  KeyValuePair(const K &key_, const V &val_)
      : key(key_), value(val_), next(nullptr) {};
};

template <typename K, typename V, int Capacity = 128> class Dictionary {
private:
  std::array<KeyValuePair<K, V> *, Capacity> table;
  size_t hash(const K &key) const;

public:
  Dictionary();
  ~Dictionary();

  V &operator[](const K &key);

  void insert(const K &key, const V &value);
  std::optional<V> get(const K &key) const;
  bool remove(const K &key);

  template <typename _K, typename _V, int _Capacity>
  friend std::ostream &operator<<(std::ostream &os,
                                  const Dictionary<_K, _V, _Capacity> &d);
};

template <typename K, typename V, int Capacity>
Dictionary<K, V, Capacity>::Dictionary() {
  for (size_t i = 0; i < Capacity; i++)
    table[i] = nullptr;
}

template <typename K, typename V, int Capacity>
Dictionary<K, V, Capacity>::~Dictionary() {
  for (size_t i = 0; i < Capacity; i++) {
    KeyValuePair<K, V> *next = table[i];
    while (next) {
      KeyValuePair<K, V> *prev = next;
      next = next->next;
      delete prev;
    }

    table[i] = nullptr;
  }
}

template <typename K, typename V, int Capacity>
size_t Dictionary<K, V, Capacity>::hash(const K &key) const {
  static Hash<K> hasher;
  return hasher(key) % Capacity;
}

template <typename K, typename V, int Capacity>
void Dictionary<K, V, Capacity>::insert(const K &key, const V &value) {

  size_t index = hash(key);
  KeyValuePair<K, V> *prev = nullptr;
  KeyValuePair<K, V> *entry = table[index];

  while (entry != nullptr && entry->key != key) {
    prev = entry;
    entry = entry->next;
  }

  if (entry == nullptr) {
    entry = new KeyValuePair<K, V>(key, value);
    if (prev == nullptr) {
      table[index] = entry;
    } else {
      prev->next = entry;
    }
  } else {
    entry->value = value;
  }
}

template <typename K, typename V, int Capacity>
std::ostream &operator<<(std::ostream &os,
                         const Dictionary<K, V, Capacity> &d) {
  for (int i = 0; i < Capacity; ++i) {
    KeyValuePair<K, V> *entry = d.table[i];
    while (entry != nullptr) {
      os << entry->key << ": " << entry->value << std::endl;
      entry = entry->next;
    }
  }
  return os;
}

template <typename K, typename V, int Capacity>
V &Dictionary<K, V, Capacity>::operator[](const K &key) {
  size_t hash_ = hash(key);

  KeyValuePair<K, V> *itr = table[hash_];
  while (itr) {
    if (itr->key == key)
      return itr->value;
    itr = itr->next;
  }
  insert(key, V());

  hash_ = hash(key);
  itr = table[hash_];
  while (itr) {
    if (itr->key == key)
      return itr->value;
    itr = itr->next;
  }
}

template <typename K, typename V, int Capacity>
std::optional<V> Dictionary<K, V, Capacity>::get(const K &key) const {
  size_t hash_ = hash(key);

  KeyValuePair<K, V> *itr = table[hash_];
  while (itr) {
    if (itr->key == key)
      return itr->value;
    itr = itr->next;
  }

  return std::nullopt;
}

template <typename K, typename V, int Capacity>
bool Dictionary<K, V, Capacity>::remove(const K &key) {

  size_t hash_ = hash(key);
  KeyValuePair<K, V> *itr = table[hash_];
  KeyValuePair<K, V> *prev = nullptr;

  while (itr) {
    if (itr->key == key) {
      if (prev == nullptr)
        table[hash_] = itr->next;
      else
        prev->next = itr->next;
      delete itr;
      return true;
    }
    prev = itr;
    itr = itr->next;
  }

  return false;
}