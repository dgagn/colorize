#include <vector>

template<typename T>
std::vector<T> merge(const std::vector<T> &first,
    const std::vector<T> &second) {
  std::vector<T> merged;
  merged.reserve(first.size() + second.size());
  merged.insert(merged.end(), first.begin(), first.end());
  merged.insert(merged.end(), second.begin(), second.end());
  return merged;
}
