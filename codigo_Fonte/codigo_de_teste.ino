// todos o leds vão em um ground comum
// resistor de 100 ohms
// ligar os leds nas portas PWM do arduino que tem o ~ seguido do numero, exemplo (~11)

#include <Wire.h>

const int MPU = 0x68; // cendereço I2C da MPU-6050

// variaveis para armazenar os valores
float AccX, AccY, AccZ, Temp, GyrX, GyrY, GyrZ;

void setup() {
  Wire.begin();
  Serial.begin(9600); // comunicação serial

  Wire.beginTransmission(MPU);// inicia a comunicação com a mpu
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

// configurar fundo de escala do giroscopio
  Wire.beginTransmission(MPU);
  Wire.write(0x1B);
  Wire.write(0x00011000);
  Wire.endTransmission();

  // configurar fundo de escala do acelerometro
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);
  Wire.write(0b00011000);
  Wire.endTransmission();
}
void loop() {
// comandos para iniciar transmissão de dados
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true); // solicita os dados do sensor

  // Armazenar o valor dos sensores nas variaveis correspondentes
  AccX = Wire.read() << 8 | Wire.read(); //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AccY = Wire.read() << 8 | Wire.read(); //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AccZ = Wire.read() << 8 | Wire.read(); //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Temp = Wire.read() << 8 | Wire.read(); //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyrX = Wire.read() << 8 | Wire.read(); //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyrY = Wire.read() << 8 | Wire.read(); //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyrZ = Wire.read() << 8 | Wire.read(); //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  // Imprime o serial dos valores obtidos

  Serial.print(GyrX / 16.4);
  Serial.print(" ");
  Serial.print(GyrY / 16.4);
  Serial.print(" ");
  Serial.print(GyrZ / 16.4);
  Serial.print(" ");

  delay(100); // cria uma pausa de 0,1 segundos até repetir o loop do codigo novamente
}