# 联网配置 / Network Configuration

[中文首页](../README.md) · [English overview](../README.en.md) · [English instructions](#english)

## 中文说明

仓库中的真实 Wi-Fi 密码、OneNET token、天气 API key 及相关密钥副本已移除，配置默认留空。**不填写时，tea 固件跳过联网，小程序跳过对应的云端请求。** 原有通信和界面功能代码保留，填写自己的有效配置后再联调。

### 1. STM32 固件：Wi-Fi 与 OneNET MQTT

在 [tea 的 wifi.c](../02_Software/01_Source_Code/tea/MDK-ARM/Middlewares/WIFI/wifi.c) 顶部配置：

- `WIFI_SSID`：自己的 **2.4GHz** Wi-Fi 名称。
- `WIFI_PASSWORD`：该 Wi-Fi 的密码。
- `ONENET_MQTT_PRODUCT_ID`、`ONENET_MQTT_DEVICE_NAME`：自己的 OneNET 产品 ID 和设备名称。
- `ONENET_MQTT_TOKEN`：为该设备生成的 **MQTT 设备鉴权 token**，注意资源路径、权限和有效期。

这些宏使用 `#ifndef` 包装，可以由本地构建环境的预处理宏提供 C 字符串值，例如通过 Keil 的项目预处理宏配置注入；也可以仅在本机填写空字符串进行调试。不要提交填入真实值的源码、工程配置或包含凭据的固件产物。

### 2. 微信小程序：OneNET HTTP 鉴权与天气 API

在 [pages/index/index.js](../02_Software/03_wxxcx/pages/index/index.js) 中，本地调试需要填写：

- `config.auth_info`：自己的 **OneNET HTTP API 鉴权 token**。它与固件的 MQTT 设备 token 用途不同，不要混用。
- `config.product_id`、`config.device_name`：与固件对应的产品 ID、设备名称。
- `fetchWeatherData()` 中的 `API_KEY`：自己的 **心知天气 API key**，用于天气和空气质量接口；接口权限取决于自己的服务开通情况。

用微信开发者工具导入 `02_Software/03_wxxcx`，使用自己的小程序配置，并按实际服务设置合法请求域名。只在受控的本地环境调试，不要提交填入 token 或 key 的文件。

**小程序是客户端，无法安全隐藏 API 密钥。** 把密钥移到另一个 JS 文件、环境变量或本地存储，最终提供给客户端后仍可能被提取。生产环境应由自己的服务端保存 OneNET 鉴权信息和天气 API key，代理请求并校验用户/设备权限；不要把长期或高权限的鉴权 token 下发给客户端。

### 3. 辅助工具与泄露后的处理

[AT 指令示例](../02_Software/01_Source_Code/AT指令.txt) 仅保留占位符；[OneNET 配置说明](../02_Software/01_Source_Code/onenet.txt) 不再保存真实密钥。如需本地生成 token，将 [config.example.ini](../04_Tools/config.example.ini) 复制为同目录的 `config.ini`，再自行填写资源路径、有效期和对应密钥。生成的 `config.ini`、`Token.log` 已被忽略，请勿强制提交；使用辅助程序前请自行确认来源可信。

删除当前文件中的凭据**不会清除 Git 历史、已有克隆或缓存**。曾公开且仍在使用的 Wi-Fi 密码、OneNET token、用户 AccessKey / 设备密钥和天气 API key 应在对应路由器或平台更换、撤销或重新生成。仓库内的配置清理不代表已更改平台账户、替换实际凭据或重写 Git 历史。

## English

The repository stores no real Wi-Fi password, OneNET token, weather API key, or related secret copies. Credentials are blank by default. The `tea` firmware skips networking when required settings are missing, and the Mini Program skips the corresponding cloud requests.

### Firmware: Wi-Fi and OneNET MQTT

Configure the macros at the top of [wifi.c](../02_Software/01_Source_Code/tea/MDK-ARM/Middlewares/WIFI/wifi.c):

| Setting | Value to provide |
| --- | --- |
| `WIFI_SSID` | Your 2.4 GHz Wi-Fi network name |
| `WIFI_PASSWORD` | Its password |
| `ONENET_MQTT_PRODUCT_ID` | Your OneNET product ID |
| `ONENET_MQTT_DEVICE_NAME` | Your device name |
| `ONENET_MQTT_TOKEN` | A valid MQTT device authentication token with the appropriate resource, permissions, and expiry |

These macros use `#ifndef` guards, so local build definitions can supply C string values, for example through Keil preprocessor settings. Alternatively, fill the blank values only in your local working copy. Do not commit credentials in source code, project settings, or firmware binaries.

### Mini Program: OneNET HTTP and weather

In [pages/index/index.js](../02_Software/03_wxxcx/pages/index/index.js), configure:

- `config.auth_info`: your OneNET **HTTP API token**. This serves a different purpose from the firmware's MQTT device token.
- `config.product_id` and `config.device_name`: the product and device matching the firmware.
- `API_KEY` inside `fetchWeatherData()`: your Seniverse weather API key. Weather and air-quality access depend on your service permissions.

Import `02_Software/03_wxxcx` into WeChat DevTools, use your own Mini Program settings, and configure the permitted request domains for your services. Keep direct credential-based testing in a controlled local environment.

Mini Program clients cannot safely conceal secrets: moving keys to another JS file, environment variable, or local storage does not prevent extraction once provided to the client. For production, keep OneNET and weather credentials on your backend, proxy requests, and validate user/device permissions. Do not distribute long-lived or highly privileged tokens to clients.

### Supporting tools and previously exposed credentials

The [AT command examples](../02_Software/01_Source_Code/AT指令.txt) contain placeholders, and the [OneNET notes](../02_Software/01_Source_Code/onenet.txt) no longer store real keys. If you use the local token helper, copy [config.example.ini](../04_Tools/config.example.ini) to `04_Tools/config.ini` and supply your own resource, expiry, and key. Verify the executable's provenance before using it. Generated `config.ini` and `Token.log` are ignored by Git; do not force-add them.

Removing secrets from current files does not remove them from Git history, existing clones, or caches. Rotate or revoke any previously exposed credentials that are still valid at the router or service provider. Repository cleanup does not update service accounts, replace active credentials, or rewrite Git history.
