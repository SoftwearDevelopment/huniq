#include <iostream>
#include <string>
#include <utility>

#include <tsl/sparse_map.h>
#include <tsl/sparse_set.h>


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
    "\nThis is useful for replacing the `sort | uniq -c` pattern"
    "\nin cases where the input is very large (larger than ram)"
    "\nbut the uniqed output is mach smaller:"
    "\n"
    "\nThe sort step above needs to load the entire input data into"
    "\nmemory, so the amount of memory is roughly equal to the size"
    "\nof the input data. huniq already deduplicates the data in"
    "\nmemory, so it's memory requirement is roughly equal to that"
    "\nof the deduped output."
    "\n"
    "\nNote that huniq generally has no advantage to just using"
    "\n`uniq` without the sort, since uniq just removes consecutive"
    "\nduplicates so it just needs to keep a single line in memory."
    "\n"
    "\nhuniq returns the input data in arbitrary order."
    "\n";
}

template<typename T>
struct uniq_set : tsl::sparse_set<T> {
  template<typename Arg>
  void add(Arg&& arg) {
    this->insert(std::forward<Arg>(arg));
  }
};

template<typename T>
struct count_uniq_set : tsl::sparse_map<T, size_t> {
  template<typename Arg>
  void add(Arg&& arg) {
    auto r = this->try_emplace(std::forward<Arg>(arg), 0);
    auto &pair  = *(std::get<0>(r));
    auto &count = const_cast<size_t&>(std::get<1>(pair));
    // TODO: Why is the const_cast necessary?
    count++;
  }
};

std::ostream& operator<<(std::ostream& os, const std::pair<std::string, size_t> &p) {
  os << std::get<1>(p) << "  " << std::get<0>(p);
  return os;
}

template<typename Range>
void uniq(Range &&r) {
  std::string el;
  while (std::getline(std::cin, el)) r.add(std::move(el));
  
  for (auto &e : r) std::cout << e << "\n";
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

  if (count) uniq(count_uniq_set<std::string>{});
  else       uniq(uniq_set<std::string>{});

  return 0;
}
