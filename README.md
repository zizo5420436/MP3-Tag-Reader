# 🎵 MP3 Tag Reader

## 📌 Overview  
The **MP3 Tag Reader** is a lightweight and efficient tool built in **C** to extract and display metadata from MP3 files. It reads **ID3 tags** to present details such as **Title**, **Artist**, **Album**, and **Track Number**. Ideal for developers or music enthusiasts who want to **analyze or manage MP3 metadata**.

---

## 🧠 Understanding ID3 Tags  

ID3 tags are metadata containers within MP3 files that help store song information. They are used by media players to show song details like title and artist.

There are two main versions:

- 🎧 **ID3v1**:  
  - Fixed size (128 bytes)  
  - Found at the **end** of the MP3 file  
  - Identified by the `"TAG"` signature  

- 🎧 **ID3v2**:  
  - Located at the **beginning** of the MP3 file  
  - Supports multiple metadata fields  
  - Uses flexible frame-based storage  
  - This project supports **ID3v2.3**  

---

## ⚙️ Key Features

- ✅ Supports **ID3v2.3** tag format  
- ✅ Automatically detects and displays **ID3 version**  
- ✅ Extracts fields like **Title (TIT2), Album (TALB), Artist (TPE1), Year (TYER)**  
- ✅ User guidance with `--help` option  
- ✅ Shows **error messages** if no tag is present or format is unsupported  

---

## 🛠 Technical Details

- **ID3v1**:  
  - Last 128 bytes of the MP3 file  
  - Simple structure for basic metadata  

- **ID3v2**:  
  - Starts with a 10-byte header  
  - Followed by **frames**, each containing a specific tag field  
  - Example frames:  
    - `TIT2` → Title  
    - `TALB` → Album  
    - `TPE1` → Artist  
    - `TYER` → Year  

---

## 📥 How to Compile

```bash
gcc mp3_tag_reader.c -o mp3tag
```

---

## ▶️ How to Run

```bash
./mp3tag sample.mp3
```

Use `--help` for usage instructions:

```bash
./mp3tag --help
```

---

## 🧪 Sample Output

```
MP3 Tag Reader - ID3 Metadata

Title      : Bohemian Rhapsody
Artist     : Queen
Album      : A Night at the Opera
Year       : 1975
Track No.  : 01
Genre      : Rock
```

---
