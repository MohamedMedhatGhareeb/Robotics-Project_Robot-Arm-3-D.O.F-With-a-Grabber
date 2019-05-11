#include <VarSpeedServo.h>
#include <math.h>

/* Arm dimensions( mm ) */
#define a1 55 //a1 = base to 2# joint length arm
#define a2 111 //a2 = length arm from joint 2 to 3
#define a3 140 //a3 = length arm from joint #3 to gripper


#define base_servo 4
/* Using Servo 3.2 Kg.cm  */
#define shoulder_servo 5
/* Using Servo 3.2 Kg.cm  */
#define elbow_servo 6
/* Using Micro servo 1.3 Kg.cm */
#define Gripper_servo 7
/*Using Micro servo 1.3 Kg.cm */

  float x_coord;            // X coordinate of the end point
  float y_coord;            // Y coordinate of the end point
  float z_coord;            // Z coordinate of the end point
  float gripper_angle;      //gripper angle


#define speed1 30
#define speed2 100
#define speed3 170


//Some Values to be used 
#define pi 3.141592654

VarSpeedServo servo1,servo2,servo3,servo4;





void setup()
{
servo1.attach( base_servo, 544, 2400 ); //setting min and max values in microseconds,default min is 544, max is 2400
servo2.attach( shoulder_servo, 544, 2400 );
servo3.attach( elbow_servo, 544, 2400 );
servo4.attach( Gripper_servo, 544, 2400 );


//servos.start(); //Start the servo shield
servo_park();
delay( 2000 );
Serial.begin( 9600 );
Serial.println("Start");
}



void loop()
{
// test fixed positions

//set_arm ( 20, 20, 0, 90, 10);
//delay(1000);
//set_arm ( 20, 50, 0, 150, 10);
//delay(1000);
//set_arm ( 20, 70, 0, 150, 10);
//delay(3000);


  
if(Serial.available()>0){

 char data = Serial.read();
  switch(data) {

    case 'x' : x_coord++; //adjust x position up
    break;
    case 'u' : x_coord--; // adjust x position down
    break;
    
    case 'y' : y_coord++; // adjust y position up
    break;
    case 'v' : y_coord--; // adjust y position down
    break;
    
    case 'z' : z_coord++; // agjust z position up
    break;
    case 'w' : z_coord--; // adjust z postion down
    break;
    
    case 'r' : gripper_angle++; //adjust gripper wider
               // set boundries to the gripper
              if( gripper_angle > 150 ) {
              gripper_angle = 120;
             }
              break;
    case 's' : gripper_angle--; // adjust gripper narrower
             // set boundries to the gripper
              if( gripper_angle < 70 ) {
              gripper_angle = 170;
             }
             break;
             
     case 'm' : arm_park();
     break;    

     case 'n' : servo_park();
     break;     
     }

  set_arm(x_coord, y_coord, z_coord, gripper_angle, speed2);
 
   }

}


// XYZ Positioning using the base, shoulder, elbow joints 

void set_arm( float x, float y, float z, float gripper, int servospeed){


float theta1_r = atan2( x, y ); // in radian value
float theta1_d = ((theta1_r*180)/pi);

if(theta1_d >= 10 || theta1_d <= 180 ){

            theta1_d = theta1_d;
   }
   if( theta1_d <=9){
    theta1_d =10;
   }

   if ( theta1_d >= 181 ){
    theta1_d = 180;
   }

float r_distance = sqrt(( x * x ) + ( y * y ));


float s = z -a1 ; // length in mm

float alpha_r = asin(s/r_distance); // s must always be less than R distance 
float alpha_d = ((alpha_r*180)/pi);



float theta2_r = alpha_r + acos((sq(a2)+sq(r_distance)-sq(a3))/(2*a2*r_distance));
float theta2_d = ((theta2_r*180)/pi);


 if(theta2_d >= 10 || theta2_d <= 180 ){

            theta2_d = theta2_d;
   }
   if( theta2_d <=9 ){
    theta2_d = 10;
   }

   if (theta2_d >= 181 ) {
    theta2_d = 180;
   }




float theta3_r = pi - acos((sq(a1)+sq(a3)-sq(r_distance))/(2*a2*a3));
float theta3_d = ((theta3_r*180)/pi);


if(theta3_d >= 0 || theta3_d <= 180 ){

            theta3_d = theta3_d;
   }
   if( theta3_d <=0 ){
    theta3_d = 0;
   }

   if( theta3_d > 180) {
    theta3_d = 180 ;
   }


servo1.write ( theta1_d, servospeed);
servo2.write ( theta2_d, servospeed);
servo3.write ( theta3_d, servospeed);
servo4.write ( gripper, servospeed);
servo1.wait();
servo2.wait();
servo3.wait();
servo4.wait();
Serial.print("T1:");
Serial.print(theta1_d);
Serial.print("           T2:");
Serial.print(theta2_d);
Serial.print("         T3:");
Serial.println(theta3_d);

Serial.print("X:");
Serial.print(x);
Serial.print("           Y:");
Serial.print(y);
Serial.print("         Z:");
Serial.println(z);

delay(100);  // delay to give the robot time to perform the required position

}



void servo_park(){                    // park position using servo angles
  servo1.write ( 150, speed1); 
  //servo.setposition(base_servo ): (Angle, Speed)
  servo2.write ( 105, speed1); 
  //servo.setposition( shoulder_servo )
  servo3.write ( 170, speed1);
  //servo.setposition( elbow_servo )
  servo4.write ( 80, speed1);
  //servo.setposition( Gripper_servo )
  servo1.wait();
  servo2.wait();
  servo3.wait();
  servo4.wait();
  delay(500);

  return;
}

void arm_park(){  // park position using XYZ Co-Ordinates
  set_arm(x_coord = 70, y_coord = 0, z_coord = 0, gripper_angle= 140, speed1);
  delay (500);
}



void zero_x()   //fixed y axis movement
{
for( double yaxis = 250.0; yaxis < 400.0; yaxis += 1 ) {
   Serial.print(" Y axis = ");
   Serial.println(yaxis);
   set_arm( 0, yaxis, 200.0, 0 ,10);
   delay( 10 );
   }
   delay(1000);
for( double yaxis = 400.0; yaxis > 250.0; yaxis -= 1 ) {
   Serial.print(" Y axis = ");
   Serial.println(yaxis);
   set_arm( 0, yaxis, 200.0, 0 ,10);
   delay( 10 );
   }
}
