#include <iostream>
#include <vector>
#include <sstream>
#include <random>
#include <iomanip>

// Función para convertir un entero en una cadena
std::string intToString(int number) {
	std::stringstream ss;
	ss << std::setw(4) << std::setfill(' ') << number;
	return ss.str();
}

// Función para ordenar la matriz
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

int main() {
	// Definir las dimensiones de la matriz
	const int filas = 5;
	const int columnas = 5;

	// Crear una matriz vacía utilizando vectores anidados
	std::vector<std::vector<std::string>> matriz(filas, std::vector<std::string>(columnas, "    "));

	// Generar números aleatorios y llenar la matriz
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(1, filas * columnas);

	for (int i = 0; i < filas; ++i) {
		for (int j = 0; j < columnas; ++j) {
			int numero = dist(gen);
			matriz[i][j] = intToString(numero);
		}
	}

	// Ordenar la matriz
	ordenarMatriz(matriz);

	// Posición inicial del carácter representativo
	int posX = 0;
	int posY = 0;

	// Bucle para mover el carácter representativo
	char character = '>';

	while (true) {
		// Limpiar la pantalla
		system("clear");

		// Mostrar la matriz con el carácter representativo
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

		// Actualizar la posición del carácter representativo
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
