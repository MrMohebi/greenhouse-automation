#ifndef INTERFACES_H
#define INTERFACES_H

#include <Arduino.h>

class Triggers {
public:

  Triggers(String _id = "", int _type = 0, uint8_t _pinNum = 0, String _varName = "", String _name = "", float _min = 0, float _max = 0, uint8_t _activeState = false, uint8_t _defaultState = false, int _createdAt = 0);
  String id;
  int type;
  uint8_t pinNum;
  String varName;
  String name;
  float min;
  float max;
  uint8_t activeState;
  uint8_t defaultState;
  int createdAt;
};

#endif