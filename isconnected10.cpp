#include <iostream>
#include <chrono>
#include <cstdio>
#include <regex>
#include <string>

double
checkInternetConnection(int &isConnected)
{
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();
  std::string response = "";
  double time_ping;

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
	time_ping = stod(matches[1].str());
    isConnected = 1;
    //std::cout << isConnected << "   " << tmp << std::endl;

  } else
  {
	time_ping = -1;
    isConnected = 0;
    //std::cout << isConnected << std::endl;
  }
  pclose(pipes);
  return time_ping;

}

void
recorded_connection_test(int isConnected, double time_ping, double x, double y, double theta)
{
    double log_timestamp = carmen_get_time() - tachograph_starttime;
    stringstream sst;
	sst << "CONNECTION" << " " <<
			to_string(isConnected) << " " <<
			to_string(time_ping) << " " <<
            to_string(x) << " " <<
			to_string(y) << " " <<
			to_string(theta) << " " <<
			to_string(carmen_get_time()) << " " <<
			to_string(log_timestamp) <<
			endl;
	string line = sst.str();
	save_single_line_in_file(tachograph_filename, line);
}
