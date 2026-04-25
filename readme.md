# Semaphore & Mutex

## 1. Lý thuyết
Semaphore trong FreeRTOS là một cơ chế dùng để gửi tín hiệu giữa các task hoặc giữa interrupt và task. Khi chưa có tín hiệu, task sẽ bị dừng lại và chờ; khi có tín hiệu, task sẽ được đánh thức để tiếp tục chạy. Nhờ đó, semaphore giúp các phần trong hệ thống phối hợp đúng thời điểm và tránh xung đột (Đồng bộ dữ liệu)

Mutex trong FreeRTOS là một “ổ khóa” dùng để bảo vệ tài nguyên dùng chung giữa các task. Khi một task đã khóa mutex, các task khác phải chờ cho đến khi mutex được mở (unlock) mới được truy cập. Nhờ đó, mutex giúp tránh xung đột dữ liệu và hỗ trợ cơ chế ưu tiên (priority inheritance) để hạn chế lỗi priority inversion.

Hiểu đơn giản:
Semaphore = “có sự kiện thì chạy” → dùng để báo hiệu (event)
Mutex = “khóa tài nguyên, dùng xong mở ra” → dùng để bảo vệ tài nguyên (resource)

## Khác biệt giữa binary semaphore và mutex
**Binary Semaphore**
```cpp
SemaphoreHandle_t sem;

void TaskA(void *param)
{
    printf("Task A: Doing work...\n");
    vTaskDelay(1000);

    printf("Task A: Done -> Give semaphore\n");
    xSemaphoreGive(sem);

    vTaskDelete(NULL);
}

void TaskB(void *param)
{
    printf("Task B: Waiting for semaphore...\n");

    xSemaphoreTake(sem, portMAX_DELAY);

    printf("Task B: Got semaphore -> Continue work\n");

    vTaskDelete(NULL);
}

int main(void)
{
    sem = xSemaphoreCreateBinary();

    xTaskCreate(TaskA, "A", 128, NULL, 1, NULL);
    xTaskCreate(TaskB, "B", 128, NULL, 1, NULL);

    vTaskStartScheduler();
}
```
**Output**
```cpp
Task B: Waiting for semaphore...
Task A: Doing work...
Task A: Done -> Give semaphore
Task B: Got semaphore -> Continue work
```
---

SemaphoreHandle_t mutex;

void TaskA(void *param)
{
    printf("Task A: Doing work...\n");
    vTaskDelay(1000);

    printf("Task A: Try to give mutex\n");
    xSemaphoreGive(mutex); // ❌ sai: không phải owner

    vTaskDelete(NULL);
}

void TaskB(void *param)
{
    printf("Task B: Waiting for mutex...\n");

    xSemaphoreTake(mutex, portMAX_DELAY);

    printf("Task B: Got mutex -> Continue work\n");

    vTaskDelete(NULL);
}

int main(void)
{
    mutex = xSemaphoreCreateMutex();

    xTaskCreate(TaskA, "A", 128, NULL, 1, NULL);
    xTaskCreate(TaskB, "B", 128, NULL, 1, NULL);

    vTaskStartScheduler();
}

**Output**
```cpp
Task B: Waiting for mutex...
Task A: Doing work...
Task A: Try to give mutex
```

---
**Nhận xét**
Semaphore dùng để báo hiệu và đồng bộ giữa các task (hoặc ISR với task). Nó không quan tâm “ai gửi, ai nhận”, chỉ cần có tín hiệu thì task chờ sẽ được đánh thức. Vì vậy thường dùng cho event như: interrupt báo dữ liệu sẵn sàng.

Mutex dùng để bảo vệ tài nguyên dùng chung. Nó có khái niệm ownership (task nào lock thì task đó phải unlock) và hỗ trợ priority inheritance để tránh priority inversion. Vì vậy dùng khi nhiều task cùng truy cập UART, SPI, biến chung,...

## Semaphore API

| **Tính năng**                          | **RTOS API**                     |
| -------------------------------------- | -------------------------------- |
| Create Binary Semaphore                | `xSemaphoreCreateBinary`         |
| Create Binary Semaphore (static)       | `xSemaphoreCreateBinaryStatic`   |
| Create Counting Semaphore              | `xSemaphoreCreateCounting`       |
| Create Counting Semaphore (static)     | `xSemaphoreCreateCountingStatic` |
| Take semaphore (wait / receive signal) | `xSemaphoreTake`                 |
| Give semaphore (send signal)           | `xSemaphoreGive`                 |
| Take semaphore from ISR                | `xSemaphoreTakeFromISR`          |
| Give semaphore from ISR                | `xSemaphoreGiveFromISR`          |
| Get semaphore count                    | `uxSemaphoreGetCount`            |
| Delete semaphore                       | `vSemaphoreDelete`               |

---

## Mutex API

| **Tính năng**                   | **RTOS API**                           |
| ------------------------------- | -------------------------------------- |
| Create Mutex                    | `xSemaphoreCreateMutex`                |
| Create Mutex (static)           | `xSemaphoreCreateMutexStatic`          |
| Create Recursive Mutex          | `xSemaphoreCreateRecursiveMutex`       |
| Create Recursive Mutex (static) | `xSemaphoreCreateRecursiveMutexStatic` |
| Lock mutex                      | `xSemaphoreTake`                       |
| Unlock mutex                    | `xSemaphoreGive`                       |
| Lock recursive mutex            | `xSemaphoreTakeRecursive`              |
| Unlock recursive mutex          | `xSemaphoreGiveRecursive`              |
| Get mutex owner                 | `xSemaphoreGetMutexHolder`             |
| Delete mutex                    | `vSemaphoreDelete`                     |

