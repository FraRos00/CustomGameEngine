#pragma once

#include "utils/Map.hpp"
#include <cstddef>
#include <list>
#include <memory>
#include <string>
#include <unordered_map>
class LRUMapCache {

public:
  LRUMapCache(size_t maxSize) : maxSize(maxSize) {}

  Map *Get(const std::string &key);

  void Put(const std::string &key, std::unique_ptr<Map> map,
           const std::string &currentMap);

  bool Contains(const std::string &key);

  std::vector<Map *> GetAll();

private:
  struct Entry {
    std::unique_ptr<Map> map;
    std::list<std::string>::iterator usageIt;
  };

  std::unordered_map<std::string, Entry> cache;
  std::list<std::string> usage;

  size_t maxSize = 5;

  void EvictLRU(const std::string &currentMap);
};
