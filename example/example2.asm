; Move 10 to register a
; and print the value of it to console
mov %a, $21
prints [100]
printi %a
printc $13
printc $13

; If you need register a,
; but if you need also the value of it,
; you can push the register to the stack
push %a

; Work a litle with register a
mov %a, $55
add %a, $71
div %a, $3
prints [180]
printi %a
printc $13
printc $13

; If you need the old value of register a,
; get it from the stack with popping it.
; And print the value of register a.
pop %a
prints [100]
printi %a
printc $13

; Close the program
exit

; Data down here

.space $100
.def "Original value of register a: ", $0

.space $180
.def "New value of a: ", $0

; Assemble it like in example1.asm and execute it