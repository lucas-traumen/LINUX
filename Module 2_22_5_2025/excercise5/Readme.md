#  Cách build make file
`make all` để chạy file main.exe\
`make clean` để xóa file main.exe đã được thực thi của đoạn code trước\
# Mô tả bài toán
## Định nghĩa các trạng thái hoạt động
Chế độ hệ thống:
-  MODE_AUTO: Hệ thống tự động quản lý việc tưới nước dựa trên cảm biến.
-  MODE_MANUAL: Hệ thống chờ lệnh thủ công hoặc bị khóa tự động.\
Trạng thái tưới nước của bơm:
-  PUMP_OFF: Bơm không hoạt động.
-  PUMP_ON: Bơm đang hoạt động.\
Trạng thái LED:
-  LED_NORMAL: Hệ thống hoạt động bình thường, không tưới.
-  LED_WATERING: Hệ thống đang tưới nước.
-  LED_LOW_MOISTURE_ALERT: Độ ẩm đất quá thấp (chưa tưới hoặc tưới không đủ).\
**Ở đoạn code**

