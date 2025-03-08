#include<stdio.h>
#include"view.h"
#include"type.h"
#include<string.h>
#include<stdlib.h>

/* Function Definitions */

/* Check which Operation is to be Performed
 * Input: Command Line Arguments
 * Output: Operation to be Performed
 * Return Value: p_view, p_edit, p_help or p_unsupported on Invalid options provided by User
 */

OperationType check_operation_type(int argc,char *argv[])
{
    if (argv[1]==NULL)
    {
        return p_unsupported;
    }
    
    
    if(strcmp(argv[1], "-v") == 0)
    {
        return p_view;
    }
    else if(strcmp(argv[1], "-e") == 0)
    {
        
        return p_edit;
    }
    else if(strcmp(argv[1], "-h") == 0)
    {
        return p_help;
    }
    else
    {
        return p_unsupported;
    }
}
//validate arguments
Status read_and_validate_mp3_file(int argc,char *argv[], Mp3Tag *mp3_tag)
{
    if (argc < 3) 
    {
        printf("Usage: ./a.out -v <mp3_filename>\n");
        return e_failure;
    }
    if(argv[2] == NULL)
    {
        return e_failure;
    }
    char *mp3=strrchr(argv[2],'.');
    if(!mp3 || strcmp(mp3,".mp3"))
    {
        return e_failure;
    }
    //open file
    mp3_tag->fptr_mp3 = fopen(argv[2], "rb");
    if(mp3_tag->fptr_mp3 == NULL)
    {
        printf("File not opened\n");
        return e_failure;
    }
    //printf("File opened successfully\n");
    return e_success;
}
//view mp3 tag
Status view_mp3_tag(Mp3Tag *mp3_tag)
{
    //skip 10 bytes
    fseek(mp3_tag->fptr_mp3, 10, SEEK_SET);
    // printf("Reading the MP3 file\n");
    /*Title*/
    fread(mp3_tag->frame_id, 4, 1, mp3_tag->fptr_mp3);
    mp3_tag->frame_id[4] = '\0';
    if(strcmp(mp3_tag->frame_id, "TIT2") != 0)
    {
        return e_failure;
    }
    //printf("Frame ID: %s\n", mp3_tag->frame_id);
    // Read Title Size (4 bytes) (convert from sync-safe integer)
    mp3_tag->title_size = get_data_size(mp3_tag->fptr_mp3);

    //printf("Title Size: %d\n", mp3_tag->title_size);
    //skip flag 2 bytes
    fseek(mp3_tag->fptr_mp3, 3, SEEK_CUR);
   // printf("File position before reading title: %ld\n", ftell(mp3_tag->fptr_mp3));
    //allocate memory for title
    mp3_tag->title = (char *)malloc(mp3_tag->title_size+1);
        if (mp3_tag->title == NULL) {
        printf("Memory allocation failed\n");
        return e_failure;
    }
    //read title
    if(fread(mp3_tag->title, mp3_tag->title_size, 1, mp3_tag->fptr_mp3) == 0)
    {
        printf("Error in reading title\n");
        return e_failure;
    }
    //printf("File position before reading title: %ld\n", ftell(mp3_tag->fptr_mp3));
    mp3_tag->title[mp3_tag->title_size] = '\0';

    //printf("Title: %s\n", mp3_tag->title);
    //printf("size of title : %ld\n",sizeof(mp3_tag->title));
    /*Artist*/
    //read artist frame id
    fread(mp3_tag->frame_id, 4, 1, mp3_tag->fptr_mp3);
    mp3_tag->frame_id[4] = '\0';
    //printf("Frame ID: %s\n", mp3_tag->frame_id);
    if(strcmp(mp3_tag->frame_id, "TPE1") != 0)
    {
        return e_failure;
    }
    // Read Artist Size (4 bytes) (convert from sync-safe integer)
    mp3_tag->artist_size = get_data_size(mp3_tag->fptr_mp3);
    //printf("artist size: %d\n", mp3_tag->artist_size);
    //skip flag 2 bytes
    fseek(mp3_tag->fptr_mp3, 3, SEEK_CUR);
    //allocate memory for artist
    mp3_tag->artist = (char *)malloc(mp3_tag->artist_size+1);
    //read artist
    fread(mp3_tag->artist, mp3_tag->artist_size, 1, mp3_tag->fptr_mp3);
    mp3_tag->artist[mp3_tag->artist_size] = '\0';
   // printf("Artist: %s\n", mp3_tag->artist);

    /*Album*/
    //read album frame id
    fread(mp3_tag->frame_id, 4, 1, mp3_tag->fptr_mp3);
    mp3_tag->frame_id[4] = '\0';
    //printf("Frame ID: %s\n", mp3_tag->frame_id);
    if(strcmp(mp3_tag->frame_id, "TALB") != 0)
    {
        return e_failure;
    }
    // Read Album Size (4 bytes) (convert from sync-safe integer)
    mp3_tag->album_size = get_data_size(mp3_tag->fptr_mp3);
    //skip flag 2 bytes
    fseek(mp3_tag->fptr_mp3, 3, SEEK_CUR);
    //allocate memory for album
    mp3_tag->album = (char *)malloc(mp3_tag->album_size+1);
    //read album
    fread(mp3_tag->album, mp3_tag->album_size, 1, mp3_tag->fptr_mp3);
    mp3_tag->album[mp3_tag->album_size] = '\0';
   // printf("Album: %s\n", mp3_tag->album);

    /*Year*/
    //read year frame id
    fread(mp3_tag->frame_id, 4, 1, mp3_tag->fptr_mp3);
    mp3_tag->frame_id[4] = '\0';
   // printf("Frame ID: %s\n", mp3_tag->frame_id);
    if(strcmp(mp3_tag->frame_id, "TYER") != 0)
    {
        return e_failure;
    }
    // Read Year Size (4 bytes) (convert from sync-safe integer)
    mp3_tag->year_size = get_data_size(mp3_tag->fptr_mp3);
    //skip flag 2 bytes
    fseek(mp3_tag->fptr_mp3, 3, SEEK_CUR);
    //allocate memory for year
    mp3_tag->year = (char *)malloc(mp3_tag->year_size+1);
    //read year
    fread(mp3_tag->year, mp3_tag->year_size, 1, mp3_tag->fptr_mp3);
    mp3_tag->year[mp3_tag->year_size] = '\0';
    //printf("Year: %s\n", mp3_tag->year);


    /*Genre*/
    //read genre frame id
    fread(mp3_tag->frame_id, 4, 1, mp3_tag->fptr_mp3);
    mp3_tag->frame_id[4] = '\0';
   // printf("Frame ID: %s\n", mp3_tag->frame_id);
    if(strcmp(mp3_tag->frame_id, "TCON") != 0)
    {
        return e_failure;
    }
    // Read Genre Size (4 bytes) (convert from sync-safe integer)
    mp3_tag->genre_size = get_data_size(mp3_tag->fptr_mp3);
    //skip flag 2 bytes
    fseek(mp3_tag->fptr_mp3, 3, SEEK_CUR);
    //allocate memory for genre 
    mp3_tag->genre = (char *)malloc(mp3_tag->genre_size+1);
    //read genre
    fread(mp3_tag->genre, mp3_tag->genre_size, 1, mp3_tag->fptr_mp3);
    mp3_tag->genre[mp3_tag->genre_size] = '\0';
    //printf("Genre: %s\n", mp3_tag->genre);

    /*Comment*/
    //read comment frame id
    fread(mp3_tag->frame_id, 4, 1, mp3_tag->fptr_mp3);
    mp3_tag->frame_id[4] = '\0';
    //printf("Frame ID: %s\n", mp3_tag->frame_id);
    if(strcmp(mp3_tag->frame_id, "COMM") != 0)
    {
        return e_failure;
    }
    // Read Comment Size (4 bytes) (convert from sync-safe integer)
    mp3_tag->comment_size = get_data_size(mp3_tag->fptr_mp3);
    //skip flag 2 bytes
    fseek(mp3_tag->fptr_mp3, 3, SEEK_CUR);
    //allocate memory for comment
    mp3_tag->comment = (char *)malloc(mp3_tag->comment_size+1);
    //read comment
    fread(mp3_tag->comment, mp3_tag->comment_size, 1, mp3_tag->fptr_mp3);
    mp3_tag->comment[mp3_tag->comment_size] = '\0';
   // printf("Comment: %s\n", mp3_tag->comment);

    

    return e_success;
 
}
//Display
void print_centered(const char *text, int width) {
    int len = strlen(text);
    if (len >= width) {
        printf(" %.*s ", width, text);  // Truncate if text is too long
        return;
    }
    int padding = (width - len) / 2;
    int extra_space = (width - len) % 2; // Handle odd width cases
    printf("%*s%s%*s", padding, "", text, padding + extra_space, "");
}

// Function to display MP3 tag information in a formatted table
Status display_data(Mp3Tag *mp3_tag) {
    printf("+------------+---------------------------------------------------+\n");
    printf("|"); print_centered("Tag", 12); printf("|"); print_centered("Information", 51); printf("|\n");
    printf("+------------+---------------------------------------------------+\n");

    printf("|"); print_centered("Title", 12); printf("|"); print_centered(mp3_tag->title, 51); printf("|\n");
    printf("|"); print_centered("Artist", 12); printf("|"); print_centered(mp3_tag->artist, 51); printf("|\n");
    printf("|"); print_centered("Album", 12); printf("|"); print_centered(mp3_tag->album, 51); printf("|\n");
    printf("|"); print_centered("Year", 12); printf("|"); print_centered(mp3_tag->year, 51); printf("|\n");
    printf("|"); print_centered("Comment", 12); printf("|"); print_centered(mp3_tag->comment, 51); printf("|\n");
    printf("|"); print_centered("Genre", 12); printf("|"); print_centered(mp3_tag->genre, 51); printf("|\n");

    printf("+------------+---------------------------------------------------+\n");

    return e_success;
}
//get data size
uint get_data_size(FILE *fptr_mp3)
{
    
    unsigned char data_size[4];  
    if (fread(data_size, 1, 4, fptr_mp3) != 4) 
    {
        printf("Error reading size bytes\n");
        return 0;
    }
   // printf("Size Bytes: %02X %02X %02X %02X\n",
          // data_size[0], data_size[1], data_size[2], data_size[3]);

    uint size = ((uint)data_size[0] << 21) | 
                ((uint)data_size[1] << 14) |
                ((uint)data_size[2] << 7)  | 
                ((uint)data_size[3]);

                //printf("Size: %d\n", size-1);
    return size-1;

}
    