
// Start Logo
#define TXT_LOGO "lamaquetade.infotronikblog.com"

// Configuración WiFi
#define SSID "YourSSID"             // Reemplaza con tu SSID
#define WIFIPASS "YourPass"  // Reemplaza con tu password

// Configuración del servidor DCCpp
#define SERVERIP "192.168.4.1"
#define PORT 2560
#define MAX_ATTEMPS 15

#define MAX_CONNECTION_ATTEMPS 10

/* DESVÍOS */
#define MAX_DESVIOS 2
#define MAX_ACC 10
#define MAX_SENSORES 16


/** COORDENADAS BUCLE1 */
#define BN_RECTA_LARGA 180
#define BN_RECTA_LARGA_B1_NORTE 100
#define BN_X_START_B1_NORTE 140

#define BN_RECTA_CORTA 94
#define BN_X_START 60
#define BN_Y_START 30

/** COORDENADAS PISTA CENTRAL */
#define ANCHO_RECTA 8
#define LARGO_RECTA 220
#define LARGO_DESVIO 20
#define ANCHO_APEAD 6

/** COORDENADAS FUNCIONES */
#define FLINE1 30
#define FLINE2 255
#define FLINE1_1 200
#define FLINE1_2 220
#define FLINE1_3 240
#define FLINE1_4 260

/** TRACK COLORS */
#define COLOR_OCUPADO   0xF800      /*   0, 128,   0 */
#define COLOR_LIBRE     0x07E0      /* 255,   0,   0 */
#define COLOR_PISTA     0xFFFF      /* 255, 255, 255 */

/** TEXTS */

#define TXT_START_TEXT 18

#define TXTL_SOLDADOR   "Soldador Mod.B1"
#define TXTL_EXTERIOR   "Luces exterior"
#define TXTL_CASAS      "Luces casas"
#define TXTL_PASO_1     "Paso a Nivel"

#define TXTL_TV_TALLER  "TV taller"
#define TXTL_TALLER     "Luces taller"
#define TXTL_CARRETERA  "Luces carretera"
#define TXTL_BARRIADA   "Anim. Barriada"



/* Posición textos */

#define POS_COL_1_TXT_DATA 180
#define POS_ROW_1_TXT_DATA  85
#define POS_ROW_2_TXT_DATA 105
#define POS_ROW_3_TXT_DATA 125
#define POS_ROW_4_TXT_DATA 145
// #define POS_TXT_DATA

