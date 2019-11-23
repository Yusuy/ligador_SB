Ligador
CiC - Software Básico

Guilherme de Castro Ribeiro 14/0142151
Victor Gabriel Rodrigues de Almeida 14/0052399

Ligador: Na mesma pasta encontram-se arquivos de teste e headers utlizados

Para a compilação:
  g++ main.cpp -o main

Para execução do código:
  ./main arg_1.asm arg_2.asm

Observações: Não é necessário a entrada de 2 arquivos para leitura, mas o programa trabalha apenas com 1 ou 2 arquivos de entrada
e ambos devem possuir a extensão ".asm", caso contrário será tratado como erro de extensão e não será feita a ligação.

Foi utilizada a seguinte versão do g++ nos testes:

g++ (Debian 6.3.0-18+deb9u1) 6.3.0 20170516
Copyright (C) 2016 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
