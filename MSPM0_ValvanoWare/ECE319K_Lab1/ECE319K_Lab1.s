// ****************** ECE319K_Lab1.s ***************
// Your solution to Lab 1 in assembly code
// Author: Hailin Chen hc32869
// Last Modified: 1-25
// Spring 2026
        .data
        .align 2
// Declare global variables here if needed
// with the .space assembly directive

        .text
        .thumb
        .align 2
        .global EID
EID:    .string "HC32869" // replace ZZZ123 with your EID here

        .global Phase
        .align 2
Phase:  .long 10
// Phase= 0 will display your objective and some of the test cases, 
// Phase= 1 to 5 will run one test case (the ones you have been given)
// Phase= 6 to 7 will run one test case (the inputs you have not been given)
// Phase=10 will run the grader (all cases 1 to 7)
        .global Lab1
// Input: R0 points to the list
// Return: R0 as specified in Lab 1 assignment and terminal window
// According to AAPCS, you must save/restore R4-R7
// If your function calls another function, you must save/restore LR
Lab1: PUSH {R4-R7,LR}
       // your solution goes here
        movs R1, #0
        subs R1, R1, #1
        Loop1:
        adds R1, R1, #1
        ldr R2, =EID
        movs R6, #0
        ldr R3, [R0]
        cmp R3, #0
        beq end1
        adds R0, R0, #8
        ind_check:
        ldrb R4, [R3, R6]
        ldrb R5, [R2, R6]
        adds R6, R6, #1
        cmp R4, R5
        bne Loop1
        cmp R6, #7
        bne ind_check
        movs R0, R1
        b end
        end1:
        movs R0, #0
        subs R0, R0, #1
        end:

      POP  {R4-R7,PC} // return


        .align 2
        .global myClass
myClass: .long pAB123  // pointer to EID
         .long 95      // Score
         .long pXYZ1   // pointer to EID
         .long 96      // Score
         .long pAB5549 // pointer to EID
         .long 94      // Score
         .long 0       // null pointer means end of list
         .long 0
pAB123:  .string "AB123"
pXYZ1:   .string "XYZ1"
pAB5549: .string "AB5549"
        .end
