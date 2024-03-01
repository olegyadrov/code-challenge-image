#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>
#include <memory>
#include <chrono>
#include <istream>

class Image
{
    /** Non-member extraction operator. */
    friend std::istream& operator>>(std::istream& is, Image& image);
    
public:
    /** Constructs an empty image instance. */
    Image();
    /** Constructs an unitialized image with the given size. */
    Image(const size_t width, const size_t height, const size_t bytesPerPixel);
    /** Constructs an image instance from the provided pixel data. */
    Image(const size_t width, const size_t height, const size_t bytesPerPixel, uint8_t* pixelData);
    /** Constructs a deep copy instance. */
    Image(Image& image);
    /** Transfers ownership of other.m_buffer to m_buffer. */
    Image(Image&& other);
    /** Default destructor. */
    ~Image() = default;
    /** Returns the number of pixel columns in the image (0 if empty). */
    size_t width() const;
    /** Returns the number of pixel rows in the image (0 if empty). */
    size_t height() const;
    /** Returns the modifiable pixel data for the image (nullptr if empty). */
    uint8_t* pixelData() const;
    /** Returns a pointer to the pixel data at the scanline with index i. */
    uint8_t* scanLine(size_t i) const;
    /** Returns the number of bytes per pixel in the image, e.g. 3 for an RGB image. */
    size_t bytesPerPixel() const;
    /** Returns the timestamp of when this image was acquired. */
    std::chrono::time_point<std::chrono::system_clock> acquiredAt() const;
    /** Sets the acquisition timestamp. */
    void setAcquiredAt(std::chrono::time_point<std::chrono::system_clock> timestamp);

private:
    size_t m_width;
    size_t m_height;
    size_t m_bytesPerPixel;
    std::unique_ptr<uint8_t[]> m_buffer;
    std::chrono::time_point<std::chrono::system_clock> m_acquiredAt;
};

#endif /* !IMAGE_H */
