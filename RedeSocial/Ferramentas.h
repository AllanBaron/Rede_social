#pragma once
#ifndef FERRAMENTAS_H
#define FERRAMENTAS_H

#include <windows.h>
#include <string>
const int COR_PADRAO = 7, COR_VERDE_ESCURO = 2, COR_CINZA = 8, COR_BRANCO = 15, COR_VERDE_CLARO = 10, COR_VERMELHO = 12, COR_AZUL_CLARO = 11;

using namespace std;

// Window
void MaximizetWindow() {
	HWND consoleWindow = GetConsoleWindow();
	ShowWindow(consoleWindow, SW_MAXIMIZE);
}

void RestoreWindow() {
	HWND consoleWindow = GetConsoleWindow();
	ShowWindow(consoleWindow, SW_RESTORE);
}

void limparTela() {
	system("cls");
}

void clearCin() {
	string temp;
	cin.clear();

	getline(cin, temp);
	cin.ignore(100, '\n');
}

void irParaTop(int x, int y) {
	COORD coord; // coordinates
	coord.X = x; coord.Y = y; // X and Y coordinates
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // moves to the coordinates
}

// Texto
string quabraLinhaTexto(string texto, int delimitador) {
	bool quebrarLinha = false;
	int contPalavras = 1;

	for (size_t i = 0; i < texto.length(); i++) {
		if (quebrarLinha && texto[i] == ' ') {
			i++;
			string init = texto.substr(0, i);
			string end = texto.substr(i, texto.length());
			texto = init + "\n" + end;

			quebrarLinha = false;
		}
		else if (contPalavras % delimitador == 0) {
			quebrarLinha = true;
		}
		else if (texto[i] == '\n') {

			if (texto[i + 1] == ' ') {
				i++;
				string init = texto.substr(0, i++);
				string end = texto.substr(i, texto.length());
				texto = init + end;
			}
			contPalavras = 0;
		}

		contPalavras++;
	}

	return texto;
}

COORD posicaoDeInsercaoNoConsole() {
	CONSOLE_SCREEN_BUFFER_INFO consoleBuffer;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleBuffer))
	{
		return consoleBuffer.dwCursorPosition;
	}
	else
	{
		return { 0, 0 };
	}
}

int larguraDoTerminal() {
	CONSOLE_SCREEN_BUFFER_INFO consoleBuffer;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleBuffer);

	int largura = consoleBuffer.srWindow.Right - consoleBuffer.srWindow.Left;
	return (largura);
}

int meioDoTerminal() {
	return (larguraDoTerminal() / 2);
}

int quantidadeParaAlinharCentro(string texto) {
	return (meioDoTerminal() - (texto.size() / 2));
}

int quantidadeParaAlinharDireita(string texto) {
	return (larguraDoTerminal() - posicaoDeInsercaoNoConsole().X - texto.size());
}

void preencherLinhaComCaractere(char caractere) {
	cout << string(larguraDoTerminal()+1, caractere) << endl;
}

void preencherQuantidadeDeCaracteres(char caractere, int quantidade) {
	cout << string(quantidade, caractere);
}

void alterarCorTexto(int cor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor);
}

void redefinirCorTexto() {
	alterarCorTexto(COR_PADRAO);
}

void alinharTextoDireita(string texto) {
	preencherQuantidadeDeCaracteres(' ', quantidadeParaAlinharDireita(texto)+1);
	cout << texto << endl;
}

string alinharTextoCentro(string texto) {
	preencherQuantidadeDeCaracteres(' ', quantidadeParaAlinharCentro(texto));
	return texto;
}


#endif