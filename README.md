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

Esse problema explora o desafio de coordenar múltiplas threads acessando uma área de memória compartilhada, garantindo uma sincronização eficaz e coordenando as threads a fim de prevenir conflitos e manter a integridade de dados. As principais características desse problema são:

- Algumas threads podem ler e outras podem escrever;
- Nenhuma thread pode acessar a área compartilhada para leitura ou escrita enquanto a outra thread estiver escrevendo.

Desejamos evitar que mais de uma thread modifique o recurso compartilhado simultaneamente. 

## Explicação do código

## Instruções para compilação
