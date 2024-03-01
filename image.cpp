#include "image.h"

std::istream& operator>>(std::istream& is, Image& image)
{
    size_t width, height, bytesPerPixel;
    is >> width;
    is >> height;
    is >> bytesPerPixel;
    const uint8_t imageSize = width * height * bytesPerPixel;
    if (imageSize == 0)
    {
        throw std::invalid_argument("Invalid image size");
    }
    image.m_width = width;
    image.m_height = height;
    image.m_bytesPerPixel = bytesPerPixel;
    image.m_buffer = std::make_unique<uint8_t[]>(imageSize);
    is.read(reinterpret_cast<char*>(image.m_buffer.get()), imageSize);
    image.m_acquiredAt = std::chrono::system_clock::now();
    return is;
}

Image::Image()
    : m_width{0}
    , m_height{0}
    , m_bytesPerPixel{0}
    , m_buffer{nullptr}
    , m_acquiredAt{}
{
}

Image::Image(const size_t width, const size_t height, const size_t bytesPerPixel)
{
    const uint8_t imageSize = width * height * bytesPerPixel;
    if (imageSize == 0)
    {
        throw std::invalid_argument("Invalid image size");
    }
    m_width = width;
    m_height = height;
    m_bytesPerPixel = bytesPerPixel;
    m_buffer = std::make_unique<uint8_t[]>(imageSize);
}

Image::Image(const size_t width, const size_t height, const size_t bytesPerPixel, uint8_t* pixelData)
    : Image(width,
        height,
        bytesPerPixel)
{
    const uint8_t imageSize = width * height * bytesPerPixel;
    std::memcpy(m_buffer.get(), pixelData, imageSize);
    m_acquiredAt = std::chrono::system_clock::now();
}

Image::Image(Image& image)
    : Image(image.width(),
        image.height(),
        image.bytesPerPixel(),
        image.pixelData())
{
}

Image::Image(Image&& other)
{
    std::swap(m_width, other.m_width);
    std::swap(m_height, other.m_height);
    std::swap(m_bytesPerPixel, other.m_bytesPerPixel);
    std::swap(m_buffer, other.m_buffer);
    std::swap(m_acquiredAt, other.m_acquiredAt);
}

size_t Image::width() const
{
    return m_width;
}

size_t Image::height() const
{
    return m_height;
}

size_t Image::bytesPerPixel() const
{
    return m_bytesPerPixel;
}

uint8_t* Image::pixelData() const
{
    return m_buffer.get();
}

uint8_t* Image::scanLine(size_t i) const
{
    if (i >= m_height)
    {
        return nullptr;
    }
    return m_buffer.get() + i * m_width * m_bytesPerPixel;
}

std::chrono::time_point<std::chrono::system_clock> Image::acquiredAt() const
{
    return m_acquiredAt;
}

void Image::setAcquiredAt(std::chrono::time_point<std::chrono::system_clock> timestamp)
{
    m_acquiredAt = timestamp;
}
