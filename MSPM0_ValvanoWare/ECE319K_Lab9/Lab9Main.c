// Lab9Main.c
// Runs on MSPM0G3507
// Lab 9 ECE319K
// Your name
// Last Modified: January 12, 2026

 #include <stdio.h>
 #include <stdint.h>
 #include <ti/devices/msp/msp.h>
 #include "../inc/ST7735.h"
 #include "../inc/Clock.h"
 #include "../inc/LaunchPad.h"
 #include "../inc/TExaS.h"
 #include "../inc/Timer.h"
 #include "../inc/ADC1.h"
 #include "../inc/DAC5.h"
 #include "../inc/Arabic.h"
 #include "SmallFont.h"
 #include "LED.h"
 #include "Switch.h"
 #include "Sound.h"
 #include "images/images.h"
 #include "UART1.h"
 #include "UART2.h"
 #include "FIFO1.h"
 #include "../inc/SPI.h"
 //#include "spi0.h"
// #include "UART1.h"
// #include "UART1.h"

// ****note to ECE319K students****
// the data sheet says the ADC does not work when clock is 80 MHz
// however, the ADC seems to work on my boards at 80 MHz
// I suggest you try 80MHz, but if it doesn't work, switch to 40MHz
void PLL_Init(void){ // set phase lock loop (PLL)
  // Clock_Init40MHz(); // run this line for 40MHz
  Clock_Init80MHz(0);   // run this line for 80MHz
}

Arabic_t ArabicAlphabet[]={
alif,ayh,baa,daad,daal,dhaa,dhaal,faa,ghayh,haa,ha,jeem,kaaf,khaa,laam,meem,noon,qaaf,raa,saad,seen,sheen,ta,thaa,twe,waaw,yaa,zaa,space,dot,null
};
Arabic_t Hello[]={alif,baa,ha,raa,meem,null}; // hello
Arabic_t WeAreHonoredByYourPresence[]={alif,noon,waaw,ta,faa,raa,sheen,null}; // we are honored by your presence
char engHonored[] = "We are honored by your presence";
// void state0(){
// }

// games  engine runs at 30Hz

uint8_t TExaS_LaunchPadLogicPB27PB26(void){
  return (0x80|((GPIOB->DOUT31_0>>26)&0x03));
}

typedef enum {English, Spanish, Portuguese, French} Language_t;
Language_t myLanguage=English;
typedef enum {HELLO, GOODBYE, LANGUAGE} phrase_t;
const char Hello_English[] ="Hello";
const char Hello_Spanish[] ="\xADHola!";
const char Hello_Portuguese[] = "Ol\xA0";
const char Hello_French[] ="All\x83";
const char Goodbye_English[]="Goodbye";
const char Goodbye_Spanish[]="Adi\xA2s";
const char Goodbye_Portuguese[] = "Tchau";
const char Goodbye_French[] = "Au revoir";
const char Language_English[]="English";
const char Language_Spanish[]="Espa\xA4ol";
const char Language_Portuguese[]="Portugu\x88s";
const char Language_French[]="Fran\x87" "ais";
const char *Phrases[3][4]={
  {Hello_English,Hello_Spanish,Hello_Portuguese,Hello_French},
  {Goodbye_English,Goodbye_Spanish,Goodbye_Portuguese,Goodbye_French},
  {Language_English,Language_Spanish,Language_Portuguese,Language_French}
};
//controls
uint8_t inputs = 0; 
// A1, B1, A2, B2, grounded1, double jump1, grounded2, double jump2
// bit 3       bit 0
uint8_t slidepot1 = 0;
//6bits
uint8_t slidepot2 = 0;
uint8_t swordPos1 = 0;
uint8_t swordPos2 = 0;
uint8_t joystick1 = 0; 
// bits 4-7 LR, bits 0-3 UD
uint8_t joystick2 = 0; 
uint8_t status1 = 0;
//0-1 hp, 2 tgl invincibility, 3-7 invincibility time
uint8_t status2 = 0;
//0-1 hp, 2 tgl invincibility
uint8_t dashCD1 = 0;
uint8_t dashCD2 = 0;

// current states
uint8_t OldSwPos[2];
int8_t oldPos[4];
int8_t positions[4];
int8_t velocity[4];
int8_t acceleration[4];
//x1, y1, x2, y2
void state0_init(void);
void state1_init(void);
void state2_init(void);
void state3_init();
void drawHearts();
void readData();
// ALL ST7735 OUTPUT MUST OCCUR IN MAIN
void main1(){
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf(INITR_BLACKTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
  ST7735_FillScreen(ST7735_BLACK);
  ADCinit();     //PB18 = ADC1 channel 5, slidepot
  Switch_Init(); // initialize switches
  LED_Init();    // initialize LED
  Sound_Init();  // initialize sound
  //TExaS_Init(0,0,&TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
  //state2_init();
  TimerG12_IntArm(80000000/30,2);
  UART1_Init();
  UART2_Init();
  SysTick_Init();
  __enable_irq();
  uint8_t results[5];
  while(1){
    for(int i = 0; i<5; i++){results[i] = 0;}
    UART1_OutChar(10);
    UART1_OutChar(11);
    UART1_OutChar(12);
    UART1_OutChar(13);
    UART1_OutChar(14);
    Clock_Delay1ms(1);
    results[0] = UART2_InChar();
    results[1] = UART2_InChar();
    results[2] = UART2_InChar();
    results[3] = UART2_InChar();
    results[4] = UART2_InChar();
  }
}
void main(){
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf(INITR_BLACKTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
  ST7735_FillScreen(ST7735_BLACK);
  ADCinit();     //PB18 = ADC1 channel 5, slidepot
  Switch_Init(); // initialize switches
  LED_Init();    // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(0,0,&TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
  state2_init();
  TimerG12_IntArm(80000000/30,2);
  __enable_irq();
}
int main10(void){ // final main
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf(INITR_BLACKTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
  ST7735_FillScreen(ST7735_BLACK);
  ADCinit();     //PB18 = ADC1 channel 5, slidepot
  Switch_Init(); // initialize switches
  LED_Init();    // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(0,0,&TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
    // initialize interrupts on TimerG12 at 30 Hz
  TimerG12_IntArm(80000000/30,2);
  // initialize all data structures

  __enable_irq();
  state0_init();
  while(1){
    // wait for semaphore
       // clear semaphore
       // update ST7735R
    // check for end game or level switch
  }
}
int state = 2;
int language = 0;
int dataReady = 1;

// language select
char Hell[] = "Hello";
int8_t min(int8_t a, int8_t b); 
int8_t max(int8_t a, int8_t b);
uint8_t umin(uint8_t a, uint8_t b); 
uint8_t umax(uint8_t a, uint8_t b);
void eraseOld();
void drawPlayers();
uint8_t makeSwords();
int8_t ypos(int8_t x, int8_t y, int8_t a, int8_t p);
void sendPos1();
void sendPos2();
void sendState();
uint8_t controls1 = 0;
uint8_t controls2 = 0;

void state0_init(void){
  ST7735_SetCursor(0,15);
  ST7735_OutString(Hell);
  Arabic_SetCursor(0,31);
  Arabic_OutString(Hello);
}
void state0(void){
  if(inputs&4){
    language++;
    language%=3;
  }
  if(inputs&8){
    state = 1;
    sendState();
    state1_init();
  }
}


void state1_init(void){
  UART1_OutChar(0xF1);
  ST7735_FillScreen(ST7735_BLACK);
  //logo
  ST7735_SetCursor(0,15);
}

void state1(void){
  if(inputs&4){
    state = 0; 
    sendState();
    state0_init();
  }
  if(inputs&8){
    state = 2;
    sendState();
    state2_init();
  }
}
int8_t bounds[] = {127, 127}; //change
void state2_init(void){
  UART1_OutChar(0xF2);
  ST7735_FillScreen(ST7735_BLACK);
  ST7735_FillRect(10, 110, 50, 10, 0xc487);
  ST7735_FillRect(70, 110, 50, 10, 0xc487);
  ST7735_FillRect(20, 75, 80, 10, 0xc487);
  ST7735_FillRect(0, 155, 128, 5, 0xc487);
  positions[0] = 30; positions[1] = 149;
  positions[2] = 42; positions[3] = 149;
  acceleration[1] = 2; acceleration[3] = 2;
  status1 = 3; status2 = 3;
  ST7735_DrawBitmap(positions[0], positions[1], player1, 11, 13);
  ST7735_DrawBitmap(positions[2], positions[3], player2, 11, 13);
  makeSwords();
  
}
void state2(){
  if(dataReady){
     eraseOld();
     drawPlayers();
     drawHearts();
    //  sendPos1();
    //  sendPos2();
     //AssignValues();
     makeSwords();
  }
  for(int i = 0; i<4; i++) oldPos[i] = positions[i];
  OldSwPos[0] = swordPos1;
  OldSwPos[1] = swordPos2;
  for(int i = 0; i<4; i++){
    if(i%2==0){
      positions[i]+=velocity[i];
      positions[i] = min(bounds[i%2], positions[i]);
      positions[i] = max(0, positions[i]);
    }
    else{
      uint8_t temp = positions[i];
      temp+=velocity[i];
      temp = umin(155, temp);
      //temp = umax(0, temp);
      positions[i] = temp;
    }
      velocity[i]+=acceleration[i];
  }
    if(velocity[1]>4) velocity[1] = 4;
    if(velocity[3]>4) velocity[3] = 4;
    if(acceleration[0]==0) velocity[0]/=2;
    if(acceleration[2]==0) velocity[2]/=2;
    if(~status1&4){
      if(velocity[0]<-3) velocity[0] = -3;//capping mobility
      if(velocity[0]>3) velocity[0] = 3;
    }
    if(~status2&4){
      if(velocity[2]<-3) velocity[2] = -3;//capping mobility
      if(velocity[2]>3) velocity[2] = 3;
    }
    positions[1] = ypos(positions[0], positions[1], velocity[1], 0);
    positions[3] = ypos(positions[2], positions[3], velocity[3], 1);
    if(!(status1&0xF8)) status1&=(~0x04);
    else status1-=8;
    if(!(status2&0xF8)) status2&=(~0x04);
    else status2-=8;
    if(swordPos1<slidepot1) swordPos1 = umax(swordPos1+3, slidepot1);
    if(swordPos1>slidepot1) swordPos1 = umin(swordPos1-3, slidepot1);
    if(swordPos2<slidepot2) swordPos2 = umax(swordPos2+3, slidepot2);
    if(swordPos2>slidepot2) swordPos2 = umin(swordPos2-3, slidepot2);
    if(dashCD1!=0) dashCD1--;
    if(dashCD2!=0) dashCD2--;
    readData();
}
void drawHearts(){
  int8_t health1 = status1&3;
  int8_t health2 = status2&3;
  if(health1==0){ state++;return; }
  if(health2==0) {
  state++; 
  return;}
  ST7735_FillRect(5, 5, 30, 8, 0x0000);
  ST7735_FillRect(98, 5, 30, 8, 0x0000);
  if(health1>2) ST7735_DrawBitmap(5, 10, heart, 5, 5);
  if(health1>1) ST7735_DrawBitmap(15, 10, heart, 5, 5);
  if(health1>0) ST7735_DrawBitmap(25, 10, heart, 5, 5); 
  if(health2>2) ST7735_DrawBitmap(118, 10, heart, 5, 5);
  if(health2>1) ST7735_DrawBitmap(108, 10, heart, 5, 5);
  if(health2>0) ST7735_DrawBitmap(98, 10, heart, 5, 5);  
}
int8_t min(int8_t a, int8_t b){
  if(a>b) return b;
  return a;
}
int8_t max(int8_t a, int8_t b){
  if(a>b) return a;
  return b;
}
uint8_t umin(uint8_t a, uint8_t b){
  if(a>b) return b;
  return a;
}
uint8_t umax(uint8_t a, uint8_t b){
  if(a>b) return a;
  return b;
}
int8_t pointsy[] = {12, 11, 11, 11, 10, 10, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -9, -10, -10, -11, -11, -11};
int8_t pointsx[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 11, 11, 11, 11, 12, 11, 11, 11, 11, 10, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
void eraseOldSwords(){
  for(int j = 0; j<2; j++){
    int val = OldSwPos[j]%32;
    int16_t x_offset = pointsx[val];
    int16_t y_offset = pointsy[val];

    if(OldSwPos[j]>31){
      x_offset*=-1; y_offset*=-1;
      }
    int16_t xloff = 0, yloff = 0;
    uint8_t startx = oldPos[0+j*2]+6;
    uint8_t starty = oldPos[1+j*2]-2;
    ST7735_DrawPixel(startx, starty, 0x0000);
    uint16_t lastx = 0;
    uint16_t lasty = 0;
    for(int i = 0; i<16; i++){
      xloff+=x_offset;
      yloff+=y_offset;
      uint16_t tempx = xloff>>4;
      uint16_t tempy = yloff>>4;
      if(tempx!=lastx||tempy!=lasty){
        ST7735_DrawPixel(tempx+startx, tempy+starty, 0x0000);
      }
    }
  }
}
void eraseOld(){
  ST7735_FillRect(oldPos[0], (uint8_t)oldPos[1]-13, 11, 13, 0x0000);
  ST7735_FillRect(oldPos[2], (uint8_t)oldPos[3]-13, 11, 13, 0x0000);
  eraseOldSwords();
  //make environment back
  ST7735_FillRect(10, 110, 50, 10, 0xc487);
  ST7735_FillRect(70, 110, 50, 10, 0xc487);
  ST7735_FillRect(20, 75, 80, 10, 0xc487);
  ST7735_FillRect(0, 155, 128, 5, 0xc487);
}
uint8_t makeSwords(){
  uint8_t hits = 0;
  int val = swordPos1%32;
  int16_t x_offset = pointsx[val];
  int16_t y_offset = pointsy[val];

  if(swordPos1>31){
    x_offset*=-1; y_offset*=-1;
    }
  int16_t xloff = 0, yloff = 0;
  uint8_t startx = positions[0]+6;
  uint8_t starty = positions[1]-2;
  ST7735_DrawPixel(startx, starty, 0xFFFF);
  uint16_t lastx = 0;
  uint16_t lasty = 0;
  uint8_t yval = positions[3];
  for(int i = 0; i<16; i++){
    xloff+=x_offset;
    yloff+=y_offset;
    uint16_t tempx = xloff>>4;
    uint16_t tempy = yloff>>4;
    if(tempx!=lastx||tempy!=lasty){
      uint16_t val1 = tempx+startx;
      uint16_t val2 = tempy+starty;
      ST7735_DrawPixel(tempx+startx, tempy+starty, 0xFFFF);
      bool a  = tempx+startx>=positions[2]&&tempx+startx<=positions[2]+11;
      bool b = val2<=yval;
      bool c = val2>=(yval-13);
      if(a&&b&&c) hits = 1;
    }
  }
  val = swordPos2%32;
  x_offset = pointsx[val];
  y_offset = pointsy[val];
  if(swordPos2>31){
    x_offset*=-1; y_offset*=-1;
    }
  xloff = 0, yloff = 0;
  startx = positions[2]+6;
  starty = positions[3]-2;
  ST7735_DrawPixel(startx, starty, 0xFFFF);
  lastx = 0;
  lasty = 0;
  yval = positions[1];
  for(int i = 0; i<16; i++){
    xloff+=x_offset;
    yloff+=y_offset;
    uint16_t tempx = xloff>>4;
    uint16_t tempy = yloff>>4;
    if(tempx!=lastx||tempy!=lasty){
      uint16_t val1 = tempx+startx;
      uint16_t val2 = tempy+starty;
      ST7735_DrawPixel(tempx+startx, tempy+starty, 0xFFFF);
      bool a  = tempx+startx>=positions[0]&&tempx+startx<=positions[0]+11;
      bool b = val2<=yval;
      bool c = val2>=(yval-13);
      if(a&&b&&c) hits|=2;
    }
  }
  if((~status1&4)&&(hits&2)){
    status1+=4;
    status1+=8*8;
    status1--;
    if(positions[0]>positions[2]) velocity[0] =10;
    else velocity[0] = -10;
  }
  if((~status2&4)&&(hits&1)){
    status2+=4;
    status2+=8*8;
    status2--;
    if(positions[2]>positions[0]) velocity[2] =10;
    else velocity[2] = -10;
  }
}
void drawPlayers(){
  if(status1&4) ST7735_DrawBitmap(positions[0], (uint8_t)positions[1], player1i, 11, 13);
  else ST7735_DrawBitmap(positions[0], (uint8_t)positions[1], player1, 11, 13);
  if(status2&4) ST7735_DrawBitmap(positions[2], (uint8_t)positions[3], player2i, 11, 13);
  else ST7735_DrawBitmap(positions[2], (uint8_t)positions[3], player2, 11, 13);
}
//finding collisions with 
int8_t ypos(int8_t x, int8_t y, int8_t a, int8_t p){
  uint8_t ret = (uint8_t)y;
  uint8_t hit = 0;
  uint8_t temp = y-155;
  if(temp<=0){ ret = 155; hit++;}
  if(x>5&&x<55&&(uint8_t)y>=110&&(uint8_t)y-a<=110){ ret = 110; hit++;}
  if(x>65&&x<115&&(uint8_t)y>=110&&(uint8_t)y-a<=110) {ret = 110; hit++;}
  if(x>15&&x<95&&(uint8_t)y>=75&&(uint8_t)y-a<=75) {ret = 75; hit++;}
  if(hit){
    velocity[p*2+1] = 0;
    if(p==0)
    inputs|= 3<<4;
  else inputs|=3<<6;
  }
  else{
    uint8_t  c = 0;
  } 
  return ret;
}

uint32_t oldInput = 0;
void readData(){
   slidepot1 = ADCin()>>6;//sword position

   uint32_t Input = GPIOB->DIN31_0;
    // if(Input&1<<12){acceleration[0] = 1;}//move right
    // else acceleration[0] = 0;
   if(Input&1<<16){
    if(!dashCD1){
      if (velocity[0]>=0) {
        velocity[0] = 10;
      }
      else velocity[0] = -10;
      status1|=4;
      status1&=7;
      status1+=8*5;
      dashCD1 = 0xA;
    }
   }
   if(Input&1<<12&&!(oldInput&1<<12)){//jump
     if(inputs&16){
       velocity[1] = -12;
       inputs&=(~16);
     }
     else if (inputs&32) {
       velocity[1] = -8;
       inputs&=(~32);
     }
     }//change
    oldInput = Input;
    while(Fifo_size()>=12){
      while(true){
        uint8_t val = UART2_InChar();
        uint8_t val2 = UART2_InChar();
        if(val==0xF0&&val2==0xFF) break;
      }
      slidepot2 = UART2_InChar();
      swordPos1 = UART2_InChar();
      status1 = UART2_InChar();
      positions[0] = UART2_InChar();
      positions[1] = UART2_InChar();
      positions[2] = UART2_InChar();
      positions[3] = UART2_InChar();
      controls2 = UART2_InChar();
      status2 = UART2_InChar();
      swordPos2 = UART2_InChar();
      break;
    }
  

}
void sendState(){
  UART_OutChar(0xFC+state);
}

void state3_init(){
  UART1_OutChar(0xF3);
  UART1_OutChar(status1);
  UART1_OutChar(status2);
}
void state3(){
  ST7735_FillScreen(0x0000);

}
uint8_t UARTFrame = 0;
void TIMG12_IRQHandler(void){
   if(state==0) state0();
   if(state==1) state1();
   if(state==2){
      if(UARTFrame==0)
      state2();
      if(UARTFrame==1){
        UART1_OutChar(0xF0);
        UART1_OutChar(0xFF);
        UART1_OutChar(slidepot1);
        UART1_OutChar(swordPos1);
      }
      if(UARTFrame==2){
        UART1_OutChar(status1);
        UART1_OutChar(positions[0]);
        UART1_OutChar(positions[1]);
        UART1_OutChar(positions[2]);
      }
      if(UARTFrame==3){
        UART1_OutChar(positions[3]);
        UART1_OutChar(controls1);
        UART1_OutChar(status2);
        UART1_OutChar(swordPos2);
      }
      
      UARTFrame++;
      UARTFrame%=4;
   } 
   if(state==3) state3();
}