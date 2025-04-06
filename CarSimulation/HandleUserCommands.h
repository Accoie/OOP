#pragma once

#include "Car.h"
#include <set>

const std::string SET_GEAR = "SetGear";
const std::string SET_SPEED = "SetSpeed";
const std::string ENGINE_ON = "EngineOn";
const std::string ENGINE_OFF = "EngineOff";
const std::string INFO = "Info";

const std::set<std::string> COMMANDS =
{
    SET_GEAR,
    SET_SPEED,
    ENGINE_ON,
    ENGINE_OFF,
    INFO
};

int HandleUserCommands(Car& car, std::string command, std::string valueString);