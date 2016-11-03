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
 const int start        = 10;
 
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
int transformer1[6] = {0, 0, 0, 0, 0, 0};
int transformer2[6] = {0, 0, 0, 0, 0, 0};
int transformer3[6] = {0, 0, 0, 0, 0, 0};
int transformer4[6] = {0, 0, 0, 0, 0, 0};
int transformer5[6] = {0, 0, 0, 0, 0, 0};

// Transformer Status Array
bool transformerStatus[5] = {false, false, false, false, false};

// Transformer Max Current Array
int maxCurrent[5] = {0, 0, 0, 0, 0};

// Dummy Variables
bool tripind1 = false;
bool tripind2 = false;
bool tripind3 = false;
bool tripind4 = false;
bool tripind5 = false;

// Max Voltage is always 230
#define VOLTAGE_MAX        230

/* Define available CmdMessenger commands */
enum {
    PING,
    SEND_MAX_CURRENT,
    GET_STATUS,
    GET_STATUS_RSP,
    GET_DATA,
    GET_DATA_RSP,
    STOP_TRANS,
    START_ALARM,
    RESET_ALARM,
    RESET_TRIP,
    STOP,
    RESPONSE,
};

/* Initialize CmdMessenger -- this should match PyCmdMessenger instance */
const long BAUD_RATE = 1000000;
CmdMessenger cmd = CmdMessenger(Serial,',',';','/');


/* Attach callbacks for CmdMessenger commands */
void attach_callbacks(void) { 

    cmd.attach(PING,receivePing);
    cmd.attach(SEND_MAX_CURRENT,receiveMaxCurrent);
    cmd.attach(GET_STATUS,sendTransformerStatus);
    cmd.attach(GET_DATA,sendTransformerData);
    cmd.attach(STOP_TRANS,receiveStopCommand);
    cmd.attach(START_ALARM,receiveSetAlarm);
    cmd.attach(RESET_ALARM,receiveResetAlarm);
    cmd.attach(RESET_TRIP,receiveResetTripped);
    cmd.attach(STOP,stopTransformers);
            
    cmd.attach(processUnknownCommand);
}

// Handle unknown commands
void processUnknownCommand(void){
    cmd.sendCmd(RESPONSE,"Error");
}

// Handle Ping
void receivePing(void){
    
    digitalWrite(start,HIGH);

    cmd.sendCmd(RESPONSE,"OK");
}

// Get the Max Currents
void receiveMaxCurrent(void){
   
   int transformer = cmd.readBinArg<int>();
   int current = cmd.readBinArg<int>();

   // Set the max current
   maxCurrent[transformer] = current;

   // dummy
   if (current){
      transformerStatus[transformer] = true;
   }
   else
   {
      transformerStatus[transformer] = false;
   }
   
   cmd.sendCmd(RESPONSE,"OK");
}


// Send the Transformer Status
void sendTransformerStatus(void){
   cmd.sendCmdStart(GET_STATUS_RSP);
   for (int i = 0; i < 5; i++)       
       cmd.sendCmdBinArg(transformerStatus[i]);
   
   cmd.sendCmdEnd();  
}

// Send the Transformer Data
void sendTransformerData(void){
   

   cmd.sendCmdStart(GET_DATA_RSP);

   for (int i = 0; i < 6; i++){
          cmd.sendCmdBinArg(transformer1[i]);
   }
   for (int i = 0; i < 6; i++){        
          cmd.sendCmdBinArg(transformer2[i]);
   }
   for (int i = 0; i < 6; i++){
          cmd.sendCmdBinArg(transformer3[i]);
   }
   for (int i = 0; i < 6; i++){        
          cmd.sendCmdBinArg(transformer4[i]);
   }
   for (int i = 0; i < 6; i++){
          cmd.sendCmdBinArg(transformer5[i]);     
   }
   
   cmd.sendCmdEnd();   

   // Get the next set of Transformer Data
   refreshTransformerData();   
}

// Set the Trip Line for the requested Transformer
void receiveStopCommand(void){
  
   int transformer = cmd.readBinArg<int>();
   
   if (transformer == 0){
      digitalWrite(trip1,HIGH);
      tripind1 = true;
   }
   else if (transformer == 1){
      digitalWrite(trip2,HIGH);
      tripind2 = true;   
   }
   else if (transformer == 2){
      digitalWrite(trip3,HIGH);
      tripind3 = true;
   }   
   else if (transformer == 3){
      digitalWrite(trip4,HIGH);
      tripind4 = true;   
   }
   else if (transformer == 4){
      digitalWrite(trip5,HIGH);  
      tripind5 = true;
   }

   cmd.sendCmd(RESPONSE,"OK");   
}

// Trip the Main Line
void stopTransformers(void){
     digitalWrite(start,LOW);

   for (int i = 0; i < 5; i++){       
       transformerStatus[i] = false;
   }

   tripind1 = true;
   tripind2 = true;
   tripind3 = true;
   tripind4 = true;
   tripind5 = true;
   
   cmd.sendCmd(RESPONSE,"OK");

}

// Reset the Trip Lines for the all Transformers
void receiveResetTripped(void){

   tripind1 = false;
   tripind2 = false;
   tripind3 = false;
   tripind4 = false;
   tripind5 = false;

   for (int i = 0; i < 5; i++){       
       transformerStatus[i] = true;
   }
  
   digitalWrite(trip1,LOW);
   digitalWrite(trip2,LOW);   
   digitalWrite(trip3,LOW);   
   digitalWrite(trip4,LOW);   
   digitalWrite(trip5,LOW);   

   cmd.sendCmd(RESPONSE,"OK");   
}

// Set the Alarm Port
void receiveSetAlarm(void){
  
   digitalWrite(alarm,HIGH);
     
   cmd.sendCmd(RESPONSE,"OK");     
}

// Reset the Alarm Port
void receiveResetAlarm(void){
  
   digitalWrite(alarm,LOW);
     
   cmd.sendCmd(RESPONSE,"OK");     
}


void selectChannel(int channel){
   digitalWrite(cs,LOW);
   delay(1);
   digitalWrite(wr,LOW);
   delay(1);
   digitalWrite(select0,CH[channel][0]);
   digitalWrite(select1,CH[channel][1]);
   digitalWrite(select2,CH[channel][2]);
   digitalWrite(select3,CH[channel][3]);
   digitalWrite(select4,CH[channel][4]);
   delay(1);
   digitalWrite(wr,HIGH);
   digitalWrite(cs,HIGH);
}

// Refresh the Transformer Data
void refreshTransformerData(void){      
     
     getDataTransformer1();
     getDataTransformer2();
     getDataTransformer3();
     getDataTransformer4();
     getDataTransformer5();               
}

// Transformer 1
void getDataTransformer1(void){
  
   // Get Transformer 1 values
   int in;   
   bool statusInd = false;
   
   for (int i = 0; i < 6; i++){
       selectChannel(i);
       //in = analogRead (input);
       if (tripind1 == true || transformerStatus[0] == false)
          in = 0;
       else
          in = random(1023);
       
       if (i < 3)
          transformer1[i]  = map(in, 0, 1023, 0, VOLTAGE_MAX);
       else
          transformer1[i]  = map(in, 0, 1023, 0, maxCurrent[0]);
             
       if (transformer1[i] > 0)
          statusInd = true;
              
       delay(1);
   }

   transformerStatus[0] = statusInd;   
}

// Transformer 2
void getDataTransformer2(void){
  
   // Get Transformer 2 values
   int in;
   bool statusInd = false;
   int j = 0;
   
   for (int i = 6; i < 12; i++){      
       selectChannel(i);
       //in = analogRead (input);
       if (tripind2 == true || transformerStatus[1] == false)
          in = 0;
       else
          in = random(1023);
       
       if (i < 9)
          transformer2[j]  = map(in, 0, 1023, 0, VOLTAGE_MAX);
       else
          transformer2[j]  = map(in, 0, 1023, 0, maxCurrent[1]);
             
       if (transformer2[j] > 0)
          statusInd = true;

       j++;
       
       delay(1);
   }

   transformerStatus[1] = statusInd;   
}

// Transformer 3
void getDataTransformer3(void){
  
   // Get Transformer 3 values
   int in;
   bool statusInd = false;
   int j = 0;
   
   for (int i = 12; i < 18; i++){
       selectChannel(i);
       //in = analogRead (input);
       if (tripind3 == true || transformerStatus[2] == false)
          in = 0;
       else
          in = random(1023);
       
       if (i < 15)
          transformer3[j]  = map(in, 0, 1023, 0, VOLTAGE_MAX);
       else
          transformer3[j]  = map(in, 0, 1023, 0, maxCurrent[2]);
             
       if (transformer3[j] > 0)
          statusInd = true;

       j++;
       
       delay(1);
   }
   
   transformerStatus[2] = statusInd;
}

// Transformer 4
void getDataTransformer4(void){
  
   // Get Transformer 4 values
   int in;
   bool statusInd = false;
   int j = 0;
   
   for (int i = 18; i < 24; i++){
       selectChannel(i);
       //in = analogRead (input);
       if (tripind4 == true || transformerStatus[3] == false)
          in = 0;
       else
          in = random(1023);
       
       if (i < 21)
          transformer4[j]  = map(in, 0, 1023, 0, VOLTAGE_MAX);
       else
          transformer4[j]  = map(in, 0, 1023, 0, maxCurrent[3]);
             
       if (transformer4[j] > 0)
          statusInd = true;

       j++;
       
       delay(1);
   }
   
   transformerStatus[3] = statusInd;
}

// Transformer 5
void getDataTransformer5(void){
  
   // Get Transformer 5 values
   int in;
   bool statusInd = false;
   int j = 0;
   
   for (int i = 24; i < 30; i++){
       selectChannel(i);
       //in = analogRead (input);
       if (tripind5 == true || transformerStatus[4] == false)
          in = 0;
       else
          in = random(1023);
       
       if (i < 27)
          transformer5[j]  = map(in, 0, 1023, 0, VOLTAGE_MAX);
       else
          transformer5[j]  = map(in, 0, 1023, 0, maxCurrent[4]);
             
       if (transformer5[j] > 0)
          statusInd = true;

       j++;
       
       delay(1);
   }

   transformerStatus[4] = statusInd;   
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
  pinMode(start,OUTPUT);
  pinMode(input,INPUT);

  // Setup Serial and attach callbacks to setup the serial messages
  Serial.begin(BAUD_RATE);
  attach_callbacks();

  randomSeed(analogRead(0));

   // Get the Initial Transformer Data
   //refreshTransformerData();  
}

void loop() {
   // put your main code here, to run repeatedly:

   // Begin Serial Communication
   cmd.feedinSerialData();

}
