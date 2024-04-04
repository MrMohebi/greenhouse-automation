#include "interfaces.h";

Triggers::Triggers(String _id, int _type, uint8_t _pinNum, String _varName, String _name, float _min, float _max, uint8_t _activeState, uint8_t _defaultState, int _createdAt){
  id = _id;
  type = _type;
  pinNum = _pinNum;
  varName = _varName;
  name = _name;
  min = _min;
  max = _max;
  activeState = _activeState;
  defaultState = _defaultState;
  createdAt = _createdAt;
};