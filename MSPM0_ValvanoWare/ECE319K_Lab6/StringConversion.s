// StringConversion.s
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly
// Runs on any Cortex M0
// ECE319K lab 6 number to string conversion
//
// You write udivby10 and Dec2String
     .data
     .align 2
// no globals allowed for Lab 6
    .global OutChar    // virtual output device
    .global OutDec     // your Lab 6 function
    .global Test_udivby10

    .text
    .align 2
// **test of udivby10**
// since udivby10 is not AAPCS compliant, we must test it in assembly
Test_udivby10:



    MOVS R0,#123
    BL   udivby10
// put a breakpoint here
// R0 should equal 12 (0x0C)
// R1 should equal 3

    LDR R0,=12345
    BL   udivby10
// put a breakpoint here
// R0 should equal 1234 (0x4D2)
// R1 should equal 5

    MOVS R0,#0
    BL   udivby10
// put a breakpoint here
// R0 should equal 0
// R1 should equal 0
    POP {PC}

// ****************************************************
// divisor=10
// Inputs: R0 is 16-bit dividend
// quotient*10 + remainder = dividend
// Output: R0 is 16-bit quotient=dividend/10
//         R1 is 16-bit remainder=dividend%10 (modulus)
// not AAPCS compliant because it returns two values
udivby10:
    PUSH {R4-R7, LR} //R0 IN, R1 LOW, R2 MID, R3 UP, R4 MID*10
    MOVS R1, R0
    MOVS R3, R0
    LSRS R1, #4
    LSRS R3, #2
loop: 
    CMP R1, R3
    BEQ end
    ADDS R2, R1, R3
    ADDS R2, #1
    LSRS R2, #1
    MOVS R4, #10
    MULS R4, R2
    CMP R4, R0
    BEQ end
    BLO less
    MOVS R3, R2
    SUBS R3, #1
    B loop
    less:
    MOVS R1, R2
    B loop
end:
    ADDS R2, R1, R3
    ADDS R2, #1
    LSRS R2, #1
    MOVS R1, R0
    MOVS R0, R2
    MOVS R3, #10
    MULS R2, R3
    SUBS R1, R2
    POP {R4-R7, PC}

  
//-----------------------OutDec-----------------------
// Convert a 16-bit number into unsigned decimal format
// Call the function OutChar to output each character
// You will call OutChar 1 to 5 times
// OutChar does not do actual output, OutChar does virtual output used by the grader
// Input: R0 (call by value) 16-bit unsigned number
// Output: none
// Invariables: This function must not permanently modify registers R4 to R11
OutDec:
   PUSH {R1-R7, LR}
// write this
//R4 IN, R5 CMP
   MOVS R4, R0
   MOVS R5, #0
   ; CMP R0, #0
   ; BNE ODloop
   ; MOVS R0, #48
   ; BL OutChar
   ; B ODend
ODloop:
   MOVS R0, R4
   ODIloop:   
   CMP R0, R5
   BEQ break
   BL udivby10
   B ODIloop
   break:
   MOVS R2, #10
   MULS R5, R2
   ADDS R5, R1
   MOVS R0, R1
   ADDS R0, #48
   BL OutChar
   CMP R4, R5
   BEQ ODend
   B ODloop
ODend:
   POP  {R1-R7, PC}
// * * * * * * * * End of OutDec * * * * * * * *

// ECE319H recursive version
// Call the function OutChar to output each character
// You will call OutChar 1 to 5 times
// Input: R0 (call by value) 16-bit unsigned number
// Output: none
// Invariables: This function must not permanently modify registers R4 to R11

OutDec2:
   PUSH {LR}
// write this

   POP  {PC}



     .end
