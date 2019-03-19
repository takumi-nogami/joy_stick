#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int32.h>
#include <AccelStepper.h>

#define EnablePin_R 12
#define StepPin_R 8
#define DirPin_R 7

#define EnablePin_L 6
#define StepPin_L 5
#define DirPin_L 4

ros::NodeHandle node;
geometry_msgs::Point msg;
ros::Publisher message("cmd_msg", &msg);

AccelStepper stepperL(1, StepPin_L, DirPin_L);
AccelStepper stepperR(1, StepPin_R, DirPin_R);

int fg=0;
float Interval;

void stepper_Callback(const geometry_msgs::Twist &stepper){
  fg = 1;
  if(stepper.linear.x>0.5){
    digitalWrite(DirPin_R, HIGH);
    digitalWrite(DirPin_L, LOW);
    Interval = interval(stepper.linear.x);
  }else if(stepper.linear.x<-0.5){
    digitalWrite(DirPin_R, LOW);
    digitalWrite(DirPin_L, HIGH);
    Interval = interval(-stepper.linear.x);
  }else if(stepper.angular.z>0.5){  //risht
    digitalWrite(DirPin_L,HIGH); // 5番ピンをHigh状態へ
    digitalWrite(DirPin_R,HIGH);
    Interval = interval(stepper.angular.z);
  }else if(stepper.angular.z<-0.5){  //left
    digitalWrite(DirPin_L,LOW);  // 5番ピンをLow状態へ
    digitalWrite(DirPin_R,LOW);
    Interval = interval(-stepper.angular.z);
  }else{
    fg = 0;
  }
}

float interval(float x){
  float y;
  y = -1000*x + 1500;
  return y;
}

ros::Subscriber<geometry_msgs::Twist>stepper("cmd_stepper", &stepper_Callback);

void setup() { 
  pinMode(EnablePin_L,OUTPUT); // Enable
  pinMode(EnablePin_R,OUTPUT); // Enable
  
  pinMode(StepPin_L,OUTPUT); // Step
  pinMode(StepPin_R,OUTPUT); // Step
  
  pinMode(DirPin_L,OUTPUT); // Dir
  pinMode(DirPin_R,OUTPUT); // Dir
  
  pinMode(11,OUTPUT); 
  pinMode(10,OUTPUT);  //HowStep
  pinMode(9,OUTPUT);  
  
  digitalWrite(EnablePin_L,LOW); // Set Enable low　→　Low状態でEnable
  digitalWrite(EnablePin_R,LOW); // Set Enable low　→　Low状態でEnable
  
  digitalWrite(11,HIGH);
  digitalWrite(10,LOW); //FULLSTEP
  digitalWrite(9,LOW);
  
  node.initNode();
  node.subscribe(stepper);
  node.advertise(message);
}

void loop() {
  if(fg != 0){
  digitalWrite(StepPin_L,HIGH); // 5番ピンをHigh状態へ
  digitalWrite(StepPin_R,HIGH);
  delayMicroseconds(Interval); // ５００ｍｓ待って
  digitalWrite(StepPin_L,LOW); // 5番ピンをLow状態へ
  digitalWrite(StepPin_R,LOW);
  delayMicroseconds(Interval); // ５００ｍｓ待って
  }
  node.spinOnce();
  delay(1);
}

