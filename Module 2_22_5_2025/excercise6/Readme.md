# THỰC THI FILE BẰNG " Makefile"
Executing in terminate by cmd:  `make all`\
Deleting .exe file : `make clean`\
Deleting .log file : `make clean_applog`
# MÔ TẢ BÀI TOÁN 
## FLOWCHART
## PHÂN TÍCH CODE VÀ ĐÁNH GIÁ
### Đề bài yêu cầu
*Trong các ứng dụng thực tế, việc chỉ dùng printf để gỡ lỗi và ghi lại thông tin là không đủ. Một hệ thống logger chuyên nghiệp cần có khả năng:\
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
Trước hết ta hãy để ý 1 sô thứ quan trọng sau:
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

