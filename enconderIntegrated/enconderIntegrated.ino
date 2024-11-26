#include <PulsePosition.h>
#include <ams_as5048b.h>
#include <Wire.h>

#define U_RAW 1
#define U_TRN 2
#define U_DEG 3
#define U_RAD 4
#define U_GRAD 5
#define U_MOA 6
#define U_SOA 7
#define U_MILNATO 8
#define U_MILSE 9
#define U_MILRU 10

AMS_AS5048B mysensor;
PulsePositionInput ReceiverInput(RISING);
float ReceiverValue[]={0, 0, 0, 0, 0, 0, 0, 0};
int ChannelNumber=0; 
int PWM_MAX = 4095;
int A_MAX = 410;
float InputThrottle;
float InputPitch;
float InputRoll;
float theta;

void read_receiver(void){ // lê a posição dos sticks e dá update no array ReceiverValue
  ChannelNumber = ReceiverInput.available();
  if (ChannelNumber > 0) {
  for (int i=1; i<=ChannelNumber;i++){
    ReceiverValue[i-1]=ReceiverInput.read(i);
    }
  }
}

void read_enconder(void){
  theta = mysensor.angleR(U_RAD,false); // depois ver os parametros da funçao para saber o que faz o false
}

void setup() {
  Serial.begin(57600);

  Wire.begin();
  //init AMS_AS5048B object
	mysensor.begin();
	//consider the current position as zero
	mysensor.setZeroReg();

  ReceiverInput.begin(14);
  analogWriteFrequency(1, 250);
  analogWriteResolution(12);

  delay(250);
  
  while (ReceiverValue[2] < 1020) { // para não obter arranques indesejados
      read_receiver();
      delay(4);
    }
}


void loop() {
    // Ler valores do receptor e do encoder
    read_receiver();
    read_encoder();

    // Normalizar entradas do receptor // testar os valores de cada um dos canais para obter algo mais preciso
    float InputThrottle = map(ReceiverValue[2], 1000, 2000, 0, PWM_MAX);
    float InputPitch = mapf(ReceiverValue[1], 1000, 2000, -1.0, 1.0);
    float InputRoll = mapf(ReceiverValue[0], 1000, 2000, -1.0, 1.0);
    float InputYaw = mapf(ReceiverValue[3], 1000, 2000, -1.0, 1.0);

    // Calcular amplitude dinâmica
    float amplitude = min(A_max, InputThrottle / 4.0);

    // Calcular modulação da velocidade
    float InputVelocity = InputThrottle + amplitude * (InputPitch * sin(theta) + InputRoll * cos(theta));

    // Limitar velocidade ao intervalo do PWM
    InputVelocity = constrain(InputVelocity, 0, PWM_MAX);

    // Enviar sinal PWM ao motor
    analogWrite(1, (int)InputVelocity);
}
