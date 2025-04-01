#include "ClassBMP.h"

int main()
{
    try
    {
        // Load the image file
        ClassBMP image_one("a.bmp");   

        // Perform a clockwise rotation
        std::cout << "Rotating image clockwise by 90 degrees..." << std::endl;
        image_one.RotateClockwise90();      
        image_one.SaveToFile("Rotated90Clockwise.bmp");

        ClassBMP image_two("a.bmp");  
        // Perform a counter-clockwise rotation
        std::cout << "Rotating image counter-clockwise by 90 degrees..." << std::endl;
        image_two.RotateCounterClockwise90();
        image_two.SaveToFile("Rotated90CounterClockwise.bmp");

        ClassBMP image_three("a.bmp");  
        // Apply Gaussian Blur effect
        std::cout << "Applying Gaussian Blur to the image..." << std::endl;
        image_three.ApplyGaussianBlur();
        image_three.SaveToFile("GaussianBlur.bmp");

        std::cout << "Image processing completed successfully!" << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "An error occurred during processing: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
