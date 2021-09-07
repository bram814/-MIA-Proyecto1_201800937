//
// Created by abraham on 15/08/21.
//

#include "../../Header/Script/Exec.h"

void Exec::execute_exec(Nodo *root) {
    list<Nodo> :: iterator temp;
    temp = root->hijo.begin()->hijo.begin();
    int i = 0;
    string input;
    while(i < root->hijo.begin()->contador) {
        if(temp->tipo == "PATH"){
            ifstream file(temp->valor);
            while(getline(file, input)){
                if(input.length()>1 && input[0]!='#'){
                    Controlador::print(">> " + input);
                    Controlador::command(input);
                }
            }
            break;
        }
        temp++;
        i++;
    }
}
