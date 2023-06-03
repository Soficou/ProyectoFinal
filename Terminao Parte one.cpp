#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <sstream>

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
	
	// Posición inicial del carácter representativo (columna 1, posición vertical aleatoria)
	int posX = 1;
	int posY = rand() % (filas - 2) + 1;
	
	// Número de intentos restantes
	int intentos = 3;
	
	// Resultados de las operaciones almacenados en la meta
	std::vector<int> resultados;
	
	// Generar números aleatorios en las celdas cercanas al personaje
	for (int i = posY - 1; i <= posY + 1; ++i) {
		for (int j = posX - 1; j <= posX + 1; ++j) {
			if (i >= 0 && i < filas && j >= 0 && j < columnas) {
				int numero = rand() % (max - min + 1) + min;
				matriz[i][j] = numero;
			}
		}
	}
	
	// Calcular los valores para la validación
	int arriba = matriz[posY - 1][posX] + matriz[posY - 1][posX - 1] + matriz[posY - 1][posX + 1];
	int izquierda = matriz[posY][posX - 1];
	int abajo = matriz[posY + 1][posX] + matriz[posY + 1][posX - 1] + matriz[posY + 1][posX + 1];
	int derecha = matriz[posY][posX + 1];
	
	// Agregar el resultado de la operación a la meta
	resultados.push_back((arriba + derecha + abajo) * izquierda);
	
	// Bucle para mover el carácter representativo
	char character = '>';
	
	while (intentos > 0) {
		clearScreen();
		
		// Mostrar la matriz con los números visibles
		for (int i = 0; i < filas; ++i) {
			for (int j = 0; j < columnas; ++j) {
				if ((i == posY && j == posX) || (i == filas - 1 && j == columnas - 1)) {
					gotoxy(j * 6, i * 2);
					std::cout << "|" << character << "   ";
				} else if ((i == posY - 1 && j >= posX - 1 && j <= posX + 1) ||
					(i == posY && (j == posX - 1 || j == posX + 1)) ||
					(i == posY + 1 && j >= posX - 1 && j <= posX + 1)) {
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
		std::cout << "Resultado = (" << arriba << " + " << derecha << " + " << abajo << ") * " << izquierda << " = "
			<< (arriba + derecha + abajo) * izquierda << std::endl;
		
		// Solicitar al usuario el resultado del cálculo
		std::cout << std::endl << "Ingrese el resultado del cálculo: ";
		int resultado;
		std::cin >> resultado;
		
		// Validar el resultado
		if (resultado == (arriba + derecha + abajo) * izquierda) {
			std::cout << "Correcto!" << std::endl;
		} else {
			std::cout << "Incorrecto. El resultado correcto es " << (arriba + derecha + abajo) * izquierda << "."
				<< std::endl;
		}
		
		// Mover el personaje según la entrada del usuario
		char movimiento;
		std::cout << "Ingrese la dirección de movimiento (W, A, S, D): ";
		std::cin >> movimiento;
		
		switch (movimiento) {
		case 'W':
		case 'w':
			if (posY > 1) {
				--posY;
			}
			break;
		case 'S':
		case 's':
			if (posY < filas - 2) {
				++posY;
			}
			break;
		case 'A':
		case 'a':
			if (posX > 1) {
				--posX;
			}
			break;
		case 'D':
		case 'd':
			if (posX < columnas - 2) {
				++posX;
			}
			break;
		default:
			break;
		}
		
		// Calcular los nuevos valores para la validación
		arriba = matriz[posY - 1][posX] + matriz[posY - 1][posX - 1] + matriz[posY - 1][posX + 1];
		izquierda = matriz[posY][posX - 1];
		abajo = matriz[posY + 1][posX] + matriz[posY + 1][posX - 1] + matriz[posY + 1][posX + 1];
		derecha = matriz[posY][posX + 1];
		
		// Agregar el resultado de la operación a la meta
		resultados.push_back((arriba + derecha + abajo) * izquierda);
		
		// Comprobar si se alcanzó la meta
		if (posX == columnas - 1 && posY == filas - 1) {
			clearScreen();
			std::cout << "¡Felicidades! Has alcanzado la meta." << std::endl;
			std::cout << "Resultados obtenidos: ";
			for (int i = 0; i < resultados.size(); ++i) {
				std::cout << resultados[i];
				if (i < resultados.size() - 1) {
					std::cout << ", ";
				}
			}
			std::cout << std::endl;
			return 0;
		}
		
		--intentos;
	}
	
	clearScreen();
	bool ganado = true;
	for (int resultado : resultados) {
		if (resultado == 0) {
			ganado = false;
			break;
		}
	}
	
	if (ganado) {
		std::cout << "¡Felicidades! Has alcanzado la meta." << std::endl;
		std::cout << "Resultados obtenidos: ";
		for (int i = 0; i < resultados.size(); ++i) {
			std::cout << resultados[i];
			if (i < resultados.size() - 1) {
				std::cout << ", ";
			}
		}
		std::cout << std::endl;
	} else {
		std::cout << "Lo siento, no has logrado completar la meta." << std::endl;
	}
	
	return 0;
}

