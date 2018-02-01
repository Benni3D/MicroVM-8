; Declare function main_loop 
.set _main_loop, $50

; Initialize counter-register with
; with 3, because we want to loop 3 times
; the function main_loop
mov %c, $3

; Call main_loop
call _main_loop

; Exit the program 
exit

; Define function main_loop 
.space _main_loop
; Print an integer to the screen 
printi $21
printc $13

; Sleep 10 seconds 
sleep $10

; And loop function main_loop

loop _main_loop

; Return from function
ret
