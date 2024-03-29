#include <fstream>
#include <iostream>
#include <sstream>
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

  if (file.is_open()) {
    std::string content;
    getline(file, content);
    std::stringstream ss{content};

    while (!ss.eof()) {
      std::string dir;
      ss >> dir;
      while (dir.back() != '"' && dir.back() != ')') {
        std::string rest;
        ss >> rest;
        dir += "\\ " + rest;
        std::cout << dir << std::endl;
      }
      sanitize_dir(dir);
      git_fetch(dir);
    }
  } else {
    std::cout << "Couldn't open projectile repository bookmarks" << std::endl;
  }
  return 0;
}
