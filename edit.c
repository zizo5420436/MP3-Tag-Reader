#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "edit.h"
#include "type.h"


char update_frame_id[5]; // Initialize Frame ID
unsigned char sync_size[4]; 

Status edit_info(int argc,char *argv[], Mp3Tag_edit *mp3_tag_edit)
{
    if (argc < 5) 
    {
        printf("Usage: ./a.out -e <modifier> \"New_Value\" <mp3_filename>\n");
        return e_failure;
    }
    //modifier = /
   
    mp3_tag_edit->modifier = argv[2];  // Modifier (e.g., "title", "artist", etc.)
    mp3_tag_edit->new_value = argv[3]; // New value to be updated

    char *dot = strrchr(argv[4], '.'); // Find the last occurrence of '.'
    
    if (!dot || strcmp(dot, ".mp3") != 0) { // Check for NULL and compare extension
        return e_failure;
    }

    //open src file 
    mp3_tag_edit->fptr_mp3 = fopen(argv[4],"rb");
    
    return e_success;
    
}
//edit mp3 tag
Status edit_mp3_tag(Mp3Tag_edit *mp3_tag_edit)
{
    //open file
    mp3_tag_edit->fptr_temp = fopen("yaariyan.mp3", "wb");
    
    if (mp3_tag_edit->fptr_mp3 == NULL) {
        perror("Error creating test file");
        return e_failure;
    }
   // mp3_tag_edit->fptr_temp = (char*)malloc(1024);
   
        

        // Copy first 10 bytes from source to temp file
        char buffer[10];
        
        fread(buffer, 10, 1, mp3_tag_edit->fptr_mp3);
        
        fwrite(buffer, 10, 1, mp3_tag_edit->fptr_temp);
        
        if (strcmp(mp3_tag_edit->modifier, "-t") == 0) {
            strcpy(update_frame_id, "TIT2");
        } else if (strcmp(mp3_tag_edit->modifier, "-A") == 0) {
            strcpy(update_frame_id, "TPE1");
        } else if (strcmp(mp3_tag_edit->modifier, "-a") == 0) {
            strcpy(update_frame_id, "TALB");
        } else if (strcmp(mp3_tag_edit->modifier, "-y") == 0) {
            strcpy(update_frame_id, "TYER");
        } else if (strcmp(mp3_tag_edit->modifier, "-G") == 0) {
            strcpy(update_frame_id, "TCON");
        } else if (strcmp(mp3_tag_edit->modifier, "-c") == 0) {
            strcpy(update_frame_id, "COMM");
        } else {
            printf("Invalid Modifier\n");
            return e_failure;
        }
        // copy the updated frame content to temp file  
        //printf("Saved\n");
        return e_success;

}

//update frame content
Status update_frame_content(Mp3Tag_edit *mp3_tag_edit)
{
    //find where the frame content starts and encode the new value
   // fseek(mp3_tag_edit->fptr_mp3, 0, SEEK_SET);
    //fseek(mp3_tag_edit->fptr_temp, 0, SEEK_SET);
    
    int content_size = 0;
    char buffer_title[5];
    char buffer_size[4];
    char buffer_flag[2];
    unsigned char *buffer_content = NULL;
    //printf("%ld is",ftell(mp3_tag_edit->fptr_mp3));
    while(!feof(mp3_tag_edit->fptr_mp3))
    {
        //printf("starting\n");
        fread(buffer_title, 4, 1, mp3_tag_edit->fptr_mp3);
        buffer_title[4] = '\0';
        if(strcmp(buffer_title, update_frame_id) == 0)
        {
            fwrite(buffer_title, 4, 1, mp3_tag_edit->fptr_temp);
            get_size_for_edit(mp3_tag_edit);
            //write the size of the new content
            //printf("Synchsafe Size Bytes: %02X %02X %02X %02X\n", 
           // sync_size[0], sync_size[1], sync_size[2], sync_size[3]);
            fwrite(sync_size, 4, 1, mp3_tag_edit->fptr_temp); 
            //skip size of the old content
            fread(buffer_size,4,1,mp3_tag_edit->fptr_mp3);
            //size finding
            content_size=get_data_size_copy(buffer_size);
           // printf("content size is %d \n",content_size);
            //skip flag 2 bytes and make to 0
            fwrite("\0\0", 3, 1, mp3_tag_edit->fptr_temp);
            //skip the old content
            fseek(mp3_tag_edit->fptr_mp3, 3, SEEK_CUR);
            //write the new content
            fwrite(mp3_tag_edit->new_value, strlen(mp3_tag_edit->new_value), 1, mp3_tag_edit->fptr_temp);
            //skip pointer of original file upto old content size
            fseek(mp3_tag_edit->fptr_mp3,content_size,SEEK_CUR);
            //copy the rest of the file
            if(copy_remaining_content(mp3_tag_edit) == e_failure)
            {
                return e_failure;
            }

            break;
  
        }else
        {
            fwrite(buffer_title, 4, 1, mp3_tag_edit->fptr_temp);
            fread(buffer_size, 4, 1, mp3_tag_edit->fptr_mp3);
            fwrite(buffer_size, 4, 1, mp3_tag_edit->fptr_temp);
           // printf("buffer size : %s\n",buffer_size);
            //read size of content
             content_size=get_data_size_copy(buffer_size);
             if (content_size < 0 || content_size > 1000000) // Prevent huge allocations
             {
                 printf("Error: Invalid content size %X\n", content_size);
                 return e_failure;
             }
            //copy flag 3 bytes
            fread(buffer_flag, 3, 1, mp3_tag_edit->fptr_mp3);
            //write flag 3 bytes
            fwrite(buffer_flag, 3, 1, mp3_tag_edit->fptr_temp);
              // **Dynamically allocate buffer_content**
            buffer_content = (unsigned char *)malloc(content_size);
            //copy content
            fread(buffer_content, content_size, 1, mp3_tag_edit->fptr_mp3);
            //write content
            fwrite(buffer_content, content_size, 1, mp3_tag_edit->fptr_temp);
            free(buffer_content);
        }

    }
}
//get data size
void get_size_for_edit(Mp3Tag_edit *mp3_tag_edit) 
{
    int size = strlen(mp3_tag_edit->new_value)+1;
    
    // Convert to synchsafe integer
    sync_size[0] = (size >> 21) & 0x7F;
    sync_size[1] = (size >> 14) & 0x7F;
    sync_size[2] = (size >> 7)  & 0x7F;
    sync_size[3] = size & 0x7F;
    
    //printf("Synchsafe Size: %d %d %d %d\n", sync_size[0], sync_size[1], sync_size[2], sync_size[3]);
}
//get data size for copying 
uint get_data_size_copy(const char *buffer_size) {
    // Synchsafe integer decoding
    int size = 0;
    size = (unsigned char)buffer_size[0] << 21;
    size |= (unsigned char)buffer_size[1] << 14;
    size |= (unsigned char)buffer_size[2] << 7;
    size |= (unsigned char)buffer_size[3];

   
    return size-1;
}



//copy remaining data
Status copy_remaining_content(Mp3Tag_edit *mp3_tag_edit)
{
    char data;
    while (fread(&data, 1, 1, mp3_tag_edit->fptr_mp3) > 0)
    {
        fwrite(&data, 1, 1, mp3_tag_edit->fptr_temp);
    }
    return e_success;
}


