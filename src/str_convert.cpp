#include <string>
#include <concepts>
#include <sstream>

template<typename T>
concept arithmetic = std::is_integral_v<T> or std::is_floating_point_v<T>;

template<typename T>
requires arithmetic<T> T str_convert(const std::string &ref) {
  T result;
  std::string s(ref);
  s.erase(s.find_last_not_of(" \f\n\r\t\v") + 1);
  std::stringstream ss(s);
  ss >> result;
  if (!ss.eof()) throw std::runtime_error("Argument is not of type uint64_t.");
  return result;
}
