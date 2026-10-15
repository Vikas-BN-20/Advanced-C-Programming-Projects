#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "edit.h"

int get_frame_size(unsigned char *size_bytes)
{
    return (size_bytes[0] << 24 | size_bytes[0] << 16) | (size_bytes[0] << 8) | size_bytes[3];
}

void put_frame_size(int size, unsigned char *size_bytes)
{
    size_bytes[0] = (size >> 24) & 0xFF;
    size_bytes[1] = (size >> 16) & 0xFF;
    size_bytes[2] = (size >> 8) & 0xFF;
    size_bytes[3] = size & 0xFF;
}

int map_option_to_id(char *option, char *frame_id_out)
{
    if (strcmp(option, "-t") == 0)
    {
        strcpy(frame_id_out, "TIT2");
        return 1;
    }
    if (strcmp(option, "-A") == 0)
    {
        strcpy(frame_id_out, "TPE1");
        return 1;
    }
    if (strcmp(option, "-a") == 0)
    {
        strcpy(frame_id_out, "TALB");
        return 1;
    }
    if (strcmp(option, "-y") == 0)
    {
        strcpy(frame_id_out, "TYER");
        return 1;
    }
    if (strcmp(option, "-c") == 0)
    {
        strcpy(frame_id_out, "TCON");
        return 1;
    }
    if (strcmp(option, "-C") == 0)
    {
        strcpy(frame_id_out, "COMM");
        return 1;
    }

    return 0;
}

void edit_mp3_tag(char *file_name, char *selected_id, char *new_text)
{
    FILE *fp = fopen(file_name, "rb");
    if (fp == NULL)
    {
        printf("Error : could not open %s\n", file_name);
        return;
    }

    FILE *temp = fopen("temp.mp3", "wb");
    if (temp == NULL)
    {
        printf("Error : could not create temp.mp3\n");
        fclose(fp);
        return;
    }
    
    // copy 10 byte header as it is
    char header[10]; 
    fread(header, 1, 10, fp);
    fwrite(header, 1, 10, temp);

    char frame_id[5];
    unsigned char size_bytes[4];
    unsigned char flags[2];

    for (int i = 0; i < 6; i++)
    {
        if (fread(frame_id, 1, 4, fp) != 4)
            break;
        frame_id[4] = '\0';

        fread(size_bytes, 1, 4, fp);
        int old_size = get_frame_size(size_bytes);

        fread(flags, 1, 2, fp);

        if (strcmp(frame_id, selected_id) == 0)
        {
            fwrite(frame_id, 1, 4, temp); // write frame id

            int new_size = strlen(new_text) + 1; // new size = encoding byte + text length
            unsigned char new_size_bytes[4];
            put_frame_size(new_size, new_size_bytes);
            fwrite(new_size_bytes, 1, 4, temp);

            fwrite(flags, 1, 2, temp); // write same flags

            char encoding = 0; // encoding byte
            fwrite(&encoding, 1, 1, temp);
            fwrite(new_text, 1, strlen(new_text), temp);

            fseek(fp, old_size, SEEK_CUR);
        }
        else
        {
            fwrite(frame_id, 1, 4, temp); // copy unchanged frame using malloc
            fwrite(size_bytes, 1, 4, temp);
            fwrite(flags, 1, 2, temp);

            if (old_size > 0)
            {
                char *buffer = (char *)malloc(old_size);
                fread(buffer, 1, old_size, fp);
                fwrite(buffer, 1, old_size, temp);
                free(buffer);
            }
        }
    }

    // copy remaining bytes(rest of metadata + audio data)

    char ch;
    while (fread(&ch, 1, 1, fp) == 1)
    {
        fwrite(&ch, 1, 1, temp);
    }

    fclose(fp);
    fclose(temp);

    // replace original file with the updated temp file
    remove(file_name);
    rename("temp.mp3", file_name);

    printf("Success : %s Updated in %s\n", selected_id, file_name);
}