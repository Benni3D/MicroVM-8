; <- This is a comment
; Move 10 to Register a
mov %a, $10

; Move 65 to memory at address 100
mov [100], 'A'

; Print an integer from Register a
printi %a

; Print an char from memory at address 100
printc [100]

; Print an string from memory at address 101
prints [101]

; Print directly integers to console
printi $100

; Print a new line (13 = '\n')
printc $13

; Move 10 to register a and 21 to register b
mov %a, $10
mov %b, $21

; Add register b to register a (a += b)
add %a, %b

; And print the value of register a to console
printi %a

; hlt for halt the program
; or exit to close it
exit
; Down here is only Data

; Let space to address 101
.space $101

; Define the string "This is an example String!"
; And define 2 Bytes 13 for new line and 0 for end of string
.def "This is an example String!", $13, $0


; To assemble this example
; Copy the executable in this directory,
; open a console and write "microasm8 <src-file> <output-file>" in it
; After that execute the Virtual Machine
; with "microvm8 <output-file-of-assembler>".