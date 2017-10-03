#include <chrono>
#include <fstream>
#include <future>
#include <iostream>
#include <unistd.h>
#include <vector>
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

std::future<int> git_fetch(const std::string &dir) {
  chdir(dir.c_str());
  std::cout << "Starting git fetch for " << dir << std::endl;
  return std::async(system, "git fetch --all");
}

int main() {
  std::string projectile_bookmarks =
      get_path("~/.emacs.d/projectile-bookmarks.eld");
  std::ifstream file{projectile_bookmarks};
  std::string dir;
  std::vector<std::future<int>> v{};

  if (file.is_open()) {
    while (!file.eof()) {
      file >> dir;
      sanitize_dir(dir);
      v.push_back(git_fetch(dir));
    }

    for (auto &f : v) {
      f.wait_for(std::chrono::seconds(60));
    }

  } else {
    std::cout << "Couldn't open projectile repository bookmarks" << std::endl;
  }
  return 0;
}
