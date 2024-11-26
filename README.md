# DDMRAV

código para implementar antes de correr o swashplate:

int minValues[4] = {2000, 2000, 2000, 2000}; // Inicialmente valores altos
int maxValues[4] = {1000, 1000, 1000, 1000}; // Inicialmente valores baixos

void setup() {
    Serial.begin(9600);
}

void loop() {
    read_receiver(); // Função que lê os valores do receptor em ReceiverValue

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
