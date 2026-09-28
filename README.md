# Internet_of_Things
# HW1 - AMB82-MINI Voice LED Controller

本專案為 HW1 作業，主要實作以語音辨識控制 AMB82-MINI 板上 LED。

專案包含兩份主要檔案：

- `615K0025C.ino`：AMB82-MINI 開發板端程式，負責接收控制指令並控制藍色與綠色 LED。
- `voice_led_controller.html`：電腦端語音控制介面，負責語音辨識、指令轉換與 Serial 傳輸。

系統流程為：

使用者語音 → 語音辨識 → 指令轉換 → Serial 傳輸 → AMB82-MINI → LED 控制

---

## 專案介紹

本專案使用生成式 AI 輔助開發（Vibe Coding），建立一套以語音控制 AMB82-MINI 開發板 LED 的系統。

使用者透過電腦麥克風輸入語音，瀏覽器進行語音辨識後，將辨識結果轉換為控制指令，並透過 USB Serial 傳送至 AMB82-MINI。

AMB82-MINI 接收到指令後，控制板載藍色 LED 或綠色 LED，並將執行結果回傳至電腦端顯示。

---

## 檔案說明

### `615K0025C.ino`

Ameba Mini 端程式，主要功能包含：

- 接收 `LEFT`、`RIGHT`、`BLUE`、`STATUS` 指令
- 控制藍色 LED 與綠色 LED
- 藍色 LED 閃爍三次
- 回傳 LED 目前狀態
- 處理未知指令與過長指令

### `voice_led_controller.html`

電腦端語音控制介面，主要功能包含：

- 使用瀏覽器麥克風進行語音辨識
- 將辨識結果轉換為控制指令
- 使用 Web Serial 傳送指令至 AMB82-MINI
- 顯示板端回傳的執行結果
- 處理非控制語句、通訊失敗與逾時情況

---

## 執行環境

### 硬體

- AMB82-MINI 開發板
- USB 傳輸線
- 電腦

### 開發環境

- Arduino IDE
- AMB82-MINI Board Support Package
- Google Chrome 或 Microsoft Edge

### 通訊設定

- Serial Baud Rate：`115200 bps`
- LED 腳位：
  - Blue LED：`LED_B`
  - Green LED：`LED_G`

---

## 操作方式

1. 使用 Arduino IDE 開啟並燒錄 `615K0025C.ino`。
2. 使用 Chrome 或 Edge 開啟 `voice_led_controller.html`。
3. 按下 `Connect Ameba` 並選擇 AMB82-MINI 的 Serial Port。
4. 按下 `Start listening` 並允許麥克風權限。
5. 說出語音指令：
   - `left`：藍色 LED 亮起
   - `right`：綠色 LED 亮起
   - `blue`：藍色 LED 閃爍三次
6. 可按下 `Read LED status` 查詢目前 LED 狀態。

---

## HW1 重點

本作業主要練習使用生成式 AI 進行 Vibe Coding，並整合：

- 語音辨識
- Serial 通訊
- 嵌入式控制
- LED 狀態回傳
- 異常處理
