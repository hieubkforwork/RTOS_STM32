# 🚀 getState RTOS

<!-- ![MyProject Banner](https://raw.githubusercontent.com/tennguoidung/myproject/main/assets/banner.png) -->

> 📌 Because CMSIS RTOS doesn't support API to get state, we need to change into FreeRTOS using eTaskGetState API.

<!-- ---

## 🌟 Tính năng

- 🔍 Phân tích file log định dạng `.log`
- 🎯 Lọc theo mức độ log: `INFO`, `WARN`, `ERROR`
- 📤 Xuất dữ liệu ra định dạng `.csv`, `.json`
- ⚙️ Giao diện dòng lệnh dễ dùng

---

## 🖼️ Giao diện (ví dụ minh họa)

![Demo GIF](https://raw.githubusercontent.com/tennguoidung/myproject/main/assets/demo.gif)

--- -->

## 📥 Setup

### 1. Enable eTaskGetState in file FreeRTOSConfig.h
```c
#define INCLUDE_eTaskGetState 1
```
![Demo1](getStateb1.png)
 
 ### 2. Casting from type osThreadId to TaskHandle_t

![Demo1](getStateb2.png)


## 🖼️ Usage
### 1. Get state of task1 & task2

![Demo1](getStateb3.png)

![Demo1](getStateb4.png)

### 2.Hercules Testing
![Demo1](getState4.png)