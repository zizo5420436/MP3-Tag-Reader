#include<stdio.h>
#ifndef edit_h
#define edit_h
#include"type.h" // User defined types

/*
 * Structure to store information required for storing the Updated Fram Content details
 * Information abouth the Source and Temporary MP3 files
 */

typedef struct _mp3_tag_edit
{
    FILE* fptr_mp3; // File Pointer to MP3 File
    FILE* fptr_temp; // Temporary File Pointer
    char* new_value; // New Value
    char* modifier; // Modifier

} Mp3Tag_edit;

/*
 * Function to edit the MP3 Tag
 */
Status edit_info(int argc,char *argv[], Mp3Tag_edit *mp3_tag_edit);

//edit mp3 tag

Status edit_mp3_tag(Mp3Tag_edit *mp3_tag_edit);

//get data size
void get_size_for_edit(Mp3Tag_edit *mp3_tag_edit);

//update frame content
Status update_frame_content(Mp3Tag_edit *mp3_tag_edit);

//read data size for copying
uint get_data_size_copy(const char *buffer_size);
//copy remaining data

Status copy_remaining_content(Mp3Tag_edit *mp3_tag_edit);




#endif

