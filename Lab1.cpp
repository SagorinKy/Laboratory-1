#include "ClassBMP.h"

int main()
{
    try
    {
        // Load the image file
        ClassBMP image("a.bmp");   // Изменено на правильное имя класса

        // Perform a clockwise rotation
        std::cout << "Rotating image clockwise by 90 degrees..." << std::endl;
        image.RotateClockwise90();      // Изменены имена методов
        image.SaveToFile("Rotated90Clockwise.bmp");

        // Perform a counter-clockwise rotation
        std::cout << "Rotating image counter-clockwise by 90 degrees..." << std::endl;
        image.RotateCounterClockwise90();
        image.SaveToFile("Rotated90CounterClockwise.bmp");

        // Apply Gaussian Blur effect
        std::cout << "Applying Gaussian Blur to the image..." << std::endl;
        image.ApplyGaussianBlur();
        image.SaveToFile("GaussianBlur.bmp");

        std::cout << "Image processing completed successfully!" << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "An error occurred during processing: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
