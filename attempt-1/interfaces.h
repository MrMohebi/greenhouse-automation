#ifndef INTERFACES_H
#define INTERFACES_H

#include <Arduino.h>

class Triggers {
public:

  Triggers(String _id = "", int _pinNum = 0, String _varName = "", String _name = "", float _min = 0, float _max = 0, bool _activeState = false, bool _defaultState = false, int _createdAt = 0);
  String id;
  int pinNum;
  String varName;
  String name;
  float min;
  float max;
  bool activeState;
  bool defaultState;
  int createdAt;
};

#endif