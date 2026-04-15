/* ECE319K_Lab4main.c
 * Traffic light FSM
 * ECE319H students must use pointers for next state
 * ECE319K students can use indices or pointers for next state
 * Put your names here or look silly
  */

#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
#include "../inc/Clock.h"
#include "../inc/UART.h"
#include "../inc/Timer.h"
#include "../inc/Dump.h"  // student's Lab 3
#include <stdio.h>
#include <string.h>
// put your EID in the next line
const char EID1[] = "hc32869"; //  ;replace abc123 with your EID
// Hint implement Traffic_Out before creating the struct, make struct match your Traffic_Out
int light_state = 0;
int timer = 0;
int turn = 0;
int white = (1<<22)+(1<<26)+(1<<27);
uint32_t whyAreTheseNumbersRandom = 7+(7<<6)+(1<<22)+(1<<26)+(1<<27);
bool processing;
// initialize all 6 LED outputs and 3 switch inputs
// assumes LaunchPad_Init resets and powers A and B
void nextstate();
void Traffic_Init(void){ // assumes LaunchPad_Init resets and powers A and B
 // write this 
  GPIOB->DOE31_0 |=0x1C7;
  IOMUX->SECCFG.PINCM[PB15INDEX] = 0x40081;
  int* ptr = &IOMUX->SECCFG.PINCM[11];
  IOMUX->SECCFG.PINCM[32] = 0x40081;
  IOMUX->SECCFG.PINCM[42] = 0x40081;
  //
  IOMUX->SECCFG.PINCM[PB0INDEX] = 0x00081;
  IOMUX->SECCFG.PINCM[12] = 0x00081;
  IOMUX->SECCFG.PINCM[14] = 0x00081;
  IOMUX->SECCFG.PINCM[22] = 0x00081;
  IOMUX->SECCFG.PINCM[23] = 0x00081;
  IOMUX->SECCFG.PINCM[24] = 0x00081;
  IOMUX->SECCFG.PINCM[49] = 0x00081;
  IOMUX->SECCFG.PINCM[56] = 0x00081;

  IOMUX->SECCFG.PINCM[PB5INDEX] = 0x40081;
  GPIOB->DOUTSET31_0 = 1<<5;
}
struct state{
  uint32_t id;
  uint32_t west;
  uint32_t south;
  uint32_t walk;
  uint32_t check;
  uint32_t cd;
};

struct state states[10];
/* Activate LEDs
* Inputs: west is 3-bit value to three east/west LEDs
*         south is 3-bit value to three north/south LEDs
*         walk is 3-bit value to 3-color positive logic LED on PB22,PB26,PB27
* Output: none
* - west =1 sets west green
* - west =2 sets west yellow
* - west =4 sets west red
* - south =1 sets south green
* - south =2 sets south yellow
* - south =4 sets south red
* - walk=0 to turn off LED
* - walk bit 22 sets blue color
* - walk bit 26 sets red color
* - walk bit 27 sets green color
* Feel free to change this. But, if you change the way it works, change the test programs too
* Be friendly*/
void Traffic_Out(uint32_t west, uint32_t south, uint32_t walk){
  west = west<<6;
  uint32_t sum = west+south+walk;
  uint32_t sum1 = whyAreTheseNumbersRandom&(~sum);
  GPIOB->DOUTSET31_0 = sum;
  GPIOB->DOUTCLR31_0 = sum1;
}
/* Read sensors
 * Input: none
 * Output: sensor values
 * - bit 0 is west car sensor
 * - bit 1 is south car sensor
 * - bit 2 is walk people sensor
* Feel free to change this. But, if you change the way it works, change the test programs too
 */
uint32_t Traffic_In(void){
    uint32_t temp = GPIOB->DIN31_0;
    uint32_t* ptr = &GPIOB->DIN31_0;
    temp = temp>>15;
    temp&=7;
    return temp; // write this
}

void SysTick_Handler(){
  if(timer>-2)
  timer--;
}

void nextstate(){
  processing = true;
  if(light_state==4){
    while(timer>700){
      int tstate = 0;
      if((timer/50)%2 == 1&&tstate==0){
        Traffic_Out(4, 4, 1<<26);
        tstate = 1;
      }
      else if(tstate==1){
        Traffic_Out(4, 4, 0);
        tstate = 0;
      }
    }
    while(timer>600){
      Traffic_Out(4, 4, 1<<26);
    }
  }
  if(light_state==2){
    while(timer>800){
      Traffic_Out(4, 2, 1<<26);
    }
  }
  if(light_state==1){
    while(timer>800){
      Traffic_Out(2, 4, 1<<26);
    }
  }
  while(1){
    int temp = Traffic_In();
    if(temp==0){
      Traffic_Out(4,4,1<<26);
      continue;
    }
    light_state = light_state<<1;
    if(light_state==8) light_state=1;
    if(light_state&Traffic_In()){
      if(light_state==1){ Traffic_Out(1, 4, 1<<26);}
      if(light_state==2){ Traffic_Out(4, 1, 1<<26);}
      if(light_state==4){ Traffic_Out(4, 4, white);}
      timer = 1000;
      processing = false;
      break;
    }
  }  

}

void tmain(){
states[0].id = 0;
states[0].west = 4;
states[0].south = 4;
states[0].walk = 1<<26;
states[0].cd = 500;

states[1].id = 1;
states[1].west = 1;
states[1].south = 4;
states[1].walk = 1<<26;
states[1].cd = 1000;

states[3].id = 3;
states[3].west = 4;
states[3].south = 1;
states[3].walk = 1<<26;
states[3].cd = 1000;

states[5].id = 5;
states[5].west = 4;
states[5].south = 4;
states[5].walk = white;
states[5].cd = 1000;
//offset states
states[2].id = 2;
states[2].west = 2;
states[2].south = 4;
states[2].walk = 1<<26;
states[2].cd = 500;

states[4].id = 4;
states[4].west = 4;
states[4].south = 2;
states[4].walk = 1<<26;
states[4].cd = 500;

states[6].id = 6;
states[6].west = 4;
states[6].south = 4;
states[6].walk = 1<<26;
states[6].cd = 100;

states[7].id = 7;
states[7].west = 4;
states[7].south = 4;
states[7].walk = 0;
states[7].cd = 100;

states[8].id = 8;
states[8].west = 4;
states[8].south = 4;
states[8].walk = 1<<26;
states[8].cd = 100;

states[9].id = 9;
states[9].west = 4;
states[9].south = 4;
states[9].walk = 0;
states[9].cd = 100;
light_state = 0;
Traffic_Out(4, 4, 1<<26);
  while(1){
    uint32_t data = light_state;
    Debug_Dump2(data);
          // 1) output depending on state using Traffic_Out
      // call your Debug_Dump logging your state number and output
      // 2) wait depending on state
      // 3) hard code this so input always shows all switches pressed
      // 4) next depends on state and input
      if (timer<=0) {
        if(light_state>5){
          light_state++;
          light_state%=10;
        }
        else if(light_state==0){
          turn++; turn%=3;
          while(1){
            uint32_t temp = Traffic_In();
            if(temp&(1<<turn)) break;
            turn++;
            turn%=3;
          }
          light_state = 1+turn*2;          
        }
        else{
          if(light_state%2==0){ light_state=0;
          }
          else if(Traffic_In()-(1<<turn)!=0)light_state++;
        }
        timer = states[light_state].cd;
      }
      Traffic_Out(states[light_state].west, states[light_state].south, states[light_state].walk);
  }
}


// use main1 to determine Lab4 assignment
void Lab4Grader(int mode);
void Grader_Init(void);
int main1(void){ // main1
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Lab4Grader(0); // print assignment, no grading
  while(1){
  }
}
// use main2 to debug LED outputs
// at this point in ECE319K you need to be writing your own test functions
// modify this program so it tests your Traffic_Out  function
int main2(void){ // main2
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Grader_Init(); // execute this line before your code
  LaunchPad_LED1off();
  Traffic_Init(); // your Lab 4 initialization
  if((GPIOB->DOE31_0 & 0x20)==0){
    UART_OutString("access to GPIOB->DOE31_0 should be friendly.\n\r");
  }
  UART_Init();
  UART_OutString("Lab 4, Spring 2026, Step 1. Debug LEDs\n\r");
  UART_OutString("EID1= "); UART_OutString((char*)EID1); UART_OutString("\n\r");
  while(1){
    // write code to test your Traffic_Out
    if((GPIOB->DOUT31_0&0x20) == 0){
      UART_OutString("DOUT not friendly\n\r");
    }
  }
}
// use main3 to debug the three input switches
// at this point in ECE319K you need to be writing your own test functions
// modify this program so it tests your Traffic_In  function
int main3(void){ // main3
  uint32_t last=0,now;
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Traffic_Init(); // your Lab 4 initialization
  Debug_Init();   // Lab 3 debugging
  UART_Init();
  __enable_irq(); // UART uses interrupts
  UART_OutString("Lab 4, Spring 2026, Step 2. Debug switches\n\r");
  UART_OutString("EID1= "); UART_OutString((char*)EID1); UART_OutString("\n\r");
  while(1){
    now = Traffic_In(); // Your Lab4 input
    if(now != last){ // change
      UART_OutString("Switch= 0x"); UART_OutUHex(now); UART_OutString("\n\r");
      Debug_Dump(now);
    }
    last = now;
    Clock_Delay(800000); // 10ms, to debounce switch
  }
}
// use main4 to debug using your dump
// proving your machine cycles through all states
int main4(void){// main4
  Clock_Init80MHz(0);
  LaunchPad_Init();
  LaunchPad_LED1off();
  Traffic_Init(); // your Lab 4 initialization
 // set initial state
  Debug_Init();   // Lab 3 debugging
  UART_Init();
  __enable_irq(); // UART uses interrupts
  UART_OutString("Lab 4, Spring 2026, Step 3. Debug FSM cycle\n\r");
  UART_OutString("EID1= "); UART_OutString((char*)EID1); UART_OutString("\n\r");
// initialize your FSM
GPIOB->DOUT31_0|=4;
GPIOB->DOUT31_0&=0;
int* ptr = &GPIOB->DOUT31_0;
uint32_t input;
  SysTick_Init();   // Initialize SysTick for software waits
  SysTick->LOAD = 80000;
  SysTick->VAL = 0;
  
  while(1){
    tmain();
  }
}

// use main5 to grade
int main(void){// main5
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Grader_Init(); // execute this line before your code
  LaunchPad_LED1off();
  Traffic_Init(); // your Lab 4 initialization
// initialize your FSM
  SysTick_Init();   // Initialize SysTick for software waits
  // initialize your FSM
  Lab4Grader(1); // activate UART, grader and interrupts
uint32_t input;
  SysTick_Init();   // Initialize SysTick for software waits
  SysTick->LOAD = 80000;
  SysTick->VAL = 0;
  
  while(1){
    tmain();
  }
}


