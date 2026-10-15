/* 
NAME : VIKAS B N 
DATE : 21/09/2026
PROJECT : MP3 TAG READER AND EDITOR
DESCRIPTION : The MP3 Tag Reader is a simple C based application.
              It is designed to read and display metadata embedded in MP3 audio files, such as song title, artist, album, genre, and other tag information.
*/

#include <stdio.h>
#include <string.h>
#include "types.h"
#include "view.h"
#include "edit.h"

void show_help()
{
    printf("\n+----------------------------------------------------------------------------------+");
    printf("\n|                      MP3 Tag Reader & Editor - Usage :                           |");
    printf("\n+----------------------------------------------------------------------------------+\n");
    printf("|          ./a.out -h                                      Show this help          |\n");
    printf("|          ./a.out -v song.mp3                             View metadata           |\n");
    printf("|          ./a.out -e song.mp3 -t New Title                Edit title              |\n");
    printf("|          ./a.out -e song.mp3 -A New Artist               Edit artist             |\n");
    printf("|          ./a.out -e song.mp3 -a New Album                Edit album              |\n");
    printf("|          ./a.out -e song.mp3 -y 2026                     Edit year               |\n");
    printf("|          ./a.out -e song.mp3 -c Rock                     Edit genre              |\n");
    printf("|          ./a.out -e song.mp3 -C New Comment              Edit comme              |\n");
    printf("+----------------------------------------------------------------------------------+\n");
    printf("\n");
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Error : No arguments given.\nUse --> ./a.out -h command for help.\n");
        return 0;
    }
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-help") == 0)
    {
        show_help();
    }
    else if (strcmp(argv[1], "-v") == 0)
    {
        if (argc < 3 || strstr(argv[2], ".mp3") == NULL)
        {
            printf("Error : Please give a valid mp3 file name\n");
            return 0;
        }
        view_mp3_tags(argv[2]);
    }
    else if (strcmp(argv[1], "-e") == 0)
    {
        // excepts : -e song.mp3 -t New Title (words after option)
        if (argc < 5 || strstr(argv[2], ".mp3") == NULL)
        {
            printf("Error : Usage -> ./a.out -e song.mp3 -t New Title\n");
            return 0;
        }

        char frame_id[5];
        if (map_option_to_id(argv[3], frame_id) == 0)
        {
            printf("Error : Invalid edit option %s\n", argv[3]);
            return 0;
        }

        // combine remaining words into string (so spaces work)
        char new_text[200] = "";
        for (int i = 4; i < argc; i++)
        {
            strcat(new_text, argv[i]);
            if (i != argc - 1)
                strcat(new_text, " ");
        }
        edit_mp3_tag(argv[2], frame_id, new_text);
    }
    else
    {
        printf("Error : Invalid option. Use -h for help.\n");
    }

    return 0;
}