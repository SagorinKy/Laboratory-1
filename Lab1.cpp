#include "ClassBMP.h"
#include <chrono>
#include <iostream>

int main()
{
    try
    {
        auto total_start = std::chrono::high_resolution_clock::now();
        // Load the image file
        ClassBMP image_one("a.bmp");   

        // Perform a clockwise rotation
        std::cout << "Rotating image clockwise by 90 degrees..." << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        image_one.RotateClockwise90();      
        auto end = std::chrono::high_resolution_clock::now();
        image_one.SaveToFile("Rotated90Clockwise.bmp");
        std::cout << "Right rotation time: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                  << " ms" << std::endl;

        ClassBMP image_two("a.bmp");  
        // Perform a counter-clockwise rotation
        std::cout << "Rotating image counter-clockwise by 90 degrees..." << std::endl;
        start = std::chrono::high_resolution_clock::now();
        image_two.RotateCounterClockwise90();
        end = std::chrono::high_resolution_clock::now();
        image_two.SaveToFile("Rotated90CounterClockwise.bmp");
        std::cout << "Left rotation time: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                  << " ms" << std::endl;

        ClassBMP image_three("a.bmp");  
        // Apply Gaussian Blur effect
        std::cout << "Applying Gaussian Blur to the image..." << std::endl;
        start = std::chrono::high_resolution_clock::now();
        image_three.ApplyGaussianBlur();
        end = std::chrono::high_resolution_clock::now();
        image_three.SaveToFile("GaussianBlur.bmp");
        std::cout << "Writing filtering time: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                  << " ms" << std::endl;

        auto total_end = std::chrono::high_resolution_clock::now();
        image_three.SaveToFile("GaussianBlur.bmp");
        std::cout << "All time taken: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(total_end - total_start).count()
                  << " ms" << std::endl;


        std::cout << "Image processing completed successfully!" << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "An error occurred during processing: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
