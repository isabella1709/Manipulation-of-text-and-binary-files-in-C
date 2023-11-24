#ifndef FUNCOESGERADOR_H
#define FUNCOESGERADOR_H

#include <stdio.h>
#include <stdbool.h> //biblioteca para variáveis booleanas
#include <stdlib.h> //biblioteca pra funções de alocação dinamica
#include <string.h> //biblioteca pra manipulação de strings (precisa pro strcpy)
//definindo o máximo de tamanho para nome
#define maximo_nome 50 

struct pessoas { //struct para pessoas
  char nome[maximo_nome];
  int id;
  struct pessoas* prox;
};

extern struct pessoas pessoa; // variável global para manipular o struct pessoas

void verificar_file(FILE*arq); // função para verificar se o arquivo foi aberto corretamente
void liberar_memoria(struct pessoas*primeiro); // função para liberar memória heap alocada
void escrever_binario(struct pessoas*primeiro, const char*arquivo_saida); // função para escrever em binário no arquivo de saída
struct pessoas* criar_pessoa(int id, const char* nome); // função para aloca e retorna uma nova pessoa como ponteiro
void exibir_cadastros(struct pessoas *cadastro); // função para exibir a lista de cadastros
void escrever_binario_txt(struct pessoas*primeiro, const char*arquivo_saida); //função para escrever o aquivo binário em txt para o arquivo de saída
//
void cadastro_unico(struct pessoas *cadastro, int cadastro_id_exibir); // função para cadastrar uma pessoa
void remover_cadastro(int cadastro_id, struct pessoas**cadastro); // função para remover um cadastro
void cadastrar(int novo_cadastro, char novo_nome[maximo_nome], struct pessoas**cadastro); // função para cadastrar uma pessoa
#endif