void draw(){
    switch(fase){

        case CANTSTATES:
            lcd.setCursor(0,0);
            lcd.print("Estados? ");
            if(cantstates < 10){
                lcd.print(0);
                lcd.print(cantstates);
            }else {
                lcd.print(cantstates);
            }
            lcd.setCursor(0,1);
            lcd.print("-    ");
            lcd.write(2);
            lcd.print("    +   ");
            lcd.write(1);
        break;

        case INSTATES:
            // Imprimiendo funcion de transición
            lcd.setCursor(0,0);
            lcd.print("q");
            printState(currentstate);
            lcd.print(",");
            
            if(currentsymbol == BLANK) lcd.write(BLANKCH);
            else lcd.print(currentsymbol);
            lcd.print(" ");
            
            lcd.write(ARROW); lcd.print(" ");

            if(transitions[currentstate][currentsymbol][WRITE] == BLANK)
                lcd.write(BLANKCH);
            else
                lcd.print(transitions[currentstate][currentsymbol][WRITE]);
            lcd.print(" ");
            
            //Movimiento a realizar
            switch(transitions[currentstate][currentsymbol][MOVE]){
                case LEFT: lcd.print("L"); break;
                case RIGHT: lcd.print("R"); break;
                case STAY: lcd.print("S"); break;
            }
            lcd.print(" ");

            printState(transitions[currentstate][currentsymbol][NEXTSTATE]);
            lcd.print(" ");

            //Etiquetas para reconocer cada entrada
            lcd.setCursor(8,1); lcd.print("w");
            lcd.setCursor(10,1); lcd.print("m");
            lcd.setCursor(12,1); lcd.print("n");

            //Muesta cursor en la entrada seleccionada
            switch(currentproperty){
                case WRITE: lcd.setCursor(8,0); break;
                case MOVE: lcd.setCursor(10,0); break;
                case NEXTSTATE: lcd.setCursor(12,0); break;
            }
            delay(50);
        break;

        
        case DATA:
            lcd.setCursor(0,0);
            lcd.print(" Ingrese datos");
            lcd.setCursor(0,1);
            lcd.print("  a la cinta  ");
            lcd.write(1);
        break;


        case STRSTATE:
            lcd.setCursor(0,0);
            lcd.print("Est. inicio? ");
            if(current_q < 10){
                lcd.print(0);
                lcd.print(current_q );
            }else {
                lcd.print(current_q );
            }
            lcd.setCursor(0,1);
            lcd.print("-         +   ");
            lcd.write(1);
        break;

        case PROCESSING:
            lcd.setCursor(0,0);
            lcd.print("Procesando...");
            lcd.setCursor(0,1);
            lcd.print("q =");
            printState(current_q);
        break;

        case FINISHED:
            lcd.setCursor(0,0);
            if(current_q == accepted)
                lcd.print("** ACEPTADO **");
            else
                lcd.print("**RECHAZADO**");
        break;
    }
}

/*
    Imprime el estado actual en formato 00, 01..
    Si el estado es el definido como el de aceptacion
    o rechazo, se imprime A o X respectivamente.
*/
void printState(int state){
    if(state == accepted) lcd.print("A ");
    else if(state == rejected) lcd.print("X ");
    else if(state < 10){
        lcd.print(0);
        lcd.print(state);
    }else {
        lcd.print(state);
    }
}
