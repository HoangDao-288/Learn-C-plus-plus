#include <iostream>

class Car {
    int speed;  // 4 bytes
    int gear;   // 4 bytes
public:
    void setSpeed(const int &speed) {
        this->speed = speed; // this trỏ tới object đang gọi hàm
    }

    Car* getPtr()  { return this;  }  // trả về địa chỉ
    Car  getCopy() { return *this; }  // trả về bản sao object

    // Method chaining nhờ *this
    Car& setSpeedUseThis(int s) { speed = s; return *this; }
    Car& setGear(int g)  { gear  = g; return *this; }

    void show() {
        std::cout << "Address of object use 'this' pointer: " << this << std::endl;     // 0x2000 - same! this = &sedan
    }
};

int main() {

Car sedan;  // sedan chiem 8 bytes (4 bytes speed + 4 bytes gear) tren stack - RAM
sedan.setSpeed(100);
// Compiler thực chất dịch thành: Car::setSpeed(&sedan, 100)
//                                              ↑ đây chính là this

sedan.setSpeedUseThis(120).setGear(5); // Method chaining nhờ *this

std::cout << "Address of sedan: " << &sedan << std::endl;
sedan.show();  // Same! this = &sedan

    return 0;
}