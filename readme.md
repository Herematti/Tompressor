Tompressor is a simple compression program using the Huffman tree algorithm

## Building

**Linux / macOS:**
```
g++ $(ls *.cpp | grep -v secret.cpp) -o tompressor -O3
```

**Windows:**
```
g++ *.cpp -o tompressor -O3
```

## Usage

**Compress** files into a single `.tom` archive:
```
.\tompressor -c outputPath file1 file2 file3 ...
```
The `.tom` extension is added automatically, so `output` becomes `output.tom`

**Decompress** an archive into a directory:
```
.\tompressor -x archive.tom directory
```
The output directory must already exist
