# STM32 Calculator Project - Tóm tắt

## Tổng quan

Project **STM32 Calculator** là một máy tính đơn giản được phát triển cho vi điều khiển STM32 sử dụng C++ và HAL library. Project này được thiết kế để demo GitHub với cấu trúc chuẩn và có thể chạy được trên cả desktop và STM32.

## Tính năng chính

### 🧮 Calculator Class
- **Phép tính cơ bản**: Cộng, trừ, nhân, chia
- **Phép tính nâng cao**: Lũy thừa, căn bậc hai, phần trăm
- **Chức năng bộ nhớ**: Lưu, gọi, cộng, trừ, xóa bộ nhớ
- **Xử lý lỗi**: Kiểm tra chia cho 0, số không hợp lệ
- **Input processing**: Xử lý input từ keypad theo thứ tự

### 📺 Display Class
- **Hỗ trợ đa dạng**: LCD và UART
- **Hiển thị thông minh**: Số, text, phép tính, kết quả
- **Điều khiển cursor**: Vị trí hiển thị linh hoạt
- **Status display**: Hiển thị trạng thái máy tính

### ⌨️ Keypad Class
- **Matrix scanning**: Quét keypad 4x4
- **Debouncing**: Xử lý chống dội phím
- **Event handling**: Callback system cho key events
- **GPIO control**: Điều khiển pin linh hoạt

## Cấu trúc Project

```
STM32_Calculator_Project/
├── 📁 Core/                    # Core application files
│   ├── 📁 Inc/                # Header files
│   │   ├── main.h             # Main header
│   │   ├── calculator.h       # Calculator class header
│   │   ├── display.h          # Display class header
│   │   ├── keypad.h           # Keypad class header
│   │   └── stm32f1xx_hal.h   # Mock STM32 HAL header
│   └── 📁 Src/                # Source files
│       ├── main.cpp            # Main application
│       ├── calculator.cpp      # Calculator implementation
│       ├── display.cpp         # Display implementation
│       └── keypad.cpp         # Keypad implementation
├── 📄 demo.cpp                 # Desktop demo program
├── 📄 mock_hal.cpp             # Mock HAL implementation
├── 📄 main.cpp                 # STM32 main program
├── 📄 startup_stm32f103xb.s   # STM32 startup code
├── 📄 system_stm32f1xx.c      # System configuration
├── 📄 STM32F103C8T6_FLASH.ld  # Linker script
├── 📄 Makefile                 # STM32 build configuration
├── 📄 Makefile.demo            # Desktop build configuration
├── 📄 build_demo.bat           # Windows build script
├── 📄 clean.bat                # Windows clean script
├── 📄 README.md                # Project documentation
├── 📄 BUILD_GUIDE.md           # Build instructions
├── 📄 PROJECT_SUMMARY.md       # This file
├── 📄 LICENSE                  # MIT License
└── 📄 .gitignore               # Git ignore rules
```

## Công nghệ sử dụng

### 🖥️ Desktop Development
- **Compiler**: GCC/G++ (C++11)
- **Build System**: Make hoặc Batch scripts
- **Mock System**: STM32 HAL simulation

### 🔧 STM32 Development
- **MCU**: STM32F103C8T6 (Blue Pill)
- **Toolchain**: ARM GCC (arm-none-eabi-gcc)
- **HAL Library**: STM32F1xx HAL
- **Build System**: Make với linker script

## Cách sử dụng

### 🚀 Quick Start

1. **Clone project:**
   ```bash
   git clone <repository-url>
   cd STM32_Calculator_Project
   ```

2. **Desktop testing:**
   ```bash
   # Windows
   build_demo.bat
   
   # Linux/macOS
   make -f Makefile.demo
   make -f Makefile.demo run
   ```

3. **STM32 deployment:**
   ```bash
   make clean
   make all
   make flash
   ```

### 📋 Requirements

**Desktop:**
- GCC/G++ compiler với C++11 support
- Make utility (Linux/macOS)

**STM32:**
- ARM GCC toolchain
- ST-Link Utility hoặc OpenOCD
- STM32F103C8T6 board

## Demo Features

### 🧮 Calculator Operations
```
Basic: 123 + 456 = 579
Memory: Store 100, Recall 100
Advanced: 2^8 = 256, √144 = 12
Error: 10 ÷ 0 = ERROR
```

### 📺 Display Output
```
=== STM32 CALCULATOR ===
123 + 456 = 579
Memory: [M] Error: [E]
```

### ⌨️ Keypad Input
```
Matrix Layout:
┌─────┬─────┬─────┬─────┐
│  1  │  2  │  3  │  +  │
├─────┼─────┼─────┼─────┤
│  4  │  5  │  6  │  -  │
├─────┼─────┼─────┼─────┤
│  7  │  8  │  9  │  *  │
├─────┼─────┼─────┼─────┤
│  C  │  0  │  =  │  /  │
└─────┴─────┴─────┴─────┘
```

## Development Workflow

### 🔄 Iterative Development
1. **Desktop Development** → Code và test logic
2. **Mock Testing** → Verify với mock HAL
3. **STM32 Integration** → Deploy lên hardware
4. **Hardware Testing** → Test thực tế
5. **Optimization** → Tối ưu cho embedded

### 🧪 Testing Strategy
- **Unit Testing**: Test từng class riêng biệt
- **Integration Testing**: Test tương tác giữa các class
- **Hardware Testing**: Test trên STM32 thực
- **Mock Testing**: Test với simulated hardware

## Performance & Optimization

### ⚡ STM32 Constraints
- **Flash**: 64KB (STM32F103C8T6)
- **RAM**: 20KB
- **Clock**: 72MHz
- **GPIO**: 37 pins

### 🎯 Optimization Tips
- Sử dụng `const` cho constants
- Minimize dynamic memory allocation
- Optimize GPIO operations
- Efficient keypad scanning

## Extensibility

### 🔌 Plugin Architecture
- **Calculator**: Thêm phép tính mới
- **Display**: Hỗ trợ display khác
- **Keypad**: Thay đổi layout keypad
- **HAL**: Port sang MCU khác

### 📱 Future Features
- [ ] Scientific calculator functions
- [ ] Multiple display support
- [ ] Bluetooth connectivity
- [ ] Data logging
- [ ] Web interface

## Contributing

### 🤝 How to Contribute
1. Fork project
2. Create feature branch
3. Implement changes
4. Test thoroughly
5. Submit pull request

### 📝 Code Standards
- **C++11** compliance
- **Clear naming** conventions
- **Comprehensive comments**
- **Error handling**
- **Memory safety**

## License

**MIT License** - Cho phép sử dụng tự do cho mục đích thương mại và cá nhân.

## Support

### 📚 Documentation
- README.md - Hướng dẫn cơ bản
- BUILD_GUIDE.md - Hướng dẫn build chi tiết
- PROJECT_SUMMARY.md - Tóm tắt project này

### 🐛 Issues & Bugs
- Report issues trên GitHub
- Include system information
- Provide reproduction steps
- Attach error logs

### 💡 Ideas & Suggestions
- Feature requests welcome
- Performance improvements
- Code optimization
- Documentation enhancement

---

**STM32 Calculator Project** - Một project demo hoàn chỉnh cho GitHub, thể hiện kỹ năng embedded C++ development và project organization.
