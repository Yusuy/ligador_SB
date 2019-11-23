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

section  .data
endl db 0x0a, 0x0d

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

section .bss
name resb 64
name_size EQU $-name
num1 resb 4
num2 resb 4
cmd resb 1

section .text
global _start:
_start:
jump_line

;print ask_name
mov eax, 4
mov ebx, 1
mov ecx, ask_name
mov edx, ask_name_size
int 0x80

;read name
mov eax, 3
mov ebx, 0
mov ecx, name
mov edx, name_size
int 0x80

jump_line

;print hello_part_1
mov eax, 4
mov ebx, 1
mov ecx, hello_part_1
mov edx, hello_part_1_size
int 0x80

;print name
mov eax, 4
mov ebx, 1
mov ecx, name
int 0x80

;print hello_part_2
mov eax, 4
mov ebx, 1
mov ecx, hello_part_2
mov edx, hello_part_2_size
int 0x80

print_menu:
mov eax, 4
mov ebx, 1
mov ecx, menu
mov edx, menu_size
int 0x80

;print menu_choice
mov eax, 4
mov ebx, 1
mov ecx, menu_choice
mov edx, menu_choice_size
int 0x80

;read cmd
mov eax, 3
mov ebx, 0
mov ecx, cmd
mov edx, 1
int 0x80

jump_line

mov eax, [cmd]
cmp eax, 0x31
jz option_1

mov eax, [cmd]
cmp eax, 0x32
jz option_2

mov eax, [cmd]
cmp eax, 0x33
jz option_3

mov eax, [cmd]
cmp eax, 0x34
jz option_4

mov eax, [cmd]
cmp eax, 0x35
jz option_5

mov eax, [cmd]
cmp eax, 0x36
jz option_6

;print not_a_choice
mov eax, 4
mov ebx, 1
mov ecx, not_a_choice
mov edx, not_a_choice_size
int 0x80
jmp print_menu

option_6:
mov eax, 1
int 0x80

option_1:
jmp print_menu

option_2:
jmp print_menu

option_3:
jmp print_menu

option_4:
jmp print_menu

option_5:
jmp print_menu
