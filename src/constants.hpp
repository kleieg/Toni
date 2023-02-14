#ifndef SRC_CONSTANTS_HPP_
#define SRC_CONSTANTS_HPP_

#include <Arduino.h>


// uncomment the below line to enable serial input as additional command source
// um den Serial Monitor als zusätzliche Kommandoquelle zu haben bitte in der nächste Zeile den Kommentar entfernen
//#define SerialInputAsCommand
// 7:            8: up         9: upLong
// 4: allLong    5: pause      6: pauseLong
// 1:            2: down       3: downLong

// uncomment the below line to support the MH2024K16SS chip on the DfMiniMp3 player
// um den Chip MH2024K16SS auf dem DfMiniMp3 Player zu ünterstützen bitte in der nächste Zeile den Kommentar entfernen
//#define DFMiniMp3_T_CHIP_VARIANT Mp3ChipMH2024K16SS

// ####### helper for level ############################

enum class level : uint8_t {
  inactive,
  active  ,
};
enum class levelType : uint8_t {
  activeHigh, // normally open
  activeLow , // normally closed
};

inline constexpr int getLevel(levelType t, level l) { return (l == level::inactive) ? (t == levelType::activeHigh ? LOW : HIGH)
                                                                                    : (t == levelType::activeHigh ? HIGH : LOW); }


#ifdef TonUINO_Classic
// ####### buttons #####################################

inline constexpr uint32_t  buttonLongPress = 1000; // timeout for long press button in ms
inline constexpr uint8_t   buttonPausePin  = A0;
inline constexpr uint8_t   buttonUpPin     = A1;
inline constexpr uint8_t   buttonDownPin   = A2;


inline constexpr levelType buttonPinType   = levelType::activeHigh;      // @@klh geändert von activeLow auf activeHigh wegen Sensortasten !!
inline constexpr uint32_t  buttonDbTime    = 25; // Debounce time in milliseconds (default 25ms)

// ####### chip_card ###################################

inline constexpr uint32_t cardCookie      = 0x1337b347;
inline constexpr uint8_t  cardVersion     = 0x02;
inline constexpr byte     mfrc522_RSTPin  =  9;
inline constexpr byte     mfrc522_SSPin   = 10;
inline constexpr uint8_t  cardRemoveDelay =  3;

// ####### mp3 #########################################

#define DFPlayerUsesSoftwareSerial
#define CHECK_MISSING_ONPLAYFINISHED

inline constexpr uint8_t       maxTracksInFolder        = 255;
inline constexpr uint8_t       dfPlayer_receivePin      = 2;
inline constexpr uint8_t       dfPlayer_transmitPin     = 3;
inline constexpr uint8_t       dfPlayer_busyPin         = 4;
inline constexpr levelType     dfPlayer_busyPinType     = levelType::activeHigh;
inline constexpr unsigned long dfPlayer_timeUntilStarts = 500;

// ####### tonuino #####################################

inline constexpr uint8_t       shutdownPin     = 7;
inline constexpr levelType     shutdownPinType = levelType::activeHigh;
inline constexpr uint8_t       openAnalogPin   = A7;
inline constexpr unsigned long cycleTime       = 50;
#endif /* TonUINO_Classic */

#endif /* SRC_CONSTANTS_HPP_ */
