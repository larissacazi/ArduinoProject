// Programa modificado do blog Flipeflop
//http://blog.filipeflop.com/wireless/tutorial-arduino-bluetooth-hc-05-mestre.html

 
//Carrega a biblioteca SoftwareSerial
#include <SoftwareSerial.h>

//Carrega a biblioteca Wire
#include<Wire.h>
    
//Define os pinos para a serial do bluetooth, pino 10 RX e pino 11 TX  
SoftwareSerial mySerial(10, 11); // RX, TX  


//Endereco I2C do MPU6050
const int MPU=0x68;  
//Variaveis para armazenar valores dos sensores
int AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

    
void setup()   
{  
  //Inicia a serial  
  Serial.begin(115200);  
  Serial.println("Digite os comandos AT :");  
  //Inicia a serial configurada nas portas 10 e 11
  mySerial.begin(9600);  

  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  
  //Inicializa o MPU-6050
  Wire.write(0); 
  Wire.endTransmission(true);
}  
    
void loop()  
{  
  // Read device output if available.  
  if (mySerial.available()) 
  {  
     while(mySerial.available()) 
     { // Enquanto tiver mais dados ele continua lendo
      delay(10); //Aguarda 10ms
      Serial.write((char)mySerial.read()); 
     }  
   Serial.println(""); //Pula para a linha seguinte
  }  
   
  // Lê dados pela usb e envia para o bluetooth.  
  if (Serial.available())
  {  
    delay(10); // Aguarda 10ms 
    mySerial.write(Serial.read());  
  }  

  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  //Solicita os dados do sensor
  Wire.requestFrom(MPU,14,true);  
  //Armazena o valor dos sensores nas variaveis correspondentes
  AcX=Wire.read()<<8|Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  
  //Envia valor X do acelerometro para a serial e o LCD
  Serial.print("AcX = "); Serial.print(AcX);

  //Envia valor Y do acelerometro para a serial e o LCD
  Serial.print(" | AcY = "); Serial.print(AcY);
  
  //Envia valor Z do acelerometro para a serial e o LCD
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  
  //Envia valor da temperatura para a serial e o LCD
  //Calcula a temperatura em graus Celsius
  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);
  
  //Envia valor X do giroscopio para a serial e o LCD
  Serial.print(" | GyX = "); Serial.print(GyX);
  
  //Envia valor Y do giroscopio para a serial e o LCD  
  Serial.print(" | GyY = "); Serial.print(GyY);
  
  //Envia valor Z do giroscopio para a serial e o LCD
  Serial.print(" | GyZ = "); Serial.println(GyZ);
  
  //Aguarda 300 ms e reinicia o processo
  delay(300);
}
