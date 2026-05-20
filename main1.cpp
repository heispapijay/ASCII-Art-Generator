#include "image.h"

// darkest to lightest
const std::string chars = "@#S%?*+;:,. ";

int main(int argc, char* argv[]) {

	if (argc < 2) {
		std::cout << "need an image file\n";
		return 1;
	}

	ColorImage img;
	img.Load(argv[1]);

	// convert to grayscale
	GrayscaleImage gray(img);

	int w = gray.GetWidth();
	int h = gray.GetHeight();

	int cols = 80;
	if (argc >= 3) cols = std::stoi(argv[2]);

	int rows = (int)(cols * h / (float)w * 0.5);

	float xstep = w / (float)cols;
	float ystep = h / (float)rows;

	std::string out = "";

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {

			int x = (int)(c * xstep + xstep / 2);
			int y = (int)(r * ystep + ystep / 2);

			Byte lum = gray.Get(x, y);

			int idx = lum * (chars.size() - 1) / 255;
			out += chars[idx];
		}
		out += "\n";
	}

	std::cout << out;

	return 0;
}

// if (argc >= 4) {
// 	std::ofstream f(argv[3]);
// 	f << out;
// 	std::cout << "saved to " << argv[3] << "\n";
// }