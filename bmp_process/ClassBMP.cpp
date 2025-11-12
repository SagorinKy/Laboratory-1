#include "ClassBMP.h"

ClassBMP::ClassBMP(const char* file_path)   
{

    std::ifstream input_stream(file_path, std::ios_base::binary);
    if (!input_stream)
    {
        throw std::runtime_error("Unable to open file!");
    }

    input_stream.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    if (file_header.file_signature != 0x4D42)
    {
        throw std::runtime_error("The file is not a BMP image!");
    }

    input_stream.read(reinterpret_cast<char*>(&image_info), sizeof(image_info));

    if (image_info.bits_per_pixel == 24)
    {
        input_stream.read(reinterpret_cast<char*>(&color_info), sizeof(color_info));
    }

    input_stream.seekg(file_header.pixel_data_offset, input_stream.beg);
    pixel_data.resize(image_info.raw_image_size);
    input_stream.read(reinterpret_cast<char*>(pixel_data.data()), pixel_data.size());
}


void ClassBMP::RotateClockwise90()
{
    int old_row_size = (image_info.image_width * (image_info.bits_per_pixel / 8) + 3) & ~3;
    int new_row_size = (image_info.image_height * (image_info.bits_per_pixel / 8) + 3) & ~3;

    std::vector<uint8_t> rotated_data(new_row_size * image_info.image_width);

    #pragma omp parallel for  
    for (int y = 0; y < image_info.image_height; ++y)
    {
        for (int x = 0; x < image_info.image_width; ++x)
        {
            int old_index = y * old_row_size + x * (image_info.bits_per_pixel / 8);
            int new_index = (image_info.image_width - x - 1) * new_row_size + y * (image_info.bits_per_pixel / 8);

            for (int channel = 0; channel < (image_info.bits_per_pixel / 8); ++channel)
            {
                rotated_data[new_index + channel] = pixel_data[old_index + channel];
            }
        }
    }

    std::swap(image_info.image_width, image_info.image_height);
    image_info.raw_image_size = rotated_data.size();
    file_header.total_file_size = file_header.pixel_data_offset + rotated_data.size();

    pixel_data = std::move(rotated_data);
}

void ClassBMP::RotateCounterClockwise90()
{
    int old_row_size = (image_info.image_width * (image_info.bits_per_pixel / 8) + 3) & ~3;
    int new_row_size = (image_info.image_height * (image_info.bits_per_pixel / 8) + 3) & ~3;

    std::vector<uint8_t> rotated_data(new_row_size * image_info.image_width);

    #pragma omp parallel for  
    for (int y = 0; y < image_info.image_height; ++y)
    {
        for (int x = 0; x < image_info.image_width; ++x)
        {
            int old_index = y * old_row_size + x * (image_info.bits_per_pixel / 8);
            int new_index = x * new_row_size + (image_info.image_height - y - 1) * (image_info.bits_per_pixel / 8);

            for (int channel = 0; channel < (image_info.bits_per_pixel / 8); ++channel)
            {
                rotated_data[new_index + channel] = pixel_data[old_index + channel];
            }
        }
    }

    std::swap(image_info.image_width, image_info.image_height);
    image_info.raw_image_size = rotated_data.size();
    file_header.total_file_size = file_header.pixel_data_offset + rotated_data.size();

    pixel_data = std::move(rotated_data);
}

void ClassBMP::ApplyGaussianBlur()
{
    const float kernel[5][5] =
    {
        {1/256.0f, 4/256.0f, 6/256.0f, 4/256.0f, 1/256.0f},
        {4/256.0f, 16/256.0f, 24/256.0f, 16/256.0f, 4/256.0f},
        {6/256.0f, 24/256.0f, 36/256.0f, 24/256.0f, 6/256.0f},
        {4/256.0f, 16/256.0f, 24/256.0f, 16/256.0f, 4/256.0f},
        {1/256.0f, 4/256.0f, 6/256.0f, 4/256.0f, 1/256.0f}
    };

    std::vector<uint8_t> blurred_data(pixel_data.size());
    int channels = image_info.bits_per_pixel / 8;

    #pragma omp parallel for  
    for (int y = 2; y < image_info.image_height - 2; y++)
    {
        for (int x = 2; x < image_info.image_width - 2; x++)
        {
            for (int c = 0; c < channels; c++)
            {
                float color = 0.0f;

                for (int ky = -2; ky <= 2; ky++)
                {
                    for (int kx = -2; kx <= 2; kx++)
                    {
                        int pixel_x = x + kx;
                        int pixel_y = y + ky;
                        color += pixel_data[(pixel_y * image_info.image_width + pixel_x) * channels + c] * kernel[ky + 2][kx + 2];
                    }
                }
                blurred_data[(y * image_info.image_width + x) * channels + c] = static_cast<uint8_t>(color);
            }
        }
    }
    pixel_data = blurred_data;
}

void ClassBMP::SaveToFile(const char* file_path)
{
    std::ofstream output_stream(file_path, std::ios_base::binary);
    if (!output_stream)
    {
        throw std::runtime_error("Error opening file for writing");
    }

    output_stream.write(reinterpret_cast<const char*>(&file_header), sizeof(file_header));
    output_stream.write(reinterpret_cast<const char*>(&image_info), sizeof(image_info));

    if (image_info.bits_per_pixel == 24)
    {
        output_stream.write(reinterpret_cast<const char*>(&color_info), sizeof(color_info));
    }

    output_stream.write(reinterpret_cast<const char*>(pixel_data.data()), pixel_data.size());
}
