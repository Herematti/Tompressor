Tompressor is a simple compression program made using the huffman tree algorythm.

To first start the file, use
```
    g++ *.cpp -o tompressor -O3
```
to compile the project.


After that to use the compression there are only two commands:

```
    .\tompressor -c path-to-uncompressed-file path-to-compressed-file
    .\tompressor -x path-to-compressed-file path-to-uncompressed-file
```