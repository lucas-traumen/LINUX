# Thực thi file bằng " Makefile"
Executing in terminate by cmd:  `make all`\
Deleting .exe file : `make clean`
# Decrypting Project
## FLOWCHART


## Code Inspection
### Code Structure
**Đầu tiên bao gồm các hàm trong thực thi trong file led_driver.h**
 |Hàm | Mô tả |
| :--- | :--- |
| int led_init(size_t num_pixels); | Cấp phát bộ nhớ buffer cho dải LED|
| void led_shutdown(); | Giải phóng bộ nhớ |
| void led_set_pixel_color(size_t index, uint8_t r, uint8_t g, uint8_t b);	| Gán màu cho pixel tại vị trí index |
| void led_fill(uint8_t r, uint8_t g, uint8_t b);	| Gán cùng một màu cho tất cả pixel |
| void led_clear();	| Tắt tất cả các LED |
| const uint32_t* led_get_buffer();	| Trả về con trỏ buffer dữ liệu (dạng read-only) |
| size_t led_get_pixel_count();	| Lấy số lượng pixel đã cấp phát |

**Phân tích cụ thể nào** 🚀 \
*Khởi tạo led " ở đây tôi khởi tạo 5 leds "*\
  Lúc này tại hàm `led_init(size_t num_pixels)` được gọi và gán với 1 argument có giá trị =5
  ```
    led_buffer = (uint32_t*)malloc(sizeof(uint32_t) * 5 );
    if (!led_buffer) return ERROR_MEMORY_ALLOC ;
    pixel_count = 5;
    led_clear(); // Set all LEDs to black initially
    return 0;
```

  
*Trường hợp 1:*
```
led_set_pixel_color(0, 255, 0, 0);     // Red
led_set_pixel_color(1, 0, 255, 0);     // Green
led_set_pixel_color(2, 0, 0, 255);     // Blue
led_set_pixel_color(3, 255, 255, 0);   // Yellow
led_set_pixel_color(4, 255, 255, 255); // White
```
Ta xét 1 trường hợp đầu là Red 🦫( maybe i'm lazy)\
 Các argument lần lượt `0, 255, 0, 0` được truyền vào `size_t index, uint8_t r, uint8_t g, uint8_t b`\
 Tài dòng lệnh này `if (!led_buffer || index >= pixel_count) return;` Do ta được cấp phát "buffer" và vị trí leds nằm ở phạm vi số led được khai báo\
 ⚠️ **Cảnh báo** G-R-B format packed into 24 bits, top 8 bits are zero *nó bị ngược với đối số và tham số ở hàm trên*\
 `led_buffer[index] = ((uint32_t)g << 16) | ((uint32_t)r << 8) | b;` Lúc này ta nhận được led_buffer[0]=((0x00<<16)|(0xFF<<8)|0x00)\
 🫳 0000 0000 0000 0000 1111 1111 0000 0000 \
*Sau đó in ra thôi* 😄
 Ta dùng hàm `print_led_buffer()`\
  Trong hàm này:\
   Ta phân tích xíu về tên hàm : \
   | led_get_buffer | ta cấp phát động bộ đệm cho số lượng led được đưa vào. Ví dụ có 5 leds thì tạo bộ đệm chứa 5 cái |\
   | led_get_pixel_count | đếm số lượng led đã được cấp hay nói mỗi led là 1 pixel |\
   `buffer[i] & 0xFFFFFF`\
   Bit 31     ...     24 | 23 ... 16 | 15 ... 8 | 7 ... 0\
     [Không dùng]     |   Green   |   Red    |  Blue\
  ->Lúc này màn hình sẽ xuất `Pixel 0: 0x00FF00` *Vậy là led ở vị trí đầu trở thành màu đỏ*\
*Trường hợp 2:*
`led_fill(128, 0, 128)`\
Cấu trúc khá giống `led_set_pixel_color` nó sẽ set toàn bộ thay vì từng pixel(led)\
Và kết quả là:
```
Pixel 0: 0x008080
Pixel 1: 0x008080
Pixel 2: 0x008080
Pixel 3: 0x008080
Pixel 4: 0x008080
```
*Trường hợp 3:*
```
    led_clear(); // Turn off all
    print_led_buffer();

    led_shutdown();
 ```

