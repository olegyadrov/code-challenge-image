#include "image.h"

#include <iostream>
#include <algorithm>

Image cropImage(const Image& image, int left, int top, int right, int bottom)
{
    if (left < 0 || right >= image.width() || left >= right ||
        top < 0 || bottom >= image.height() || top >= bottom)
        {
            throw std::invalid_argument("Invalid image size");
        }
    const size_t croppedImageWidth = right - left + 1;
    const size_t croppedImageHeight = bottom - top + 1;
    const size_t croppedImageSize = croppedImageWidth * croppedImageHeight * image.bytesPerPixel();
    const size_t croppedImageBytesPerLine = croppedImageWidth * image.bytesPerPixel();
    Image croppedImage(croppedImageWidth, croppedImageHeight, image.bytesPerPixel());
    for (size_t croppedImageLineIndex = 0; croppedImageLineIndex < croppedImageHeight; croppedImageLineIndex++)
    {
        uint8_t* src = image.scanLine(top + croppedImageLineIndex) + left * image.bytesPerPixel();
        uint8_t* dst = croppedImage.pixelData() + croppedImageLineIndex * croppedImageBytesPerLine;
        std::memcpy(dst, src, croppedImageBytesPerLine);
    }
    croppedImage.setAcquiredAt(std::chrono::system_clock::now());
    return croppedImage;
}

void printDebugData(const Image& image)
{
    std::cout << "Image size: " << image.width() << "x" << image.height() << std::endl;
    std::cout << "Bytes per pixel: " << image.bytesPerPixel() << std::endl;
    std::cout << "Acquired at: " << std::chrono::system_clock::to_time_t(image.acquiredAt()) << std::endl;
    for (size_t row = 0; row < image.height(); row++)
    {
        for (size_t column = 0; column < image.width(); column++)
        {
            for (size_t byteComponent = 0; byteComponent < image.bytesPerPixel(); byteComponent++)
            {
                std::cout << static_cast<unsigned int>(image.pixelData()[row * image.width() * image.bytesPerPixel() + column * image.bytesPerPixel() + byteComponent]);
                if (byteComponent != image.bytesPerPixel() - 1)
                {
                    std::cout << ",";
                }
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "----------------" << std::endl;
}

int main(int argc, char *argv[])
{
    std::vector<uint8_t> testData = {
        0, 0, 0, 1, 1, 1, 2, 2, 2,
        3, 3, 3, 4, 4, 4, 5, 5, 5,
        6, 6, 6, 7, 7, 7, 8, 8, 8
    };
    Image imageA(3, 3, 3, testData.data());
    printDebugData(imageA);
    Image imageB = cropImage(imageA, 0, 0, 1, 1);
    printDebugData(imageB);

    return EXIT_SUCCESS;
}
