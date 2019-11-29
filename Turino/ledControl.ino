/*
    Actualiza los leds que representan el cabezal.
    bit(index) devuelve 2^index.
    Si index = 10, ledvalue = 1024.
    Su binario = 00000100 00000000
    hbyte = 00000100
    lbyte = 00000000
    Se encenderá el led 11
*/
void regist(int index){
    ledvalue = bit(index);
    
    byte HBYTE = 0;
    byte LBYTE = 0;
    
    int hbyte = ledvalue & B11111111;
    int lbyte = abs(ledvalue / 256);
    
    HBYTE = hbyte;
    LBYTE = lbyte;
    
    digitalWrite(ST, LOW);
    shiftOut(DS, SH, MSBFIRST, LBYTE);
    shiftOut(DS, SH, MSBFIRST, HBYTE);
    digitalWrite(ST, HIGH);
    
}

// Actualiza los leds en la tira
void updateLedStrip(){
    for (int i = 0; i < stripmax; i++){
        switch (tape[i]){
            case ZERO: ledstrip[i] = CRGB(200,200,200); break;
            case ONE: ledstrip[i] = CRGB(255,0,255); break;
            case BLANK: ledstrip[i] = CRGB(0,0,0); break;
        }  
    }
    FastLED.show();
}
