#include <LiquidCrystal.h>
#include <FastLED.h>

// Pines a utilizar
#define LEDSTRIP 8
#define DS 9
#define ST 10
#define SH 11

enum states {CANTSTATES, INSTATES, DATA, STRSTATE, PROCESSING, FINISHED};
enum stateproperties {WRITE, MOVE, NEXTSTATE};
enum movevalues {LEFT, RIGHT, STAY};
enum inputs {ZERO, ONE, BLANK};
enum customchars {ARROW, CHECK, RESET, BLANKCH};

//Caracteres propios para mostrar en LCD
byte arrow[] = {
  B00000,
  B00000,
  B00100,
  B00010,
  B11111,
  B00010,
  B00100,
  B00000
};

byte check[] = {
  B00000,
  B00000,
  B00001,
  B00011,
  B10110,
  B11100,
  B01000,
  B00000
};

byte reset[] = {
  B00000,
  B00000,
  B01101,
  B10011,
  B10111,
  B10000,
  B01110,
  B00000
};

byte blank[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B10001,
  B11111,
  B00000
};

// Variables
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

const int stripmax = 15;
const int maxstates = 20;

// Para manejo de botones
boolean btnPrevState[4];
boolean btnState[4];

// FUNCIONAMIENTO DE LA MÁQUINA
// Valor a usar para encender uno de los leds del cursor
long ledvalue = 0;

// Indice donde esta ubicado el cursor
int ledcursor = 0;

// Cantidad de estados a utilizar
int cantstates = 1;

// Matriz para representar los estados
// Cada estado se representa por una matriz 3x3
int transitions[maxstates][3][3];

// Estado inicial de la maquina
int initialState = 0;

// Variables para ejecución de la máquina
int current_q = 0;
int accepted = 0;
int rejected = 0;

/*
 * Variable para manejar en que fase está la maquina
 * CANTSTATES - Ingresar cantidad de estados
 * INSTATES - Ingresar función de transición
 * DATA - Ingresar datos a la cinta
 * STRSTATE - Ingresar estado inicial
 * PROCESSING - Procesamiento de la cinta
 * FINISHED - Finalizacion
*/
int fase = CANTSTATES;

// Cinta de la maquina
int tape[stripmax];
// Manejo de tira LED
CRGB ledstrip[stripmax];

// Variables para ingresar estados
int currentstate = 0;
int currentproperty = WRITE;
int currentsymbol = ZERO;


void setup() {
    pinMode(ST, OUTPUT);
    pinMode(DS, OUTPUT);
    pinMode(SH, OUTPUT);
    regist(ledcursor);

    // Inicializacion caracteres propios
    lcd.createChar(ARROW, arrow);
    lcd.createChar(CHECK, check);
    lcd.createChar(RESET, reset);
    lcd.createChar(BLANKCH, blank);
    
    lcd.begin(16, 2);

    //Inicializacion de matriz de transiciones
    initTransitions();
    
    // Inicializacion de tira LED
    FastLED.addLeds<WS2811, LEDSTRIP, BRG>(ledstrip, stripmax);
    FastLED.setBrightness(70);
    for(int i = 0; i < stripmax; i++){
        ledstrip[i] = CRGB(0,0,0);
        tape[i] = BLANK;
    }
    FastLED.show();
    
    Serial.begin(9600);
}

void loop() {
  
    delay(10);
    
    button1();
    
    //button2();
    
    button3();
    
    button4();
    
    draw();

    updateLedStrip();

    processTape();
}
