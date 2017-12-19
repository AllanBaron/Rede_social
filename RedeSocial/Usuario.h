#pragma once
#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <string>

using namespace std;

struct Usuario {
	int ID;
	string nome;
	string sobrenome;
	string email;
	string senha;
	int dataNascDia;
	int dataNascMes;
	int dataNascAno;
	string sexo;

	Usuario(int ID, string nome, string sobrenome, string email, string senha, int dataNascDia, int dataNascMes, int dataNascAno, string sexo) {
		this->ID = ID;
		this->nome = nome;
		this->sobrenome = sobrenome;
		this->email = email;
		this->senha = senha;
		this->dataNascDia = dataNascDia;
		this->dataNascMes = dataNascMes;
		this->dataNascAno = dataNascAno;
		this->sexo = sexo;
	}
};

struct ElementoUsuario {
	Usuario *usuario;
	ElementoUsuario *proximoUsuario;

	ElementoUsuario(Usuario *usuario) {
		this->usuario = usuario;
		this->proximoUsuario = NULL;
	}
};

struct ListaUsuarios {
	ElementoUsuario *primeiro;

	ListaUsuarios(ElementoUsuario *primeiro) {
		this->primeiro = primeiro;
	}

	bool buscarUsuarioPorID(int ID, Usuario *&usuario) {
		if (this->primeiro == NULL) {
			return false;
		}

		ElementoUsuario *atual = this->primeiro;

		while (atual != NULL) {
			if (atual->usuario->ID == ID) {
				usuario = atual->usuario;
				return true;
			}
	
			atual = atual->proximoUsuario;
		}

		return false;
	}

	bool buscarUsuarioPorEmail(string email, Usuario *&usuario) {
		if (this->primeiro == NULL) {
			return false;
		}

		ElementoUsuario *atual = this->primeiro;

		while (atual != NULL) {	
			if (atual->usuario->email == email) {
				usuario = atual->usuario;
				return true;
			}

			atual = atual->proximoUsuario;
		}

		return false;
	}

	void mostrarTodosUsuarios() {
		if (this->primeiro != NULL) {
			ElementoUsuario *atual = this->primeiro;

			while (atual != NULL) {
				cout << "ID:" << atual->usuario->ID << " Nome: " << atual->usuario->nome << endl;

				atual = atual->proximoUsuario;
			}
		}
	}

	bool inserir(ElementoUsuario *novoElemento) {
		if (this->primeiro == NULL) {
			this->primeiro = novoElemento;
			return true;
		}

		ElementoUsuario *atual = this->primeiro;
		while (atual != NULL) {
			if (atual->proximoUsuario == NULL) {
				atual->proximoUsuario = novoElemento;
				break;
			}
			atual = atual->proximoUsuario;
		}
		return true;
	}

	bool deletar(int ID) {
		if (this->primeiro != NULL && this->primeiro->usuario->ID == ID) {
			if (this->primeiro->proximoUsuario != NULL) {
				ElementoUsuario *atual = this->primeiro;
				this->primeiro = atual->proximoUsuario;
				delete atual;
				return true;
			}

			delete this->primeiro;
			this->primeiro = NULL;
			return true;
		}
		else if(this->primeiro != NULL && this->primeiro->proximoUsuario != NULL) {
			ElementoUsuario *anterior = this->primeiro;
			ElementoUsuario *atual = anterior->proximoUsuario;

			while (atual != NULL && atual->usuario->ID != ID) {
				if (atual->usuario->ID == ID) {
					anterior->proximoUsuario = atual->proximoUsuario;
					delete atual;
					break;
				}
				anterior = atual;
				atual = anterior->proximoUsuario;
			}
			return true;
		}
		return false;
	}

	int size() {
		int contador = 0;
		ElementoUsuario *atual = this->primeiro;

		while (atual != NULL) {
			contador++;
			atual = atual->proximoUsuario;
		}

		return contador;
	}
};

#endif