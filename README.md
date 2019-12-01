Ligador e Simulador Assembly --- Calculadora IA-32
************************************************************************************************
CiC - Software Básico

Guilherme de Castro Ribeiro 14/0142151
Victor Gabriel Rodrigues de Almeida 14/0052399
************************************************************************************************

LIGADOR: Na mesma pasta encontram-se arquivos de teste e headers utlizados

Para a compilação:
  g++ main.cpp -o main

Para execução do código:
  ./main arg_1.asm arg_2.asm
_________________________________________________________________________________________________
Observações: Não é necessário a entrada de 2 arquivos para leitura, mas o programa trabalha apenas com 1 ou 2 arquivos de entrada. Mais de 2 arquivos podem ser colocados, mas apenas os 2 primeiros serão ligados.
Ambos devem possuir a extensão ".asm", caso contrário será tratado como erro de extensão e não será feita a ligação.
O processo de montagem gera arquivos ".obj", contendo cabeçado. O ligador gera arquivos ".linked", prontos para serem simulados.
_________________________________________________________________________________________________
_________________________________________________________________________________________________
SIMULADOR: Na mesma pasta entrcontra-se um simulador para os arquivos ".linked" gerados no ligador

Para a compilação:
  g++ simulador.cpp -o simulador

Para execução do código:
  ./simulador arquivo.linked


_________________________________________________________________________________________________
Foi utilizada a seguinte versão do g++ nos testes:

g++ (Debian 6.3.0-18+deb9u1) 6.3.0 20170516
Copyright (C) 2016 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
_________________________________________________________________________________________________
_________________________________________________________________________________________________

CALCULADORA: Na mesma pasta encontra-se, ainda, a calculadora IA-32

Para a compilação:
  nasm -f elf calculadora.asm
  ld -m elf_i386 -s -o calculadora calculadora.o

Para execução:
  ./calculadora
_________________________________________________________________________________________________
Foi utilizada a seguinte versão do NASM nos testes:
NASM version 2.12.01
