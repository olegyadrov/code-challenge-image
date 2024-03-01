# Implement a Class for an Image

Our group provides a service that analyzes 2d images. These images could come from an Ultrasound probe, Camera, or another image acquisition device.

For example, one method of this Image service takes as input a rectangular image and returns a cropped version of this image.

```
Image cropImage(const Image& image, int left, int top, int right, int bottom);
```

Given the following requirements for an `Image`
- Is a two-dimensional rectangular matrix of pixels
- Each pixel component is 8 bits
- Acquired at a specific time
- Acquired as one of a sequence of images in a stream
- `Image` objects are copyable and movable
- `Image` objects can be empty

Write a class interface and implementation this `Image`. This `Image` can be passed into an API such as `cropImage`. It is not necessary to write `cropImage` but the `Image` class should expose enough of an interface to write a `cropImage` implementation.
