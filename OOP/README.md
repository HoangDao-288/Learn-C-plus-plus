# Lập Trình Hướng Đối Tượng (Object-Oriented Programming)

## 1. This Pointer (Con Trỏ This)

**Định nghĩa:** `this` là một con trỏ ẩn được compiler tự động truyền vào mọi non-static member function, trỏ tới object đang gọi hàm đó.

**Cách hoạt động:**
```cpp
class Student {
public:
    string name;
    
    void setName(string name) {
        this->name = name;  // this->name là member, name là tham số
    }
    
    void printInfo() {
        cout << "Tên: " << this->name << endl;
    }
};

int main() {
    Student s1;
    s1.setName("Hoanh");  // this trỏ tới s1
    
    Student s2;
    s2.setName("Duc");    // this trỏ tới s2
}
```

### 1.1 Static Member Function

**Định nghĩa:** Static member function không có `this` pointer, không thể truy cập member variables (trừ khi chúng cũng static).

```cpp
class Counter {
private:
    static int count;
    int id;
    
public:
    Counter() { count++; }
    
    static void printCount() {
        cout << "Tổng object: " << count << endl;  // OK - static member
        // cout << id << endl;  // LỖI - không có this
    }
};

int Counter::count = 0;

int main() {
    Counter c1, c2, c3;
    Counter::printCount();  // Output: Tổng object: 3
}
```

### 1.2 Const Member Function

**Định nghĩa:** Const member function không thể sửa member variables của object.

```cpp
class Circle {
private:
    double radius;
    
public:
    Circle(double r) : radius(r) {}
    
    double getArea() const {  // const function
        return 3.14 * radius * radius;  // OK - chỉ đọc
        // radius = 5;  // LỖI - không thể sửa
    }
    
    void setRadius(double r) {  // non-const function
        radius = r;  // OK - có thể sửa
    }
};
```

### 1.3 Phân Biệt this và *this

**`this` vs `*this`:**
```cpp
class Point {
public:
    int x, y;
    
    Point(int x, int y) : x(x), y(y) {}
    
    void demo() {
        // this là con trỏ tới Point object
        cout << this->x << ", " << this->y << endl;  // 1, 2
        
        // *this là Point object chính nó
        Point copy = *this;  // Copy toàn bộ object
    }
    
    Point& returnThis() {
        return *this;  // Trả về reference tới object gốc
    }
};

int main() {
    Point p(1, 2);
    p.demo();
}
```

---

## 2. Virtual Function và Virtual Pure Function

**Định nghĩa:** Virtual function cho phép polymorphism - gọi đúng function dựa trên actual type, không phải declared type.

### 2.1 Virtual Function (Có triển khai)

```cpp
class Animal {
public:
    virtual void speak() {  // virtual function
        cout << "Animal sound" << endl;
    }
    
    virtual ~Animal() {}  // Virtual destructor
};

class Dog : public Animal {
public:
    void speak() override {  // override keyword (C++11)
        cout << "Woof! Woof!" << endl;
    }
};

class Cat : public Animal {
public:
    void speak() override {
        cout << "Meow! Meow!" << endl;
    }
};

int main() {
    Animal* animal1 = new Dog();
    Animal* animal2 = new Cat();
    
    animal1->speak();  // Output: Woof! Woof! (gọi Dog::speak)
    animal2->speak();  // Output: Meow! Meow! (gọi Cat::speak)
    
    delete animal1;
    delete animal2;
}
```

### 2.2 Pure Virtual Function (Abstract Function)

```cpp
class Shape {
public:
    virtual void draw() = 0;  // Pure virtual = 0
    virtual double area() = 0;
    
    virtual ~Shape() {}
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : radius(r) {}
    
    void draw() override {
        cout << "Vẽ hình tròn" << endl;
    }
    
    double area() override {
        return 3.14 * radius * radius;
    }
};

int main() {
    // Shape s;  // LỖI - không thể tạo object từ abstract class
    
    Circle c(5);
    c.draw();
    cout << "Diện tích: " << c.area() << endl;
}
```

---

## 3. Overloading vs Overriding

| Tiêu chí | Overloading | Overriding |
|----------|-----------|-----------|
| **Khái niệm** | Hàm cùng tên, tham số khác | Hàm cùng tên, tham số giống trong derived class |
| **Scope** | Cùng class | Parent class và derived class |
| **Signature** | Khác nhau | Giống nhau (C++11+) |
| **Return type** | Có thể khác | Phải giống (hoặc covariant) |
| **Từ khóa** | N/A | `virtual`, `override` |

**Ví dụ Overloading:**
```cpp
class Math {
public:
    int add(int a, int b) {
        return a + b;
    }
    
    double add(double a, double b) {  // Cùng tên, khác tham số
        return a + b;
    }
    
    int add(int a, int b, int c) {  // Cùng tên, số lượng tham số khác
        return a + b + c;
    }
};

int main() {
    Math m;
    cout << m.add(1, 2) << endl;        // Output: 3
    cout << m.add(1.5, 2.5) << endl;    // Output: 4
    cout << m.add(1, 2, 3) << endl;     // Output: 6
}
```

**Ví dụ Overriding:**
```cpp
class Vehicle {
public:
    virtual void start() {
        cout << "Vehicle is starting" << endl;
    }
};

class Car : public Vehicle {
public:
    void start() override {  // Override parent's function
        cout << "Car engine is starting" << endl;
    }
};

int main() {
    Vehicle* v = new Car();
    v->start();  // Output: Car engine is starting
}
```

---

## 4. Bốn Tính Chất Chính của OOP Thể Hiện trong Class

### 4.1 Encapsulation (Đóng Gói)

Ẩn dữ liệu bên trong, chỉ expose những gì cần thiết.

```cpp
class BankAccount {
private:
    double balance;  // Ẩn dữ liệu
    
public:
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }
    
    double getBalance() const {
        return balance;
    }
};
```

### 4.2 Inheritance (Kế Thừa)

Derived class kế thừa từ base class.

```cpp
class Person {
protected:
    string name;
    
public:
    Person(string n) : name(n) {}
};

class Student : public Person {  // Kế thừa
public:
    Student(string n) : Person(n) {}
};
```

### 4.3 Polymorphism (Đa Hình)

Cùng interface, nhiều cách triển khai.

```cpp
class Shape {
public:
    virtual void draw() = 0;  // Interface
};

class Circle : public Shape {
public:
    void draw() override { cout << "Draw Circle" << endl; }
};

class Square : public Shape {
public:
    void draw() override { cout << "Draw Square" << endl; }
};

int main() {
    vector<Shape*> shapes;
    shapes.push_back(new Circle());
    shapes.push_back(new Square());
    
    for (auto shape : shapes) {
        shape->draw();  // Polymorphism - gọi đúng triển khai
    }
}
```

### 4.4 Abstraction (Trừu Tượng)

Ẩn chi tiết phức tạp, chỉ show interface đơn giản.

```cpp
class DatabaseConnection {
public:
    virtual void connect() = 0;
    virtual void query(string sql) = 0;
    virtual void disconnect() = 0;
};

class MySQLConnection : public DatabaseConnection {
public:
    void connect() override { cout << "Connecting to MySQL" << endl; }
    void query(string sql) override { cout << "Executing: " << sql << endl; }
    void disconnect() override { cout << "MySQL disconnected" << endl; }
};
```