# 🌱 IoT Smart System for Agrotechnology

Proyek ini merupakan bagian dari modul **Workshop Agrotechnology (Internet of Things)** yang diselenggarakan oleh **Pusat Studi Multimedia & Robotika, Universitas Gunadarma**. Sistem ini menggunakan mikrokontroler **WeMos ESP32** untuk memantau kondisi lingkungan serta mengotomatisasi perangkat pendukung.

## Deskripsi Sistem

Sistem ini dirancang untuk pemantauan lahan pertanian secara *real-time*. Data yang dibaca oleh sensor dikirim ke *cloud* melalui platform **ThingSpeak** untuk keperluan analisis dan visualisasi data, serta ditampilkan secara lokal melalui layar **LCD 2004**.

## Fitur Utama

* **Monitoring Sensor:** Membaca suhu dan kelembapan udara menggunakan sensor DHT21 serta kelembapan tanah menggunakan Soil Moisture Sensor.
* **Otomatisasi:** Kontrol relay otomatis berdasarkan kondisi suhu, kelembapan udara, dan kelembapan tanah.
* **Integrasi IoT:** Pengiriman data ke platform ThingSpeak menggunakan koneksi WiFi.
* **Visualisasi Lokal:** Menampilkan data status sistem secara *real-time* pada layar LCD 2004.

## Komponen yang Digunakan

| No | Komponen             | Jumlah |
| -- | -------------------- | ------ |
| 1  | Wemos D1 R32 (ESP32) | 1      |
| 2  | Sensor DHT21         | 1      |
| 3  | Soil Moisture Sensor | 1      |
| 4  | LCD 20x4 I2C         | 1      |
| 5  | Relay Module         | 2      |
| 6  | Pompa Air            | 1      |
| 7  | Kipas (Opsional)     | 1      |

---

## Konfigurasi Pin

| Komponen             | Pin Wemos D1 R32   |
| -------------------- | ------------------ |
| DHT21                | GPIO 4             |
| Soil Moisture Sensor | GPIO 34            |
| Relay Fan            | GPIO 17            |
| Relay Pump           | GPIO 26            |
| LCD I2C              | SDA (21), SCL (22) |

---

## Cara Penggunaan

### 1. Persiapan

* Install **Arduino IDE**
* Tambahkan Board Manager untuk **ESP32**

### 2. Konfigurasi

Sesuaikan data berikut pada program:

* `ssid`
* `password`
* `Channel ID`
* `Write API Key`

### 3. Wiring

Hubungkan semua komponen sesuai tabel konfigurasi pin.

### 4. Upload Program

* Hubungkan board menggunakan USB
* Upload program ke ESP32
* Lepas kabel daya DC sebelum proses upload untuk menghindari gangguan daya

---

## Cara Kerja Sistem

1. Sensor membaca suhu, kelembapan udara, dan kelembapan tanah.
2. Data ditampilkan pada LCD 20x4.
3. ESP32 mengirim data ke ThingSpeak melalui WiFi.
4. Relay akan aktif otomatis untuk mengontrol pompa atau kipas berdasarkan kondisi sensor.

---

## Platform IoT

* ThingSpeak
* ESP32 WiFi Communication
* Real-time Monitoring

---

## Dokumentasi

Repositori ini berisi:

* Source code Arduino
* Wiring diagram
* Dokumentasi workshop
* Konfigurasi ThingSpeak
* Dokumentasi hasil pengujian sistem

---

## 👨‍💻 Developer

**Pusat Studi Multimedia & Robotika**
Universitas Gunadarma

---

## 📜 License

Project ini dibuat untuk kebutuhan pembelajaran dan workshop akademik.
