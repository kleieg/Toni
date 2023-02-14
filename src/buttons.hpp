#ifndef SRC_BUTTONS_HPP_
#define SRC_BUTTONS_HPP_

#include <Arduino.h>
#include <JC_Button.h>

#include "commands.hpp"
#include "constants.hpp"

class Buttons: public CommandSource {
public:
  Buttons();

  commandRaw getCommandRaw() override;
  bool isNoButton();
  bool isReset();

private:

  void readButtons();

  Button buttonPause;
  Button buttonUp   ;
  Button buttonDown ;

  bool ignoreRelease     = false;
  bool ignoreAll         = false;

  uint8_t longPressFactor = 1;
};

#endif /* SRC_BUTTONS_HPP_ */
