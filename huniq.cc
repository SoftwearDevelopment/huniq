#include <iostream>
#include <string>
#include <utility>
#include <array>

#include <tsl/sparse_map.h>
#include <tsl/sparse_set.h>

#include <metrohash128.h>

void help() {
  // TODO: Can we somehow extract this from the readme?
  std::cerr <<
    "\n# huniq"
    "\n"
    "\nSimplified version of the uniq(1) tool, that uses a hash"
    "\ntable internally to remove and count duplicates."
    "\n"
    "\n# usage"
    "\n"
    "\n  `$ huniq [-c|--count] [-h|--help] < FILE > FILE`"
    "\n"
    "\n-c and --count can be used to indicate that duplicate elements should be"
    "\ncounted."
    "\n-h and --help will display this help page"
    "\n"
    "\n# why?"
    "\n"
    "\nThis is useful for replacing the `sort | uniq -c`, `sort | uniq` or `sort -u`"
    "\nin cases where sorting is not required."
    "\n"
    "\n`huniq -c` and `huniq` are both generally faster and use less memory than"
    "\ntheir counterparts, this is achieved by using a couple of optimizations:"
    "\n"
    "\nA hash table is used to store duplicates instead of sorting the input;"
    "\nthis increases performance, since hashing is usually faster than sorting."
    "\nIt also means that duplicates do not have to be stored individually (they"
    "\nall occupy the same hash bucket), so the memory requirements grow with the"
    "\nsize of the output and not the input. E.g. if each line in the input has a"
    "\none duplicate at average, we need 50% less memory."
    "\n"
    "\n`huniq` also does not store the actual lines themselves, instead it just stores"
    "\na hash value (16 byte each) of that line. This is especially very useful when very"
    "\nlong lines are in the input."
    "\n"
    "\n`huniq` outputs lines in the order they where given, while `huniq -c` returns lines"
    "\nin arbitrary order."
    "\nhuniq does not swap data to disk like gnu sort does, so for that reason it sometimes"
    "\nalso uses more memory than sort, especially when there are many items and not many duplicates."
    "\n"
    "\nNote that huniq generally has no advantage to just using"
    "\n`uniq` without the sort, since uniq just removes consecutive"
    "\nduplicates so it just needs to keep a single line in memory."
    "\n";
}

typedef std::array<uint64_t, 2> murmurhash_t;

struct murmuridentity_64 {
  size_t operator()(const murmurhash_t &v) const {
    return v[0];
  }
};

std::ostream& operator<<(std::ostream& os, const std::pair<std::string, size_t> &p) {
  os << std::get<1>(p) << "  " << std::get<0>(p);
  return os;
}

void uniq() {
  tsl::sparse_set<murmurhash_t, murmuridentity_64> set;

  std::string el;
  murmurhash_t hash;
  while (std::getline(std::cin, el)) {
    // NOTE: We have to use a decent hash function, because we
    // will be using the entropy that is in the hash for collision
    // detection.
    // It has to be 128 bits because of the birthday problem.
    MetroHash128::Hash((const uint8_t*)el.data(), el.size(), (uint8_t*)hash.data());
    auto res = set.insert(hash);
    if (std::get<1>(res))
      std::cout << el << '\n';
  }
}

void uniq_count() {
  std::string el;
  tsl::sparse_map<std::string, size_t> map;

  while (std::getline(std::cin, el)) {
    auto r = map.try_emplace(std::move(el), 0);
    auto &pair  = *(std::get<0>(r));
    auto &count = const_cast<size_t&>(std::get<1>(pair));
    // TODO: Why is the const_cast necessary?
    count++;
  }
  
  for (auto &e : map)
    std::cout << e << '\n';
}

int main(int argc, char **argv) {
  bool count=false;

  for (int n=1; n<argc; n++) {
    std::string a{argv[n]};
    if (a == "--help" || a == "-h") {
      help();
      return 0;
    } else if (a == "--count" || a == "-c") {
      count = true;
    } else {
      std::cerr << "Invalid argument: " << a << "\n\n";
      help();
      return 10;
    }
  }

  if (count) uniq_count();
  else uniq();

  return 0;
}
