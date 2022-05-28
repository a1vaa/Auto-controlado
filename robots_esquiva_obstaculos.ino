#include <Servo.h> 
#include <NewPing.h>
#include <AFMotor.h>  

NewPing sonar(A0, A1, 200); //(trig,echo,dist max)
Servo myServo; 

int distancia = 0;
int distanciaD = 0;
int distanciaIz = 0;
boolean Booleano = false;

AF_DCMotor Motor1(1); 
AF_DCMotor Motor4(4);

char dato;
void setup() {
  Serial1.begin(9600);
  myServo.attach(10);  
  delay(1000); 
  myServo.write(0);
  delay(500);
  myServo.write(180);
  delay(500);
  myServo.write(90);
  Motor1.setSpeed(250);
  Motor4.setSpeed(250);
pinMode(52,OUTPUT);
}

void loop() {
    if (Serial1.available()) {
    dato = Serial1.read();
  
  switch (dato){
    case 'C':
     encendido();
    break;
    case 'F': 
    Adelante();
    break;
    case 'B':
    Reversa();
    break;
    case 'L':
    GirarIzquierda();
    break;
    case 'D':
    GirarDerecha();
    break;
    case 'S':
    Frenar();
    break;
  }
    }
    }

  
void encendido()
{  
distancia = medirDistancia();
if (distancia >= 25 && distancia <= 250)
{
  Adelante();
}
else if (distancia < 25)
{
  Frenar();
  delay(150);
  Reversa();
  delay(250);
  Frenar();
  delay(250);
  distanciaD = mirarDerecha();
  delay(250);
  distanciaIz = mirarIzquierda();
  delay(250);

  if(distanciaD >= distanciaIz)
    {
      GirarDerecha();
      Frenar();
    }
    else if(distanciaIz >= distanciaD)
    {
      GirarIzquierda();
      Frenar();
    }
  }
}

int mirarDerecha()
{
    myServo.write(0); 
    delay(350);
    int distancia = medirDistancia();
    return distancia;
}

int mirarIzquierda()
{
    myServo.write(180); 
    delay(350);
    int distancia = medirDistancia();
    delay(50);
    myServo.write(115); 
    return distancia;
}

int medirDistancia() {
  int distance = sonar.ping_cm(); 
  if (distance > 0){
    Serial.print("Distancia ");
    Serial.print(distance);
    Serial.println(" cm");
  distance=250;
  }
  return distance;
}

void Frenar() {
  Motor1.run(RELEASE); 
  Motor4.run(RELEASE);
}
  
void Adelante() {
 if(Booleano == false)
  {
    Booleano = true;
    Motor1.run(FORWARD);      
    Motor4.run(FORWARD);
    //controlVelocidad();
  }
}

void Reversa() {
    Booleano = false;
    Motor1.run(BACKWARD);      
    Motor4.run(BACKWARD);
    //controlVelocidad();
}  

void GirarDerecha() {
  Motor1.run(FORWARD);
  Motor4.run(BACKWARD);     
  delay(400);  
} 
 
void GirarIzquierda() {
  Motor1.run(BACKWARD);     
  Motor4.run(FORWARD);     
  delay(400);
} 

 /*void controlVelocidad(){
   for (int velocidad = 0; velocidad < 160; velocidad +=2) 
   {
      Motor1.setSpeed(velocidad);
      Motor4.setSpeed(velocidad);
      delay(3);
   }
  }
  */
