#ifndef CLASS_BMP_H
#define CLASS_BMP_H

#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <cstdint>

#pragma pack(push, 1)
struct FileHeader
{
    uint16_t file_signature{0x4D42};
    uint32_t total_file_size{0};
    uint16_t reserved_field1{0};
    uint16_t reserved_field2{0};
    uint32_t pixel_data_offset{0};
};

struct ImageInfoHeader
{
    uint32_t header_size{0};
    int32_t image_width{0};
    int32_t image_height{0};
    uint16_t color_planes{1};
    uint16_t bits_per_pixel{0};
    uint32_t compression_type{0};
    uint32_t raw_image_size{0};
    int32_t horizontal_resolution{0};
    int32_t vertical_resolution{0};
    uint32_t color_palette_count{0};
    uint32_t important_colors{0};
};

struct ColorHeader
{
    uint32_t red_bitmask{0x00ff0000};
    uint32_t blue_bitmask{0x000000ff};
    uint32_t green_bitmask{0x0000ff00};
    uint32_t alpha_bitmask{0xff000000};
    uint32_t color_space_signature{0x73524742};
    uint32_t reserved_fields[16]{0};
};
#pragma pack(pop)

class ClassBMP
{
public:
    FileHeader file_header;
    ImageInfoHeader image_info;
    ColorHeader color_info;
    std::vector<uint8_t> pixel_data;

    ClassBMP(const char* file_path); 
    void RotateClockwise90();         
    void RotateCounterClockwise90();
    void ApplyGaussianBlur();

    void SaveToFile(const char* file_path);
};

#endif
