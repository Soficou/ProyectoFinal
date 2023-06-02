
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <ctime>
	
#ifdef _WIN32
#include <windows.h>
#endif
	
	// Funci�n para convertir un entero en una cadena
	std::string intToString(int number) {
	std::stringstream ss;
	ss << std::setw(4) << std::setfill(' ') << number;
	return ss.str();
}
	
	// Funci�n para ordenar la matriz
	void ordenarMatriz(std::vector<std::vector<std::string>>& matriz) {
		int filas = matriz.size();
		int columnas = matriz[0].size();
		
		for (int i = 0; i < filas; ++i) {
			for (int j = 0; j < columnas; ++j) {
				for (int k = 0; k < filas; ++k) {
					for (int l = 0; l < columnas; ++l) {
						int valorActual = std::stoi(matriz[i][j]);
						int valorSiguiente = std::stoi(matriz[k][l]);
						if (valorActual > valorSiguiente) {
							std::swap(matriz[i][j], matriz[k][l]);
						}
					}
				}
			}
		}
	}
	
	// Funci�n para limpiar la pantalla en Windows
	void clearScreen() {
#ifdef _WIN32
		std::system("cls");
#else
		std::system("clear");
#endif
	}
	
	int main() {
		// Inicializar el generador de n�meros aleatorios con una semilla basada en el tiempo actual
		srand(time(0));
		
		// Definir las dimensiones de la matriz
		const int filas = 5;
		const int columnas = 5;
		
		// Crear una matriz vac�a utilizando vectores anidados
		std::vector<std::vector<std::string>> matriz(filas, std::vector<std::string>(columnas, "    "));
		
		// Definir el rango de los n�meros aleatorios
		int min = 1;
		int max = 10;
		
		// Generar n�meros aleatorios del 1 al 10 y llenar la matriz
		for (int i = 0; i < filas; ++i) {
			for (int j = 0; j < columnas; ++j) {
				int numero = rand() % (max - min + 1) + min;
				matriz[i][j] = intToString(numero);
			}
		}
		
		// Ordenar la matriz
		ordenarMatriz(matriz);
		
		// Posici�n inicial del car�cter representativo
		int posX = 0;
		int posY = 0;
		
		// Bucle para mover el car�cter representativo
		char character = '>';
		
		while (true) {
			// Limpiar la pantalla
			clearScreen();
			
			// Mostrar la matriz con el car�cter representativo
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
			std::cout << "Presione W/A/S/D para mover el car�cter representativo. Presione Q para salir." << std::endl;
			char input;
			std::cin >> input;
			
			// Actualizar la posici�n del car�cter representativo
			if (input == 'W' || input == 'w') {
				if (posY > 0) {
					--posY;
				}
			} else if (input == 'A' || input == 'a') {
				if (posX > 0) {
					--posX;
				}
			} else if (input == 'S' || input == 's') {
				if (posY < filas - 1) {
					++posY;
				}
			} else if (input == 'D' || input == 'd') {
				if (posX < columnas - 1) {
					++posX;
				}
			} else if (input == 'Q' || input == 'q') {
				break;
			}
		}
		
		return 0;
	}
