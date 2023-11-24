#include <stdio.h> 
#include <stdbool.h> //biblioteca para uso de variáveis booleanas
#include <stdlib.h> //biblioteca pra funções de alocação dinamica
#include <string.h> //biblioteca pra manipulação de strings (precisa pro strcpy)
#include "funcoes.h" //incluindo o cabeçalho com as funções e variáveis globais

// o argc é a quantidade de argumentos sendo passados
// o argv são os argumentos
int main(int argc, char *argv[]) {

  //caso insira uma quantidade de argumento diferente de 3 (programa, arquivo de entrada e de saida) da erro
  if (argc != 3) {
    printf("Precisa inserir o nome do programa, o nome do arquivo de entrada e "
           "o nome do arquivo de saída\n");
    return 1;
  }
  //salvando os nomes inicializados nos parametros como variaveis
  const char *arquivo_entrada = argv[1];
  const char *arquivo_saida = argv[2];

  //abrindo o arquivo de entrada
  FILE *texto;
  texto = fopen(arquivo_entrada, "r"); //abrindo aquivo de entrada e lendo
  verificar_file(texto); //verificando se o arquivo foi aberto corretamente

  //inicializando primeiro e anterior
  struct pessoas *primeiro = NULL;
  struct pessoas *anterior = NULL;
  
  //enquanto essa leitura não chegar ao eof(end of file) vai executar os comandos
  while (fscanf(texto, "%d %s", &pessoa.id, pessoa.nome) != EOF) {
    
    struct pessoas* nova_pessoa = criar_pessoa(pessoa.id, pessoa.nome); // realiza a alocação de cadastros em memória heap

    //inicializando o atual
    struct pessoas* atual = primeiro;
    anterior = NULL; //reinicializando o anterior para não haver problemas de ordenação

    //se o atual não for vazio e o id atual for menor que o de nova pessoa, então vai atribuir seu valor para anterior e o novo valor de atual será o proximo
    while(atual != NULL && nova_pessoa->id > atual->id){
      anterior = atual;
      atual = atual->prox;
    }

    //se o anterior for vazio, então a nova_pessoa terá o valor de primeiro, já que tem o menor id
    if (anterior == NULL){
      nova_pessoa->prox = primeiro;
      primeiro = nova_pessoa;
    }
    //se o anterior não for vazio, inserindo nova_pessoa entre o anterior e o atual
    else{
      anterior->prox = nova_pessoa;
      nova_pessoa->prox = atual;
    } 
  }
  // exibir_cadastros(primeiro);
  fclose(texto); //fechando o arquivo de entrada
  escrever_binario(primeiro, arquivo_saida); //função que escreve em binário a lista encadeada no arquivo de saída
  liberar_memoria(primeiro); //liberando a memória heap alocada
  
  return 0;
}