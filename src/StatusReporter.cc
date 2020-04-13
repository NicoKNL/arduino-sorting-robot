#include "StatusReporter.hh"
#include "config.hh"
#include <wiringPi.h>

StatusReporter::StatusReporter(int pin0, int pin1, int pin2) {
    m_pin0 = pin0;
    m_pin1 = pin1;
    m_pin2 = pin2;
    setStatus(DEFAULT_NO_STATUS);
}

void StatusReporter::setStatus(int status) {
    digitalWrite(m_pin0, (status & (1 << 0)));
    digitalWrite(m_pin1, (status & (1 << 1)));
    digitalWrite(m_pin2, (status & (1 << 2)));
}
