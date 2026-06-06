#include "Sculptor.h"
#include <iostream>
#include <fstream>
#include <string>

// criar um cogumelo

int main(void) {
    Sculptor cogumelo(20, 20, 20);

    // cor vermelha e visivel
    cogumelo.setColor(1, 0, 0, 1);

    // chapeu centro em X=10, Y=10, Z=13 e raio 6
    cogumelo.putSphere(10, 10, 13, 6);

    // corta tudo que esta de z=9 para baixo
    cogumelo.cutBox(0, 19, 0, 19, 0, 9);

    // cor branco e visivel
    cogumelo.setColor(1, 1, 1, 1);

    // caule quadrado do chao ate base do chapeu
    cogumelo.putBox(9, 11, 9, 11, 0, 9);

    cogumelo.writeOFF("cogumelo.off");



    return 0;
}

