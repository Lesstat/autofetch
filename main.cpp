#include <fstream>
#include <iostream>
#include <wordexp.h>

std::string get_path(const char *path) {
  wordexp_t p;
  char **w;
  std::string result;
  wordexp(path, &p, 0);
  w = p.we_wordv;
  result = w[0];
  wordfree(&p);
  return result;
}

void sanitize_dir(std::string &dir) {
  if (dir.front() == '(')
    dir.erase(0, 2);
  else
    dir.erase(0, 1);
  if (dir.back() == ')') {
    dir.pop_back();
  }
  dir.pop_back();
  dir = get_path(dir.c_str());
}

void git_fetch(const std::string &dir) {
  std::cout << "Starting git fetch for " << dir << std::endl;
  std::string git_command{"setsid git -C "};
  git_command += dir;
  git_command += " fetch --all";
  system(git_command.c_str());
}

int main() {
  std::string projectile_bookmarks =
      get_path("~/.emacs.d/projectile-bookmarks.eld");
  std::ifstream file{projectile_bookmarks};
  std::string dir;

  if (file.is_open()) {
    while (!file.eof()) {
      file >> dir;
      sanitize_dir(dir);
      git_fetch(dir);
    }
  } else {
    std::cout << "Couldn't open projectile repository bookmarks" << std::endl;
  }
  return 0;
}
