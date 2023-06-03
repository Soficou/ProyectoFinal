#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#endif

// Función para convertir un entero en una cadena
std::string intToString(int number) {
	std::stringstream ss;
	ss << std::setw(4) << std::setfill(' ') << number;
	return ss.str();
}

// Función para limpiar la pantalla en Windows
void clearScreen() {
#ifdef _WIN32
	std::system("cls");
#else
	std::system("clear");
#endif
}

#ifdef _WIN32
void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
#else
void gotoxy(int x, int y) {
	printf("\033[%d;%df", y + 1, x + 1);
	fflush(stdout);
}
#endif

int main() {
	// Inicializar el generador de números aleatorios con una semilla basada en el tiempo actual
	srand(time(0));
	
	// Definir las dimensiones de la matriz
	const int filas = 5;
	const int columnas = 5;
	
	// Crear una matriz vacía utilizando vectores anidados
	std::vector<std::vector<int>> matriz(filas, std::vector<int>(columnas, 0));
	
	// Definir el rango de los números aleatorios
	int min = 1;
	int max = 10;
	
	// Posición inicial del carácter representativo (columna 0, posición vertical aleatoria)
	int posX = 0;
	int posY = rand() % filas;
	
	// Número de intentos restantes
	int intentos = 8;
	
	// Bucle para mover el carácter representativo
	char character = '>';
	
	while (intentos > 0) {
		// Limpiar la pantalla
		clearScreen();
		
		// Generar números aleatorios en las celdas cercanas al personaje
		for (int i = std::max(posY - 1, 0); i <= std::min(posY + 1, filas - 1); ++i) {
			for (int j = std::max(posX - 1, 0); j <= std::min(posX + 1, columnas - 1); ++j) {
				int numero = rand() % (max - min + 1) + min;
				matriz[i][j] = numero;
			}
		}
		
		// Calcular los valores para la validación
		int arriba = matriz[std::max(posY - 3, 0)][posX] + matriz[std::max(posY - 2, 0)][posX] + matriz[std::max(posY - 1, 0)][posX];
		int derecha = matriz[posY][posX + 1];
		int abajo = matriz[posY][std::max(posX - 3, 0)] + matriz[posY][std::max(posX - 2, 0)] + matriz[posY][std::max(posX - 1, 0)];
		int izquierda = matriz[posY - 1][posX];
		
		// Mostrar la matriz en la pantalla
		for (int i = 0; i < filas; ++i) {
			for (int j = 0; j < columnas; ++j) {
				if (i == posY && j == posX) {
					gotoxy(j * 6, i * 2);
					std::cout << "|" << character << "   ";
				} else if (i >= std::max(posY - 1, 0) && i <= std::min(posY + 1, filas - 1) && j >= std::max(posX - 1, 0) && j <= std::min(posX + 1, columnas - 1)) {
					gotoxy(j * 6, i * 2);
					std::cout << "|" << intToString(matriz[i][j]);
				} else {
					gotoxy(j * 6, i * 2);
					std::cout << "|      ";
				}
			}
			std::cout << "|" << std::endl;
		}
		
		// Mostrar los valores para la validación
		gotoxy(0, filas * 2 + 2);
		std::cout << "Resultado = (" << arriba << " + " << matriz[posY][posX] << " + " << izquierda << ") * " << abajo << " = " << (arriba + matriz[posY][posX] + izquierda) * abajo;
		
		// Solicitar al usuario el resultado del cálculo
		std::cout << std::endl << "Ingrese el resultado del cálculo: ";
		int resultado;
		std::cin >> resultado;
		
		// Validar el resultado
		if (resultado == (arriba + matriz[posY][posX] + izquierda) * abajo) {
			std::cout << "Correcto!" << std::endl;
		} else {
			std::cout << "Incorrecto. El resultado correcto es " << (arriba + matriz[posY][posX] + izquierda) * abajo << "." << std::endl;
			posX += 2;
			intentos -= 2;
		}
		
		// Esperar antes de continuar al siguiente movimiento
		Sleep(1000);
	}
	
	// Mostrar el mensaje final
	clearScreen();
	std::cout << "Lo siento, has perdido." << std::endl;
	
	return 0;
}
