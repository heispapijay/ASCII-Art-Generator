# PNG to ASCII Art Converter

A simple and efficient C++ command-line utility that converts PNG images into ASCII art. 

It reads a PNG file, converts it to grayscale, downsamples it to a target width while maintaining the original aspect ratio, and prints the matching ASCII character for each pixel/block brightness to the console.

---

## 📋 Prerequisites

This tool depends on **`libpng`** to decode PNG files, and requires a compiler supporting **C++17** (due to the use of `std::clamp`).

### Install `libpng`

#### macOS (via Homebrew)
```bash
brew install libpng
```

#### Ubuntu / Debian
```bash
sudo apt-get update
sudo apt-get install build-essential libpng-dev
```

---

## 🛠️ Compilation

To compile `main1.cpp`, use the following commands based on your operating system.

### macOS (Apple Silicon / Homebrew)
Homebrew typically installs libraries in `/opt/homebrew`. You need to specify the include and library search paths:
```bash
g++ -O3 -std=c++17 main1.cpp -o ascii_art -I/opt/homebrew/include -L/opt/homebrew/lib -lpng
```

### Linux or standard environments
If `libpng` is installed in standard system paths:
```bash
g++ -O3 -std=c++17 main1.cpp -o ascii_art -lpng
```

---

## 🚀 Usage

Run the compiled executable from your terminal by passing the path to a PNG image:

```bash
./ascii_art <path_to_png> [columns]
```

### Parameters
* **`<path_to_png>`** (Required): The path to the PNG image you want to convert.
* **`[columns]`** (Optional, default: `80`): The width of the output ASCII art in characters. The height (number of rows) is automatically calculated to preserve the image's aspect ratio.

### Examples

**Default width (80 columns):**
```bash
./ascii_art robot_head.png
```

**Custom width (120 columns):**
```bash
./ascii_art robot_head.png 120
```

**Save the ASCII art to a text file:**
Since `main1.cpp` outputs directly to standard output, you can redirect the output to a file using the shell `>` operator:
```bash
./ascii_art robot_head.png 80 > robot_head.txt
```

---

## 🎨 Brightness Mapping

The program maps pixel luminance to ASCII characters ranging from darkest to lightest:
`@#S%?*+;:,. ` *(space represents the brightest pixels/white, `@` represents the darkest pixels/black)*
