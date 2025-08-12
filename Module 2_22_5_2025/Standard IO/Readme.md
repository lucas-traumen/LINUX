# THỰC THI FILE BẰNG " Makefile"
Executing in terminate by cmd:  `make all`\
Deleting .exe file : `make clean`\
Deleting .log file : `make clean_applog`
# MÔ TẢ BÀI TOÁN 
## FLOWCHART
## PHÂN TÍCH CODE VÀ ĐÁNH GIÁ
### Đề bài yêu cầu
*Trong các ứng dụng thực tế, việc chỉ dùng printf để gỡ lỗi và ghi lại thông tin là không đủ. Một hệ thống logger chuyên nghiệp cần có khả năng:
- Ghi log ra nhiều nơi khác nhau (console, file).
- Lọc các thông điệp log dựa trên mức độ nghiêm trọng (ví dụ: chỉ hiển thị lỗi, bỏ qua thông tin gỡ lỗi).
- Tự động thêm các thông tin hữu ích như timestamp, tên file, và số dòng vào mỗi thông điệp log.*

### Hướng giải quyết
**Logger đa đầu ra (Multi-target Logger)**
- Logger phải có khả năng ghi log đồng thời ra màn hình console (stderr cho các lỗi nghiêm trọng và stdout cho các log thông thường) và một file văn bản.
- Việc ghi vào file là tùy chọn và được cấu hình khi khởi tạo.

**Lọc theo cấp độ (Level Filtering)**
- Logger phải có thể được cấu hình với một mức log tối thiểu (ví dụ: LOG_INFO).
- Bất kỳ thông điệp nào có mức độ ưu tiên thấp hơn (giá trị số lớn hơn) mức đã cấu hình sẽ bị bỏ qua và không được ghi lại.
- Cần có một hàm để thay đổi mức lọc này tại thời điểm chạy.

**Tự động thêm Metadata**
- Logger phải tự động lấy và chèn timestamp, tên file nguồn, và số dòng vào đầu mỗi thông điệp log.
- Gợi ý: Sử dụng các macro có sẵn của trình biên dịch là __FILE__ và __LINE__.

**Giao diện tiện lợi (Convenience Interface)**
- Tạo một macro log_message(...) để người dùng có thể gọi một cách thuận tiện mà không cần phải tự điền __FILE__ và __LINE__.
### Phân tích và kiểm tra thưc tế 💂‍♂️
Đầu tiên ta đến tới phần file main.c trước. Khi bắt đầu ta phải khởi tạo một file 'app_logr' bằng 1 hàm `logger_init`\
Trước hết ta hãy để ý 1 số thứ quan trọng sau:
```
typedef enum {
    LOG_EMERGENCY = 0,
    LOG_ALERT,
    LOG_CRITICAL,
    LOG_ERROR,
    LOG_WARNING,
    LOG_NOTICE,
    LOG_INFO,
    LOG_DEBUG
} LogLevel;
--------------------------------------------------------------------------------------------------------------------------------------------------------------------
static FILE *log_file = NULL;
static LogLevel current_level = LOG_INFO;
```
Như vậy trong hàm nãy sẻ tạo ra 1 file và set mode: "a" (write-only). Nếu không tạo được file thì nó sẽ gán giá trị **NULL** và return về **ERROR_INITIALATION**\
Tiếp theo tới phần log_message
```
#define log_message(level, fmt, ...) \
    logger_log(level, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
```
Bằng cách sử dụng macro để định nghĩa variadic function thành hàm logger_level. Trong đó:
```
__FILE__	Tên file nguồn hiện tại (string literal)
__LINE__	Số dòng hiện tại (int)
fmt             là chuỗi định dạng ("Error code %d").
__VA_ARGS__     là các đối số thay thế (ví dụ 404).
##__VA_ARGS__   là kỹ thuật “ăn” dấu phẩy nếu không có đối số nào.
```
Để tổng quan hơn ta thử phân tích dòng mã này 
`log_message(LOG_ERROR, "Something went wrong: %d", error_code);`\
Lúc này nó sẽ thành: `logger_log(LOG_ERROR, "main.c", 42, "Something went wrong: %d", error_code);`
Khi đi vào trong hàm, đầu tiên ta sẽ thấy  `if (level > current_level) return;`
đoạn mã này có yế nghĩa nếu mức độ log được thêm vào thấp hơn mức độ hiện tại thì sẽ thoát khỏi hàm, ngược lại. Ví dụ:
```
current_level = LOG_WARNING;
logger_log(LOG_DEBUG, ...) → bị bỏ
logger_log(LOG_ERROR, ...) → được ghi
```
`char timestamp[20];`
Khai báo mảng ký tự để chứa chuỗi thời gian, ví dụ "2025-07-08 14:23:01".


`get_timestamp(timestamp, sizeof(timestamp));`
Gọi hàm để lấy thời gian hiện tại theo định dạng YYYY-MM-DD HH:MM:SS, lưu vào timestamp.


`char message[1024];`
Vùng nhớ để chứa nội dung log được định dạng, như "Failed to connect to server port 3306".


`va_list args;`
Chuẩn bị để xử lý danh sách tham số biến thiên (...).


`va_start(args, fmt);`
Khởi động danh sách biến thiên, bắt đầu từ tham số fmt.


`vsnprintf(message, sizeof(message), fmt, args);`
Định dạng chuỗi log như printf, nhưng lưu vào message[] và giới hạn kích thước.

Ví dụ:\
`fmt = "User %s logged in", args = "alice"`\
`→ message = "User alice logged in"`




