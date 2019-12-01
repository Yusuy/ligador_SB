;------------- UnB - Software Básico - 02/2019 ----------
;------------- Trabalho 2.3 - CALCULADORA NASM ----------
;--------------------------------------------------------
;- Guilherme de Castro Ribeiro - 14/0142151 -------------
;- Victor Gabriel Rodrigues de Almeida - 14/0052399 -----
;--------------------------------------------------------
;- COMANDOS PARA EXECUÇÃO : 
;      nasm -f elf calculadora.asm
;      ld -m elf_i386 -s -o calculadora calculadora.o
;      ./calculadora
;--------------------------------------------------------


%macro jump_line 0 ; MACRO PARA PRINTAR UMA LINHA VAZIA 
push ebp
mov ebp,esp
push eax
push ebx
push ecx
push edx
mov eax, 4
mov ebx, 1
mov ecx, endl
mov edx, endl_size
int 0x80
pop edx
pop ecx
pop ebx
pop eax
pop ebp
%endmacro

%macro cheguei 0 ; MACRO PARA DEBUGGAR PROGRAMA
push ebp
mov ebp,esp
push eax
push ebx
push ecx
push edx
mov eax, 4
mov ebx, 1
mov ecx, msg
mov edx, msg_size
int 0x80
pop edx
pop ecx
pop ebx
pop eax
pop ebp
%endmacro

%macro nao_devia 0 ; MACRO PARA DEBUGGAR PROGRAMA
push ebp
mov ebp,esp
push eax
push ebx
push ecx
push edx
mov eax, 4
mov ebx, 1
mov ecx, msg2
mov edx, msg2_size
int 0x80
pop edx
pop ecx
pop ebx
pop eax
pop ebp
%endmacro


;-------------------------DATA---------------

section .data

endl db 0dH,0ah
endl_size EQU $-endl
msg db 'Cheguei dentro da soma',0dH,0ah
msg_size EQU $-msg
msg2 db 'NAO DEVIA ESTAR AQUI',0dH,0ah
msg2_size EQU $-msg


ask_name db 'Por favor, digite seu nome: ',0dH,0ah
ask_name_size EQU $-ask_name

hello_part_1 db 'Olá, ',0
hello_part_1_size EQU $-hello_part_1

hello_part_2 db 'Bem-vindo ao programa de CALC IA-32',0dH,0ah
hello_part_2_size EQU $-hello_part_2

menu db 0dH,0ah,'ESCOLHA UMA OPÇÃO:',0dH,0ah,'1 - SOMA',0dH,0ah,'2 - SUBTRAÇÃO',0dH,0ah,'3 - MULTIPLICAÇÃO',0dH,0ah,'4 - DIVISÃO',0dH,0ah,'5 - MOD',0dH,0ah,'6 - SAIR',0dH,0ah
menu_size EQU $-menu

menu_choice db 'Opção escolhida: ',0
menu_choice_size EQU $-menu_choice

not_a_choice db 'Opção inválida, digite uma opção válida',0dH,0ah
not_a_choice_size EQU $-not_a_choice

ask_first_op db 'Digite o primeiro operando: ',0dH,0ah
ask_first_op_size EQU $-ask_first_op

ask_second_op db 'Digite o segundo operando: ',0dH,0ah
ask_second_op_size EQU $-ask_second_op

msg_result db 'Resultado: ',0
msg_result_size EQU $-msg_result

minus_symbol db '- ',0dH
number_zero db '0 ',0dH
number_one db '1 ',0dH
number_two db '2 ',0dH
number_three db '3 ',0dH
number_four db '4 ',0dH
number_five db '5 ',0dH
number_six db '6 ',0dH
number_seven db '7 ',0dH
number_eight db '8 ',0dH
number_nine db '9 ',0dH


;-------------------------BSS---------------

section .bss

first_op resb 32
first_op_size EQU $-first_op

buffer_first_op resd 1
;buffer_first_op_size EQU $-buffer_first_op

second_op resb 32
second_op_size EQU $-second_op

buffer_second_op resd 1

name resb 32
name_size EQU $-name

cmd resb 1

index resb 32

wait_key_op resb 32
wait_key_op_size EQU $-wait_key_op


; ------------------------TEXT---------------

section .text
global _start

_start: 
jump_line              ; Pula linha

push ask_name
push ask_name_size
call print             ; Função que escreve strings

push name
push name_size
call read              ; Função que recebe/lê strings

;jump_line

push hello_part_1
push hello_part_1_size
call print

push name
push name_size
call print

push hello_part_2
push hello_part_2_size
call print

print_menu:
push menu
push menu_size
call print


call_menu_choice:

push menu_choice
push menu_choice_size
call print


mov edx,1
push cmd            ; Variável que recebe opção de
push edx            ; instrução feita pelo usuário
call read

cmp byte [cmd],0x31 ; SOMA - OP 1
je option_1

cmp byte [cmd],0x32 ; SUB - OP 2
je option_2

cmp byte [cmd],0x33  ; MULT - OP 3
je option_3

cmp byte [cmd],0x34  ; DIV - OP 4
je option_4

cmp byte [cmd],0x35  ; MOD - OP 5
je option_5

cmp byte [cmd],0x36 ; SAIR - OP 6
je option_6

jmp print_menu  ; Caso nenhuma opção váida seja escolhida,
                ; printa novamente o menu


;---------------SOMA------------

option_1:

call empty_operators

push ask_first_op
push ask_first_op_size
call print

receive_op1:

push first_op
push first_op_size
call read

cmp dword [first_op],10 ; Caso input recebido seja "enter" do teclado,
jz receive_op1          ; retorna para a requisição de entrada

push ask_second_op
push ask_second_op_size
call print

receive_op2:

push second_op
push second_op_size
call read

cmp dword [second_op],10 ; Caso input recebido seja "enter" do teclado,
jz receive_op2           ; retorna para a requisição de entrada

push first_op
push first_op_size
call convert_first_to_int ; Função que converte string para inteiro com sinal

push second_op
push second_op_size
call convert_second_to_int ; Função que converte string para inteiro com sinal

mov eax,[buffer_first_op]
mov ebx,[buffer_second_op]
add eax,ebx                ; Soma os dois operandos da instrução

push msg_result
push msg_result_size
call print

push eax
call print_signed          ; Função que escreve número inteiro com sinal


jump_line

call wait_key ; Função que espera que usuário pressione tecla
              ; para seguir execução
jump_line

jmp print_menu

;---------------SUB------------

option_2:

call empty_operators

push ask_first_op
push ask_first_op_size
call print

receive_op1_sub:

push first_op
push first_op_size
call read

cmp dword [first_op],10
jz receive_op1_sub

push ask_second_op
push ask_second_op_size
call print

receive_op2_sub:

push second_op
push second_op_size
call read

cmp dword [second_op],10
jz receive_op2_sub

push first_op
push first_op_size
call convert_first_to_int

push second_op
push second_op_size
call convert_second_to_int

mov eax,[buffer_first_op]
mov ebx,[buffer_second_op]

not ebx             ; Faz o complemento de 2 no
add ebx,1           ; segundo operando

add eax,ebx         ; Soma operandos

push msg_result
push msg_result_size
call print

push eax
call print_signed


jump_line

call wait_key

jump_line

jmp print_menu

;---------------MULT------------

option_3:

call empty_operators

push ask_first_op
push ask_first_op_size
call print

receive_op1_mult:

push first_op
push first_op_size
call read

cmp dword [first_op],10
jz receive_op1_mult

push ask_second_op
push ask_second_op_size
call print

receive_op2_mult:

push second_op
push second_op_size
call read

cmp dword [second_op],10
jz receive_op2_mult

push first_op
push first_op_size
call convert_first_to_int

push second_op
push second_op_size
call convert_second_to_int

mov eax,[buffer_first_op]
mov ebx,[buffer_second_op]
mul ebx                     ; Faz multiplicação dos operandos

push msg_result
push msg_result_size
call print

push eax
call print_signed


jump_line

call wait_key

jump_line

jmp print_menu


;---------------DIV------------

option_4:

call empty_operators

push ask_first_op
push ask_first_op_size
call print

receive_op1_div:

push first_op
push first_op_size
call read

cmp dword [first_op],10
jz receive_op1_div

push ask_second_op
push ask_second_op_size
call print

receive_op2_div:

push second_op
push second_op_size
call read

cmp dword [second_op],10
jz receive_op2_div

push first_op
push first_op_size
call convert_first_to_int

push second_op
push second_op_size
call convert_second_to_int

mov eax,[buffer_first_op]
mov ebx,[buffer_second_op]

cdq                         ; Estende o EAX para EDX:EAX
idiv ebx                    ; Faz a divisão

push msg_result
push msg_result_size
call print

push eax                    ; Retorna quociente da divisão
call print_signed

jump_line

call wait_key

jump_line

jmp print_menu

;---------------MOD------------

option_5:

call empty_operators

push ask_first_op
push ask_first_op_size
call print

receive_op1_mod:

push first_op
push first_op_size
call read

cmp dword [first_op],10
jz receive_op1_mod

push ask_second_op
push ask_second_op_size
call print

receive_op2_mod:

push second_op
push second_op_size
call read

cmp dword [second_op],10
jz receive_op2_mod

push first_op
push first_op_size
call convert_first_to_int

push second_op
push second_op_size
call convert_second_to_int

mov eax,[buffer_first_op]
mov ebx,[buffer_second_op]
cdq
idiv ebx

push msg_result
push msg_result_size
call print

push edx                    ; Retorna resto da divisão
call print_signed

jump_line

call wait_key

jump_line

jmp print_menu

;---------------SAIR------------

option_6:

mov eax, 1   ; Comandos para encerrar programa
mov ebx, 0
int 0x80



;-----------------WAIT-KEY---------------

wait_key:

mov eax,3                   ; Comandos para realizar leitura
mov ebx,0                   ; do teclado
mov ecx,wait_key_op
mov edx,wait_key_op_size
int 80h

ret 4

;------------CONVERT-FIRST-TO-INT----------

convert_first_to_int:

mov byte [index],0 ; Zera index

push ebp            ; Empilha regs
mov ebp,esp
push eax
push ebx
push ecx
push edx

mov eax,[ebp+12]    ; Atualiza regs
mov esi,eax
mov eax,0
mov ecx,0

begin_pass1:        ; Faz passagens pela string do operador
xor ebx,ebx         
mov bl,[esi+ecx]    ; Pega uma parte do operador

cmp bl,45               ; Verifica se é o sinal de negativo
je minus_symbol_pass1

cmp bl,57               ; Verifica se é maior que 9 (tabela ascii)
jg end_pass1

cmp bl,48               ; Verifica se é menor que 0 (tabela ascii)
jl end_pass1

cmp bl,10               ; Verifica se é \n
je end_pass1

cmp bl,13               ; Verifica se é CR
je end_pass1

cmp bl,0                ; Verifica se é NULL
jz end_pass1

sub bl,48               ; Converte para int
add eax,ebx             ; Soma ao int
mov ebx,10              ; 
mul ebx                 ; Multiplica por 10

jmp next_pass1

minus_symbol_pass1:
mov byte [index],1 

next_pass1:
inc ecx

jmp begin_pass1

end_pass1:
mov ebx,10
div ebx

cmp byte [index],1
jne negative_pass1

mov ecx,0FFFFFFFFH
imul ecx

negative_pass1:
mov dword [buffer_first_op],eax

pop edx             ; Desempilha
pop ecx
pop ebx
pop eax
pop ebp

ret 4

;------------CONVERT-SECOND-TO-INT----------

convert_second_to_int:

mov byte [index],0

push ebp
mov ebp,esp
push eax
push ebx
push ecx
push edx

mov eax,[ebp+12]
mov esi,eax
mov eax,0
mov ecx,0

begin_pass2:
xor ebx,ebx
mov bl,[esi+ecx]

cmp bl,45
je minus_symbol_pass2

cmp bl,57
jg end_pass2

cmp bl,48
jl end_pass2

cmp bl,10
je end_pass2

cmp bl,13
je end_pass2

cmp bl,0
jz end_pass2

sub bl,48
add eax,ebx
mov ebx,10
mul ebx

jmp next_pass2

minus_symbol_pass2:
mov byte [index],1

next_pass2:
inc ecx

jmp begin_pass2

end_pass2:
mov ebx,10
div ebx

cmp byte [index],1
jne negative_pass2

mov ecx,0FFFFFFFFH
imul ecx

negative_pass2:
mov dword [buffer_second_op],eax

pop edx
pop ecx
pop ebx
pop eax
pop ebp

ret 4


;---------------PRINT-SIGNED-----------

print_signed:

push ebp            ; Empilha regs
mov ebp,esp
push eax
push ebx
push ecx
push edx

mov eax,[ebp+8]

cmp eax,0
jge positive_number

mov eax,4            ; Printa sinal de menos
mov ebx,1
mov ecx,minus_symbol
mov edx,1
int 80h

mov eax,[ebp+8]
add eax,-1
not eax

positive_number:

mov ecx,0

begin_number_verification:
inc ecx
mov edx,0
mov esi,10
idiv esi
push edx

cmp ecx,32
jnz begin_number_verification

mov eax,0

number_printing:
inc eax
pop edx
mov ecx,edx
push eax

cmp ecx,1
jne next_1          ; Verifica qual número é representado por 
                    ; em cada bit do reg. Printa se corresponder
                    ; com o que está sendo verificado.
mov eax,4
mov ebx,1
mov ecx,number_one   
mov edx,1
int 80h

next_1:
cmp ecx,2
jne next_2

mov eax,4
mov ebx,1
mov ecx,number_two
mov edx,1
int 80h

next_2:
cmp ecx,3
jne next_3

mov eax,4
mov ebx,1
mov ecx,number_three
mov edx,1
int 80h

next_3:
cmp ecx,4
jne next_4

mov eax,4
mov ebx,1
mov ecx,number_four
mov edx,1
int 80h

next_4:
cmp ecx,5
jne next_5

mov eax,4
mov ebx,1
mov ecx,number_five
mov edx,1
int 80h

next_5:
cmp ecx,6
jne next_6

mov eax,4
mov ebx,1
mov ecx,number_six
mov edx,1
int 80h

next_6:
cmp ecx,7
jne next_7

mov eax,4
mov ebx,1
mov ecx,number_seven
mov edx,1
int 80h

next_7:
cmp ecx,8
jne next_8

mov eax,4
mov ebx,1
mov ecx,number_eight
mov edx,1
int 80h

next_8:
cmp ecx,9
jne next_9

mov eax,4
mov ebx,1
mov ecx,number_nine
mov edx,1
int 80h

next_9:
cmp ecx,0
jne next_0

mov eax,4
mov ebx,1
mov ecx,number_zero
mov edx,1
int 80h

next_0:
pop eax
cmp eax,32
jne number_printing

pop edx
pop ecx
pop ebx
pop eax
pop ebp

ret 4


;---------------PRINT------------

print:

push ebp                ; Empilha todos valores de todos os
mov ebp,esp             ; registradores e altera posição do
push eax                ; base pointer.
push ebx
push ecx
push edx
mov eax,4               ; Comandos para imprimir string
mov ebx,1
mov ecx,[ebp + 12]
mov edx,[ebp + 8]
int 80h
pop edx                 ; Retorna valores empilhados aos 
pop ecx                 ; registradores
pop ebx
pop eax
pop ebp
ret 4


;---------------READ------------

read:

push ebp                ; Empilha todos valores de todos os
mov ebp,esp             ; registradores e altera posição do
push eax                ; base pointer.
push ebx
push ecx
push edx
mov eax,3               ; Comandos para ler do teclado
mov ebx,0
mov ecx,[ebp + 12]
mov edx,[ebp + 8]
int 80h
pop edx                 ; Retorna valores empilhados aos 
pop ecx                 ; registradores
pop ebx
pop eax
pop ebp
ret 4


;------------EMPTY-OPERATORS-------------

empty_operators:

push ecx
mov ecx,0

loop:                       ; Loop para zerar conteudo das
mov byte [first_op+ecx],0   ; variaveis que armazenam os 
mov byte [second_op+ecx],0  ; operadores. Garantir que não
cmp ecx,31                  ; tenham lixo de memória.
jne index_sum

pop ecx
ret 4

index_sum:
inc ecx
jmp loop


;------------------------------------------