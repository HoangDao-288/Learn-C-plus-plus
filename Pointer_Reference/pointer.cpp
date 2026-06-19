#include <iostream>

/* Pass by Reference */
float calculateArea_useRef(int &radius) {
    return 3.14f * radius * radius;
}

/* Pass by Pointer */
float calculateArea_usePtr(int *radius) {
    return 3.14f * (*radius) * (*radius);
}

int main() {

    /* Khai bao va cap phat dong pointer */
    int *ptr1 = new int(10);         /// Cap phat dong 1 so nguyen co gia tri la 10
    std::cout << "ptr1: " << *ptr1 << std::endl;
    std::cout << "Calculate Area (Use Reference): " << calculateArea_useRef(*ptr1) << std::endl;
    std::cout << "Calculate Area (Use Pointer): " << calculateArea_usePtr(ptr1) << std::endl;
    delete ptr1;                     /// Giai phong bo nho da cap phat dong

    /* Khai bao va cap phat tinh (stack) pointer */
    int a = 20;
    int *ptr2 = &a;                      /// Cap phat tinh 1 so nguyen co gia tri la 20
    std::cout << "ptr2 point to 'stack address': " << ptr2 << std::endl;
    std::cout << "ptr2 point to 'stack address have value': " << *ptr2 << std::endl;
    std::cout << "ptr2 have address: " << &ptr2 << std::endl;
    // delete ptr2;  /// Sai, khong giai phong bo nho da cap phat tinh

    int **ptr2_double = &ptr2;              /// ptr2_double tro den dia chi cua ptr2
    
    std::cout << "Double Pointer ptr2_double have value: " << ptr2_double << std::endl;
    std::cout << "Double Pointer ptr2_double point to 'value of stack address': " << **ptr2_double << std::endl;
    // delete ptr2_double;  /// Sai, khong giai phong bo nho da cap phat tinh

    /* Khai bao con tro null */
    int *ptr3 = nullptr;                /// Khai bao con tro null
    if (ptr3 == nullptr) {
        std::cout << "ptr3: " << "Con tro null" << std::endl;
    }

    /* -----Memory Leak-----
    int *ptr = new int(10);
    std::cout << *ptr << std::endl;
    */

    /* -----Dangling Pointer-----
    int *ptr = new int(10);
    std::cout << *ptr << std::endl;
    delete ptr;                    
    std::cout << *ptr << std::endl; /// Sai, truy cap vao con tro da bi giai phong
                                    /// Undefined Behavior
    if (ptr != nullptr) {
        std::cout << "Con tro khong null" << std::endl; /// Van chay vao day
    }   /// Dangling Pointer 
    
    */

    /* const with Pointer*/
    const int *ptr4 = new int(30);          /// *ptr4 la const
    int const *ptr5 = new int(40);          /// *ptr5 la const
    int* const ptr6 = new int(50);          /// ptr6 la const
    const int* const ptr7 = new int(60);    /// *ptr7 va ptr7 deu la const
    
    delete ptr4;
    delete ptr5;
    delete ptr6;
    delete ptr7;

    /* Double Pointer */

    /// Khai bao thong qua cap phat dong
    int **ptr8 = new int*(new int(80));
    std::cout << "Double Pointer ptr8 have address: " << &ptr8 << std::endl;
    std::cout << "Double Pointer ptr8 have value: " << *ptr8 << std::endl;
    std::cout << "Double Pointer ptr8 point to 'value of heap address': " << **ptr8 << std::endl;

    /// Khai bao thong qua con tro don
    int *ptr9 = new int(90);
    std::cout << "ptr9 have address: " << &ptr9 << std::endl;
    std::cout << "ptr9 have value: " << ptr9 << std::endl;
    std::cout << "ptr9 point to 'value of heap address': " << *ptr9 << std::endl;
    int **ptr10 = &ptr9;  /// ptr10 tro den dia chi cua ptr9
    std::cout << "Double Pointer ptr10 have value: " << ptr10 << std::endl;
    std::cout << "Double Pointer ptr10 point to 'value of heap address': " << **ptr10 << std::endl;

    // free the inner heap int allocated for ptr8, then free the int* allocated for ptr8
    delete *ptr8; // deletes the int(80)
    delete ptr8;  // deletes the int* allocated by new int*(...)
    delete ptr9;  // deletes the int(90)
    // ptr10 points to ptr9 (stack address) - do NOT delete ptr10

    /* Pointer with array */
    int arr[] = {1, 2, 3, 4, 5};
    int *ptr_arr = arr;  /// ptr_arr tro den dia chi cua phan tu dau tien cua mang

    std::cout << "Size of int: " << sizeof(int) << " bytes" << std::endl;
    std::cout << "Pointer point to value & address of arr[0]: " << *ptr_arr << ", " << ptr_arr << std::endl;
    std::cout << "Pointer point to value & address of arr[1]: " << *(ptr_arr + 1) << ", " << (ptr_arr + 1) << std::endl;
    std::cout << "Pointer point to value & address of arr[2]: " << *(ptr_arr + 2) << ", " << (ptr_arr + 2) << std::endl;

    return 0;
}


