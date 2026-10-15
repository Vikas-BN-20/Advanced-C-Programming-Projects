#include <stdio.h>
#include <string.h>
#include "types.h"
#include "view.h"

void view_mp3_tags(char *file_name)
{
    FILE *fp = fopen(file_name, "rb");

    if (fp == NULL)
    {
        printf("Error : could not open %s\n", file_name);
        return;
    }

    fseek(fp, 10, SEEK_SET); // move past the 10 byte ID3 header

    char frame_id[5];
    unsigned char size_bytes[4];
    char text[100];

    printf("\n+----------------------------------------------------------------------------------+");
    printf("\n|                                MP3 AUDIO DETAILS                                 |");
    printf("\n+----------------------------------------------------------------------------------+\n");

    for (int i = 0; i < 6; i++)
    {
        if (fread(frame_id, 1, 4, fp) != 4)
            break;
        frame_id[4] = '\0';

        fread(size_bytes, 1, 4, fp);
        int size = get_frame_size(size_bytes);

        fseek(fp, 2, SEEK_CUR); // skip flags
        fseek(fp, 1, SEEK_CUR); // skip encoding byte

        int read_len = size - 1;
        if (read_len > 99)
            read_len = 99;
        if (read_len < 0)
            read_len = 0;

        fread(text, 1, read_len, fp);
        text[read_len] = '\0';

        if (strcmp(frame_id, "TIT2") == 0)
            printf(" Title   : %s\n", text);
        else if (strcmp(frame_id, "TPE1") == 0)
            printf(" Artist  : %s\n", text);
        else if (strcmp(frame_id, "TALB") == 0)
            printf(" Album   : %s\n", text);
        else if (strcmp(frame_id, "TYER") == 0)
            printf(" Year    : %s\n", text);
        else if (strcmp(frame_id, "TCON") == 0)
            printf(" Genre   : %s\n", text);
        else if (strcmp(frame_id, "COMM") == 0)
            printf(" Comment : %s\n", text);
    
    }

    fclose(fp);

    printf("+----------------------------------------------------------------------------------+\n");

}