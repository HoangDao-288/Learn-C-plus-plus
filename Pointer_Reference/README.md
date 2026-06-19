# Con Trỏ và Tham Chiếu (Pointer & Reference)

## 1. Memory Leak (Rò rỉ Bộ Nhớ)

**Định nghĩa:** Memory leak xảy ra khi bạn cấp phát bộ nhớ trên heap nhưng không giải phóng nó, dẫn tới bộ nhớ bị lãng phí.

**Nguyên nhân chính:**
- Cấp phát bộ nhớ với `new` nhưng quên dùng `delete`
- Exception xảy ra trước khi có cơ hội gọi `delete`
- Con trỏ bị ghi đè mà chưa giải phóng bộ nhớ cũ

**Ví dụ:**
```cpp
void leakyFunction() {
    int* ptr = new int(42);  // Cấp phát bộ nhớ
    // ... làm gì đó ...
    // Quên delete ptr -> Memory leak
}
```

**Cách khắc phục:**
- Luôn cặp `new` và `delete`
- Dùng smart pointers (`unique_ptr`, `shared_ptr`)
- Dùng RAII pattern

---

## 2. Dangling Pointer (Con Trỏ Treo)

**Định nghĩa:** Dangling pointer là con trỏ vẫn tham chiếu tới bộ nhớ đã được giải phóng.

**Các trường hợp gây ra:**
- Giải phóng bộ nhớ nhưng không set pointer thành `nullptr`
- Trả về con trỏ tới biến local từ hàm

**Ví dụ 1 - Giải phóng bộ nhớ:**
```cpp
int* ptr = new int(42);
delete ptr;
// ptr bây giờ là dangling pointer
*ptr = 100;  // Undefined Behavior!
```

**Ví dụ 2 - Biến local:**
```cpp
int* func() {
    int x = 42;
    return &x;  // Dangling pointer! x sẽ bị destroy khi hàm kết thúc
}
```

**Cách tránh:**
- Set pointer thành `nullptr` sau khi delete
- Không trả về con trỏ tới biến local
- Dùng smart pointers

---

## 3. Pass by Reference vs Pass by Pointer

**Pass by Reference:**
```cpp
void modifyByRef(int& ref) {
    ref = 100;  // Thay đổi giá trị gốc
}

int main() {
    int x = 42;
    modifyByRef(x);  // Truyền biến trực tiếp, không cần &
    cout << x;  // Output: 100
}
```

**Pass by Pointer:**
```cpp
void modifyByPtr(int* ptr) {
    *ptr = 100;  // Thay đổi giá trị gốc
}

int main() {
    int x = 42;
    modifyByPtr(&x);  // Truyền địa chỉ
    cout << x;  // Output: 100
}
```

**Sự khác nhau:**
| Tiêu chí | Reference | Pointer |
|----------|-----------|---------|
| Null check | Không cần | Cần kiểm tra `nullptr` |
| Gán lại | Không thể | Có thể |
| Dùng | Hàm cần sửa đổi tham số | Cấp phát động, optional |

---

## 4. nullptr

**Định nghĩa:** `nullptr` là một hằng số đại diện cho "con trỏ không trỏ tới đâu".

**Tại sao dùng `nullptr` thay vì `NULL`?**
- `NULL` là macro (`#define NULL 0`)
- `nullptr` là keyword được type-check bởi compiler
- `nullptr` rõ ràng hơn và an toàn hơn

**Ví dụ:**
```cpp
int* ptr = nullptr;  // Pointer không trỏ tới gì

if (ptr != nullptr) {
    *ptr = 42;  // An toàn kiểm tra trước
}

delete ptr;  // An toàn gọi delete trên nullptr (không làm gì)
```

---

## 5. const với Pointer

**5.1 Pointer to const (Con trỏ tới hằng):**
```cpp
const int* ptr = &x;
*ptr = 100;  // KHÔNG được - không thể sửa giá trị
ptr = &y;    // OK - có thể thay đổi địa chỉ
```

**5.2 const pointer (Hằng con trỏ):**
```cpp
int* const ptr = &x;
*ptr = 100;  // OK - có thể sửa giá trị
ptr = &y;    // KHÔNG được - không thể thay đổi địa chỉ
```

**5.3 const pointer to const:**
```cpp
const int* const ptr = &x;
*ptr = 100;  // KHÔNG được - không thể sửa giá trị
ptr = &y;    // KHÔNG được - không thể thay đổi địa chỉ
```

**Quy tắc nhớ:** Đọc từ phải sang trái
- `int* const` → const pointer to int
- `const int*` → pointer to const int

---

## 6. Double Pointer (Con Trỏ Đôi)

**Định nghĩa:** Con trỏ tới một con trỏ (pointer to pointer).

**Khai báo:**
```cpp
int x = 42;
int* ptr = &x;          // Con trỏ tới int
int** doublePtr = &ptr; // Con trỏ tới con trỏ
```

**Cách sử dụng:**
```cpp
cout << x;           // 42
cout << *ptr;        // 42
cout << **doublePtr; // 42

**doublePtr = 100;   // Sửa giá trị x thành 100
```

**Trường hợp dùng:**
- Cấp phát mảng 2D động
- Truyền con trỏ vào hàm để hàm có thể thay đổi địa chỉ

---

## 7. Pointer với Array

**7.1 Pointer tới array:**
```cpp
int arr[5] = {1, 2, 3, 4, 5};
int* ptr = arr;  // ptr trỏ tới phần tử đầu

cout << *ptr;      // 1
cout << *(ptr + 1); // 2
cout << ptr[2];    // 3 (tương đương *(ptr + 2))
```

**7.2 Cấp phát mảng động:**
```cpp
int n = 5;
int* arr = new int[n];  // Cấp phát mảng 5 phần tử

arr[0] = 10;
delete[] arr;  // Lưu ý: dùng delete[], không phải delete
```

**7.3 Mảng con trỏ:**
```cpp
int* ptrArray[3];  // Mảng 3 con trỏ tới int

int x = 1, y = 2, z = 3;
ptrArray[0] = &x;
ptrArray[1] = &y;
ptrArray[2] = &z;

cout << *ptrArray[0];  // 1
```

**Lưu ý quan trọng:**
- `new int` cấp phát 1 phần tử
- `new int[n]` cấp phát n phần tử
- Phải dùng `delete[]` để giải phóng mảng, không phải `delete`