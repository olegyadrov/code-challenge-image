# Implementation Notes

## Image format
The phrase "each pixel component is 8 bits" is ambiguous. It's unclear whether it implies the entire pixel is 8 bits or each color component is 8 bits, leading to an `RGB24` format. While some `YUV` formats do only use 8 bits per component, that's relatively rare. To accommodate this ambiguity, the `Image` constructor includes a `bytesPerPixel` parameter.

## Crop function
Although not strictly necessary, I've introduced a `scanLine(int i)` utility function to make implementing crop functionality easier.

## Constructors
One constructor is defined as follows:

`Image(const size_t width, const size_t height, const size_t bytesPerPixel);`

This constructor allocates the required memory upfront but leaves the image buffer uninitialized. This method allows for direct writing to the pixel buffer, eliminating the need for unnecessary data copying. Consequently, the user is responsible for setting the acquisition timestamp.

## Reference cropImage() implementation

The `main.cpp` file includes a reference implementation of the `cropImage()` function, along with a `printDebugData()` function for debugging purposes.
