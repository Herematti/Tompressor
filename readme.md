Tompressor is a simple compression program using the Huffman tree algorithm

## Compilation

```
g++ *.cpp -o tompressor -O3
```

## Usage

**Compress** files into a single `.tom` archive:
```
.\tompressor -c output file1 file2 file3 ...
```
The `.tom` extension is added automatically, so `output` becomes `output.tom`

**Decompress** an archive into a directory:
```
.\tompressor -x archive.tom directory
```
The output directory must already exist
