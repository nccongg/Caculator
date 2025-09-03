# STM32 Calculator Project

Một project calculator đơn giản được phát triển cho vi điều khiển STM32 sử dụng C++ và HAL library.

## Mô tả

Project này demo một máy tính cơ bản với các chức năng:
- Cộng, trừ, nhân, chia
- Hiển thị kết quả trên LCD hoặc UART
- Xử lý input từ keypad
- Giao diện người dùng đơn giản

## Phần cứng yêu cầu

- STM32F103C8T6 (Blue Pill) hoặc tương tự
- LCD 16x2 hoặc UART để hiển thị
- Keypad 4x4 hoặc các nút bấm
- Breadboard và dây nối

## Cấu trúc project

```
STM32_Calculator_Project/
├── Core/
│   ├── Inc/           # Header files
│   └── Src/           # Source files
├── Drivers/            # STM32 HAL drivers
├── Middlewares/        # Middleware libraries
├── STM32F103C8T6_FLASH.ld  # Linker script
├── Makefile           # Build configuration
├── README.md          # This file
└── .gitignore         # Git ignore rules
```

## Tính năng

- [x] Các phép tính cơ bản
- [x] Xử lý input từ keypad
- [x] Hiển thị kết quả
- [x] Xử lý lỗi chia cho 0
- [x] Giao diện người dùng thân thiện

## Cách build

### Trên Desktop (Testing):

**Windows:**
```batch
# Build demo program
build_demo.bat

# Clean build files
clean.bat
```

**Linux/macOS:**
```bash
# Build demo program
make -f Makefile.demo

# Run demo
make -f Makefile.demo run

# Clean build files
make -f Makefile.demo clean
```

### Trên STM32:

1. Cài đặt ARM GCC toolchain
2. Cài đặt Make
3. Chạy lệnh build:
   ```bash
   make clean
   make all
   ```

## Cách flash

Sử dụng ST-Link Utility hoặc OpenOCD:
```bash
make flash
```

## Tác giả

Được tạo để demo GitHub với project STM32 đơn giản.

## License

MIT License - Xem file LICENSE để biết thêm chi tiết.
