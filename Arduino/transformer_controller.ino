#include <CmdMessenger.h>


 // Initialize the PINs variables
 //        Name           PIN 
 const int input        = A5;
 const int select0      = A0;
 const int select1      = A1;
 const int select2      = A2;
 const int select3      = A3;
 const int select4      = A4;
 const int wr           = 2;
 const int cs           = 3;
 const int alarm        = 4;
 const int trip1        = 5;
 const int trip2        = 6;
 const int trip3        = 7;
 const int trip4        = 8;
 const int trip5        = 9;
 
 //Channel switch truth table
  const int CH[32][5] = {
    {0,0,0,0,0},//CH1
    {1,0,0,0,0},//CH2
    {0,1,0,0,0},//CH3
    {1,1,0,0,0},//CH4
    {0,0,1,0,0},//CH5
    {1,0,1,0,0},//CH6
    {0,1,1,0,0},//CH7
    {1,1,1,0,0},//CH8
    {0,0,0,1,0},//CH9
    {1,0,0,1,0},//CH10
    {0,1,0,1,0},//CH11
    {1,1,0,1,0},//CH12
    {0,0,1,1,0},//CH13
    {1,0,1,1,0},//CH14
    {0,1,1,1,0},//CH15
    {1,1,1,1,0},//CH16
    {0,0,0,0,1},//CH17
    {1,0,0,0,1},//CH18
    {0,1,0,0,1},//CH19
    {1,1,0,0,1},//CH20
    {0,0,1,0,1},//CH21
    {1,0,1,0,1},//CH22
    {0,1,1,0,1},//CH23
    {1,1,1,0,1},//CH24
    {0,0,0,1,1},//CH25
    {1,0,0,1,1},//CH26
    {0,1,0,1,1},//CH27
    {1,1,0,1,1},//CH28
    {0,0,1,1,1},//CH29
    {1,0,1,1,1},//CH30
    {0,1,1,1,1},//CH31
    {1,1,1,1,1},//CH32
  };

// Transformer arrays
float transformer1[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float transformer2[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float transformer3[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float transformer4[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float transformer5[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

// Transformer Status Array
bool transformerStatus[5] = {false, false, false, false, false};


void selectChannel(int channel){
   digitalWrite(cs,LOW);
   delay(10);
   digitalWrite(wr,LOW);
   delay(10);
   digitalWrite(select0,CH[channel][0]);
   digitalWrite(select1,CH[channel][1]);
   digitalWrite(select2,CH[channel][2]);
   digitalWrite(select3,CH[channel][3]);
   digitalWrite(select4,CH[channel][4]);
   delay(10);
   digitalWrite(wr,HIGH);
   digitalWrite(cs,HIGH);
}

void setup() {
  // put your setup code here, to run once:

// Setup the PINs
  pinMode(wr,OUTPUT);
  pinMode(cs,OUTPUT);
  pinMode(select0,OUTPUT);
  pinMode(select1,OUTPUT);
  pinMode(select2,OUTPUT);
  pinMode(select3,OUTPUT);
  pinMode(select4,OUTPUT);
  pinMode(alarm,OUTPUT);
  pinMode(trip1,OUTPUT);
  pinMode(trip2,OUTPUT);
  pinMode(trip3,OUTPUT);
  pinMode(trip4,OUTPUT);
  pinMode(trip5,OUTPUT);
  pinMode(input,INPUT);


}

void loop() {
  // put your main code here, to run repeatedly:

}
