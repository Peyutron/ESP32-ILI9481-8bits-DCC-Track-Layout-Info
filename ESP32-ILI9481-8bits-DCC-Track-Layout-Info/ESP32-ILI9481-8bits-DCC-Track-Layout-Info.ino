/**
  * Version: ESP32 ILI9481 8 bits DCC Layout Screen
  * Project instructions: 
  *  - http://lamaquetade.infotronikblog.com/
  *  
  * Project repository:  https://github.com/Peyutron
  * Creator: Carlos MC
  *
  * External Library:
  *  - TFT_eSPI.h:     https://github.com/Bodmer/TFT_eSPI/tree/master
  *
  * ESP32 Library:
  *  - WiFi:           https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/src/WiFi.h
  * 
  * Board -> DOIT ESP32C3 Dev Module
  * CPU Frequency 80MHz
  * Display -> ILI9481 8 Bits no touch
  * - User_Setups/User_Setup_Select.h
  * - #include <User_Setups/Setup70d_ILI9488_S3_Parallel.h>
  * - #define ILI9481_DRIVER
  * - Pin configuration -> https://www.infotronikblog.com/2025/10/macro-keyboard-esp32-con-tft-ili9488.html
  *
**/
#include <WiFi.h>
#include "listaAccesorios.h"
#include "listaDetectores.h"
#include "ScreenConfig.h"
#include <TFT_eSPI.h>     // Hardware-specific library



TFT_eSPI tft = TFT_eSPI();  // Invoke custom library
const int receive_pin = A4;


// Recepción de datos
#define MAX_COMMAND_LENGTH 30
uint8_t bserial = false;
char c;
char b;
char commandString[MAX_COMMAND_LENGTH + 1];

String command;
String commandOld;

bool printdata = true;
int8_t line = -1;

uint8_t sensores[MAX_SENSORES] = {  
                                    true, true, true, true, true,
                                    true, true, true, true, true,
                                    true, true, true, true, true
                                 };

uint8_t accesorios[MAX_ACC]= {
                              false, false, false, false, false,
                              false, false, false, false, false
                              };

uint8_t desvios[MAX_DESVIOS]= {true, false};



// Variables globales cliente
WiFiClient client;
unsigned long previousMillis = 0;
const long interval = 15000;  // 15 segundos
bool connected = false;
uint8_t connectionsAttempts = MAX_CONNECTION_ATTEMPS;


void setup()
{
  Serial.begin(115200); // Velocidad serial
  delay(200);

  tft.begin();
  delay(200);
  tft.setRotation(3);  // Rotación
  // tft.invertDisplay(true); // Invert colors

  tft.fillScreen(TFT_BLACK);     // Fondo de pantalla
  tft.setTextColor(TFT_WHITE);   // Color del texto

  Serial.println(F("\n\nIniciando ESP32..."));
  tft.setTextSize(2);       // Tamaño de la letra
  connectToWiFi();

  ClearScreen();
  ftfDrawSections();
  tftDrawAccessories();
  tftDrawTurnouts();
  tftPrintData(commandString);
  tftPrintOnOff(false);

  Locomotora("1 3 100 0");


}
// FIN SETUP
void loop()
{

  // Comunicación Wifi
  checkConnection();
  sendKeepAlive();
  handleCommands();

  // Comunicación Serial.
  RecibeDatosSeriales();
} // END LOOP