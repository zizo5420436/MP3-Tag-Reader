# MP3 Tag Reader  

## Overview  
MP3 Tag Reader is a simple and efficient tool designed to extract and display metadata from MP3 files. It reads **ID3 tags** to provide details such as **Title, Artist, Album, Track Number**, and more. This project is useful for individuals who want to **view and manage MP3 tag data** efficiently. Future enhancements could include **tag editing capabilities** to modify metadata.  

## Understanding ID3 Tags  
ID3 tags allow metadata to be embedded within an MP3 file, helping organize and display song details in media players. The two main versions are:  
- **ID3v1** – A fixed 128-byte structure at the end of an MP3 file, identified by the "TAG" signature.  
- **ID3v2** – A flexible and structured format typically found at the beginning of an MP3 file, supporting more metadata fields.  

## Key Features  
✅ Supports **ID3v2.3** tag format. ✅ Detects and displays **ID3 version** used in the file. ✅ Extracts and presents **all available metadata fields**. ✅ Provides a **help menu (--help option)** for user guidance. ✅ Displays **error messages** if an ID3 tag is not found.  

## Technical Details  
- **ID3v1** uses **128 bytes** for metadata storage.  
- **ID3v2** consists of a **header** and multiple **frames**, each holding a piece of metadata.  
- The tool reads common ID3v2 fields such as: **TIT2 (Title), TALB (Album), TPE1 (Artist), TYER (Year).**
  

