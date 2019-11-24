;CALCULADORA NASM
;cd /home/victor//github/ligador_SB
;nasm -f elf calculadora.asm
;ld -m elf_i386 -s -o calculadora calculadora.o
;./calculadora

%macro jump_line 0
mov eax, 4
mov ebx, 1
mov ecx, endl
mov edx, 2
int 0x80
%endmacro

%macro cheguei 0
mov eax, 4
mov ebx, 1
mov ecx, msg
mov edx, msg_size
int 0x80
%endmacro

section  .data
endl db 0x0a, 0x0d
msg db "Cheguei", 0x0a, 0x0d
msg_size EQU $-msg

ask_name db "Por favor, digite seu nome: "
ask_name_size EQU $-ask_name

hello_part_1 db "Olá, "
hello_part_1_size EQU $-hello_part_1

hello_part_2 db "Bem-vindo ao programa de CALC IA-32", 0x0a, 0x0d
hello_part_2_size EQU $-hello_part_2

menu db "ESCOLHA UMA OPÇÃO:", 0X0a, 0x0d, "1 - SOMA", 0X0a, 0x0d, "2 - SUBTRAÇÃO", 0X0a, 0x0d, "3 - MULTIPLICAÇÃO", 0X0a, 0x0d, "4 - DIVISÃO", 0X0a, 0x0d, "5 - MOD" , 0X0a, 0x0d, "6 - SAIR", 0X0a, 0x0d
menu_size EQU $-menu

menu_choice db "Opção escolhida: "
menu_choice_size EQU $-menu_choice

not_a_choice db "Opção inválida, digite uma opção válida", 0x0a, 0x0d
not_a_choice_size EQU $-not_a_choice

ask_first_op db "Digite o primeiro operando: "
ask_first_op_size EQU $-ask_first_op

ask_second_op db "Digite o segundo operando: "
ask_second_op_size EQU $-ask_second_op

section .bss
name resb 32
name_size EQU $-name
num1 resb 4
num2 resb 4
cmd resb 1

section .text
global _start:
_start:
jump_line

mov ecx, ask_name
mov edx, ask_name_size
call print

mov ecx, name
mov edx, name_size
call read

jump_line

mov ecx, hello_part_1
mov edx, hello_part_1_size
call print

mov ecx, name
mov edx, name_size
call print

mov ecx, hello_part_2
mov edx, hello_part_2_size
call print

print_menu:
mov ecx, menu
mov edx, menu_size
call print

mov ecx, menu_choice
mov edx, menu_choice_size
call print

mov ecx, cmd
mov edx, 1
call read

mov eax, [cmd]
cmp eax, 0x36
je option_6

mov ecx, ask_first_op
mov edx, ask_first_op_size
call print

mov ecx, num1
mov edx, 4
call read

jump_line

mov ecx, ask_second_op
mov edx, ask_second_op_size
call print

mov ecx, num2
mov edx, 4
call read

jump_line

option_6:
mov eax, 1
mov ebx, 0
int 0x80

print:
mov eax, 4
mov ebx, 1
int 0x80
ret

read:
mov eax, 3
mov ebx, 0
int 0x80
ret
