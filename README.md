# MC504
Este repositório possui o código para o Projeto Multithread da disciplina MC504.

## Integrantes
Ana Carolina de Almeida Cardoso, 246914

Pedro Damasceno Vasconcellos, 260640

Mateus de Lima Almeida, 242827

Victor Hoshikawa Satoh, 260711

## Objetivo
Nosso projeto visa implementar uma solução, utilizando semáforos, mutex locks e variáveis de condição, para modelar o problema dos Leitores e Escritores, apresentado na seção 4.2 do livro The Little Book of Semaphores, de Allen Downey.

## Contextualização

![image](https://github.com/user-attachments/assets/1cbf12d4-f318-4507-9e6a-335efe32b9cb)

Esse problema explora o desafio de coordenar múltiplas threads acessando uma área de memória compartilhada (geralmente um banco de dados ou um arquivo), garantindo uma sincronização eficaz e coordenando as threads a fim de prevenir conflitos e manter a integridade de dados. Nesse problema, utilizamos threads para representar:

- **Leitores**: só leem um recurso.
- **Escritores:** modificam esse recurso.

Desejamos evitar que mais de uma thread modifique o recurso compartilhado simultaneamente, garantindo consistência e segurança. 

## Instruções para compilação

Para compilar esse projeto, basta no terminal digitar `make` na pasta do projeto. Isso irá utilizar o arquivo `Makefile` para gerar um arquivo executável chamado `./leitores_escritores`. Por fim, é necessário digitar no terminal:

```
./leitores_escritores N M
```
Onde N e M são respectivamente o número de leitores e escritores, onde obrigatoriamente deve-se ter N < 10 e M < 3. Com isso, será visualizada a execução simultânea de múltiplas threads leitoras e escritoras, que alternam entre si em:

- Leitura do buffer.
- Escrita no buffer.
- Atualização do estado global ASCII.

## Funcionamento do código
Para resolver o Problema dos Leitores-Escritores, criamos um modelo de solução que utiliza threads, mutexes e variáveis de condição. Temos um recurso compartilhado entre as threads que é um buffer de texto, que pode ser acessado por qualquer leitor simultaneamente, desde que nenhum escritor esteja ativo. O escritor, por sua vez, precisa de exclusividade total: ele só entra quando não há leitores e escritores ativos.

### Estrutura de sincronização 
```
typedef struct {
    int leitores_ativos;
    int escritores_ativos;
    int leitores_esperando;
    int escritores_esperando;
    char buffer[MAX_BUFFER];
} Estado;
```
- `buffer` armazena a última mensagem escrita por um escritor.
- `leitores_ativos` e `escritores_ativos` controlam o número de threads dentro da seção crítica.
- `leitores_esperando` e `escritores_esperando` armazenam quantos estão aguardando entrada.

Além disso, também utilizamos:

``` 
pthread_mutex_t mutex;
pthread_cond_t cond_leitor;
pthread_cond_t cond_escritor;
```
- `mutex` garante exclusão mútua no acesso ao estado compartilhado.
- `cond_leitor` e `cond_escritor` são utilizadas para controlar o avanço de leitores e escritores conforme as condições do sistema.

### Lógica de controle

- **Leitores**:
  - Entram se não houver escritores ativos.
  - Quando o último leitor sai, acorda um escritor, caso haja um aguardando.
 
- **Escritores**:
  - Só entram se não houver leitores e escritores ativos.
  - Ao sair, priorizam outro escritor se houver ou liberam todos os leitores.

Um sistema de log exibe o estado global do nosso programa, indicando quem está lendo, quem está escrevendo, quem está esperando e o conteúdo atual do buffer.

## Exemplo de saída do código

Durante a execução do nosso código, vemos repetidamente o estado do nosso sistema após cada entrada/saída de um leitor ou escritor, impresso da seguinte maneira: 
```
╔═════════════ ESTADO DO SISTEMA ═════════════╗
║ Escritor ativo        : [E0]                ║
║ Leitores ativos       : (nenhum)            ║
║ Buffer                : "Escrito por escritor 0"
║---------------------------------------------║
║ Leitores esperando    : L1 L2               ║
║ Escritores esperando  : E1                  ║
╚═════════════════════════════════════════════╝
```
Quando alguma thread realiza alguma ação, é exibida uma mensagem que indica o que foi feito.
```
Escritor 0 escreveu
Leitor 1 leu: Escrito por escritor 0. 
```

## Organização do código

Os arquivos principais do nosso programa são:
- `sync.h` e `sync.c`: implementam a lógica de sincronização usando `pthread_mutex_t` e `pthread_cond_t`, além do controle do estado global compartilhado. Gerenciam a entrada e a saída de leitores e escritores, assegurando o respeito às regras de exclusão mútua e prioridade.
- `leitor.c`: contém a função de thread dos leitores, que acessam o buffer compartilhado se não houver escritor ativo. Leitores podem atuar simultaneamente.
- `escritor.c`: define o comportamento das threads escritoras, que precisam de acesso exclusivo ao buffer. Um escritor só entra quando não há outros leitores e escritores ativos.
- `logger.c`: responsável por imprimir o estado atual do sistema em formato ASCII, exibindo leitores e escritores que estão ativos ou esperando, além do conteúdo atual do buffer.
- `main.c`: cria as threads de leitores e escritores, inicializa a sincronização e executa o programa por um período fixo de 15s.
- `Makefile`: auxilia com a compilação do projeto.
