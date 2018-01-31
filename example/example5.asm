; Print the string at address 65
prints [65]

; Read the name from console and save it to address 150
reads [150]

; Say "Welcome, " and the name from address 150 and a new line
prints [50]
prints [150]
printc $13

; Close the program
exit

; Data down here

.space $50
.def "Welcome ", $0
.space $65
.def "Welcome to our Example program", $13, "What is your name? ", $0

; Assemble it like in example1.asm and execute it