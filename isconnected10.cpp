#include <iostream>
#include <chrono>
#include <cstdio>
#include <regex>
#include <string>

double
checkInternetConnection()
{
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();
  std::string response = "";
  double tmp;
  double isConnected;

  char buffer[1024];
  FILE *pipes = popen("ping google.com -c 1", "r");
  if (!pipes)
  {
    std::cout << "0" << std::endl;
  }
  while (!feof(pipes))
  {
    if (fgets(buffer, 1024, pipes) != NULL)
      response += buffer;
  }
  end = std::chrono::system_clock::now();
  std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

  std::regex pattern("time=([0-9.]+)");
  std::smatch matches;
  if (std::regex_search(response, matches, pattern))
  {
    tmp = stod(matches[1].str());
    isConnected = 1.0;
    std::cout << isConnected << "   " << tmp << std::endl;

  } else
  {
    isConnected = 0.0;
    std::cout << isConnected << std::endl;
  }
  pclose(pipes);

}

int main() {
  checkInternetConnection();
  return 0;
}
