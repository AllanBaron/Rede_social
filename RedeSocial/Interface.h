#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H

#include <windows.h>
#include <iostream>
#include <string>
#include "Ferramentas.h"

using namespace std;

void loading() {
	string tamanhoTexto, antesCode = "\xB1", dapois = "\xDB";

	system("cls");
	alterarCorTexto(COR_PADRAO);
	
	cout << "\n\n\n";
	cout << alinharTextoCentro("Cadastrando usu\xA0rios\n");
	cout << "\n\n\n\n\n";

	for (int i = 0; i <= 100; i++) {
		tamanhoTexto += antesCode;
	}
	
	preencherQuantidadeDeCaracteres(' ', quantidadeParaAlinharCentro(tamanhoTexto));
	
	alterarCorTexto(COR_VERDE_ESCURO);
	cout << tamanhoTexto;

	cout << "\r";

	alterarCorTexto(COR_VERDE_CLARO);

	preencherQuantidadeDeCaracteres(' ', quantidadeParaAlinharCentro(tamanhoTexto));
	for (int i = 0; i <= 100; i++) {
		cout << dapois;
		Sleep(20);

	}
	cout << "\n\n\n\n\n";

	cout << alinharTextoCentro("Todos os usu\xA0rios cadastrados com sucesso!!!\n");

	Sleep(1800);

	alterarCorTexto(COR_PADRAO);
}

void renderiza_rodape() {
	system("cls");

	preencherLinhaComCaractere('\xDF');

	cout << alinharTextoCentro("\xCD\xCD\xB9\xBA\xBA     Social PlusPlus     \xBA\xBA\xCC\xCD\xCD");

	cout << "\n";
	redefinirCorTexto();
	preencherLinhaComCaractere('\xDC');
	
}

void renderiza_rodape_logado(string textoEsquerda, string textoDireita) {
	alterarCorTexto(128);
	preencherLinhaComCaractere(' ');
	cout << textoEsquerda;

	alinharTextoDireita(textoDireita);
	preencherLinhaComCaractere(' ');
	
	redefinirCorTexto();
	preencherLinhaComCaractere('\xDF');

	cout << "\n\n";
}

bool fazer_pergunta(string pergunta, string menssagemErro, bool limparTela) {

	string resporta;

	do {
		if (limparTela) {
			system("cls");
		}

		if (menssagemErro.size()) {
			cout << menssagemErro << endl;
		}

		cout << pergunta << " Sim / N\xC6o" << endl;
		cin >> resporta;

		menssagemErro = "Valor invalido!";
	}
	while(resporta != "Sim" && resporta != "sim" && resporta != "S" && resporta != "s" && resporta != "N\xC6o" && resporta != "n\xC6o" && resporta != "N" && resporta != "n");

	
	if (resporta == "Sim" || resporta == "sim" || resporta == "S" || resporta == "s") {
		return true;
	}
	else if (resporta == "Não" || resporta == "n\xC6o" || resporta == "N" || resporta == "n") {
		return false;
	}

}

void renderiza_menu(int selecionado, string texto[], int tamanho, int quebrarLinha) {

	for (int i = 0; i < quebrarLinha; i++) {
		cout << "\n";
	}	

	for (int i = 0; i < tamanho; i++) {
		if (selecionado == i+1) {
			cout << alinharTextoCentro(">> " + texto[i] + " <<") << endl;
		}
		else {
			cout << alinharTextoCentro(texto[i]) << endl;
		}
	}
}

#endif