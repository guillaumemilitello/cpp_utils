#pragma once

#include <string>
#include <sstream>
#include <random>
#include <functional>
#include <unordered_set>

namespace uuid
{
    static std::random_device              rd;
    static std::mt19937                    gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    static std::uniform_int_distribution<> dis2(8, 11);

    std::string generate_uuid_v4()
    {
        std::stringstream ss;
        int i;
        ss << std::hex;
        for (i = 0; i < 8; i++) { ss << dis(gen); }
        ss << "-";
        for (i = 0; i < 4; i++) { ss << dis(gen); }
        ss << "-4";
        for (i = 0; i < 3; i++) { ss << dis(gen); }
        ss << "-";
        ss << dis2(gen);
        for (i = 0; i < 3; i++) { ss << dis(gen); }
        ss << "-";
        for (i = 0; i < 12; i++) { ss << dis(gen); }
        return ss.str();
    }
}

struct Key
{
  int         _first;
  float       _second;
  std::string _third;

  bool operator==(const Key &other_) const
  {
    return _first == other_._first && _second == other_._second && _third == other_._third;
  }
};

struct Hashable
{
  const std::string _hashKey = uuid::generate_uuid_v4();
};

struct KeyHashable : public Hashable
{
  int         _first;
  float       _second;
  std::string _third;

  bool operator==(const Key &other_) const
  {
    return _first == other_._first && _second == other_._second && _third == other_._third;
  }
};

namespace std
{
  template <>
  struct hash<Key>
  {
    std::size_t operator()(const Key& k_) const
    {
      // Compute individual hash values for first, second and third and combine them using XOR and bit shifting:
      return ((std::hash<int>()(k_._first)
               ^ (std::hash<float>()(k_._second) << 1)) >> 1)
               ^ (std::hash<std::string>()(k_._third) << 1);
    }
  };

  template <>
  struct hash<Hashable>
  {
    std::size_t operator()(const Hashable& hashable_) const
    {
        return std::hash<std::string>()(hashable_._hashKey);
    }
  };
}

std::unordered_set<Key> hashSetKey;

std::unordered_set<Hashable> hashSetHashable;

// need specification, we are only allowed to write template specialization for std::hash
std::unordered_set<KeyHashable, std::hash<Hashable>> hashSetKeyHashable;
