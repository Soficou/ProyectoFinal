#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

const int tamano = 5;
const int intentosMaximos = 8;

void imprimirMatriz(int matriz[tamano][tamano]) {
    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
            std::cout << "|  " << matriz[i][j] << "  ";
        }
        std::cout << "|" << std::endl;
    }
}

void generarNumeros(int matriz[tamano][tamano]) {
    srand(time(0));

    for (int i = 1; i < tamano - 1; i++) {
        for (int j = 1; j < tamano - 1; j++) {
            matriz[i][j] = rand() % 10 + 1;
        }
    }
}

bool validarRespuesta(int matriz[tamano][tamano], int jugadorX, int jugadorY, int respuesta) {
    int sumaArriba = matriz[jugadorY - 1][jugadorX] + matriz[jugadorY - 2][jugadorX] + matriz[jugadorY - 3][jugadorX];
    int multiplicacionDerecha = matriz[jugadorY][jugadorX + 1];
    int sumaAbajo = matriz[jugadorY + 1][jugadorX] + matriz[jugadorY + 2][jugadorX] + matriz[jugadorY + 3][jugadorX];
    int multiplicacionIzquierda = matriz[jugadorY][jugadorX - 1];

    int resultadoArriba = sumaArriba * multiplicacionDerecha;
    int resultadoAbajo = sumaAbajo * multiplicacionIzquierda;
    int resultadoFinal = resultadoArriba - resultadoAbajo;

    return resultadoFinal == respuesta;
}

int main() {
    int matriz[tamano][tamano];
    int jugadorX = 0;
    int jugadorY = 0;
    int intentos = 0;

    generarNumeros(matriz);

    imprimirMatriz(matriz);

    while (true) {
        COORD coord;
        coord.X = jugadorX * 6 + 3;
        coord.Y = jugadorY + 1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        char tecla;
        std::cin >> tecla;

        int nuevaPosicionX = jugadorX;
        int nuevaPosicionY = jugadorY;

        switch (tecla) {
            case 'w':
                if (jugadorY > 0)
                    nuevaPosicionY--;
                break;
            case 's':
                if (jugadorY < tamano - 1)
                    nuevaPosicionY++;
                break;
            case 'a':
                if (jugadorX > 0)
                    nuevaPosicionX--;
                break;
            case 'd':
                if (jugadorX < tamano - 1)
                    nuevaPosicionX++;
                break;
        }

        if (nuevaPosicionX != jugadorX || nuevaPosicionY != jugadorY) {
            jugadorX = nuevaPosicionX;
            jugadorY = nuevaPosicionY;

            intentos++;

            if (intentos > intentosMaximos) {
                std::cout << "Has perdido la partida. ¡Intenta de nuevo!" << std::endl;
                break;
            }

            system("cls");
            generarNumeros(matriz);
            imprimirMatriz(matriz);

            std::cout << "Intentos: " << intentos << " / " << intentosMaximos << std::endl;
            std::cout << "Ingrese su respuesta: ";

            int respuesta;
            std::cin >> respuesta;

            if (validarRespuesta(matriz, jugadorX, jugadorY, respuesta)) {
                std::cout << "¡Respuesta correcta! Sigue avanzando." << std::endl;
            } else {
                jugadorX = nuevaPosicionX - (nuevaPosicionX - jugadorX);
                jugadorY = nuevaPosicionY - (nuevaPosicionY - jugadorY);

                std::cout << "Respuesta incorrecta. Regresando a la posición anterior." << std::endl;
            }
        }
    }

    return 0;
}
