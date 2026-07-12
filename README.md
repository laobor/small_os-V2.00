# small_os-V2.00
Lightweight Chinese dual-mode RTOS. Sim mode: no while(1), no HW timer, all CPUs. Real mode: standard while(1) + SysTick, supports GD32/STM32. For dev debugging &amp; mass production.
# small_os V2.00

**一个支持“仿真/实时”双模式的轻量级国产嵌入式 RTOS**

small_os V2.00 是一款面向资源受限场景的国产实时操作系统内核。它创新性地提供了 **仿真任务** 与 **实时任务** 两种运行模式，既满足开发阶段快速迭代的需求，也保障量产固件的高可靠性。
small_os V2.00  由私有库内small_os（https://github.com/laobor/small_os.git）升级而成。

## ✨ 核心特性

- **极致精简**：内核最小占用 < 2KB ROM，< 256B RAM（视配置而定），适用于 Cortex-M0/M3/M4 等 MCU。
- **双模式设计**：
  - 🧪 **仿真任务模式**（轻量级仿真）  
    - 任务中 **禁止** 使用 `while(1)` / `for(;;)` 死循环，任务均为有限状态机或一次性执行（执行完自动删除）。  
    - 无需硬件定时器，可在纯软件环境（如 PC 模拟器）中运行，方便业务逻辑验证和单元测试。
  - ⚙️ **实时任务模式**（硬件级实跑）  
    - 任务中 **允许** 使用 `while(1)` / `for(;;)` 死循环，完全符合传统 RTOS 开发习惯。  
    - 依赖硬件时钟中断（SysTick）进行抢占式调度，确保实时响应。
- **模式切换**：通过 `#define SMALL_OS_MODE_REAL` 宏或配置文件选择模式，灵活适配不同开发阶段。
- **国产自主**：全内核自主研发，无第三方依赖，安全可控。

## 🔌 硬件支持

- **仿真模式**：支持所有处理器架构（可在无硬件的模拟环境中运行）。
- **实时模式**：当前支持 GD32、STM32 系列（其他 ARM Cortex-M 可快速移植）。

## 📖 快速开始

请参阅 [示例代码](examples/) 和 [文档](docs/) 了解如何使用。

 
