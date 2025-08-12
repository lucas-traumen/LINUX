#  Cách build make file
`make all` để chạy file main.exe\
`make clean` để xóa file main.exe đã được thực thi của đoạn code trước
# Mô tả bài toán
## Định nghĩa các trạng thái hoạt động
Chế độ hệ thống:
-  MODE_AUTO: Hệ thống tự động quản lý việc tưới nước dựa trên cảm biến.
-  MODE_MANUAL: Hệ thống chờ lệnh thủ công hoặc bị khóa tự động.

Trạng thái tưới nước của bơm:
-  PUMP_OFF: Bơm không hoạt động.
-  PUMP_ON: Bơm đang hoạt động.

Trạng thái LED:
-  LED_NORMAL: Hệ thống hoạt động bình thường, không tưới.
-  LED_WATERING: Hệ thống đang tưới nước.
-  LED_LOW_MOISTURE_ALERT: Độ ẩm đất quá thấp (chưa tưới hoặc tưới không đủ).
-  LED_ERROR: Lỗi hệ thống (ví dụ: cảm biến hỏng, bơm kẹt).

**Ở đoạn code trong file enums.h**
```
typedef enum {
    MODE_AUTO,
    MODE_MANUAL
} SystemMode;

typedef enum {
    PUMP_OFF,
    PUMP_ON
} PumpState;

typedef enum {
    LED_NORMAL,
    LED_WATERING,
    LED_LOW_MOISTURE_ALERT,
    LED_ERROR
} LedStatus;
```
## Cấu trúc dữ liệu chính
Dữ liệu cảm biến: Cần có một cấu trúc để lưu trữ giá trị đọc được từ cảm biến độ ẩm đất và nhiệt độ môi trường.\
Cài đặt hệ thống: Cần một cấu trúc để lưu trữ các tham số cấu hình như:\
-  Ngưỡng độ ẩm tối thiểu để bắt đầu tưới.
-  Ngưỡng độ ẩm tối đa để dừng tưới.
-  Thời gian tưới tối đa cho mỗi lần.
-  Chu kỳ kiểm tra cảm biến (ví dụ ở đoạn code đây: mỗi 10 giây).
-  Trạng thái chế độ hiện tại (Tự động/Thủ công).
**Ở đoạn code trong file config.h**
```
#define MOISTURE_MIN_THRESHOLD 5  // %
#define MOISTURE_MAX_THRESHOLD 7  // %
#define WATERING_DURATION 2        // seconds
#define SENSOR_CHECK_INTERVAL 10   // seconds (10 seconds)
```
## Yêu cầu chức năng
### Khởi tạo hệ thống:
-  Thiết lập các chân GPIO cho cảm biến, bơm, LED, nút nhấn.
-  Đặt các giá trị mặc định ban đầu cho các cài đặt hệ thống (ngưỡng độ ẩm, thời gian tưới, v.v.).
-  Đưa hệ thống vào chế độ MODE_AUTO mặc định ban đầu.

**Ở đoạn code trong file main.c**
```
    SystemState system = {
        .mode = MODE_AUTO,
        .pump = PUMP_OFF,
        .led = LED_NORMAL,
        .moistureMin = MOISTURE_MIN_THRESHOLD,
        .moistureMax = MOISTURE_MAX_THRESHOLD,
        .wateringDuration = WATERING_DURATION
    };
```

