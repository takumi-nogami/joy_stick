#include <ros.h>

#include <std_msgs/Int32.h>
#include <VarSpeedServo.h>

VarSpeedServo myservo_dodai;
VarSpeedServo myservo_joint;

ros::NodeHandle node;

void hand_Callback(const std_msgs::Int32 &hand_msg){
  if(hand_msg.data == 0){ 
    myservo_joint.write(155, 256, true); // OPEN
    delay(1500);
    node.spinOnce();
  }else if(hand_msg.data == 1){
    myservo_joint.write(89, 64, true);  //CLOSE
    delay(1500);
    node.spinOnce();
  }else if(hand_msg.data == 2){
    myservo_dodai.write(165, 64, true); // RAISE
    delay(1500);
    node.spinOnce();
  }else if(hand_msg.data == 3){
    myservo_dodai.write(15, 256, true);  // DOWN
    delay(1500);
    node.spinOnce();
  }
}

ros::Subscriber<std_msgs::Int32>hand("cmd_hand", &hand_Callback);

void setup() { 
  myservo_dodai.attach(10);
  myservo_joint.attach(5);
  node.initNode();
  node.subscribe(hand);
}

void loop() {
  node.spinOnce();
  delay(1);
}
