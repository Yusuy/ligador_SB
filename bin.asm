zero: equ 0
um: equ 1
tres: equ 3
quatro: equ 4
SECTION DATA
DOIS: CONST 2
OLD_DATA: SPACE
NEW_DATA: SPACE
TMP_DATA: SPACE
SECTION TEXT
INPUT OLD_DATA
LOAD OLD_DATA
L1: DIV DOIS
STORE  NEW_DATA
MULT DOIS
STORE TMP_DATA
LOAD OLD_DATA
SUB TMP_DATA
STORE TMP_DATA
OUTPUT TMP_DATA
COPY NEW_DATA,OLD_DATA
copy a, zero
copy b, um
copy c, tres
copy d, quatro
copy aa, a+zero
copy bb, b+um
copy cc, c+tres
copy dd, d+quatro
LOAD OLD_DATA
JMPP L1
STOP
