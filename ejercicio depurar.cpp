#include <iostream>
using namespace std;    
void agregarTiempo(int &tiempo, int extra){ 
    tiempo += extra; 
    if(tiempo > 60) {
        tiempo = 60; 
}
};
