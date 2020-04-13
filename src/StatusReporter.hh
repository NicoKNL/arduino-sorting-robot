#include <string>
#include <vector>
#include "SortingRobot.hh"

class StatusReporter {
private:
  const int DEFAULT_NO_STATUS = 6; // # of LEDs as first LED = 0
  int m_pin0;
  int m_pin1;
  int m_pin2;
  const std::vector<std::string> t = // translation
  {
  "Off", "Idle", " Waiting", "Error", "IngestingDisk", "Sorting"
  };
  void setStatus(int status);

public:
  // TODO: Make this a singleton class
  StatusReporter(int pin0, int pin1, int pin2);
  void logState(SortingRobotSystem & robo);
};
