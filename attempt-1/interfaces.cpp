#include "interfaces.h";

Triggers::Triggers(String _id, int _pinNum, String _varName, String _name, float _min, float _max, bool _activeState, bool _defaultState, int _createdAt){
  id = _id;
  pinNum = _pinNum;
  varName = _varName;
  name = _name;
  min = _min;
  max = _max;
  activeState = _activeState;
  defaultState = _defaultState;
  createdAt = _createdAt;
};