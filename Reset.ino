#include<Servo.h>

Servo pitch_ser;
Servo yaw_ser;

void setup()
{
    pitch_ser.attach(5);
    yaw_ser.attach(6);
    pinMode(A0,INPUT);
    pinMode(A1,INPUT);
    pinMode(A2,INPUT);
    pinMode(A3,INPUT);
    Serial.begin(9600);

    //伺服电机自检过程

    int pitch_angle;
    int yaw_angle;

    //pitch轴伺服电机自检
    for(pitch_angle = 0;pitch_angle < 180; pitch_angle++)
    {
        pitch_ser.write(pitch_angle);
        delay(3);
    }
    pitch_ser.write(90);
    delay(100);

    //yaw轴伺服电机自检
    for(yaw_angle = 0;yaw_angle < 180; yaw_angle++)
    {
        yaw_ser.write(yaw_angle);
        delay(3);
    }
    yaw_ser.write(90);
    delay(100);


    //双轴联动自检
    pitch_angle = 0;
    yaw_angle = 0;
    pitch_ser.write(pitch_angle);
    yaw_ser.wiret(yaw_angle);
    delay(200);



    //正向转动自检
    for(pitch_angle = 0,yaw_angle = 0;pitch_angle < 180 && yaw_angle <180; pitch_angle++,yaw_angle ++)
    {
        pitch_ser.write(pitch_angle);
        yaw_ser.write(yaw_angle);
        delay(3);
    }

    //逆向转动自检
    for(pitch_angle = 180,yaw_angle = 180;pitch_angle > 0  && yaw_angle > 0; pitch_angle--,yaw_angle --)
    {
        pitch_ser.write(pitch_angle);
        yaw_ser.write(yaw_angle);
        delay(3);
    }

    //伺服电机角度归位
    pitch_ser.write(90);
    yaw_ser.write(90);




}

void loop()
{

    int sensor_pitch_a,sensor_pitch_b;
    int sensor_yaw_a,sensor_yaw_b;


    sensor_pitch_a = analogRead(A0);
    sensor_pitch_b = analogRead(A1);
    sensor_yaw_a = analogRead(A2);
    sensor_yaw_b = analogRead(A3);
    //数据滤波及标准化

    //均值滤波
    int i,j,k;
    for(i=0;i<19;i++)
    {
        sensor_pitch_a  += analogRead(A0);
        sensor_pitch_b  += analogRead(A1);
        sensor_yaw_a    += analogRead(A2);
        sensor_yaw_b    += analogRead(A3);
        delay(10);
    }
    sensor_pitch_a  /= 10;
    sensor_pitch_b  /= 10;
    sensor_yaw_a    /= 10;
    sensor_yaw_b    /= 10;

    //伺服电机角度归位
    pitch_ser.write(90);
    yaw_ser.write(90);

    //串口输出当前光敏电阻数值
    Serial.print("sensor_pitch_a:");
    Serial.println(sensor_pitch_a);
    Serial.print("sensor_pitch_b:")
    Serial.println(sensor_pitch_b);
    Serial.print("sensor_yaw_a:");
    Serial.println(sensor_yaw_a);
    Serial.print("sensor_yaw_b:");
    Serial.println(sensor_yaw_b);

}