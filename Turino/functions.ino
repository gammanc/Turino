void initTransitions(){
    for (int i = 0; i < maxstates; i++){
        transitions[i][ZERO][WRITE] = ZERO;
        transitions[i][ZERO][MOVE] = STAY;
        transitions[i][ZERO][NEXTSTATE] = 0;
        
        transitions[i][ONE][WRITE] = ZERO;
        transitions[i][ONE][MOVE] = STAY;
        transitions[i][ONE][NEXTSTATE] = 0;
        
        transitions[i][BLANK][WRITE] = ZERO;
        transitions[i][BLANK][MOVE] = STAY;
        transitions[i][BLANK][NEXTSTATE] = 0;
    }
}

/*
    Procesa la función de transición ingresada
*/
void processTape(){
    if(fase == PROCESSING){
        
        // El programa podría nunca terminar de procesar si no se define un
        // estado de aceptación o rechazo, como lo define la teoría
        while(current_q != accepted && current_q != rejected){
            
            int current_cell_value = tape[ledcursor];

            int symbol_to_write = transitions[current_q][current_cell_value][WRITE];
            int movement = transitions[current_q][current_cell_value][MOVE];
            int next_state = transitions[current_q][current_cell_value][NEXTSTATE];

            //Escribir en la cinta
            tape[ledcursor] = symbol_to_write;
            updateLedStrip();
            delay(1000);
            
            //Mover el cabezal
            switch(movement){
                case LEFT:
                    ledcursor--;
                    ledcursor = constrain(ledcursor, 0, stripmax-1);
                break;
                case RIGHT:
                    ledcursor++;
                    ledcursor = constrain(ledcursor, 0, stripmax-1);
                break;
            }
            
            regist(ledcursor);
            delay(1000);

            //Cambiar el estado
            current_q = next_state;
        }

        fase = FINISHED;
    }
}
