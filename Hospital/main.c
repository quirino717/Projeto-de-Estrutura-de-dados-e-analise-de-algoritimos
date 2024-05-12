//bibliotecas utilizadas
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//estruturas
typedef struct{
  int dia;
  int mes;
  int ano;
} Data;

typedef struct{
  char nome[200];
  int idade;
  char RG[200];
  Data entrada;
} Registro;

typedef struct Elista{
  Registro dados;
  struct Elista *proximo;
}Elista;

typedef struct Lista{
  int qtde;
  Elista *primeiro;
}Lista;

typedef struct Efila {
    struct Efila *anterior;
    Registro dados;
    struct Efila *proximo;
}Efila;

typedef struct {
    Efila  *head;
    Efila *tail;
    int qtde;
} Fila;

typedef struct EABB{
  Registro dados;
  struct EABB* esq;
  struct EABB* dir;
  struct EABB* pai;
} EABB;

typedef struct ABB{
  EABB* raiz;
  int qtde;
} ABB;

//nessa partes estão as declarações dos menus, pq algumas das funções chamam eles e todos os menus chamam o menu principal
int menu_principal(int escolha, Registro dados, Lista *l, Fila *f, ABB *arvore); //declaração da função menu_principal

int menu_cadastro(int escolha, Registro dados, Lista *l, Fila *f, ABB *arvore); //declaração da função menu_cadastro

int menu_atendimento(int escolha, Registro dados, Lista *l, Fila *f, ABB *arvore);
//declaração da função menu_atendimento

int menu_pesquisa(int escolha, Registro dados, Lista *l, Fila *f, ABB *arvore); //declaração da função menu_pesquisa

int menu_cs(int escolha, Registro dados, Lista *l, Fila *f, ABB *arvore); //declaração da função menu_cs


//******* FUNÇÕES *******

//funções da lista encadeada
Lista *inicializa_lista(){
  Lista *l = malloc(sizeof(Lista)); //aloca a memória para a lista
  l->primeiro = NULL; //como está inicializando a lista, o primeiro elemento da lista é nulo
  l->qtde = 0; //como está inicializando a lista, a lista está vazia então a quantidade é zero
  return l;
}

void inserir(Lista *l, Registro dados){
  Elista *novo = malloc(sizeof(Elista)); //aloca memoria para o novo elemento da lista

  //como a insercao deve ser feita sempre no inicio...
  novo->dados = dados; //a célula recebe os dados do paciente
  novo->proximo = l->primeiro; //o proximo elemento da lista recebe o primeiro elemento da lista
  l->primeiro = novo; //o primeiro elemento da lista recebe o novo elemento

  l->qtde++; //aumenta a quantidade da lista
}

void remover(Lista *l) {
  if(l->primeiro == NULL){ //verifica se a lista está vazia
    printf("\tNao ha nenhum paciente cadastrado ainda!!\n");
    return; //se sim, só retorna
  } else { //se Nao

    //pede o nome do paciente que vai ser removido
    printf("Informe o nome do paciente a ser removido: ");
    char nome[200]; //variável que recebe o nome do paciente que vai ter os dados removidos
    scanf("%199[^\n]", nome); //recebe o nome do paciente. como dados.nome pode receber nome e sobrenome %199[^\n] é usado pra salvar o nome digitado até o final ao invés de só até o primeiro espaço

    Elista *atual = l->primeiro; //cria um ponteiro que aponta para o primeiro elemento da lista, e será usado pra percorrer a lista
    Elista *anterior = NULL; //cria um ponteiro que aponta para o elemento anterior ao atual

    while(atual != NULL && strcmp(atual->dados.nome, nome) != 0){ //enquanto o atual for diferente de nulo e o nome do atual for diferente do nome de quem vai ter os dados removidos, percorre a lista toda
      anterior = atual; //o anterior recebe o atual
      atual = atual->proximo; //o atual recebe o próximo
    }

    if (atual == NULL){ //se atual for igual a nulo retorna, pois chegou no final da lista e Nao encontrou o paciente
      printf("\tNao ha cadastros referentes a essa pessoa!!\n");
      return;
    }

    if (atual == l->primeiro) { //se o paciente que vai ser removido for o primeiro da lista
      l->primeiro = atual->proximo; //o ponteiro que aponta para o começo da lista recebe o próximo elemento
    } else { //se Nao for o primeiro
      anterior->proximo = atual->proximo; //o ponteiro que aponta para o elemento anterior ao atual recebe o próximo
    }

    printf("\n\nO cadastro do paciente %s foi removido!!\n", nome); //avisa que o paciente foi removido

    free(atual); //apaga o atual
    l->qtde--; //diminui a quantidade da lista
  }
}

void imprimir(Lista *l){
  if (l->qtde == 0){ //verifica se a lista está vazia
    printf("\tNao ha nenhum paciente cadastrado ainda!!\n\n"); 
    return; //se sim, exibe a mensagem de aviso e retorna
  } else { //se Nao...

      printf("Exibindo lista de pacientes: \n\n");
      sleep(1);

      Elista *atual = l->primeiro; //ponteiro que aponta para o primeiro elemento da lista

      while(atual != NULL){ //enquanto o atual for diferente de nulo, percorre toda a lista
        printf("\tNome: %s | Idade: %d | RG: %s | Data de entrada: %d/%d/%d\n", atual->dados.nome, atual->dados.idade, atual->dados.RG, atual->dados.entrada.dia, atual->dados.entrada.mes, atual->dados.entrada.ano); //imprime os dados de todos os pacientes da lista
        atual = atual->proximo; //atualiza o valor do atual enquanto percorre a lista
    }
      printf("\n");
  }
}

void consultar(Lista *l){
  //a mesma lógica da função remover pode ser usada aqui, com a mudança sendo exibir os dados ao invés de remover

  if(l->primeiro == NULL){ //verifica se a lista está vazia
    printf("\nNao ha nenhum paciente cadastrado ainda!!\n");
    return; //se sim, só retorna
  } else { //se Nao

    //pede o nome do paciente que vai ter os dados consultados
    printf("Informe o nome do paciente que deseja consultar os dados: ");
    char nome[200]; //variável que recebe o nome do paciente que vai ter os dados consultados
    scanf("%199[^\n]", nome); //recebe o nome do paciente. como dados.nome pode receber nome e sobrenome %199[^\n] é usado pra salvar o nome digitado até o final ao invés de só até o primeiro espaço

    Elista *atual = l->primeiro; //cria um ponteiro que aponta para o primeiro elemento da lista, e será usado pra percorrer a lista
    Elista *anterior = NULL; //cria um ponteiro que aponta para o elemento anterior ao atual

    while(atual != NULL && strcmp(atual->dados.nome, nome) != 0){ //enquanto o atual for diferente de nulo e o nome do atual for diferente do nome de quem vai ter os dados consultados, percorre a lista toda
      anterior = atual; //o anterior recebe o atual
      atual = atual->proximo; //o atual recebe o próximo
    }

    if (atual == NULL){ //se atual for igual a nulo retorna, pois chegou no final da lista e Nao encontrou o paciente
      printf("\n\tNao ha cadastros referentes a essa pessoa!!\n");
      return;
    }

    printf("\n\tNome: %s | Idade: %d | RG: %s | Data: %d/%d/%d\n", atual->dados.nome, atual->dados.idade, atual->dados.RG, atual->dados.entrada.dia, atual->dados.entrada.mes, atual->dados.entrada.ano); //imprime os todos os dados do paciente

  }
}

void atualizar(Lista *l){
  //a mesma lógica usada nas funções remover e consultar pode ser usada aqui, já que precisa percorrer toda a lista até achar a pessoa que vai ter os dados atualizados

  if(l->qtde == 0){ //verifica se a lista está vazia
    printf("\tNao ha nenhum paciente cadastrado ainda!!\n");
    return; //se sim, só retorna
  } else {//se Nao

    //pede o nome do paciente que vai ter os dados atualizados
    printf("Informe o nome do paciente que deseja atualizar os dados: ");
    char nome[200]; //variável que recebe o nome do paciente que vai ter os dados atualizados
    scanf("%199[^\n]", nome); //recebe o nome do paciente. como dados.nome pode receber nome e sobrenome %199[^\n] é usado pra salvar o nome digitado até o final ao invés de só até o primeiro espaço

    Elista *atual = l->primeiro; //cria um ponteiro que aponta para o primeiro elemento da lista, e será usado pra percorrer a lista
    Elista *anterior = NULL; //cria um ponteiro que aponta para o elemento anterior ao atual

    while(atual != NULL && strcmp(atual->dados.nome, nome) != 0){ //enquanto o atual for diferente de nulo e o nome do atual for diferente do nome de quem vai ter os dados atualizados, percorre a lista toda
      anterior = atual; //o anterior recebe o atual
      atual = atual->proximo; //o atual recebe o próximo
    }

    if (atual == NULL){ //se atual for igual a nulo retorna, pois chegou no final da lista e Nao encontrou o paciente
      printf("\n\tNao ha cadastros referentes a essa pessoa!!\n");
      return;
    }

    int atualizar; //variável que recebe a opcao escolhida pelo usuário
    printf("\n\tPaciente encontrado!!\n");
    printf("\nQual dado gostaria de atualizar:\n\n"); //pergunta qual dado o usuário quer atualizar
    printf("\t1 - Nome\n");
    printf("\t2 - Idade\n");
    printf("\t3 - RG\n");
    printf("\t4 - Data de entrada\n\n");
    printf("Digite o numero do que quer atualizar: "); //então pede a escolha do usuário
    scanf("%d", &atualizar); //e recebe a escolha do usuário
    getchar(); //armazena o enter para que Nao haja erro se for atualizar o nome

    if (atualizar == 1){
      printf("\t\nInforme o novo nome: ");
      scanf("%199[^\n]", atual->dados.nome); //atualiza o nome do paciente, ou seja, atual recebe o novo nome
    }
    if (atualizar == 2){
      printf("\t\nInforme a nova idade: ");
      scanf("%d", &atual->dados.idade); //atualiza a idade do paciente, ou seja, atual recebe a nova idade
    }
    if (atualizar == 3){
      printf("\t\nInforme o novo RG: ");
      scanf("%s", atual->dados.RG); //atualiza o RG do paciente, ou seja, atual recebe o novo RG
    }
    if (atualizar == 4){
      printf("\nInforme o novo dia do cadastro: ");
      scanf("%d", &atual->dados.entrada.dia);
      printf("Informe o novo mes do cadastro: ");
      scanf("%d", &atual->dados.entrada.mes);
      printf("Iforme o novo ano do cadastro: ");
      scanf("%d", &atual->dados.entrada.ano); //atualiza a data de entrada do paciente, ou seja, atual recebe as novas datas
    }

    printf("\n\nOs dados do paciente %s foram atualizados com sucesso!!\n", nome); //avisa que a atualização foi feita

  }  
}

void cadastrar(Lista *l){
  Registro dados;

  system("cls");

  //pergunta as informações do paciente para salvar na lista
  printf("Informe os dados do paciente:\n\n");
  printf("\tNome: ");
  scanf("%200[^\n]", dados.nome); //recebe o nome do paciente, dados.nome pode receber tanto só o primeiro nome quanto o sobrenome, por isso o %200[^\n] é utilizado, ele salva o nome digitado até o final ao invés de só até o primeiro espaço
  printf("\tIdade: ");
  scanf("%d", &dados.idade); //recebe a idade do paciente
  printf("\tRG: ");
  scanf("%s", dados.RG); //recebe o RG do paciente
  printf("\tDia do cadastro: ");
  scanf("%d", &dados.entrada.dia); //recebe o dia de entrada do paciente
  printf("\tmes do cadastro: ");
  scanf("%d", &dados.entrada.mes); //recebe o mes de entrada do paciente
  printf("\tAno do cadastro: ");
  scanf("%d", &dados.entrada.ano); //recebe o ano de entrada do paciente

  printf("\n\nPaciente %s foi cadastrado!!\n", dados.nome); //avisa que o paciente foi cadastrado


  inserir(l, dados); //finalmente insere o paciente na lista de cadastros
}


//comentar funções da fila
Fila *cria_Fila(){
  Fila *f = malloc(sizeof(Fila)); //aloca memória para a fila
    f->head = NULL; //como está inicializando a fila, o começo da fila aponta pro nulo
    f->tail = NULL; //como está inicializando a fila, o final da fila aponta pro fica nulo
    f->qtde = 0; //como está inicializando a fila, a fila está vazia então a quantidade é zero
    return f; //retorna a fila
}

Efila *criar_Efila(Registro dados){
    Efila *e = malloc(sizeof(Efila)); //aloca memória para a cécula da fila
    e->anterior = NULL; //como a célula está sendo criada agora, o seu anterior é nulo
    e->dados = dados; //a célula vai receber os dados do paciente
    e->proximo = NULL; ////como a célula está sendo criada agora, o seu próximo também é nulo
    return e; //retorna a célula
}

void enqueue(Fila *f, Registro dados){
    Efila *nova = criar_Efila(dados); //cria uma célula nova para a fila

    if(f->qtde == 0){ //se a quantidade da fila for igual a zero, a fila está vazia e a célula entra no começo
        f->head = nova; //o começo da fila passa a apontar pra nova célula
        f->tail = nova; //o final da fila também passa a apontar pra nova célula     
    } else { //se a quantidade Nao for zero, já tem paciente na fila e a nova célula entra no final, então...
        nova->anterior = f->tail; //o anterior da nova célula passa a apontar pro final da fila
        f->tail->proximo = nova; //o próximo do final da fila passa a apontar pra nova célula
        f->tail = nova; //e o final da fila recebe a cécula nova
    }

    f->qtde++; //então aumenta a quantidade da fila
}

void dequeue(Fila *f){
  if(f->qtde ==0){ //checa se a fila está vazia
    printf("\nNao ha mais pacientes na fila de espera!!\n");
    return; //se estiver então os pacientes já foram atendidos ou ainda Nao foi inserido paciente na fila, então exibe a mensagem de aviso e retorna
  }

  //se Nao estiver vazia, então...
  Registro dados = f->head->dados; //cria uma variável que recebe os dados do paciente que vai ser atendido, ou seja, o paciente que está no começo da fila
  Efila *end = f->head; //cria uma variável auxiliar que aponta para o primeiro paciente da fila

  if(f->qtde == 1){ //se a quantidade da fila for igual a um, só tem um paciente na fila, então...
      f->head = NULL; //o começo da fila aponta pra nulo
      f->tail = NULL; //o final da fila aponta pra nulo também
  } else { //se Nao, tem mais de um paciente na fila, então...
    f->head->proximo->anterior = NULL; //o anterior do próximo do começo da fila aponta pra nulo
    f->head = f->head->proximo; //o começo da fila aponta pra o próximo da fila
  }

  free(end); //então apaga a cécula referente ao paciente
  f->qtde--; //e diminui a quantidade da fila

}

void imprimir_fila(Fila *f){
  if (f->qtde == 0){ //se a quantidade da fila for zero...
    printf("\tNao ha pacientes na fila de espera!!\n\n");
    return; //signiica que Nao ha pacientes na fila, então exibe a mensagem de aviso e retorna
  } else { //se Nao for zero, tem pacientes na fila, então...
      printf("Exibindo fila de espera: \n\n");
      sleep(1);
      Efila *atual = f->head; //cria um ponteiro auxiliar que aponta pro começo da fila
      int ordem = 0; //cria uma variavel para mostrar a ordem de posição dos pacientes na fila

      while(atual != NULL){ //enquanto atual for diferente de nulo, percorre toda a fila
        ordem++; //aumenta o valor da ordem em 1
        printf("\t%d° paciente a ser atendido: %s\n", ordem, atual->dados.nome); //mostra a posição do paciente na fila e o seu nome
        atual = atual->proximo; //atualiza o valor do atual
    }

    printf("\n");
  }
}

void verifica(Fila *f, Lista *l, Registro dados){
  printf("Informe o nome do paciente que deseja por na fila de espera: ");
  char nome[200]; //variável que recebe o nome do paciente para checar se existe no sistema
  scanf("%199[^\n]", nome); //recebe o nome do paciente. como dados.nome pode receber nome e sobrenome %199[^\n] é usado pra salvar o nome digitado até o final ao invés de só até o primeiro espaço

  Elista *atual = l->primeiro; //cria um ponteiro que aponta para o primeiro elemento da lista, e será usado pra percorrer a lista
  Elista *anterior = NULL; //cria um ponteiro que aponta para o elemento anterior ao atual

  while(atual != NULL && strcmp(atual->dados.nome, nome) != 0){ //enquanto o atual for diferente de nulo e o nome do atual for diferente do nome de quem vai entrar na fila de espera, percorre a lista toda
    anterior = atual; //o anterior recebe o atual
    atual = atual->proximo; //o atual recebe o próximo
  }

  if(atual != NULL){ //se atual for diferente de nulo, significa que o paciente possui cadastro
    enqueue(f, atual->dados); //então adiona o paciente na fila de espera
    printf("\n\nPaciente %s será o %d° a ser atendido!!\n", nome, f->qtde);
  } else { //se Nao, significa que o paciente Nao possui cadastro e Nao pode entrar na fila de espera
    printf("\nEsse paciente Nao possui cadastro em nosso sistema\n");
  }
}

void imprimir_nomes(Lista *l){
  Elista *atual = l->primeiro; //ponteiro que aponta para o primeiro elemento da lista

  while(atual != NULL){ //enquanto o atual for diferente de nulo, percorre toda a lista
    printf("\tPaciente: %s, deu entrada em: %d/%d/%d\n", atual->dados.nome, atual->dados.entrada.dia, atual->dados.entrada.mes, atual->dados.entrada.ano); //imprime o nome de todos os pacientes da lista e quando deram entrada no nosso hospital
    atual = atual->proximo; //atualiza o valor do atual enquanto percorre a lista
  }

  if (l->qtde == 0){ //verifica se a lista de cadastros está vazia
    printf("\tNao ha cadastros de pacientes!!\n"); //se está, imprime a mensagem de aviso
  }
  printf("\n");
}


//funções da ABB
EABB *cria_vertice(ABB *arvore, Registro dados){
  EABB* novo = malloc(sizeof(EABB)); //aloca memória para o vértice novo
  //como o vértice novo está sendo criado agora, as folhas da direita, da esquerda e o pai são nulas
  novo->dir = NULL; 
  novo->esq = NULL;
  novo->pai = NULL;
  novo->dados = dados; //o vértice recebe os dados do paciente
  return novo; //retorna o vértice novo
}

ABB *cria_arvore(){
  ABB* arvore = malloc(sizeof(ABB)); //aloca memória para a árvore
  arvore->raiz = NULL; //como a árvore está sendo criada agora, a raiz dela é nula
  arvore->qtde = 0; //e Nao tem nada na árvora, então a quantidade é zero
  return arvore; //retorna a árvore
}

void inserir_ABB(ABB* arvore, Registro dados, int escolha){

  if (escolha == 1){ //se a escolha no menu de pesquisa for 1, insere na árvore binária de busca tendo os valores dos anos de entrada como referência
    EABB * novo = cria_vertice(arvore, dados); //cria um novo nó com os dados do paciente

    if(arvore->raiz == NULL){ //se a raiz da árvore for nula...
      arvore->raiz = novo; //a raiz da árvore recebe o novo nó
      arvore->qtde++; //aumenta a quantidade da árvore
    } else { //se a raiz Nao for nula...
      EABB *atual = arvore->raiz; //cria um ponteiro auxiliar que aponta para a raiz da árvore
      EABB *pai = NULL; //cria um ponteiro que aponta para o pai do atual

      while(atual != NULL){ //roda pela árvore enquanto o atual Nao for nulo procurando um local para inserir o novo nó
        pai = atual; //atualiza o valor do pai

        if(novo->dados.entrada.ano < atual->dados.entrada.ano){ //se o ano de entrada do novo paciente for menor que o ano de entrada do paciente atual na lista, vai para a esquerda
          atual = atual->esq;
        } else { //se for maior, vai para a direita
          atual = atual->dir;
        }
      }

      novo->pai = pai; //o pai do novo nó recebe o pai do atual

      if(novo->dados.entrada.ano < pai->dados.entrada.ano){ //se o ano de entrada do novo paciente for menor que o ano de entrada do pai, vai para a esquerda
        pai->esq = novo;
      } else { //se for maior, vai para a direita
        pai->dir = novo;
      }
      arvore->qtde++;
    }     
  }
  if (escolha == 2){ //se a escolha no menu de pesquisa for 2, insere na árvore binária de busca tendo os valores dos meses de entrada como referência    
    EABB * novo = cria_vertice(arvore, dados); //cria um novo nó com os dados do paciente

    if(arvore->raiz == NULL){ //se a raiz da árvore for nula...
      arvore->raiz = novo; //a raiz da árvore recebe o novo nó
      arvore->qtde++; //aumenta a quantidade da árvore
    } else { //se a raiz Nao for nula...
      EABB *atual = arvore->raiz; //cria um ponteiro auxiliar que aponta para a raiz da árvore
      EABB *pai = NULL; //cria um ponteiro que aponta para o pai do atual

      while(atual != NULL){ //roda pela árvore enquanto o atual Nao for nulo procurando um local para inser
        pai = atual; //atualiza o valor do pai

        if(novo->dados.entrada.mes < atual->dados.entrada.mes){ //se o mes de entrada do novo paciente for menor que o mes de entrada do paciente atual na lista, vai para a esquerda
          atual = atual->esq;
        } else { //se for maior, vai para a direita
          atual = atual->dir;
        }
      }

      novo->pai = pai; //o pai do novo nó recebe o pai do atual

      if(novo->dados.entrada.mes < pai->dados.entrada.mes){ //se o mes de entrada do novo paciente for menor que o mes de entrada do pai, vai para a esquerda
        pai->esq = novo;
      } else { //se for maior, vai para a direita
        pai->dir = novo;
      }
      arvore->qtde++;
    }
  }
  if (escolha == 3){ //se a escolha no menu de pesquisa for 3, insere na árvore binária de busca tendo os valores dos dias de entrada como referência    
    EABB * novo = cria_vertice(arvore, dados); //cria um novo nó com os dados do paciente

    if(arvore->raiz == NULL){ //se a raiz da árvore for nula...
      arvore->raiz = novo; //a raiz da árvore recebe o novo nó
      arvore->qtde++; //aumenta a quantidade da árvore
    } else { //se a raiz Nao for nula...
      EABB *atual = arvore->raiz; //cria um ponteiro auxiliar que aponta para a raiz da árvore
      EABB *pai = NULL; //cria um ponteiro que aponta para o pai do atual

      while(atual != NULL){ //roda pela árvore enquanto o atual Nao for nulo procurando um local para inser
        pai = atual; //atualiza o valor do pai

        if(novo->dados.entrada.dia < atual->dados.entrada.dia){ //se o dia de entrada do novo paciente for menor que o dia de entrada do paciente atual na lista, vai para a esquerda
          atual = atual->esq;
        } else { //se for maior, vai para a direita
          atual = atual->dir;
        }
      }

      novo->pai = pai; //o pai do novo nó recebe o pai do atual

      if(novo->dados.entrada.dia < pai->dados.entrada.dia){ //se o dia de entrada do novo paciente for menor que o dia de entrada do pai, vai para a esquerda
        pai->esq = novo;
      } else { //se for maior, vai para a direita
        pai->dir = novo;
      }
      arvore->qtde++;
    }
  }
  if (escolha == 4){ //se a escolha no menu de pesquisa for 4, insere na árvore binária de busca tendo os valores das idades como referência    
    EABB * novo = cria_vertice(arvore, dados); //cria um novo nó com os dados do paciente

    if(arvore->raiz == NULL){ //se a raiz da árvore for nula...
      arvore->raiz = novo; //a raiz da árvore recebe o novo nó
      arvore->qtde++; //aumenta a quantidade da árvore
    } else { //se a raiz Nao for nula...
      EABB *atual = arvore->raiz; //cria um ponteiro auxiliar que aponta para a raiz da árvore
      EABB *pai = NULL; //cria um ponteiro que aponta para o pai do atual

      while(atual != NULL){ //roda pela árvore enquanto o atual Nao for nulo procurando um local para inser
        pai = atual; //atualiza o valor do pai

        if(novo->dados.idade < atual->dados.idade){ //se a idade do novo paciente for menor que a idade do paciente atual na lista, vai para a esquerda
          atual = atual->esq;
        } else { //se for maior, vai para a direita
          atual = atual->dir;
        }
      }

      novo->pai = pai; //o pai do novo nó recebe o pai do atual

      if(novo->dados.idade < pai->dados.idade){ //se a idade do novo paciente for menor que a idade do pai, vai para a esquerda
        pai->esq = novo;
      } else { //se for maior, vai para a direita
        pai->dir = novo;
      }
      arvore->qtde++;
    }
  }
}

int remover_vertice(ABB* arvore, EABB* vertice){
  if (arvore->raiz == NULL){ //se a raiz da arvore é nula, significa que ela está vazia
    return 0;
  }

  int filhos; //cria uma variável pra fazer a verificação de filhos
  //checa quantidade de folhas
  if (vertice->esq == NULL && vertice->dir == NULL){
    filhos = 0; //é folha ou raiz sozinha
  }
  if (vertice->esq != NULL || vertice->dir != NULL){
    filhos = 1; //é galho com uma folha
  }
  if (vertice->esq != NULL && vertice->dir != NULL){
    filhos = 2; //é galho com duas folhas
  }

  if (filhos == 0){ //se é folha ou raiz sozinha
    if (vertice->pai == NULL){ //vê se é a raiz ou uma folha comparando com o pai
      arvore->raiz = NULL; //se é pai, então a raiz é nula
    } else { //se Nao for pai
      if (vertice->pai->esq == vertice){ //checa se é folha esquerda ou direito
        vertice->pai->esq = NULL; //remove a folha esquerda
      } else {
        vertice->pai->dir = NULL; //remove a folha direita
      }
    }
    free(vertice); //remove folha
    arvore->qtde--;
    return 1;

  } else {
    if (filhos == 1){ //remove galhos com uma folha
      EABB *aux; //variavel auxiliar
      if(vertice->esq != NULL){ //checa se só tem folha na esquerda
        aux = vertice->esq; //guarda oq vai ser trocado
        vertice->dados.idade = vertice->esq->dados.idade; //troca a folha da esquerda com oq vai ser removido
        vertice->dados = aux->dados; //vertice recebe o valor da troca
        remover_vertice(arvore, vertice->esq); //chama a função com referência da folha
        arvore->qtde--;
      } else { //mesma coisa, mas pra direita
        aux = vertice->dir; 
        vertice->dados.idade = vertice->dir->dados.idade;
        vertice->dados = aux->dados;
        remover_vertice(arvore, vertice->dir);
        arvore->qtde--;
      }
    } else {
      EABB *aux; //variavel auxiliar
      Registro atual; //variavel pra troca
      aux = vertice->esq; //vai pro galho da esquerda
      while(aux->dir != NULL){ //depois procura a folha mais a direita
        aux = aux->dir; //vai atualizando a posição
      }
      atual = aux->dados; //guarda o valor da folha mais a direita
      aux->dados = vertice->dados; //folha mais a direita recebe o valor que vai ser removido
      vertice->dados = atual; //valor que vai ser removido recebe o valor da folha mais a direita
      remover_vertice(arvore, aux); //chama a função com referência da folha mais a direita
      arvore->qtde--;
    }
  }
  return 0;  
}

void apaga_ABB(ABB* arvore){
  while(arvore->raiz != NULL){ //enquanto a raiz Nao for nula, chama a função de remover para limpar a árvore
    remover_vertice(arvore, arvore->raiz);
  }
}

void in_ordem(EABB * raiz) {
  //imprime os valores da árvore em ordem do menor para o maior
  if (raiz){ //se a raiz Nao for nula
    in_ordem(raiz->esq); //chama a função com referência a esquerda
    printf("\tNome: %s | Idade: %d | RG: %s | Data de entrada: %d/%d/%d\n", raiz->dados.nome, raiz->dados.idade, raiz->dados.RG, raiz->dados.entrada.dia, raiz->dados.entrada.mes, raiz->dados.entrada.ano); //imprime os dados
    in_ordem(raiz->dir); //chama a função com referência a direita
  }
}

void pesquisa(Lista *l, ABB* arvore, Fila *f, Registro dados, int escolha){
  int sair; //variavel criada para sair do menu de cadastro, já que um sleep Nao ia ser a melhor opcao para esse caso

  if (l ->qtde == 0){ //se a lista de cadastros estiver vazia, Nao ha oq pesquisar, então retorna para o menu de pesquisa
    system("cls");
    printf("\tNao ha pacientes cadasatrados ainda!!\n");
    sleep(2);
    menu_pesquisa(escolha, dados, l, f, arvore);
  }

  sleep(1); //aguarda 1 segundo para mostrar os cadastros

  Elista *atual = l->primeiro; //ponteiro que aponta para o primeiro elemento da lista
  while(atual != NULL){ 
    inserir_ABB(arvore, atual->dados, escolha);
    atual = atual->proximo; //atualiza o valor do atual enquanto percorre a lista
  }

  in_ordem(arvore->raiz); //chama a função de impressão da árvore

  while(sair != 1){ //enqunto a variavel sair for diferente de 1, ele continua na tela e mostra a mensagem de sair de novo
    printf("\nDigite 1 para sair: ");
    scanf("%d", &sair);
  }

  if (sair == 1){ //se for igual a 1, volta pro menu de cadastro
    apaga_ABB(arvore); //chama a função de apagar a árvore antes de voltar para o menu, para limpar a árvore para a próxima pesquisa, assim os dados Nao são inseridos mais de uma vez
    menu_pesquisa(escolha, dados, l, f, arvore);
  }  
}


//funções relecionadas ao arquivo
int carregar(int escolha, Registro dados, Lista *l){
  if (l->qtde > 0){ //verifica se a lista já cadastros já Nao está carregada
    //caso esteja, exibe a mensagem de aviso e retorna pro menu de carrgar/salvar
    printf("\tA lista de cadastros já está carregada!!\n");
    sleep(3);
    return 0;
  } else if (l->qtde == 0){ //se a lista Nao estiver carregada...

    FILE *registros; //cria um ponteiro para o arquivo de texto
    registros = fopen("pacientes.txt", "r"); //procura o arquivo de texto no modo de leitura "r"

    while (!feof(registros)){ //lê o arquivo, linha por linha, até chegar no final
      fscanf(registros, "Nome: %199[^|] | Idade: %d | RG: %199[^|] | Data de entrada: %d/%d/%d\n", dados.nome, &dados.idade, dados.RG, &dados.entrada.dia, &dados.entrada.mes, &dados.entrada.ano); //lê as informações do arquivo de texto...
      //como o dados.nome pode receber nome e sobrenome, o %199[^|] é usado para ler até a primeira "|", que é onde o nome termina 
      inserir(l, dados); //e então salva elas na lista de cadastros, já que a lista vem vazia ao iniciar o programa
    }

    fclose(registros); //fecha o arquivo
  }
  return escolha; //retorna a escolha
}

int salvar(int escolha, Registro dados, Lista *l){
  FILE *registros; //cria um ponteiro para o arquivo de texto
  registros = fopen("pacientes.txt", "w"); //abre o arquivo e apaga oq tem nele
  fclose(registros); //fecha o arquivo

  registros = fopen("pacientes.txt", "r+"); //abre novamente, mas no modo de escrita

  Elista *atual = l->primeiro; //ponteiro que aponta para o primeiro elemento da lista

  while(atual != NULL){ 
    fprintf(registros, "Nome: %s| Idade: %d| RG: %s| Data de entrada: %d/%d/%d\n", atual->dados.nome, atual->dados.idade, atual->dados.RG, atual->dados.entrada.dia, atual->dados.entrada.mes, atual->dados.entrada.ano); //antes de salvar na lista, salva as informações no arquivo de texto
    atual = atual->proximo; //atualiza o valor do atual enquanto percorre a lista
  }

  fclose(registros); //fecha o arquivo

  return escolha;

}


//menus
#define SIZE_MENU 160
#define SIZE_TASK (SIZE_MENU/2 - 2)

#define RB "\e(0\x6a\e(B" // 188 Right Bottom corner
#define RT "\e(0\x6b\e(B" // 187 Right Top corner
#define LT "\e(0\x6c\e(B" // 201 Left Top cornet
#define LB "\e(0\x6d\e(B" // 200 Left Bottom corner
#define MC "\e(0\x6e\e(B" // 206 Midle Cross
#define HL "\e(0\x71\e(B" // 205 Horizontal Line
#define LC "\e(0\x74\e(B" // 204 Left Cross
#define RC "\e(0\x75\e(B" // 185 Right Cross
#define BC "\e(0\x76\e(B" // 202 Bottom Cross
#define TC "\e(0\x77\e(B" // 203 Top Cross
#define VL "\e(0\x78\e(B" // 186 Vertical Line
#define SP " "             // space string

void draw_menu_header(char* title) {
    int title_length = strlen(title);
    int space_length = SIZE_MENU - title_length - 4; // 2 spaces on each side
    int left_spaces = space_length / 2;
    int right_spaces = space_length - left_spaces;

    printf(LT);
    for (int i = 0; i < left_spaces; i++) {
        printf(HL);
    }
    printf("  %s  ", title);
    for (int i = 0; i < right_spaces; i++) {
        printf(HL);
    }
    printf(RT);
    printf("\n");
}

void draw_horizontal_line(int length) {
    printf(LC);
    for (int i = 0; i < length; i++) {
        printf(HL);
    }
    printf(RC);
    printf("\n");
}

void draw_top_line(int length) {
    printf(LT);
    for (int i = 0; i < length; i++) {
        printf(HL);
    }
    printf(RT);
    printf("\n");
}

void draw_botton_line(int length) {
    printf(LB);
    for (int i = 0; i < length; i++) {
        printf(HL);
    }
    printf(RB);
    printf("\n");
}

void draw_line_cross(int length) {
    printf(LC);
    for (int i = 0; i < length; i++) {
        printf(HL);
    }
    printf(RC);
    printf("\n");
}

void center_text(int length, char* text, int end_line) {
    int text_length = strlen(text);
    int space_length = length - text_length - 2; // 1 space on each side
    int left_spaces = space_length / 2;
    int right_spaces = space_length - left_spaces;

    printf(VL);
    for (int i = 0; i < left_spaces; i++) {
        printf(SP);
    }
    printf(" %s ", text);
    for (int i = 0; i < right_spaces; i++) {
        printf(SP);
    }
    printf(VL);
    if (end_line)
        printf("\n");
}

void draw_vertical_line(int length) {
    printf(VL);
    for (int i = 0; i < length; i++) {
        printf(SP);
    }
    printf(VL);
    printf("\n");
}

void draw_blank_line(int length) {
    printf(VL);
    for (int i = 0; i < length; i++) {
        printf(SP);
    }
    printf(VL);
    printf("\n");
}

void draw_initial_menu_options() {
    draw_blank_line(SIZE_MENU);
    center_text(SIZE_MENU, "1 - Acessar o menu de cadastro", 1);
    draw_line_cross(SIZE_MENU);
    center_text(SIZE_MENU, "2 - Acessar o menu de atendimento", 1);
    draw_line_cross(SIZE_MENU);
    center_text(SIZE_MENU, "3 - Realizar uma pesquisa", 1);
    draw_line_cross(SIZE_MENU);
    center_text(SIZE_MENU, "4 - Carregar ou salvar o arquivo", 1);
    draw_line_cross(SIZE_MENU);
    center_text(SIZE_MENU, "5 - Acessar as nossas informações sobre", 1);
    draw_line_cross(SIZE_MENU);
    center_text(SIZE_MENU, "6 - Encerrar o programa", 1);
    draw_blank_line(SIZE_MENU);
}

int menu_principal(int escolha, Registro dados, Lista *l, Fila *f, ABB *arvore) {
    system("cls");

    FILE *registros;
    registros = fopen("pacientes.txt", "r");
    if (registros == NULL) {
        registros = fopen("pacientes.txt", "w+");
    }
    fclose(registros);

    draw_menu_header("Menu Principal");

    draw_initial_menu_options();
    printf("O que deseja fazer?\n\n");
    printf("Digite o numero de sua escolha: ");
    scanf("%d", &escolha);

    do {  
        switch(escolha) {
            case 1:
                system("cls");
                printf("Acessando menu de cadastro...\n");
                sleep(3);
                menu_cadastro(escolha, dados, l, f, arvore);
                break;
            case 2:
                system("cls");
                printf("Acessando menu de atendimento...\n");
                sleep(3);
                menu_atendimento(escolha, dados, l, f, arvore);
                break;
            case 3:
                system("cls");
                printf("Acessando menu de pesquisa...\n");
                sleep(3);
                menu_pesquisa(escolha, dados, l, f, arvore);
                break;
            case 4:
                system("cls");
                printf("Acessando menu de carregamento ou salvamento...\n");
                sleep(3);
                menu_cs(escolha, dados, l, f, arvore);
                break;
            case 5:
                system("cls");
                printf("Exibindo nossas informações...\n");
                sleep(3);
                system("cls");
                printf("Leonardo Quirino | 11.121.422-7 | Engenharia de Robôs\nMatheus Kenji | 11.121.088-6 | Engenharia de Robôs\n\n");
                sleep(5);
                menu_principal(escolha, dados, l, f, arvore);
                break;
            case 6:
                system("cls");
                printf("\tEncerrando em...\n");
                sleep(1);
                printf("\t3...\n");
                sleep(1);
                printf("\t2...\n");
                sleep(1);
                printf("\t1...\n");
                sleep(1);
                exit(0);
            default:
                printf("opcao inválida!!\n");
                sleep(3);
                menu_principal(escolha, dados, l, f, arvore);
                break;
        } 
    } while (escolha != 6);

    return escolha;
}
int menu_cadastro(int escolha, Registro dados, Lista *l, Fila *f, ABB *arvore) {
    system("cls");

    printf("Área de cadastro\n\n");
    printf("O que deseja fazer?\n\n");

    draw_menu_header("Menu de Cadastro");

    center_text(SIZE_MENU, "1 - Cadastrar um paciente", 1);
    draw_line_cross(SIZE_MENU);
    center_text(SIZE_MENU, "2 - Consultar um cadastro", 1);
    draw_line_cross(SIZE_MENU);
    center_text(SIZE_MENU, "3 - Ver lista de cadastros", 1);
    draw_line_cross(SIZE_MENU);
    center_text(SIZE_MENU, "4 - Atualizar dados", 1);
    draw_line_cross(SIZE_MENU);
    center_text(SIZE_MENU, "5 - Remover um cadastro", 1);
    draw_line_cross(SIZE_MENU);
    center_text(SIZE_MENU, "6 - Retornar ao menu principal", 1);
    draw_blank_line(SIZE_MENU);

    printf("Escolha uma opcao: ");
    scanf("%d", &escolha);
    getchar();

    do {
        switch(escolha) {
            case 1:
                system("cls");
                if (l->qtde == 0) {
                    printf("Carrengando lista de cadastros...\n");
                    carregar(escolha, dados, l);
                    sleep(2);
                }
                system("cls");
                cadastrar(l);
                sleep(3);
                menu_cadastro(escolha, dados, l, f, arvore);
                break;

            case 2:
                system("cls");
                consultar(l);
                int sair;
                while(sair != 1) {
                    printf("\nDigite 1 para sair: ");
                    scanf("%d", &sair);
                }
                if (sair == 1) {
                    menu_cadastro(escolha, dados, l, f, arvore);
                }
                break;

            case 3:
                system("cls");
                imprimir(l);
                while(sair != 1) {
                    printf("Digite 1 para sair: ");
                    scanf("%d", &sair);
                }
                if (sair == 1) {
                    menu_cadastro(escolha, dados, l, f, arvore);
                }
                break;

            case 4:
                system("cls");
                atualizar(l);
                sleep(3);
                menu_cadastro(escolha, dados, l, f, arvore);
                break;

            case 5:
                system("cls");
                remover(l);
                sleep(3);
                menu_cadastro(escolha, dados, l, f, arvore);
                break;

            case 6:
                system("cls");
                printf("Retornando para o menu principal...\n");
                sleep(3);
                menu_principal(escolha, dados, l, f, arvore);
                break;

            default:
                printf("opcao inválida\n");
                sleep(3);
                menu_cadastro(escolha, dados, l, f, arvore);
                break;
        }
    } while (escolha != 6);

    return escolha;
}
int menu_atendimento(int escolha, Registro dados, Lista *l, Fila *f, ABB *arvore) {
    system("cls");

    int sala;

    printf("Área de atendimento\n\n");
    printf("O que deseja fazer?\n\n");

    draw_menu_header("Menu de Atendimento");

    center_text(SIZE_MENU, "1 - Adicionar um paciente à fila de espera", 1);
    draw_line_cross(SIZE_MENU);
    center_text(SIZE_MENU, "2 - Chamar paciente", 1);
    draw_line_cross(SIZE_MENU);
    center_text(SIZE_MENU, "3 - Ver fila de espera", 1);
    draw_line_cross(SIZE_MENU);
    center_text(SIZE_MENU, "4 - Retornar ao menu principal", 1);
    draw_blank_line(SIZE_MENU);

    printf("Escolha uma opcao: ");
    scanf("%d", &escolha);
    getchar();

    do {
        switch(escolha) {
            case 1:
                system("cls");
                if (l ->qtde == 0) {
                    printf("\tNao ha nenhum paciente cadastrado ainda!!\n");
                    sleep(2);
                } else {
                    printf("Esses são os pacientes cadastrados no nosso sistema: \n\n");
                    sleep(1);
                    imprimir_nomes(l);
                    sleep(1);
                    verifica(f, l, dados);
                }
                sleep(3);
                menu_atendimento(escolha, dados, l, f, arvore);
                break;

            case 2:
                system("cls");
                if (f->qtde == 0) {
                    printf("\tNao ha nenhum paciente na fila de espera!!\n");
                    sleep(2);
                    menu_atendimento(escolha, dados, l, f, arvore);
                }
                sala = rand() % 15;
                printf("\tPaciente %s, por favor vá até a sala %d para ser atendido!!\n", f->head->dados.nome, sala);
                dequeue(f);
                sleep(5);
                menu_atendimento(escolha, dados, l, f, arvore);
                break;

            case 3:
                system("cls");
                imprimir_fila(f);
                int sair;
                while(sair != 1) {
                    printf("Digite 1 para sair: ");
                    scanf("%d", &sair);
                }
                if (sair == 1) {
                    menu_atendimento(escolha, dados, l, f, arvore);
                }
                break;

            case 4:
                system("cls");
                printf("Retornando para o menu principal...\n");
                sleep(3);
                menu_principal(escolha, dados, l, f, arvore);
                break;

            default:
                printf("opcao inválida\n");
                sleep(3);
                menu_atendimento(escolha, dados, l, f, arvore);
                break;
        }
    } while (escolha != 4);

    return escolha;
}
int menu_pesquisa(int escolha, Registro dados, Lista *l, Fila *f, ABB *arvore) {
    system("cls");

    printf("Área de pesquisa\n\n");
    printf("O que deseja fazer?\n\n");

    draw_menu_header("Menu de Pesquisa");

    center_text(SIZE_MENU, "1 - Pesquisar por ano de entrada", 1);
    draw_line_cross(SIZE_MENU);
    center_text(SIZE_MENU, "2 - Pesquisar por mes de entrada", 1);
    draw_line_cross(SIZE_MENU);
    center_text(SIZE_MENU, "3 - Pesquisar por dia de entrada", 1);
    draw_line_cross(SIZE_MENU);
    center_text(SIZE_MENU, "4 - Pesquisar por idade", 1);
    draw_line_cross(SIZE_MENU);
    center_text(SIZE_MENU, "5 - Retornar ao menu principal", 1);
    draw_blank_line(SIZE_MENU);

    printf("Escolha uma opcao: ");
    scanf("%d", &escolha);

    do {
        switch(escolha) {
            case 1:
                system("cls");
                printf("Dados dos pacientes, exibidos com base no ano de entrada:\n\n");
                pesquisa(l, arvore, f, dados, escolha);
                break;

            case 2:
                system("cls");
                printf("Dados dos pacientes, exibidos com base no mes de entrada:\n\n");
                pesquisa(l, arvore, f, dados, escolha);
                break;

            case 3:
                system("cls");
                printf("Dados dos pacientes, exibidos com base no dia de entrada:\n\n");
                pesquisa(l, arvore, f, dados, escolha);
                break;

            case 4:
                system("cls");
                printf("Dados dos pacientes, exibidos em ordem do paciente mais novo ao mais velho:\n\n");
                pesquisa(l, arvore, f, dados, escolha);
                break;

            case 5:
                system("cls");
                printf("Retornando para o menu principal...\n");
                sleep(3);
                menu_principal(escolha, dados, l, f, arvore);
                break;

            default:
                printf("opcao inválida\n");
                sleep(3);
                menu_pesquisa(escolha, dados, l, f, arvore);
                break;
        }
    } while (escolha != 5);

    return escolha;
}
int menu_cs(int escolha, Registro dados, Lista *l, Fila *f, ABB *arvore) {
    system("cls");

    printf("Área de atualização do arquivo\n\n");
    printf("O que deseja fazer?\n\n");

    draw_menu_header("Menu de Atualização do Arquivo");

    center_text(SIZE_MENU, "1 - Carregar a lista de cadastros de pacientes", 1);
    draw_line_cross(SIZE_MENU);
    center_text(SIZE_MENU, "2 - Salvar as alterações no arquivo", 1);
    draw_line_cross(SIZE_MENU);
    center_text(SIZE_MENU, "3 - Retornar ao menu principal", 1);
    draw_blank_line(SIZE_MENU);

    printf("Escolha uma opcao: ");
    scanf("%d", &escolha);

    do {
        switch(escolha) {
            case 1:
                system("cls");
                if (l->qtde == 0) {
                    printf("\tCadastros carregados com sucesso!!\n");
                    sleep(3);
                }
                carregar(escolha, dados, l);
                menu_cs(escolha, dados, l, f, arvore);
                break;

            case 2:
                system("cls");
                salvar(escolha, dados, l);
                printf("Arquivo atualizado com sucesso!!\n");
                sleep(3);
                menu_cs(escolha, dados, l, f, arvore);
                break;

            case 3:
                system("cls");
                printf("Retornando para o menu principal...\n");
                sleep(3);
                menu_principal(escolha, dados, l, f, arvore);
                break;

            default:
                printf("opcao inválida\n");
                sleep(3);
                menu_cs(escolha, dados, l, f, arvore);
                break;
        }
    } while (escolha != 3);

    return escolha;
}
int main(void) {
    Lista *l = inicializa_lista();
    Fila *f = cria_Fila();
    ABB *arvore = cria_arvore();
    int escolha;
    Registro dados;

    printf("\t*************************************************************\n");
    printf("\t**************** Bem-vindo ao nosso hospital ****************\n");
    printf("\t*************************************************************\n");
    sleep(3);

    menu_principal(escolha, dados, l, f, arvore);

    return 0;
}
