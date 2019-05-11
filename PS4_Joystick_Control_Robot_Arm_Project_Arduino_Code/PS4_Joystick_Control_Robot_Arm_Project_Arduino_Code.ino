
#include <PS4USB.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
PS4USB PS4(&Usb);

bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;

int ix_axis_left;
int ix_left;
int iy_axis_left;
int iy_left;
int ix_axis_right;
int ix_right;

int g_angle = 90 ;
int b_angle = 90 ;
int s_angle = 90 ;
int e_angle = 90 ;

int vrep_b_angle;
int vrep_s_angle;
int vrep_e_angle;
int vrep_g_angle;

#include <VarSpeedServo.h>

 VarSpeedServo servo1, servo2, servo3, servo4;


void setup() {
  //Serial.begin(115200);
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect
#endif
  if (Usb.Init() == -1) {
    //Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt

    
    
  }
 // Serial.print(F("\r\nPS4 USB Library Started"));
  servo1.attach(4);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(7);

}

void loop() {
     //V-REP joint values   
        vrep_b_angle = map ( b_angle , 10, 180, -45, 125);
        vrep_s_angle = map ( s_angle, 10, 180, -100, 70);
        vrep_e_angle = map ( e_angle, 0, 180, 10, -170);
        vrep_g_angle = map ( g_angle, 80, 170, -20, 80);
        
    //serial_senddata();
        
  Usb.Task();

  if (PS4.connected()) {




// base servo control by left x axis pad on PS4 Controller         

     if (PS4.getAnalogHat(LeftHatX) && PS4.getAnalogHat(LeftHatX) < 100) {
     // Serial.print(F("\r\nLeft_X: "));
     // Serial.print(PS4.getAnalogHat(LeftHatX));
     // Serial.print(F("\r\nbase angle: "));
     // Serial.print(b_angle);
      ix_axis_left = map (PS4.getAnalogHat(LeftHatX), 0, 100, 30, 0);
      
      b_angle++;
      delay(40);
       if ( b_angle >= 10 || b_angle <= 180 ){
              b_angle++;
              }
       if ( b_angle < 10) {
              b_angle = 10; 
              }
       if (b_angle > 180) {
            b_angle = 180;
             }


      
      servo1.write(b_angle, ix_axis_left);
      serial_senddata();
      }
      
    if (PS4.getAnalogHat(LeftHatX) && PS4.getAnalogHat(LeftHatX) > 150){
       // Serial.print(F("\r\nLeft_X: "));
       // Serial.print(PS4.getAnalogHat(LeftHatX));
       // Serial.print(F("\r\nbase angle: "));
       // Serial.print(b_angle);
        ix_left = map(PS4.getAnalogHat(LeftHatX), 150, 255, 0, 30);

       b_angle--;
        delay(40);
       if ( b_angle >= 10 || b_angle <= 180 ){
              b_angle--;
              }
       if ( b_angle < 10) {
              b_angle = 10; 
              }
       if (b_angle > 180) {
            b_angle = 180;
             }
        servo1.write(b_angle, ix_left);
        serial_senddata();
         }

// shoulder servo control by left Y axis PS4 controller

     if (PS4.getAnalogHat(LeftHatY) && PS4.getAnalogHat(LeftHatY) < 100) { // These are the only analog buttons on the PS4 controller
     // Serial.print(F("\r\nLeft_Y: "));
     // Serial.print(PS4.getAnalogHat(LeftHatY));
     // Serial.print(F("\r\nshoulder angle: "));
     // Serial.print(s_angle);
      iy_axis_left = map (PS4.getAnalogHat(LeftHatY), 0, 100, 30, 0);
      s_angle++;
      delay(40);
       if ( s_angle >= 10 || s_angle <= 180 ){
              s_angle++;
              }
       if ( s_angle < 10) {
              s_angle = 10; 
              }
       if (s_angle > 180) {
            s_angle = 180;
             }
      servo2.write(s_angle, iy_axis_left);
      serial_senddata();
      }
      
    if (PS4.getAnalogHat(LeftHatY) && PS4.getAnalogHat(LeftHatY) > 150){
       // Serial.print(F("\r\nLeft_Y: "));
       // Serial.print(PS4.getAnalogHat(LeftHatY));
       // Serial.print(F("\r\nshoulder angle: "));
       // Serial.print(s_angle);
        iy_left = map (PS4.getAnalogHat(LeftHatY), 150, 225, 0, 30);

        s_angle--;
        delay(40);
       if ( s_angle >= 10 || s_angle <= 180 ){
              s_angle--;
              }
       if ( s_angle < 10) {
              s_angle = 10; 
              }
       if (s_angle > 180) {
            s_angle = 180;
             }
        servo2.write(s_angle, iy_left);
        serial_senddata();
         }


// ELBOW SERVO CONTROL BY PS4 RIGHT X AXIS  on PS4 controller


     if (PS4.getAnalogHat(RightHatY) && PS4.getAnalogHat(RightHatY) < 100) { // These are the only analog buttons on the PS4 controller
     // Serial.print(F("\r\nRight_X: "));
    //  Serial.print(PS4.getAnalogHat(RightHatX));
     // Serial.print(F("\r\nelbow angle: "));
     // Serial.print(e_angle);
      ix_axis_right = map (PS4.getAnalogHat(RightHatY), 0, 100, 30, 0);

     // Serial.print(F("\r\nRight_X inverse: "));
    //  Serial.print(ix_axis_right);
     e_angle++;
      delay(40);
       if ( e_angle >= 0 || e_angle <= 180 ){
              e_angle++;
              }
       if ( e_angle < 0) {
              e_angle = 0; 
              }
       if (e_angle > 180) {
            e_angle = 180;
             }
      servo3.write(e_angle, ix_axis_right);
      serial_senddata();
      }
      
    if (PS4.getAnalogHat(RightHatY) && PS4.getAnalogHat(RightHatY) > 150){
      ////  Serial.print(F("\r\nRight_X: "));
      //  Serial.print(PS4.getAnalogHat(RightHatX));
      //  Serial.print(F("\r\nelbow angle: "));
     //   Serial.print(e_angle);
        ix_right = map ( PS4.getAnalogHat(RightHatY), 150, 255, 0, 30);

        e_angle--;
         delay(40);
       if ( e_angle >= 0 || e_angle <= 180 ){
              e_angle--;
              }
       if ( e_angle < 0) {
              e_angle = 0; 
              }
       if (e_angle > 180) {
            e_angle = 180;
             }
        servo3.write(e_angle,  ix_right);
        serial_senddata();
         }

// gribber control by R2 & L2 analog buttons on PS4 controller
   if (PS4.getAnalogButton(L2)) { // These are the only analog buttons on the PS4 controller
      //Serial.print(F("\r\nL2: "));
     // Serial.print(PS4.getAnalogButton(L2));
     // Serial.print(F("\r\ngribber angle: "));
     // Serial.print(g_angle);
       g_angle++;
     delay(40);
       if ( g_angle >= 80 || g_angle <= 175 ){
              g_angle++;
              }
       if ( g_angle < 80) {
              g_angle = 80; 
              }
       if (g_angle > 175) {
            g_angle = 175;
             }       
              
       
      servo4.write(g_angle, PS4.getAnalogButton(L2));
      serial_senddata();
      }
      
    if (PS4.getAnalogButton(R2)){
        //Serial.print(F("\r\nR2: "));
       // Serial.print(PS4.getAnalogButton(R2));
       // Serial.print(F("\r\ngribber angle: "));
       // Serial.print(g_angle);

        
        g_angle--;
        delay(40);
       if ( g_angle >= 80 || g_angle <= 175 ){
              g_angle--;
              }
       if ( g_angle < 80) {
              g_angle = 80; 
              }
       if (g_angle > 175) {
            g_angle = 175;
             }
        servo4.write(g_angle, PS4.getAnalogButton(R2));
        serial_senddata();
         }
if (PS4.getButtonClick(CIRCLE)) {
  Position_1();
     Serial.print(35);
     Serial.print(",");
     Serial.print(-20);
     Serial.print(",");
     Serial.print(-80);
     Serial.print(",");  
     Serial.println(-20);
     delay(40);
}
if (PS4.getButtonClick(CROSS)) {
  Position_2();
     Serial.print(-45);
     Serial.print(",");
     Serial.print(-100);
     Serial.print(",");
     Serial.print(-170);
     Serial.print(",");  
     Serial.println(80);
     delay(40);
}
  if (PS4.getButtonClick(SQUARE)) {
  Position_3();
     Serial.print(125);
     Serial.print(",");
     Serial.print(-100);
     Serial.print(",");
     Serial.print(10);
     Serial.print(",");  
     Serial.println(47);
     delay(40);
}
if (PS4.getButtonClick(TRIANGLE)) {
  Position_4();

  
     Serial.print(50);
     Serial.print(",");
     Serial.print(-35);
     Serial.print(",");
     Serial.print(-155);
     Serial.print(",");  
     Serial.println(-20);
     delay(40);
}         
     }
        
       // delay(1000);

  }




  void serial_senddata(){
     
     Serial.print(vrep_b_angle);
     Serial.print(",");
     Serial.print(vrep_s_angle);
     Serial.print(",");
     Serial.print(vrep_e_angle);
     Serial.print(",");  
     Serial.println(vrep_g_angle);
    
     delay(40);
     return;
  }

void Position_1(){
  servo1.write(90, 35);
  servo2.write(90, 35);
  servo3.write(90, 35);
  servo4.write(80, 35);

  servo1.wait();
  servo2.wait();
  servo3.wait();
  servo4.wait();

  
  delay(300);
}

void Position_2(){
  servo1.write(10, 35);
  servo2.write(10, 35);
  servo3.write(180, 35);
  servo4.write(170, 35);

  servo1.wait();
  servo2.wait();
  servo3.wait();
  servo4.wait();
  
  delay(300);
  
  
}

void Position_3(){
  servo1.write(180, 35);
  servo2.write(10, 35);
  servo3.write(0, 35);
  servo4.write(140, 35);

  servo1.wait();
  servo2.wait();
  servo3.wait();
  servo4.wait();

  
  delay(300);
}


void Position_4(){
  servo1.write(105, 35);
  servo2.write(75, 35);
  servo3.write(165, 35);
  servo4.write(80, 35);

  servo1.wait();
  servo2.wait();
  servo3.wait();
  servo4.wait();

  
  delay(300);
}
  
