#include <sys/utsname.h>

#include <concepts>
#include <iostream>
#include <sstream>
#include <vector>

template<typename T>
int index_of(const std::vector<T> &vec, const T &value) {
  auto itr = std::find(vec.begin(), vec.end(), value);
  uint32_t position = itr - vec.begin();
  return itr == vec.end() ? -1 : (int) position;
}

bool has_flag(const std::string &flag, const std::vector<std::string> &argv) {
  std::string prefix = flag.starts_with('-') ? ""
      : flag.length() == 1 ? "-"
          : "--";
  int position = index_of<std::string>(argv, prefix + flag);
  int terminator = index_of<std::string>(argv, "--");
  return position != -1 && (terminator == -1 || position < terminator);
}

bool has_colors(const std::vector<std::string> &argv) {
  return has_flag("no-color", argv) || has_flag("no-colors", argv) ||
      has_flag("color=false", argv) || has_flag("color=never", argv);
}

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

int force_env_level() {
  const char *envp = std::getenv("FORCE_COLOR");

  if (!envp) return -1;

  return strcmp(envp, "true") != 0 ? 1 : strcmp(envp, "false") != 0 ? 0 :
      strlen(envp) == 0 ? 1 : std::min(str_convert<int>(envp), 3);
}

int main(const int argc, const char **argv) {
  struct utsname name{};
  if (uname(&name)) exit(1);

  std::cout << force_env_level() << std::endl;

  std::vector<std::string> arguments(argv + 1, argv + argc);
  std::cout << has_colors(arguments) << std::endl;

  return 0;
}
