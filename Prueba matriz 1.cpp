#include <iostream>
#include <windows.h>

#define FILAS 5
#define COLUMNAS 5

void gotoxy(int x, int y)
{
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hCon, dwPos);
}

void dibujarMatriz()
	
{
	int inicioX = 2;  // Ajustar el valor según la posición deseada de la matriz en la pantalla
	int inicioY = 2;  // Ajustar el valor según la posición deseada de la matriz en la pantalla
	
	for (int i = 0; i < FILAS; i++)
	{
		for (int j = 0; j < COLUMNAS; j++)
		{
			int posX = inicioX + j * 10;  // Ajustar el valor para espaciar las celdas horizontalmente
			int posY = inicioY + i * 4;   // Ajustar el valor para espaciar las celdas verticalmente
			
			gotoxy(posX, posY);
			std::cout << char(218) << char(196) << char(196) << char(196) << char(191);
			
			gotoxy(posX, posY + 1);
			std::cout << char(179) << "   " << char(179);
			
			gotoxy(posX, posY + 2);
			std::cout << char(179) << "   " << char(179);
			
			gotoxy(posX, posY + 3);
			std::cout << char(192) << char(196) << char(196) << char(196) << char(217);
		}
	}
}

int main()
{
	
	system("cls");
	system("color 17");
	dibujarMatriz();
	
	return 0;
}
