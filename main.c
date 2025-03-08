#include<stdio.h>
#include"type.h"
#include "edit.h"
#include"view.h"
#include<string.h>


int main(int argc, char *argv[])
{
    Mp3Tag mp3_tag;
    Mp3Tag_edit mp3_tag_edit;


    OperationType operation = check_operation_type(argc, argv);
    if(operation == p_unsupported)
    {
        printf("Invalid Option\n");
        printf("Usage: %s <option> <filename>\n", argv[0]);
        return 0;
    }else if(operation == p_help)
    {
        printf ("INFO: Help Menu for Tag Reader and Editor:\n");
        printf ("INFO: For Viewing the Tags -> ./mp3_tag_reader -v <file_name.mp3>\n");
        printf ("INFO: For Editing the Tags -> ./mp3_tag_reader -e <modifier> \"New_Value\" <file_name.mp3>\n");
        printf ("INFO: Modifier Functions:\n");
        printf ("-t\tModify Title Tag\n-A\tModify Artist Tag\n-a\tModify Album Tag\n-y\tModify Year Tag\n-G\tModify Content Type Tag\n-c\tModify Comments Tag\n");
        return 0;
    }else if(operation == p_view)
    {
        
        if(read_and_validate_mp3_file(argc, argv, &mp3_tag) == e_failure)
        {
            printf("Error in reading the MP3 file\n");
            return 0;
        }
        if(view_mp3_tag(&mp3_tag) == e_failure)
        {
            printf("Error in viewing the MP3 file\n");
            return 0;
        }
        if(display_data(&mp3_tag) == e_failure)
        {
            printf("Error in displaying the MP3 file\n");
            return 0;
        }

    }else if(operation == p_edit)
    {
        
        if(edit_info(argc, argv, &mp3_tag_edit) == e_failure)
        {
            printf("Error in reading the MP3 file\n");
            return 0;
        }
        if(edit_mp3_tag(&mp3_tag_edit)== e_failure)
        {
            printf("Error in editing the MP3 file\n");
            return 0;
        }
        if(update_frame_content(&mp3_tag_edit)==e_failure)
        {
            printf("Error in update the MP3 file\n");
            return 0;
        }
        //edit_mp3_tag(&tag_info);
    }else
    {
        printf("Invalid Option\n");
        printf("Usage: %s <option> <filename>\n", argv[0]);
    }

}