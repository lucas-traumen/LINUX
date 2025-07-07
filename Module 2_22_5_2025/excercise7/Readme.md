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

**Phân tích cụ thể nào** 🚀 
`int led_init(size_t num_pixels)`
