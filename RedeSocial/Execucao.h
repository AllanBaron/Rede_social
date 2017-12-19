#pragma once
#ifndef EXECUCAO_H
#define EXECUCAO_H

#include <string>
#include "Usuario.h"
#include "Post.h"
#include "Interface.h"
#include "DadosPreCarregados.h"
#include "Ferramentas.h"

using namespace std;

void fazer_cadastro(ListaUsuarios *listaUsuarios) {
	int usuarioID = listaUsuarios->size();
	cout << usuarioID << endl;

	string nome;
	string sobrenome;
	string email;
	string senha;
	int dataNascDia;
	int dataNascMes;
	int dataNascAno;
	string sexo;

	system("cls");
	cout << "Nome: ";
	cin >> nome;

	system("cls");
	cout << "Sobrenome: ";
	cin >> sobrenome;

	system("cls");
	cout << "E-mail:";
	cin >> email;

	system("cls");
	cout << "Senha:";
	cin >> senha;

	system("cls");
	cout << "Nascimento" << endl;
	cout << "Digite a dia" << endl;
	cin >> dataNascDia;

	system("cls");
	cout << "Nascimento" << endl;
	cout << "Digite a m\x88s" << endl;
	printf("%02d/", dataNascDia);
	cin >> dataNascMes;

	system("cls");
	cout << "Nascimento" << endl;
	cout << "Digite a ano" << endl;
	printf("%02d/%02d/", dataNascDia, dataNascMes);
	cin >> dataNascAno;

	listaUsuarios->inserir(new ElementoUsuario(new Usuario(usuarioID, nome, sobrenome, email, senha, dataNascDia, dataNascMes, dataNascAno, sexo)));
}

bool fazer_login(ListaUsuarios *listaUsuarios, Usuario *usuarioAtivo) {
	string email = "", senha = "", mensagemErro;
	bool statusEmail = false, statusSenha = false;
	Usuario *usuarioTemp = NULL;

	while (!statusSenha) {
		system("cls");

		if (mensagemErro.length()) {
			cout << mensagemErro << endl;
			if (!statusEmail) {
				if (!fazer_pergunta("E-mail n\xC6o cadastrado\nTentar outro email?", "", true)) {
					break;
				}
			}
			else {
				if (!statusSenha) {
					if (fazer_pergunta("<- Voltar", "", true)) {
						statusEmail = false;
					}
					if (!fazer_pergunta("Tentar outro email?", "", false)) {
						break;
					}
				}
			}

			system("cls");
		}

		if (!statusEmail) {
			cout << "E-mail: ";
			cin >> email;

			statusEmail = listaUsuarios->buscarUsuarioPorEmail(email, usuarioTemp);
		}

		if (statusEmail) {
			cout << "Senha: ";
			cin >> senha;

			if (usuarioTemp != NULL && usuarioTemp->senha == senha) {
				statusSenha = true;
			}
			else {
				mensagemErro = "Senha incorreta";
			}
		}
		else {
			mensagemErro = "E-mail n\xC6o cadastrado";
		}
	}

	return statusSenha;
}

void Fazer_postagem(ListaUsuarios *listaUsuarios, ListaPosts *listaPosts) {

}

void executa_menu_logado(int menuSelecionado, string menuTexto[], string textoEsquerda, string textoDireita) {
	renderiza_rodape();
	renderiza_rodape_logado(textoEsquerda, textoDireita);
	renderiza_menu(menuSelecionado, menuTexto, 2, 0);
}

int menu(ListaUsuarios *listaUsuarios, Usuario *usuarioAtivo) {
	// Menu
	int menuSelecionado = 1;
	string menuTexto[2] = { "Fazer uma postagem",  "Sair" };

	// Mensagens
	string textoDireita = "ESC para ver os Posts  ";
	string textoEsquerda = "  Bem vindo, " + usuarioAtivo->nome + "!";

	system("cls");
	executa_menu_logado(menuSelecionado, menuTexto, textoEsquerda, textoDireita);

	while (true) {
	
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			return 0;
		}
		else if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
			if (menuSelecionado == 2) {
				return 2;
			}
			if (menuSelecionado == 1) {
				return 1;
			}

			executa_menu_logado(menuSelecionado, menuTexto, textoEsquerda, textoDireita);
		}
		else if (GetAsyncKeyState(VK_UP) & 0x8000) {
			if (menuSelecionado > 2) {
				menuSelecionado = 2;
			}
			else {
				menuSelecionado = 1;
			}
			
			executa_menu_logado(menuSelecionado, menuTexto, textoEsquerda, textoDireita);
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			if (menuSelecionado < 1) {
				menuSelecionado = 1;
			}
			else {
				menuSelecionado = 2;
			}
			
			executa_menu_logado(menuSelecionado, menuTexto, textoEsquerda, textoDireita);
		}

		Sleep(60);
	}
}

void executa_rede_social(ListaUsuarios *listaUsuarios, ListaPosts *listaPosts, Usuario *usuarioAtivo) {
	// Menu
	int menuSelecionado = 1;

	// Mensagens 
	string textoDireita = "ESC para acessar o MENU  ";
	string textoEsquerda = "  Bem vindo, " + usuarioAtivo->nome + "!";

	system("cls");
	listaPosts->mostrarTodosPosts(listaUsuarios);

	renderiza_rodape();
	renderiza_rodape_logado(textoEsquerda, textoDireita);
	listaPosts->mostrarTodosPosts(listaUsuarios);
	irParaTop(0, 0);

	while (true) {
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			menuSelecionado = menu(listaUsuarios, usuarioAtivo);

			if (menuSelecionado == 1) {

			}
			else if (menuSelecionado == 2) {
				textoDireita = "Deslogando...    ";
				textoEsquerda = "  At\x82 outra hora " + usuarioAtivo->nome + "!";

				system("cls");
				renderiza_rodape();
				renderiza_rodape_logado(textoEsquerda, textoDireita);
				Sleep(1800);

				break;
			}

			renderiza_rodape();
			renderiza_rodape_logado(textoEsquerda, textoDireita);
			listaPosts->mostrarTodosPosts(listaUsuarios);
			irParaTop(0, 0);
		}
		else if (GetAsyncKeyState(VK_UP) & 0x8000) {
			irParaTop(0, 0);
		}

		Sleep(60);
	}

}

void menu_deslogado_tecla_enter(int menuSelecionado, ListaUsuarios *listaUsuarios, ListaPosts *listaPosts, Usuario *usuarioAtivo) {
	switch (menuSelecionado) {
		case 1:
			clearCin();
			if (fazer_login(listaUsuarios, usuarioAtivo)) {
				executa_rede_social(listaUsuarios, listaPosts, usuarioAtivo);
			}
			break;
		case 2:
			clearCin();
			fazer_cadastro(listaUsuarios);
			break;
		case 3:
			if (listaPosts->size() == 0) {
				inicia_dados_pre_carregados(listaUsuarios, listaPosts);

				loading();
			}
			
			usuarioAtivo = listaUsuarios->primeiro->usuario;

			executa_rede_social(listaUsuarios, listaPosts, usuarioAtivo);
			break;
	}
}

void executa_menu_deslogado(int menuSelecionado, string menuTexto[]) {
	renderiza_rodape();
	renderiza_menu(menuSelecionado, menuTexto, 4, 2);
}

void inicializa() {
	// Variaveis
	Usuario *usuarioAtivo = NULL;

	// Menu
	int menuSelecionado = 1;
	string menuTexto[4] = { "Login-se", "Cadastrar-se", "Dados pre-cadastraos", "Sair" };

	// Listas
	ListaUsuarios *listaUsuarios = new ListaUsuarios(NULL);
	ListaPosts *listaPosts = new ListaPosts(NULL);

	executa_menu_deslogado(menuSelecionado, menuTexto);

	while (true) {
		if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
			if (menuSelecionado == 4) {
				break;
			}

			menu_deslogado_tecla_enter(menuSelecionado, listaUsuarios, listaPosts, usuarioAtivo);

			executa_menu_deslogado(menuSelecionado, menuTexto);
		}
		else if (GetAsyncKeyState(VK_UP) & 0x8000) {
			if (menuSelecionado > 3) {
				menuSelecionado = 3;
			}
			else if (menuSelecionado > 2) {
				menuSelecionado = 2;
			}
			else {
				menuSelecionado = 1;
			}

			executa_menu_deslogado(menuSelecionado, menuTexto);
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			if (menuSelecionado < 2) {
				menuSelecionado = 2;
			}
			else if (menuSelecionado < 3) {
				menuSelecionado = 3;
			}
			else {
				menuSelecionado = 4;
			}

			executa_menu_deslogado(menuSelecionado, menuTexto);
		}
		
		Sleep(60);
	}
}

#endif