/*Auto-controlado
es un autito controlado por bluetooth atreves de un joystick de una app en arduino*/
#include <Servo.h> 
#include <NewPing.h>
#include <AFMotor.h>  

NewPing sonar(A0, A1, 250); //(trig,echo,dist max) Defie el sensor(trig,Echo, max de distancia)
Servo myServo;  //Servo lo declaro como de tipo servo de la libreria servo 
Servo servo1;
int distancia = 0;
int distanciaD = 0;
int distanciaIz = 0;
boolean Booleano = false;

AF_DCMotor Motor1(1); //conectar al motor 1 //la libreria del motor se la declara o programa 
AF_DCMotor Motor4(4); //conectar al motor 4 // void loop (programa) // la libreria 
void setup () { 
  Serial.begin(9600);//declaro al serial
myServo.attach(10);  //declaro uso del programa de la libreria servo
  delay(1000); 
  myServo.write(0);// muestro el my servo a 0º
  delay(500);
  myServo.write(180); // muestro 
  delay(500);
  myServo.write(90);
  Motor1.setSpeed(250); //hago uso de un programa de la libreria AFMOTOR de la max 250 
  Motor4.setSpeed(250);
  servo1.write(90);
  servo1.write(0);
}
void loop (){
  servo1.write(90);
  servo1.write(0);º
distancia = medirDistancia();//medir distanci es una programa de la lbreria que mide distancia New PING , calcula la distanci sobre 2 
if (distancia >= 25 && distancia <= 250)// si la distancia entra entre 25 y 250 avan_a 
{
  Adelante();// si es verdadero es el avance, llamoa un void (prohtamacion orientado a objeto)
}
else if (distancia < 20 ) {// si no , si la distancia es 20 //detecta
  Frenar();//llama al objeto frenar
  delay(150);// pausa eser
  Reversa();//llma al objeto reversa 
  delay(250);
  Frenar();// llamo al objetivo frenar
  delay(250); 
  distanciaD = mirarDerecha(); //g 
  delay(250);
  distanciaIz = mirarIzquierda();
  delay(250);

  if(distanciaD >= distanciaIz) // si la distancia 
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

int mirarDerecha()//programa 
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
    return distance;// lo tuve que usar palabra vieja  
  }
  
void Frenar() {//
  Motor1.run(RELEASE); 
  Motor4.run(RELEASE);
}
  
void Adelante() {//objeto adelante, estoy llamando a la programacion orientada objeto 
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
 
void GirarDerecha() { // una rueda
  Motor1.run(FORWARD); // 
  //Motor4.run(BACKWARD);     
  delay(1000);  
} 
 
void GirarIzquierda() {//problema de rosamiento 
 // Motor1.run(BACKWARD);    //sacar uno 
  Motor4.run(FORWARD);     
  delay(1000);
} 
