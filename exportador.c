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
  FILE *binario;
  binario = fopen(arquivo_entrada, "rb"); //abrindo o arquivo de entrada e lendo em modo binário
  verificar_file(binario); //verificando se o aquivo foi aberto corretamente

  //inicializando primeiro e anterior
  struct pessoas *primeiro = NULL;
  struct pessoas *anterior = NULL;
 
  while (fread(&pessoa, sizeof(struct pessoas), 1, binario) == 1) { //enquanto o arquivo binário não for vazio continuará rodando

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
    } //se o anterior não for vazio, inserindo nova_pessoa entre o anterior e o atual
    else{
      anterior->prox = nova_pessoa;
      nova_pessoa->prox = atual;
    }
  }
  fclose(binario); //fechando o arquivo binário
  escrever_binario_txt(primeiro, arquivo_saida); //função para escrever o aquivo binário em txt para o arquivo de saída
  liberar_memoria(primeiro); //liberando memória heap alocada

  return 0;
}