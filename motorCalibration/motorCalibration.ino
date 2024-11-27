#include <PulsePosition.h>

PulsePositionInput ReceiverInput(RISING);
float ReceiverValue[]={0, 0, 0, 0, 0, 0, 0, 0};
int ChannelNumber=0; 
int minValues[4] = {2000, 2000, 2000, 2000};

void read_receiver(void){ //Função que lê os valores do receptor
  ChannelNumber = ReceiverInput.available();
  if (ChannelNumber > 0) {
      for (int i=1; i<=ChannelNumber;i++){
    ReceiverValue[i-1]=ReceiverInput.read(i);
    }
  }
}

void setup() {
  Serial.begin(57600);
  pinMode(13, OUTPUT); 
  digitalWrite(13, HIGH);
  ReceiverInput.begin(14);
}
void loop() {
  
read_receiver();

for (int i = 0; i < 4; i++) {
    if (ReceiverValue[i] < minValues[i]) {
        minValues[i] = ReceiverValue[i];
    }
    if (ReceiverValue[i] > maxValues[i]) {
        maxValues[i] = ReceiverValue[i];
    }
}

// Imprime os valores no monitor serial para monitoramento
Serial.print("Throttle Min/Max: ");
Serial.print(minValues[2]);
Serial.print(" / ");
Serial.println(maxValues[2]);

Serial.print("Pitch Min/Max: ");
Serial.print(minValues[1]);
Serial.print(" / ");
Serial.println(maxValues[1]);

Serial.print("Roll Min/Max: ");
Serial.print(minValues[0]);
Serial.print(" / ");
Serial.println(maxValues[0]);

Serial.print("Yaw Min/Max: ");
Serial.print(minValues[3]);
Serial.print(" / ");
Serial.println(maxValues[3]);

delay(500); // Atualiza a cada 500ms
}



