// Pololu #713 motor driver pin assignments
  const int PWMA = 11; // Pololu drive A
  const int AIN2 = 10;
  const int AIN1 = 9;
  const int STDBY = 8;
  const int BIN1 = 7; // Pololu drive B
  const int BIN2 = 6;
  const int PWMB = 5;
  bool flag = false;

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
  int sense_right = analogRead(A7);
  int sense_mid = analogRead(A6);
  int sense_left = analogRead(A5);
  int vdes_r = 915;
  int vdes_m = 900;
  int vdes_l = 875;
  int err_right = abs(vdes_r - sense_right);
  int err_mid = abs(vdes_m - sense_mid);
  int err_left = abs(vdes_l - sense_left);

  int threshold = 150;
  int v_right;
  int v_left;
  int t = 0;
  if (flag) {
    t = millis();
  }

  //THIN LINE AND CHECKERBOARD
  if(t/1000 >= 17 && t/1000 <= 28){
    if(err_mid < threshold) {
      motorWrite(255, AIN1, AIN2, PWMA);
      motorWrite(255, BIN1, BIN2, PWMB);
    }
    //turn right
    else if(err_left < threshold) {
      v_left = map(err_left, 0,785, 50, 128);
      v_right = (int)-0.25*v_left;
      motorWrite(v_right, AIN1, AIN2, PWMA);
      motorWrite(v_left, BIN1, BIN2, PWMB);
      delay(100);
    }
    //turn left
    else {
      v_right = map(err_right, 0,785, 100, 255);
      v_left = (int)  -0.25*v_right;
      motorWrite(v_right, AIN1, AIN2, PWMA);
      motorWrite(v_left, BIN1, BIN2, PWMB);
      delay(100);
    }
  }

  //WHITE GAP
  if(t/1000 >= 36 && t/1000 <= 40){
      motorWrite(255, AIN1, AIN2, PWMA);
      motorWrite(255, BIN1, BIN2, PWMB);
    
  }
  
  //turn right, normal
  if(err_left >= threshold) {
    flag = true;
    v_left = map(err_left, 0,785, 100, 255);
    if(t/1000 >= 28 && t/1000 <= 36 ) {
        v_right = -v_left;
    }
    else{
      v_right = (int)-0.9*v_left;
    }
    motorWrite(v_right, AIN1, AIN2, PWMA);
    motorWrite(v_left, BIN1, BIN2, PWMB);
    delay(100);
  }
  
  //turn left
  else if(err_right >= threshold) {
    flag = true;
    v_right = map(err_right, 0,785, 100, 255);
    if(t/1000 >= 28 && t/1000 <= 34) {
        v_left = -v_right;
    }
    else{
      v_left = (int)-0.9*v_right;
    }
    motorWrite(v_right, AIN1, AIN2, PWMA);
    motorWrite(v_left, BIN1, BIN2, PWMB);
    delay(100);
  }
  
  else if(err_right < threshold && err_left < threshold){
    motorWrite(255, AIN1, AIN2, PWMA);
    motorWrite(255, BIN1, BIN2, PWMB);
  }

  /* ProportionAL controller
  //float gain = .25;
  //int command = err * gain;
  //command = constrain(command,-255, 255);
  */ 

  /* serial monitor
  //Serial.print(sense_right);
  //Serial.print(" ");
  //Serial.print(sense_mid);
  //Serial.print(" ");
  //Serial.print(sense_left);
  //Serial.print(" ");
  //Serial.print(err_right);
  //Serial.print(" ");
  //Serial.println(err_left);
  //Serial.print(" ");
  //Serial.print(v_right);
  //Serial.print(" ");
  //Serial.println(v_left);
  Serial.println(t/1000);
  */
  
  
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
