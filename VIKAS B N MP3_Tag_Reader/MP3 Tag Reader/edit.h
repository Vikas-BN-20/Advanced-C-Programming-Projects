#ifndef EDIT_H
#define EDIT_H

int map_option_to_id(char *option, char *frame_id_out); // maps user option(-t , -A, -a, -y, -c, -C) to a frame ID

void edit_mp3_tag(char *file_name, char *selected_id, char *new_text); // edits one tag in the mp3

#endif