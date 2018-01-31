; Prepare register a for the loop
mov %a, $0

; Down here are the instructions for the loop
printi %a
printc $13
inc %a

; Jump to start of the loop (address 4)
jmp $4

; Because this is is an infinite loop,
; you don't need to close the program

; Assemble it like in example1.asm and execute it