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

string valida_usuario(ListaUsuarios *listaUsuarios) {
	string usuarioLogin, mensagemErro;
	Usuario *usuarioTemp = NULL;

	while (true) {
		limparTela();
		renderiza_rodape(1);

		if (mensagemErro.length()) {
			alterarCorTexto(COR_VERMELHO);
			cout << mensagemErro << endl;
			redefinirCorTexto();
		}
		cout << "Usu\xA0rio: @";
		cin >> usuarioLogin;

		if (!listaUsuarios->buscarUsuario(usuarioLogin, usuarioTemp)) {
			break;
		}
		mensagemErro = "Usu\xA0rio j\xA0 exite!\n";
	}

	return usuarioLogin;

}

string valida_senha() {
	string senha, senhaAutenticacao, mensagemErro;
	while (true) {
		limparTela();
		renderiza_rodape(1);

		if (mensagemErro.length()) {
			alterarCorTexto(COR_VERMELHO);
			cout << mensagemErro << endl;
			redefinirCorTexto();
		}

		cout << "Senha: ";
		cin >> senha;

		cout << "Repita a senha novamente: ";
		cin >> senhaAutenticacao;

		if (senha == senhaAutenticacao) {
			break;
		}

		mensagemErro = "As senhas n\xC6o s\xC6o iguais!\n";
	}

	return senha;
}

int valida_dia() {
	int dia;
	string mensagemErro;

	while (true) {
		limparTela();
		renderiza_rodape(1);

		if (mensagemErro.length()) {
			alterarCorTexto(COR_VERMELHO);
			cout << mensagemErro << endl;
			redefinirCorTexto();
		}

		cout << "Data de nascimento" << endl;
		cout << "Digite o dia" << endl;
		cin >> dia;

		if (dia > 0 && dia <= 31) {
			break;
		}

		mensagemErro = "Dia invalido!\n";
	}

	return dia;
}

int valida_mes(int dia) {
	int mes;
	string mensagemErro;

	while (true) {
		limparTela();
		renderiza_rodape(1);

		if (mensagemErro.length()) {
			alterarCorTexto(COR_VERMELHO);
			cout << mensagemErro << endl;
			redefinirCorTexto();
		}

		cout << "Data de nascimento" << endl;
		cout << "Digite o m\x88s" << endl;		
		printf("%02d/", dia);
		cin >> mes;

		if (mes > 0 && mes <= 12) {
			break;
		}

		mensagemErro = "M\x88s invalido!\n";
	}

	return mes;
}

int valida_ano(int dia, int mes) {
	int ano;
	string mensagemErro;

	while (true) {
		system("cls");
		renderiza_rodape(1);

		if (mensagemErro.length()) {
			alterarCorTexto(COR_VERMELHO);
			cout << mensagemErro << endl;
			redefinirCorTexto();
		}

		cout << "Data de nascimento" << endl;
		cout << "Digite a ano" << endl;
		printf("%02d/%02d/", dia, mes);
		cin >> ano;

		if (ano > 1900 && ano <= 1999) {
			break;
		}
		else if (ano > 2017) {
			mensagemErro = "Ops, Voc\x88 ainda n\xC6o nasceu!\n";
		}
		else if (ano > 1999) {
			mensagemErro = "Voc\x88 tende ter mais de 18 anos!\n";
		}
		else {
			mensagemErro = "Ano invalido!\n";
		}

		
	}

	return ano;
}

string valida_sexo() {
	int escolhar;
	string sexo, mensagemErro;

	while (true) {
		limparTela();
		renderiza_rodape(1);

		if (mensagemErro.length()) {
			alterarCorTexto(COR_VERMELHO);
			cout << mensagemErro << endl;
			redefinirCorTexto();
		}

		cout << "Sexo" << endl;
		cout << "1 - Masculino" << endl;
		cout << "2 - Feminino\n" << endl;
		
		cout << "Escolha: ";
		cin >> escolhar;

		if (escolhar == 1) {
			sexo = "Masculino";
			break;
		}
		else if(escolhar == 2) {
			sexo = "Feminino";
			break;
		}

		mensagemErro = "Valor invalido!\n";
	}

	return sexo;
}

void fazer_cadastro(ListaUsuarios *listaUsuarios) {
	int usuarioID = listaUsuarios->size();
	Usuario *usuarioTemp = NULL;

	string nome;
	string sobrenome;
	string usuarioLogin;
	string senha;
	int dataNascDia;
	int dataNascMes;
	int dataNascAno;
	string sexo;

	limparTela();
	renderiza_rodape(1);
	cout << "Nome: ";
	cin >> nome;

	limparTela();
	renderiza_rodape(1);
	cout << "Sobrenome: ";
	cin >> sobrenome;

	usuarioLogin = valida_usuario(listaUsuarios);
	
	senha = valida_senha();

	dataNascDia = valida_dia();
	dataNascMes = valida_mes(dataNascDia);
	dataNascAno = valida_ano(dataNascDia, dataNascMes);
	Sleep(800);

	sexo = valida_sexo();

	listaUsuarios->inserir(new ElementoUsuario(new Usuario(usuarioID, nome, sobrenome, usuarioLogin, senha, dataNascDia, dataNascMes, dataNascAno, sexo)));
}

bool fazer_login(ListaUsuarios *listaUsuarios, Usuario *&usuarioAtivo) {
	string usuarioLogin = "", senha = "", mensagemErro;
	bool statusEmail = false, statusSenha = false;
	Usuario *usuarioTemp = NULL;

	while (!statusSenha) {
		limparTela();
		renderiza_rodape(1);

		if (mensagemErro.length()) {
			
			alterarCorTexto(COR_VERMELHO);
			cout << mensagemErro << endl;
			redefinirCorTexto();

			if (!statusEmail) {
				if (!fazer_pergunta("Tentar outro email?", "", false)) {
					break;
				}

				limparTela();
				renderiza_rodape(1);
			}
			else {
				if (!statusSenha) {
					if (!fazer_pergunta("Tentar novamente?", "", false)) {
						break;
					}

					limparTela();
					renderiza_rodape(1);

					cout << "Usu\xA0rio: @";
					cout << usuarioLogin << "\n";
				}
			}			
		}

		if (!statusEmail) {
			cout << "Usu\xA0rio: @";
			cin >> usuarioLogin;

			statusEmail = listaUsuarios->buscarUsuario(usuarioLogin, usuarioTemp);
		}

		if (statusEmail) {
			cout << "Senha: ";
			cin >> senha;

			if (usuarioTemp != NULL && usuarioTemp->senha == senha) {
				statusSenha = true;
				usuarioAtivo = usuarioTemp;
			}
			else {
				mensagemErro = "Senha incorreta\n";
			}
		}
		else {
			mensagemErro = "E-mail n\xC6o cadastrado\n";
		}
	}

	return statusSenha;
}

void Fazer_postagem(ListaUsuarios *listaUsuarios, ListaPosts *listaPosts, Usuario *usuarioAtivo, string textoEsquerda, string textoDireita) {
	string texto, textoTemp, citarUsuario, usuarioCitado, mensagemErro;
	Usuario *usuarioTemp = NULL;

	limparTela();
	renderiza_rodape_logado(textoEsquerda, textoDireita);

	cout << "Digite abaixo:" << endl;
	clearCin();
	cin >> texto;
	getline(cin, textoTemp);

	texto += textoTemp;

	if (fazer_pergunta("\n\nCitar outro usu\xA0rio?", "", false)) {
		while (true) {
			if (mensagemErro.length()) {
				limparTela();
				renderiza_rodape_logado(textoEsquerda, textoDireita);

				cout << "Texto:" << endl;
				cout << texto;

				alterarCorTexto(COR_VERMELHO);
				cout << mensagemErro << endl;
				redefinirCorTexto();

				if (fazer_pergunta("\nCancelar?", "", false)) {
					break;
				}

				limparTela();
				renderiza_rodape_logado(textoEsquerda, textoDireita);

				cout << "Digite abaixo:" << endl;
				cout << texto;

				alterarCorTexto(COR_VERMELHO);
				cout << mensagemErro << endl;
				redefinirCorTexto();
			}

			cout << "Usu\xA0rio: @";
			cin >> citarUsuario;

			if (listaUsuarios->buscarUsuario(citarUsuario, usuarioTemp)){
				usuarioCitado = usuarioTemp->nome;
				break;
			}

			mensagemErro = "\n\nUsu\xA0rio n\xC6o exite!\n";

			
		}
		
	}
	
	if (texto.length() > 0) {
		cout << texto;
		listaPosts->inserir(new ElementoPost(new Post(listaPosts->size(), usuarioAtivo->ID, texto, usuarioCitado)));
	}
	
}

void executa_menu_logado(int menuSelecionado, string menuTexto[], string textoEsquerda, string textoDireita) {
	limparTela();
	renderiza_rodape_logado(textoEsquerda, textoDireita);
	renderiza_menu(menuSelecionado, menuTexto, 2, 0);
}

int menu(ListaUsuarios *listaUsuarios, Usuario *usuarioAtivo) {
	// Menu
	int menuSelecionado = 1;
	string menuTexto[2] = { "Fazer uma postagem",  "Sair" };

	// Mensagens
	string textoDireita = "ESC para ver os Posts  ";
	string textoEsquerda = "  Bem vindo, " + usuarioAtivo->nome + " " +  usuarioAtivo->sobrenome + "!";

	limparTela();
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
	string textoEsquerda = "  Bem vindo, " + usuarioAtivo->nome + " " + usuarioAtivo->sobrenome + "!";

	limparTela();
	renderiza_rodape_logado(textoEsquerda, textoDireita);
	listaPosts->mostrarTodosPosts(listaUsuarios);
	irParaTop(0, 0);

	while (true) {
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			menuSelecionado = menu(listaUsuarios, usuarioAtivo);

			if (menuSelecionado == 1) {
				Fazer_postagem(listaUsuarios, listaPosts, usuarioAtivo, textoEsquerda, textoDireita);
			}
			else if (menuSelecionado == 2) {
				textoDireita = "Deslogando...    ";
				textoEsquerda = "  At\x82 outra hora " + usuarioAtivo->nome + " " + usuarioAtivo->sobrenome + "!";

				limparTela();
				renderiza_rodape_logado(textoEsquerda, textoDireita);
				Sleep(1800);

				break;
			}

			limparTela();
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

void menu_deslogado_tecla_enter(int menuSelecionado, ListaUsuarios *listaUsuarios, ListaPosts *listaPosts, Usuario *usuarioAtivo, bool &dadosPreCarregados) {
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
			if (!dadosPreCarregados) {
				inicia_dados_pre_carregados(listaUsuarios, listaPosts);
				dadosPreCarregados = true;
				loading();
			}
			
			usuarioAtivo = listaUsuarios->primeiro->usuario;

			executa_rede_social(listaUsuarios, listaPosts, usuarioAtivo);
			break;
	}
}

void executa_menu_deslogado(int menuSelecionado, string menuTexto[]) {
	renderiza_rodape(0);
	renderiza_menu(menuSelecionado, menuTexto, 4, 2);
}

void inicializa() {
	// Variaveis
	bool dadosPreCarregados = false;
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

			menu_deslogado_tecla_enter(menuSelecionado, listaUsuarios, listaPosts, usuarioAtivo, dadosPreCarregados);

			menuSelecionado = 1;
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