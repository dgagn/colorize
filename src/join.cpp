#include <sstream>
#include <vector>
#include <string>

template<typename T>
std::string join(const std::vector<T> &vec, const std::string &delimiter = "") {
  if(vec.empty()) return "";
  std::ostringstream oss;
  std::copy(vec.begin(), vec.end() - 1, std::ostream_iterator<T>(oss, delimiter.c_str()));
  oss << vec.back();
  return oss.str();
}