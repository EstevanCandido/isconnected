#include <iostream>
#include <chrono>
#include <cstdio>
#include <regex>

void checkInternetConnection() {
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();
  std::string response = "";
  char buffer[1024];
  FILE *pipes = popen("ping google.com -c 1", "r");
  if (!pipes) {
    std::cout << "0" << std::endl;
    return;
  }
  while (!feof(pipes)) {
    if (fgets(buffer, 1024, pipes) != NULL)
      response += buffer;
  }
  end = std::chrono::system_clock::now();
  std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

  std::regex pattern("time=([0-9.]+)");
  std::smatch matches;
  if (std::regex_search(response, matches, pattern)) {
    std::cout << "1" << std::endl;
    std::cout << "Response time: " << matches[1].str() << " milliseconds" << std::endl;
  } else {
    std::cout << "0" << std::endl;
  }
  pclose(pipes);
}

int main() {
  checkInternetConnection();
  return 0;
}
