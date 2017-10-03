#include <fstream>
#include <iostream>
#include <wordexp.h>

std::string get_path() {
  wordexp_t p;
  char **w;
  std::string result;
  wordexp("~/.emacs.d/projectile-bookmarks.eld", &p, 0);
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
}

int main() {
  std::string projectile_bookmarks = get_path();
  std::ifstream file{projectile_bookmarks};
  std::string dir;

  if (file.is_open()) {

    while (!file.eof()) {
      file >> dir;
      sanitize_dir(dir);
      std::cout << dir << std::endl;
    }
  } else {
    std::cout << "Couldn't open projectile repository bookmarks" << std::endl;
  }
  return 0;
}
