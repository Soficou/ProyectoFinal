# include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <conio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#endif

// Funci n para convertir un entero en una cadena
std::string intToString(int number) {
	std::stringstream ss;
	ss << std::setw(4) << std::setfill(' ') << number;
	return ss.str();
}

// Funcion para limpiar la pantalla en Windows
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
	system("color 17");
	// Inicializar el generador de n meros aleatorios con una semilla basada en el tiempo actual
	srand(time(0));
	
	// Definir las dimensiones de la matriz
	const int filas = 5;
	const int columnas = 5;
	
	// Crear una matriz vac a utilizando vectores anidados
	std::vector<std::vector<int>> matriz(filas, std::vector<int>(columnas, 0));
	
	// Definir el rango de los n meros aleatorios
	int min = 1;
	int max = 10;
	
	// Posici n inicial del car cter representativo (columna 1, posici n vertical aleatoria)
	int posX = 1;
	int posY = rand() % (filas - 2) + 1;
	
	// N mero de intentos restantes
	int intentos = 3;
	
	// Resultados de las operaciones almacenados en la meta
	std::vector<int> resultados;
	
	// Generar n meros aleatorios en las celdas cercanas al personaje
	for (int i = posY - 1; i <= posY + 1; ++i) {
		for (int j = posX - 1; j <= posX + 1; ++j) {
			int numero = rand() % (max - min + 1) + min;
			matriz[i][j] = numero;
		}
	}
	
	// Calcular los valores para la validaci n
	int arriba = matriz[posY - 1][posX] + matriz[posY - 1][posX - 1] + matriz[posY - 1][posX + 1];
	int derecha = matriz[posY][posX + 1];
	int izquierda = matriz[posY][posX - 1];
	int abajo = matriz[posY + 1][posX] + matriz[posY + 1][posX - 1] + matriz[posY + 1][posX + 1];
	
	
	// Agregar el resultado de la operaci n a la meta
	resultados.push_back((arriba*derecha)-(abajo*izquierda));
	
	// Bucle para mover el car cter representativo
	char character = '>';
	
	// Variable para almacenar la tecla presionada
	char key;
	
	// Mostrar la matriz inicial
	clearScreen();
	
	while (intentos > 0) {
		// Mostrar la matriz con los n meros visibles
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
			
		// Mostrar los valores para la validaci n
		gotoxy(0, filas * 2 + 2);
		// Solicitar al usuario el resultado del c lculo
		
		std::cout << std::endl << "Ingrese el resultado del c lculo: ";
		int resultado;
		std::cin >> resultado;
		
		
		// Validar el resultado
		if (resultado == ((arriba*derecha)-(abajo*izquierda))) {
			std::cout << "Correcto!" << std::endl;
			std::cout << std::endl << "Ingrese el movimiento (W: arriba, S: abajo, A: izquierda, D: derecha): ";
		} else {
			std::cout << "Incorrecto. El resultado correcto es " << ((arriba*derecha)-(abajo*izquierda)) << "."
				<< std::endl;
		}
		
		// Actualizar la posici n del personaje seg n la tecla presionada
		key = _getch();
		switch (key) {
		case 'w': // Arriba
		case 'W':
			if (posY > 1) posY--;
			break;
		case 'a': // Izquierda
		case 'A':
			if (posX > 1) posX--;
			break;
		case 's': // Abajo
		case 'S':
			if (posY < filas - 2) posY++;
			break;
		case 'd': // Derecha
		case 'D':
			if (posX < columnas - 2) posX++;
			break;
		default:
			break;
		}
		
		// Actualizar los n meros en las celdas cercanas al personaje
		for (int i = posY - 1; i <= posY + 1; ++i) {
			for (int j = posX - 1; j <= posX + 1; ++j) {
				int numero = rand() % (max - min + 1) + min;
				matriz[i][j] = numero;
			}
		}
		
		// Calcular los nuevos valores para la validaci n
		arriba = matriz[posY - 1][posX] + matriz[posY - 1][posX - 1] + matriz[posY - 1][posX + 1];
		izquierda = matriz[posY][posX - 1];
		abajo = matriz[posY + 1][posX] + matriz[posY + 1][posX - 1] + matriz[posY + 1][posX + 1];
		derecha = matriz[posY][posX + 1];
		
		// Agregar el resultado de la operaci n a la meta
		resultados.push_back((arriba*derecha)-(abajo*izquierda));
		
		// Reducir los intentos restantes
		intentos--;
		
		// Limpiar la pantalla para el siguiente movimiento
		clearScreen();
	}
	
	// Mostrar la matriz final con los n meros visibles
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
	
	// Mostrar los resultados de las operaciones en la meta
	gotoxy(0, filas * 2 + 2);
	std::cout << "Resultados en la meta: ";
	for (int i = 0; i < resultados.size(); ++i) {
		std::cout << resultados[i];
		if (i < resultados.size() - 1) {
			std::cout << ", ";
		}}
	std::cout << std::endl;
	
	// Calcular el resultado final
	int resultadoFinal = resultados[0] - resultados[1];
	
	// Mostrar el resultado final
	std::cout << "El resultado final es: " << resultadoFinal << std::endl;
	
	bool ganado = true;
	for (int resultado : resultados) {
		if (resultado == 0) {
			ganado = false;
			break;
		}}
	
	// Mostrar el mensaje de ganador o perdedor
	clearScreen();
	if (ganado) {
		std::cout << " Felicidades! Has completado la meta." << std::endl;
	} else {
		std::cout << "Lo siento, no has logrado completar la meta." << std::endl;
		
		
	}
	system("color 17");
	
	return 0;
}
