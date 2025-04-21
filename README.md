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

Para compilar esse projeto, basta no terminal digitar `make` na pasta do projeto. Isso irá utilizar o arquivo `Makefile` para gerar um arquivo executável chamado `./leitores_escritores`. Basta digitar o nome do arquivo executável no terminal para que seja visualizada a execução simultânea de múltiplas threads leitoras e escritoras, que alternam em:

- Leitura do buffer.
- Escrita no buffer.
- Atualização do estado global ASCII.

## Organização do código


## Funcionamento do código


