# Cấp Phát Bộ Nhớ (Memory Allocation)

## 1. Khu Vực Bộ Nhớ của Con Trỏ

### Câu hỏi: Khi con trỏ được khởi tạo, nó cũng sẽ được cấp phát 1 ô nhớ. Vậy ô nhớ này thuộc vùng nhớ nào - Heap, Stack hay Global?

**Trả lời:** Phụ thuộc vào nơi khai báo con trỏ:

**a) Con trỏ được khai báo cục bộ (Local Pointer):**
```cpp
void func() {
    int* ptr = new int(42);  // Con trỏ 'ptr' nằm trên STACK
                             // Dữ liệu 42 nằm trên HEAP
}
```
- Con trỏ `ptr` (biến chứa địa chỉ) → **STACK**
- Dữ liệu mà nó trỏ tới → **HEAP**

**b) Con trỏ là global:**
```cpp
int* globalPtr;  // Khai báo toàn cục → GLOBAL/DATA SEGMENT

int main() {
    globalPtr = new int(42);  // globalPtr nằm trên vùng GLOBAL
                              // Dữ liệu 42 nằm trên HEAP
}
```

**c) Con trỏ là member của class:**
```cpp
class MyClass {
public:
    int* memberPtr;  // Vị trí phụ thuộc vào object được tạo ở đâu
};

int main() {
    MyClass obj;      // obj trên STACK → memberPtr cũng trên STACK
    MyClass* objPtr = new MyClass();  // objPtr trên HEAP → memberPtr cũng trên HEAP
}
```

**Bản đồ bộ nhớ:**
```
┌─────────────────────────────────┐
│         CODE SEGMENT            │  Chứa machine code
├─────────────────────────────────┤
│    GLOBAL/DATA SEGMENT          │  Biến global, static
├─────────────────────────────────┤
│          HEAP                   │  Cấp phát động (new)
│          ↓                      │  Tăng từ dưới lên
├─────────────────────────────────┤
│                                 │
│          ↑                      │
│        STACK                    │  Biến local, con trỏ local
│                                 │  Tăng từ trên xuống
├─────────────────────────────────┤
```

---

## 2. Địa Chỉ Bộ Nhớ và Byte

**Khái niệm:**
- Mỗi ô nhớ có 1 địa chỉ riêng
- Mỗi ô nhớ chỉ chứa đúng 1 byte (8 bit)
- Địa chỉ là một số không âm để định vị ô nhớ

**Ví dụ minh họa:**
```
Địa chỉ:  1000      1001      1002      1003
        ┌─────────┬─────────┬─────────┬─────────┐
        │ 01001000│ 10010110│ 00011001│ 00010010│  <- Từng byte
        └─────────┴─────────┴─────────┴─────────┘
        ◄─────────────── Một biến int ──────────────►
              (giả sử hệ thống little-endian)
```

---

## 3. Cấu Trúc Bộ Nhớ của Biến Int (4 Bytes)

**Ví dụ: `int x = 305419896;`**

```
Địa chỉ:  1000      1001      1002      1003
        ┌─────────┬─────────┬─────────┬─────────┐
        │ byte 0  │ byte 1  │ byte 2  │ byte 3  │
        └─────────┴─────────┴─────────┴─────────┘
        ◄──────────── int x = 305419896 ──────────────►

Giá trị hex: 0x12345678
```

**Cách lấy địa chỉ từng byte:**
```cpp
int x = 305419896;  // 0x12345678

int* xPtr = &x;     // Địa chỉ byte đầu tiên (1000)

// Lấy địa chỉ các byte khác
unsigned char* bytePtr = (unsigned char*)&x;

cout << "Địa chỉ byte 0: " << (void*)(bytePtr + 0) << endl;  // 1000
cout << "Địa chỉ byte 1: " << (void*)(bytePtr + 1) << endl;  // 1001
cout << "Địa chỉ byte 2: " << (void*)(bytePtr + 2) << endl;  // 1002
cout << "Địa chỉ byte 3: " << (void*)(bytePtr + 3) << endl;  // 1003

// Giá trị từng byte (little-endian)
cout << "Byte 0: " << (int)bytePtr[0] << endl;  // 0x78 = 120
cout << "Byte 1: " << (int)bytePtr[1] << endl;  // 0x56 = 86
cout << "Byte 2: " << (int)bytePtr[2] << endl;  // 0x34 = 52
cout << "Byte 3: " << (int)bytePtr[3] << endl;  // 0x12 = 18
```

---

## 4. Cấp Phát Bộ Nhớ Động (Dynamic Memory Allocation)

### 4.1 Các Phương Pháp Cấp Phát

**a) Cấp phát với `new`:**
```cpp
// Cấp phát 1 biến
int* ptr = new int(42);
delete ptr;
ptr = nullptr;  // Good practice

// Cấp phát mảng
int* arr = new int[10];
delete[] arr;  // Lưu ý: [] để xóa mảng
arr = nullptr;

// Cấp phát struct
struct Point { int x, y; };
Point* p = new Point{1, 2};
delete p;
p = nullptr;
```

**b) So sánh `new` vs Stack allocation:**
```cpp
// Stack allocation - tự động giải phóng
{
    int x = 42;  // Stack
    int arr[10];  // Stack
}  // Tự động hủy

// Heap allocation - phải tự giải phóng
{
    int* x = new int(42);  // Heap
    int* arr = new int[10];  // Heap
    // Phải delete, không thì memory leak!
}
```

### 4.2 Lifetime của Biến

**Stack Variable:**
```cpp
void demo() {
    int x = 42;  // Tạo
    cout << x;   // Sử dụng
}  // Hủy tự động

// x không còn tồn tại sau khi hàm kết thúc
```

**Heap Variable:**
```cpp
void demo() {
    int* ptr = new int(42);  // Tạo (con trỏ trên stack, dữ liệu trên heap)
    cout << *ptr;            // Sử dụng
    delete ptr;              // Phải tự hủy
    ptr = nullptr;           // Tốt nhất set nullptr
}

// Dữ liệu được giải phóng khi gọi delete
```

### 4.3 Smart Pointers (C++11+)

**Giải pháp tự động quản lý bộ nhớ:**

```cpp
#include <memory>

// unique_ptr - chỉ một owner
{
    std::unique_ptr<int> ptr(new int(42));
    cout << *ptr;  // 42
}  // Tự động delete

// shared_ptr - nhiều owners
{
    std::shared_ptr<int> ptr1(new int(42));
    std::shared_ptr<int> ptr2 = ptr1;  // Chia sẻ
    
    cout << ptr1.use_count();  // 2
}  // Khi cả ptr1 và ptr2 hủy, dữ liệu được delete
```

---

## 5. Memory Layout Tổng Quát

**Ví dụ đầy đủ:**
```cpp
int globalVar = 100;        // GLOBAL SEGMENT

int* globalPtr;             // GLOBAL SEGMENT

int main() {
    static int staticVar = 50;      // Khởi tạo trong GLOBAL, còn lại STACK
    
    int localVar = 42;              // STACK
    
    int* localPtr = new int(99);    // Con trỏ trên STACK
                                    // Dữ liệu trên HEAP
    
    int arr[10];                    // STACK
    
    int* dynArr = new int[10];      // Con trỏ trên STACK
                                    // Mảng trên HEAP
    
    // Layout:
    // HEAP:   [99], [HEAP_ARRAY]
    // STACK:  localVar, localPtr, arr, dynArr
    // GLOBAL: globalVar, globalPtr, staticVar
    
    delete localPtr;
    delete[] dynArr;
}
```

---

## Bảng Tóm Tắt

| Loại | Vị Trí | Thời Gian Sống | Giải Phóng | Kích Thước |
|------|--------|---|---|---|
| **Stack** | Stack | Khi block kết thúc | Tự động | Giới hạn |
| **Heap** | Heap | Đến khi delete | Thủ công | Lớn |
| **Global** | Global Segment | Toàn chương trình | Tự động khi exit | Cố định |
| **Static** | Global Segment | Toàn chương trình | Tự động khi exit | Cố định |