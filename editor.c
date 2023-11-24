#include <stdio.h>
#include <stdbool.h> //biblioteca para uso de variáveis booleanas
#include <stdlib.h> //biblioteca pra funções de alocação dinamica
#include <string.h> //biblioteca pra manipulação de strings (precisa pro strcpy)
#include "funcoes.h"

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
  binario = fopen(arquivo_entrada, "rb");
  verificar_file(binario);

  //inicializando primeiro e anterior
  struct pessoas *primeiro = NULL;
  struct pessoas *anterior = NULL;

  
  while (fread(&pessoa, sizeof(struct pessoas), 1, binario) == 1) {
    //criando o espaço na memoria para o novo elemento
    struct pessoas* nova_pessoa = criar_pessoa(pessoa.id, pessoa.nome);

    struct pessoas* atual = primeiro;
    anterior = NULL;
    
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
  
  fclose(binario); 

  //Menu
  int opcao;

  //fica dentro do "do" enquanto a opção não for 0
  do{ 

    //inicializando a variavel opção, exibindo as opções do menu e lendo a resposta do usuário
    opcao = -1;
    printf("\n--Menu de opções--\n");
    printf("1 - Exibir os cadastros\n");
    printf("2 - Cadastrar\n");
    printf("3 - Excluir um cadastro\n");
    printf("4 - Exibir um cadastro\n");
    printf("5 - Gerar o arquivo binário\n");
    printf("0 - Sair do menu\n");
    printf("Digite o número da opção que deseja selecionar: ");
    scanf("%d", &opcao);

    switch(opcao){
      
      //caso o usuário escolha a opção 1 irá exibir os cadastros
      case 1:
        exibir_cadastros(primeiro);
        break;

      //caso o usuário escolha a opção 2 irá poder inserir um novo cadastro
      case 2:
        printf("Insira seu novo ID e Nome: ");
        int novo_cadastro;
        char novo_nome[maximo_nome];
        scanf("%d", &novo_cadastro);
        scanf("%s", novo_nome);
        cadastrar(novo_cadastro, novo_nome, &primeiro);
        break;

      //caso o usuário escolha a opção 3 irá poder excluir um novo cadastro a partir de um id
      case 3:
        printf("Insira o ID do cadastro que deseja excluir: ");
        int cadastro_id;
        scanf("%d", &cadastro_id);
        remover_cadastro(cadastro_id, &primeiro);
        if(primeiro != NULL){
          printf("\nCadastro removido!");
        } else{
          printf("Cadastro não encontrado!\n");
        }
        break;

      //caso o usuário escolha a opção 4 irá poder exibir um cadastro a partir de um id
      case 4:
        printf("Insira o ID do cadastro que deseja exibir: ");
        int cadastro_id_exibir;
        scanf("%d", &cadastro_id_exibir);
      
        cadastro_unico(primeiro, cadastro_id_exibir);
      break;

      //caso o usuário escolha a opção 5 irá gerar o arquivo binário 
      case 5:
  
        escrever_binario(primeiro, arquivo_saida);
        printf("Gravação feita com sucesso!");
        break;

      //caso o usuário escolha a opção 0 irá gerar o arquivo binário e encerrar o programa
      case 0:
        printf("Encerrando sessão e gerando arquivo binário. Obrigada por utilizar nosso programa!");
        
          escrever_binario(primeiro, arquivo_saida);
          liberar_memoria(primeiro);
        break;

      //caso o usuário escolha uma opção inválida o programa avisa
      default:
        printf("A opção selecionada é inválida!\n");
      break;
    }
  } while(opcao != 0);

  return 0;
}