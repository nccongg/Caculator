# STM32 Calculator Project - Build Guide

## Tổng quan

Project này bao gồm một máy tính đơn giản được phát triển cho STM32 sử dụng C++ và HAL library. Project có thể được build và test trên desktop trước khi deploy lên STM32.

## Cấu trúc Project

```
STM32_Calculator_Project/
├── Core/
│   ├── Inc/           # Header files
│   │   ├── main.h
│   │   ├── calculator.h
│   │   ├── display.h
│   │   └── keypad.h
│   └── Src/           # Source files
│       ├── main.cpp
│       ├── calculator.cpp
│       ├── display.cpp
│       └── keypad.cpp
├── demo.cpp           # Demo program for desktop testing
├── mock_hal.cpp       # Mock STM32 HAL implementation
├── Makefile           # Build for STM32
├── Makefile.demo      # Build for desktop testing
├── README.md          # Project documentation
└── BUILD_GUIDE.md     # This file
```

## Yêu cầu hệ thống

### Để build cho STM32:
- ARM GCC toolchain (arm-none-eabi-gcc)
- Make utility
- ST-Link Utility hoặc OpenOCD để flash

### Để build cho desktop testing:
- GCC/G++ compiler (C++11 support)
- Make utility

## Build và Test trên Desktop

### 1. Cài đặt dependencies

**Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install -y build-essential g++ make
```

**macOS:**
```bash
brew install gcc make
```

**Windows (MSYS2):**
```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make
```

### 2. Build demo program

```bash
cd STM32_Calculator_Project
make -f Makefile.demo
```

### 3. Chạy demo

```bash
make -f Makefile.demo run
```

Hoặc chạy trực tiếp:
```bash
./calculator_demo
```

### 4. Clean build files

```bash
make -f Makefile.demo clean
```

## Build cho STM32

### 1. Cài đặt ARM toolchain

**Ubuntu/Debian:**
```bash
sudo apt-get install gcc-arm-none-eabi
```

**macOS:**
```bash
brew install arm-none-eabi-gcc
```

**Windows:**
Tải và cài đặt ARM GCC từ ARM website hoặc sử dụng MSYS2.

### 2. Build project

```bash
cd STM32_Calculator_Project
make clean
make all
```

### 3. Flash lên STM32

```bash
make flash
```

## Các target có sẵn

### Makefile.demo targets:
- `all` - Build demo program
- `clean` - Remove build files
- `run` - Build and run demo
- `install-deps` - Install build dependencies
- `help` - Show help message

### Makefile targets (STM32):
- `all` - Build STM32 project
- `clean` - Remove build files
- `flash` - Flash to STM32

## Troubleshooting

### Lỗi compile thường gặp:

1. **Missing compiler:**
   - Cài đặt GCC/G++ compiler
   - Đảm bảo PATH có compiler

2. **C++11 not supported:**
   - Cập nhật compiler lên phiên bản mới hơn
   - Sử dụng `-std=c++14` hoặc `-std=c++17`

3. **Missing STM32 HAL headers:**
   - Sử dụng mock headers cho desktop testing
   - Cài đặt STM32CubeIDE cho development thực tế

### Lỗi build STM32:

1. **Missing ARM toolchain:**
   - Cài đặt arm-none-eabi-gcc
   - Kiểm tra PATH

2. **Linker errors:**
   - Kiểm tra startup file và linker script
   - Đảm bảo tất cả symbols được định nghĩa

## Testing

### Demo program test:
- Test các phép tính cơ bản
- Test error handling
- Test memory functions
- Test input processing

### STM32 testing:
- Flash lên board
- Kết nối UART để xem output
- Test keypad input
- Kiểm tra LED status

## Development Workflow

1. **Desktop Development:**
   - Code và test trên desktop trước
   - Sử dụng mock HAL functions
   - Debug logic và algorithms

2. **STM32 Integration:**
   - Replace mock functions với real HAL
   - Test trên hardware thực
   - Optimize cho embedded constraints

3. **Iteration:**
   - Fix bugs trên desktop
   - Test trên STM32
   - Repeat cho đến khi hoàn thiện

## Contributing

1. Fork project
2. Create feature branch
3. Make changes
4. Test thoroughly
5. Submit pull request

## License

MIT License - Xem file LICENSE để biết thêm chi tiết.
