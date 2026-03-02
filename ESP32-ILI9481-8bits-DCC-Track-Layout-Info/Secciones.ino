// Cambia el color de las rutas / Dibuja el plano
// Secciones 1, 4, 6, 7, 8, 9, 10, 11

void Seccion(int posx, int posy, int H1, int W1, uint8_t estado) {
  tft.fillRect(posx, posy, H1, W1, GetColor(estado)); // VIA NORTE BUCLE RETORNO 1
}

// MODULO 1
void Bucle_1(uint8_t estado) { // INTERIOR BUCLE RETORNO 1

    tft.fillRect(BN_X_START, BN_Y_START, BN_RECTA_CORTA, ANCHO_RECTA, GetColor(estado)); // INFERIOR

    for (int i = 0; i < 8; i++) tft.drawLine(30 + i, 50, 60 + i, BN_Y_START, GetColor(estado)); // Linea inclinada con 8px de ancho
    
    tft.fillRect(30, 50, ANCHO_RECTA, 40, GetColor(estado));  // LATERAL IZQUIERDO
    
    for (int i = 0; i < 8; i++) tft.drawLine(30 + i, 90, 55 + i, 110, GetColor(estado)); // Linea inclinada con 8px de ancho
    
    tft.fillRect(55, 104, BN_RECTA_CORTA, ANCHO_RECTA, GetColor(estado)); // INFERIOR
    
    for (int i = 0; i < 8; i++) tft.drawLine(140 + i, 110, 160 + i, 90, GetColor(estado)); // Linea inclinada con 8px de ancho
}

void SalidaBucle1(uint8_t estado) { //  SALIDA BUCLE RETORNO 1 SUR
  
  tft.fillRect(160, 70, ANCHO_RECTA, 20, GetColor(estado));

  for (int i = 0; i < 8; i++) tft.drawLine(160 + i, 70, 180 + i, 50, GetColor(estado)); // Linea inclinada con 8px de ancho

  tft.fillRect(180, 50, 60, ANCHO_RECTA, GetColor(estado)); // VIA SUR
}

void Seccion14(uint8_t estado) { // BUCLE RETORNO

  tft.fillRect(60, 60, 60, ANCHO_APEAD, GetColor(estado)); // Taller 2
  tft.fillRect(60, 75, 70, ANCHO_APEAD, GetColor(estado)); // Taller 
}

void DesvioCocherasPrincipal(uint16_t color1, uint16_t color2) { // B1_COCHERAS_CON_PRINCIPAL    
    
    tft.fillRect(140 , 30, LARGO_DESVIO, ANCHO_RECTA, color2);
    
    for (int i = 0; i < 10; i++) tft.drawLine(140 + i, 60, 155 + i, 38, color1); // Linea inclinada con 8px de ancho
}

void DesvioCocheras(uint16_t color1, uint16_t color2) { // B1_COCHERAS
    
  tft.fillRect(120 , 60, LARGO_DESVIO, ANCHO_APEAD, color2);
  for (int i = 0; i < 10; i++) tft.drawLine(120 + i, 80 , 140 + i, 60, color1); // Linea inclinada con 8px de ancho
}

// MODULO 2
void Bucle_2(uint8_t estado) {  // INTERIOR BUCLE 2

  for (int i = 0; i < 8; i++) tft.drawLine(410 + i, BN_Y_START, 440 + i, 50, GetColor(estado)); // Linea inclinada con 8px de ancho
  tft.fillRect(440, 50, ANCHO_RECTA, 40, GetColor(estado)); // LATERAL DERECHO
  for (int i = 0; i < 8; i++) tft.drawLine(420 + i, 110, 440 + i, 90, GetColor(estado)); // Linea inclinada con 8px de ancho
  tft.fillRect(330, 104, BN_RECTA_CORTA, ANCHO_RECTA, GetColor(estado)); // INFERIOR
  for (int i = 0; i < 8; i++) tft.drawLine(330 + i, 110, 310 + i, 90, GetColor(estado)); // Linea inclinada con 8px de ancho
}  
  
void SalidaBucle2(uint8_t estado) { //  SALIDA BUCLE RETORNO 1 SUR

  tft.fillRect(310, 70, ANCHO_RECTA, 20, GetColor(estado));
    
  for (int i = 0; i < 8; i++) tft.drawLine(310 + i, 70, 290 + i, 50, GetColor(estado)); // Linea inclinada con 8px de ancho
    
  tft.fillRect(240, 50, 60, ANCHO_RECTA, GetColor(estado)); // VIA SUR
}

// Accesorios
void PintaAccesorios(int curX, int curY, String text, uint8_t estado) {

  int r = 4;
  tft.setCursor(curX, curY -10);
  tft.println(text);
  tft.drawCircle((curX - 10), (curY - 5), 4, TFT_WHITE);
  if (estado) {
    tft.fillCircle((curX - 10), (curY - 5), (r - 1), TFT_GREEN);
  } else {
    tft.fillCircle((curX - 10), (curY - 5), (r - 1), TFT_RED);
  }
}

void tftPrintOnOff(bool isOn)
{
  if (isOn) tft.fillCircle(25, 20, 8, TFT_GREEN);
  else tft.fillCircle(25, 20, 8, TFT_RED);
}

// Imprime el comando recibido 
void tftPrintData(char *com)
{
    //if(String(Length() > 30), Substr(Discription,0 , 27) + "..." , Discription)
    tft.fillRect(0, 280 , 240, 40, TFT_BLUE); // Monitor Serial);
    tft.setCursor(TXT_START_TEXT, 292);

    // si la recepción tiene más de 40 caracteres
    if (strlen(com) > 16)
    {
      char commandDCC[17];
      strncpy(commandDCC, com, 16);
      commandDCC[17] = '\0';
      tft.print(String(commandDCC));
    }
    else tft.print(String(com));


}

// Show connections status
void tftPrintIP()
{
  tft.fillRect(240, 280 , 240, 40, TFT_BLUE); // Monitor Serial);
  tft.setCursor(250, 282);
  if (WiFi.status() == WL_CONNECTED) tft.println(WiFi.localIP());
  else tft.println(F("Serial only"));
  
  tft.setCursor(250, 302);
  if (client.connected()) 
  {
    tft.print("IP: ");
    tft.print(SERVERIP);
  }
  else tft.print("Server offline");
}

// Limpia la pantalla
void ClearScreen() 
{
  tft.fillRect(10, 3, LARGO_RECTA + 10, (tft.height()/2) + 10, TFT_BLUE);
  tft.setCursor(90, 125);
  tft.println(F("M1"));

  tft.fillRect(240, 3, LARGO_RECTA + 10, (tft.height()/2) + 10, TFT_BLUE);
  tft.setCursor(360, 125);
  tft.println(F("M2"));

  tft.setCursor(60, 9);
  tft.print(TXT_LOGO);
}

void tftDrawAccessories()
{
    PintaAccesorios(FLINE1, FLINE1_1, TXTL_SOLDADOR, accesorios[0]); // Efecto soldador
    PintaAccesorios(FLINE1, FLINE1_2, TXTL_EXTERIOR, accesorios[1]); // Interruptor luces exteriores
    PintaAccesorios(FLINE1, FLINE1_3, TXTL_CASAS, accesorios[2]);    // Luces Taller
    PintaAccesorios(FLINE1, FLINE1_4, TXTL_PASO_1, accesorios[3]);    // Luces Taller

    PintaAccesorios(FLINE2, FLINE1_1, TXTL_TV_TALLER, accesorios[4]); // Soldador
    PintaAccesorios(FLINE2, FLINE1_2, TXTL_TALLER, accesorios[5]);  // TV taller
    PintaAccesorios(FLINE2, FLINE1_3, TXTL_CARRETERA, accesorios[6]); // Soldador
    PintaAccesorios(FLINE2, FLINE1_4, TXTL_BARRIADA, accesorios[7]); // Soldador
}

void tftDrawTurnouts()
{
    if (desvios[0]) DesvioCocherasPrincipal(COLOR_LIBRE, COLOR_OCUPADO);
    else DesvioCocherasPrincipal(COLOR_OCUPADO, COLOR_LIBRE);
    
    if (desvios[1]) DesvioCocheras(COLOR_LIBRE, COLOR_OCUPADO);
    else DesvioCocheras(COLOR_OCUPADO, COLOR_LIBRE);
}

void ftfDrawSections()
{
  //  *** Diagrama de vías ***** //
  // MODULO B1
  // VIA NORTE BUCLE RETORNO 1 SENSOR 5
  Seccion(BN_X_START_B1_NORTE, 
          BN_Y_START, 
          BN_RECTA_LARGA_B1_NORTE, 
          ANCHO_RECTA, 
          sensores[SENS05]); 
  
  // INTERIOR BUCLE RETORNO 1 SENSORES 1,2,4
  Bucle_1(sensores[SENS04]);  
  
  //  VIA SUR BUCLE RETORNO 1
  SalidaBucle1(sensores[SENS03]); 
  
  // MODULO B1 COCHERAS
  Seccion14(sensores[SENS06]);
  
  // MODULO B2
  // VIA NORTE MODULO 2
  Seccion(240, 
          BN_Y_START, 
          BN_RECTA_LARGA, 
          ANCHO_RECTA, 
          sensores[SENS07]); 
  Bucle_2(sensores[SENS07]);
  SalidaBucle2(sensores[SENS07]); //  VIA SUR BUCLE RETORNO 1
}

void intro()
{

}


uint16_t GetColor(uint8_t estado){
  if (estado) return COLOR_LIBRE;
  else return COLOR_OCUPADO;
}