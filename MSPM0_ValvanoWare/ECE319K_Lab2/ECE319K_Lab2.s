// ****************** ECE319K_Lab2.s ***************
// Your solution to Lab 2 in assembly code
// Author: Your name
// Last Modified: Your date
// ECE319K Spring 2026 (ECE319H students do Lab2H)
// I/O port addresses
    .include "../inc/msp.s"

        .data
        .align 2
// Declare global variables here if needed 

        
// with the .space assembly directive


        .text
        .thumb
        .align 2
        .global EID
EID:    .string "HC32869" // replace ZZZ123 with your EID here
        .align 2

// this allow your Lab2 programs to the Lab2 grader
        .global Lab2Grader
// this allow the Lab2 grader to call your Lab2 program
        .global Lab2
// these two allow your Lab2 programs to all your Lab3 solutions
        .global Debug_Init
        .global Dump

// Switch input: PB2 PB1 or PB0, depending on EID
// LED output:   PB18 PB17 or PB16, depending on EID
// logic analyzer pins PB18 PB17 PB16 PB2 PB1 PB0
// analog scope pin PB20
Lab2:
// Initially the main program will
//   set bus clock at 80 MHz,
//   reset and power enable both Port A and Port B
// Lab2Grader will
//   configure interrupts  on TIMERG0 for grader or TIMERG7 for TExaS
//   initialize ADC0 PB20 for scope,
//   initialize UART0 for grader or TExaS
     MOVS R0,#1
// 0 for info,
// 1 debug with logic analyzer,
// 2 debug with scope,
// 3 debug without scope or logic analyzer
// 10 for grade
     BL   Lab2Grader
     BL   Debug_Init // your Lab3 (ignore this line while doing Lab 2)
    BL   Lab2Init
loop:
   
     B    loop


// make switch an input, LED an output
// PortB is already reset and powered
// Set IOMUX for your input and output
// Set GPIOB_DOE31_0 for your output (be friendly)
time:   .long 1600000
         .long 160000
         .long 480000
         .long 1040000
         .long 1120000


Lab2Init: PUSH {R4-R7, LR}
// ***do not reset/power Port A or Port B, already done****
LDR R1, =IOMUXPB2
LDR R0, =0x40081
STR R0, [R1]
LDR R1, =IOMUXPB18
LDR R0, =0x00081
STR R0, [R1]
LDR R1, =GPIOB_DOE31_0
LDR R0, [R1]
MOVS R2, #1
LSLS R2, R2, #18
ORRS R0, R0, R2
STR R0, [R1]
//setup
LDR R6, =time
MOVS R7, #4
LDR R5, =GPIOB_DIN31_0
mloop:
LDRB R2, [R5]
MOVS R1, #4
ANDS R1, R1, R2
BEQ noin //NO INPUT
ADDS R7, R7, #4
CMP R7, #20
BLT noreset //if less than
MOVS R7, #4
noreset:
inloop:
LDR R2, [R5]
MOVS R1, #4
ANDS R1, R1, R2
BNE inloop //NO INPUT
noin:
LDR R1, [R6]
ADDS R0, R6, R7
LDR R0, [R0]
SUBS R1, R1, R0
LDR R2, =GPIOB_DOUT31_0
LDR R4, =0X40000
STR R4, [R2]
PUSH {R0-R4}
BL  Dump
POP {R0-R4}
BL Delay
MOVS R0, R1
LDR R4, =0
LDR R2, =GPIOB_DOUT31_0
STR R4, [R2]
PUSH {R0-R4}
BL  Dump
POP {R0-R4}
BL Delay
B mloop
POP {R4-R7, PC} 
BX   LR

//R0 contains delay time in cycles
Delay: 
SUBS R0, R0, #3
Dloop:
NOP
SUBS R0, R0, #4
BPL Dloop //Positive or zero 
BX   LR

   .end
