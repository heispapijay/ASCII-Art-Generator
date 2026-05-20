#include "image.h"
#include <fstream>

static const std::string palette = "@#S%?*+;:,. ";

static char intensityToChar(Byte lum) {
    int idx = (lum * (int)(palette.size() - 1)) / 255;
    return palette[idx];
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input.png> [output.txt] [cols]\n";
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argc >= 3 ? argv[2] : "";
    int cols = argc >= 4 ? std::stoi(argv[3]) : 80;

    ColorImage color;
    color.Load(inputFile);

    if (color.GetWidth() == 0 || color.GetHeight() == 0) {
        std::cerr << "Failed to load image: " << inputFile << "\n";
        return 1;
    }

    GrayscaleImage gray(color);

    int imgW = gray.GetWidth();
    int imgH = gray.GetHeight();

    int rows = std::max(1, (int)(cols * imgH / (double)imgW * 0.45));

    float xStep = imgW / (float)cols;
    float yStep = imgH / (float)rows;

    std::string result;
    result.reserve((cols + 1) * rows);

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int x0 = (int)(col * xStep);
            int y0 = (int)(row * yStep);
            int x1 = std::min((int)((col + 1) * xStep), imgW);
            int y1 = std::min((int)((row + 1) * yStep), imgH);

            long sum = 0;
            int count = 0;
            for (int y = y0; y < y1; y++) {
                for (int x = x0; x < x1; x++) {
                    sum += gray(x, y);
                    count++;
                }
            }

            Byte avg = count > 0 ? (Byte)(sum / count) : 0;
            result += intensityToChar(avg);
        }
        result += '\n';
    }

    std::cout << result;

    if (!outputFile.empty()) {
        std::ofstream ofs(outputFile);
        if (!ofs) {
            std::cerr << "Could not write to " << outputFile << "\n";
            return 1;
        }
        ofs << result;
        std::cout << "Saved to " << outputFile << "\n";
    }

    return 0;
}
