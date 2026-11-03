# 智能茶艺机 · Intelligent Tea Art Machine

**让自己做的机器，完成添茶、注水、摇壶和倒茶。**

这是一个把 STM32 控制、电路设计、机械结构、串口触摸屏和微信小程序结合起来的茶艺机 DIY 项目。你可以用它研究自动泡茶的动作流程，也可以从中拆出一个小模块，做自己的自动倒水装置、机械茶台或物联网练习。

从电路到模型，从固件到界面，仓库保留了制作这台机器的多种工程资料，方便你看懂、修改，再做出自己的版本。

![智能茶艺机实物正面](05_Information/电子版照片/正面.jpg)

> 实物照片来自本仓库。[查看更多角度](05_Information/电子版照片)
>
> 本项目适合学习、实验和二次制作。仓库包含多个开发阶段的工程，复现时需要按实际硬件调试；下文会说明已有内容和仍需完善的部分。

## 它有什么用？

泡茶时，添茶、加水、移动茶壶、倒茶往往需要人反复操作。这个项目尝试把这些动作编排成程序，让电机、舵机和水泵配合完成。

| 模块 | 仓库里有什么 | 你能拿它做什么 |
| --- | --- | --- |
| 茶艺动作 | 添茶、注水、摇壶、倒茶以及清洗的动作编排 | 观察机械动作如何协作，修改角度和时序，设计自己的泡茶流程 |
| 执行机构 | 舵机缓动、步进电机位置与速度控制、直流电机及水泵驱动代码 | 从控制一个舵机开始，逐步组合成能工作的机构 |
| 本地操作 | 串口屏通信代码、HMI 界面工程和图片素材 | 给机器做一个能直接点击操作的面板 |
| 联网操作 | Wi-Fi AT 指令、OneNET MQTT 通信、微信小程序 | 学习设备如何上报状态、接收手机端指令 |
| 机械与电路 | 电路工程、原理图 PDF、SolidWorks 零件与装配模型、STEP 文件 | 理解软硬件如何配合，按自己的尺寸和器件调整设计 |
| AI 实验 | 独立的 NanoEdge AI 气味信号分类工程 | 探索传感器采样和单片机端分类，不必一开始就加入主控系统 |

## 它是怎么配合工作的？

```text
本地操作：串口触摸屏 → STM32 主控
联网操作：微信小程序 ↔ OneNET 云平台 ↔ Wi-Fi 模块 ↔ STM32 主控
执行动作：STM32 主控 → 舵机 / 电机 / 水泵 → 茶具与水路机构
```

主控工程以 STM32G431 为核心。程序接收操作指令，再按时间安排不同机构的动作；串口屏负责本地交互，OneNET 和微信小程序提供联网交互的代码基础。

AI 分类是单独的实验工程，需要独立调试。联网功能也需要配置你自己的设备和服务，不能只下载小程序就直接控制机器。

## 文件结构

下面只列出主要入口，省略芯片驱动库、第三方库和中间文件。

```text
IntelligentTeaArt_Machine/
├── 01_Hardware/                    # 电路设计与仿真
│   ├── 01_Project/
│   │   ├── Complete_project.epro   # 电路工程
│   │   ├── core2.0.pdf             # 核心板电路图
│   │   ├── control2.0.pdf          # 控制板电路图
│   │   └── Servo.pdf              # 舵机相关电路图
│   └── 02_Simulation/             # 温度电路仿真文件（.ms14）
├── 02_Software/
│   ├── 00_Ref/test2/              # 参考工程，含步进电机控制说明
│   ├── 01_Source_Code/
│   │   ├── tea1/                  # 茶艺机控制工程之一
│   │   ├── tea2/                  # 茶艺机控制工程之一
│   │   ├── tea3/                  # 含茶艺动作编排、串口屏与联网代码
│   │   ├── EdgeAI/                # 传感器采样与 NanoEdge AI 分类实验
│   │   ├── ai/                    # AI 库、模型相关文件与说明
│   │   └── 移植HAL库/             # HAL 库移植笔记及配图
│   ├── 02_UI/                     # 串口屏 HMI 工程、TFT 文件和界面素材
│   └── 03_wxxcx/                  # 微信小程序，含 OneNET 交互页面
├── 03_Mechanical/                 # SolidWorks 零件、装配体与 STEP 模型
├── 04_Tools/                      # 辅助程序与配置文件
├── 05_Information/
│   └── 电子版照片/               # 实物各角度照片
├── LICENSE                       # MIT 许可证
└── README.md                     # 项目介绍与入门指引
```

常用入口：

- **想看电路怎么接：** [电路图与工程](01_Hardware/01_Project)。
- **想改泡茶动作：** [tea3 的 app.c](02_Software/01_Source_Code/tea3/MDK-ARM/APP/app.c) 中的动作表；[commond.h](02_Software/01_Source_Code/tea3/MDK-ARM/APP/commond.h) 中的舵机位置参数。
- **想看动作何时执行：** [任务调度 TaskList.c](02_Software/01_Source_Code/tea3/MDK-ARM/TimePiece/TaskList.c)。
- **想改机器上的界面：** [串口屏 UI 目录](02_Software/02_UI)。
- **想改手机端：** [微信小程序目录](02_Software/03_wxxcx)。
- **想看整机结构：** [机械设计目录](03_Mechanical)，其中包含 `装配体1.SLDASM`、`装配体1.STEP` 和 `kongfu tea.SLDASM` 等文件。

## 联网前需要自行提供的配置

仓库中的真实 Wi-Fi 密码、OneNET token、天气 API key 及相关密钥副本已移除，配置默认留空。**不填写时，tea3 固件跳过联网，小程序跳过对应的云端请求。** 原有通信和界面功能代码保留，填写自己的有效配置后再联调。

### 1. STM32 固件：Wi-Fi 与 OneNET MQTT

在 [tea3 的 wifi.c](02_Software/01_Source_Code/tea3/MDK-ARM/Middlewares/WIFI/wifi.c) 顶部配置：

- `WIFI_SSID`：自己的 **2.4GHz** Wi-Fi 名称。
- `WIFI_PASSWORD`：该 Wi-Fi 的密码。
- `ONENET_MQTT_PRODUCT_ID`、`ONENET_MQTT_DEVICE_NAME`：自己的 OneNET 产品 ID 和设备名称。
- `ONENET_MQTT_TOKEN`：为该设备生成的 **MQTT 设备鉴权 token**，注意资源路径、权限和有效期。

这些宏使用 `#ifndef` 包装，可以由本地构建环境的预处理宏提供 C 字符串值，例如通过 Keil 的项目预处理宏配置注入；也可以仅在本机填写空字符串进行调试。不要提交填入真实值的源码、工程配置或包含凭据的固件产物。换用旧版 tea2 时，Wi-Fi 入口为 [commond.h](02_Software/01_Source_Code/tea2/MDK-ARM/APP/commond.h) 中的 `SSID` 和 `PASS`；该版本的云端示例与 tea3 不同，需按自身工程调试。

### 2. 微信小程序：OneNET HTTP 鉴权与天气 API

在 [pages/index/index.js](02_Software/03_wxxcx/pages/index/index.js) 中，本地调试需要填写：

- `config.auth_info`：自己的 **OneNET HTTP API 鉴权 token**。它与固件的 MQTT 设备 token 用途不同，不要混用。
- `config.product_id`、`config.device_name`：与固件对应的产品 ID、设备名称。
- `fetchWeatherData()` 中的 `API_KEY`：自己的 **心知天气 API key**，用于天气和空气质量接口；接口权限取决于自己的服务开通情况。

用微信开发者工具导入 `02_Software/03_wxxcx`，使用自己的小程序配置，并按实际服务设置合法请求域名。只在受控的本地环境调试，不要提交填入 token 或 key 的文件。

**小程序是客户端，无法安全隐藏 API 密钥。** 把密钥移到另一个 JS 文件、环境变量或本地存储，最终提供给客户端后仍可能被提取。生产环境应由自己的服务端保存 OneNET 鉴权信息和天气 API key，代理请求并校验用户/设备权限；不要把长期或高权限的鉴权 token 下发给客户端。

### 3. 辅助工具与泄露后的处理

[AT 指令示例](02_Software/01_Source_Code/AT指令.txt) 仅保留占位符；[OneNET 配置说明](02_Software/01_Source_Code/onenet.txt) 不再保存真实密钥。如需本地生成 token，将 [config.example.ini](04_Tools/config.example.ini) 复制为同目录的 `config.ini`，再自行填写资源路径、有效期和对应密钥。生成的 `config.ini`、`Token.log` 已被忽略，请勿强制提交；使用辅助程序前请自行确认来源可信。

删除当前文件中的凭据**不会清除 Git 历史、已有克隆或缓存**。曾公开且仍在使用的 Wi-Fi 密码、OneNET token、用户 AccessKey / 设备密钥和天气 API key 应在对应路由器或平台更换、撤销或重新生成。本次代码清理没有更改任何平台账户、替换实际凭据或重写 Git 历史。

## 一起改进

欢迎通过 [Issues](https://github.com/Epiphany-Leave/IntelligentTeaArt_Machine/issues) 分享问题、复现记录和改进想法，也欢迎提交 Pull Request。

如果你做出了自己的版本，欢迎分享照片、所用硬件和调试经验。补充器件清单、接线说明和装配步骤，也能帮助下一位 DIY 爱好者更快开始。

## 许可证

本项目的原创内容采用 [MIT License](LICENSE)。

仓库包含 STM32 HAL、CMSIS、LVGL、NanoEdge AI 等第三方代码或库；这些部分仍遵循各自的版权声明和许可证，根目录 MIT 许可证不替代第三方授权。
