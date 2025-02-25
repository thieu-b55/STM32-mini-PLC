/*
* MIT License
*
* Copyright (c) 2025 thieu-b55
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

If the touch screen response is poor, change this line

Librarie XPT2046_Touchscreen_master

file   : XPT2046_Touchscreen.cpp
line   : 25

change : #define Z_THRESHOLD     300   >>>   #define Z_THRESHOLD     200   

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

#include <SPI.h>
#include <TFT_eSPI.h>
#include <FlashStorage_STM32.h>
#include "STM32TimerInterrupt.h"
#include <XPT2046_Touchscreen.h>

#define CAL_VAL           0x7777

#define MAX_LINE          1000
#define MAX_INST          20

#define RESOLUTION        9

#define INPUT_MODULE_0    PB0
#define INPUT_MODULE_1    PB1
#define INPUT_MODULE_2    PB9
#define INPUT_MODULE_3    PB8

#define OUTPUT_MODULE_0   PB7
#define OUTPUT_MODULE_1   PC13
#define OUTPUT_MODULE_2   PE1
#define OUTPUT_MODULE_3   PE2

#define TFT_MOSI          PB15
#define TFT_MISO          PB14
#define TFT_SCLK          PB13
#define TFT_CS            PB12 
#define TFT_DC            PB11 
#define TFT_RST           PB10 

#define TFT_TOUCH_MOSI    PB5
#define TFT_TOUCH_MISO    PB4
#define TFT_TOUCH_SCLK    PB3
#define TFT_TOUCH_CS      PA4
#define TFT_TOUCH_INT     PA5  

#define PWM_0_UIT         PA8
#define PWM_1_UIT         PA15
#define PWM_2_UIT         PA6
#define PWM_3_UIT         PB6

#define ADC_CH_0          PA0
#define ADC_CH_1          PA1
#define ADC_CH_2          PA2
#define ADC_CH_3          PA3

#define IN_0              PC0
#define IN_1              PC1
#define IN_2              PC2
#define IN_3              PC3
#define IN_4              PC4
#define IN_5              PC5
#define IN_6              PC6
#define IN_7              PC7
#define IN_8              PE8
#define IN_9              PE9
#define IN_10             PE10
#define IN_11             PE11
#define IN_12             PE12
#define IN_13             PE13
#define IN_14             PE14
#define IN_15             PE15

#define UIT_0             PD0
#define UIT_1             PD1
#define UIT_2             PD2
#define UIT_3             PD3
#define UIT_4             PD4
#define UIT_5             PD5
#define UIT_6             PD6
#define UIT_7             PD7
#define UIT_8             PD8
#define UIT_9             PD9
#define UIT_10            PD10
#define UIT_11            PD11
#define UIT_12            PD12
#define UIT_13            PD13
#define UIT_14            PD14
#define UIT_15            PD15

#define KEYB_R_0          PC8
#define KEYB_R_1          PC9
#define KEYB_R_2          PC10
#define KEYB_R_3          PC11
#define KEYB_R_4          PC12
#define KEYB_C_0          PE4
#define KEYB_C_1          PE5
#define KEYB_C_2          PE6
#define KEYB_C_3          PE7

#define BLINK             PE0

#define PROG_RUN          PA7     //0 = programmeren    1 = run

#define F1                10
#define LINKS             11
#define F2                12
#define HEKJE             13
#define RECHTS            14
#define STERRETJE         15
#define OP                16
#define NEER              17
#define ESC               18
#define ENT               19

#define IN                200
#define OUT               201
#define MERKER            202
#define TMR               203
#define CTRU              204
#define CTRD              205
#define AND               206
#define OR                207
#define XOR               208
#define OPEN              209
#define CLOSE             210
#define RISE              211
#define FALL              212
#define NOT               213
#define EQUALS            214
#define SET               215
#define RST               216
#define TMR_R             217
#define CTR_R             218
#define PWM               219
#define PWM_F             220
#define AI_E              221
#define AI_G              222
#define AI_L              223
#define AI_G_L            224
#define LEFT              225
#define RIGHT             226
#define INS_C             227
#define DEL_C             228
#define NEW               229
#define TOP               230
#define UP                231
#define DOWN              232
#define INS               233
#define DEL               234

void TimerHandler0();
void touch_int();
void touch_calibrate();
void touch();
void calibrate_test();
void programma_array_reset();
void keuzemenu();        
void keyboard_scan();
void key_detect();
void no_key_detect();
void programmeerscherm();
void bereken_programma_lijn_positie_int();
void toon_programma_lijn();
void print_lijnnummer();
void print_edit_lijn();
void lijn_controle();
void bereken_programma_lengte();
void print_error_test();
void printf_5_int(int freq_int);
void plaats_ster_pwm();
void ai_onderlijn();
void links_freq(int, int);
void links_ai();
void printf_4_int(int waarde_int);
void printf_3_int(int waarde_int);
void printf_2_int(int waarde_int);
void printf_6_int(int waarde_int);
void print_tmr_pag();
void plaats_ster_tmr();
void print_ctr_pag();
void plaats_ster_ctr();
void onderlijn();
void bereken_tijd(int x);
void bereken_tienden();
void tijd_naar_array();
void array_naar_tijd();
void links_uren();
void links_minuten();
void links_seconden();
void links_hondersten();
void shift_left_ctr();
void flash_keuzemenu();
void int_to_bytes(int);
int bytes_to_int();
void schrijf_instellingen();
void schrijf_programma();
void lees_instellingen();
void lees_programma();
void print_in_out();
void plaats_ster_in_out();
void print_adres();
void lees_input();
void lees_naar_input_array(int);
void lees_ai();
void schrijf_output();
void nu_naar_vorig();
void schrijf_van_output_array(int);
void freq_array_reset();
void ai_array_reset();
void tmr_ctr_instelling_reset();
void status_array_reset();
void tmr_ctr_reset();
void totaal_reset();
void schrijf_output_nul();
void buffer_array_links();

volatile bool cyclus_start_bool = false;
bool touch_bool = false;
bool blink_bool = false;
bool touched_bool = false;
bool calibrated_bool = false;
bool in_out_gekozen_bool = false;
bool keuze_bool = true;
bool programmeren_bool = false;
bool program_error_bool = false;
bool veranderd_bool = false;
bool max_bool;
bool o_c_error_bool = false;
bool pwm_instellen_bool = false;
bool cursor_positie_bool;
bool tmr_instellen_bool = false;
bool ctr_instellen_bool = false;
bool ctru_vorig_bool[64];
bool ctrd_vorig_bool[64];
bool print_flash_adres_bool = true;
bool prog_flash_bool = false;
bool flash_keuze_bool = false;
bool flash_schrijven_bool = false;
bool flash_lezen_bool = false;
bool programma_printen_bool = false;
bool programma_wissen_bool = false;
bool aantal_in_out_kiezen_bool = false;
bool edit_bool = false;
bool error_array_bool[25];
bool o_c_array_bool[25];
bool tmr_status_bool[64];
bool ctr_status_bool[64];
bool status_array_bool[6][64];   // [0] = IN   [1] = OUT   [2] = MERKER   [3] = TMR   [4] = CTRU   [5] = CTRD
bool status_array_vorig_bool[6][64];
bool not_bool = false;
bool rise_fall_bool = false;
bool haakjes_bool;

char print_char[20];

int commando_coord_int[35][2] = {{5, 130},
                                 {109, 130},
                                 {161, 130},
                                 {213, 130},
                                 {265, 130},
                                 {317, 130},
                                 {5, 170},
                                 {57, 170},
                                 {109, 170},
                                 {161, 170},
                                 {213, 170},
                                 {5, 210},
                                 {57, 210},
                                 {109, 210},
                                 {213, 210},
                                 {265, 210},
                                 {317, 210},
                                 {5, 250},
                                 {57, 250},
                                 {5, 290},
                                 {57, 290},
                                 {161, 290},
                                 {213, 290},
                                 {265, 290},
                                 {317, 290},
                                 {5, 90},
                                 {57, 90},
                                 {109, 90},
                                 {161, 90},
                                 {430, 90},
                                 {430, 130},
                                 {430, 170},
                                 {430, 210},
                                 {430, 250},
                                 {430, 290}};

int key_naar_int[20] = {10, 1, 4, 7, 11, 12, 2, 5, 8, 0, 13, 3, 6, 9, 14, 15, 16, 17, 18, 19};
int keuzemenu_hor_int[8] = {70, 100, 130, 160, 190, 220, 250, 280};

int pwm_hor_int[8][2] = {{35, 75},
                         {35, 100},
                         {35, 125},
                         {35, 150},
                         {35, 200},
                         {35, 225},
                         {35, 250},
                         {35, 275}};

int tmr_ctr_coor_int[2][4] = {{0, 50, 0, 50},
                              {429, 479, 0, 50}};

int tmr_ctr_hor_int[16][2] = {{35, 75},
                              {35, 100},
                              {35, 125},
                              {35, 150},
                              {35, 175},
                              {35, 200},
                              {35, 225},
                              {35, 250},
                              {250, 75},
                              {250, 100},
                              {250, 125},
                              {250, 150},
                              {250, 175},
                              {250, 200},
                              {250, 225},
                              {250, 250}};

int in_out_hor_int[3][2] = {{35, 125},
                            {35, 150},
                            {35, 200}};

int cyclustijd_int = 100000;  // tijd in microseconden;
int timer_int;
int x_positie_int;
int x_positie_vorig_int;
int eeprom_adres_int;
int eeprom_adres_hex;
int aantal_input_int = 16;
int aantal_output_int = 16;
int in_out_instellen_int = 0;
int tmr_ctr_pag_int = 0;
int pag_keuze_int = 0;
int tmr_instelling_int[64];
int tmr_nu_int[64];
int ctr_instelling_int[64];
int ctr_nu_int[64];
int ctr_int[4];
int uren_array[2];
int minuten_array[2];
int seconden_array[2];
int hondersten_array[2];
int freq_array_int[4] = {1, 1, 1, 1};
int ai_in_int[4];
int ai_array_int[4][2];    //[0] lage waarde (ai = 0) [1] hoge waarde bij (ai = pow(2, RESOLUTION))
int duty_cycle_array_int[4] = {0, 0, 0, 0};
int duty_cycle_array_temp_int[4] = {0, 0, 0, 0};
int duty_cycle_array_vorig_int[4] = {0, 0, 0, 0};
int keuzemenu_pos_int = 0;
int key_int = 0;
int rij_int = 0;
int programma_lengte_int;
int commando_int;
int commando_plus_int;
int commando_plus_2_int;
int commando_min_1_int;
int commando_min_2_int;
int commando_min_3_int;
int commando_min_4_int;
int pwm_positie_int;
int ai_positie_int;
int commando_saved_int;
int commando_saved_min_1_int;
int commando_saved_min_2_int;
int commando_saved_min_3_int;
int pwm_instellen_int = 0;
int ctr_instellen_int = 0;
int tmr_instellen_int = 0;
int flash_keuze_int;
int low_byte;
int middle_byte;
int high_byte;
int beschikbaar_flash_geheugen_int;
int uren_int;
int minuten_int;
int seconden_int;
int tienden_int;
int hondersten_int;
int tijd_instellen_int = 0;
int x_0_int;
int y_0_int;
int x_touch_int;
int y_touch_int;
int programma_lijn_int;
int programma_lijn_max_int = 0;  
int programma_lijn_positie_int;
int hulp_lijn_positie_int;
int commando_teller_int;
int edit_lijn_positie_int;
int edit_lijn_positie_vorig_int;
int lengte_int;
int pixel_positie_int[MAX_INST + 1];
int programma_array_int[MAX_LINE + 1][MAX_INST + 1];
int open_teller_int;
int close_teller_int;
int buffer_teller_int;
int buffer_array_int[30];
int open_array_int[MAX_LINE + 1];
int open_temp_int;
int open_positie_int;
int pow_int;

float x_factor_float;
float y_factor_float;

long start_micros_long;

String commando_string[35] = {{"IN"},
                              {"OUT"},
                              {"M"},
                              {"TMR"},
                              {"CTRU"},
                              {"CTRD"},
                              {"&&"},
                              {"||"},
                              {"^"},
                              {"("},
                              {")"},
                              {"/\\"},
                              {"\\/"},
                              {"!"},
                              {" = "},
                              {" SET "},
                              {" RST "},
                              {"TMR_R"},
                              {"CTR_R"},
                              {"PWM"},
                              {"PWM_F"},
                              {"AI ="},
                              {"AI >"},
                              {"AI <"},
                              {"AI ><"},
                              {"<<<"},
                              {">>>"},
                              {"INS"},
                              {"DEL"},
                              {"NEW"},
                              {"TOP"},
                              {"+++"},
                              {"---"},
                              {"INS"},
                              {"DEL"}};

TFT_eSPI tft = TFT_eSPI(); 
SPIClass SPI_1(TFT_TOUCH_MOSI, TFT_TOUCH_MISO, TFT_TOUCH_SCLK);
XPT2046_Touchscreen ts(TFT_TOUCH_CS);

HardwareTimer *PWM_0 = new HardwareTimer(TIM1);
HardwareTimer *PWM_1 = new HardwareTimer(TIM2);
HardwareTimer *PWM_2 = new HardwareTimer(TIM3);
HardwareTimer *PWM_3 = new HardwareTimer(TIM4);

STM32Timer ITimer0(TIM6);                                   

void setup(){
  delay(2500);
  attachInterrupt(TFT_TOUCH_INT, touch_int, FALLING);
  analogReadResolution(RESOLUTION);
  ts.begin(SPI_1);
  ts.setRotation(3);
  Serial.begin(115200);
  pinMode(INPUT_MODULE_0, OUTPUT);
  pinMode(INPUT_MODULE_1, OUTPUT);
  pinMode(INPUT_MODULE_2, OUTPUT);
  pinMode(INPUT_MODULE_3, OUTPUT);
  pinMode(OUTPUT_MODULE_0, OUTPUT);
  pinMode(OUTPUT_MODULE_1, OUTPUT);
  pinMode(OUTPUT_MODULE_2, OUTPUT);
  pinMode(OUTPUT_MODULE_3, OUTPUT);
  pinMode(IN_0, INPUT_PULLDOWN);
  pinMode(IN_1, INPUT_PULLDOWN);
  pinMode(IN_2, INPUT_PULLDOWN);
  pinMode(IN_3, INPUT_PULLDOWN);
  pinMode(IN_4, INPUT_PULLDOWN);
  pinMode(IN_5, INPUT_PULLDOWN);
  pinMode(IN_6, INPUT_PULLDOWN);
  pinMode(IN_7, INPUT_PULLDOWN);
  pinMode(IN_8, INPUT_PULLDOWN);
  pinMode(IN_9, INPUT_PULLDOWN);
  pinMode(IN_10, INPUT_PULLDOWN);
  pinMode(IN_11, INPUT_PULLDOWN);
  pinMode(IN_12, INPUT_PULLDOWN);
  pinMode(IN_13, INPUT_PULLDOWN);
  pinMode(IN_14, INPUT_PULLDOWN);
  pinMode(IN_15, INPUT_PULLDOWN);
  pinMode(KEYB_R_0, INPUT_PULLDOWN);
  pinMode(KEYB_R_1, INPUT_PULLDOWN);
  pinMode(KEYB_R_2, INPUT_PULLDOWN);
  pinMode(KEYB_R_3, INPUT_PULLDOWN);
  pinMode(KEYB_R_4, INPUT_PULLDOWN);
  pinMode(TFT_TOUCH_INT, INPUT);
  pinMode(PROG_RUN, INPUT_PULLDOWN);
  pinMode(KEYB_C_0, OUTPUT);
  pinMode(KEYB_C_1, OUTPUT);
  pinMode(KEYB_C_2, OUTPUT);
  pinMode(KEYB_C_3, OUTPUT);
  pinMode(UIT_0, OUTPUT);
  pinMode(UIT_1, OUTPUT);
  pinMode(UIT_2, OUTPUT);
  pinMode(UIT_3, OUTPUT);
  pinMode(UIT_4, OUTPUT);
  pinMode(UIT_5, OUTPUT);
  pinMode(UIT_6, OUTPUT);
  pinMode(UIT_7, OUTPUT);
  pinMode(UIT_8, OUTPUT);
  pinMode(UIT_9, OUTPUT);
  pinMode(UIT_10, OUTPUT);
  pinMode(UIT_11, OUTPUT);
  pinMode(UIT_12, OUTPUT);
  pinMode(UIT_13, OUTPUT);
  pinMode(UIT_14, OUTPUT);
  pinMode(UIT_15, OUTPUT);
  pinMode(BLINK, OUTPUT);
  digitalWrite(INPUT_MODULE_0, true);
  digitalWrite(INPUT_MODULE_1, true);
  digitalWrite(INPUT_MODULE_2, true);
  digitalWrite(INPUT_MODULE_3, true);
  digitalWrite(OUTPUT_MODULE_0, true);
  digitalWrite(OUTPUT_MODULE_1, true);
  digitalWrite(OUTPUT_MODULE_2, true);
  digitalWrite(OUTPUT_MODULE_3, true);
  digitalWrite(UIT_0, false);
  digitalWrite(UIT_1, false);
  digitalWrite(UIT_2, false);
  digitalWrite(UIT_3, false);
  digitalWrite(UIT_4, false);
  digitalWrite(UIT_5, false);
  digitalWrite(UIT_6, false);
  digitalWrite(UIT_7, false);
  digitalWrite(UIT_8, false);
  digitalWrite(UIT_9, false);
  digitalWrite(UIT_10, false);
  digitalWrite(UIT_11, false);
  digitalWrite(UIT_12, false);
  digitalWrite(UIT_13, false);
  digitalWrite(UIT_14, false);
  digitalWrite(UIT_15, false);
  digitalWrite(KEYB_C_0, false);
  digitalWrite(KEYB_C_1, false);
  digitalWrite(KEYB_C_2, false);
  digitalWrite(KEYB_C_3, false);
  digitalWrite(BLINK, false);
  totaal_reset();
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextFont(4);
  tft.setCursor((480 - tft.textWidth("STM32 PLC", 4)) / 2, 150);
  tft.print("STM32 PLC");
  tft.setTextFont(2);
  tft.setCursor(10, 300);
  tft.print("thieu-b55 februari 2025");
  delay(5000);
  /*
  touch calibrate
  */
  calibrate_test();
  if(!(calibrated_bool)){
    touch_calibrate();
    calibrate_test();
  }
  timer_int = cyclustijd_int / 1000;
  pow_int = pow(2, RESOLUTION);
  ITimer0.attachInterruptInterval(cyclustijd_int, TimerHandler0);   
  if(digitalRead(PROG_RUN)){
    keuze_bool = false;
    lees_instellingen();
    lees_programma();
  }
  else{
    keuze_bool = true;
  }
}

  /*
   EEPROM.put / EEPROM.get >> uint16_t / float
   EEPROM.update / EEPROM.write / EEPROM.read >> uint8_t / char
  */

void loop(){
  PWM_0->setPWM(1, PWM_0_UIT, freq_array_int[0], duty_cycle_array_int[0]);
  PWM_1->setPWM(1, PWM_1_UIT, freq_array_int[1], duty_cycle_array_int[1]);
  PWM_2->setPWM(1, PWM_2_UIT, freq_array_int[2], duty_cycle_array_int[2]);
  PWM_3->setPWM(1, PWM_3_UIT, freq_array_int[3], duty_cycle_array_int[3]);
  if(!digitalRead(PROG_RUN)){
    programmeren_bool = false;
    pwm_instellen_bool = false;
    tmr_instellen_bool = false;
    ctr_instellen_bool = false;
    prog_flash_bool = false;
    flash_lezen_bool = false;
    flash_schrijven_bool = false;
    programma_printen_bool = false;
    programma_wissen_bool = false;
    aantal_in_out_kiezen_bool = false;
    keuze_bool = true;
    keuzemenu();
    while((keuze_bool) && (!digitalRead(PROG_RUN))){
      touched_bool = false;
      while((!touched_bool) && (!digitalRead(PROG_RUN))){
        touch();
      }
      for(int keuze_int = 0; keuze_int < 8; keuze_int++){
        if((y_touch_int >= keuzemenu_hor_int[keuze_int]) && (y_touch_int <= keuzemenu_hor_int[keuze_int] + 25)){
          keuze_bool = false;
          switch(keuze_int){
            case 0:
              programmeren_bool = true;
              break;
            case 1:
              pwm_instellen_bool = true;
              break;
            case 2:
              tmr_instellen_bool = true;
              break;
            case 3:
              ctr_instellen_bool = true;
              break;
            case 4:
              prog_flash_bool = true;
              break;
            case 5:
              programma_printen_bool = true;
              break;
            case 6:
              programma_wissen_bool = true;
              break;
            case 7:
              aantal_in_out_kiezen_bool = true;
              break;
          }
          tft.fillScreen(TFT_BLACK);
          tft.setTextColor(TFT_WHITE);
          tft.setTextFont(2);
        }
      }
    }
    
    /*
    PROGRAMMEREN
    */
    if((programmeren_bool) && (!digitalRead(PROG_RUN))){
      veranderd_bool = false;
      programmeerscherm();
      tft.setCursor(0, 20);
      tft.setTextColor(TFT_WHITE);
      touched_bool = false;
      key_int = 99;
      commando_int = 99;
      commando_plus_int = 99;
      programma_lijn_int = 0;
      edit_lijn_positie_int = 0;
      programma_lijn_positie_int = 0;
      toon_programma_lijn();
      while((programmeren_bool) && (!digitalRead(PROG_RUN))){
        touch();
        if(touched_bool){
          touched_bool = false;
          commando_int = 0xff;
          for(int x = 0; x < 35; x ++){
            if((x_touch_int >= commando_coord_int[x][0]) && (x_touch_int <= commando_coord_int[x][0] + 44) &&
                (y_touch_int >= commando_coord_int[x][1]) && (y_touch_int <= commando_coord_int[x][1] + 25)){
              commando_int = x;
              commando_plus_int = x + 200;
            }
          }
          /*
          /*
          Programmeren
          */
          if((programma_lijn_positie_int == edit_lijn_positie_int) && (commando_int < (LEFT - 200)) && (programma_lijn_positie_int < MAX_INST + 1)){
            if(programma_lijn_positie_int != 0){
              commando_min_1_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int - 1];
              commando_min_2_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int - 2];
            }
            if(((programma_lijn_positie_int == 0) || (commando_min_1_int == AND) || (commando_min_1_int == OR) || (commando_min_1_int == XOR) || (commando_min_1_int == OPEN) || (commando_min_1_int == NOT)
                || (commando_min_1_int == RISE) || (commando_min_1_int == FALL))
                && ((commando_plus_int == IN) || (commando_plus_int == OUT) || (commando_plus_int == MERKER) || (commando_plus_int == TMR) || (commando_plus_int == CTRU) || (commando_plus_int == CTRD))){
              programma_array_int[programma_lijn_int][programma_lijn_positie_int] = commando_plus_int;
              programma_lijn_positie_int ++;
              edit_lijn_positie_int ++;
              programma_array_int[programma_lijn_int][programma_lijn_positie_int] = 99;
              x_positie_int = tft.getCursorX() + 5;
              x_positie_vorig_int = x_positie_int;
              toon_programma_lijn();
            }
            if(((programma_lijn_positie_int == 0) || (commando_min_1_int == AND) || (commando_min_1_int == OR) || (commando_min_1_int == XOR) || (commando_min_1_int == OPEN))
                && ((commando_plus_int == RISE) || (commando_plus_int == FALL) || (commando_plus_int == NOT))){
              programma_array_int[programma_lijn_int][programma_lijn_positie_int] = commando_plus_int;
              toon_programma_lijn();
            }
            if(((programma_lijn_positie_int == 0) || (commando_min_1_int == AND) || (commando_min_1_int == OR) || (commando_min_1_int == XOR) || (commando_min_1_int == NOT)|| (commando_min_1_int == OPEN))
                && (commando_plus_int == OPEN)){
              programma_array_int[programma_lijn_int][programma_lijn_positie_int] = commando_plus_int;
              toon_programma_lijn();
            }
            if((programma_lijn_positie_int == 0)
                && ((commando_plus_int == AI_E) || (commando_plus_int == AI_G) || (commando_plus_int == AI_L))){
              programma_array_int[programma_lijn_int][programma_lijn_positie_int] = commando_plus_int;
              programma_lijn_positie_int ++;
              edit_lijn_positie_int ++;
              programma_array_int[programma_lijn_int][programma_lijn_positie_int] = 9;
              programma_lijn_positie_int ++;
              edit_lijn_positie_int ++;
              programma_array_int[programma_lijn_int][programma_lijn_positie_int] = 0;
              ai_positie_int = 1;
              toon_programma_lijn();
              tft.drawLine(pixel_positie_int[edit_lijn_positie_int - 2], 70, pixel_positie_int[edit_lijn_positie_int -2] + 8, 70, TFT_WHITE);
            }
            if((programma_lijn_positie_int == 0) && (commando_plus_int == AI_G_L)){
              programma_array_int[programma_lijn_int][programma_lijn_positie_int] = commando_plus_int;
              programma_lijn_positie_int ++;
              edit_lijn_positie_int ++;
              programma_array_int[programma_lijn_int][programma_lijn_positie_int] = 9;
              programma_lijn_positie_int ++;
              edit_lijn_positie_int ++;
              programma_array_int[programma_lijn_int][programma_lijn_positie_int] = 0;
              programma_lijn_positie_int ++;
              edit_lijn_positie_int ++;
              programma_array_int[programma_lijn_int][programma_lijn_positie_int] = 0;
              ai_positie_int = 1;
              toon_programma_lijn();
              tft.drawLine(pixel_positie_int[edit_lijn_positie_int - 3], 70, pixel_positie_int[edit_lijn_positie_int -3] + 8, 70, TFT_WHITE);
            }
            if(!((programma_array_int[programma_lijn_int][0] == AI_E) || (programma_array_int[programma_lijn_int][0] == AI_G) || (programma_array_int[programma_lijn_int][0] == AI_L) || (programma_array_int[programma_lijn_int][0] == AI_G_L))){
              if(((programma_lijn_positie_int != 0) && ((commando_min_2_int == IN) || (commando_min_2_int == OUT) || (commando_min_2_int == MERKER) || (commando_min_2_int == TMR) || (commando_min_2_int == CTRU) || (commando_min_2_int == CTRD) || (commando_min_1_int == CLOSE)))
                  && ((commando_plus_int == AND) || (commando_plus_int == OR) || (commando_plus_int == XOR))){
                programma_array_int[programma_lijn_int][programma_lijn_positie_int] = commando_plus_int;
                toon_programma_lijn();
              }
              if(((programma_lijn_positie_int != 0) && ((commando_min_2_int == IN) || (commando_min_2_int == OUT) || (commando_min_2_int == MERKER) || (commando_min_2_int == TMR) || (commando_min_2_int == CTRU) || (commando_min_2_int == CTRD) || (commando_min_1_int == CLOSE)))
                  && ((commando_plus_int == EQUALS) || (commando_plus_int == SET) || (commando_plus_int == RST))){
                programma_array_int[programma_lijn_int][programma_lijn_positie_int] = commando_plus_int;
                toon_programma_lijn();
              }
              if(((programma_lijn_positie_int != 0) && ((commando_min_2_int == IN) || (commando_min_2_int == OUT) || (commando_min_2_int == MERKER) || (commando_min_2_int == TMR) || (commando_min_2_int == CTRU) || (commando_min_2_int == CTRD) || (commando_min_1_int == CLOSE)))
                  && (commando_plus_int == CLOSE)){
                programma_array_int[programma_lijn_int][programma_lijn_positie_int] = commando_plus_int;
                toon_programma_lijn();
              }
              if(((commando_min_1_int == SET) || (commando_min_1_int == RST)) && ((commando_plus_int == OUT) || (commando_plus_int == MERKER))){
                programma_array_int[programma_lijn_int][programma_lijn_positie_int] = commando_plus_int;
                programma_lijn_positie_int ++;
                edit_lijn_positie_int ++;
                programma_array_int[programma_lijn_int][programma_lijn_positie_int] = 99;
                toon_programma_lijn();
              }
              if((commando_min_1_int == EQUALS) && ((commando_plus_int == OUT) || (commando_plus_int == MERKER) || (commando_plus_int == TMR) || (commando_plus_int == CTRU)
                  || (commando_plus_int == CTRD) || (commando_plus_int == TMR_R) || (commando_plus_int == CTR_R))){
                programma_array_int[programma_lijn_int][programma_lijn_positie_int] = commando_plus_int;
                programma_lijn_positie_int ++;
                edit_lijn_positie_int ++;
                programma_array_int[programma_lijn_int][programma_lijn_positie_int] = 99;
                toon_programma_lijn();
              }
              if(((commando_min_1_int == EQUALS) || (commando_min_1_int == SET) || (commando_min_1_int == RST)) && ((commando_plus_int == PWM) || (commando_plus_int == PWM_F))){
                programma_array_int[programma_lijn_int][programma_lijn_positie_int] = commando_plus_int;
                programma_lijn_positie_int ++;
                edit_lijn_positie_int ++;
                programma_array_int[programma_lijn_int][programma_lijn_positie_int] = 9;
                programma_lijn_positie_int ++;
                edit_lijn_positie_int ++;
                programma_array_int[programma_lijn_int][programma_lijn_positie_int] = 0;
                pwm_positie_int = 1;
                toon_programma_lijn();
                tft.drawLine(pixel_positie_int[edit_lijn_positie_int - 2], 70, pixel_positie_int[edit_lijn_positie_int -2] + 8, 70, TFT_WHITE);
              }
            }
            if((programma_array_int[programma_lijn_int][0] == AI_E) || (programma_array_int[programma_lijn_int][0] == AI_G) || (programma_array_int[programma_lijn_int][0] == AI_L)){
              if((programma_lijn_positie_int == 3) && ((commando_plus_int == EQUALS) || (commando_plus_int == SET) || (commando_plus_int == RST))){
                programma_array_int[programma_lijn_int][programma_lijn_positie_int] = commando_plus_int;
                toon_programma_lijn();
              }
              if((programma_lijn_positie_int == 4) && ((commando_plus_int == OUT) || (commando_plus_int == MERKER))){
                programma_array_int[programma_lijn_int][programma_lijn_positie_int] = commando_plus_int;
                programma_lijn_positie_int ++;
                edit_lijn_positie_int ++;
                programma_array_int[programma_lijn_int][programma_lijn_positie_int] = 99;
                toon_programma_lijn();
              }
              if((programma_lijn_positie_int == 4) && ((commando_plus_int == PWM) || (commando_plus_int == PWM_F))){
                programma_array_int[programma_lijn_int][programma_lijn_positie_int] = commando_plus_int;
                programma_lijn_positie_int ++;
                edit_lijn_positie_int ++;
                programma_array_int[programma_lijn_int][programma_lijn_positie_int] = 9;
                programma_lijn_positie_int ++;
                edit_lijn_positie_int ++;
                programma_array_int[programma_lijn_int][programma_lijn_positie_int] = 0;
                pwm_positie_int = 1;
                toon_programma_lijn();
                tft.drawLine(pixel_positie_int[edit_lijn_positie_int - 2], 70, pixel_positie_int[edit_lijn_positie_int -2] + 8, 70, TFT_WHITE);
              }
            }
            if(programma_array_int[programma_lijn_int][0] == AI_G_L){
              if((programma_lijn_positie_int == 4) && ((commando_plus_int == EQUALS) || (commando_plus_int == SET) || (commando_plus_int == RST))){
                programma_array_int[programma_lijn_int][programma_lijn_positie_int] = commando_plus_int;
                toon_programma_lijn();
              }
              if((programma_lijn_positie_int == 5) && ((commando_plus_int == OUT) || (commando_plus_int == MERKER))){
                programma_array_int[programma_lijn_int][programma_lijn_positie_int] = commando_plus_int;
                programma_lijn_positie_int ++;
                edit_lijn_positie_int ++;
                programma_array_int[programma_lijn_int][programma_lijn_positie_int] = 99;
                toon_programma_lijn();
              }
              if((programma_lijn_positie_int == 5) && ((commando_plus_int == PWM) || (commando_plus_int == PWM_F))){
                programma_array_int[programma_lijn_int][programma_lijn_positie_int] = commando_plus_int;
                programma_lijn_positie_int ++;
                edit_lijn_positie_int ++;
                programma_array_int[programma_lijn_int][programma_lijn_positie_int] = 9;
                programma_lijn_positie_int ++;
                edit_lijn_positie_int ++;
                programma_array_int[programma_lijn_int][programma_lijn_positie_int] = 0;
                pwm_positie_int = 1;
                toon_programma_lijn();
                tft.drawLine(pixel_positie_int[edit_lijn_positie_int - 2], 70, pixel_positie_int[edit_lijn_positie_int -2] + 8, 70, TFT_WHITE);
              }
            }
            if(programma_lijn_positie_int >= (MAX_INST)){
              max_bool = true;
              tft.setTextColor(TFT_RED);
              tft.print("  *MAX*");
              tft.setTextColor(TFT_WHITE);
            }
            else{
              max_bool = false;
            }
            bereken_programma_lijn_positie_int();
            edit_lijn_positie_int = programma_lijn_positie_int;
          }
          /*
          Edit programma
          */

          /********
          LINE EDIT
          /********

          /*
          NEW LINE
          */
          if(commando_plus_int == NEW){
            if(!max_bool){
              tft.drawLine(0, 70, 479, 70, TFT_BLACK);
              int x;
              open_teller_int = 0;
              close_teller_int = 0;
              for(x = 0; x < 25; x ++){
                error_array_bool[x] = false;
                o_c_array_bool[x] = false;
              }
              program_error_bool = false;
              o_c_error_bool = false;
              x = 0;
              while(programma_array_int[programma_lijn_int][x] != 0xff){
                if((programma_array_int[programma_lijn_int][x] == IN) || (programma_array_int[programma_lijn_int][x] == OUT) || (programma_array_int[programma_lijn_int][x] == MERKER) || (programma_array_int[programma_lijn_int][x] == TMR)
                    || (programma_array_int[programma_lijn_int][x] == CTRU) || (programma_array_int[programma_lijn_int][x] == CTRD) || (programma_array_int[programma_lijn_int][x] == TMR_R) || (programma_array_int[programma_lijn_int][x] == CTR_R)){
                  x += 2;
                } 
                if((programma_array_int[programma_lijn_int][x] == AI_E) || (programma_array_int[programma_lijn_int][x] == AI_G) || (programma_array_int[programma_lijn_int][x] == AI_L)){
                  x += 3;
                } 
                if(programma_array_int[programma_lijn_int][x] == AI_G_L){
                  x += 4;
                } 
                if(((programma_array_int[programma_lijn_int][x] == AND) || (programma_array_int[programma_lijn_int][x] == OR) || (programma_array_int[programma_lijn_int][x] == XOR) || (programma_array_int[programma_lijn_int][x] == NOT)
                    || (programma_array_int[programma_lijn_int][x] == RISE) || (programma_array_int[programma_lijn_int][x] == FALL))
                    && ((programma_array_int[programma_lijn_int][x + 1] == AND) || (programma_array_int[programma_lijn_int][x + 1] == OR) || (programma_array_int[programma_lijn_int][x + 1] == XOR) || (programma_array_int[programma_lijn_int][x + 1] == EQUALS)
                    || (programma_array_int[programma_lijn_int][x + 1] == SET) || (programma_array_int[programma_lijn_int][x + 1] == RST))){
                  error_array_bool[x] = true;
                  error_array_bool[x + 1] = true;
                  program_error_bool  = true;
                }
                if(((programma_array_int[programma_lijn_int][x] == SET) || (programma_array_int[programma_lijn_int][x] == RST) || (programma_array_int[programma_lijn_int][x] == EQUALS))
                    && ((programma_array_int[programma_lijn_int][x + 1] == SET) || (programma_array_int[programma_lijn_int][x + 1] == RST) || (programma_array_int[programma_lijn_int][x + 1] == EQUALS))){
                  error_array_bool[x] = true;
                  error_array_bool[x + 1] = true;
                  program_error_bool  = true;
                }
                if(((programma_array_int[programma_lijn_int][x] == NOT) || (programma_array_int[programma_lijn_int][x] == RISE) || (programma_array_int[programma_lijn_int][x] == FALL)) && ((programma_array_int[programma_lijn_int][x + 1] == NOT) || (programma_array_int[programma_lijn_int][x + 1] == RISE) || (programma_array_int[programma_lijn_int][x + 1] == FALL))){
                  error_array_bool[x] = true;
                  error_array_bool[x + 1] = true;
                  program_error_bool  = true;
                }
                if(((programma_array_int[programma_lijn_int][x] == RISE) || (programma_array_int[programma_lijn_int][x] == FALL)) && (programma_array_int[programma_lijn_int][x + 1] == OPEN)){
                  open_teller_int ++;
                  o_c_array_bool[x] = true;
                }
                if(programma_array_int[programma_lijn_int][x] == OPEN){
                  open_teller_int ++;
                  o_c_array_bool[x] = true;
                }
                if(programma_array_int[programma_lijn_int][x] == CLOSE){
                  close_teller_int ++;
                  o_c_array_bool[x] = true;
                }
                x++;
              }
              if(open_teller_int != close_teller_int){
                o_c_error_bool = true;
              }                                                     
              x = 0;
              while(programma_array_int[programma_lijn_int][x] != 0xff){
                if((programma_array_int[programma_lijn_int][x] == IN) || (programma_array_int[programma_lijn_int][x] == OUT) || (programma_array_int[programma_lijn_int][x] == MERKER) || (programma_array_int[programma_lijn_int][x] == TMR)
                    || (programma_array_int[programma_lijn_int][x] == CTRU) || (programma_array_int[programma_lijn_int][x] == CTRD) || (programma_array_int[programma_lijn_int][x] == TMR_R) || (programma_array_int[programma_lijn_int][x] == CTR_R)){
                  x += 2;   
                  if((programma_array_int[programma_lijn_int][x] == IN) || (programma_array_int[programma_lijn_int][x] == OUT) || (programma_array_int[programma_lijn_int][x] == MERKER) || (programma_array_int[programma_lijn_int][x] == TMR)
                    || (programma_array_int[programma_lijn_int][x] == CTRU) || (programma_array_int[programma_lijn_int][x] == CTRD) || (programma_array_int[programma_lijn_int][x] == TMR_R) || (programma_array_int[programma_lijn_int][x] == CTR_R)
                    || (programma_array_int[programma_lijn_int][x] == NOT) || (programma_array_int[programma_lijn_int][x] == RISE) || (programma_array_int[programma_lijn_int][x] == FALL)){
                    error_array_bool[x] = true;
                    program_error_bool  = true;
                    x += 2;
                  }    
                }
                else{
                  x++;
                }   
              }
              x = 0;
              while(programma_array_int[programma_lijn_int][x] != 0xff){
                if((programma_array_int[programma_lijn_int][x] == IN) || (programma_array_int[programma_lijn_int][x] == OUT) || (programma_array_int[programma_lijn_int][x] == MERKER) || (programma_array_int[programma_lijn_int][x] == TMR)
                    || (programma_array_int[programma_lijn_int][x] == CTRU) || (programma_array_int[programma_lijn_int][x] == CTRD) || (programma_array_int[programma_lijn_int][x] == TMR_R) || (programma_array_int[programma_lijn_int][x] == CTR_R)){
                  x += 2;
                } 
                if(programma_array_int[programma_lijn_int][x] == INS_C){
                  error_array_bool[x] = true;
                  program_error_bool  = true;
                }
                x++;
              }
              x = 0;
              while(programma_array_int[programma_lijn_int][x] != 0xff){  
                if(((programma_array_int[programma_lijn_int][x] == IN) && (programma_array_int[programma_lijn_int][x - 2] != PWM)) || (programma_array_int[programma_lijn_int][x] == OUT) || (programma_array_int[programma_lijn_int][x] == MERKER) || (programma_array_int[programma_lijn_int][x] == TMR)
                    || (programma_array_int[programma_lijn_int][x] == CTRU) || (programma_array_int[programma_lijn_int][x] == CTRD) || (programma_array_int[programma_lijn_int][x] == TMR_R) || (programma_array_int[programma_lijn_int][x] == CTR_R)){
                  int max_int = 63;
                  if(programma_array_int[programma_lijn_int][x] == IN){
                    max_int = aantal_input_int - 1;
                  }
                  if(programma_array_int[programma_lijn_int][x] == OUT){
                    max_int = aantal_output_int - 1;
                  }
                  if(programma_array_int[programma_lijn_int][x + 1] > max_int){
                    error_array_bool[x + 1] = true;
                    program_error_bool = true;
                  }
                  x += 2;  
                }
                else{
                  x++;
                } 
              }
              x = 0;
              while(programma_array_int[programma_lijn_int][x] != 0xff){
                if(programma_array_int[programma_lijn_int][x] == PWM){
                  if(programma_array_int[programma_lijn_int][x + 1] > 3){
                    error_array_bool[x + 1] = true;
                    program_error_bool = true;
                  }
                  if(programma_array_int[programma_lijn_int][x + 2] > 100){
                    error_array_bool[x + 2] = true;
                    program_error_bool = true;
                  }
                }
                x ++;
              }
              x = 0;
              while(programma_array_int[programma_lijn_int][x] != 0xff){
                if(programma_array_int[programma_lijn_int][x] == PWM_F){
                  if(programma_array_int[programma_lijn_int][x + 1] > 3){
                    error_array_bool[x + 1] = true;
                    program_error_bool = true;
                  }
                  if(programma_array_int[programma_lijn_int][x + 2] > 3){
                    error_array_bool[x + 2] = true;
                    program_error_bool = true;
                  }
                }
                x ++;
              }
              if((programma_array_int[programma_lijn_int][0] == AI_E) || (programma_array_int[programma_lijn_int][0] == AI_G) || (programma_array_int[programma_lijn_int][0] == AI_L)){
                if(programma_array_int[programma_lijn_int][1] > 3){
                  error_array_bool[1] = true;
                  program_error_bool = true;
                }
                if(programma_array_int[programma_lijn_int][2] > 100){
                  error_array_bool[2] = true;
                  program_error_bool = true;
                }
              }
              if(programma_array_int[programma_lijn_int][0] == AI_G_L){
                if(programma_array_int[programma_lijn_int][1] > 3){
                  error_array_bool[1] = true;
                  program_error_bool = true;
                }
                if(programma_array_int[programma_lijn_int][2] > 100){
                  error_array_bool[2] = true;
                  program_error_bool = true;
                }
                if(programma_array_int[programma_lijn_int][3] > 100){
                  error_array_bool[3] = true;
                  program_error_bool = true;
                }
              }
              print_error_test();
              if(!((program_error_bool) || (o_c_error_bool))){
                bereken_programma_lengte();
                open_array_int[programma_lijn_int] = open_teller_int;
                if(programma_array_int[programma_lijn_max_int][0] != 0xff){
                  programma_lijn_max_int += 1;
                  if(programma_lijn_max_int > (MAX_LINE - 1)){
                    programma_lijn_max_int = MAX_LINE - 1;
                  }
                  for(int x = 0; x < (MAX_INST + 1); x++){
                    pixel_positie_int[x] = 0xff;
                  }
                }
                edit_lijn_positie_int = 0;
                programma_lijn_positie_int = 0;
                if(!veranderd_bool){
                  programma_lijn_int = programma_lijn_max_int;
                }
                veranderd_bool = false;
                tft.setTextColor(TFT_WHITE);
                print_lijnnummer();
                print_edit_lijn();
                programma_lijn_positie_int = edit_lijn_positie_int;
              }
              program_error_bool = false;
              o_c_error_bool = false;
           }
          }
          /*
          GOTO TOP
          */
          if(commando_plus_int == TOP){
            programma_lijn_int = 0;
            print_lijnnummer();
            print_edit_lijn();
            programma_lijn_positie_int = edit_lijn_positie_int;
          }
          /*
          NEXT LINE
          */
          if((commando_plus_int == UP)  && (!veranderd_bool)){
            tft.drawLine(0, 70, 479, 70, TFT_BLACK);
            programma_lijn_int += 1;
            if(programma_lijn_int > programma_lijn_max_int){
              programma_lijn_int = programma_lijn_max_int;
            }
            print_lijnnummer();
            print_edit_lijn();
            programma_lijn_positie_int = edit_lijn_positie_int;
          }
          /*
          PREVIOUS LINE
          */
          if((commando_plus_int == DOWN) && (!veranderd_bool)){
            tft.drawLine(0, 70, 479, 70, TFT_BLACK);
            programma_lijn_int -= 1;
            if(programma_lijn_int < 0){
              programma_lijn_int = 0;
            }
            print_lijnnummer();
            print_edit_lijn();
            programma_lijn_positie_int = edit_lijn_positie_int;
          }
          /*
          INSERT LINE
          */
          if((commando_plus_int == INS) && (programma_lijn_positie_int == edit_lijn_positie_int)){
            if(programma_lijn_max_int < (MAX_LINE - 1)){
              int x = MAX_LINE - 1;
              int y = MAX_LINE - 2;
              while(x > programma_lijn_int){
                for(int z = 0; z < MAX_INST + 1; z++){
                  programma_array_int[x][z] = programma_array_int[y][z];
                  open_array_int[x] = open_array_int[y];
                }
                x --;
                y --;
              }
              for(int z = 0; z < MAX_INST + 1; z++){
                programma_array_int[programma_lijn_int][z] = 0xff;
              }
              programma_lijn_max_int ++;
              print_lijnnummer();
              print_edit_lijn();
              programma_lijn_positie_int = edit_lijn_positie_int;
            }
          }
          /*
          DELETE LINE
          */
          if((commando_plus_int == DEL)  && (programma_lijn_positie_int == edit_lijn_positie_int)){
            for(int x = programma_lijn_int; x < (MAX_LINE + 1); x ++){
              for(int z = 0; z < MAX_INST + 1; z++){
                programma_array_int[x][z] = programma_array_int[x + 1][z];
                open_array_int[x] = open_array_int[x + 1];
               }
            }
            for(int z = 0; z < MAX_INST + 1; z++){
              programma_array_int[MAX_LINE][z] = 0xff;
            }
            if(programma_lijn_max_int > 0){
              programma_lijn_max_int --;
            }
            if(programma_lijn_int > 0){
              programma_lijn_int --;
            }
            else{
              programma_lijn_int = 0;
            }
            print_lijnnummer();
            print_edit_lijn();
            programma_lijn_positie_int = edit_lijn_positie_int;
            tft.drawLine(0, 70, 479, 70, TFT_BLACK);
          }

          /**********
          INLINE EDIT
          **********/

          /*
          POSITION -1
          */
          if(commando_plus_int == LEFT){
            lengte_int = 0;
            edit_bool = true;
            edit_lijn_positie_int -= 1;
            if(edit_lijn_positie_int < 0){
              edit_lijn_positie_int = 0;
            }
            commando_saved_int = programma_array_int[programma_lijn_int][edit_lijn_positie_int];
            if(edit_lijn_positie_int != 0){
              commando_saved_min_1_int = programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1];
              commando_saved_min_2_int = programma_array_int[programma_lijn_int][edit_lijn_positie_int - 2];
              if(programma_array_int[programma_lijn_int][0] == AI_G_L){
                commando_saved_min_3_int = programma_array_int[programma_lijn_int][edit_lijn_positie_int - 3];
              }
              if((commando_saved_min_1_int == IN) || (commando_saved_min_1_int == OUT) || (commando_saved_min_1_int == MERKER) || (commando_saved_min_1_int == TMR)
                  || (commando_saved_min_1_int == CTRU) || (commando_saved_min_1_int == CTRD) || (commando_saved_min_1_int == CTR_R) 
                  || (commando_saved_min_1_int == TMR_R) || (commando_saved_min_2_int == PWM)){
                lengte_int = 12;
              }
              else{
                lengte_int = tft.textWidth(commando_string[commando_saved_int - 200], 2);
              }
              if(commando_saved_min_1_int == PWM){
                lengte_int = 8;
              }
              if(commando_saved_min_2_int == PWM){
                lengte_int = 20;
              }
              if(commando_saved_min_1_int == PWM_F){
                lengte_int = 8;
              }
              if(commando_saved_min_2_int == PWM_F){
                lengte_int = 8;
              }
              if((commando_saved_min_1_int == AI_E) || (commando_saved_min_1_int == AI_G) || (commando_saved_min_1_int == AI_L)){
                lengte_int = 8;
              }
              if((commando_saved_min_2_int == AI_E) || (commando_saved_min_2_int == AI_G) || (commando_saved_min_2_int == AI_L)){
                lengte_int = 20;
              }
              if(programma_array_int[programma_lijn_int][0] == AI_G_L){
                if(commando_saved_min_3_int == AI_G_L){
                  lengte_int = 20;
                }
                if(commando_saved_min_2_int == AI_G_L){
                  lengte_int = 20;
                }
                if(commando_saved_min_1_int == AI_G_L){
                  lengte_int = 8;
                }
              }
            }
            else{
              lengte_int = tft.textWidth(commando_string[commando_saved_int - 200], 2);
            }
            tft.drawLine(0, 70, 479, 70, TFT_BLACK);
            if(lengte_int != 0){
              tft.drawLine(pixel_positie_int[edit_lijn_positie_int], 70, (pixel_positie_int[edit_lijn_positie_int] + lengte_int), 70, TFT_WHITE);
            }
          }
          /*
          POSITION +1
          */
          if(commando_plus_int == RIGHT){
            edit_lijn_positie_int += 1;
            lengte_int = 0;
            if(edit_lijn_positie_int > programma_lijn_positie_int){
              edit_lijn_positie_int = programma_lijn_positie_int;
            }
            commando_saved_int = programma_array_int[programma_lijn_int][edit_lijn_positie_int];
            commando_saved_min_1_int = programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1];
            commando_saved_min_2_int = programma_array_int[programma_lijn_int][edit_lijn_positie_int - 2];
            if(programma_array_int[programma_lijn_int][0] == AI_G_L){
              commando_saved_min_3_int = programma_array_int[programma_lijn_int][edit_lijn_positie_int - 3];
            }
            if((commando_saved_min_1_int == IN) || (commando_saved_min_1_int == OUT) || (commando_saved_min_1_int == MERKER) || (commando_saved_min_1_int == TMR)
                || (commando_saved_min_1_int == CTRU) || (commando_saved_min_1_int == CTRD) || (commando_saved_min_1_int == CTR_R)
                || (commando_saved_min_1_int == TMR_R) || (commando_saved_min_2_int == PWM)){
              lengte_int = 12;
            }
            else{
              lengte_int = tft.textWidth(commando_string[commando_saved_int - 200], 2);
            }
            if(commando_saved_min_1_int == PWM){
              lengte_int = 8;
            }
            if(commando_saved_min_2_int == PWM){
              lengte_int = 20;
            }
            if(commando_saved_min_1_int == PWM_F){
              lengte_int = 8;
            }
            if(commando_saved_min_2_int == PWM_F){
              lengte_int = 8;
            }
            if((commando_saved_min_1_int == AI_E) || (commando_saved_min_1_int == AI_G) || (commando_saved_min_1_int == AI_L)){
              lengte_int = 8;
            }
            if((commando_saved_min_2_int == AI_E) || (commando_saved_min_2_int == AI_G) || (commando_saved_min_2_int == AI_L)){
              lengte_int = 20;
            }
            if(programma_array_int[programma_lijn_int][0] == AI_G_L){
              if(commando_saved_min_3_int == AI_G_L){
                lengte_int = 20;
              }
              if(commando_saved_min_2_int == AI_G_L){
                lengte_int = 20;
              }
              if(commando_saved_min_1_int == AI_G_L){
                lengte_int = 8;
              }
            }
            tft.drawLine(0, 70, 479, 70, TFT_BLACK);
            if(lengte_int != 0){
              tft.drawLine(pixel_positie_int[edit_lijn_positie_int], 70, pixel_positie_int[edit_lijn_positie_int] + lengte_int, 70, TFT_WHITE);
            }
          }
          /*
          INGAVE NIEUW COMMANDO
          */
          if((programma_lijn_positie_int != edit_lijn_positie_int) && (commando_int < (LEFT - 200))){
            if(((commando_saved_int == AND) || (commando_saved_int == OR) || (commando_saved_int == XOR) || (commando_saved_int == RISE) || (commando_saved_int == FALL) || (commando_saved_int == NOT)) 
                && ((commando_plus_int == AND) || (commando_plus_int == OR) || (commando_plus_int == XOR) || (commando_plus_int == RISE) || (commando_plus_int == FALL) || (commando_plus_int == NOT))){
              programma_array_int[programma_lijn_int][edit_lijn_positie_int] = commando_plus_int;
              print_edit_lijn();
              edit_lijn_positie_int = programma_lijn_positie_int;
              tft.drawLine(0, 70, 479, 70, TFT_BLACK);
            }
            if(((commando_saved_int ==SET) || (commando_saved_int ==RST) || (commando_saved_int ==EQUALS)) && ((commando_plus_int ==SET) || (commando_plus_int ==RST) || (commando_plus_int ==EQUALS))){
              programma_array_int[programma_lijn_int][edit_lijn_positie_int] = commando_plus_int;
              print_edit_lijn();
              edit_lijn_positie_int = programma_lijn_positie_int;
              tft.drawLine(0, 70, 479, 70, TFT_BLACK);
            }
            if((commando_saved_min_1_int != EQUALS) && (commando_saved_min_1_int != SET) && (commando_saved_min_1_int != RST)){
              if(((commando_saved_int == IN) || (commando_saved_int == OUT) || (commando_saved_int == MERKER) || (commando_saved_int == TMR) || (commando_saved_int == CTRU) || (commando_plus_int == CTRD)) 
                  && ((commando_plus_int == IN) || (commando_plus_int == OUT) || (commando_plus_int == MERKER) || (commando_plus_int == TMR) || (commando_plus_int == CTRU) || (commando_plus_int == CTRD))){
                programma_array_int[programma_lijn_int][edit_lijn_positie_int] = commando_plus_int;
                print_edit_lijn();
                edit_lijn_positie_int = programma_lijn_positie_int;
                tft.drawLine(0, 70, 479, 70, TFT_BLACK);
              }  
            }
            if(commando_saved_min_1_int == EQUALS){
              if(((commando_saved_int == OUT) || (commando_saved_int == MERKER) || (commando_saved_int == TMR) || (commando_saved_int == CTRU) || (commando_saved_int == CTRD)
                  || (commando_saved_int == TMR_R) || (commando_saved_int == CTR_R)) 
                  && ((commando_plus_int == OUT) || (commando_plus_int == MERKER) || (commando_plus_int == TMR) || (commando_plus_int == CTRU)
                  || (commando_plus_int == CTRD) || (commando_plus_int == TMR_R) || (commando_plus_int == CTR_R))){
                programma_array_int[programma_lijn_int][edit_lijn_positie_int] = commando_plus_int;
                print_edit_lijn();
                edit_lijn_positie_int = programma_lijn_positie_int;
                tft.drawLine(0, 70, 479, 70, TFT_BLACK);
              }  
            }
            if((commando_saved_min_1_int == SET) || (commando_saved_min_1_int == RST)){
              if(((commando_saved_int == OUT) || (commando_saved_int == MERKER)) && ((commando_plus_int == OUT) || (commando_plus_int == MERKER))){
                programma_array_int[programma_lijn_int][edit_lijn_positie_int] = commando_plus_int;
                print_edit_lijn();
                edit_lijn_positie_int = programma_lijn_positie_int;
                tft.drawLine(0, 70, 479, 70, TFT_BLACK);
              }  
            }
            if((commando_saved_int == INS_C) && ((commando_plus_int == IN) || (commando_plus_int == OUT) || (commando_plus_int == MERKER) || (commando_plus_int == TMR) || (commando_plus_int == CTRU) || (commando_plus_int == CTRD)
                || (commando_plus_int == TMR_R) || (commando_plus_int == CTR_R))){
              int x = programma_lijn_positie_int;
              programma_lijn_positie_int ++;
              int y = programma_lijn_positie_int;
              while(x > (edit_lijn_positie_int - 1)){
                programma_array_int[programma_lijn_int][y] = programma_array_int[programma_lijn_int][x];
                x--;
                y--;
              }
              programma_array_int[programma_lijn_int][edit_lijn_positie_int] = commando_plus_int;
              edit_lijn_positie_int ++;
              int tmp_int = edit_lijn_positie_int;
              programma_array_int[programma_lijn_int][edit_lijn_positie_int] = 99;
              print_edit_lijn();
              edit_lijn_positie_int = tmp_int;
              tft.drawLine(0, 70, 479, 70, TFT_BLACK);
            }
            if((commando_saved_int == INS_C) && ((commando_plus_int == AND) || (commando_plus_int == OR) || (commando_plus_int == XOR) || (commando_plus_int == RISE) || (commando_plus_int == FALL) || (commando_plus_int == NOT) || (commando_plus_int == OPEN) || (commando_plus_int == CLOSE)
                || (commando_plus_int == SET) || (commando_plus_int == RST) || (commando_plus_int == EQUALS))){
              programma_array_int[programma_lijn_int][edit_lijn_positie_int] = commando_plus_int;
              print_edit_lijn();
              edit_lijn_positie_int = programma_lijn_positie_int;
              tft.drawLine(0, 70, 479, 70, TFT_BLACK);
            }
            if((commando_saved_int == INS_C) && ((commando_plus_int == AI_E) || (commando_plus_int == AI_G) || (commando_plus_int == AI_L)) && (edit_lijn_positie_int == 0)
                && ((programma_array_int[programma_lijn_int][1] == EQUALS) || (programma_array_int[programma_lijn_int][1] == SET) || (programma_array_int[programma_lijn_int][1] == RST))){
              for(int x = 19; x > 2; x--){
                programma_array_int[programma_lijn_int][x] = programma_array_int[programma_lijn_int][x - 2];
              }
              programma_array_int[programma_lijn_int][0] = commando_plus_int;
              programma_array_int[programma_lijn_int][1] = 9;
              programma_array_int[programma_lijn_int][2] = 0;
              programma_lijn_positie_int += 2;
              print_edit_lijn();
              edit_lijn_positie_int = programma_lijn_positie_int;
              tft.drawLine(0, 70, 479, 70, TFT_BLACK);
            }
            if((commando_saved_int == INS_C) && (commando_plus_int == AI_G_L) && (edit_lijn_positie_int == 0)
                && ((programma_array_int[programma_lijn_int][1] == EQUALS) || (programma_array_int[programma_lijn_int][1] == SET) || (programma_array_int[programma_lijn_int][1] == RST))){
              for(int x = 19; x > 3; x--){
                programma_array_int[programma_lijn_int][x] = programma_array_int[programma_lijn_int][x - 3];
              }
              programma_array_int[programma_lijn_int][0] = commando_plus_int;
              programma_array_int[programma_lijn_int][1] = 9;
              programma_array_int[programma_lijn_int][2] = 0;
              programma_array_int[programma_lijn_int][3] = 0;
              programma_lijn_positie_int += 3;
              print_edit_lijn();
              edit_lijn_positie_int = programma_lijn_positie_int;
              tft.drawLine(0, 70, 479, 70, TFT_BLACK);
            }
            if((((commando_saved_int == PWM) || (commando_saved_int == PWM_F)) && (commando_saved_min_1_int == EQUALS)) && ((commando_plus_int == OUT) || (commando_plus_int == MERKER) || (commando_plus_int == TMR) 
                  || (commando_plus_int == CTRU) || (commando_plus_int == CTRD) || (commando_plus_int == TMR_R) || (commando_plus_int == CTR_R))){
              
              programma_array_int[programma_lijn_int][edit_lijn_positie_int] = commando_plus_int;
              programma_array_int[programma_lijn_int][edit_lijn_positie_int + 1] = 99;
              programma_array_int[programma_lijn_int][edit_lijn_positie_int + 2] = 0xff;
              print_edit_lijn();
              programma_lijn_positie_int --;
              edit_lijn_positie_int = programma_lijn_positie_int;
              tft.drawLine(0, 70, 479, 70, TFT_BLACK);
            }                                                                                    
            if((((commando_saved_int == PWM) || (commando_saved_int == PWM_F)) && ((commando_saved_min_1_int == SET) || (commando_saved_min_1_int == RST))) && ((commando_plus_int == OUT) || (commando_plus_int == MERKER))){
              
              programma_array_int[programma_lijn_int][edit_lijn_positie_int] = commando_plus_int;
              programma_array_int[programma_lijn_int][edit_lijn_positie_int + 1] = 99;
              programma_array_int[programma_lijn_int][edit_lijn_positie_int + 2] = 0xff;
              print_edit_lijn();
              programma_lijn_positie_int --;
              edit_lijn_positie_int = programma_lijn_positie_int;
              tft.drawLine(0, 70, 479, 70, TFT_BLACK);
            }
            if((commando_saved_min_1_int == SET) || (commando_saved_min_1_int == RST) ||(commando_saved_min_1_int == EQUALS)){
              if(((commando_saved_int == OUT) || (commando_saved_int == MERKER) || (commando_saved_int == TMR) || (commando_saved_int == CTRU) || (commando_saved_int == CTRD)
                   || (commando_saved_int == TMR_R) || (commando_saved_int == CTR_R)) && ((commando_plus_int == PWM) || (commando_plus_int == PWM_F))){
                programma_array_int[programma_lijn_int][edit_lijn_positie_int] = commando_plus_int;
                programma_array_int[programma_lijn_int][edit_lijn_positie_int + 1] = 9;
                programma_array_int[programma_lijn_int][edit_lijn_positie_int + 2] = 0;
                programma_array_int[programma_lijn_int][edit_lijn_positie_int + 3] = 0xff;
                print_edit_lijn();
                programma_lijn_positie_int ++;
                edit_lijn_positie_int = programma_lijn_positie_int;
                tft.drawLine(0, 70, 479, 70, TFT_BLACK);
              }
            }
          }

          /*
          INSERT COMMAND
          */
          if((commando_plus_int == INS_C) && (programma_array_int[programma_lijn_int][0] < AI_E)){
            veranderd_bool = true;
            if(programma_lijn_positie_int < MAX_INST){
              if(((programma_array_int[programma_lijn_int][edit_lijn_positie_int] == AND) || (programma_array_int[programma_lijn_int][edit_lijn_positie_int] == OR) || (programma_array_int[programma_lijn_int][edit_lijn_positie_int] == XOR) || (programma_array_int[programma_lijn_int][edit_lijn_positie_int] == NOT)
                || (programma_array_int[programma_lijn_int][edit_lijn_positie_int] == OPEN) || (programma_array_int[programma_lijn_int][edit_lijn_positie_int] == CLOSE) || (programma_array_int[programma_lijn_int][edit_lijn_positie_int] == IN) || (programma_array_int[programma_lijn_int][edit_lijn_positie_int] == OUT)
                || (programma_array_int[programma_lijn_int][edit_lijn_positie_int] == SET) || (programma_array_int[programma_lijn_int][edit_lijn_positie_int] == RST) || (programma_array_int[programma_lijn_int][edit_lijn_positie_int] == EQUALS) || (programma_array_int[programma_lijn_int][edit_lijn_positie_int] == MERKER)
                || (programma_array_int[programma_lijn_int][edit_lijn_positie_int] == TMR) || (programma_array_int[programma_lijn_int][edit_lijn_positie_int] == CTRU) || (programma_array_int[programma_lijn_int][edit_lijn_positie_int] == CTRD) || (programma_array_int[programma_lijn_int][edit_lijn_positie_int] == TMR_R)
                || (programma_array_int[programma_lijn_int][edit_lijn_positie_int] == CTR_R)) && (((programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1] != SET) && (programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1] != RST)
                && (programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1] != EQUALS)))){
                int x = programma_lijn_positie_int;
                programma_lijn_positie_int ++;
                int y = programma_lijn_positie_int;
                while(x > (edit_lijn_positie_int - 1)){
                  programma_array_int[programma_lijn_int][y] = programma_array_int[programma_lijn_int][x];
                  x--;
                  y--;
                }
                commando_saved_int = INS_C;
                programma_array_int[programma_lijn_int][edit_lijn_positie_int] = commando_plus_int;
                edit_lijn_positie_vorig_int = edit_lijn_positie_int;
                print_edit_lijn();
                edit_lijn_positie_int = edit_lijn_positie_vorig_int;
              }
            }
            if(programma_lijn_positie_int >= (MAX_INST)){
              tft.setTextColor(TFT_RED);
              tft.print("  *MAX*");
              tft.setTextColor(TFT_WHITE);
            }
            bereken_programma_lijn_positie_int();
          }
          /*
          DELETE COMMAND
          */
          if(commando_plus_int == DEL_C){
            veranderd_bool = true;
            commando_int = programma_array_int[programma_lijn_int][edit_lijn_positie_int];
            if(edit_lijn_positie_int > 0){
              commando_min_1_int = programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1];
            }
            if(edit_lijn_positie_int > 1){
              commando_min_2_int = programma_array_int[programma_lijn_int][edit_lijn_positie_int - 2];
            }
            if((commando_int == IN) || (commando_int == OUT) || (commando_int == MERKER) || (commando_int == TMR) || (commando_int == CTRU)
                || (commando_int == CTRD) || (commando_int == TMR_R) || (commando_int == CTR_R)){
              for(int x = edit_lijn_positie_int; x < MAX_INST -2; x++){
                programma_array_int[programma_lijn_int][x] = programma_array_int[programma_lijn_int][x + 2];
              }
              programma_array_int[programma_lijn_int][MAX_INST] = 0xff;
              programma_array_int[programma_lijn_int][MAX_INST - 1] = 0xff;
              toon_programma_lijn();
            }
            if((commando_int == AND) || (commando_int == OR) || (commando_int == XOR) || (commando_int == RISE) || (commando_int == FALL) || (commando_int == NOT) || (commando_int == OPEN) || (commando_int == CLOSE)
                || (commando_int == SET) || (commando_int == RST) || (commando_int == EQUALS)){
              for(int x = edit_lijn_positie_int; x < MAX_INST - 1; x++){
                programma_array_int[programma_lijn_int][x] = programma_array_int[programma_lijn_int][x + 1];
              }
              programma_array_int[programma_lijn_int][(MAX_INST)] = 0xff;
              toon_programma_lijn();
            }
            if((commando_int == AI_E) || (commando_int == AI_G) || (commando_int == AI_L)){
              for(int x = edit_lijn_positie_int; x < MAX_INST -3; x++){
                programma_array_int[programma_lijn_int][x] = programma_array_int[programma_lijn_int][x + 3];
              }
              programma_array_int[programma_lijn_int][MAX_INST] = 0xff;
              programma_array_int[programma_lijn_int][MAX_INST - 1] = 0xff;
              programma_array_int[programma_lijn_int][MAX_INST - 2] = 0xff;
              toon_programma_lijn();
            }
            if(commando_int == AI_G_L){
              for(int x = edit_lijn_positie_int; x < MAX_INST -4; x++){
                programma_array_int[programma_lijn_int][x] = programma_array_int[programma_lijn_int][x + 4];
              }
              programma_array_int[programma_lijn_int][MAX_INST] = 0xff;
              programma_array_int[programma_lijn_int][MAX_INST - 1] = 0xff;
              programma_array_int[programma_lijn_int][MAX_INST - 2] = 0xff;
              programma_array_int[programma_lijn_int][MAX_INST - 3] = 0xff;
              toon_programma_lijn();
            }
            if(commando_int == PWM){
              programma_array_int[programma_lijn_int][edit_lijn_positie_int] = 0xff;
              programma_array_int[programma_lijn_int][edit_lijn_positie_int + 1] = 0xff;
              programma_array_int[programma_lijn_int][edit_lijn_positie_int + 2] = 0xff;
              toon_programma_lijn();
            }
            if(commando_int == PWM_F){
              programma_array_int[programma_lijn_int][edit_lijn_positie_int] = 0xff;
              programma_array_int[programma_lijn_int][edit_lijn_positie_int + 1] = 0xff;
              programma_array_int[programma_lijn_int][edit_lijn_positie_int + 2] = 0xff;
              toon_programma_lijn();
            }
          }
          bereken_programma_lijn_positie_int();
          delay(500);
        }
        /*************
        KEYBOARD INPUT
        *************/
        keyboard_scan();
        if(key_int != 99){
          /*
          PROGRAMMEREN
          */
          if(((key_int >= 0) && (key_int < 10)) && (programma_lijn_positie_int == edit_lijn_positie_int)){
            commando_min_1_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int - 1];
            commando_min_2_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int - 2];
            if((commando_min_2_int == IN) || (commando_min_2_int == OUT) || (commando_min_2_int == MERKER) || (commando_min_2_int == TMR) || (commando_min_2_int == CTRU) || (commando_min_2_int == CTRD)
                || (commando_min_2_int == TMR_R) || (commando_min_2_int == CTR_R)){
              int nummer_int = commando_min_1_int;
              int tiental_int = nummer_int / 10;
              int eenheden_int = nummer_int - (tiental_int * 10);
              tiental_int = eenheden_int;
              eenheden_int = key_int;
              programma_array_int[programma_lijn_int][programma_lijn_positie_int - 1] = (tiental_int * 10) + eenheden_int;
              tft.fillRect(pixel_positie_int[programma_lijn_positie_int - 1], 50, 20, 20, TFT_BLACK);
              if(commando_min_2_int == IN){
                tft.setCursor(pixel_positie_int[programma_lijn_positie_int - 1], 50);
                if(programma_array_int[programma_lijn_int][programma_lijn_positie_int - 1] > aantal_input_int - 1){
                  tft.setTextColor(TFT_RED);
                  program_error_bool = true;
                }
                else{
                  tft.setTextColor(TFT_WHITE);
                  program_error_bool = false;
                }
                printf_2_int(programma_array_int[programma_lijn_int][programma_lijn_positie_int - 1]);
                tft.print(print_char);
              }
              if(commando_min_2_int == OUT){
                tft.setCursor(pixel_positie_int[programma_lijn_positie_int - 1], 50);
                if(programma_array_int[programma_lijn_int][programma_lijn_positie_int - 1] > aantal_output_int - 1){
                  tft.setTextColor(TFT_RED);
                  program_error_bool = true;
                }
                else{
                  tft.setTextColor(TFT_WHITE);
                  program_error_bool = false;
                }
                printf_2_int(programma_array_int[programma_lijn_int][programma_lijn_positie_int - 1]);
                tft.print(print_char);
              }
              if((commando_min_2_int != IN) || (commando_min_2_int != OUT)){
                tft.setCursor(pixel_positie_int[programma_lijn_positie_int - 1], 50);
                if(programma_array_int[programma_lijn_int][programma_lijn_positie_int - 1] > 63){
                  tft.setTextColor(TFT_RED);
                  program_error_bool = true;
                }
                else{
                  tft.setTextColor(TFT_WHITE);
                  program_error_bool = false;
                }
                printf_2_int(programma_array_int[programma_lijn_int][programma_lijn_positie_int - 1]);
                tft.print(print_char);
              }
            } 
          }
          if(((((key_int >= 0) && (key_int < 10)) || (key_int == LINKS) || (key_int == RECHTS))) && (programma_lijn_positie_int == edit_lijn_positie_int) && (programma_lijn_positie_int > 2)){
            commando_min_1_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int - 1];
            commando_min_2_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int - 2];
            commando_min_3_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int - 3];
            commando_min_4_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int - 4];
            if(commando_min_3_int == PWM){
              if(key_int == LINKS){
                pwm_positie_int = 1;
                tft.drawLine(pixel_positie_int[edit_lijn_positie_int - 1], 70, pixel_positie_int[edit_lijn_positie_int -1] + 20, 70, TFT_BLACK);
                tft.drawLine(pixel_positie_int[edit_lijn_positie_int - 2], 70, pixel_positie_int[edit_lijn_positie_int -2] + 8, 70, TFT_WHITE);
              }
              if(key_int == RECHTS){
                pwm_positie_int = 2;
                tft.drawLine(pixel_positie_int[edit_lijn_positie_int - 2], 70, pixel_positie_int[edit_lijn_positie_int -2] + 8, 70, TFT_BLACK);
                tft.drawLine(pixel_positie_int[edit_lijn_positie_int - 1], 70, pixel_positie_int[edit_lijn_positie_int -1] + 20, 70, TFT_WHITE);
              }
              if(pwm_positie_int == 1){
                if(key_int < 10){
                  programma_array_int[programma_lijn_int][edit_lijn_positie_int - 2] = key_int;
                  tft.setCursor(pixel_positie_int[edit_lijn_positie_int - 2], 50);
                  tft.fillRect(pixel_positie_int[edit_lijn_positie_int - 2], 50, 10, 20, TFT_BLACK);
                  if(key_int > 3){
                    tft.setTextColor(TFT_RED);
                  }
                  tft.print(key_int);
                  tft.setTextColor(TFT_WHITE);
                }
              }
              if(pwm_positie_int == 2){
                if(key_int < 10){
                  int tmp = programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1];
                  tmp = tmp - ((tmp / 100) * 100);
                  tmp = (tmp * 10) + key_int;
                  if(tmp > 100){
                    tft.setTextColor(TFT_RED);
                  }
                  programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1] = tmp;
                  tft.setCursor(pixel_positie_int[edit_lijn_positie_int - 1], 50);
                  tft.fillRect(pixel_positie_int[edit_lijn_positie_int - 1], 50, 30, 20, TFT_BLACK);
                  printf_3_int(programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1]);
                  tft.print(print_char);
                  tft.setTextColor(TFT_WHITE);
                }
              }
            }
            if(commando_min_3_int == PWM_F){
              if(key_int == LINKS){
                pwm_positie_int = 1;
                tft.drawLine(pixel_positie_int[edit_lijn_positie_int - 1], 70, pixel_positie_int[edit_lijn_positie_int -1] + 8, 70, TFT_BLACK);
                tft.drawLine(pixel_positie_int[edit_lijn_positie_int - 2], 70, pixel_positie_int[edit_lijn_positie_int -2] + 8, 70, TFT_WHITE);
              }
              if(key_int == RECHTS){
                pwm_positie_int = 2;
                tft.drawLine(pixel_positie_int[edit_lijn_positie_int - 2], 70, pixel_positie_int[edit_lijn_positie_int -2] + 8, 70, TFT_BLACK);
                tft.drawLine(pixel_positie_int[edit_lijn_positie_int - 1], 70, pixel_positie_int[edit_lijn_positie_int -1] + 8, 70, TFT_WHITE);
              }
              if(pwm_positie_int == 1){
                if(key_int < 10){
                  programma_array_int[programma_lijn_int][edit_lijn_positie_int - 2] = key_int;
                  tft.setCursor(pixel_positie_int[edit_lijn_positie_int - 2], 50);
                  tft.fillRect(pixel_positie_int[edit_lijn_positie_int - 2], 50, 10, 20, TFT_BLACK);
                  if(key_int > 3){
                    tft.setTextColor(TFT_RED);
                  }
                  tft.print(key_int);
                  tft.setTextColor(TFT_WHITE);
                }
              }
              if(pwm_positie_int == 2){
                if(key_int < 10){
                  programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1] = key_int;
                  tft.setCursor(pixel_positie_int[edit_lijn_positie_int - 1], 50);
                  tft.fillRect(pixel_positie_int[edit_lijn_positie_int - 1], 50, 30, 20, TFT_BLACK);
                  if(key_int > 3){
                    tft.setTextColor(TFT_RED);
                  }
                  tft.print(key_int);
                  tft.setTextColor(TFT_WHITE);
                }
              }
            }
            if(((commando_min_3_int == AI_E) ||(commando_min_3_int == AI_G) || (commando_min_3_int == AI_L))){
              if(key_int == LINKS){
                ai_positie_int = 1;
                tft.drawLine(pixel_positie_int[edit_lijn_positie_int - 1], 70, pixel_positie_int[edit_lijn_positie_int -1] + 20, 70, TFT_BLACK);
                tft.drawLine(pixel_positie_int[edit_lijn_positie_int - 2], 70, pixel_positie_int[edit_lijn_positie_int -2] + 8, 70, TFT_WHITE);
              }
              if(key_int == RECHTS){
                ai_positie_int = 2;
                tft.drawLine(pixel_positie_int[edit_lijn_positie_int - 2], 70, pixel_positie_int[edit_lijn_positie_int -2] + 8, 70, TFT_BLACK);
                tft.drawLine(pixel_positie_int[edit_lijn_positie_int - 1], 70, pixel_positie_int[edit_lijn_positie_int -1] + 20, 70, TFT_WHITE);
              }
              if(key_int < 10){
                if(ai_positie_int == 1){
                  programma_array_int[programma_lijn_int][edit_lijn_positie_int - 2] = key_int;
                  tft.setCursor(pixel_positie_int[edit_lijn_positie_int - 2], 50);
                  tft.fillRect(pixel_positie_int[edit_lijn_positie_int - 2], 50, 10, 20, TFT_BLACK);
                  if(key_int > 3){
                    tft.setTextColor(TFT_RED);
                  }
                  tft.print(key_int);
                  tft.setTextColor(TFT_WHITE);
                }
                if(ai_positie_int == 2){
                  int tmp = programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1];
                  tmp = tmp - ((tmp / 100) * 100);
                  tmp = (tmp * 10) + key_int;
                  if(tmp > 100){
                    tft.setTextColor(TFT_RED);
                  }
                  programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1] = tmp;
                  tft.setCursor(pixel_positie_int[edit_lijn_positie_int - 1], 50);
                  tft.fillRect(pixel_positie_int[edit_lijn_positie_int - 1], 50, 30, 20, TFT_BLACK);
                  printf_3_int(programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1]);
                  tft.print(print_char);
                  tft.setTextColor(TFT_WHITE);
                }
                tft.fillRect(200, 50, 329, 20, TFT_BLACK);
                if((programma_array_int[programma_lijn_int][edit_lijn_positie_int - 2] < 4) && (programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1] <= 100)){
                  tft.setCursor(200,50);
                  float nul_waarde_float = ai_array_int[programma_array_int[programma_lijn_int][edit_lijn_positie_int - 2]][0];
                  float max_waarde_float = ai_array_int[programma_array_int[programma_lijn_int][edit_lijn_positie_int - 2]][1];
                  float percent_float = programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1];
                  float tmp_float = (((max_waarde_float - nul_waarde_float) * percent_float) / 100.0) + nul_waarde_float;
                  tft.setTextColor(TFT_YELLOW);
                  tft.print(tmp_float, 2);  
                  tft.setTextColor(TFT_WHITE);         
                }
              }
            }
            if(commando_min_4_int == AI_G_L){
              if(key_int == LINKS){
                ai_positie_int --;
                if(ai_positie_int < 1){
                  ai_positie_int = 1;
                }
              }
              if(key_int == RECHTS){
                ai_positie_int ++;
                if(ai_positie_int > 3){
                  ai_positie_int = 3;
                }
              }
              if(ai_positie_int == 1){
                tft.drawLine(35, 70, 120, 70, TFT_BLACK);
                tft.drawLine(pixel_positie_int[edit_lijn_positie_int - 3], 70, pixel_positie_int[edit_lijn_positie_int -3] + 8, 70, TFT_WHITE);
              }
              if(ai_positie_int == 2){
                tft.drawLine(35, 70, 120, 70, TFT_BLACK);
                tft.drawLine(pixel_positie_int[edit_lijn_positie_int - 2], 70, pixel_positie_int[edit_lijn_positie_int -2] + 20, 70, TFT_WHITE);
              }
              if(ai_positie_int == 3){
                tft.drawLine(35, 70, 120, 70, TFT_BLACK);
                tft.drawLine(pixel_positie_int[edit_lijn_positie_int - 1], 70, pixel_positie_int[edit_lijn_positie_int -1] + 20, 70, TFT_WHITE);
              }
              if(key_int < 10){
                if(ai_positie_int == 1){
                  programma_array_int[programma_lijn_int][edit_lijn_positie_int - 3] = key_int;
                  tft.setCursor(pixel_positie_int[edit_lijn_positie_int - 3], 50);
                  tft.fillRect(pixel_positie_int[edit_lijn_positie_int - 3], 50, 10, 20, TFT_BLACK);
                  if(key_int > 3){
                    tft.setTextColor(TFT_RED);
                  }
                  tft.print(key_int);
                  tft.setTextColor(TFT_WHITE);
                }
                if(ai_positie_int == 2){
                  int tmp = programma_array_int[programma_lijn_int][edit_lijn_positie_int - 2];
                  tmp = tmp - ((tmp / 100) * 100);
                  tmp = (tmp * 10) + key_int;
                  if(tmp > 100){
                    tft.setTextColor(TFT_RED);
                  }
                  programma_array_int[programma_lijn_int][edit_lijn_positie_int - 2] = tmp;
                  tft.setCursor(pixel_positie_int[edit_lijn_positie_int - 2], 50);
                  tft.fillRect(pixel_positie_int[edit_lijn_positie_int - 2], 50, 25, 20, TFT_BLACK);
                  printf_3_int(programma_array_int[programma_lijn_int][edit_lijn_positie_int - 2]);
                  tft.print(print_char);
                  tft.setTextColor(TFT_WHITE);
                }
                if(ai_positie_int == 3){
                  int tmp = programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1];
                  tmp = tmp - ((tmp / 100) * 100);
                  tmp = (tmp * 10) + key_int;
                  if(tmp > 100){
                    tft.setTextColor(TFT_RED);
                  }
                  programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1] = tmp;
                  tft.setCursor(pixel_positie_int[edit_lijn_positie_int - 1], 50);
                  tft.fillRect(pixel_positie_int[edit_lijn_positie_int - 1], 50, 25, 20, TFT_BLACK);
                  printf_3_int(programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1]);
                  tft.print(print_char);
                  tft.setTextColor(TFT_WHITE);
                }
                tft.fillRect(200, 50, 329, 20, TFT_BLACK);
                if((programma_array_int[programma_lijn_int][edit_lijn_positie_int - 3] < 4) && (programma_array_int[programma_lijn_int][edit_lijn_positie_int - 2] <= 100) && (programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1] <= 100)){
                  float nul_waarde_float = ai_array_int[programma_array_int[programma_lijn_int][edit_lijn_positie_int - 3]][0];
                  float max_waarde_float = ai_array_int[programma_array_int[programma_lijn_int][edit_lijn_positie_int - 3]][1];
                  float percent_float = programma_array_int[programma_lijn_int][edit_lijn_positie_int - 2];
                  float tmp_float = (((max_waarde_float - nul_waarde_float) * percent_float) / 100.0) + nul_waarde_float;
                  tft.setTextColor(TFT_YELLOW);
                  tft.setCursor(200,50);
                  tft.print("> ");
                  tft.print(tmp_float, 2);  
                  percent_float = programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1];
                  tmp_float = (((max_waarde_float - nul_waarde_float) * percent_float) / 100.0) + nul_waarde_float;
                  tft.setTextColor(TFT_YELLOW);
                  tft.setCursor(290,50);
                  tft.print("< ");
                  tft.print(tmp_float, 2);  
                  tft.setTextColor(TFT_WHITE);         
                }
              }
              no_key_detect();
              //key_int = 99;
            }
          }
          /*
          EDIT
          */
          if(((key_int >= 0) && (key_int < 10)) && (programma_lijn_positie_int != edit_lijn_positie_int)){
            commando_min_1_int = 0;
            commando_min_2_int = 0;
            if(edit_lijn_positie_int > 0){
              commando_min_1_int = programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1];
            }
            if(edit_lijn_positie_int > 1){
              commando_min_2_int = programma_array_int[programma_lijn_int][edit_lijn_positie_int - 2];
            }
            if(edit_lijn_positie_int > 2){
              commando_min_3_int = programma_array_int[programma_lijn_int][edit_lijn_positie_int - 3];
            }
            if((commando_min_1_int == IN) || (commando_min_1_int == OUT) || (commando_min_1_int == MERKER) || (commando_min_1_int == TMR) || (commando_min_1_int == CTRU) || (commando_min_1_int == CTRD)
                || (commando_min_1_int == TMR_R) || (commando_min_1_int == CTR_R)){
              int nummer_int = programma_array_int[programma_lijn_int][edit_lijn_positie_int];
              int tiental_int = nummer_int / 10;
              int eenheden_int = nummer_int - (tiental_int * 10);
              tiental_int = eenheden_int;
              eenheden_int = key_int;
              programma_array_int[programma_lijn_int][edit_lijn_positie_int] = (tiental_int * 10) + eenheden_int;
              tft.fillRect(pixel_positie_int[edit_lijn_positie_int], 50, 20, 20, TFT_BLACK);
              if(commando_min_1_int == IN){
                tft.setCursor(pixel_positie_int[edit_lijn_positie_int], 50);
                if(programma_array_int[programma_lijn_int][edit_lijn_positie_int] > aantal_input_int - 1){
                  tft.setTextColor(TFT_RED);
                  program_error_bool = true;
                }
                else{
                  tft.setTextColor(TFT_WHITE);
                  program_error_bool = false;
                }
                printf_2_int(programma_array_int[programma_lijn_int][edit_lijn_positie_int]);
                tft.print(print_char);
              }
              if(commando_min_1_int == OUT){
                tft.setCursor(pixel_positie_int[edit_lijn_positie_int], 50);
                if(programma_array_int[programma_lijn_int][edit_lijn_positie_int] > aantal_output_int - 1){
                  tft.setTextColor(TFT_RED);
                  program_error_bool = true;
                }
                else{
                  tft.setTextColor(TFT_WHITE);
                  program_error_bool = false;
                }
                printf_2_int(programma_array_int[programma_lijn_int][edit_lijn_positie_int]);
                tft.print(print_char);
              }
              if(!((commando_min_1_int == OUT) || (commando_min_1_int == IN))){
                tft.setCursor(pixel_positie_int[edit_lijn_positie_int], 50);
                if(programma_array_int[programma_lijn_int][edit_lijn_positie_int] > 63){
                  tft.setTextColor(TFT_RED);
                  program_error_bool = true;
                }
                else{
                  tft.setTextColor(TFT_WHITE);
                  program_error_bool = false;
                }
                printf_2_int(programma_array_int[programma_lijn_int][edit_lijn_positie_int]);
                tft.print(print_char);
              }
            }
            if(commando_min_1_int == PWM){
              if(key_int < 10){
                programma_array_int[programma_lijn_int][edit_lijn_positie_int] = key_int;
                tft.setCursor(pixel_positie_int[edit_lijn_positie_int], 50);
                tft.fillRect(pixel_positie_int[edit_lijn_positie_int], 50, 10, 20, TFT_BLACK);
                if(key_int > 3){
                  tft.setTextColor(TFT_RED);
                }
                tft.print(key_int);
                tft.setTextColor(TFT_WHITE);
              }
            }
            if(edit_lijn_positie_int > 1){
              if(commando_min_2_int == PWM){
                if(key_int < 10){
                  int tmp = programma_array_int[programma_lijn_int][edit_lijn_positie_int];
                  tmp = tmp - ((tmp / 100) * 100);
                  tmp = (tmp * 10) + key_int;
                  if(tmp > 100){
                    tft.setTextColor(TFT_RED);
                  }
                  programma_array_int[programma_lijn_int][edit_lijn_positie_int] = tmp;
                  tft.setCursor(pixel_positie_int[edit_lijn_positie_int], 50);
                  tft.fillRect(pixel_positie_int[edit_lijn_positie_int], 50, 30, 20, TFT_BLACK);
                  printf_3_int(programma_array_int[programma_lijn_int][edit_lijn_positie_int]);
                  tft.print(print_char);
                  tft.setTextColor(TFT_WHITE);
                }
              }
            }
            if(commando_min_1_int == PWM_F){
              if(key_int < 10){
                programma_array_int[programma_lijn_int][edit_lijn_positie_int] = key_int;
                tft.setCursor(pixel_positie_int[edit_lijn_positie_int], 50);
                tft.fillRect(pixel_positie_int[edit_lijn_positie_int], 50, 10, 20, TFT_BLACK);
                if(key_int > 3){
                  tft.setTextColor(TFT_RED);
                }
                tft.print(key_int);
                tft.setTextColor(TFT_WHITE);
              }
            }
            if(edit_lijn_positie_int > 1){
              if(commando_min_2_int == PWM_F){
                if(key_int < 10){
                  programma_array_int[programma_lijn_int][edit_lijn_positie_int] = key_int;
                  tft.setCursor(pixel_positie_int[edit_lijn_positie_int], 50);
                  tft.fillRect(pixel_positie_int[edit_lijn_positie_int], 50, 30, 20, TFT_BLACK);
                  if(key_int > 3){
                    tft.setTextColor(TFT_RED);
                  }
                  tft.print(key_int);
                  tft.setTextColor(TFT_WHITE);
                }
              }
            }
            if((commando_min_1_int == AI_E) || (commando_min_1_int == AI_G) || (commando_min_1_int == AI_L)){
              if(key_int < 10){
                programma_array_int[programma_lijn_int][edit_lijn_positie_int] = key_int;
                tft.setCursor(pixel_positie_int[edit_lijn_positie_int], 50);
                tft.fillRect(pixel_positie_int[edit_lijn_positie_int], 50, 10, 20, TFT_BLACK);
                if(key_int > 3){
                  tft.setTextColor(TFT_RED);
                }
                tft.print(key_int);
                tft.setTextColor(TFT_WHITE);
                tft.fillRect(200, 50, 329, 20, TFT_BLACK);
                if((programma_array_int[programma_lijn_int][edit_lijn_positie_int] < 4) && (programma_array_int[programma_lijn_int][edit_lijn_positie_int + 1] <= 100)){
                  tft.setCursor(200,50);
                  float nul_waarde_float = ai_array_int[programma_array_int[programma_lijn_int][edit_lijn_positie_int]][0];
                  float max_waarde_float = ai_array_int[programma_array_int[programma_lijn_int][edit_lijn_positie_int]][1];
                  float percent_float = programma_array_int[programma_lijn_int][edit_lijn_positie_int + 1];
                  float tmp_float = (((max_waarde_float - nul_waarde_float) * percent_float) / 100.0) + nul_waarde_float;
                  tft.setTextColor(TFT_YELLOW);
                  tft.print(tmp_float, 2);  
                  tft.setTextColor(TFT_WHITE);         
                }
              }
            }
            if(edit_lijn_positie_int > 1){
              if((commando_min_2_int == AI_E) || (commando_min_2_int == AI_G) || (commando_min_2_int == AI_L)){
                if(key_int < 10){
                  int tmp = programma_array_int[programma_lijn_int][edit_lijn_positie_int];
                  tmp = tmp - ((tmp / 100) * 100);
                  tmp = (tmp * 10) + key_int;
                  if(tmp > 100){
                    tft.setTextColor(TFT_RED);
                  }
                  programma_array_int[programma_lijn_int][edit_lijn_positie_int] = tmp;
                  tft.setCursor(pixel_positie_int[edit_lijn_positie_int], 50);
                  tft.fillRect(pixel_positie_int[edit_lijn_positie_int], 50, 25, 20, TFT_BLACK);
                  printf_3_int(programma_array_int[programma_lijn_int][edit_lijn_positie_int]);
                  tft.print(print_char);
                  tft.setTextColor(TFT_WHITE);
                }
                tft.fillRect(200, 50, 329, 20, TFT_BLACK);
                if((programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1] < 4) && (programma_array_int[programma_lijn_int][edit_lijn_positie_int] <= 100)){
                  tft.setCursor(200,50);
                  float nul_waarde_float = ai_array_int[programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1]][0];
                  float max_waarde_float = ai_array_int[programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1]][1];
                  float percent_float = programma_array_int[programma_lijn_int][edit_lijn_positie_int];
                  float tmp_float = (((max_waarde_float - nul_waarde_float) * percent_float) / 100.0) + nul_waarde_float;
                  tft.setTextColor(TFT_YELLOW);
                  tft.print(tmp_float, 2);  
                  tft.setTextColor(TFT_WHITE);         
                }
              }
            }
            if(commando_min_1_int == AI_G_L){
              if(key_int < 10){
                programma_array_int[programma_lijn_int][edit_lijn_positie_int] = key_int;
                tft.setCursor(pixel_positie_int[edit_lijn_positie_int], 50);
                tft.fillRect(pixel_positie_int[edit_lijn_positie_int], 50, 10, 20, TFT_BLACK);
                if(key_int > 3){
                  tft.setTextColor(TFT_RED);
                }
                tft.print(key_int);
                tft.setTextColor(TFT_WHITE);
                tft.fillRect(200, 50, 329, 20, TFT_BLACK);
                if((programma_array_int[programma_lijn_int][edit_lijn_positie_int] < 4) && (programma_array_int[programma_lijn_int][edit_lijn_positie_int + 1] <= 100) && (programma_array_int[programma_lijn_int][edit_lijn_positie_int + 2] <= 100)){
                  float nul_waarde_float = ai_array_int[programma_array_int[programma_lijn_int][edit_lijn_positie_int]][0];
                  float max_waarde_float = ai_array_int[programma_array_int[programma_lijn_int][edit_lijn_positie_int]][1];
                  float percent_float = programma_array_int[programma_lijn_int][edit_lijn_positie_int + 1];
                  float tmp_float = (((max_waarde_float - nul_waarde_float) * percent_float) / 100.0) + nul_waarde_float;
                  tft.setTextColor(TFT_YELLOW);
                  tft.setCursor(200,50);
                  tft.print("> ");
                  tft.print(tmp_float, 2);  
                  percent_float = programma_array_int[programma_lijn_int][edit_lijn_positie_int + 2];
                  tmp_float = (((max_waarde_float - nul_waarde_float) * percent_float) / 100.0) + nul_waarde_float;
                  tft.setTextColor(TFT_YELLOW);
                  tft.setCursor(290,50);
                  tft.print("< ");
                  tft.print(tmp_float, 2);  
                  tft.setTextColor(TFT_WHITE);         
                }
              }
            }
            if(edit_lijn_positie_int > 1){
              if(commando_min_2_int == AI_G_L){
                if(key_int < 10){
                  int tmp = programma_array_int[programma_lijn_int][edit_lijn_positie_int];
                  tmp = tmp - ((tmp / 100) * 100);
                  tmp = (tmp * 10) + key_int;
                  if(tmp > 100){
                    tft.setTextColor(TFT_RED);
                  }
                  programma_array_int[programma_lijn_int][edit_lijn_positie_int] = tmp;
                  tft.setCursor(pixel_positie_int[edit_lijn_positie_int], 50);
                  tft.fillRect(pixel_positie_int[edit_lijn_positie_int], 50, 25, 20, TFT_BLACK);
                  printf_3_int(programma_array_int[programma_lijn_int][edit_lijn_positie_int]);
                  tft.print(print_char);
                  tft.setTextColor(TFT_WHITE);
                }
                tft.fillRect(200, 50, 329, 20, TFT_BLACK);
                if((programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1] < 4) && (programma_array_int[programma_lijn_int][edit_lijn_positie_int] <= 100) && (programma_array_int[programma_lijn_int][edit_lijn_positie_int + 1] <= 100)){
                  float nul_waarde_float = ai_array_int[programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1]][0];
                  float max_waarde_float = ai_array_int[programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1]][1];
                  float percent_float = programma_array_int[programma_lijn_int][edit_lijn_positie_int];
                  float tmp_float = (((max_waarde_float - nul_waarde_float) * percent_float) / 100.0) + nul_waarde_float;
                  tft.setTextColor(TFT_YELLOW);
                  tft.setCursor(200,50);
                  tft.print("> ");
                  tft.print(tmp_float, 2);  
                  percent_float = programma_array_int[programma_lijn_int][edit_lijn_positie_int + 1];
                  tmp_float = (((max_waarde_float - nul_waarde_float) * percent_float) / 100.0) + nul_waarde_float;
                  tft.setTextColor(TFT_YELLOW);
                  tft.setCursor(290,50);
                  tft.print("< ");
                  tft.print(tmp_float, 2);  
                  tft.setTextColor(TFT_WHITE);         
                }
              }
            }
            if(edit_lijn_positie_int > 2){
              if(commando_min_3_int == AI_G_L){
                if(key_int < 10){
                  int tmp = programma_array_int[programma_lijn_int][edit_lijn_positie_int];
                  tmp = tmp - ((tmp / 100) * 100);
                  tmp = (tmp * 10) + key_int;
                  if(tmp > 100){
                    tft.setTextColor(TFT_RED);
                  }
                  programma_array_int[programma_lijn_int][edit_lijn_positie_int] = tmp;
                  tft.setCursor(pixel_positie_int[edit_lijn_positie_int], 50);
                  tft.fillRect(pixel_positie_int[edit_lijn_positie_int], 50, 25, 20, TFT_BLACK);
                  printf_3_int(programma_array_int[programma_lijn_int][edit_lijn_positie_int]);
                  tft.print(print_char);
                  tft.setTextColor(TFT_WHITE);
                }
                tft.fillRect(200, 50, 329, 20, TFT_BLACK);
                if((programma_array_int[programma_lijn_int][edit_lijn_positie_int - 2] < 4) && (programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1] <= 100) && (programma_array_int[programma_lijn_int][edit_lijn_positie_int] <= 100)){
                  float nul_waarde_float = ai_array_int[programma_array_int[programma_lijn_int][edit_lijn_positie_int - 2]][0];
                  float max_waarde_float = ai_array_int[programma_array_int[programma_lijn_int][edit_lijn_positie_int - 2]][1];
                  float percent_float = programma_array_int[programma_lijn_int][edit_lijn_positie_int - 1];
                  float tmp_float = (((max_waarde_float - nul_waarde_float) * percent_float) / 100.0) + nul_waarde_float;
                  tft.setTextColor(TFT_YELLOW);
                  tft.setCursor(200,50);
                  tft.print("> ");
                  tft.print(tmp_float, 2);  
                  percent_float = programma_array_int[programma_lijn_int][edit_lijn_positie_int];
                  tmp_float = (((max_waarde_float - nul_waarde_float) * percent_float) / 100.0) + nul_waarde_float;
                  tft.setTextColor(TFT_YELLOW);
                  tft.setCursor(290,50);
                  tft.print("< ");
                  tft.print(tmp_float, 2);  
                  tft.setTextColor(TFT_WHITE);         
                }
              }
            }
          }
          if(key_int == ESC){
            programmeren_bool = false;
            keuze_bool = true;
          }
          no_key_detect();
          //key_int = 99;
        }
      }
    }
    /*
    PWM AI INSTELLEN
    */
    if((pwm_instellen_bool) && (!digitalRead(PROG_RUN))){
      tft.setTextFont(4);
      tft.setCursor(((480 - tft.textWidth("PWM / AI instellen", 4)) / 2), 20);
      tft.print("PWM / AI instellen");
      tft.setTextFont(2);
      tft.setCursor(((480 - tft.textWidth("Druk < Esc > om te eindigen", 2)) / 2), 50);
      tft.print("Druk < Esc > om te eindigen");
      cursor_positie_bool = false;
      for(int x = 0; x < 8; x ++){
        if(x < 4){
          tft.setCursor(pwm_hor_int[x][0], pwm_hor_int[x][1]);
          tft.print("PWM_");
          tft.print(x);
          tft.setCursor(pwm_hor_int[x][0] + 75, pwm_hor_int[x][1]);
          printf_5_int(freq_array_int[x]);
          tft.print(print_char);
          tft.print("   Hz");
        }
        else{
          tft.setCursor(pwm_hor_int[x][0], pwm_hor_int[x][1]);
          tft.print("AI_");
          tft.print(x - 4);
          tft.setCursor(pwm_hor_int[x][0] + 75, pwm_hor_int[x][1]);
          printf_4_int(ai_array_int[x - 4][0]);
          tft.print(print_char);
          tft.setCursor(pwm_hor_int[x][0] + 140, pwm_hor_int[x][1]);
          printf_4_int(ai_array_int[x - 4][1]);
          tft.print(print_char);
        }
      }
      pwm_instellen_int = 0;
      plaats_ster_pwm();
      while((pwm_instellen_bool) && (!digitalRead(PROG_RUN))){
        keyboard_scan();
        if(key_int == ESC){
          pwm_instellen_bool = false;
          keuze_bool = true;
          no_key_detect();
        }
        if(key_int == OP){
          cursor_positie_bool = false;
          tft.fillRect(0, 70, 480, 240, TFT_BLACK );
          for(int x = 0; x < 8; x ++){
            if(x < 4){
              tft.setCursor(pwm_hor_int[x][0], pwm_hor_int[x][1]);
              tft.print("PWM_");
              tft.print(x);
              tft.setCursor(pwm_hor_int[x][0] + 75, pwm_hor_int[x][1]);
              printf_5_int(freq_array_int[x]);
              tft.print(print_char);
              tft.print("   Hz");
            }
            else{
              tft.setCursor(pwm_hor_int[x][0], pwm_hor_int[x][1]);
              tft.print("AI_");
              tft.print(x - 4);
              tft.setCursor(pwm_hor_int[x][0] + 75, pwm_hor_int[x][1]);
              printf_4_int(ai_array_int[x - 4][0]);
              tft.print(print_char);
              tft.setCursor(pwm_hor_int[x][0] + 140, pwm_hor_int[x][1]);
              printf_4_int(ai_array_int[x - 4][1]);
              tft.print(print_char);
            }
          }
          pwm_instellen_int --;
          if(pwm_instellen_int < 4){
            tft.drawLine(pwm_hor_int[pwm_instellen_int][0], pwm_hor_int[pwm_instellen_int][1] + 18, pwm_hor_int[pwm_instellen_int][0] + 300, pwm_hor_int[pwm_instellen_int][1] + 18, TFT_BLACK);
          }
          if(pwm_instellen_int > 3){
            ai_onderlijn();
          }
          if(pwm_instellen_int < 0){
            pwm_instellen_int = 0;
          }
          plaats_ster_pwm();
          no_key_detect();
        }
        if(key_int == NEER){
          cursor_positie_bool = false;
          tft.fillRect(0, 70, 480, 240, TFT_BLACK );
          for(int x = 0; x < 8; x ++){
            if(x < 4){
              tft.setCursor(pwm_hor_int[x][0], pwm_hor_int[x][1]);
              tft.print("PWM_");
              tft.print(x);
              tft.setCursor(pwm_hor_int[x][0] + 75, pwm_hor_int[x][1]);
              printf_5_int(freq_array_int[x]);
              tft.print(print_char);
              tft.print("   Hz");
            }
            else{
              tft.setCursor(pwm_hor_int[x][0], pwm_hor_int[x][1]);
              tft.print("AI_");
              tft.print(x - 4);
              tft.setCursor(pwm_hor_int[x][0] + 75, pwm_hor_int[x][1]);
              printf_4_int(ai_array_int[x - 4][0]);
              tft.print(print_char);
              tft.setCursor(pwm_hor_int[x][0] + 140, pwm_hor_int[x][1]);
              printf_4_int(ai_array_int[x - 4][1]);
              tft.print(print_char);
            }
          }
          pwm_instellen_int ++;
          if(pwm_instellen_int < 4){
            tft.drawLine(pwm_hor_int[pwm_instellen_int][0], pwm_hor_int[pwm_instellen_int][1] + 17, pwm_hor_int[pwm_instellen_int][0] + 300, pwm_hor_int[pwm_instellen_int][1] + 17, TFT_BLACK);
          }
          if(pwm_instellen_int > 3){
            ai_onderlijn();
          }
          if(pwm_instellen_int > 7){
            pwm_instellen_int = 7;
          }
          plaats_ster_pwm();
          no_key_detect();
        }
        if(((key_int >= 0) && (key_int < 10)) || (key_int == LINKS) || (key_int == RECHTS)){
          if((key_int == LINKS) && (pwm_instellen_int > 3)){
            cursor_positie_bool = false;
          }
          if((key_int == RECHTS) && (pwm_instellen_int > 3)){
            cursor_positie_bool = true;
          }
          if(pwm_instellen_int < 4){
            if((key_int >= 0) && (key_int < 10)){
              tft.fillRect(pwm_hor_int[pwm_instellen_int][0] + 75, pwm_hor_int[pwm_instellen_int][1], 75, 15, TFT_BLACK);
              tft.setCursor(pwm_hor_int[pwm_instellen_int][0] + 75, pwm_hor_int[pwm_instellen_int][1]);
              links_freq(freq_array_int[pwm_instellen_int], pwm_instellen_int);
              tft.print(print_char);
              tft.print("   Hz");
            }
          }
          else{
            ai_onderlijn();
            if((key_int >= 0) && (key_int < 10)){
              if(!cursor_positie_bool){
                tft.fillRect(pwm_hor_int[pwm_instellen_int][0] + 75, pwm_hor_int[pwm_instellen_int][1], 35, 15, TFT_BLACK);
                links_ai();
                tft.setCursor(pwm_hor_int[pwm_instellen_int][0] + 75, pwm_hor_int[pwm_instellen_int][1]);
                tft.print(print_char);
              }
              if(cursor_positie_bool){
                tft.fillRect(pwm_hor_int[pwm_instellen_int][0] + 140, pwm_hor_int[pwm_instellen_int][1], 55, 15, TFT_BLACK);
                links_ai();
                tft.setCursor(pwm_hor_int[pwm_instellen_int][0] + 140, pwm_hor_int[pwm_instellen_int][1]);
                tft.print(print_char);
              }
            }
          }
          no_key_detect();
        }
      }
    }
    /*
    TIMER INSTELLEN
    */
    if((tmr_instellen_bool) && (!digitalRead(PROG_RUN))){
      tft.setTextFont(4);
      tft.setCursor(((480 - tft.textWidth("TMR's instellen", 4)) / 2), 20);
      tft.print("TMR's instellen");
      tft.setTextFont(2);
      tft.setCursor(5, 20);
      tft.print("<<<");
      tft.setCursor(455, 20);
      tft.print(">>>");
      tft.setCursor(((480 - tft.textWidth("Druk < Ent > om te bevestigen < Esc > om te eindigen", 2)) / 2), 45);
      tft.print("Druk < Ent > om te bevestigen < Esc > om te eindigen");
      touched_bool = false;
      tmr_ctr_pag_int = 0;
      tmr_instellen_int = 0;
      print_tmr_pag();
      while((tmr_instellen_bool) && (!digitalRead(PROG_RUN))){
        touch();
        if(touched_bool){
          for(int x = 0; x < 2; x ++){
            if((x_touch_int >= tmr_ctr_coor_int[x][0]) && (x_touch_int <= tmr_ctr_coor_int[x][1]) && (y_touch_int >= tmr_ctr_coor_int[x][2]) && (y_touch_int <= tmr_ctr_coor_int[x][3])){
              pag_keuze_int = x;
            }
          }
          touched_bool = false;
          switch(pag_keuze_int){
            case 0:
              tmr_ctr_pag_int --;
              if(tmr_ctr_pag_int < 0){
                tmr_ctr_pag_int = 0;
              }
              tmr_instellen_int = 0;
              print_tmr_pag();
              break;
            case 1:
              tmr_ctr_pag_int ++;
              if(tmr_ctr_pag_int > 3){
                tmr_ctr_pag_int = 3;
              }
              tmr_instellen_int = 0;
              print_tmr_pag();
          }
        }
        keyboard_scan();
        if(key_int == ESC){
          tmr_instellen_bool = false;
          keuze_bool = true;
          no_key_detect();
        }
        if(key_int == OP){
          tmr_instellen_int --;
          if(tmr_instellen_int < 0){
            tmr_instellen_int = 0;
          }
          print_tmr_pag();
          tijd_instellen_int = 0;
          onderlijn();
          no_key_detect();
        }
        if(key_int == NEER){
          tmr_instellen_int ++;
          if(tmr_instellen_int > 15){
            tmr_instellen_int = 15;
          }
          print_tmr_pag();
          tijd_instellen_int = 0;
          onderlijn();
          no_key_detect();
        }
        if(key_int == LINKS){
          tijd_instellen_int --;
          if(tijd_instellen_int < 0){
            tijd_instellen_int = 0;
          }
          onderlijn();
          no_key_detect();
        }
        if(key_int == RECHTS){
          tijd_instellen_int ++;
          if(tijd_instellen_int > 3){
            tijd_instellen_int = 3;
          }
          onderlijn();
          no_key_detect();
        }
        if((key_int >= 0) && (key_int < 10)){
          tft.fillRect(tmr_ctr_hor_int[tmr_instellen_int][0] + 75, tmr_ctr_hor_int[tmr_instellen_int][1], 75, 15, TFT_BLACK);
          tft.setCursor(tmr_ctr_hor_int[tmr_instellen_int][0] + 75, tmr_ctr_hor_int[tmr_instellen_int][1]);
          tijd_naar_array();
          memset(print_char, 0, sizeof(print_char));
          switch(tijd_instellen_int){
            case 0:
              links_uren();
              uren_int = (uren_array[1] * 10) + uren_array[0];
              tft.setCursor(tmr_ctr_hor_int[tmr_instellen_int][0] + 75, tmr_ctr_hor_int[tmr_instellen_int][1]);
              array_naar_tijd();
              sprintf(print_char, "%02d:%02d:%02d:%02d", uren_int, minuten_int, seconden_int, hondersten_int);
              tft.print(print_char);
              onderlijn();
              break;
            case 1:
              links_minuten();
              minuten_int = (minuten_array[1] * 10) + minuten_array[0];
              tft.setCursor(tmr_ctr_hor_int[tmr_instellen_int][0] + 75, tmr_ctr_hor_int[tmr_instellen_int][1]);
              array_naar_tijd();
              sprintf(print_char, "%02d:%02d:%02d:%02d", uren_int, minuten_int, seconden_int, hondersten_int);
              tft.print(print_char);
              onderlijn();
              break;
            case 2:
              links_seconden();
              seconden_int = (seconden_array[1] * 10) + seconden_array[0];
              tft.setCursor(tmr_ctr_hor_int[tmr_instellen_int][0] + 75, tmr_ctr_hor_int[tmr_instellen_int][1]);
              array_naar_tijd();
              sprintf(print_char, "%02d:%02d:%02d:%02d", uren_int, minuten_int, seconden_int, hondersten_int);
              tft.print(print_char);
              onderlijn();
              break;
            case 3:
              links_hondersten();
              hondersten_int = (hondersten_array[1] * 10) + hondersten_array[0];
              tft.setCursor(tmr_ctr_hor_int[tmr_instellen_int][0] + 75, tmr_ctr_hor_int[tmr_instellen_int][1]);
              array_naar_tijd();
              sprintf(print_char, "%02d:%02d:%02d:%02d", uren_int, minuten_int, seconden_int, hondersten_int);
              tft.print(print_char);
              onderlijn();
              break;
          }
          no_key_detect();
        }
        if(key_int == ENT){
          if((minuten_int < 60) && (seconden_int < 60)){
            bereken_tienden();
          }
          print_tmr_pag();
          onderlijn();
          plaats_ster_tmr();
          no_key_detect();
        }
      }
    }
    /*
    CTR INSTELLEN
    */
    if((ctr_instellen_bool)  && (!digitalRead(PROG_RUN))){
      tft.setTextFont(4);
      tft.setCursor(((480 - tft.textWidth("CTR's instellen", 4)) / 2), 20);
      tft.print("CTR's instellen");
      tft.setTextFont(2);
      tft.setCursor(5, 20);
      tft.print("<<<");
      tft.setCursor(455, 20);
      tft.print(">>>");
      tft.setCursor(((480 - tft.textWidth("Druk < Esc > om te eindigen", 2)) / 2), 45);
      tft.print("Druk < Esc > om te eindigen");
      touched_bool = false;
      tmr_ctr_pag_int = 0;
      ctr_instellen_int = 0;
      print_ctr_pag();
      while((ctr_instellen_bool) && (!digitalRead(PROG_RUN))){
        touch();
        if(touched_bool){
          for(int x = 0; x < 2; x ++){
            if((x_touch_int >= tmr_ctr_coor_int[x][0]) && (x_touch_int <= tmr_ctr_coor_int[x][1]) && (y_touch_int >= tmr_ctr_coor_int[x][2]) && (y_touch_int <= tmr_ctr_coor_int[x][3])){
              pag_keuze_int = x;
            }
          }
          touched_bool = false;
          switch(pag_keuze_int){
            case 0:
              tmr_ctr_pag_int --;
              if(tmr_ctr_pag_int < 0){
                tmr_ctr_pag_int = 0;
              }
              ctr_instellen_int = 0;
              print_ctr_pag();
              break;
            case 1:
              tmr_ctr_pag_int ++;
              if(tmr_ctr_pag_int > 3){
                tmr_ctr_pag_int = 3;
              }
              ctr_instellen_int = 0;
              print_ctr_pag();
          }
          
        }
        keyboard_scan();
        if(key_int == ESC){
          ctr_instellen_bool = false;
          keuze_bool = true;
          no_key_detect();
        }
        if(key_int == OP){
          ctr_instellen_int --;
          if(ctr_instellen_int < 0){
            ctr_instellen_int = 0;
          }
          plaats_ster_ctr();
          no_key_detect();
        }
        if(key_int == NEER){
          ctr_instellen_int ++;
          if(ctr_instellen_int > 15){
            ctr_instellen_int = 15;
          }
          plaats_ster_ctr();
          no_key_detect();
        }
        if((key_int >= 0) && (key_int < 10)){
          shift_left_ctr();
          tft.fillRect(tmr_ctr_hor_int[ctr_instellen_int][0] + 75, tmr_ctr_hor_int[ctr_instellen_int][1], 40, 20, TFT_BLACK);
          tft.setCursor(tmr_ctr_hor_int[ctr_instellen_int][0] + 75, tmr_ctr_hor_int[ctr_instellen_int][1]);
          tft.print(ctr_instelling_int[(tmr_ctr_pag_int * 16) + ctr_instellen_int]);
          no_key_detect();
        }
      }
    }
    /*
    NAAR FLASH SCHRIJVEN
    */
    if((prog_flash_bool) && (!digitalRead(PROG_RUN))){
      flash_keuzemenu();
      flash_keuze_bool = true;
      flash_schrijven_bool = false;
      flash_lezen_bool = false;
      while((flash_keuze_bool) && (!digitalRead(PROG_RUN))){
        keyboard_scan();
        if(key_int == ESC){
          flash_keuze_bool = false;
          no_key_detect();
        }
        touched_bool = false;
        while((!touched_bool) && (flash_keuze_bool) && (!digitalRead(PROG_RUN))){
          touch();
          keyboard_scan();
          if(key_int == ESC){
            flash_keuze_bool = false;
            no_key_detect();
          }
        }
        for(int flash_keuze_int = 0; flash_keuze_int < 2; flash_keuze_int++){
          if((y_touch_int >= keuzemenu_hor_int[flash_keuze_int]) && (y_touch_int <= keuzemenu_hor_int[flash_keuze_int] + 25)){
            switch(flash_keuze_int){
              case 0:
                flash_schrijven_bool = true;
                flash_lezen_bool = false;
                flash_keuze_bool = false;
                break;
              case 1:
                flash_lezen_bool = true;
                flash_schrijven_bool = false;
                flash_keuze_bool = false;
                break;
            }
          }
        }
      }
      if(flash_schrijven_bool){
        tft.fillScreen(TFT_BLACK);
        tft.setTextFont(2);
        tft.setCursor(((480 - tft.textWidth("Flash schrijven", 2)) / 2), 20);
        tft.print("Flash schrijven");
        tft.setCursor(((480 - tft.textWidth("Druk < Ent > om schrijven te starten < Esc > om te eindigen", 2)) / 2), 50);
        tft.print("Druk < Ent > om schrijven te starten < Esc > om te eindigen");
        bool test_bool = true;
        bool schrijf_bool = false;
        while(test_bool){
          keyboard_scan();
          if(key_int == ESC){
            flash_schrijven_bool = false;
            keuze_bool = true;
            test_bool = false;  
            no_key_detect();
          }
          if(key_int == ENT){
            schrijf_bool = true;
            test_bool = false;  
            no_key_detect();
            tft.fillRect(0, 50, 479, 20, TFT_BLACK);
          }
        }
        if(schrijf_bool){
          print_flash_adres_bool = true;
          schrijf_instellingen();
          schrijf_programma();
          EEPROM.commit();
          tft.fillRect(0, 40, 479, 10, TFT_BLACK);
          tft.setCursor(((480 - tft.textWidth("Druk < Esc > om verder te gaan", 2)) / 2), 50);
          tft.print("Druk < Esc > om verder te gaan");
          while(flash_schrijven_bool){
            keyboard_scan();
            if(key_int == ESC){
              flash_schrijven_bool = false;
              prog_flash_bool = false;
              keuze_bool = true;
              no_key_detect();  
            }
          }
        }
      }
      /*
      FLASH LEZEN
      */
      if(flash_lezen_bool){ 
        tft.fillScreen(TFT_BLACK);
        tft.setCursor(((480 - tft.textWidth("Flash lezen", 2)) / 2), 20);
        tft.print("Flash lezen");
        tft.setCursor(((480 - tft.textWidth("Druk < Ent > om lezen te starten < Esc > om te eindigen", 2)) / 2), 50);
        tft.print("Druk < Ent > om lezen te starten < Esc > om te eindigen");
        bool test_bool = true;
        bool lees_bool = false;
        while(test_bool){
          keyboard_scan();
          if(key_int == ESC){
            flash_lezen_bool = false;
            keuze_bool = true;
            test_bool = false;  
            no_key_detect();
          }
          if(key_int == ENT){
            lees_bool = true;
            test_bool = false;  
            no_key_detect();
            tft.fillRect(0, 50, 479, 20, TFT_BLACK);
          }
        }
        if(lees_bool){
          totaal_reset();
          print_flash_adres_bool = true;
          lees_instellingen();
          lees_programma();
          bereken_programma_lengte();
          tft.fillRect(0, 40, 479, 10, TFT_BLACK);
          tft.setCursor(((480 - tft.textWidth("Druk < Esc > om verder te gaan", 2)) / 2), 50);
          tft.print("Druk < Esc > om verder te gaan");
          while(lees_bool){
            keyboard_scan();
            if(key_int == ESC){
              flash_lezen_bool = false;
              prog_flash_bool = false;
              lees_bool = false;
              keuze_bool = true;
              no_key_detect();  
            }
          }
        }
      }
    }
    /*
    PROGRAMMA PRINTEN
    */
    if((programma_printen_bool) && (!digitalRead(PROG_RUN))){
      tft.setTextFont(4);
      tft.setCursor(((480 - tft.textWidth("Programma printen", 4)) / 2), 20);
      tft.print("Programma printen");
      tft.setTextFont(2);
      tft.setCursor(((480 - tft.textWidth("Druk < Ent > om printen te starten < Esc > om te eindigen", 2)) / 2), 50);
      tft.print("Druk < Ent > om printen te starten < Esc > om te eindigen");
      bool test_bool = true;
      bool print_bool = false;
      bereken_programma_lengte();

      while(test_bool){
        keyboard_scan();
        if(key_int == ESC){
          programma_printen_bool = false;
          keuze_bool = true;
          test_bool = false;  
          no_key_detect();
        }
        if(key_int == ENT){
          print_bool = true;
          test_bool = false;  
          no_key_detect();
          tft.fillRect(0, 50, 479, 20, TFT_BLACK);
        }
      }
      if(print_bool){
        Serial.println();
        Serial.println();
        Serial.print("Programma gebruikt: ");
        Serial.print(programma_lengte_int);
        Serial.print(" bytes van de 16000 beschikbare bytes");
        Serial.println();
        Serial.println();
        int x;
        int y;
        int temp[3];
        for(x = 0; x < MAX_LINE; x ++){
          if(programma_array_int[x][0] == 0xff){
            Serial.println();
            break;
          }
          memset(print_char, 0, sizeof(print_char));
          sprintf(print_char, "%04d      ", x);
          Serial.print(print_char);
          for(y = 0; y < MAX_INST + 1; y ++){
            commando_int = programma_array_int[x][y];
            if(commando_int == 0xff){
              Serial.println();
              break;
            }
            if(commando_int >= 200){
              commando_int -= 200;
              Serial.print(commando_string[commando_int]);
              Serial.print(" ");
            }
            else{
              Serial.print(commando_int);
              Serial.print(" ");
            }
          }
        }
        Serial.println();
        Serial.println();
        Serial.print("Aantal inputs:       ");
        Serial.println(aantal_input_int);
        Serial.print("Aantal outputs:     ");
        Serial.println(aantal_output_int);
        Serial.println();
        Serial.println();
        Serial.print("Cyclustijd:     ");
        Serial.print(cyclustijd_int);
        Serial.println("  microseconden");
        Serial.println();
        Serial.println();
        for(int x = 0; x < 4; x++){
          Serial.print("PWM");
          Serial.print(x);
          Serial.print("    ");
          Serial.print(freq_array_int[x]);
          Serial.print("  Hz");
          Serial.println();
        }
        Serial.println();
        Serial.println();
        for(int x = 0; x < 4; x++){
          Serial.print("AI");
          Serial.print(x);
          Serial.print("    ");
          Serial.print(ai_array_int[x][0]);
          Serial.print("    ");
          Serial.print(ai_array_int[x][1]);
          Serial.println();
        }
        Serial.println();
        Serial.println();
        for(int x = 0; x < 64; x++){
          Serial.print("TMR");
          Serial.print(x);
          Serial.print("    ");
          bereken_tijd(x);
          Serial.print(print_char);
          Serial.println();
        }
        Serial.println();
        Serial.println();
        for(int x = 0; x < 64; x++){
          Serial.print("CTR");
          Serial.print(x);
          Serial.print("    ");
          Serial.print(ctr_instelling_int[x]);
          Serial.println();
        }
        Serial.println();
        Serial.println();
      }
    }
    /*
    PROGRAMMA WISSEN
    */
    if( (programma_wissen_bool)  && (!digitalRead(PROG_RUN))){
      tft.setTextFont(4);
      tft.setCursor(((480 - tft.textWidth("Programma wissen", 4)) / 2), 20);
      tft.print("Programma wissen");
      tft.setTextFont(2);
      tft.setCursor(((480 - tft.textWidth("Druk < Ent > om wissen te starten < Esc > om te eindigen", 2)) / 2), 50);
      tft.print("Druk < Ent > om wissen te starten < Esc > om te eindigen");
      bool test_bool = true;
      bool wis_bool = false;
      while(test_bool){
        keyboard_scan();
        if(key_int == ESC){
          programma_wissen_bool = false;
          keuze_bool = true;
          test_bool = false;  
          no_key_detect();
        }
        if(key_int == ENT){
          wis_bool = true;
          test_bool = false;  
          no_key_detect();
          tft.fillRect(0, 50, 479, 20, TFT_BLACK);
        }
      }
      if(wis_bool){
        totaal_reset();
        programma_lengte_int = 0;
      }
      tft.setCursor(((480 - tft.textWidth("Druk < Esc > om verder te gaan", 2)) / 2), 50);
      tft.print("Druk < Esc > om verder te gaan");
      while(wis_bool){
        keyboard_scan();
        if(key_int == ESC){
          programma_wissen_bool = false;
          wis_bool = false;
          keuze_bool = true;
          no_key_detect();  
        }
      }
    }
    /*
    AANTAL IN OUT CYCLUSTIJD
    */
    if((aantal_in_out_kiezen_bool)  && (!digitalRead(PROG_RUN))){
      bool input_ok_bool = true;
      bool output_ok_bool = true;
      int begin_input_int = aantal_input_int;
      int begin_output_int = aantal_output_int;
      int tmp_cyclustijd_int = cyclustijd_int;
      tft.setTextFont(4);
      tft.setCursor(((480 - tft.textWidth("Inputs  Outputs  Cyclustijd", 4)) / 2), 20);
      tft.print("Inputs  Outputs  Cyclustijd");
      tft.setTextFont(2);
      tft.setCursor(((480 - tft.textWidth("Bevestig met < Ent >  < Esc > om te eindigen zonder aanpassingen", 2)) / 2), 50);
      tft.print("Bevestig met < Ent >  < Esc > om te eindigen zonder aanpassingen");
      print_in_out();
      in_out_instellen_int = 0;
      plaats_ster_in_out();
      while((aantal_in_out_kiezen_bool) && (!digitalRead(PROG_RUN))){
        keyboard_scan();
        if(key_int == ENT){
          tft.setCursor(((480 - tft.textWidth("Veranderingen worden weggeschreven", 2)) / 2), 70);
          tft.print("Veranderingen worden weggeschreven");
          aantal_in_out_kiezen_bool = false;
          if(!((aantal_input_int == 16) || (aantal_input_int == 32) || (aantal_input_int == 48) || (aantal_input_int == 64))){
            aantal_input_int = begin_input_int;
            input_ok_bool = false;
          }
          if(!((aantal_output_int == 16) || (aantal_output_int == 32) || (aantal_output_int == 48) || (aantal_output_int == 64))){
            aantal_output_int = begin_output_int;
            output_ok_bool = false;
          }
          if((tmp_cyclustijd_int >= 10000) && (tmp_cyclustijd_int <= 100000)){
            cyclustijd_int = tmp_cyclustijd_int;
            timer_int = cyclustijd_int / 1000;
            ITimer0.attachInterruptInterval(cyclustijd_int, TimerHandler0);   
          }
          if((input_ok_bool) && (output_ok_bool)){
            print_flash_adres_bool = false;
            schrijf_instellingen();
            EEPROM.commit();
          }
          no_key_detect();
        }
        if(key_int == ESC){
          aantal_in_out_kiezen_bool = false;
          no_key_detect();
        }
        if(key_int == OP){
          tmp_cyclustijd_int = cyclustijd_int;
          tft.fillRect(0, 100, 480, 200, TFT_BLACK );
          print_in_out();
          in_out_instellen_int --;
          if(in_out_instellen_int < 0){
            in_out_instellen_int = 0;
          }
          plaats_ster_in_out();
          no_key_detect();
        }
        if(key_int == NEER){
          tmp_cyclustijd_int = cyclustijd_int;
          tft.fillRect(0, 100, 480,220, TFT_BLACK );
          print_in_out();
          in_out_instellen_int ++;
          if(in_out_instellen_int > 2){
            in_out_instellen_int = 2;
          }
          plaats_ster_in_out();
          no_key_detect();
        }
        if((key_int >= 0) && (key_int < 10)){
          int temp;
          if(in_out_instellen_int < 2){
            if(in_out_instellen_int == 0){
            tft.fillRect(in_out_hor_int[0][0] + 120, in_out_hor_int[0][1], 120, 15, TFT_BLACK);
            tft.setCursor(in_out_hor_int[0][0] + 120, in_out_hor_int[0][1]);
            temp = aantal_input_int;
            }
            if(in_out_instellen_int == 1){
            tft.fillRect(in_out_hor_int[1][0] + 120, in_out_hor_int[1][1], 120, 15, TFT_BLACK);
            tft.setCursor(in_out_hor_int[1][0] + 120, in_out_hor_int[1][1]);
            temp = aantal_output_int;
            }
            temp = temp - ((temp / 10) * 10);
            temp = (temp * 10) + key_int;
            if(in_out_instellen_int == 0){
              aantal_input_int = temp;
            }
            else{
              aantal_output_int = temp;
            }
            if(!((temp == 16) || (temp == 32) || (temp == 48) || (temp == 64))){
              tft.setTextColor(TFT_RED);
            }
            if(in_out_instellen_int == 0){
              tft.setCursor(in_out_hor_int[0][0] + 120, in_out_hor_int[0][1]);
            }
            else{
              tft.setCursor(in_out_hor_int[1][0] + 120, in_out_hor_int[1][1]);
            }
            tft.print(temp);
          }
          if(in_out_instellen_int == 2){
            int honderd = tmp_cyclustijd_int / 100000;
            int tien = (tmp_cyclustijd_int - (honderd * 100000)) / 10000;
            int een =  (tmp_cyclustijd_int - (honderd * 100000) - (tien * 10000)) / 1000;
            tmp_cyclustijd_int = (tien * 100000) + (een * 10000) + (key_int * 1000);
            tft.fillRect(0, 100, 480,220, TFT_BLACK );
            tft.setCursor(in_out_hor_int[0][0], in_out_hor_int[0][1]);
            tft.print("Aantal inputs");
            tft.setCursor(in_out_hor_int[0][0] + 120, in_out_hor_int[0][1]);
            printf_2_int(aantal_input_int);
            tft.print(print_char);
            tft.setCursor(in_out_hor_int[1][0], in_out_hor_int[1][1]);
            tft.print("Aantal outputs");
            tft.setCursor(in_out_hor_int[1][0] + 120, in_out_hor_int[1][1]);
            printf_2_int(aantal_output_int);
            tft.print(print_char);
            tft.setCursor(in_out_hor_int[2][0], in_out_hor_int[2][1]);
            tft.print("Cyclus tijd");
            if((tmp_cyclustijd_int > 100000) || (tmp_cyclustijd_int < 10000)){
              tft.setTextColor(TFT_RED);
            }
            tft.setCursor(in_out_hor_int[2][0] + 120, in_out_hor_int[2][1]);
            printf_6_int(tmp_cyclustijd_int);
            tft.print(print_char);
            tft.setTextColor(TFT_WHITE);
            tft.print("   microseconden");
          }
          tft.setTextColor(TFT_WHITE);
          no_key_detect();
        }
      }
    }
  }

  /*
  RUN
  */
  if(digitalRead(PROG_RUN)){
    tft.fillScreen(TFT_BLACK);
    keuze_bool = false;
    programmeren_bool = false;
    pwm_instellen_bool = false;
    tmr_instellen_bool = false;
    ctr_instellen_bool = false;
    prog_flash_bool = false;
    flash_lezen_bool = false;
    flash_schrijven_bool = false;
    programma_printen_bool = false;
    programma_wissen_bool = false;
    aantal_in_out_kiezen_bool = false;
    status_array_reset();
    tmr_ctr_reset();
    schrijf_output_nul();
    not_bool = false;
    rise_fall_bool = false;
    while(digitalRead(PROG_RUN)){
      if(cyclus_start_bool){
        start_micros_long = micros();
        cyclus_start_bool = false;
        for(int x = 0; x < 30; x++){
          buffer_array_int[x] = false;
        }
        programma_lijn_int = 0;
        programma_lijn_positie_int = 0;
        buffer_teller_int = 0;
        if(open_array_int[programma_lijn_int] == 0){
          haakjes_bool = false;
        }
        else{
          haakjes_bool = true;
          open_temp_int = open_array_int[programma_lijn_int];
        }
        lees_input();
        lees_ai();
        
        while(programma_array_int[programma_lijn_int][0] != 0xff){

          /* GEEN HAAKJES*/

          if(!(haakjes_bool)){
            while(programma_array_int[programma_lijn_int][programma_lijn_positie_int] != 0xff){
              commando_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
              if((commando_int > PWM_F) && (commando_int < LEFT)){
                if(commando_int == AI_E){
                  if(ai_in_int[programma_array_int[programma_lijn_int][programma_lijn_positie_int + 1]] == (((programma_array_int[programma_lijn_int][programma_lijn_positie_int + 2]) * pow_int) / 100)){
                    buffer_array_int[0] = true;
                  }
                  else{
                    buffer_array_int[0] = false;
                  }
                  programma_lijn_positie_int += 3;
                }
                if(commando_int == AI_G){
                  if(ai_in_int[programma_array_int[programma_lijn_int][programma_lijn_positie_int + 1]] > (((programma_array_int[programma_lijn_int][programma_lijn_positie_int + 2]) * pow_int) / 100)){
                    buffer_array_int[0] = true;
                  }
                  else{
                    buffer_array_int[0] = false;
                  }
                  programma_lijn_positie_int += 3;
                }
                if(commando_int == AI_L){
                  if(ai_in_int[programma_array_int[programma_lijn_int][programma_lijn_positie_int + 1]] < (((programma_array_int[programma_lijn_int][programma_lijn_positie_int + 2]) * pow_int) / 100)){
                    buffer_array_int[0] = true;
                  }
                  else{
                    buffer_array_int[0] = false;
                  }
                  programma_lijn_positie_int += 3;
                }
                if(commando_int == AI_G_L){
                  if((ai_in_int[programma_array_int[programma_lijn_int][programma_lijn_positie_int + 1]] > (((programma_array_int[programma_lijn_int][programma_lijn_positie_int + 2]) * pow_int) / 100))
                      && (ai_in_int[programma_array_int[programma_lijn_int][programma_lijn_positie_int + 1]] < (((programma_array_int[programma_lijn_int][programma_lijn_positie_int + 3]) * pow_int) / 100))){
                    buffer_array_int[0] = true;
                  }
                  else{
                    buffer_array_int[0] = false;
                  }
                  programma_lijn_positie_int += 4;
                }
                commando_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                if(commando_int == EQUALS){
                  programma_lijn_positie_int ++;
                  commando_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                  if((commando_int == OUT) || (commando_int == MERKER)){
                    programma_lijn_positie_int++;
                    commando_plus_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    status_array_bool[commando_int - 200][commando_plus_int] = buffer_array_int[0];
                  }
                  if(commando_int == PWM){
                    if(buffer_array_int[0]){
                      duty_cycle_array_temp_int[programma_array_int[programma_lijn_int][programma_lijn_positie_int + 1]] = programma_array_int[programma_lijn_int][programma_lijn_positie_int + 2];
                    }
                    else{
                      duty_cycle_array_temp_int[programma_array_int[programma_lijn_int][programma_lijn_positie_int + 1]] = 0;
                    }
                    programma_lijn_positie_int += 2;
                  }
                  if(commando_int == PWM_F){
                    if(buffer_array_int[0]){
                      duty_cycle_array_temp_int[programma_array_int[programma_lijn_int][programma_lijn_positie_int + 1]] = (ai_in_int[programma_array_int[programma_lijn_int][programma_lijn_positie_int + 2]] * 100) / pow_int;
                    }
                    else{
                      duty_cycle_array_temp_int[programma_array_int[programma_lijn_int][programma_lijn_positie_int + 1]] = 0;
                    }
                    programma_lijn_positie_int += 2;
                  }
                }
                if(commando_int == SET){
                  if((commando_int == OUT) || (commando_int == MERKER)){
                    programma_lijn_positie_int++;
                    commando_plus_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    if(buffer_array_int[0]){
                      status_array_bool[commando_int - 200][commando_plus_int] = true;
                    }
                  }
                  if(commando_int == PWM){
                    if(buffer_array_int[0]){
                      duty_cycle_array_temp_int[programma_array_int[programma_lijn_int][programma_lijn_positie_int + 1]] = programma_array_int[programma_lijn_int][programma_lijn_positie_int + 2];
                    }
                    programma_lijn_positie_int += 2;
                  }
                  if(commando_int == PWM_F){
                    if(buffer_array_int[0]){
                      duty_cycle_array_temp_int[programma_array_int[programma_lijn_int][programma_lijn_positie_int + 1]] = (ai_in_int[programma_array_int[programma_lijn_int][programma_lijn_positie_int + 2]] * 100) / pow_int;
                    }
                    programma_lijn_positie_int += 2;
                  }
                }
                if(commando_int == RST){
                  if((commando_int == OUT) || (commando_int == MERKER)){
                    programma_lijn_positie_int++;
                    commando_plus_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    if(buffer_array_int[0]){
                      status_array_bool[commando_int - 200][commando_plus_int] = false;
                    }
                  }
                  if(commando_int == PWM){
                    if(buffer_array_int[0]){
                      duty_cycle_array_temp_int[programma_array_int[programma_lijn_int][programma_lijn_positie_int + 1]] = 0;
                    }
                    programma_lijn_positie_int += 2;
                  }
                  if(commando_int == PWM_F){
                    if(buffer_array_int[0]){
                      duty_cycle_array_temp_int[programma_array_int[programma_lijn_int][programma_lijn_positie_int + 1]] = 0;
                    }
                    programma_lijn_positie_int += 2;
                  }
                }
              }
              if(programma_lijn_positie_int == 0){
                if((commando_int == NOT) || (commando_int == RISE) || (commando_int == FALL)){
                  if(commando_int == NOT){
                    programma_lijn_positie_int++;
                    commando_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    programma_lijn_positie_int++;
                    commando_plus_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    buffer_array_int[buffer_teller_int] = status_array_bool[commando_int - 200][commando_plus_int] ^ 1;
                  }
                  if(commando_int == RISE){
                    programma_lijn_positie_int++;
                    commando_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    programma_lijn_positie_int++;
                    commando_plus_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    if((!(status_array_vorig_bool[commando_int - 200][commando_plus_int])) && (status_array_bool[commando_int - 200][commando_plus_int])){
                      buffer_array_int[buffer_teller_int] = true;
                    }
                    else{
                      buffer_array_int[buffer_teller_int] = false;
                    }
                  }
                  if(commando_int == FALL){
                    programma_lijn_positie_int++;
                    commando_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    programma_lijn_positie_int++;
                    commando_plus_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    if((status_array_vorig_bool[commando_int - 200][commando_plus_int]) && (!(status_array_bool[commando_int - 200][commando_plus_int]))){
                      buffer_array_int[buffer_teller_int] = true;
                    }
                    else{
                      buffer_array_int[buffer_teller_int] = false;
                    }
                  }
                }
                else{
                  programma_lijn_positie_int++;
                  commando_plus_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                  buffer_array_int[buffer_teller_int] = status_array_bool[commando_int - 200][commando_plus_int];
                }
              }    
              if((commando_int > CTRD) && (commando_int < EQUALS)){
                if(commando_int == AND){
                  programma_lijn_positie_int++;
                  commando_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                  if(commando_int == RISE){
                    rise_fall_bool = true;
                    programma_lijn_positie_int++;
                    commando_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    programma_lijn_positie_int++;
                    commando_plus_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    if((buffer_array_int[buffer_teller_int]) && (!(status_array_vorig_bool[commando_int - 200][commando_plus_int])) && (status_array_bool[commando_int - 200][commando_plus_int])){
                      buffer_array_int[buffer_teller_int] = true;
                    }
                    else{
                      buffer_array_int[buffer_teller_int] = false;
                    }
                  }
                  if(commando_int == FALL){
                    rise_fall_bool = true;
                    programma_lijn_positie_int++;
                    commando_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    programma_lijn_positie_int++;
                    commando_plus_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    if((buffer_array_int[buffer_teller_int]) && (status_array_vorig_bool[commando_int - 200][commando_plus_int]) && (!(status_array_bool[commando_int - 200][commando_plus_int]))){
                      buffer_array_int[buffer_teller_int] = true;
                    }
                    else{
                      buffer_array_int[buffer_teller_int] = false;
                    }
                  }
                  if(!(rise_fall_bool)){
                    if(commando_int == NOT){
                      not_bool = true;
                      programma_lijn_positie_int++;
                      commando_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    }
                    programma_lijn_positie_int++;
                    commando_plus_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    if(!not_bool){
                      if((buffer_array_int[buffer_teller_int]) && (status_array_bool[commando_int - 200][commando_plus_int])){
                        buffer_array_int[buffer_teller_int] = true;
                      }
                      else{
                        buffer_array_int[buffer_teller_int] = false;
                      }
                    }
                    else{
                      if((buffer_array_int[buffer_teller_int]) && (!(status_array_bool[commando_int - 200][commando_plus_int]))){
                        buffer_array_int[buffer_teller_int] = true;
                      }
                      else{
                        buffer_array_int[buffer_teller_int] = false;
                      }
                    }
                    not_bool = false;
                  }
                  rise_fall_bool = false;
                }
                if(commando_int == OR){
                  programma_lijn_positie_int++;
                  commando_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                  if(commando_int == RISE){
                    rise_fall_bool = true;
                    programma_lijn_positie_int++;
                    commando_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    programma_lijn_positie_int++;
                    commando_plus_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    if((buffer_array_int[buffer_teller_int]) || ((!(status_array_vorig_bool[commando_int - 200][commando_plus_int])) && (status_array_bool[commando_int - 200][commando_plus_int]))){
                      buffer_array_int[buffer_teller_int] = true;
                    }
                    else{
                      buffer_array_int[buffer_teller_int] = false;
                    }
                  }
                  if(commando_int == FALL){
                    rise_fall_bool = true;
                    programma_lijn_positie_int++;
                    commando_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    programma_lijn_positie_int++;
                    commando_plus_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    if((buffer_array_int[buffer_teller_int]) || ((status_array_vorig_bool[commando_int - 200][commando_plus_int]) && (!(status_array_bool[commando_int - 200][commando_plus_int])))){
                      buffer_array_int[buffer_teller_int] = true;
                    }
                    else{
                      buffer_array_int[buffer_teller_int] = false;
                    }
                  }
                  if(!(rise_fall_bool)){
                    if(commando_int == NOT){
                      not_bool = true;
                      programma_lijn_positie_int++;
                      commando_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    }
                    programma_lijn_positie_int++;
                    commando_plus_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    if(!not_bool){
                      if((buffer_array_int[buffer_teller_int]) || (status_array_bool[commando_int - 200][commando_plus_int])){
                        buffer_array_int[buffer_teller_int] = true;
                      }
                      else{
                        buffer_array_int[buffer_teller_int] = false;
                      }
                    }
                    else{
                      if((buffer_array_int[buffer_teller_int]) || (!(status_array_bool[commando_int - 200][commando_plus_int]))){
                        buffer_array_int[buffer_teller_int] = true;
                      }
                      else{
                        buffer_array_int[buffer_teller_int] = false;
                      }
                    }
                    not_bool = false;
                  }
                  rise_fall_bool = false;
                }
                if(commando_int == XOR){
                  programma_lijn_positie_int++;
                  commando_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                  if(commando_int == RISE){
                    rise_fall_bool = true;
                    programma_lijn_positie_int++;
                    commando_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    programma_lijn_positie_int++;
                    commando_plus_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    if((buffer_array_int[buffer_teller_int]) ^ ((!(status_array_vorig_bool[commando_int - 200][commando_plus_int])) && (status_array_bool[commando_int - 200][commando_plus_int]))){
                      buffer_array_int[buffer_teller_int] = true;
                    }
                    else{
                      buffer_array_int[buffer_teller_int] = false;
                    }
                  }
                  if(commando_int == FALL){
                    rise_fall_bool = true;
                    programma_lijn_positie_int++;
                    commando_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    programma_lijn_positie_int++;
                    commando_plus_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    if((buffer_array_int[buffer_teller_int]) ^ ((status_array_vorig_bool[commando_int - 200][commando_plus_int]) && (!(status_array_bool[commando_int - 200][commando_plus_int])))){
                      buffer_array_int[buffer_teller_int] = true;
                    }
                    else{
                      buffer_array_int[buffer_teller_int] = false;
                    }
                  }
                  if(!(rise_fall_bool)){
                    if(commando_int == NOT){
                      not_bool = true;
                      programma_lijn_positie_int++;
                      commando_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    }
                    programma_lijn_positie_int++;
                    commando_plus_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    if(!not_bool){
                      if((buffer_array_int[buffer_teller_int]) ^ (status_array_bool[commando_int - 200][commando_plus_int])){
                        buffer_array_int[buffer_teller_int] = true;
                      }
                      else{
                        buffer_array_int[buffer_teller_int] = false;
                      }
                    }
                    else{
                      if((buffer_array_int[buffer_teller_int]) ^ (!(status_array_bool[commando_int - 200][commando_plus_int]))){
                        buffer_array_int[buffer_teller_int] = true;
                      }
                      else{
                        buffer_array_int[buffer_teller_int] = false;
                      }
                    }
                    not_bool = false;
                  }
                  rise_fall_bool = false;
                }
              }
              //if((commando_int > NOT) && (commando_int < AI_E)){
              if(((commando_int == EQUALS) || (commando_int == SET) || (commando_int == RST)) && (buffer_teller_int == 0)){
                if(commando_int == EQUALS){
                  programma_lijn_positie_int++;
                  commando_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                  if((commando_int == OUT) || (commando_int == MERKER)){
                    programma_lijn_positie_int++;
                    commando_plus_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    status_array_bool[commando_int - 200][commando_plus_int] = buffer_array_int[0];
                  }
                  if(commando_int == TMR){
                    programma_lijn_positie_int++;
                    commando_plus_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    if(buffer_array_int[0]){
                      tmr_nu_int[commando_plus_int] -= timer_int;
                      if(tmr_nu_int[commando_plus_int] < 0){
                        tmr_nu_int[commando_plus_int] = 0;
                      }
                      if(commando_plus_int < 56){
                        if(tmr_nu_int[commando_plus_int] == 0){
                          status_array_bool[3][commando_plus_int] = true;
                        }
                      }
                      else{
                        if(tmr_nu_int[commando_plus_int] == 0){
                          status_array_bool[3][commando_plus_int] = status_array_bool[3][commando_plus_int] ^ 1;
                          tmr_nu_int[commando_plus_int] = (tmr_instelling_int[commando_plus_int] * 100);
                        }
                      }
                    }
                  }
                  if(commando_int == CTRU){
                    programma_lijn_positie_int++;
                    commando_plus_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    if((buffer_array_int[0]) && (!ctru_vorig_bool[commando_plus_int])){
                      ctr_nu_int[commando_plus_int]++;
                      if(ctr_nu_int[commando_plus_int] > ctr_instelling_int[commando_plus_int]){
                        ctr_nu_int[commando_plus_int] = ctr_instelling_int[commando_plus_int];
                      }
                      if(ctr_nu_int[commando_plus_int] == ctr_instelling_int[commando_plus_int]){
                        status_array_bool[4][commando_plus_int] = true;                                 
                      }
                      else{
                        status_array_bool[4][commando_plus_int] = false;
                      }
                      if(ctr_nu_int[commando_plus_int] == 0){
                        status_array_bool[5][commando_plus_int] = true;                                 
                      }
                      else{
                        status_array_bool[5][commando_plus_int] = false;
                      }
                    }
                    ctru_vorig_bool[commando_plus_int] = buffer_array_int[0];
                  }
                  if(commando_int == CTRD){
                    programma_lijn_positie_int++;
                    commando_plus_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    if((buffer_array_int[0]) && (!ctrd_vorig_bool[commando_plus_int])){
                      ctr_nu_int[commando_plus_int]--;
                      if(ctr_nu_int[commando_plus_int] < 0){
                        ctr_nu_int[commando_plus_int] = 0;
                      }
                      if(ctr_nu_int[commando_plus_int] == ctr_instelling_int[commando_plus_int]){
                        status_array_bool[4][commando_plus_int] = true;
                      }
                      else{
                        status_array_bool[4][commando_plus_int] = false;
                      }
                      if(ctr_nu_int[commando_plus_int] == 0){
                        status_array_bool[5][commando_plus_int] = true;
                      }
                      else{
                        status_array_bool[5][commando_plus_int] = false;
                      }
                    }
                    ctrd_vorig_bool[commando_plus_int] = buffer_array_int[0];
                  }
                  if(commando_int == TMR_R){
                    programma_lijn_positie_int++;
                    commando_plus_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    if(buffer_array_int[0]){
                      tmr_nu_int[commando_plus_int] = (tmr_instelling_int[commando_plus_int] * 100);
                      status_array_bool[3][commando_plus_int] = false;
                    }
                  }
                  if(commando_int == CTR_R){
                    programma_lijn_positie_int++;
                    commando_plus_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    if(buffer_array_int[0]){
                      ctr_nu_int[commando_plus_int] = 0;
                      status_array_bool[4][commando_plus_int] = false;
                      status_array_bool[5][commando_plus_int] = true;
                    }
                  }
                  if(commando_int == PWM){
                    if(buffer_array_int[0]){
                      duty_cycle_array_temp_int[programma_array_int[programma_lijn_int][programma_lijn_positie_int + 1]] = programma_array_int[programma_lijn_int][programma_lijn_positie_int + 2];
                    }
                    else{
                      duty_cycle_array_temp_int[programma_array_int[programma_lijn_int][programma_lijn_positie_int + 1]] = 0;
                    }
                  }
                  if(commando_int == PWM_F){
                    if(buffer_array_int[0]){
                      duty_cycle_array_temp_int[programma_array_int[programma_lijn_int][programma_lijn_positie_int + 1]] = (ai_in_int[programma_array_int[programma_lijn_int][programma_lijn_positie_int + 2]] * 100) / pow_int;
                    }
                    else{
                      duty_cycle_array_temp_int[programma_array_int[programma_lijn_int][programma_lijn_positie_int + 1]] = 0;
                    }
                  }
                }
                if(commando_int == SET){
                  programma_lijn_positie_int++;
                  commando_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                  if((commando_int == OUT) || (commando_int == MERKER)){
                    programma_lijn_positie_int++;
                    commando_plus_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    if(buffer_array_int[0]){
                      status_array_bool[commando_int - 200][commando_plus_int] = true;
                    }
                  }
                  if(commando_int == PWM){
                    if(buffer_array_int[0]){
                      duty_cycle_array_temp_int[programma_array_int[programma_lijn_int][programma_lijn_positie_int + 1]] = programma_array_int[programma_lijn_int][programma_lijn_positie_int + 2];
                    }
                  }
                  if(commando_int == PWM_F){
                    if(buffer_array_int[0]){
                      duty_cycle_array_temp_int[programma_array_int[programma_lijn_int][programma_lijn_positie_int + 1]] = (ai_in_int[programma_array_int[programma_lijn_int][programma_lijn_positie_int + 2]] * 100) / pow_int;
                    }
                  }
                }
                if(commando_int == RST){
                  programma_lijn_positie_int++;
                  commando_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                  if((commando_int == OUT) || (commando_int == MERKER)){
                    programma_lijn_positie_int++;
                    commando_plus_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
                    if(buffer_array_int[0]){
                      status_array_bool[commando_int - 200][commando_plus_int] = false;
                    }
                  }
                  if(commando_int == PWM){
                    if(buffer_array_int[0]){
                      duty_cycle_array_temp_int[programma_array_int[programma_lijn_int][programma_lijn_positie_int + 1]] = 0;
                    }
                  }
                  if(commando_int == PWM_F){
                    if(buffer_array_int[0]){
                      duty_cycle_array_temp_int[programma_array_int[programma_lijn_int][programma_lijn_positie_int + 1]] = 0;
                    }
                  }
                }
              }
              //}
              programma_lijn_positie_int++;
            }
          }
          /*
            HAAKJES
          */
          if(haakjes_bool){
            commando_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
            while((commando_int != EQUALS) && (commando_int != SET) && (commando_int != RST)){
              commando_plus_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int + 1];
              if(commando_int == NOT){
                if(commando_plus_int == OPEN){
                  buffer_array_int[buffer_teller_int] = commando_int;
                  buffer_teller_int ++;
                }
                if((commando_plus_int == IN) || (commando_plus_int == OUT) || (commando_plus_int == MERKER) || (commando_plus_int == TMR) || (commando_plus_int == CTRU) || (commando_plus_int == CTRD)){
                  commando_plus_2_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int + 2];
                  buffer_array_int[buffer_teller_int] = (status_array_bool[commando_plus_int - 200][commando_plus_2_int] ^1);
                  buffer_teller_int ++;
                  programma_lijn_positie_int += 2;
                }
              }
              if((commando_int == OPEN) || (commando_int == CLOSE)){
                buffer_array_int[buffer_teller_int] = commando_int;
                buffer_teller_int ++;
              }
              if(commando_int == RISE){
                commando_plus_2_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int + 2];
                if((!(status_array_vorig_bool[commando_plus_int - 200][commando_plus_2_int])) && (status_array_bool[commando_plus_int - 200][commando_plus_2_int])){
                  buffer_array_int[buffer_teller_int] = true;
                }
                else{
                  buffer_array_int[buffer_teller_int] = false;
                }
                buffer_teller_int ++;
                programma_lijn_positie_int += 2;
              }
              if(commando_int == FALL){
                commando_plus_2_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int + 2];
                if((status_array_vorig_bool[commando_plus_int - 200][commando_plus_2_int]) && (!(status_array_bool[commando_plus_int - 200][commando_plus_2_int]))){
                  buffer_array_int[buffer_teller_int] = true;
                }
                else{
                  buffer_array_int[buffer_teller_int] = false;
                }
                buffer_teller_int ++;
                programma_lijn_positie_int += 2;
              }
              if((commando_int == IN) || (commando_int == OUT) || (commando_int == MERKER) || (commando_int == TMR) || (commando_int == CTRU) || (commando_int == CTRD)){
                buffer_array_int[buffer_teller_int] = status_array_bool[commando_int - 200][commando_plus_int];
                buffer_teller_int ++;
                programma_lijn_positie_int ++;
              }
              if((commando_int == AND) || (commando_int == OR) || (commando_int == XOR)){
                buffer_array_int[buffer_teller_int] = commando_int;
                buffer_teller_int ++;
              }
              programma_lijn_positie_int ++;
              commando_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
            }
            while(commando_int != 0xff){
              buffer_array_int[buffer_teller_int] = commando_int;
              buffer_teller_int ++;
              programma_lijn_positie_int ++;
              commando_int = programma_array_int[programma_lijn_int][programma_lijn_positie_int];
            }
            open_temp_int = open_array_int[programma_lijn_int];
            while(open_temp_int > 0){
              for(int x = 0; x < MAX_INST + 1; x++){
                if(buffer_array_int[x] == OPEN){
                  open_positie_int = x;
                }
              }
              open_temp_int --;
              buffer_teller_int = open_positie_int;
              buffer_array_int[open_positie_int] = 99;
              open_positie_int ++;
              buffer_teller_int += 2;
              commando_int = buffer_array_int[buffer_teller_int];
              while(commando_int != CLOSE){
                if(commando_int == AND){
                  buffer_array_int[open_positie_int] = buffer_array_int[open_positie_int] && buffer_array_int[buffer_teller_int + 1];
                  buffer_array_int[buffer_teller_int] = 99;
                  buffer_array_int[buffer_teller_int + 1] = 99;
                }
                if(commando_int == OR){
                  buffer_array_int[open_positie_int] = buffer_array_int[open_positie_int] || buffer_array_int[buffer_teller_int + 1];
                  buffer_array_int[buffer_teller_int] = 99;
                  buffer_array_int[buffer_teller_int + 1] = 99;
                }
                if(commando_int == XOR){
                  buffer_array_int[open_positie_int] = buffer_array_int[open_positie_int] ^ buffer_array_int[buffer_teller_int + 1];
                  buffer_array_int[buffer_teller_int] = 99;
                  buffer_array_int[buffer_teller_int + 1] = 99;
                }
                buffer_teller_int += 2;
                commando_int = buffer_array_int[buffer_teller_int];
              }
              buffer_array_int[buffer_teller_int] = 99;
              buffer_array_links();
            }
            buffer_array_links();
            buffer_teller_int = 1;
            if(buffer_array_int[0] == NOT){
              buffer_array_int[0] = buffer_array_int[1] ^ 1;
              buffer_teller_int = 2;
            }
            commando_int = buffer_array_int[buffer_teller_int];
            while((commando_int != EQUALS) && (commando_int != SET) && (commando_int != RST)){
              if(commando_int == AND){
                if(buffer_array_int[buffer_teller_int + 1] == NOT){
                  buffer_array_int[0] = buffer_array_int[0] && (buffer_array_int[buffer_teller_int + 2] ^ 1);
                  buffer_teller_int ++;
                }
                else{
                  buffer_array_int[0] = buffer_array_int[0] && buffer_array_int[buffer_teller_int + 1];
                }
              }
              if(commando_int == OR){
                if(buffer_array_int[buffer_teller_int + 1] == NOT){
                  buffer_array_int[0] = buffer_array_int[0] || (buffer_array_int[buffer_teller_int + 2] ^ 1);
                  buffer_teller_int ++;
                }
                else{
                  buffer_array_int[0] = buffer_array_int[0] || buffer_array_int[buffer_teller_int + 1];
                }
              }
              if(commando_int == XOR){
                if(buffer_array_int[buffer_teller_int + 1] == NOT){
                  buffer_array_int[0] = buffer_array_int[0] ^ (buffer_array_int[buffer_teller_int + 2] ^ 1);
                  buffer_teller_int ++;
                }
                else{
                  buffer_array_int[0] = buffer_array_int[0] ^ buffer_array_int[buffer_teller_int + 1];
                }
              }
              buffer_teller_int += 2;
              commando_int = buffer_array_int[buffer_teller_int];
            }
            if((commando_int == EQUALS) || (commando_int == SET) || (commando_int == RST)){
              if(commando_int == EQUALS){
                buffer_teller_int++;
                commando_int = buffer_array_int[buffer_teller_int];
                if((commando_int == OUT) || (commando_int == MERKER)){
                  buffer_teller_int++;
                  commando_plus_int = buffer_array_int[buffer_teller_int];
                  status_array_bool[commando_int - 200][commando_plus_int] = buffer_array_int[0];
                }
                if(commando_int == TMR){
                  buffer_teller_int++;
                  commando_int = buffer_array_int[buffer_teller_int];
                  if(buffer_array_int[0]){
                    tmr_nu_int[commando_int] -= timer_int;
                    if(tmr_nu_int[commando_int] <= 0){
                      tmr_nu_int[commando_int] = 0;
                    }
                    if(commando_int < 56){
                      if(tmr_nu_int[commando_int] == 0){
                        status_array_bool[3][commando_int] = true;
                      }
                    }
                    else{
                      if(tmr_nu_int[commando_int] == 0){
                        status_array_bool[3][commando_int] = status_array_bool[3][commando_int] ^ 1;
                        tmr_nu_int[commando_int] = (tmr_instelling_int[commando_int] * 100);
                      }
                    }
                  }
                }
                if(commando_int == CTRU){
                  buffer_teller_int++;
                  commando_int = buffer_array_int[buffer_teller_int];
                  if((buffer_array_int[0]) && (!ctru_vorig_bool[commando_int])){
                    ctr_nu_int[commando_int]++;
                    if(ctr_nu_int[commando_int] > ctr_instelling_int[commando_int]){
                      ctr_nu_int[commando_int] = ctr_instelling_int[commando_int];
                    }
                    if(ctr_nu_int[commando_int] == ctr_instelling_int[commando_int]){
                      status_array_bool[4][commando_int] = true;                                 
                    }
                    else{
                      status_array_bool[4][commando_int] = false;
                    }
                    if(ctr_nu_int[commando_int] == 0){
                      status_array_bool[5][commando_int] = true;                                 
                    }
                    else{
                      status_array_bool[5][commando_int] = false;
                    }
                  }
                  ctru_vorig_bool[commando_int] = buffer_array_int[0];
                }
                if(commando_int == CTRD){
                  buffer_teller_int++;
                  commando_int = buffer_array_int[buffer_teller_int];
                  if((buffer_array_int[0]) && (!ctrd_vorig_bool[commando_int])){
                    ctr_nu_int[commando_int]--;
                    if(ctr_nu_int[commando_int] < 0){
                      ctr_nu_int[commando_int] = 0;
                    }
                    if(ctr_nu_int[commando_int] == ctr_instelling_int[commando_int]){
                      status_array_bool[4][commando_int] = true;
                    }
                    else{
                      status_array_bool[4][commando_int] = false;
                    }
                    if(ctr_nu_int[commando_int] == 0){
                      status_array_bool[5][commando_int] = true;
                    }
                    else{
                      status_array_bool[5][commando_int] = false;
                    }
                  }
                  ctrd_vorig_bool[commando_int] = buffer_array_int[0];
                }
                if(commando_int == TMR_R){
                  buffer_teller_int++;
                  commando_int = buffer_array_int[buffer_teller_int];
                  if(buffer_array_int[0]){
                    tmr_nu_int[commando_int] = (tmr_instelling_int[commando_int] * 100);
                    status_array_bool[3][commando_int] = false;
                  }
                }
                if(commando_int == CTR_R){
                  buffer_teller_int++;
                  commando_int = buffer_array_int[buffer_teller_int];
                  if(buffer_array_int[0]){
                    ctr_nu_int[commando_int] = 0;
                    status_array_bool[4][commando_int] = false;
                    status_array_bool[5][commando_int] = true;
                  }
                }
                if(commando_int == PWM){
                  if(buffer_array_int[0]){
                    duty_cycle_array_temp_int[buffer_array_int[buffer_teller_int + 1]] = buffer_array_int[buffer_teller_int + 2];
                  }
                  else{
                    duty_cycle_array_temp_int[buffer_array_int[buffer_teller_int + 1]] = 0;
                  }
                }
                if(commando_int == PWM_F){
                  if(buffer_array_int[0]){
                    duty_cycle_array_temp_int[buffer_array_int[buffer_teller_int + 1]] = ((ai_in_int[buffer_array_int[buffer_teller_int + 2]] * 100) / pow_int);
                  }
                  else{
                    duty_cycle_array_temp_int[buffer_array_int[buffer_teller_int + 1]] = 0;
                  }
                }
              }
              if(commando_int == SET){
                buffer_teller_int++;
                commando_int = buffer_array_int[buffer_teller_int];
                if((commando_int == OUT) || (commando_int == MERKER)){
                  buffer_teller_int++;
                  commando_int = buffer_array_int[buffer_teller_int];
                  if(buffer_array_int[0]){
                    status_array_bool[commando_int - 200][commando_int] = true;
                  }
                }
                if(commando_int == PWM){
                  if(buffer_array_int[0]){
                    duty_cycle_array_temp_int[buffer_array_int[buffer_teller_int + 1]] = buffer_array_int[buffer_teller_int + 2];
                  }
                }
                if(commando_int == PWM_F){
                  if(buffer_array_int[0]){
                    duty_cycle_array_temp_int[buffer_array_int[buffer_teller_int + 1]] = (ai_in_int[buffer_array_int[buffer_teller_int + 2]] * 100) / pow_int;
                  }
                }
              }
              if(commando_int == RST){
                buffer_teller_int++;
                commando_int = buffer_array_int[buffer_teller_int];
                if((commando_int == OUT) || (commando_int == MERKER)){
                  buffer_teller_int++;
                  commando_int = buffer_array_int[buffer_teller_int];
                  if(buffer_array_int[0]){
                    status_array_bool[commando_int - 200][commando_int] = false;
                  }
                }
                if(commando_int == PWM){
                  if(buffer_array_int[0]){
                    duty_cycle_array_temp_int[buffer_array_int[buffer_teller_int + 1]] = 0;
                  }
                }
                if(commando_int == PWM_F){
                  if(buffer_array_int[0]){
                    duty_cycle_array_temp_int[buffer_array_int[buffer_teller_int + 1]] = 0;
                  }
                }
              }
            }
          }
          buffer_teller_int = 0;
          programma_lijn_int ++;
          programma_lijn_positie_int = 0;
          if(open_array_int[programma_lijn_int] == 0){
            haakjes_bool = false;
          }
          else{
            haakjes_bool = true;
            open_temp_int = open_array_int[programma_lijn_int];
          }
          for(int x = 0; x < 30; x++){
            buffer_array_int[x] = false;
          }
        }
        if(aantal_input_int == 16){
          schrijf_output();
        }
        if(aantal_input_int > 16){
          digitalWrite(OUTPUT_MODULE_0, false);
          schrijf_output();
          digitalWrite(OUTPUT_MODULE_0, true);
          digitalWrite(OUTPUT_MODULE_1, false);
          schrijf_output();
          digitalWrite(OUTPUT_MODULE_1, true);
        }
        if(aantal_input_int > 32){
          digitalWrite(OUTPUT_MODULE_2, false);
          schrijf_output();
          digitalWrite(OUTPUT_MODULE_2, true);
        }
        if(aantal_input_int > 48){
          digitalWrite(OUTPUT_MODULE_3, false);
          schrijf_output();
          digitalWrite(OUTPUT_MODULE_3, true);
        }
        nu_naar_vorig();
        Serial.println(micros() - start_micros_long);
        if((micros() - start_micros_long) >= cyclustijd_int){
          tft.setTextColor(TFT_RED);
          tft.setCursor(((480 - tft.textWidth("RUNTIME ERROR > cyclustijd", 2)) / 2), 50);
          tft.print("RUNTIME ERROR > cyclustijd");
          tft.setCursor(((480 - tft.textWidth("Zet prog_run schakelaar op programmeren", 2)) / 2), 70);
          tft.print("Zet prog_run schakelaar op programmeren");
          tft.setTextColor(TFT_WHITE);
          while(digitalRead(PROG_RUN)){
            delay(1);
          }
        }
      } 
    }
    schrijf_output_nul();
  }
  attachInterrupt(TFT_TOUCH_INT, touch_int, FALLING);
}

/*
Functions
*/

/*
CYCLUSTIJD INTERRUPT
*/
void  TimerHandler0(){
  cyclus_start_bool = true;
  digitalWrite(LED_BUILTIN, blink_bool);
  blink_bool = !blink_bool;
}

/*
TFT TOUCH
*/
void touch_int(){
  detachInterrupt(digitalPinToInterrupt(TFT_TOUCH_INT));
  touch_bool = true;
}

void touch_calibrate(){
  int lb_x_int;
  int lb_y_int;
  int rb_x_int;
  int rb_y_int;
  int lo_x_int;
  int lo_y_int;
  int ro_x_int;
  int ro_y_int;
  int x_max_int;
  int y_max_int;
  int x_diff_int;
  int y_diff_int;
  tft.fillScreen(TFT_BLACK);
  tft.setCursor((480 - tft.textWidth("Touch calibratie", 2)) / 2, 100);
  tft.print("Touch calibratie");
  tft.setCursor((480 - tft.textWidth("Druk in de aageduide hoek", 2)) / 2, 120);
  tft.print("Druk in de aangeduide hoek");
  for(int x = 0; x < 15; x++){
    tft.drawPixel(x, 0, TFT_RED);
    tft.drawPixel(0, x, TFT_RED);
  }
  while((!(touch_bool)) || (!(ts.touched()))){
    delay(1);
  }
  touch_bool = false;
  TS_Point p = ts.getPoint();
  tft.fillScreen(TFT_BLACK);
  lb_x_int = p.x;
  lb_y_int = p.y;
  delay(500);
  tft.setCursor((480 - tft.textWidth("Touch calibratie", 2)) / 2, 100);
  tft.print("Touch calibratie");
  tft.setCursor((480 - tft.textWidth("Druk in de aangeduide hoek", 2)) / 2, 120);
  tft.print("Druk in de aangeduide hoek");
  for(int x = 0; x < 15; x++){
    tft.drawPixel(x + 464, 0, TFT_RED);
    tft.drawPixel(479, x, TFT_RED);
  }
  attachInterrupt(TFT_TOUCH_INT, touch_int, FALLING);
  while(((!(touch_bool)) || (!(ts.touched())))){
    delay(1);
  }
  touch_bool = false;
  p = ts.getPoint();
  tft.fillScreen(TFT_BLACK);
  rb_x_int = p.x;
  rb_y_int = p.y;
  delay(500);
  tft.setCursor((480 - tft.textWidth("Touch calibratie", 2)) / 2, 100);
  tft.print("Touch calibratie");
  tft.setCursor((480 - tft.textWidth("Druk in de aangeduide hoek", 2)) / 2, 120);
  tft.print("Druk in de aangeduide hoek");
  for(int x = 0; x < 15; x++){
    tft.drawPixel(x, 319, TFT_RED);
    tft.drawPixel(0, 304 + x, TFT_RED);
  }
  attachInterrupt(TFT_TOUCH_INT, touch_int, FALLING);
  while(((!(touch_bool)) || (!(ts.touched())))){
    delay(1);
  }
  touch_bool = false;
  p = ts.getPoint();
  tft.fillScreen(TFT_BLACK);
  lo_x_int = p.x;
  lo_y_int = p.y;
  delay(500);
  tft.setCursor((480 - tft.textWidth("Touch calibratie", 2)) / 2, 100);
  tft.print("Touch calibratie");
  tft.setCursor((480 - tft.textWidth("Druk in de aangeduide hoek", 2)) / 2, 120);
  tft.print("Druk in de aangeduide hoek");
  for(int x = 0; x < 15; x++){
    tft.drawPixel(x + 464, 319, TFT_RED);
    tft.drawPixel(479, 304 + x, TFT_RED);
  }
  attachInterrupt(TFT_TOUCH_INT, touch_int, FALLING);
  while(((!(touch_bool)) || (!(ts.touched())))){
    delay(1);
  }
  touch_bool = false;
  p = ts.getPoint();
  tft.fillScreen(TFT_BLACK);
  ro_x_int = p.x;
  ro_y_int = p.y;
  delay(500);
  x_0_int = (lb_x_int + lo_x_int) / 2;
  x_max_int = (rb_x_int + ro_x_int) / 2;
  y_0_int = (lb_y_int + rb_y_int) / 2;
  y_max_int = (lo_y_int + ro_y_int) / 2;
  x_diff_int = ((rb_x_int - lb_x_int) + (ro_x_int - lo_x_int)) / 2;
  y_diff_int = ((lo_y_int - lb_y_int) + (ro_y_int - rb_y_int)) / 2;
  x_factor_float = x_diff_int / 480.0;
  y_factor_float = y_diff_int / 320.0;
  print_flash_adres_bool = true;
  schrijf_instellingen();
  EEPROM.commit();
  attachInterrupt(TFT_TOUCH_INT, touch_int, FALLING);
  calibrated_bool = true;
  Serial.print("links boven x :");
  Serial.print(lb_x_int);
  Serial.print("    links boven y :");
  Serial.println(lb_y_int);
  Serial.print("rechts boven x :");
  Serial.print(rb_x_int);
  Serial.print("    rechts boven y :");
  Serial.println(rb_y_int);
  Serial.print("links onder x :");
  Serial.print(lo_x_int);
  Serial.print("    links onder y :");
  Serial.println(lo_y_int);
  Serial.print("rechts onder x :");
  Serial.print(ro_x_int);
  Serial.print("    rechts onder y :");
  Serial.println(ro_y_int);
  Serial.println();
  Serial.print(x_0_int);
  Serial.print("     ");
  Serial.print(y_0_int);
  Serial.print("     ");
  Serial.print(x_factor_float);
  Serial.print("     ");
  Serial.println(y_factor_float);
}

void touch(){
  float x_touch_float;
  float y_touch_float;
  if(touch_bool){
    touch_bool = false;
    if(ts.touched()){
      TS_Point p = ts.getPoint();
      x_touch_float = p.x - x_0_int;
      y_touch_float = p.y - y_0_int;
      x_touch_int = x_touch_float / x_factor_float;
      if(x_touch_int < 0){
        x_touch_int = 0;
      }
      if(x_touch_int > 479){
        x_touch_int = 479;
      }
      y_touch_int = y_touch_float / y_factor_float;
      if(y_touch_int < 0){
        y_touch_int = 0;
      }
      if(y_touch_int > 319){
        y_touch_int = 319;
      }
      touched_bool = true;
    }
    delay(100);
    attachInterrupt(TFT_TOUCH_INT, touch_int, FALLING);
  }
}

void calibrate_test(){
  int calibrate_test_int;
  calibrated_bool = false;
  eeprom_adres_int = 0;
  high_byte = 0;
  middle_byte = EEPROM.read(eeprom_adres_int);
  eeprom_adres_int = eeprom_adres_int + sizeof(byte);
  low_byte = EEPROM.read(eeprom_adres_int);
  calibrate_test_int = bytes_to_int();
  if(calibrate_test_int == CAL_VAL){
    calibrated_bool = true;
    print_flash_adres_bool = false;
    lees_instellingen();
  }
}

void programma_array_reset(){
  for(int x = 0; x < MAX_LINE + 1; x ++){
    open_array_int[x] = 0;
    for(int y = 0; y < MAX_INST + 1; y++){
      programma_array_int[x][y] = 0xff;
    }
  }
  programma_lijn_int = 0;
  programma_lijn_max_int = 0;
}

/*
Keuzemenu
*/
void keuzemenu(){
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextFont(4);
  tft.setCursor((480 - tft.textWidth("Keuzemenu", 4)) / 2, 20);
  tft.print("Keuzemenu");
  tft.setTextFont(2);
  tft.setCursor(35, keuzemenu_hor_int[0]);
  tft.print("Programmeren");
  tft.setCursor(35, keuzemenu_hor_int[1]);
  tft.print("PWM / AI instellen" );
  tft.setCursor(35, keuzemenu_hor_int[2]);
  tft.print("TMR's instellen");
  tft.setCursor(35, keuzemenu_hor_int[3]);
  tft.print("CTR's instellen");
  tft.setCursor(35, keuzemenu_hor_int[4]);
  tft.print("FLASH");
  tft.setCursor(35, keuzemenu_hor_int[5]);
  tft.print("Programma printen");
  tft.setCursor(35, keuzemenu_hor_int[6]);
  tft.print("Programma wissen");
  tft.setCursor(35, keuzemenu_hor_int[7]);
  tft.print("Inputs  Outputs  Cyclustijd");
}

/*
Toetsenbord 
*/
void keyboard_scan(){
  key_int = 99;
  rij_int = 0;
  digitalWrite(KEYB_C_0, true);
  key_detect();
  digitalWrite(KEYB_C_0, false);
  rij_int = 5;
  digitalWrite(KEYB_C_1, true);
  key_detect();
  digitalWrite(KEYB_C_1, false);
  rij_int = 10;
  digitalWrite(KEYB_C_2, true);
  key_detect();
  digitalWrite(KEYB_C_2, false);
  rij_int = 15;
  digitalWrite(KEYB_C_3, true);
  key_detect();
  digitalWrite(KEYB_C_3, false);
  if(!(key_int == 99)){
    key_int = key_naar_int[key_int];
  }
}

void key_detect(){
  if(digitalRead(KEYB_R_0)){
    key_int = rij_int;
  }
  if(digitalRead(KEYB_R_1)){
    key_int = rij_int + 1;
  }
  if(digitalRead(KEYB_R_2)){
    key_int = rij_int + 2;
  }
  if(digitalRead(KEYB_R_3)){
    key_int = rij_int + 3;
  }
  if(digitalRead(KEYB_R_4)){
    key_int = rij_int + 4;
  }
}

void no_key_detect(){
  digitalWrite(KEYB_C_0, true);
  digitalWrite(KEYB_C_1, true);
  digitalWrite(KEYB_C_2, true);
  digitalWrite(KEYB_C_3, true);
  while(digitalRead(KEYB_R_0)){
    delay(5);
  }
  while(digitalRead(KEYB_R_1)){
    delay(5);
  }
  while(digitalRead(KEYB_R_2)){
    delay(5);
  }
  while(digitalRead(KEYB_R_3)){
    delay(5);
  }
  while(digitalRead(KEYB_R_4)){
    delay(5);
  }
  digitalWrite(KEYB_C_0, false);
  digitalWrite(KEYB_C_1, false);
  digitalWrite(KEYB_C_2, false);
  digitalWrite(KEYB_C_3, false);
  key_int = 99;
}

/*
Programmeren
*/
void programmeerscherm(){
  for(int x = 0; x < 35; x++){
    if(x > 28){
      tft.fillRect(commando_coord_int[x][0], commando_coord_int[x][1], 44, 25, TFT_YELLOW);
    }
    else if((x > 24) && (x < 29)){
      tft.fillRect(commando_coord_int[x][0], commando_coord_int[x][1], 44, 25, TFT_GREENYELLOW);
    }
    else{
     tft.fillRect(commando_coord_int[x][0], commando_coord_int[x][1], 44, 25, TFT_WHITE); 
    }
    tft.setTextFont(2);
    tft.setTextColor(TFT_BLACK);
    tft.setCursor(commando_coord_int[x][0] + 22 - (tft.textWidth(commando_string[x], 2) / 2), commando_coord_int[x][1] + 4);
    tft.print(commando_string[x]);
  }
}

void bereken_programma_lijn_positie_int(){
  programma_lijn_positie_int = 0;
  while(programma_array_int[programma_lijn_int][programma_lijn_positie_int] != 0xff){
    programma_lijn_positie_int ++;
  }
}

void toon_programma_lijn(){
  print_lijnnummer();
  tft.drawLine(0, 70, 479, 70, TFT_BLACK);
  x_positie_int = 0;
  for(int x = 0; x < (MAX_INST + 1); x++){
    pixel_positie_int[x] = 0xff;
  }
  hulp_lijn_positie_int = 0;
  commando_int = programma_array_int[programma_lijn_int][hulp_lijn_positie_int];
  lijn_controle();
  programma_lijn_positie_int = hulp_lijn_positie_int;
  edit_lijn_positie_int = hulp_lijn_positie_int;
}

void print_edit_lijn(){
  tft.fillRect(0, 50, 480, 20, TFT_BLACK);
  x_positie_int = 0;
  hulp_lijn_positie_int = 0;
  commando_int = programma_array_int[programma_lijn_int][hulp_lijn_positie_int];
  lijn_controle();
  edit_lijn_positie_int = hulp_lijn_positie_int;
}

void lijn_controle(){
  while(commando_int != 0xff){
    commando_int = programma_array_int[programma_lijn_int][hulp_lijn_positie_int];
    if((commando_int == IN) || (commando_int == OUT) || (commando_int == MERKER) || (commando_int == TMR) || (commando_int == CTRU)
       || (commando_int == CTRD) || (commando_int == TMR_R) || (commando_int == CTR_R)){
      tft.setCursor(x_positie_int, 50);
      tft.print(commando_string[commando_int - 200]);
      pixel_positie_int[hulp_lijn_positie_int] = x_positie_int;
      x_positie_int = tft.getCursorX();
      int max_int = 63;
      if(programma_array_int[programma_lijn_int][hulp_lijn_positie_int] == IN){
        max_int = aantal_input_int - 1;
      }
      if(programma_array_int[programma_lijn_int][hulp_lijn_positie_int] == OUT){
        max_int = aantal_output_int - 1;
      }
      hulp_lijn_positie_int ++;
      printf_2_int(programma_array_int[programma_lijn_int][hulp_lijn_positie_int]);
      tft.setCursor(x_positie_int, 50);
      if(programma_array_int[programma_lijn_int][hulp_lijn_positie_int] > max_int){
        tft.setTextColor(TFT_RED);
      }
      tft.print(print_char);
      tft.setTextColor(TFT_WHITE);
      pixel_positie_int[hulp_lijn_positie_int] = x_positie_int;
      x_positie_int = tft.getCursorX();
      hulp_lijn_positie_int ++;
      if((programma_array_int[programma_lijn_int][hulp_lijn_positie_int]) != (CLOSE)){
        x_positie_int += 5;
      }
    }
    if(commando_int == PWM){
      tft.setCursor(x_positie_int, 50);
      pixel_positie_int[hulp_lijn_positie_int] = x_positie_int;
      tft.print(commando_string[commando_int - 200]);
      x_positie_int = tft.getCursorX();
      hulp_lijn_positie_int ++;
      if(programma_array_int[programma_lijn_int][hulp_lijn_positie_int] > 3){
        tft.setTextColor(TFT_RED);
      }
      pixel_positie_int[hulp_lijn_positie_int] = x_positie_int;
      tft.print(programma_array_int[programma_lijn_int][hulp_lijn_positie_int]);
      tft.setTextColor(TFT_WHITE);
      x_positie_int = tft.getCursorX();
      x_positie_int += 5;
      hulp_lijn_positie_int ++;
      printf_3_int(programma_array_int[programma_lijn_int][hulp_lijn_positie_int]);
      tft.setCursor(x_positie_int, 50);
      pixel_positie_int[hulp_lijn_positie_int] = x_positie_int;
      tft.print(print_char);
      x_positie_int = tft.getCursorX();
      hulp_lijn_positie_int ++;
    }
    if(commando_int == PWM_F){
      tft.setCursor(x_positie_int, 50);
      pixel_positie_int[hulp_lijn_positie_int] = x_positie_int;
      tft.print(commando_string[commando_int - 200]);
      x_positie_int = tft.getCursorX();
      hulp_lijn_positie_int ++;
      if(programma_array_int[programma_lijn_int][hulp_lijn_positie_int] > 3){
        tft.setTextColor(TFT_RED);
      }
      pixel_positie_int[hulp_lijn_positie_int] = x_positie_int;
      tft.print(programma_array_int[programma_lijn_int][hulp_lijn_positie_int]);
      tft.setTextColor(TFT_WHITE);
      x_positie_int = tft.getCursorX();
      x_positie_int += 5;
      hulp_lijn_positie_int ++;
      if(programma_array_int[programma_lijn_int][hulp_lijn_positie_int] > 3){
        tft.setTextColor(TFT_RED);
      }
      tft.setCursor(x_positie_int, 50);
      pixel_positie_int[hulp_lijn_positie_int] = x_positie_int;
      tft.print(programma_array_int[programma_lijn_int][hulp_lijn_positie_int]);
      tft.setTextColor(TFT_WHITE);
      x_positie_int = tft.getCursorX();
      hulp_lijn_positie_int ++;
    }
    if((commando_int == AI_E) || (commando_int == AI_G) || (commando_int == AI_L)){
      tft.setCursor(x_positie_int, 50);
      pixel_positie_int[hulp_lijn_positie_int] = x_positie_int;
      tft.print(commando_string[commando_int - 200]);
      x_positie_int = tft.getCursorX();
      x_positie_int += 5;
      hulp_lijn_positie_int ++;
      if(programma_array_int[programma_lijn_int][hulp_lijn_positie_int] > 3){
        tft.setTextColor(TFT_RED);
      }
      tft.setCursor(x_positie_int, 50);
      pixel_positie_int[hulp_lijn_positie_int] = x_positie_int;
      tft.print(programma_array_int[programma_lijn_int][hulp_lijn_positie_int]);
      tft.setTextColor(TFT_WHITE);
      x_positie_int = tft.getCursorX();
      x_positie_int += 5;
      hulp_lijn_positie_int ++;
      if(programma_array_int[programma_lijn_int][hulp_lijn_positie_int] > 100){
        tft.setTextColor(TFT_RED);
      }
      printf_3_int(programma_array_int[programma_lijn_int][hulp_lijn_positie_int]);
      tft.setCursor(x_positie_int, 50);
      pixel_positie_int[hulp_lijn_positie_int] = x_positie_int;
      tft.print(print_char);
      tft.setTextColor(TFT_WHITE);
      x_positie_int = tft.getCursorX();
      hulp_lijn_positie_int ++;
    }
    if(commando_int == AI_G_L){
      tft.setCursor(x_positie_int, 50);
      pixel_positie_int[hulp_lijn_positie_int] = x_positie_int;
      tft.print(commando_string[commando_int - 200]);
      x_positie_int = tft.getCursorX();
      x_positie_int += 5;
      hulp_lijn_positie_int ++;
      if(programma_array_int[programma_lijn_int][hulp_lijn_positie_int] > 3){
        tft.setTextColor(TFT_RED);
      }
      tft.setCursor(x_positie_int, 50);
      pixel_positie_int[hulp_lijn_positie_int] = x_positie_int;
      tft.print(programma_array_int[programma_lijn_int][hulp_lijn_positie_int]);
      tft.setTextColor(TFT_WHITE);
      x_positie_int = tft.getCursorX();
      x_positie_int += 5;
      hulp_lijn_positie_int ++;
      if(programma_array_int[programma_lijn_int][hulp_lijn_positie_int] > 100){
        tft.setTextColor(TFT_RED);
      }
      printf_3_int(programma_array_int[programma_lijn_int][hulp_lijn_positie_int]);
      tft.setCursor(x_positie_int, 50);
      pixel_positie_int[hulp_lijn_positie_int] = x_positie_int;
      tft.print(print_char);
      tft.setTextColor(TFT_WHITE);
      x_positie_int = tft.getCursorX();
      x_positie_int += 5;
      hulp_lijn_positie_int ++;
      if(programma_array_int[programma_lijn_int][hulp_lijn_positie_int] > 100){
        tft.setTextColor(TFT_RED);
      }
      printf_3_int(programma_array_int[programma_lijn_int][hulp_lijn_positie_int]);
      tft.setCursor(x_positie_int, 50);
      pixel_positie_int[hulp_lijn_positie_int] = x_positie_int;
      tft.print(print_char);
      tft.setTextColor(TFT_WHITE);
      x_positie_int = tft.getCursorX();
      hulp_lijn_positie_int ++;
    }
    if((commando_int == AND) || (commando_int == OR) || (commando_int == XOR) || (commando_int == RISE) || (commando_int == FALL) || (commando_int == NOT) || (commando_int == SET) || (commando_int == RST) || (commando_int == EQUALS)
       || (commando_int == CLOSE)){
      tft.setCursor(x_positie_int, 50);
      tft.print(commando_string[commando_int - 200]);
      pixel_positie_int[hulp_lijn_positie_int] = x_positie_int;
      x_positie_int = tft.getCursorX();
      hulp_lijn_positie_int ++;
      x_positie_int += 5;
    }
    if((commando_int == OPEN)){
      tft.setCursor(x_positie_int, 50);
      tft.print(commando_string[commando_int - 200]);
      pixel_positie_int[hulp_lijn_positie_int] = x_positie_int;
      x_positie_int = tft.getCursorX();
      hulp_lijn_positie_int ++;
    }
    if((commando_int == INS_C)){
      tft.setCursor(x_positie_int, 50);
      tft.print(commando_string[commando_int - 200]);
      pixel_positie_int[hulp_lijn_positie_int] = x_positie_int;
      x_positie_int = tft.getCursorX();
      hulp_lijn_positie_int ++;
      x_positie_int += 5;
    }
  }
}

void print_lijnnummer(){
  tft.fillRect(0, 20, 480, 20, TFT_BLACK);
  tft.fillRect(0, 50, 480, 20, TFT_BLACK);
  memset(print_char, 0, sizeof(print_char));
  sprintf(print_char, "Lijn : %04d", programma_lijn_int);
  tft.setCursor((240 - tft.textWidth(print_char, 2)) / 2, 20);
  tft.print(print_char);
  memset(print_char, 0, sizeof(print_char));
  sprintf(print_char, "Bytes gebruikt : %05d /16000", programma_lengte_int);
  tft.setCursor(((240 - tft.textWidth(print_char, 2)) / 2) + 240, 20);
  tft.print(print_char);
}

void bereken_programma_lengte(){
  programma_lengte_int = 0;
  for(int x = 0; x < MAX_LINE + 1; x ++){
    if(programma_array_int[x][0] == 0xff){
      programma_lengte_int ++;
      break;
    } 
    for(int y = 0; y < MAX_INST + 1; y ++){
      programma_lengte_int ++;
      if(programma_array_int[x][y] == 0xff){
        break;
      }
    }
  }
}

void print_error_test(){
  if((program_error_bool) || (o_c_error_bool)){
    tft.fillRect(0, 50, 480, 20, TFT_BLACK);
    x_positie_int = 0;
    edit_lijn_positie_int = 0;
    int x = 0;
    tft.setTextColor(TFT_WHITE);
    while((programma_array_int[programma_lijn_int][x]) != 0xff){
      commando_int = programma_array_int[programma_lijn_int][x];
      if(error_array_bool[x]){
        tft.setTextColor(TFT_RED);
      }
      if((commando_int == IN) || (commando_int == OUT) || (commando_int == MERKER) || (commando_int == TMR) || (commando_int == CTRU) || (commando_int == CTRD) || (commando_int == CTRU)
        || (commando_int == CTRD) || (commando_int == TMR_R) || (commando_int == CTR_R) || (commando_int == PWM) || (commando_int == PWM_F)){
        tft.setCursor(x_positie_int, 50);
        tft.print(commando_string[commando_int - 200]);
        tft.setTextColor(TFT_WHITE);
        if(!((commando_int == PWM) || (commando_int == PWM_F))){
          pixel_positie_int[edit_lijn_positie_int] = x_positie_int;
          x_positie_int = tft.getCursorX();
          x ++;
          edit_lijn_positie_int ++;
          if(error_array_bool[x]){
            tft.setTextColor(TFT_RED);
          }
          printf_2_int(programma_array_int[programma_lijn_int][x]);
          tft.setCursor(x_positie_int, 50);
          tft.print(print_char);
          tft.setTextColor(TFT_WHITE);
          pixel_positie_int[edit_lijn_positie_int] = x_positie_int;
          x_positie_int = tft.getCursorX();
          x_positie_int += 5;
        }
        else{
          pixel_positie_int[edit_lijn_positie_int] = x_positie_int;
          x_positie_int = tft.getCursorX();
          x ++;
          edit_lijn_positie_int ++;
          if(error_array_bool[x]){
            tft.setTextColor(TFT_RED);
          }
          tft.setCursor(x_positie_int, 50);
          tft.print(programma_array_int[programma_lijn_int][x]);
          tft.setTextColor(TFT_WHITE);
          pixel_positie_int[edit_lijn_positie_int] = x_positie_int;
          x_positie_int = tft.getCursorX();
          x_positie_int += 5;
          x ++;
          edit_lijn_positie_int ++;
          if(error_array_bool[x]){
            tft.setTextColor(TFT_RED);
          }
          tft.setCursor(x_positie_int, 50);
          printf_3_int(programma_array_int[programma_lijn_int][x]);
          pixel_positie_int[edit_lijn_positie_int] = x_positie_int;
          tft.setCursor(x_positie_int, 50);
          tft.print(print_char);
          tft.setTextColor(TFT_WHITE);
          edit_lijn_positie_int ++;
        }
      }
      if((commando_int == AND) || (commando_int == OR) || (commando_int == XOR) || (commando_int == RISE) || (commando_int == FALL) || (commando_int == NOT) || (commando_int == SET) || (commando_int == RST) || (commando_int == EQUALS)){
        tft.setCursor(x_positie_int, 50);
        tft.print(commando_string[commando_int - 200]);
        pixel_positie_int[edit_lijn_positie_int] = x_positie_int;
        x_positie_int = tft.getCursorX();
        x_positie_int += 5;
      }
      if((commando_int == INS_C)){
        tft.setCursor(x_positie_int, 50);
        tft.print(commando_string[commando_int - 200]);
        pixel_positie_int[edit_lijn_positie_int] = x_positie_int;
        x_positie_int = tft.getCursorX();
        x_positie_int += 5;
      }

      if((commando_int == AI_E) || (commando_int == AI_G) || (commando_int == AI_L)){
        tft.setCursor(x_positie_int, 50);
        tft.print(commando_string[commando_int - 200]);
        pixel_positie_int[edit_lijn_positie_int] = x_positie_int;
        x_positie_int = tft.getCursorX();
        x_positie_int += 5;
        x ++;
        edit_lijn_positie_int ++;
        if(error_array_bool[x]){
          tft.setTextColor(TFT_RED);
        }
        tft.setCursor(x_positie_int, 50);
        tft.print(programma_array_int[programma_lijn_int][x]);
        tft.setTextColor(TFT_WHITE);
        pixel_positie_int[edit_lijn_positie_int] = x_positie_int;
        x_positie_int = tft.getCursorX();
        x_positie_int += 5;
        x ++;
        edit_lijn_positie_int ++;
        if(error_array_bool[x]){
          tft.setTextColor(TFT_RED);
        }
        printf_3_int(programma_array_int[programma_lijn_int][x]);
        tft.setCursor(x_positie_int, 50);
        tft.print(print_char);
        tft.setTextColor(TFT_WHITE);
        pixel_positie_int[edit_lijn_positie_int] = x_positie_int;
        x_positie_int = tft.getCursorX();
        x_positie_int += 5;
      }
      if(commando_int == AI_G_L){
        tft.setCursor(x_positie_int, 50);
        tft.print(commando_string[commando_int - 200]);
        pixel_positie_int[edit_lijn_positie_int] = x_positie_int;
        x_positie_int = tft.getCursorX();
        x_positie_int += 5;
        x ++;
        edit_lijn_positie_int ++;
        if(error_array_bool[x]){
          tft.setTextColor(TFT_RED);
        }
        tft.setCursor(x_positie_int, 50);
        tft.print(programma_array_int[programma_lijn_int][x]);
        tft.setTextColor(TFT_WHITE);
        pixel_positie_int[edit_lijn_positie_int] = x_positie_int;
        x_positie_int = tft.getCursorX();
        x_positie_int += 5;
        x ++;
        edit_lijn_positie_int ++;
        if(error_array_bool[x]){
          tft.setTextColor(TFT_RED);
        }
        printf_3_int(programma_array_int[programma_lijn_int][x]);
        tft.setCursor(x_positie_int, 50);
        tft.print(print_char);
        tft.setTextColor(TFT_WHITE);
        pixel_positie_int[edit_lijn_positie_int] = x_positie_int;
        x_positie_int = tft.getCursorX();
        x_positie_int += 5;
        x ++;
        edit_lijn_positie_int ++;
        if(error_array_bool[x]){
          tft.setTextColor(TFT_RED);
        }
        printf_3_int(programma_array_int[programma_lijn_int][x]);
        tft.setCursor(x_positie_int, 50);
        tft.print(print_char);
        tft.setTextColor(TFT_WHITE);
        pixel_positie_int[edit_lijn_positie_int] = x_positie_int;
        x_positie_int = tft.getCursorX();
        x_positie_int += 5;
      }
      if((o_c_array_bool[x]) && (o_c_error_bool)){
        tft.setTextColor(TFT_RED);
      }
      else{
        tft.setTextColor(TFT_WHITE);
      }
      if((commando_int == OPEN)){
        tft.setCursor(x_positie_int, 50);
        tft.print(commando_string[commando_int - 200]);
        tft.setTextColor(TFT_WHITE);
        pixel_positie_int[edit_lijn_positie_int] = x_positie_int;
        x_positie_int = tft.getCursorX();
      }
      if((commando_int == CLOSE)){
        tft.setCursor(x_positie_int, 50);
        tft.print(commando_string[commando_int - 200]);
        tft.setTextColor(TFT_WHITE);
        pixel_positie_int[edit_lijn_positie_int] = x_positie_int;
        x_positie_int = tft.getCursorX();
        x_positie_int += 5;
      }
      x ++;
      edit_lijn_positie_int ++;
    }
  }
}

/*
PWM AI INSTELLEN
*/
void printf_5_int(int freq_int){
  int tienduizend_int = freq_int /10000;
  int duizend_int = (freq_int - (tienduizend_int * 10000)) / 1000;
  int honderd_int = (freq_int - (tienduizend_int * 10000) - (duizend_int * 1000)) / 100;
  int tien_int = (freq_int - (tienduizend_int * 10000) - (duizend_int * 1000) - (honderd_int * 100))  / 10;
  int een_int = (freq_int - (tienduizend_int * 10000) - (duizend_int * 1000) - (honderd_int * 100) - (tien_int * 10));
  memset(print_char, 0, sizeof(print_char));
  sprintf(print_char, "%01d%01d%01d%01d%01d", tienduizend_int, duizend_int, honderd_int,tien_int, een_int);
}

void ai_onderlijn(){
  tft.drawLine(pwm_hor_int[pwm_instellen_int][0], pwm_hor_int[pwm_instellen_int][1] + 17, pwm_hor_int[pwm_instellen_int][0] + 300, pwm_hor_int[pwm_instellen_int][1] + 17, TFT_BLACK);
  if(!cursor_positie_bool){
    tft.drawLine(pwm_hor_int[pwm_instellen_int][0] + 75, pwm_hor_int[pwm_instellen_int][1] + 17, pwm_hor_int[pwm_instellen_int][0] + 105, pwm_hor_int[pwm_instellen_int][1] + 17, TFT_WHITE);
  }
  if(cursor_positie_bool){
    tft.drawLine(pwm_hor_int[pwm_instellen_int][0] + 140, pwm_hor_int[pwm_instellen_int][1] + 17, pwm_hor_int[pwm_instellen_int][0] + 170, pwm_hor_int[pwm_instellen_int][1] + 17, TFT_WHITE);
  }
}

void plaats_ster_pwm(){
  tft.setCursor(pwm_hor_int[pwm_instellen_int][0] - 25, pwm_hor_int[pwm_instellen_int][1]);
  tft.setTextFont(4);
  tft.setTextColor(TFT_RED);
  tft.print("*");
  tft.setTextFont(2);
  tft.setTextColor(TFT_WHITE);
}

void links_freq(int freq_int, int pwm_int){
  int tienduizend_int = freq_int /10000;
  int duizend_int = (freq_int - (tienduizend_int * 10000)) / 1000;
  int honderd_int = (freq_int - (tienduizend_int * 10000) - (duizend_int * 1000)) / 100;
  int tien_int = (freq_int - (tienduizend_int * 10000) - (duizend_int * 1000) - (honderd_int * 100))  / 10;
  int een_int = (freq_int - (tienduizend_int * 10000) - (duizend_int * 1000) - (honderd_int * 100) - (tien_int * 10));
  int temp = (duizend_int * 10000) + (honderd_int * 1000) + (tien_int * 100) + (een_int * 10) + key_int;
  if(temp < 1){
    temp = 1;
  }
  freq_array_int[pwm_int] = temp;
  printf_5_int(freq_array_int[pwm_int]);
}

void links_ai(){
  int temp_int = ai_array_int[pwm_instellen_int - 4][cursor_positie_bool];
  int duizend_int = temp_int / 1000;
  int honderd_int = (temp_int - (duizend_int * 1000)) / 100;
  int tien_int = (temp_int - (duizend_int * 1000) - (honderd_int * 100)) / 10;
  int een_int = temp_int - (duizend_int * 1000) - (honderd_int * 100) - (tien_int * 10);
  ai_array_int[pwm_instellen_int - 4][cursor_positie_bool] = (honderd_int * 1000) + (tien_int * 100) + (een_int * 10) + key_int;
  printf_4_int(ai_array_int[pwm_instellen_int - 4][cursor_positie_bool]);
}

/*
ALGEMEEN
*/ 
void printf_4_int(int waarde_int){
  int duizend_int = waarde_int / 1000;
  int honderd_int = (waarde_int - (duizend_int * 1000)) / 100;
  int tien_int = (waarde_int - (duizend_int * 1000) - (honderd_int * 100)) / 10;
  int een_int = (waarde_int - (duizend_int * 1000) - (honderd_int * 100)- (tien_int * 10));
  memset(print_char, 0, sizeof(print_char));
  sprintf(print_char, "%01d%01d%01d%01d", duizend_int, honderd_int, tien_int, een_int);
}

void printf_3_int(int waarde_int){
  int honderd_int = waarde_int / 100;
  int tien_int = (waarde_int - (honderd_int * 100)) / 10;
  int een_int = (waarde_int - (honderd_int * 100)- (tien_int * 10));
  memset(print_char, 0, sizeof(print_char));
  sprintf(print_char, "%01d%01d%01d", honderd_int,tien_int, een_int);
}

void printf_2_int(int waarde_int){
  int tien_int = waarde_int / 10;
  int een_int = (waarde_int - (tien_int * 10));
  memset(print_char, 0, sizeof(print_char));
  sprintf(print_char, "%1d%1d", tien_int, een_int);
}

void printf_6_int(int waarde_int){
  int honderdduizend_int = waarde_int / 100000;
  int tienduizend_int = (waarde_int - (honderdduizend_int * 100000)) /10000;
  int duizend_int = (waarde_int - (honderdduizend_int * 100000) - (tienduizend_int * 10000)) / 1000;
  int honderd_int = (waarde_int - (honderdduizend_int * 100000) - (tienduizend_int * 10000) - (duizend_int * 1000)) / 100;
  int tien_int = (waarde_int - (honderdduizend_int * 100000) - (tienduizend_int * 10000) - (duizend_int * 1000) - (honderd_int * 100))  / 10;
  int een_int = (waarde_int - (honderdduizend_int * 100000) - (tienduizend_int * 10000) - (duizend_int * 1000) - (honderd_int * 100) - (tien_int * 10));
  memset(print_char, 0, sizeof(print_char));
  sprintf(print_char, "%01d%01d%01d%01d%01d%01d", honderdduizend_int, tienduizend_int, duizend_int, honderd_int,tien_int, een_int);
}

/*
Timer instellen
*/
void print_tmr_pag(){
  tft.fillRect(0, 70, 480, 240, TFT_BLACK );
  for(int x = 0; x < 16; x ++){
    tft.setCursor(tmr_ctr_hor_int[x][0], tmr_ctr_hor_int[x][1]);
    tft.print("TMR_");
    tft.print((tmr_ctr_pag_int * 16) + x);
    tft.setCursor(tmr_ctr_hor_int[x][0] + 75, tmr_ctr_hor_int[x][1]);
    bereken_tijd((tmr_ctr_pag_int * 16) + x);
    tft.print(print_char);
    tijd_instellen_int = 0;
  }
  plaats_ster_tmr();
  onderlijn();
}

void plaats_ster_tmr(){
  tft.fillRect(0, 70, 22, 195, TFT_BLACK);
  tft.fillRect(215, 70, 22, 195, TFT_BLACK);
  tft.setCursor(tmr_ctr_hor_int[tmr_instellen_int][0] - 25, tmr_ctr_hor_int[tmr_instellen_int][1]);
  tft.setTextFont(4);
  tft.setTextColor(TFT_RED);
  tft.print("*");
  tft.setTextFont(2);
  tft.setTextColor(TFT_WHITE);
}

void onderlijn(){
  tft.fillRect(tmr_ctr_hor_int[7][0] + 75,tmr_ctr_hor_int[7][1] + 16, 100, 5,TFT_BLACK);
  tft.fillRect(tmr_ctr_hor_int[15][0] + 75,tmr_ctr_hor_int[15][1] + 16, 100, 5,TFT_BLACK);
  tft.fillRect(tmr_ctr_hor_int[tmr_instellen_int][0] + 75,tmr_ctr_hor_int[tmr_instellen_int][1] + 16, 100, 5,TFT_BLACK);
  for(int x = 0; x < 15; x++){
    tft.drawPixel(tmr_ctr_hor_int[tmr_instellen_int][0] + 75 + (tijd_instellen_int * 19) + x, tmr_ctr_hor_int[tmr_instellen_int][1] + 16, TFT_WHITE);
  }
}

void bereken_tijd(int x){
  int tmp_int;
  tmp_int = tmr_instelling_int[x];
  uren_int = tmp_int / 36000;
  tmp_int = tmp_int - (uren_int * 36000);
  minuten_int = tmp_int / 600;
  tmp_int = tmp_int - (minuten_int * 600);
  seconden_int = tmp_int / 10;
  hondersten_int = (tmp_int - (seconden_int * 10)) * 10;
  memset(print_char, 0, sizeof(print_char));
  sprintf(print_char, "%02d:%02d:%02d:%02d", uren_int, minuten_int, seconden_int, hondersten_int);
}

void bereken_tienden(){
  tmr_instelling_int[(tmr_ctr_pag_int * 16) + tmr_instellen_int] = (uren_int * 36000) + (minuten_int * 600) + (seconden_int * 10) + (hondersten_int / 10);
}

void tijd_naar_array(){
  uren_array[1] = uren_int / 10;
  uren_array[0] = uren_int - (uren_array[1] * 10);
  minuten_array[1] = minuten_int / 10;
  minuten_array[0] = minuten_int - (minuten_array[1] * 10);
  seconden_array[1] = seconden_int / 10;
  seconden_array[0] = seconden_int - (seconden_array[1] * 10);
  hondersten_array[1] = hondersten_int / 10;
  hondersten_array[0] = 0;
}

void array_naar_tijd(){
  uren_int = (uren_array[1] * 10) + uren_array[0];
  minuten_int = (minuten_array[1] * 10) + minuten_array[0];
  seconden_int = (seconden_array[1] * 10) + seconden_array[0];
  hondersten_int = (hondersten_array[1] * 10) + hondersten_array[0];
}

void links_uren(){
  uren_array[1] = uren_array[0];
  uren_array[0] = key_int;
}

void links_minuten(){
  minuten_array[1] = minuten_array[0];
  minuten_array[0] = key_int;
}

void links_seconden(){
  seconden_array[1] = seconden_array[0];
  seconden_array[0] = key_int;
}

void links_hondersten(){
  hondersten_array[1] = key_int;
}

/*
Counters instellen
*/
void print_ctr_pag(){
  tft.fillRect(0, 70, 480, 240, TFT_BLACK );
  for(int x = 0; x < 16; x ++){
    tft.setCursor(tmr_ctr_hor_int[x][0], tmr_ctr_hor_int[x][1]);
    tft.print("CTR_");
    tft.print((tmr_ctr_pag_int * 16) + x);
    tft.setCursor(tmr_ctr_hor_int[x][0] + 75, tmr_ctr_hor_int[x][1]);
    tft.print(ctr_instelling_int[(tmr_ctr_pag_int * 16) + x]);
  }
  plaats_ster_ctr();
}

void plaats_ster_ctr(){
  tft.fillRect(0, 70, 22, 195, TFT_BLACK);
  tft.fillRect(215, 70, 22, 195, TFT_BLACK);
  tft.setCursor(tmr_ctr_hor_int[ctr_instellen_int][0] - 25, tmr_ctr_hor_int[ctr_instellen_int][1]);
  tft.setTextFont(4);
  tft.setTextColor(TFT_RED);
  tft.print("*");
  tft.setTextFont(2);
  tft.setTextColor(TFT_WHITE);
}

void shift_left_ctr(){
  int temp_int_0;
  int temp_int_1;
  ctr_int[3] = ctr_instelling_int[(tmr_ctr_pag_int * 16) + ctr_instellen_int] / 1000;
  temp_int_0 = ctr_instelling_int[(tmr_ctr_pag_int * 16) + ctr_instellen_int] - (ctr_int[3] *1000);
  ctr_int[2] = temp_int_0 / 100;
  temp_int_1 = temp_int_0 - (ctr_int[2] * 100);
  ctr_int[1] = temp_int_1 / 10;
  ctr_int[0] = temp_int_1 - (ctr_int[1] * 10);
  ctr_int[3] = ctr_int[2];
  ctr_int[2] = ctr_int[1];
  ctr_int[1] = ctr_int[0];
  ctr_int[0] = key_int;
  ctr_instelling_int[(tmr_ctr_pag_int * 16) + ctr_instellen_int] = (ctr_int[3] * 1000) + (ctr_int[2] * 100) + (ctr_int[1] * 10) + ctr_int[0];
}

/*
FLASH
*/
void flash_keuzemenu(){
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextFont(4);
  tft.setCursor((480 - tft.textWidth("Flash Keuzemenu", 4)) / 2, 20);
  tft.print("Flash Keuzemenu");
  tft.setTextFont(2);
  tft.setCursor(35, keuzemenu_hor_int[0]);
  tft.print("Programma naar Flash");
  tft.setCursor(35, keuzemenu_hor_int[1]);
  tft.print("Flash lezen");
}

void int_to_bytes(int waarde){
  high_byte = waarde / 0xffff;
  middle_byte = (waarde - (high_byte * 0xffff)) / 0xff;
  low_byte = (waarde -(high_byte * 0xffff) - (middle_byte * 0xff));
}

int bytes_to_int(){
  return (((high_byte * 0xffff) + (middle_byte * 0xff) + (low_byte)));
}

void print_adres(){
  eeprom_adres_hex = eeprom_adres_int + 0x80FC000;
  if(print_flash_adres_bool){
    tft.setCursor(x_positie_int, 200);
    tft.fillRect(x_positie_int, 200, 200, 15, TFT_BLACK);
    sprintf(print_char, "%05d   %08x", eeprom_adres_int, eeprom_adres_hex);
    tft.print(print_char);
  }
}

void schrijf_instellingen(){
  eeprom_adres_int = 0;
  eeprom_adres_hex = eeprom_adres_int + 0x80FC000;
  tft.setTextFont(2);
  if(print_flash_adres_bool){
    tft.setCursor(0,200);
    tft.print("adres :");
    x_positie_int = tft.getCursorX();
    x_positie_int += 10;
  }
  int_to_bytes(CAL_VAL);
  print_adres();
  EEPROM.write(eeprom_adres_int, middle_byte);
  eeprom_adres_int = eeprom_adres_int + sizeof(byte);
  print_adres();
  EEPROM.write(eeprom_adres_int, low_byte);
  eeprom_adres_int = eeprom_adres_int + sizeof(byte);
  print_adres();
  int_to_bytes(x_0_int);
  EEPROM.write(eeprom_adres_int, middle_byte);
  eeprom_adres_int = eeprom_adres_int + sizeof(byte);
  print_adres();
  EEPROM.write(eeprom_adres_int, low_byte);
  eeprom_adres_int = eeprom_adres_int + sizeof(byte);
  print_adres();
  int_to_bytes(y_0_int);
  EEPROM.write(eeprom_adres_int, middle_byte);
  eeprom_adres_int = eeprom_adres_int + sizeof(byte);
  print_adres();
  EEPROM.write(eeprom_adres_int, low_byte);
  eeprom_adres_int = eeprom_adres_int + sizeof(byte);
  print_adres();
  EEPROM.put(eeprom_adres_int, x_factor_float);
  eeprom_adres_int = eeprom_adres_int + sizeof(float);
  print_adres();
  EEPROM.put(eeprom_adres_int, y_factor_float);
  eeprom_adres_int = eeprom_adres_int + sizeof(float);
  print_adres();
  int_to_bytes(cyclustijd_int);
  EEPROM.write(eeprom_adres_int, high_byte);
  eeprom_adres_int = eeprom_adres_int + sizeof(byte);
  print_adres();
  EEPROM.write(eeprom_adres_int, middle_byte);
  eeprom_adres_int = eeprom_adres_int + sizeof(byte);
  print_adres();
  EEPROM.write(eeprom_adres_int, low_byte);
  eeprom_adres_int = eeprom_adres_int + sizeof(byte);
  print_adres();
  EEPROM.write(eeprom_adres_int, aantal_input_int);
  eeprom_adres_int = eeprom_adres_int + sizeof(byte);
  print_adres();
  EEPROM.write(eeprom_adres_int, aantal_output_int);
  eeprom_adres_int = eeprom_adres_int + sizeof(byte);
  print_adres();
}

void schrijf_programma(){
  int x;
  int y;
  for(x = 0; x < 4; x++){
    int_to_bytes(freq_array_int[x]);
    EEPROM.write(eeprom_adres_int, middle_byte);
    eeprom_adres_int = eeprom_adres_int + sizeof(byte);
    print_adres();
    EEPROM.write(eeprom_adres_int, low_byte);
    eeprom_adres_int = eeprom_adres_int + sizeof(byte);
    print_adres();
  }
  for(x = 0; x < 4; x++){
    int_to_bytes(ai_array_int[x][0]);
    EEPROM.write(eeprom_adres_int, middle_byte);
    eeprom_adres_int = eeprom_adres_int + sizeof(byte);
    print_adres();
    EEPROM.write(eeprom_adres_int, low_byte);
    eeprom_adres_int = eeprom_adres_int + sizeof(byte);
    print_adres();
    int_to_bytes(ai_array_int[x][1]);
    EEPROM.write(eeprom_adres_int, middle_byte);
    eeprom_adres_int = eeprom_adres_int + sizeof(byte);
    print_adres();
    EEPROM.write(eeprom_adres_int, low_byte);
    eeprom_adres_int = eeprom_adres_int + sizeof(byte);
    print_adres();
  }
  for(x = 0; x < 64; x ++){
    int_to_bytes(tmr_instelling_int[x]);
    EEPROM.write(eeprom_adres_int, high_byte);
    eeprom_adres_int = eeprom_adres_int + sizeof(byte);
    print_adres();
    EEPROM.write(eeprom_adres_int, middle_byte);
    eeprom_adres_int = eeprom_adres_int + sizeof(byte);
    print_adres();
    EEPROM.write(eeprom_adres_int, low_byte);
    eeprom_adres_int = eeprom_adres_int + sizeof(byte);
    print_adres();
  }
  for(x = 0; x < 64; x ++){
    int_to_bytes(ctr_instelling_int[x]);
    EEPROM.write(eeprom_adres_int, middle_byte);
    eeprom_adres_int = eeprom_adres_int + sizeof(byte);
    print_adres();
    EEPROM.write(eeprom_adres_int, low_byte);
    eeprom_adres_int = eeprom_adres_int + sizeof(byte);
    print_adres();
  }
  for(x = 0; x < MAX_LINE + 1; x ++){
    if(programma_array_int[x][0] == 0xff){
      EEPROM.write(eeprom_adres_int, 0xff);
      break;
    }
    for(y = 0; y < MAX_INST + 1; y ++){
      print_adres();
      EEPROM.write(eeprom_adres_int, programma_array_int[x][y]);
      eeprom_adres_int = eeprom_adres_int + sizeof(byte);
      if(programma_array_int[x][y] == 0xff){
        break;
      }
    }
  }
}

void lees_instellingen(){
  eeprom_adres_int = 0;
  high_byte = 0;
  eeprom_adres_hex = eeprom_adres_int + 0x80FC000;
  tft.setTextFont(2);
  tft.setCursor(0,200);
  tft.print("adres :");
  x_positie_int = tft.getCursorX();
  x_positie_int += 10;
  print_adres();
  middle_byte = EEPROM.read(eeprom_adres_int);
  eeprom_adres_int = eeprom_adres_int + sizeof(byte);
  print_adres();
  low_byte = EEPROM.read(eeprom_adres_int);
  eeprom_adres_int = eeprom_adres_int + sizeof(byte);
  print_adres();
  middle_byte = EEPROM.read(eeprom_adres_int);
  eeprom_adres_int = eeprom_adres_int + sizeof(byte);
  print_adres();
  low_byte = EEPROM.read(eeprom_adres_int);
  eeprom_adres_int = eeprom_adres_int + sizeof(byte);
  print_adres();
  x_0_int = bytes_to_int();
  middle_byte = EEPROM.read(eeprom_adres_int);
  eeprom_adres_int = eeprom_adres_int + sizeof(byte);
  print_adres();
  low_byte = EEPROM.read(eeprom_adres_int);
  eeprom_adres_int = eeprom_adres_int + sizeof(byte);
  print_adres();
  y_0_int = bytes_to_int();
  EEPROM.get(eeprom_adres_int, x_factor_float);
  eeprom_adres_int = eeprom_adres_int + sizeof(float);
  print_adres();
  EEPROM.get(eeprom_adres_int, y_factor_float);
  eeprom_adres_int = eeprom_adres_int + sizeof(float);
  print_adres();
  high_byte = EEPROM.read(eeprom_adres_int);
  eeprom_adres_int = eeprom_adres_int + sizeof(byte);
  print_adres();
  middle_byte = EEPROM.read(eeprom_adres_int);
  eeprom_adres_int = eeprom_adres_int + sizeof(byte);
  print_adres();
  low_byte = EEPROM.read(eeprom_adres_int);
  eeprom_adres_int = eeprom_adres_int + sizeof(byte);
  print_adres();
  cyclustijd_int = bytes_to_int();
  aantal_input_int = EEPROM.read(eeprom_adres_int);
  eeprom_adres_int = eeprom_adres_int + sizeof(byte);
  print_adres();
  aantal_output_int = EEPROM.read(eeprom_adres_int);
  eeprom_adres_int = eeprom_adres_int + sizeof(byte);
  print_adres();
}

void lees_programma(){
  int x;
  int y;
  bool gedaan_bool = false;
  high_byte = 0;
  for(int x = 0; x < 4; x++){
    middle_byte = EEPROM.read(eeprom_adres_int);
    eeprom_adres_int = eeprom_adres_int + sizeof(byte);
    print_adres();
    low_byte = EEPROM.read(eeprom_adres_int);
    eeprom_adres_int = eeprom_adres_int + sizeof(byte);
    print_adres();
    freq_array_int[x] = bytes_to_int();
  }
  for(int x = 0; x < 4; x++){
    middle_byte = EEPROM.read(eeprom_adres_int);
    eeprom_adres_int = eeprom_adres_int + sizeof(byte);
    print_adres();
    low_byte = EEPROM.read(eeprom_adres_int);
    eeprom_adres_int = eeprom_adres_int + sizeof(byte);
    print_adres();
    ai_array_int[x][0] = bytes_to_int();
    middle_byte = EEPROM.read(eeprom_adres_int);
    eeprom_adres_int = eeprom_adres_int + sizeof(byte);
    print_adres();
    low_byte = EEPROM.read(eeprom_adres_int);
    eeprom_adres_int = eeprom_adres_int + sizeof(byte);
    print_adres();
    ai_array_int[x][1] = bytes_to_int();
  }
  for(int x = 0; x < 64; x++){
    high_byte = EEPROM.read(eeprom_adres_int);
    eeprom_adres_int = eeprom_adres_int + sizeof(byte);
    middle_byte = EEPROM.read(eeprom_adres_int);
    eeprom_adres_int = eeprom_adres_int + sizeof(byte);
    print_adres();
    low_byte = EEPROM.read(eeprom_adres_int);
    eeprom_adres_int = eeprom_adres_int + sizeof(byte);
    print_adres();
    tmr_instelling_int[x] = bytes_to_int();
  }
  high_byte = 0;
  for(int x = 0; x < 64; x++){
    middle_byte = EEPROM.read(eeprom_adres_int);
    eeprom_adres_int = eeprom_adres_int + sizeof(byte);
    print_adres();
    low_byte = EEPROM.read(eeprom_adres_int);
    eeprom_adres_int = eeprom_adres_int + sizeof(byte);
    print_adres();
    ctr_instelling_int[x] = bytes_to_int();
  }
  beschikbaar_flash_geheugen_int = 16384 - eeprom_adres_int;
  for(x = 0; x < MAX_LINE + 1; x ++){
    if(gedaan_bool){
      programma_lijn_max_int = x - 1;
      break;
    }
    for(y = 0; y < MAX_INST + 1; y ++){
      print_adres();
      programma_array_int[x][y] = EEPROM.read(eeprom_adres_int);
      eeprom_adres_int = eeprom_adres_int + sizeof(byte);
      if(programma_array_int[x][0] == 0xff){
        gedaan_bool = true;
      }
      if(programma_array_int[x][y] == 0xff){
        break;
      }
    }
    programma_lijn_int = x;
    programma_lijn_max_int = x;
  }
}

void print_in_out(){
  tft.setCursor(in_out_hor_int[0][0], in_out_hor_int[0][1]);
  tft.print("Aantal inputs");
  tft.setCursor(in_out_hor_int[0][0] + 120, in_out_hor_int[0][1]);
  printf_2_int(aantal_input_int);
  tft.print(print_char);
  tft.setCursor(in_out_hor_int[1][0], in_out_hor_int[1][1]);
  tft.print("Aantal outputs");
  tft.setCursor(in_out_hor_int[1][0] + 120, in_out_hor_int[1][1]);
  printf_2_int(aantal_output_int);
  tft.print(print_char);
  tft.setCursor(in_out_hor_int[2][0], in_out_hor_int[2][1]);
  tft.print("Cyclus tijd");
  tft.setCursor(in_out_hor_int[2][0] + 120, in_out_hor_int[2][1]);
  printf_6_int(cyclustijd_int);
  tft.print(print_char);
  tft.print("   microseconden");
}

void plaats_ster_in_out(){
  tft.fillRect(0, 70, 20, 190, TFT_BLACK);
  tft.setCursor(in_out_hor_int[in_out_instellen_int][0] - 25, in_out_hor_int[in_out_instellen_int][1]);
  tft.setTextFont(4);
  tft.setTextColor(TFT_RED);
  tft.print("*");
  tft.setTextFont(2);
  tft.setTextColor(TFT_WHITE);
}

/*
RUN
*/
void lees_input(){
  int input_teller_int;
  if(aantal_input_int == 16){
    input_teller_int = 0;
    lees_naar_input_array(input_teller_int);
  }
  if(aantal_input_int > 16){
    input_teller_int = 0;
    digitalWrite(INPUT_MODULE_0, false);
    lees_naar_input_array(input_teller_int);
    digitalWrite(INPUT_MODULE_0, true);
    input_teller_int = 16;
    digitalWrite(INPUT_MODULE_1, false);
    lees_naar_input_array(input_teller_int);
    digitalWrite(INPUT_MODULE_1, true);
  }
  if(aantal_input_int > 32){
    input_teller_int = 32;
    digitalWrite(INPUT_MODULE_2, false);
    lees_naar_input_array(input_teller_int);
    digitalWrite(INPUT_MODULE_2, true);
  }
  if(aantal_input_int > 48){
    input_teller_int = 48;
    digitalWrite(INPUT_MODULE_3, false);
    lees_naar_input_array(input_teller_int);
    digitalWrite(INPUT_MODULE_3, true);
  }
}

void lees_naar_input_array(int pagina_int){
  status_array_bool[0][pagina_int + 0] = digitalRead(IN_0);
  status_array_bool[0][pagina_int + 1] = digitalRead(IN_1);
  status_array_bool[0][pagina_int + 2] = digitalRead(IN_2);
  status_array_bool[0][pagina_int + 3] = digitalRead(IN_3);
  status_array_bool[0][pagina_int + 4] = digitalRead(IN_4);
  status_array_bool[0][pagina_int + 5] = digitalRead(IN_5);
  status_array_bool[0][pagina_int + 6] = digitalRead(IN_6);
  status_array_bool[0][pagina_int + 7] = digitalRead(IN_7);
  status_array_bool[0][pagina_int + 8] = digitalRead(IN_8);
  status_array_bool[0][pagina_int + 9] = digitalRead(IN_9);
  status_array_bool[0][pagina_int + 10] = digitalRead(IN_10);
  status_array_bool[0][pagina_int + 11] = digitalRead(IN_11);
  status_array_bool[0][pagina_int + 12] = digitalRead(IN_12);
  status_array_bool[0][pagina_int + 13] = digitalRead(IN_13);
  status_array_bool[0][pagina_int + 14] = digitalRead(IN_14);
  status_array_bool[0][pagina_int + 15] = digitalRead(IN_15);
}

void lees_ai(){
  ai_in_int[0] = analogRead(PA0);
  ai_in_int[1] = analogRead(PA1);
  ai_in_int[2] = analogRead(PA2);
  ai_in_int[3] = analogRead(PA3);
}

void schrijf_output(){
  int output_teller_int;
  if(aantal_output_int == 16){
    output_teller_int = 0;
    schrijf_van_output_array(output_teller_int);
  }
  if(aantal_output_int > 16){
    output_teller_int = 0;
    digitalWrite(OUTPUT_MODULE_0, false);
    schrijf_van_output_array(output_teller_int);
    digitalWrite(OUTPUT_MODULE_0, true);
    output_teller_int = 16;
    digitalWrite(OUTPUT_MODULE_1, false);
    schrijf_van_output_array(output_teller_int);
    digitalWrite(OUTPUT_MODULE_1, true);
  }
  if(aantal_output_int > 32){
    output_teller_int = 32;
    digitalWrite(OUTPUT_MODULE_2, false);
    schrijf_van_output_array(output_teller_int);
    digitalWrite(OUTPUT_MODULE_2, true);
  }
  if(aantal_output_int > 48){
    output_teller_int = 48;
    digitalWrite(OUTPUT_MODULE_3, false);
    schrijf_van_output_array(output_teller_int);
    digitalWrite(OUTPUT_MODULE_3, true);
  }
  for(int x = 0; x < 4; x ++){
    if(duty_cycle_array_temp_int[x] != duty_cycle_array_vorig_int[x]){
      duty_cycle_array_int[x] = duty_cycle_array_temp_int[x];
      duty_cycle_array_vorig_int[x] = duty_cycle_array_temp_int[x];
    }
  }
  PWM_0->setPWM(1, PWM_0_UIT, freq_array_int[0], duty_cycle_array_int[0]);
  PWM_1->setPWM(1, PWM_1_UIT, freq_array_int[1], duty_cycle_array_int[1]);
  PWM_2->setPWM(1, PWM_2_UIT, freq_array_int[2], duty_cycle_array_int[2]);
  PWM_3->setPWM(1, PWM_3_UIT, freq_array_int[3], duty_cycle_array_int[3]);
}

void nu_naar_vorig(){
  for(int x = 0; x < 6; x ++){
    for(int y = 0; y < 64; y ++){
      status_array_vorig_bool[x][y] = status_array_bool[x][y];
    }
  }
}

void schrijf_van_output_array(int pagina_int){
  digitalWrite(UIT_0, status_array_bool[1][pagina_int + 0]);
  digitalWrite(UIT_1, status_array_bool[1][pagina_int + 1]);
  digitalWrite(UIT_2, status_array_bool[1][pagina_int + 2]);
  digitalWrite(UIT_3, status_array_bool[1][pagina_int + 3]);
  digitalWrite(UIT_4, status_array_bool[1][pagina_int + 4]);
  digitalWrite(UIT_5, status_array_bool[1][pagina_int + 5]);
  digitalWrite(UIT_6, status_array_bool[1][pagina_int + 6]);
  digitalWrite(UIT_7, status_array_bool[1][pagina_int + 7]);
  digitalWrite(UIT_8, status_array_bool[1][pagina_int + 8]);
  digitalWrite(UIT_9, status_array_bool[1][pagina_int + 9]);
  digitalWrite(UIT_10, status_array_bool[1][pagina_int + 10]);
  digitalWrite(UIT_11, status_array_bool[1][pagina_int + 11]);
  digitalWrite(UIT_12, status_array_bool[1][pagina_int + 12]);
  digitalWrite(UIT_13, status_array_bool[1][pagina_int + 13]);
  digitalWrite(UIT_14, status_array_bool[1][pagina_int + 14]);
  digitalWrite(UIT_15, status_array_bool[1][pagina_int + 15]);
}

void freq_array_reset(){
  for(int x= 0; x < 4; x++){
    freq_array_int[x] = 1;
  }
}

void ai_array_reset(){
  for(int x = 0; x < 4; x++){
    for(int y = 0; y < 2; y ++){
      ai_array_int[x][y] = 0;
    }
  }

}
void tmr_ctr_instelling_reset(){
  for(int x = 0; x < 64; x++){
    tmr_instelling_int[x] = 0;
    ctr_instelling_int[x] = 0;
  }
}

void status_array_reset(){
  for(int x = 1; x < 5; x ++){
    for(int y = 0; y < 64; y++){
      status_array_bool[x][y] = false;
    }
  }
  for(int y = 0; y < 64; y++){
    status_array_bool[5][y] = true;
  }
}

void tmr_ctr_reset(){
  for(int x = 0; x < 64; x++){
    tmr_nu_int[x] = (tmr_instelling_int[x] * 100);
    ctr_nu_int[x] = 0;
    ctru_vorig_bool[x] = false;
    ctrd_vorig_bool[x] = false;
  }
}

void totaal_reset(){
  status_array_reset();
  freq_array_reset();
  ai_array_reset();
  tmr_ctr_reset();
  tmr_ctr_instelling_reset();
  programma_array_reset();
  schrijf_output_nul();
}

void schrijf_output_nul(){
  digitalWrite(UIT_0, false);
  digitalWrite(UIT_1, false);
  digitalWrite(UIT_2, false);
  digitalWrite(UIT_3, false);
  digitalWrite(UIT_4, false);
  digitalWrite(UIT_5, false);
  digitalWrite(UIT_6, false);
  digitalWrite(UIT_7, false);
  digitalWrite(UIT_8, false);
  digitalWrite(UIT_9, false);
  digitalWrite(UIT_10, false);
  digitalWrite(UIT_11, false);
  digitalWrite(UIT_12, false);
  digitalWrite(UIT_13, false);
  digitalWrite(UIT_14, false);
  digitalWrite(UIT_15, false);
  digitalWrite(OUTPUT_MODULE_0, false);
  digitalWrite(OUTPUT_MODULE_0, true);
  digitalWrite(OUTPUT_MODULE_1, false);
  digitalWrite(OUTPUT_MODULE_1, true);
  digitalWrite(OUTPUT_MODULE_2, false);
  digitalWrite(OUTPUT_MODULE_2, true);
  digitalWrite(OUTPUT_MODULE_3, false);
  digitalWrite(OUTPUT_MODULE_3, true);
  for(int x = 0; x < 4; x ++){
    duty_cycle_array_int[x] = 0;
    duty_cycle_array_temp_int[x] = 0;
    duty_cycle_array_vorig_int[x] = 0;
  }
}

void buffer_array_links(){
  bool negen_negen_bool = true;
  while(negen_negen_bool){
    for(int x = 0; x < MAX_INST + 1; x ++){
      if(buffer_array_int[x] == 99){
        for(int y = x; y < MAX_INST + 1; y ++)
          buffer_array_int[y] = buffer_array_int[y + 1];
      }
    }
    negen_negen_bool = false;
    for(int x = 0; x < MAX_INST + 1; x ++){
      if(buffer_array_int[x] == 99){
        negen_negen_bool = true;
      }
    }
  }
}