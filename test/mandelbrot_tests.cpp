#include <gtest/gtest.h>

#include <cstdio>
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

#include "Mandelbrot.h"
#include "bitmap.h"
#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"

#pragma pack()

namespace {

const int kMaxIterations = 1 << 10;
const char kTestOutputDir[] = MANDELBROT_TEST_OUTPUT_DIR;

std::string test_file_path(const std::string& file_name) {
    return std::string(kTestOutputDir) + "/" + file_name;
}

std::vector<uint8_t> read_file(const std::string& file_name) {
    std::ifstream file(file_name.c_str(), std::ios::binary);
    return std::vector<uint8_t>(std::istreambuf_iterator<char>(file),
                                std::istreambuf_iterator<char>());
}

TEST(MandelbrotIterationsTest, ReturnsMaxIterationsForKnownInteriorPoints) {
    EXPECT_EQ(kMaxIterations,
              Mandelbrot::Mandelbrot::getIterations(0.0, 0.0));
    EXPECT_EQ(kMaxIterations,
              Mandelbrot::Mandelbrot::getIterations(-1.0, 0.0));
}

TEST(MandelbrotIterationsTest, ReturnsZeroForPointThatEscapesImmediately) {
    EXPECT_EQ(0, Mandelbrot::Mandelbrot::getIterations(2.0, 2.0));
}

TEST(MandelbrotIterationsTest, CountsIterationsBeforeEscape) {
    EXPECT_EQ(2, Mandelbrot::Mandelbrot::getIterations(1.0, 0.0));
    EXPECT_EQ(1, Mandelbrot::Mandelbrot::getIterations(0.0, 2.0));
}

TEST(MandelbrotIterationsTest, NeverReturnsMoreThanMaxIterations) {
    const int iterations = Mandelbrot::Mandelbrot::getIterations(-0.75, 0.1);

    EXPECT_GE(iterations, 0);
    EXPECT_LE(iterations, kMaxIterations);
}

TEST(BitmapTest, WriteReturnsFalseForInvalidPath) {
    Mandelbrot::Bitmap bitmap(1, 1);

    EXPECT_FALSE(bitmap.write(test_file_path("missing-directory/output.bmp")));
}

TEST(BitmapTest, WriteCreatesExpectedBmpHeaders) {
    const std::string file_name = test_file_path("bitmap_headers.bmp");
    std::remove(file_name.c_str());

    Mandelbrot::Bitmap bitmap(2, 3);

    ASSERT_TRUE(bitmap.write(file_name));

    const std::vector<uint8_t> bytes = read_file(file_name);
    ASSERT_EQ(sizeof(Mandelbrot::BitmapFileHeader) +
                  sizeof(Mandelbrot::BitmapInfoHeader) + 18,
              bytes.size());

    const Mandelbrot::BitmapFileHeader* file_header =
        reinterpret_cast<const Mandelbrot::BitmapFileHeader*>(&bytes[0]);
    const Mandelbrot::BitmapInfoHeader* info_header =
        reinterpret_cast<const Mandelbrot::BitmapInfoHeader*>(
            &bytes[sizeof(Mandelbrot::BitmapFileHeader)]);

    EXPECT_EQ('B', file_header->header[0]);
    EXPECT_EQ('M', file_header->header[1]);
    EXPECT_EQ(static_cast<int32_t>(bytes.size()), file_header->filesize);
    EXPECT_EQ(static_cast<int32_t>(sizeof(Mandelbrot::BitmapFileHeader) +
                                   sizeof(Mandelbrot::BitmapInfoHeader)),
              file_header->dataOffset);
    EXPECT_EQ(2, info_header->width);
    EXPECT_EQ(3, info_header->height);
    EXPECT_EQ(24, info_header->bitsPerPixel);

    std::remove(file_name.c_str());
}

TEST(BitmapTest, SetPixelWritesBgrBytes) {
    const std::string file_name = test_file_path("single_pixel.bmp");
    std::remove(file_name.c_str());

    Mandelbrot::Bitmap bitmap(1, 1);
    bitmap.setPixel(0, 0, 0x11, 0x22, 0x33);

    ASSERT_TRUE(bitmap.write(file_name));

    const std::vector<uint8_t> bytes = read_file(file_name);
    const std::size_t pixel_offset = sizeof(Mandelbrot::BitmapFileHeader) +
                                     sizeof(Mandelbrot::BitmapInfoHeader);
    ASSERT_GE(bytes.size(), pixel_offset + 3);
    EXPECT_EQ(0x33, bytes[pixel_offset + 0]);
    EXPECT_EQ(0x22, bytes[pixel_offset + 1]);
    EXPECT_EQ(0x11, bytes[pixel_offset + 2]);

    std::remove(file_name.c_str());
}

TEST(BitmapTest, FillColourWritesEveryPixel) {
    const std::string file_name = test_file_path("filled_bitmap.bmp");
    std::remove(file_name.c_str());

    Mandelbrot::Bitmap bitmap(2, 2);
    bitmap.fillColour(0x01, 0x02, 0x03);

    ASSERT_TRUE(bitmap.write(file_name));

    const std::vector<uint8_t> bytes = read_file(file_name);
    const std::size_t pixel_offset = sizeof(Mandelbrot::BitmapFileHeader) +
                                     sizeof(Mandelbrot::BitmapInfoHeader);
    ASSERT_EQ(pixel_offset + 12, bytes.size());

    for (std::size_t i = pixel_offset; i < bytes.size(); i += 3) {
        EXPECT_EQ(0x03, bytes[i + 0]);
        EXPECT_EQ(0x02, bytes[i + 1]);
        EXPECT_EQ(0x01, bytes[i + 2]);
    }

    std::remove(file_name.c_str());
}

TEST(MandelbrotDrawTest, WritesNonEmptyBitmapFile) {
    const std::string file_name = test_file_path("mandelbrot_smoke.bmp");
    std::remove(file_name.c_str());

    Mandelbrot::Mandelbrot plot(32, 24, 1);
    plot.draw(file_name, Mandelbrot::Mandelbrot::GREEN);

    const std::vector<uint8_t> bytes = read_file(file_name);
    ASSERT_EQ(sizeof(Mandelbrot::BitmapFileHeader) +
                  sizeof(Mandelbrot::BitmapInfoHeader) + (32 * 24 * 3),
              bytes.size());
    EXPECT_EQ('B', bytes[0]);
    EXPECT_EQ('M', bytes[1]);

    std::remove(file_name.c_str());
}

}  // namespace
