#include "utils/LRUMapCache.hpp"
#include <vector>

Map *LRUMapCache::Get(const std::string &key) {
  auto it = cache.find(key);

  if (it == cache.end())
    return nullptr;

  // move to the front sence RU
  usage.erase(it->second.usageIt);
  usage.push_front(key);
  it->second.usageIt = usage.begin();

  return it->second.map.get();
}

std::vector<Map *> LRUMapCache::GetAll() {
  std::vector<Map *> result;
  result.reserve(cache.size());
  for (const auto &[key, entry] : cache) {
    result.push_back(entry.map.get());
  }

  return result;
}

void LRUMapCache::Put(const std::string &key, std::unique_ptr<Map> map) {

  auto it = cache.find(key);

  if (it != cache.end()) {
    usage.erase(it->second.usageIt);
    usage.push_front(key);
    it->second.usageIt = usage.begin();
    it->second.map = std::move(map);
    return;
  }

  if (cache.size() > maxSize)
    EvictLRU();

  usage.push_front(key);
  cache[key] = {std::move(map), usage.begin()};
}

bool LRUMapCache::Contains(const std::string &key) {
  return cache.find(key) != cache.end();
}

void LRUMapCache::EvictLRU() {
  auto lruKey = usage.back();
  usage.pop_back();

  auto it = cache.find(lruKey);
  if (it != cache.end()) {
    cache.erase(it);
  }
}
