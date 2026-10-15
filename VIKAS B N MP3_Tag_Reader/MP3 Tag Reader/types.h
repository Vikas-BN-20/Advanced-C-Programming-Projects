#ifndef TYPES_H
#define TYPES_H

int get_frame_size(unsigned char *size_bytes); // convert a frames 4 size bytes into a usable int

void put_frame_size(int size, unsigned char *size_bytes); // fills a 4 byte buffer from an int size for writing

#endif