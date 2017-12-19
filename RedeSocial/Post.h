#pragma once
#ifndef POST_H
#define POST_H

#include <iostream>
#include <string>
#include "Ferramentas.h"
#include "Interface.h";

using namespace std;

struct Post {
	int ID;
	int usuarioID;
	string texto;
	string usuarioIdCitado;

	Post(int ID, int usuarioID, string texto, string usuarioIdCitado = "") {
		this->ID = ID;
		this->usuarioID = usuarioID;
		this->texto = texto;

		this->usuarioIdCitado = usuarioIdCitado;
	}
};

struct ElementoPost {
	Post *post;
	ElementoPost *proximoPost;

	ElementoPost(Post *post) {
		this->post = post;
		this->proximoPost = NULL;
	}
};

struct ListaPosts {
	ElementoPost *primeiro;

	ListaPosts(ElementoPost *primeiro) {
		this->primeiro = primeiro;
	}

	void mostrarTodosPosts(ListaUsuarios *listaUsuarios) {
		if (this->primeiro != NULL) {
			ElementoPost *atual = this->primeiro;
			Usuario *usuarioTemp;

			while (atual != NULL) {
				bool status = listaUsuarios->buscarUsuarioPorID(atual->post->usuarioID, usuarioTemp);
				
				if (status) {
					if (this->size() > 0) {
						alterarCorTexto(COR_AZUL_CLARO);
						cout << "@" << usuarioTemp->usuarioLogin << "\n" << endl;
						
						redefinirCorTexto();
						cout << quabraLinhaTexto(atual->post->texto, larguraDoTerminal() - 10);
					
						alterarCorTexto(COR_BRANCO);
						if (atual->post->usuarioIdCitado.length()) {
							cout << "\n\nUsu\xA0rio citado: @" << atual->post->usuarioIdCitado;
						}
						cout << "\n" << endl;
						redefinirCorTexto();
						preencherLinhaComCaractere('\x5F');
						cout << "\n";
					}
				}
				
				atual = atual->proximoPost;
			}
		}
		else {
			cout << alinharTextoCentro("Nenhuma postagem encontrada!");
		}
	}

	bool inserir(ElementoPost *novoElemento) {
		if (this->primeiro == NULL) {
			this->primeiro = novoElemento;
			return true;
		}

		ElementoPost *atual = this->primeiro;
		this->primeiro = novoElemento;
		this->primeiro->proximoPost = atual;
		return true;
	}

	bool inserirNoFinal(ElementoPost *novoElemento) {
		if (this->primeiro == NULL) {
			this->primeiro = novoElemento;
			return true;
		}
		
		ElementoPost *atual = this->primeiro;
		while (atual != NULL) {
			if (atual->proximoPost == NULL) {
				atual->proximoPost = novoElemento;
				break;
			}
			atual = atual->proximoPost;
		}
		return true;
	}

	bool deletar(int ID) {
		if (this->primeiro != NULL && this->primeiro->post->ID == ID) {
			if (this->primeiro->proximoPost != NULL) {
				ElementoPost *atual = this->primeiro;
				this->primeiro = atual->proximoPost;
				delete atual;
				return true;
			}

			delete this->primeiro;
			this->primeiro = NULL;
			return true;
		}
		else if (this->primeiro != NULL && this->primeiro->proximoPost != NULL) {
			ElementoPost *anterior = this->primeiro;
			ElementoPost *atual = anterior->proximoPost;

			while (atual != NULL && atual->post->ID != ID) {
				if (atual->post->ID == ID) {
					anterior->proximoPost = atual->proximoPost;
					delete atual;
					break;
				}
				anterior = atual;
				atual = anterior->proximoPost;
			}
			return true;
		}
		return false;
	}

	int size() {
		int contador = 0;
		ElementoPost *atual = this->primeiro;

		while (atual != NULL) {
			contador++;
			atual = atual->proximoPost;
		}

		return contador;
	}
};

#endif