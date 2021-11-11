#include <vector>

template<typename T>
int index_of(const std::vector<T> &vec, const T &value) {
  auto itr = std::find(vec.begin(), vec.end(), value);
  uint32_t position = itr - vec.begin();
  return itr == vec.end() ? -1 : (int) position;
}
