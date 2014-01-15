// potentiometer
#define KNOB1  0
#define PEDAL 2

// LEDs
#define LED1  6
#define LED2  7

//vars
int volume;
int volumeChange;

void setup() {
  pinMode(LED1,OUTPUT);   
  pinMode(LED2,OUTPUT);
  digitalWrite(LED1,LOW);   
  digitalWrite(LED2,HIGH);
  volumeChange = 0;

  //start serial with midi baudrate 31250
  Serial.begin(31250);
  //Serial.begin(9600); 
}

void loop () {
  
  //read and convert pot to scale we can use 0 - 127
  volume = analogRead(PEDAL)/8;
  //Serial.println(volume);
  
  // trying to send continuous controller command
  // 0xB9 = Continuous Controller change command on channel 10 (9 in hexadecimal)
  // 0xB  = Expression pedal command (11 in decimal)
  // 0x07 = Volume command
  //Midi_Send(0xBF, 0x07, volume);
  
  if (volume != volumeChange) {
     //Serial.println("Volume:");
     //Serial.println(volume);
     //Serial.println("Volume Change:");
     //Serial.println(volumeChange);
     Midi_Send(0xBF, 0x07, volume);
     volumeChange = volume;
     digitalWrite(LED1, HIGH);
  } else {
    digitalWrite(LED1, LOW);
  }
  
}

void Midi_Send(byte cmd, byte cmd2, byte volume) {  
  Serial.write(cmd);
  Serial.write(cmd2);
  Serial.write(volume);
}


