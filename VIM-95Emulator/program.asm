; Initialize counter to ASCII '0'
LDA 30

; Label: loop_start
loop_start:

; Output the current counter value
STA FF

; Check if the counter is at '9' (0x39)
CMP 39
JEQ end_loop

; Increment the counter
ADD 01

; Jump back to the start of the loop
JMP loop_start

; Label: end_loop
end_loop:

; Halt the CPU (Assuming HALT is implemented as 0xFF)
HALT