#include<Servo.h>

//定义pitch轴舵机和yaw轴舵机
Servo pitch_ser;
Servo yaw_ser;


//初始化及自检过程
void setup()
{
  pitch_ser.attach(5);
  yaw_ser.attach(6);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  Serial.begin(9600);

  //伺服电机自检过程

  int pitch_angle;
  int yaw_angle;

  //pitch轴伺服电机自检
  for (pitch_angle = 90; pitch_angle < 180; pitch_angle++)
  {
    pitch_ser.write(pitch_angle);
    delay(5);
  }
  delay(100);
  for (pitch_angle = 179; pitch_angle > 0; pitch_angle--)
  {
    pitch_ser.write(pitch_angle);
    delay(5);
  }
  delay(100);
  for (pitch_angle = 1; pitch_angle < 91; pitch_angle++)
  {
    pitch_ser.write(pitch_angle);
    delay(5);
  }
  delay(100);

  //yaw轴伺服电机自检
  for (yaw_angle = 90; yaw_angle < 180; yaw_angle++)
  {
    yaw_ser.write(yaw_angle);
    delay(5);
  }
  delay(100);
  for (yaw_angle = 179; yaw_angle > 0; yaw_angle--)
  {
    yaw_ser.write(yaw_angle);
    delay(5);
  }
  delay(100);
  for (yaw_angle = 1; yaw_angle < 91; yaw_angle++)
  {
    yaw_ser.write(yaw_angle);
    delay(5);
  }
  delay(100);


  //双轴联动自检


  //正向转动自检
  for (pitch_angle = 90, yaw_angle = 90; pitch_angle < 180 && yaw_angle < 180; pitch_angle++, yaw_angle ++)
  {
    pitch_ser.write(pitch_angle);
    yaw_ser.write(yaw_angle);
    delay(5);
  }

  //逆向转动自检
  for (pitch_angle = 179, yaw_angle = 179; pitch_angle > 0  && yaw_angle > 0; pitch_angle--, yaw_angle --)
  {
    pitch_ser.write(pitch_angle);
    yaw_ser.write(yaw_angle);
    delay(5);
  }
  for (pitch_angle = 1, yaw_angle = 1; pitch_angle < 91  && yaw_angle < 91; pitch_angle++, yaw_angle ++)
  {
    pitch_ser.write(pitch_angle);
    yaw_ser.write(yaw_angle);
    delay(5);
  }


  //伺服电机角度归位
  pitch_ser.write(90);
  yaw_ser.write(90);




}

int sensor_pitch_a, sensor_pitch_b;
int sensor_yaw_a, sensor_yaw_b;

int pitch_angle = 90;
int yaw_angle = 90;

  //校准pitch轴和yaw轴光敏传感器的初始差值
  const static int pitch_set = 0;
  const static int yaw_set = 0;

  //舵机转动角度控制向量
  int pitch_motor_victor;
  int yaw_motor_victor;
  int step = 2;

//程序标准执行过程
void loop()
{



  //伺服电机角度归位
  pitch_ser.write(pitch_angle);
  yaw_ser.write(yaw_angle);

  sensor_pitch_a = analogRead(A0);
  sensor_pitch_b = analogRead(A1);
  sensor_yaw_a = analogRead(A2);
  sensor_yaw_b = analogRead(A3);


  //数据滤波及标准化

  //均值滤波
  int i, j, k;
  for (i = 0; i < 10; i++)
  {
    sensor_pitch_a  += analogRead(A0);
    sensor_pitch_b  += analogRead(A1);
    sensor_yaw_a    += analogRead(A2);
    sensor_yaw_b    += analogRead(A3);
    delay(5);
  }
  sensor_pitch_a  /= 10;
  sensor_pitch_b  /= 10;
  sensor_yaw_a    /= 10;
  sensor_yaw_b    /= 10;

  const static int threshold = 0;
  const static int step = 1;
  const static int speed = 2;

  if(sensor_pitch_a - sensor_pitch_b > threshold)
  {
    if(sensor_yaw_a - sensor_yaw_b > threshold)
    {
      pitch_ser.write(++pitch_angle);
      yaw_ser.write(--yaw_angle);
    }
    else if(sensor_yaw_a - sensor_yaw_b < 0 - threshold)
    {
      pitch_ser.write(++pitch_angle);
      yaw_ser.write(++yaw_angle);
    }
    else
    {
      pitch_ser.write(++pitch_angle);
    }

  }
  else if(sensor_pitch_a - sensor_pitch_b < 0 - threshold)
  {
    if(sensor_yaw_a - sensor_yaw_b > threshold)
    {
      pitch_ser.write(--pitch_angle);
      yaw_ser.write(++yaw_angle);
    }
    else if(sensor_yaw_a - sensor_yaw_b < 0 - threshold)
    {
      pitch_ser.write(--pitch_angle);
      yaw_ser.write(--yaw_angle);
    }
    else
    {
      pitch_ser.write(--pitch_angle);
    }
  }
  else
  {
    if(sensor_yaw_a - sensor_yaw_b > threshold)
    {
      yaw_ser.write(++yaw_angle);
    }
    else if(sensor_yaw_a - sensor_yaw_b < 0 - threshold)
    {
      yaw_ser.write(--yaw_angle);
    }
  }
  
  Serial.print("sensor_pitch_a:");
  Serial.println(sensor_pitch_a);
  Serial.print("sensor_pitch_b:");
  Serial.println(sensor_pitch_b);
  Serial.print("sensor_yaw_a:");
  Serial.println(sensor_yaw_a);
  Serial.print("sensor_yaw_b:");
  Serial.println(sensor_yaw_b);
  Serial.println("   ");
  Serial.println("  ");

}