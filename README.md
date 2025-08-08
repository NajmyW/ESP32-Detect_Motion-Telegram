# 🚨 Sensor Deteksi Gerak ESP32 dengan Notifikasi Telegram

Proyek ini menggunakan **ESP32** dan sensor PIR untuk mendeteksi pergerakan, lalu mengirimkan **notifikasi secara otomatis ke Telegram** menggunakan **Telegram Bot API**.  
Cocok untuk sistem keamanan rumah, monitoring ruangan, atau proyek IoT lainnya.

---

## 📌 Fitur
- Deteksi gerakan menggunakan sensor **PIR** (Passive Infrared Sensor).
- Mengirim notifikasi real-time ke **Telegram**.
- Dapat digunakan dengan koneksi **Wi-Fi**.
- Konsumsi daya rendah (ESP32 deep sleep opsional).
- Konfigurasi **token bot** dan **chat ID** yang mudah.

---

## 🛠️ Hardware yang Dibutuhkan
| No  | Komponen           | Jumlah |
| --- | ------------------ | ------ |
| 1   | ESP32 Dev Board    | 1      |
| 2   | Beep Speaker       | 1      |
| 3   | Sensor PIR HC-SR501| 1      |
| 4   | Kabel Jumper       | -      |
| 5   | Breadboard         | 1      |
| 6   | Sumber Daya (USB/Adaptor) | 1 |

---

## 🔌 Rangkaian
**Koneksi Sensor PIR ke ESP32:**
| PIR Pin | ESP32 Pin |
| ------- | --------- |
| VCC     | 5V        |
| GND     | GND       |
| OUT     | GPIO 27*  |

> *GPIO dapat disesuaikan pada kode program.

---

## 📲 Persiapan Telegram Bot
1. Buka Telegram, cari **BotFather**.
2. Buat bot baru dengan perintah `/newbot` dan ikuti instruksi.
3. Simpan **Token API** yang diberikan.
4. Untuk mendapatkan **Chat ID**:
   - Cari bot `@userinfobot` di Telegram.
   - Kirim pesan `/start`, lalu catat **Chat ID**.
5. Simpan **Token** dan **Chat ID** untuk digunakan pada program ESP32.

---

## 💻 Langkah Penggunaan
1. **Siapkan Arduino IDE**
   - Install **Board ESP32** melalui Board Manager.
   - Pastikan library `WiFi.h` dan `HTTPClient.h` tersedia (default ESP32).
   
2. **Masukkan Konfigurasi**
   - Masukkan **SSID Wi-Fi**, **Password**, **Bot Token**, dan **Chat ID** pada kode.
   
3. **Upload Program**
   - Sambungkan ESP32 ke komputer.
   - Upload program melalui Arduino IDE.
   
4. **Uji Sistem**
   - Gerakkan tangan di depan sensor PIR.
   - Periksa notifikasi masuk di Telegram.

---

## 📊 Alur Kerja
1. **Sensor PIR** mendeteksi pergerakan.
2. **ESP32** mengirimkan request ke **Telegram API**.
3. **Bot Telegram** mengirimkan notifikasi ke chat pengguna.

---

## ⚠️ Catatan
- Pastikan koneksi Wi-Fi stabil.
- Jaga token bot agar tidak dibagikan secara publik.
