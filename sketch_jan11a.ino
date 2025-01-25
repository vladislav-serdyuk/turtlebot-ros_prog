#include <DynamixelWorkbench.h>

#include <ros.h>
#include <std_msgs/Int8.h>

#if defined(__OPENCM904__)
#define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
#define DEVICE_NAME ""
#endif

#define BAUDRATE  1000000
#define DXL_ID_L    2
#define DXL_ID_R    1

DynamixelWorkbench dxl_wb;

ros::NodeHandle nh;

uint8_t dxl_id_L = DXL_ID_L;
uint8_t dxl_id_R = DXL_ID_R;

void set_speed_L( const std_msgs::Int8& msg){
  dxl_wb.goalVelocity(dxl_id_L, (int32_t)speedConvert(msg.data));
}
ros::Subscriber<std_msgs::Int8> speed_L("speed_L", &set_speed_L);

void set_speed_R( const std_msgs::Int8& msg){
  dxl_wb.goalVelocity(dxl_id_R, (int32_t)speedConvert(msg.data));
}
ros::Subscriber<std_msgs::Int8> speed_R("speed_R", &set_speed_R);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //  while (!Serial); // Wait for Opening Serial Monitor
  Serial.setTimeout(50);

  const char *log;
  bool result = false;

  uint16_t model_number = 0;

  result = dxl_wb.init(DEVICE_NAME, BAUDRATE, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to init");
  }
  else
  {
    Serial.print("Succeeded to init : ");
    Serial.println(BAUDRATE);
  }

  result = dxl_wb.ping(dxl_id_L, &model_number, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to ping");
  }
  else
  {
    Serial.println("Succeeded to ping");
    Serial.print("id : ");
    Serial.print(dxl_id_L);
    Serial.print(" model_number : ");
    Serial.println(model_number);
  }

  result = dxl_wb.ping(dxl_id_R, &model_number, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to ping");
  }
  else
  {
    Serial.println("Succeeded to ping");
    Serial.print("id : ");
    Serial.print(dxl_id_R);
    Serial.print(" model_number : ");
    Serial.println(model_number);
  }

  result = dxl_wb.wheelMode(dxl_id_L, 0, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to change wheel mode");
  } else {
    Serial.println("Succeed to change wheel mode");
  }

  result = dxl_wb.wheelMode(dxl_id_R, 0, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to change wheel mode");
  } else {
    Serial.println("Succeed to change wheel mode");
  }

  nh.initNode();
  nh.subscribe(speed_L);
  nh.subscribe(speed_R);
}

void loop() {
  // put your main code here, to run repeatedly:
  nh.spinOnce();
  delay(1);
}

int speedConvert(int speed_) {
  if (speed_ >= 0) {
    return speed_ * 1023 / 100;
  } else {
    return -speed_ * 1023 / 100 + 1024;
  }
}
