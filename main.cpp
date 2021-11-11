#include <iostream>
#include <sys/utsname.h>
#include <vector>
#include "src/utils.h"

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

int force_env_level() {
  const char *envp = std::getenv("FORCE_COLOR");
  if (!envp) return -1;
  return strcmp(envp, "true") != 0 ? 1 : strcmp(envp, "false") != 0 ? 0 :
      strlen(envp) == 0 ? 1 : std::min(str_convert<int>(envp), 3);
}



int main(const int argc, const char **argv) {
  struct utsname name{};
  if (uname(&name)) exit(1);
  std::ios::sync_with_stdio(false);

  std::vector<int> f = {2, 3, 4, 5};
  std::vector<int> s = {10, 11, 12, 13, 14};
  std::vector<std::string> s2 = {"Yo", "Men", "Another"};

  std::vector<std::string> arguments(argv + 1, argv + argc);
  std::cout << has_colors(arguments) << std::endl;
  std::string s23 = "test";

  std::cout << s23.ends_with("st") << std::endl;

  return 0;
}
