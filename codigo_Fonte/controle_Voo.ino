// todos o leds vão em um ground comum
// resistor de 100 ohms
// ligar os leds nas portas PWM do arduino que tem o ~ seguido do numero, exemplo (~11)

#include <MPU6050.h>
#include <Wire.h>

MPU6050 mpu; // cria um objeto para manipular a mpu no codigo

const int ledEsq = 10; // led do lado esquerdo
const int ledDir = 5; // led do lado direito
const int ledFrent = 9; // led da frente
const int ledTraz = 3; // led de traz

void setup() {
  Wire.begin();
  Serial.begin(115200); // comunicação serial

  mpu.initialize(); // inicia a comunicação com a mpu

  pinMode(ledEsq, OUTPUT);
  pinMode(ledDir, OUTPUT);
  pinMode(ledFrent, OUTPUT);
  pinMode(ledTraz, OUTPUT);
}

void loop() {
  // cria seis variaveis que armazenam as leituras da mpu6050
  int16_t ax, ay, az, gx, gy, gz;

// mpu.getMotion6 ler os valores brutos dos sensores da mpu6050
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Normaliza os valores dos sensores para o intervalo de -90 a 90 graus
  int roll = map(gx, -32768, 32767, -90, 90);
  int pitch = map(gy, -32768, 32767, -90, 90);
  int yaw = map(gz, -32768, 32767, -90, 90);
  

  // Controle de LEDs com base no movimento de roll
  if (roll < 0) {
    int intensidade = map(roll, 0, -90, 0, 255);

    analogWrite(ledEsq, intensidade);
    analogWrite(ledDir, 0);
  } else {
    int intensidade = map(roll, 0, 90, 0, 255);

    analogWrite(ledEsq, 0);
    analogWrite(ledDir, intensidade);
  }

  // Controle de LEDs com base no movimento de pitch
  if (pitch < 0) {
    int intensidadePitch = map(pitch, -90, 0, 0, 255);

    analogWrite(ledFrent, intensidadePitch);
    analogWrite(ledTraz, 0);
  } else {
    int intensidadePitch = map(pitch, 0, 90, 0, 255);

    analogWrite(ledFrent, 0);
    analogWrite(ledTraz, intensidadePitch);
  }


  delay(100); // cria uma pausa de 0,1 segundos até repetir o loop do codigo novamente
}
