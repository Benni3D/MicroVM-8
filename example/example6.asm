; Declare function-address of "func"
.set _func, $100

; Move a value in parameter-register
mov %a, $10

; Calling function "func"
call _func


; Exit the program
exit

; Define function "func(%a)"
.space _func

; Do some stuff
printi %a
printc $13

; And return from function
ret
