# IoT Smart System for Agrotechnology

[cite_start]Proyek ini merupakan bagian dari modul **Workshop Agrotechnology (Internet of Things)** yang diselenggarakan oleh **Pusat Studi Multimedia & Robotika, Universitas Gunadarma**[cite: 3, 22]. [cite_start]Sistem ini menggunakan mikrokontroler **WeMos ESP32** untuk memantau kondisi lingkungan serta mengotomatisasi perangkat pendukung[cite: 30, 87, 264].

## Deskripsi Sistem
[cite_start]Sistem ini dirancang untuk pemantauan lahan pertanian secara *real-time*[cite: 285]. [cite_start]Data yang dibaca oleh sensor dikirim ke *cloud* melalui platform **ThingSpeak** untuk keperluan analisis dan visualisasi data, serta ditampilkan secara lokal melalui layar **LCD 2004**[cite: 255, 415].

## Fitur Utama
* [cite_start]**Monitoring Sensor:** Membaca suhu dan kelembapan udara (sensor DHT21) serta kelembapan tanah[cite: 285, 297].
* [cite_start]**Otomatisasi:** Kontrol relay otomatis berdasarkan kondisi suhu, kelembapan udara, dan kelembapan tanah[cite: 264, 376, 390].
* [cite_start]**Integrasi IoT:** Pengiriman data ke platform ThingSpeak menggunakan protokol WiFi[cite: 416, 483].
* [cite_start]**Visualisasi Lokal:** Menampilkan data status sistem secara *real-time* pada layar LCD 2004[cite: 255, 357].

## Komponen yang Digunakan
* [cite_start]**Mikrokontroler:** WeMos D1 R32 (ESP32) [cite: 30]
* [cite_start]**Sensor:** * DHT21 (Suhu & Kelembapan Udara) [cite: 297]
    * [cite_start]Soil Moisture Sensor (Kelembapan Tanah) [cite: 285]
* **Perangkat Keluaran:**
    * [cite_start]LCD 2004 + I2C Backpack [cite: 254]
    * [cite_start]Relay 4 Channel (dengan Optocoupler) [cite: 263]

## Cara Penggunaan
1. [cite_start]**Persiapan:** Pastikan Anda telah menginstal **Arduino IDE** dan menambahkan *Board Manager* untuk ESP32[cite: 35, 230].
2. [cite_start]**Konfigurasi:** * Sesuaikan konfigurasi WiFi (`ssid`, `password`) pada kode program[cite: 483].
    * [cite_start]Masukkan `Channel ID` dan `Write API Key` dari akun ThingSpeak Anda[cite: 444, 485].
3. [cite_start]**Wiring:** Hubungkan komponen ke pin WeMos D1 R32 sesuai dengan tabel *interface* yang tersedia di modul[cite: 401, 633].
4. [cite_start]**Upload:** Lepas kabel daya DC sebelum mengunggah program ke ESP32 melalui USB[cite: 406, 644].

## Dokumentasi
Untuk detail teknis, diagram pinout, dan logika program selengkapnya, silakan merujuk pada modul workshop yang tersedia di repositori ini.

---
*Dikembangkan oleh: [Nama Anda/Kelompok]*
*Pusat Studi Multimedia & Robotika - Universitas Gunadarma*

# Agrotech-Workshop

🌱 Smart Greenhouse Monitoring System (Non-IoT)

Workshop Agroteknologi – Sistem Monitoring Suhu, Kelembaban Udara, dan Kelembaban Tanah menggunakan Wemos D1

| No | Komponen             | Jumlah |      
| -- | -------------------- | ------ |
| 1  | Wemos D1 R32         | 1      |
| 2  | Sensor DHT21         | 1      |
| 3  | Soil Moisture Sensor | 1      |
| 4  | LCD 20x4 I2C         | 1      |
| 5  | Relay Module         | 2      |
| 6  | Pompa Air            | 1      |
| 7  | Kipas (opsional)     | 1      |

| Komponen       | Pin Wemos D1 R32   |
| -------------- | ------------------ |
| DHT21          | GPIO 4             |
| Soil Sensor    | GPIO 34            |
| Relay 1 (Fan)  | GPIO 17            |
| Relay 3 (Pump) | GPIO 26            |
| LCD I2C        | SDA (21), SCL (22) |



