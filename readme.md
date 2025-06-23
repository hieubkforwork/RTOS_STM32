## Delay functions in this project

### `osDelay`

- Provided by CMSIS-RTOS (or FreeRTOS).
- Suspends the calling **thread/task** for a given time (in milliseconds).
- Allows other tasks to run while waiting.
- Recommended when using an RTOS.

### `HAL_Delay`

- Provided by STM32 HAL library.
- Uses a blocking loop to wait for the given time.
- Blocks the whole CPU → no other task runs.
- Recommended only when **not using an RTOS**.

✅ **Tip:**  
When using an RTOS, prefer `osDelay` instead of `HAL_Delay` to keep multitasking smooth.
