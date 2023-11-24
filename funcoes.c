#include "funcoes.h" // biblioteca com as funções geradoras

struct pessoas pessoa; // variável global para manipular o struct pessoas

void verificar_file(FILE*arq){ // função para verificar se o arquivo foi aberto corretamente
  if (arq == NULL) { // se o arquivo for nulo 
      printf("Erro ao abrir o arquivo de saída\n"); //imprime a mensagem de erro
      exit(1); // encerra o programa
  }
}

void liberar_memoria(struct pessoas*primeiro){ // função para liberar memória heap alocada
  struct pessoas*p = primeiro; // ponteiro para percorrer a lista
  while(p){ // enquanto p não for nulo
    struct pessoas*memoria = p; // ponteiro para guardar o endereço do nó atual
    p = p->prox; // avança para o próximo nó
    free(memoria); // libera a memória alocada para o nó atual
  }
}

void escrever_binario(struct pessoas*primeiro, const char*arquivo_saida){ // função para escrever em binário no arquivo de saída
  FILE *binario = fopen(arquivo_saida, "wb"); // abre o arquivo de saída e escreve em modo binário

  verificar_file(binario); // chama a função para verificar a abertura do aquivo

  struct pessoas *p = primeiro; // ponteiro para percorrer a lista
  while(p != NULL){ // enquanto o p não for nulo
    fwrite(p, sizeof(struct pessoas), 1, binario); // escreve no arquivo o nó atual
    p = p ->prox; // avança para o próximo nó
  }

  fclose(binario); //fecha o arquivo de saída
}

struct pessoas* criar_pessoa(int id, const char* nome){ // função para aloca e retorna uma nova pessoa como ponteiro
  struct pessoas* nova_pessoa = (struct pessoas *)malloc(sizeof(struct pessoas)); // aloca memória para a nova pessoa como ponteiro

  if (nova_pessoa == NULL) { // se a nova pessoa for nula
    printf("Erro ao alocar memória"); // printa a mensagem
    exit(1); //encerra o programa
  }
  nova_pessoa->id = id; // atribui o id da pessoa ao campo id da nova pessoa
  strcpy(nova_pessoa->nome, nome); // atribui o nome da pessoa ao campo nome da nova pessoa
  nova_pessoa->prox = NULL; // atribui o ponteiro prox como nulo

  return nova_pessoa; //retorna a nova pessoa
}

void exibir_cadastros(struct pessoas *cadastro){ // função para exibir a lista de cadastros
  struct pessoas *atual = cadastro; // ponteiro para percorrer a lista
  printf("\n--Cadastros--\n");
  puts("\n");
  while (atual != NULL){ // enquanto atual não for nulo
    printf("Nome: %s, id: %d\n", atual->nome, atual->id); // printa no nome e a id da pessoa
    atual = atual->prox; // avança para o próximo nó
  }
}

void escrever_binario_txt(struct pessoas*primeiro, const char*arquivo_saida){ ///função para escrever o aquivo binário em txt para o arquivo de saída
  FILE *texto_saida = fopen(arquivo_saida, "wb"); // abre o arquivo de saída e escreve em modo binário

  verificar_file(texto_saida); // chama a função para verificar a abertura do arquivo

  struct pessoas *p = primeiro; // ponteiro para percorrer a lista
  while(p != NULL){ // enquanto p não for nulo
    fprintf(texto_saida, "%s %d\n", p->nome, p->id); // printa o nome e o id
    p = p ->prox; // avança para o próximo nó
  }

  fclose(texto_saida); // fecha o arquivo
}

void cadastro_unico(struct pessoas *cadastro, int cadastro_id_exibir){ // função para cadastrar uma pessoa
  struct pessoas *atual = cadastro; // ponteiro para percorrer a lista
  printf("\n--Cadastro--");
  while (atual != NULL){
    if(atual -> id == cadastro_id_exibir){ // se o id da pessoa for igual ao id do cadastro
      printf("Nome: %s, id: %d\n", atual->nome, atual->id); // imprime o nome e o id da pessoa
    }
    atual = atual -> prox; // avança para o próximo nó
  }  
}

void remover_cadastro(int cadastro_id, struct pessoas**cadastro){ // função para remover um cadastro
  struct pessoas *atual =  *cadastro; // ponteiro para percorrer a lista
  struct pessoas *anterior =  NULL; // ponteiro para o nó anterior ao atual

  while(atual != NULL && cadastro_id > atual->id){ // enquanto o atual não for nulo e o id do atual for menor que o id do cadastro
    anterior = atual; // o nó anterior é o atual
    atual = atual->prox; // o atual é o próximo nó
  }

  if(atual != NULL){ // se o atual for diferente de nulo
    if(anterior ==  NULL){ // se o anterior for nulo
      *cadastro = atual->prox; // o ponteiro para o cadastro é o próximo nó
    } else{ // se o anterior não for nulo
      anterior->prox = atual->prox; // o ponteiro para o nó anterior é o próximo nó
    }

  }
}

void cadastrar(int novo_cadastro, char novo_nome[maximo_nome], struct pessoas**cadastro){ // função para cadastrar uma pessoa

  struct pessoas*nova_pessoa = (struct pessoas*) malloc(sizeof(struct pessoas)); // aloca memória para a nova pessoa
  nova_pessoa->id = novo_cadastro; // atribui o id da pessoa ao campo id da nova pessoa 
  strcpy(nova_pessoa->nome, novo_nome); // atribui o nome da pessoa ao campo nome da nova pessoa
  nova_pessoa->prox = NULL; // atribui o ponteiro prox como nulo

  struct pessoas *atual = *cadastro; // ponteiro para percorrer a lista
  struct pessoas *anterior = NULL; // ponteiro para o nó anterior ao atual

  while(atual != NULL && novo_cadastro > atual->id){ // enquanto o atual não for nulo e o id do atual for menor que o id do cadastro
    anterior = atual; // o nó anterior é o atual
    atual = atual->prox; // o atual é o próximo nó
  }

  if(anterior == NULL){ // se o anterior for nulo
    nova_pessoa->prox = *cadastro; // o ponteiro para o cadastro é o próximo nó
    *cadastro = nova_pessoa; // o ponteiro para o cadastro é a nova pessoa
  }else{
    anterior->prox = nova_pessoa; // o ponteiro para o nó anterior é a nova pessoa
    nova_pessoa->prox = atual; // o ponteiro para o nó anterior é o atual
  }
}
