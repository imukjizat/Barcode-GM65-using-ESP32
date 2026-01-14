# **Barcode Scanner IoT with API Integration**

Proyek ini merupakan aplikasi Internet of Things (IoT) berbasis ESP32 yang dirancang untuk membaca barcode menggunakan pemindai barcode GM65 dan mengirimkan data barcode tersebut ke server API melalui koneksi WiFi. Sistem ini dapat digunakan dalam berbagai aplikasi seperti manajemen inventaris, sistem penjualan, dan pelacakan barang dalam lingkungan industri maupun komersial.

## **Deskripsi**

Dalam proyek ini, ESP32 digunakan sebagai perangkat utama yang terhubung ke jaringan WiFi dan berfungsi untuk melakukan komunikasi dengan API menggunakan HTTP POST. Ketika barcode dipindai, data barcode yang terdeteksi akan segera dikirimkan ke server API untuk diproses lebih lanjut. Sistem ini memanfaatkan pemindai barcode GM65 yang terhubung dengan ESP32 melalui komunikasi serial UART (Universal Asynchronous Receiver/Transmitter).

### **Fitur Utama:**
- **Koneksi WiFi otomatis:** ESP32 akan otomatis menghubungkan diri ke jaringan WiFi yang telah disiapkan.
- **Pembacaan barcode:** Data barcode dibaca menggunakan pemindai GM65 yang terhubung dengan ESP32.
- **Pengiriman data ke API:** Setelah barcode terbaca, data akan dikirimkan ke server API menggunakan HTTP POST.
- **Format data JSON:** Data barcode dikirimkan dalam format JSON, yang mempermudah integrasi dengan berbagai sistem backend.

## **Persyaratan**

Sebelum memulai, pastikan Anda sudah memiliki perangkat dan alat berikut:
- **ESP32** (misalnya, ESP32 DevKit) sebagai mikrokontroler utama.
- **Pemindai Barcode GM65** yang terhubung dengan ESP32 menggunakan UART.
- **Akses WiFi** untuk menghubungkan ESP32 ke jaringan.
- **API Endpoint** untuk menerima data barcode (contohnya: `https://iot.sindangraja.com/api/cart/add`).

## **Pemasangan dan Pengaturan**

1. **Instalasi Library:**
   - Pastikan Anda sudah menginstal library berikut di Arduino IDE:
     - `WiFi.h` untuk mengatur koneksi WiFi.
     - `HTTPClient.h` untuk melakukan permintaan HTTP POST.

2. **Pengaturan WiFi:**
   - Ubah `WIFI_SSID` dan `WIFI_PASS` dengan nama dan password WiFi yang digunakan.

3. **Pengaturan API URL:**
   - Sesuaikan `API_URL` dengan URL endpoint API yang akan menerima data barcode.

4. **Pengaturan Pemindai Barcode:**
   - Pastikan pemindai barcode GM65 terhubung dengan ESP32 menggunakan pin yang sesuai di kode (RX 34 dan TX 32).

## **Cara Kerja**

1. **WiFi Connection:**
   - ESP32 menghubungkan diri dengan jaringan WiFi dan menunggu perintah untuk mengirim data ke API.

2. **Pembacaan Barcode:**
   - Pemindai GM65 membaca barcode dan mengirimkan data tersebut ke ESP32 melalui UART. Data disimpan dalam buffer hingga selesai.

3. **API Request:**
   - Setelah barcode terbaca, data tersebut akan dikirim ke server API menggunakan HTTP POST dalam format JSON yang berisi `device_id` dan `barcode`.

4. **Timeout:**
   - Jika dalam waktu lebih dari 60 detik tidak ada input barcode, data yang ada di buffer akan tetap dikirim ke API.

## **Struktur Kode:**

### 1. **WiFi Setup:**
   Kode ini menghubungkan ESP32 ke jaringan WiFi yang telah dikonfigurasi sebelumnya.

### 2. **GM65 UART Setup:**
   Kode ini mengatur komunikasi serial antara ESP32 dan pemindai barcode GM65 untuk membaca data barcode.

### 3. **Kirim Data ke API:**
   Data barcode yang dibaca dikirimkan ke API endpoint yang sudah ditentukan menggunakan HTTP POST.

### 4. **Proses Barcode:**
   Ketika barcode terbaca, kode ini akan memproses dan mengirimkan data tersebut ke API untuk diproses lebih lanjut.

## **Pengembangan Selanjutnya:**
- Menambahkan fitur autentikasi API untuk meningkatkan keamanan pengiriman data.
- Membuat antarmuka pengguna (UI) untuk menampilkan status pemindaian barcode dan hasil pengiriman data.
- Mengoptimalkan pengiriman data untuk mendukung pengiriman batch barcode atau pemindaian lebih dari satu barcode sekaligus.

## **Lisensi**

Proyek ini dilisensikan di bawah [MIT License](LICENSE).


Jika barcode berhasil dibaca dan data berhasil dikirim ke server, Anda akan melihat output di Serial Monitor seperti berikut:

