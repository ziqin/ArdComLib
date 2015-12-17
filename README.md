```c
for (int i = 0; i < 18; ++i)
{
    puts("Happy Birthday!");
}
```

# ArdComLib - 用于 Arduino 的通信封装 

ArdComLib， _Arduino Communication Library_ ，是一个用于与 [Arduino](https://www.arduino.cc/) 进行通信的、在 Arduino 端使用的类库。它基于串行端口通信，定义了 Arduino 通过串口接收请求和发送响应的[统一形式](https://github.com/ziqin/ArdComLib/wiki/%E9%80%9A%E4%BF%A1%E5%8D%8F%E8%AE%AE)，从而简化对 Arduino 的编程工作。

请查阅 [Wiki](https://github.com/ziqin/ArdComLib/wiki) 获取更多信息。

## 已测试平台

硬件：

- [x] Arduino Uno

软件：

- [x] Arduino IDE 1.6.0
- [x] Arduino IDE 1.0.6
- [x] ArduinoJson 5.0.7

## 许可协议

[The MIT License](LICENSE)