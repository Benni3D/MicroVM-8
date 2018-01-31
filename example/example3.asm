; Initialize register a and b
mov %a, $1
mov %b, $3

; Shift register a 4 bits to left (a <<= 4)
lshf %a, $4

; Bitwise xor to a with b (a ^= b)
xor %a, %b

; Print the value of register a
printi %a

; Exit the program
exit

; Assemble it like in example1.asm and execute it