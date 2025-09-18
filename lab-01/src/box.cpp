#include "box.h"

int box_capacity(int length, int width, int height) {
    int length_in_inches = length * 12;
    int width_in_inches = width * 12;
    int height_in_inches = height * 12;

    int boxes_along_length = length_in_inches / 16;
    int boxes_along_width = width_in_inches / 16;
    int boxes_along_height = height_in_inches / 16;

    return boxes_along_length * boxes_along_width * boxes_along_height;
}