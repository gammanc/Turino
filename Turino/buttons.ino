void button1(){
    btnState[0] = button(btnPrevState[0], A0);
    if(btnPrevState[0] == LOW && btnState[0] == HIGH){
        switch(fase){
            case CANTSTATES:
                cantstates--;
                cantstates = cantstates < 1 ? 1 : cantstates;
            break;

            case INSTATES:
                switch(currentproperty){
                    case WRITE:
                        transitions[currentstate][currentsymbol][WRITE]++;
                        if(transitions[currentstate][currentsymbol][WRITE] > BLANK)
                            transitions[currentstate][currentsymbol][WRITE] = ZERO;
                    break;

                    case MOVE:
                        transitions[currentstate][currentsymbol][MOVE]++;
                        if(transitions[currentstate][currentsymbol][MOVE] > STAY)
                            transitions[currentstate][currentsymbol][MOVE] = LEFT;
                    break;

                    case NEXTSTATE:
                        transitions[currentstate][currentsymbol][NEXTSTATE]+=1;
                        if(transitions[currentstate][currentsymbol][NEXTSTATE] > (cantstates+1)) //se añade 1 de aceptacion y 1 de rechazo;
                            transitions[currentstate][currentsymbol][NEXTSTATE] = 0;
                    break;
                }
            break;

            case DATA:
                tape[ledcursor]++;
                if(tape[ledcursor] > BLANK) tape[ledcursor] = ZERO;
                for (int i = 0; i < stripmax ; i++)
                    Serial.print(tape[i]);
                Serial.println(); Serial.println();
            break;

            case STRSTATE:
                current_q--;
                current_q = current_q < 0 ? cantstates-1 : current_q;
            break;
        }
    }
    btnPrevState[0] = btnState[0];    
}

void button2(){
    /*
      Este boton no se utilizo. Servia como Regresar
    */
}


void button3(){
    btnState[2] = button(btnPrevState[2], A2);
    if(btnPrevState[2] == LOW && btnState[2] == HIGH){
      
        switch(fase){
            
            case CANTSTATES:
                cantstates++;
                cantstates = cantstates > maxstates ? maxstates : cantstates;
            break;

            case INSTATES:
                lcd.clear();
                currentproperty++;
                if(currentproperty > NEXTSTATE){
                    currentproperty = WRITE;
                    currentsymbol++;
                    
                    if(currentsymbol > BLANK){
                        currentsymbol = ZERO;
                        currentstate++;
                        if(currentstate > (cantstates - 1)) {
                            currentstate = 0;
                        }
                    }
                }
                
            break;

            case DATA:
                ledcursor++;
                ledcursor = ledcursor > (stripmax-1) ? 0 : ledcursor;
                regist(ledcursor);
            break;

            case STRSTATE:
                current_q++;
                current_q = current_q > cantstates-1 ? 0 : current_q;
            break;
        }
  
    }
    btnPrevState[2] = btnState[2]; 
}

void button4(){
    btnState[3] = button(btnPrevState[3], A4);
    if(btnPrevState[3] == LOW && btnState[3] == HIGH){
        
        switch(fase){

            case CANTSTATES:
                lcd.clear();
                lcd.cursor();
                accepted = cantstates;
                rejected = cantstates + 1;
                fase = INSTATES;
            break;

            case INSTATES:
                lcd.noCursor();
                fase = DATA;
            break;

            case DATA:
                lcd.clear();
                fase = STRSTATE;
                ledcursor = 0;
                regist(ledcursor);
            break;

            case STRSTATE:
                lcd.clear();
                fase = PROCESSING;
            break;

            case FINISHED:

              break;

            default: break;
        }
  
    }
    btnPrevState[3] = btnState[3]; 
}


/*
    Evita el efecto rebote en los botones
*/
boolean button(boolean estAnterior, int pin){
    boolean estActual = digitalRead(pin);
    if(estAnterior != estActual){
      delay(5);
      estActual = digitalRead(pin);    
    }
    return estActual;
}
