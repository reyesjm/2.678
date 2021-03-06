// Pololu #713 motor driver pin assignments
  const int PWMA = 11; // Pololu drive A
  const int AIN2 = 10;
  const int AIN1 = 9;
  const int STDBY = 8;
  const int BIN1 = 7; // Pololu drive B
  const int BIN2 = 6;
  const int PWMB = 5;

void setup (){

  pinMode (STDBY, OUTPUT );
  digitalWrite (STDBY, HIGH );
  pinMode (PWMA, OUTPUT );
  pinMode (AIN1, OUTPUT );
  pinMode (AIN2, OUTPUT );
  pinMode (PWMB, OUTPUT );
  pinMode (BIN1, OUTPUT );
  pinMode (BIN2, OUTPUT );
  Serial.begin(9600);
}

void loop ()
{
  int vdes = analogRead(A0);
  int vact = analogRead(A1);
  float err = (vdes - vact);
  float gain = .25;
  int command = err * gain;
  command = constrain(command,-255, 255);
  
  motorWrite(command, AIN1, AIN2, PWMA);
  delay(20);
  
  
}

void motorWrite (int motorSpeed, int pin_IN1, int pin_IN2, int pin_PWM )
{
    if (motorSpeed < 0){
	digitalWrite(pin_IN1, HIGH);
	digitalWrite(pin_IN2, LOW);
    }
    else{
	digitalWrite(pin_IN2, HIGH);
	digitalWrite(pin_IN1, LOW);
    }
    
    motorSpeed = abs(motorSpeed);
    motorSpeed = constrain(motorSpeed, 0, 255);
    analogWrite(pin_PWM, motorSpeed);
}
