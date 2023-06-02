#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
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

int main() {
	// Inicializar el generador de números aleatorios con una semilla basada en el tiempo actual
	srand(time(0));
	
	// Definir las dimensiones de la matriz
	const int filas = 5;
	const int columnas = 5;
	
	// Crear una matriz vacía utilizando vectores anidados
	std::vector<std::vector<std::string>> matriz(filas, std::vector<std::string>(columnas, "   "));
	
	// Definir el rango de los números aleatorios
	int min = 1;
	int max = 10;
	
	// Obtener la posición inicial del carácter representativo
	int posX = 0;
	int posY = rand() % filas;
	
	// Número de intentos restantes
	int intentos = 8;
	
	// Bucle para mover el carácter representativo
	char character = '>';
	
	while (intentos > 0) {
		// Limpiar la pantalla
		clearScreen();
		
		// Actualizar la matriz con los números cercanos al personaje
		for (int i = std::max(posY - 1, 0); i <= std::min(posY + 1, filas - 1); ++i) {
			for (int j = std::max(posX - 1, 0); j <= std::min(posX + 1, columnas - 1); ++j) {
				int numero = rand() % (max - min + 1) + min;
				matriz[i][j] = intToString(numero);
			}
		}
		
		// Mostrar la matriz con el carácter representativo y los números cercanos
		for (int i = 0; i < filas; ++i) {
			std::cout << "|";
			for (int j = 0; j < columnas; ++j) {
				if (i == posY && j == posX) {
					std::cout << " " << character << "  |";
				} else {
					std::cout << std::setw(5) << matriz[i][j] << " |";
				}
			}
			std::cout << std::endl;
			
			if (i < filas - 1) {
				std::cout << "|------|------|------|------|------|" << std::endl;
			}
		}
		
		// Obtener la entrada del usuario
		std::cout << "Presione W/A/S/D para mover el carácter representativo. Presione Q para salir." << std::endl;
		char input;
		std::cin >> input;
		
		if (input == 'Q' || input == 'q') {
			break;
		}
		
		// Actualizar la posición del personaje
		int prevX = posX;
		int prevY = posY;
		
		if (input == 'W' || input == 'w') {
			posY--;
			if (posY < 0) posY = 0;
		} else if (input == 'A' || input == 'a') {
			posX--;
			if (posX < 0) posX = 0;
		} else if (input == 'S' || input == 's') {
			posY++;
			if (posY >= filas) posY = filas - 1;
		} else if (input == 'D' || input == 'd') {
			posX++;
			if (posX >= columnas) posX = columnas - 1;
		}
		
		// Realizar los cálculos de acuerdo a las reglas especificadas
		int arriba = std::stoi(matriz[std::max(posY - 3, 0)][posX]) + std::stoi(matriz[std::max(posY - 3, 0)][std::max(posX - 1, 0)]) + std::stoi(matriz[std::max(posY - 3, 0)][std::min(posX + 1, columnas - 1)]);
		int abajo = std::stoi(matriz[std::min(posY + 1, filas - 1)][posX]) + std::stoi(matriz[std::min(posY + 1, filas - 1)][std::max(posX - 1, 0)]) + std::stoi(matriz[std::min(posY + 1, filas - 1)][std::min(posX + 1, columnas - 1)]);
		int derecha = std::stoi(matriz[posY][std::min(posX + 1, columnas - 1)]);
		int izquierda = std::stoi(matriz[posY][std::max(posX - 1, 0)]);
		
		int resultadoArriba = (arriba * derecha) - abajo;
		int resultadoAbajo = (abajo * izquierda) - arriba;
		
		std::cout << "Resultado arriba: " << resultadoArriba << std::endl;
		std::cout << "Resultado abajo: " << resultadoAbajo << std::endl;
		
		std::cout << "Ingrese el resultado del cálculo: ";
		int resultado;
		std::cin >> resultado;
		
		if (resultado == resultadoArriba && resultado == resultadoAbajo) {
			std::cout << "Correcto!" << std::endl;
		} else {
			std::cout << "Incorrecto. El resultado correcto es " << resultadoArriba << " y " << resultadoAbajo << "." << std::endl;
			posX = prevX;
			posY = prevY;
			--intentos;
		}
		
		std::cout << "Presione cualquier tecla para continuar." << std::endl;
		std::cin.ignore();
		std::cin.get();
	}
	
	if (intentos > 0) {
		std::cout << "¡Felicidades! Has llegado a la meta." << std::endl;
	} else {
		std::cout << "Lo siento, has perdido." << std::endl;
	}
	
	return 0;
}
