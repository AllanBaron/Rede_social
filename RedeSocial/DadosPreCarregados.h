#pragma once
#ifndef DADOSPRECARREGADOS_H
#define DADOSPRECARREGADOS_H



void inicia_dados_pre_carregados(ListaUsuarios *listaUsuarios, ListaPosts *listaPosts) {
	
	// Usuário 1
	int usuarioID = listaUsuarios->size();
	listaUsuarios->inserir(new ElementoUsuario(new Usuario(usuarioID, "Allan", "Baron", "allan@allan.com", "123", 4, 7, 1998, "Masculino")));
	listaPosts->inserir(new ElementoPost(new Post(listaPosts->size(), usuarioID, "Vestibulum ac diam sit amet quam vehicula elementum sed sit amet dui. Donec rutrum congue leo eget malesuada. Curabitur aliquet quam id dui posuere blandit. Quisque velit nisi, pretium ut lacinia in, elementum id enim. Donec rutrum congue leo eget malesuada.")));

	// Usuário 2
	usuarioID = listaUsuarios->size();
	listaUsuarios->inserir(new ElementoUsuario(new Usuario(usuarioID, "Jose", "Vieiro", "jose@jose.com", "123", 5, 9, 1999, "Masculino")));
	listaPosts->inserir(new ElementoPost(new Post(listaPosts->size(), usuarioID, "Proin eget tortor risus. Praesent sapien massa, convallis a pellentesque nec, egestas non nisi. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Donec velit neque, auctor sit amet aliquam vel, ullamcorper sit amet ligula. Donec rutrum congue leo eget malesuada. Curabitur aliquet quam id dui posuere blandit.")));

	// Usuário 3
	usuarioID = listaUsuarios->size();
	listaUsuarios->inserir(new ElementoUsuario(new Usuario(usuarioID, "Ana", "Favia", "ana@ana.com", "123", 20, 5, 2000, "Feminino")));
	listaPosts->inserir(new ElementoPost(new Post(listaPosts->size(), usuarioID, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Donec velit neque, auctor sit amet aliquam vel, ullamcorper sit amet ligula. Curabitur aliquet quam id dui posuere blandit.")));
}


#endif