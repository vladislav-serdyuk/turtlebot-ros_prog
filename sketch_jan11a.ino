#include <RC100.h>
#include <DynamixelWorkbench.h>

#include <ros.h>
#include <std_msgs/Int8.h>
#include <std_msgs/String.h>

#if defined(__OPENCM904__)
#define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
#define DEVICE_NAME ""
#endif

#define BAUDRATE  1000000
#define DXL_ID_L    2
#define DXL_ID_R    1

DynamixelWorkbench dxl_wb;
RC100 Controller;
int RcvData = 0;

ros::NodeHandle nh;

uint8_t dxl_id_L = DXL_ID_L;
uint8_t dxl_id_R = DXL_ID_R;

void set_speed_L( const std_msgs::Int8& msg) {
  dxl_wb.goalVelocity(dxl_id_L, (int32_t)speedConvert(msg.data));
}
ros::Subscriber<std_msgs::Int8> speed_L("speed_L", &set_speed_L);

void set_speed_R( const std_msgs::Int8& msg) {
  dxl_wb.goalVelocity(dxl_id_R, (int32_t)speedConvert(msg.data));
}
ros::Subscriber<std_msgs::Int8> speed_R("speed_R", &set_speed_R);

std_msgs::String str_msg;
ros::Publisher rc100("rc100", &str_msg);

char* last_key = "0";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //  while (!Serial); // Wait for Opening Serial Monitor
  Serial.setTimeout(50);

  Controller.begin(1);

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
  nh.advertise(rc100);
}

void loop() {
  // put your main code here, to run repeatedly:
  nh.spinOnce();
  delay(1);

  // RC100
  if (Controller.available())
  {
    RcvData = Controller.readData();
    if (RcvData & RC100_BTN_U)
    {
      send_key("U");
    }
    else if (RcvData & RC100_BTN_D)
    {
      send_key("D");
    }
    else if (RcvData & RC100_BTN_L)
    {
      send_key("L");
    }
    else if (RcvData & RC100_BTN_R)
    {
      send_key("R");
    }
    else if (RcvData & RC100_BTN_1)
    {
      send_key("1");
    }
    else if (RcvData & RC100_BTN_2)
    {
      send_key("2");
    }
    else if (RcvData & RC100_BTN_3)
    {
      send_key("3");
    }
    else if (RcvData & RC100_BTN_4)
    {
      send_key("4");
    }
    else if (RcvData & RC100_BTN_5)
    {
      send_key("5");
    }
    else if (RcvData & RC100_BTN_6)
    {
      send_key("6");
    }
    else
    {
      send_key("0");
    }
  }
}

int speedConvert(int speed_) {
  if (speed_ >= 0) {
    return speed_ * 1023 / 100;
  } else {
    return -speed_ * 1023 / 100 + 1024;
  }
}

void send_key(char key[2]) {
  if (key != last_key) {
    str_msg.data = key;
    rc100.publish(&str_msg);
    last_key = key;
  }
}
