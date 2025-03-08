#include<stdio.h>
#ifndef view_h
#define view_h
#include"type.h" // User defined types

/*
 * Structure to store information required for storing the various MP3 Tag details
 * Information about Output data is also stored
 */
typedef struct _mp3_tag
{
    FILE *fptr_mp3; // File Pointer to MP3 File
    char frame_id[5]; // Frame ID
    uint title_size; // Title Size
    char *title; // Title
    uint artist_size; // Artist Size
    char *artist; // Artist
    uint album_size; // Album Size
    char *album; // Album
    uint year_size; // Year Size
    char *year; // Year
    uint comment_size; // Comment Size
    char *comment; // Comment
    uint genre_size; // Genre Size
    char *genre; // Genre
} Mp3Tag;


/*
 * Function to display the main menu
 */

//check operation type
OperationType check_operation_type(int argc,char *argv[]);

//validate arguments
Status read_and_validate_mp3_file(int argc,char *argv[], Mp3Tag *mp3_tag);

//view mp3 tag
Status view_mp3_tag(Mp3Tag *mp3_tag);
//get data size
uint get_data_size(FILE *fptr_mp3);

//Display
Status display_data(Mp3Tag *mp3_tag);

void print_centered(const char *text, int width);


#endif