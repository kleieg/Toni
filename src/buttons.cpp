#include "buttons.hpp"

#include "constants.hpp"
#include "logger.hpp"

namespace {
constexpr bool buttonPinIsActiveLow = (buttonPinType == levelType::activeLow);
}

Buttons::Buttons()
: CommandSource()
//            pin             dbTime        puEnable              invert
, buttonPause(buttonPausePin, buttonDbTime, buttonPinIsActiveLow, buttonPinIsActiveLow)
, buttonUp   (buttonUpPin   , buttonDbTime, buttonPinIsActiveLow, buttonPinIsActiveLow)
, buttonDown (buttonDownPin , buttonDbTime, buttonPinIsActiveLow, buttonPinIsActiveLow)

{
  buttonPause.begin();
  buttonUp   .begin();
  buttonDown .begin();

}

commandRaw Buttons::getCommandRaw() {
  commandRaw ret = commandRaw::none;
  readButtons();

  if ((ignoreRelease || ignoreAll) && isNoButton()) {
    ignoreAll     = false;
    ignoreRelease = false;
    longPressFactor = 1;
    return commandRaw::none;
  }

  if (ignoreAll) {
    return commandRaw::none;
  }

  if ((  buttonPause.pressedFor(buttonLongPress)
      || buttonUp   .pressedFor(buttonLongPress)
      || buttonDown .pressedFor(buttonLongPress)
      )
     && buttonPause.isPressed()
     && buttonUp   .isPressed()
     && buttonDown .isPressed()) {
    ret = commandRaw::allLong;
    ignoreAll = true;
  }

  else if ((  buttonUp   .pressedFor(buttonLongPress)
      || buttonDown .pressedFor(buttonLongPress)
      )
     && buttonUp   .isPressed()
     && buttonDown .isPressed()) {
    ret = commandRaw::updownLong;
    ignoreAll = true;
  }

  else if (buttonPause.wasReleased() && not ignoreRelease) {
    ret = commandRaw::pause;
  }

  else if (buttonPause.pressedFor(longPressFactor * buttonLongPress)) {
    if (longPressFactor == 1)
      ret = commandRaw::pauseLong;
  }

  else if (buttonUp.wasReleased() && not ignoreRelease) {
    ret = commandRaw::up;
  }

  else if (buttonUp.pressedFor(longPressFactor * buttonLongPress)) {
    if (longPressFactor == 1)
      ret = commandRaw::upLong;
    else
      ret = commandRaw::upLongRepeat;
  }

  else if (buttonDown.wasReleased() && not ignoreRelease) {
    ret = commandRaw::down;
  }

  else if (buttonDown.pressedFor(longPressFactor * buttonLongPress)) {
    if (longPressFactor == 1)
      ret = commandRaw::downLong;
    else
      ret = commandRaw::downLongRepeat;
  }


  switch (ret) {
  case commandRaw::pauseLong     :
  case commandRaw::upLong        :
  case commandRaw::upLongRepeat  :
  case commandRaw::downLong      :
  case commandRaw::downLongRepeat:

                                   ++longPressFactor;
                                   ignoreRelease = true;
                                   break;
  default                        : break;
  }

  if (ret != commandRaw::none) {
    LOG(button_log, s_info, F("Button raw: "), static_cast<uint8_t>(ret));
  }
  return ret;
}

bool Buttons::isNoButton() {
  return not buttonPause.isPressed()
      && not buttonUp   .isPressed()
      && not buttonDown .isPressed()
      ;
}

bool Buttons::isReset() {
  constexpr int buttonActiveLevel = getLevel(buttonPinType, level::active);
  return (digitalRead(buttonPausePin) == buttonActiveLevel &&
          digitalRead(buttonUpPin   ) == buttonActiveLevel &&
          digitalRead(buttonDownPin ) == buttonActiveLevel );
}

void Buttons::readButtons() {
  buttonPause.read();
  buttonUp   .read();
  buttonDown .read();
}
