// Función para conectar a WiFi
bool connectToWiFi() 
{
  Serial.print(F("Conectando a WiFi"));
  WiFi.begin(SSID, WIFIPASS);
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < MAX_ATTEMPS) 
  {
    delay(500);
    Serial.print(F("."));
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(F("WiFi conectado!"));
    Serial.print(F("IP local: "));
    Serial.println(WiFi.localIP());
    tftPrintIP();
    return true;
  } else {
    tftPrintIP();
    Serial.println(F("\nError conectando a WiFi"));
    return false;
  }
}

// Función para conectar al servidor remoto
bool connectToServer() {
  if (!client.connected()) {
    Serial.println(F("Conectando al servidor..."));
    
    if (client.connect(SERVERIP, PORT)) 
    {
      Serial.println(F("Conectado al servidor!"));
      tftPrintIP();
      return true;
    } else {
      Serial.println(F("Error conectando al servidor"));
      tftPrintIP();
      return false;
    }
  }
  return client.connected();
}

// Función para enviar comando keep-alive
void sendKeepAlive() 
{
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) 
  {
    previousMillis = currentMillis;
    
    if (client.connected()) client.print(F("<c>"));
  }
}

// Función para verificar y mantener la conexión
void checkConnection() 
{
  if (connectionsAttempts > 1 )
  {
    // Verificar conexión WiFi
    if (WiFi.status() != WL_CONNECTED) 
    {
      Serial.println(F("WiFi desconectado, reconectando..."));
      connectToWiFi();
      connectionsAttempts--;
    }
  
    // Verificar conexión con el servidor
    if (WiFi.status() == WL_CONNECTED) 
    {
      if (!client.connected()) 
      {
        connectToServer();
        connectionsAttempts--;
      }
    }
  }
}

// Función para manejar comandos recibidos
void handleCommands() 
{
  if (client.available()) 
  {
    String response = client.readString();
    response.trim();
    if (response.length() > 0) wifiCommadParse(response);
  }
}

// Recibe datos seriales
void RecibeDatosSeriales() 
{
  memset(commandString, 0, sizeof(commandString));
  while (Serial.available() > 0)   // while there is data on the serial line
  {
    c = Serial.read();
    if (c == '<')                    // start of new command
      commandString[0] = 0;
    else if (c == '>')               // end of new command
    {
      String dataSend = "<" + String(commandString) + ">";
      if (client.connected()) client.print(dataSend);
      decodata(commandString, true);
      tftPrintData(commandString);
    }
    else if (strlen(commandString) <  MAX_COMMAND_LENGTH)  // if commandString still has space, append character just read from serial line
      sprintf(commandString, "%s%c", commandString, c); // otherwise, character is ignored (but continue to look for '<' or '>')
    
  }

}

// Busca el primer caracter que corresponde al comando y lo envía a la 
// función correspondiente.
// char = comando DCC++
// serial = control para los datos seiales. Solo se usa en los sensores para
// evitar retroalimentación del comando.
void decodata(char *com, uint8_t serial) 
{

  switch (com[0]) 
  {
    case 'p': // Encendido
      if (com[1] == '0')
      { 
        Serial.println(F(" DCC OFF"));
        tftPrintOnOff(false);
        }
      else if (com[1] == '1') 
      {
        Serial.println(F("DCC ON"));
        tftPrintOnOff(true);
      }
      break;
    case 'T': // Locomotora
      Locomotora(com + 1);
      break;
    case 'a': // Accesorios
      if (serial)Accesorio(com + 1);
      break;
    case 'H': // Desvíos
      Serial.println(F("DESVIO"));
      Desvio(com + 1);
      break;
    case 'Q': // Sensor estado alto
      CheckSensores(com + 1, false, serial);
      break;
    case 'q': // Sensor estado bajo
      CheckSensores(com + 1, true, serial);
      break;
    default:
      Serial.println(F("Command Error"));
      //tftPrintData(com);
      break;
  }
}

void wifiCommadParse(String command_DCC) 
{
  command_DCC.replace("\n", "");
  command_DCC.replace("\r", "");
  
  int posicion = 0;
  int comandosProcesados = 0;
  
  Serial.println(command_DCC);
  
  while (posicion < command_DCC.length()) 
  {
    // Buscar siguiente < desde la posición actual
    int inicio = command_DCC.indexOf('<', posicion);
    
    // Si no hay más <, terminamos
    if (inicio == -1) break;
    
    // Buscar el > correspondiente
    int fin = command_DCC.indexOf('>', inicio + 1);
    
    // Validar que hay un > después del <
    if (fin == -1) break;  // Salimos, quizás el resto llegará después
    
    // Validar que no hay otro < antes del > (comandos anidados)
    int siguienteInicio = command_DCC.indexOf('<', inicio + 1);
    if (siguienteInicio != -1 && siguienteInicio < fin) 
    {
      // Avanzamos hasta el siguiente < para intentar recuperarnos
      posicion = siguienteInicio;
      continue;
    }
    
    // Extraer el comando (sin los < >)
    String comando = command_DCC.substring(inicio + 1, fin);
    comando.trim();  // Limpiar espacios
    
    // Validar que no está vacío
    if (comando.length() == 0) 
    {
      posicion = fin + 1;
      continue;
    }
    
    // Convertir a char array y procesar
    char cmdChar[comando.length() + 1];
    comando.toCharArray(cmdChar, sizeof(cmdChar));
    
    // Procesar el comando
    decodata(cmdChar, false);
    tftPrintData(cmdChar);

    comandosProcesados++;
    posicion = fin + 1;  // Continuar después de este comando
  }

}
