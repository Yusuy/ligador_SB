;CALCULADORA NASM
;cd /home/victor/Desktop/calc
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
hello1 db "Olá, como você se chama?", 0x0D, 0x0A
size1 EQU $-hello1
hello2 db "Bem-vindo ao programa de CALC IA-32, "
size2 EQU $-hello2
menu db "ESCOLHA UMA OPÇÃO:", 0x0D, 0x0A, "-1: SOMA", 0x0D, 0x0A, "-2: SUBTRAÇÃO", 0x0D, 0x0A, "-3: MULTIPLICAÇÃO", 0x0D, 0x0A, "-4: DIVISÃO", 0x0D, 0x0A, "-5: MOD", 0x0D, 0x0A, "-6: SAIR", 0x0D, 0x0A
sizemenu EQU $-menu
endl db 0x0D, 0x0A
msg1 db "Nome: "
msg1size EQU $-msg1
msg2 db "Opção escolhida: "
msg2size EQU $-msg2
msg3 db "Opção inválida, tente novamente.", 0x0D, 0x0A, 0x0D, 0x0A
msg3size EQU $-msg3

section .bss
name resb 32
namesize EQU $-name
num1 resb 4
num2 resb 4
cmd resb 1

section .text
global _start:
_start:
jump_line

;print hello_msg_1
mov eax, 4
mov ebx, 1
mov ecx, hello1
mov edx, size1
int 0x80

;print msg_1
mov eax, 4
mov ebx, 1
mov ecx, msg1
mov edx, msg1size
int 0x80

;read name
mov eax, 3
mov ebx, 0
mov ecx, name
mov edx, namesize
int 0x80

;print hello2
mov eax, 4
mov ebx, 1
mov ecx, hello2
mov edx, size2
int 0x80

;print name
mov eax, 4
mov ebx, 1
mov ecx, name
mov edx, namesize
int 0x80

jump_line

;print menu
mov eax, 4
mov ebx, 1
mov ecx, menu
mov edx, sizemenu
int 0x80

menumsg:
;print msg2
mov eax, 4
mov ebx, 1
mov ecx, msg2
mov edx, msg2size
int 0x80

;read cmd
mov eax, 3
mov ebx, 0
mov ecx, cmd
mov edx, 1
int 0x80

sub eax, eax
;mov eax, [cmd] ;movendo pra eax o valor no endereço de cmd
;sub eax, 0x30  ;transformando em valor inteiro
;cmp eax, 1     ;comparando 1-1 = ?
jz op1         ;salta se ? = 0 (ZF setada)

add eax, 1
cmp eax, 2
jz op2

add eax, 2
cmp eax, 3
jz op3

add eax, 3
cmp eax, 4
jz op4

add eax, 4
cmp eax, 5
jz op5

add eax, 5
cmp eax, 6
jz return

;print msg3
mov eax, 4
mov ebx, 1
mov ecx, msg3
mov edx, msg3size
int 0x80
jmp menumsg

;FIM DO PROGRAMA
return:
mov eax, 1
int 0X80

op1:
call menumsg

op2:
call menumsg

op3:
call menumsg

op4:
call menumsg

op5:
call menumsg
