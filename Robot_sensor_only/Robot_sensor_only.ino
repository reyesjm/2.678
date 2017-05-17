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
  digitalWrite (STDBY, LOW );
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
  float sense_right = analogRead(A7);
  float sense_mid = analogRead(A6);
  float sense_left = analogRead(A5);
  //float err = (vdes - vact);
  //float gain = .25;
  //int command = err * gain;
  //command = constrain(command,-255, 255);
  Serial.print(sense_right);
  Serial.print(" ");
  Serial.print(sense_mid);
  Serial.print(" ");
  Serial.println(sense_left);
  
  
  //motorWrite(120, AIN1, AIN2, PWMA);
  //motorWrite(120, BIN1, BIN2, PWMB);
  //delay(1000);

  //motorWrite(-120, AIN1, AIN2, PWMA);
  //motorWrite(-120, BIN1, BIN2, PWMB);
  //delay(1000);
  
  
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
