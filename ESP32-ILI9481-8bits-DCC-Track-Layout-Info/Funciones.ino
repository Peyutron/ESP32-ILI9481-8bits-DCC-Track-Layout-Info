/** Accesorio formato <a DIR SUBDIR STATE> 
  * Solo funciona con comunicación serial porque la 
  * central no envía respuesta del comando <a x x x>
  */
void Accesorio(char *ac) 
{
  short n, s, m;
  sscanf(ac, "%d %d %d", &n, &s, &m);
  Serial.print(n);
  Serial.print(F(" "));
  Serial.print(s);
  Serial.print(F(" "));
  Serial.println(m);



  if (n == 1) 
  {
    switch (s) 
    {
      case 0:               // 1-0
        break;
      case 1:  
        accesorios[0] = m;  // 1-1   
        break;
      case 2:  
        accesorios[1] = m;  // 1-2
        break;
      case 3:  
        accesorios[2] = m;  // 1-3
        break;
    }
  }
  else if (n == 2) 
  {
    switch (s) {
      case 0: 
        accesorios[3] = m;  // 2-0
        break;
      case 1:  
        accesorios[4] = m;  // 2-1
        break;
      case 2:  
        accesorios[5] = m;  // 2-2
        break;
      case 3:  
        accesorios[6] = m;  // 2-3 (8)
        break;
    }
  }
  else if (n == 3) 
  {
    switch (s) {
      case 0: 
        accesorios[7] = m;  // 3-0
        break;
      case 1:  
        accesorios[8] = m;  // 3-1
        break;
      case 2:  
        desvios[0] = m;     // 3-2 (11)
        break;
      case 3:  
        desvios[1] = m;     // 3-3
        break;
    }
    tftDrawTurnouts();
  }
   
  tftDrawAccessories();
}

/** Desvío formato <Tid estado>
  * Respuesta H
  */
void Desvio(char *d) 
{
  int n, s;
  sscanf(d, "%d %d", &n, &s);
  Serial.print(F("Activado desvio: "));
  Serial.print(n);
  Serial.print(F(" estado: "));
  Serial.println(s);

  if (n == ACCESORIO_1)
  {
    accesorios[0] = s;
    tftDrawAccessories();
  }
  else if (n == ACCESORIO_2)
  {
    accesorios[1] = s;
    tftDrawAccessories();
  }
  else if (n == ACCESORIO_3)
  {
    accesorios[2] = s;
    tftDrawAccessories();
  }
  else if (n == ACCESORIO_4)
  {
    accesorios[3] = s;
    tftDrawAccessories();
  }
  else if (n == ACCESORIO_5)
  {
    accesorios[4] = s;
    tftDrawAccessories();
  }
  else if (n == ACCESORIO_6)
  {  
    accesorios[5] = s;
    tftDrawAccessories();
  }
  else if (n == ACCESORIO_7)
  {  
    accesorios[6] = s;
    tftDrawAccessories();
  }  
  else if (n == ACCESORIO_8)
  {  
    accesorios[7] = s;
    tftDrawAccessories();
  }
  //////////////////
  else if (n == TURNOUT_1)
  {
      desvios[0] = s;
      tftDrawTurnouts();
  }
  else if (n == TURNOUT_2)
  {
    desvios[1] = s;
    tftDrawTurnouts();
  }
}

void Locomotora(char *l) {
  int r, n, s, m;
  sscanf(l, "%d %d %d %d", &r, &n, &s, &m);

  /* Serial.print(F("Registro: "));  Serial.print(r);
    Serial.print(F(" DCC: "));      Serial.print(n);
    Serial.print(F(" Velocidad: ")); Serial.print(s);
    Serial.print(F(" S.marcha: ")); Serial.println(m);*/
  tft.fillRoundRect(POS_COL_1_TXT_DATA - 5, POS_ROW_1_TXT_DATA - 5, 130, 90, 10, TFT_BLUE);  // Pantalla locomotora);
  tft.setCursor(POS_COL_1_TXT_DATA, POS_ROW_1_TXT_DATA);
  tft.print(F("Reg: "));
  tft.print(r);
  tft.setCursor(POS_COL_1_TXT_DATA, POS_ROW_2_TXT_DATA);
  tft.print(F("DCC: "));
  tft.print(n);
  tft.setCursor(POS_COL_1_TXT_DATA, POS_ROW_3_TXT_DATA);
  tft.print(F("Vel: "));
  tft.print(s);
  tft.setCursor(POS_COL_1_TXT_DATA, POS_ROW_4_TXT_DATA);
  tft.print(F("Dir: "));
  if (m == 1) tft.print(F(">>"));
  else tft.print(F("<<"));
}

void locomotoraEX(char *lex){
  // Comando `l' Comando de DCCEX -> <l DCC REG SPEED FUNCTION>
  // La velocidad va desde 0 a 255.
  // Desde 0 a 128 va en un sentido avance y de 128 a 255 va en retroceso
  int r, n, s, m;
  
  sscanf(lex, "%d %d %d %d", &r, &n, &s, &m); // DCC REG SPEED FUNCTION
  uint8_t avance = 1;
  uint8_t valor = s;
    if (s >= 1){
      s = s-1;
    } else s = 0;
    if (valor >= 128){ //  Si la velocidad es mayor de 128 el estado es retroceso
      avance = 0;
      if (s >= 128) s = s - 128;
    }
    if (s >= 126) s = 126; // Velocidad no puede ser mayor de 126

  /* // DEBUG
    Serial.print(F("Registro: "));  Serial.print(r);
    Serial.print(F(" DCC: "));      Serial.print(n);
    Serial.print(F(" Velocidad: ")); Serial.print(s);
    Serial.print(F(" S.marcha: ")); Serial.println(m);
  */
  tft.fillRect(POS_COL_1_TXT_DATA -5, POS_ROW_1_TXT_DATA -5 , 140, 70, TFT_DARKGREY);  // Pantalla locomotora);
  tft.setCursor(POS_COL_1_TXT_DATA, POS_ROW_1_TXT_DATA);
  tft.print(F("Reg: "));
  tft.print(n);
  tft.setCursor(POS_COL_1_TXT_DATA, POS_ROW_2_TXT_DATA);
  tft.print(F("DCC: "));
  tft.print(r);
  tft.setCursor(POS_COL_1_TXT_DATA, POS_ROW_3_TXT_DATA);
  tft.print(F("Vel: "));
  tft.print(s);
  tft.setCursor(POS_COL_1_TXT_DATA, POS_ROW_4_TXT_DATA);
  tft.print(F("Dir: "));
  if (avance == 1) tft.print(F(">>"));
  else tft.print(F("<<"));
}

void CheckSensores(char *s, bool low, bool serial)
{
  int8_t n; // Número ID del sensor
  sscanf(s, "%d0", &n);
  if (low) 
  { 
    sensores[n] = true;
    if (!serial)
    {
      Serial.print(F("<q"));
      Serial.print(n);
      Serial.println(F(">"));  
    }
  } 
  else 
  {
    sensores[n] = false;
    if (!serial)
    {
      Serial.print(F("<Q"));
      Serial.print(n);
      Serial.println(F(">"));  
    }
  }
  ftfDrawSections();
}
