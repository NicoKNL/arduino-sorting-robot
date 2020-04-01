class StatusReporter {
private:
  int DEFAULT_NO_STATUS = 6; // # of LEDs as first LED = 0
  int m_pin0;
  int m_pin1;
  int m_pin2;

public:
  // TODO: Make this a singleton class
  StatusReporter(int pin0, int pin1, int pin2);

  void setStatus(int status);
};
