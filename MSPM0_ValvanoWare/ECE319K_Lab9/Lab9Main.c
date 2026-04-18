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

int main0(void){ // main 0, demonstrate Arabic output
  __disable_irq();
  Clock_Init80MHz(0);
  LaunchPad_Init();
  ST7735_InitR(INITR_REDTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
  ST7735_FillScreen(ST7735_WHITE);
  Arabic_SetCursor(0,15);
  Arabic_OutString(Hello);
  Arabic_SetCursor(0,31);
  Arabic_OutString(WeAreHonoredByYourPresence);
  Arabic_SetCursor(0,63);
  Arabic_OutString(ArabicAlphabet);
  while(1){
    
  }
}

// void state0(){
// }
uint32_t M=1;
uint32_t Random32(void){
  M = 1664525*M+1013904223;
  return M;
}
uint32_t Random(uint32_t n){
  return (Random32()>>16)%n;
}


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
// use main1 to observe special characters
int main1(void){ // main1
    char l;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf(INITR_REDTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
  ST7735_FillScreen(0x0000);            // set screen to black
  for(phrase_t myPhrase=HELLO; myPhrase<= GOODBYE; myPhrase++){
    for(Language_t myL=English; myL<= French; myL++){
         ST7735_OutString((char *)Phrases[LANGUAGE][myL]);
      ST7735_OutChar(' ');
         ST7735_OutString((char *)Phrases[myPhrase][myL]);
      ST7735_OutChar(13);
    }
  }
  Clock_Delay1ms(3000);
  ST7735_FillScreen(0x0000);       // set screen to black
  l = 128;
  while(1){
    Clock_Delay1ms(2000);
    for(int j=0; j < 3; j++){
      for(int i=0;i<16;i++){
        ST7735_SetCursor(7*j+0,i);
        ST7735_OutUDec(l);
        ST7735_OutChar(' ');
        ST7735_OutChar(' ');
        ST7735_SetCursor(7*j+4,i);
        ST7735_OutChar(l);
        l++;
      }
    }
  }
}

// use main2 to observe graphics
int main(void){ // main2
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf(INITR_REDTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
    //note: if you colors are weird, see different options for
    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  ST7735_FillScreen(ST7735_BLACK);
  ST7735_DrawBitmap(22, 159, PlayerShip0, 18,8); // player ship bottom
  ST7735_DrawBitmap(53, 151, Bunker, 18,5);
  ST7735_DrawBitmap(42, 159, PlayerShip1, 18,8); // player ship bottom
  ST7735_DrawBitmap(62, 159, PlayerShip2, 18,8); // player ship bottom
  ST7735_DrawBitmap(82, 159, PlayerShip3, 18,8); // player ship bottom
  //ST7735_DrawBitmap(0, 9, SmallEnemy10pointA, 16,10);
  // ST7735_DrawBitmap(20,9, SmallEnemy10pointB, 16,10);
  // ST7735_DrawBitmap(40, 9, SmallEnemy20pointA, 16,10);
  // ST7735_DrawBitmap(60, 9, SmallEnemy20pointB, 16,10);
  // ST7735_DrawBitmap(80, 9, SmallEnemy30pointA, 16,10);
  ST7735_DrawBitmap(62, 159, player1, 11,13);
  ST7735_DrawBitmap(82, 159, player2, 11,13);

  for(uint32_t t=500;t>0;t=t-5){
    SmallFont_OutVertical(t,104,6); // top left
    Clock_Delay1ms(50);              // delay 50 msec
  }
  ST7735_FillScreen(0x0000);   // set screen to black
  ST7735_SetCursor(1, 1);
  ST7735_OutString("GAME OVER");
  ST7735_SetCursor(1, 2);
  ST7735_OutString("Nice try,");
  ST7735_SetCursor(1, 3);
  ST7735_OutString("Earthling!");
  ST7735_SetCursor(2, 4);
  ST7735_OutUDec(1234);
  while(1){
  }
}

// use main3 to test switches and LEDs
int main3(void){ // main3
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  while(1){
    // write code to test switches and LEDs
    
  }
}
// use main4 to test sound outputs
int main4(void){ uint32_t last=0,now;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(ADC0,6,0); // ADC1 channel 6 is PB20, TExaS scope
  __enable_irq();
  while(1){
    now = Switch_In(); // one of your buttons
    if((last == 0)&&(now == 1)){
      Sound_Shoot(); // call one of your sounds
    }
    if((last == 0)&&(now == 2)){
      Sound_Killed(); // call one of your sounds
    }
    if((last == 0)&&(now == 4)){
      Sound_Explosion(); // call one of your sounds
    }
    if((last == 0)&&(now == 8)){
      Sound_Fastinvader1(); // call one of your sounds
    }
    // modify this to test all your sounds
  }
}
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

// current states
int8_t oldPos[4];
int8_t positions[4];
int8_t velocity[4];
int8_t acceleration[4];
//x1, y1, x2, y2
void state0_init(void);
void state1_init(void);
void state2_init(void);
void readData();
// ALL ST7735 OUTPUT MUST OCCUR IN MAIN
void main12(){
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
void eraseOld();
uint8_t makeSwords();
int8_t ypos(int8_t x, int8_t y, int8_t a, int8_t p);
void sendPos1();
void sendPos2();
void sendState();

void state0_init(void){
  ST7735_SetCursor(0,15);
  ST7735_OutString(Hell);
  Arabic_SetCursor(0,31);
  Arabic_OutString(Hello);
}
void state0(void){
  if(inputs&&4){
    language++;
    language%=3;
  }
  if(inputs&&8){
    state = 1;
    sendState();
    state1_init();
  }
}


void state1_init(void){
  ST7735_FillScreen(ST7735_BLACK);
  //logo
  ST7735_SetCursor(0,15);
}

void state1(void){
  if(inputs&&4){
    state = 0; 
    sendState();
    state0_init();
  }
  if(inputs&&8){
    state = 2;
    sendState();
    state2_init();
  }
}
int8_t bounds[] = {128, 160}; //change
void state2_init(void){
  ST7735_FillScreen(ST7735_BLACK);
  //draw platforms
  ST7735_FillRect(10, 100, 50, 10, 0xc487);
  ST7735_FillRect(80, 100, 50, 10, 0xc487);
}
void state2(){
  for(int i = 0; i<3; i++){
      positions[i]+=velocity[i];
      positions[i] = min(bounds[i%2], positions[i]);
      positions[i] = max(0, positions[i]);
      velocity[i]+=acceleration[i];
      }
    if(velocity[0]<-3) velocity[0] = -3;//capping x mobility
    if(velocity[0]>3) velocity[0] = 3;
    if(velocity[2]<-3) velocity[2] = -3;//capping x mobility
    if(velocity[2]>3) velocity[2] = 3;
    if(acceleration[0]==0) velocity[0]/=2;
    if(acceleration[2]==0) velocity[2]/=2;
    positions[1] = ypos(positions[0], positions[1], acceleration[1], 0);
    positions[3] = ypos(positions[2], positions[3], acceleration[3], 1);
    if(swordPos1<slidepot1) swordPos1 = max(swordPos1+20, slidepot1);
    if(swordPos1>slidepot1) swordPos1 = min(swordPos1-20, slidepot1);
    if(swordPos2<slidepot2) swordPos2 = max(swordPos2+20, slidepot2);
    if(swordPos2>slidepot2) swordPos2 = min(swordPos2-20, slidepot2);
  if(dataReady){
     readData();
     eraseOld();
     sendPos1();
     sendPos2();
     //AssignValues();
     makeSwords();
  }
}
int8_t min(int8_t a, int8_t b){
  if(a>b) return b;
  return a;
}
int8_t max(int8_t a, int8_t b){
  if(a>b) return a;
  return b;
}
void eraseOld(){
  ST7735_FillRect(oldPos[0], oldPos[1], oldPos[0]+11, oldPos[1]+13, 0xFFFF);
  ST7735_FillRect(oldPos[2], oldPos[3], oldPos[2]+11, oldPos[3]+13, 0xFFFF);
  //make environment back
  ST7735_DrawBitmap(positions[0], positions[1], player1, 11,13);
  ST7735_DrawBitmap(positions[0], positions[1], player2, 11,13);
}
int8_t pointsy[] = {12, 11, 11, 11, 10, 10, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -9, -10, -10, -11, -11, -11};
int8_t pointsx[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 11, 11, 11, 11, 12, 11, 11, 11, 11, 10, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
uint8_t makeSwords(){
  uint8_t hits = 0;
  int val = slidepot1%32;
  int16_t x_offset = pointsx[val];
  int16_t y_offset = pointsy[val];

  if(slidepot1>31){
    x_offset*=-1; y_offset*=-1;
    }
  int16_t xloff = 0, yloff = 0;
  uint8_t startx = positions[0]+6;
  uint8_t starty = positions[1]+7;
  ST7735_DrawPixel(startx, starty, 0xFFFF);
  uint16_t lastx = 0;
  uint16_t lasty = 0;
  for(int i = 0; i<16; i++){
    xloff+=x_offset;
    yloff+=y_offset;
    uint16_t tempx = xloff>>4;
    uint16_t tempy = yloff>>4;
    if(tempx!=lastx||tempy!=lasty){
      ST7735_DrawPixel(tempx, tempy, 0xFFFF);
      if(tempx>=positions[2]&&tempy<=positions[2]+11&&tempy>=positions[3]&&tempy<=positions[3]+13) hits++;
    }
  }
  val = slidepot2%32;
  x_offset = pointsx[val];
  y_offset = pointsy[val];
  xloff = 0, yloff = 0;
  startx = positions[2]+6;
  starty = positions[3]+7;
  ST7735_DrawPixel(startx, starty, 0xFFFF);
  lastx = 0;
  lasty = 0;
  for(int i = 0; i<16; i++){
    xloff+=x_offset;
    yloff+=y_offset;
    uint16_t tempx = xloff>>4;
    uint16_t tempy = yloff>>4;
    if(tempx!=lastx||tempy!=lasty){
      ST7735_DrawPixel(tempx, tempy, 0xFFFF);
      if(tempx>=positions[0]&&tempy<=positions[0]+11&&tempy>=positions[1]&&tempy<=positions[1]+13) hits+=2;
    }
  }
  if(!status1&4&&hits&2){
    status1+=8*8;
    status1--;
    if(positions[0]>positions[2]) velocity[0] =10;
    else velocity[0] = -10;
  }
  if(!status2&4&&hits&1){
    status2+=8*8;
    status2--;
    if(positions[2]>positions[0]) velocity[2] =10;
    else velocity[2] = -10;
  }
}
//finding collisions with 
int8_t ypos(int8_t x, int8_t y, int8_t a, int8_t p){
  int8_t ans = 0;
  return ans;
}
void sendPos1(){
  UART1_OutChar(0xF0+(status1&0xF));
  UART1_OutChar(swordPos1);
  UART1_OutChar(positions[0]);
  UART1_OutChar(positions[1]);
}
void sendPos2(){
  UART1_OutChar(0xC0+(status2&0xF));
  UART1_OutChar(swordPos2);
  UART1_OutChar(positions[2]);
  UART1_OutChar(positions[3]);
}
void readData(){
   slidepot1 = ADCin()>>4;
   uint32_t Input = GPIOB->DIN31_0;
   if(Input&0x8){acceleration[0] = 1;}//change
   if(Input&0x8){acceleration[0] = -1;}//change

  
  

}
void sendState(){
  UART_OutChar(0xFC+state);
}




void TIMG12_IRQHandler(void){

  if(state==0) state0();
  if(state==1) state1();
  if(state==2) state2();
}