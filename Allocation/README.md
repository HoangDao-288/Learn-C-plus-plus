1. Khi con trỏ được khởi tạo, nó cũng sẽ được cấp phát 1 ô nhớ. Vậy thì ô nhớ này thuộc vùng nhớ nào? Heap, stack hay global?
2. Mỗi ô nhớ có 1 địa chỉ riêng và chỉ chứa giá trị là 1 byte (8 bit). 
3. Ví dụ về biến int 4 bytes -> Chiếm 4 ô nhớ; địa chỉ của biến là địa chỉ của byte đầu tiên:

    Địa chỉ:  1000      1001      1002      1003
           ┌─────────┬─────────┬─────────┬─────────┐
           │  byte 0  │  byte 1  │  byte 2  │  byte 3  │
           └─────────┴─────────┴─────────┴─────────┘
           ◄──────────── int x = 305419896 ──────────────►

4. 