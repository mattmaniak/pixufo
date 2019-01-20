# PixUfo
## Requirements:
- 1024x576 resolution,
- Windows or GNU/Linux with a graphical user interface.

## Development guide
### Windows (example for cmd.exe - 64-bit only for now):
1. Install the compilation environment choosing "TDM-GCC Recommended, C/C++".
[TDM-GCC](http://tdm-gcc.tdragon.net/)

2. Clone the repository with Git and enter it's directory.

3. Download SDL2 development libraries.
[SDL2-devel-2.*.*-mingw.tar.gz](https://www.libsdl.org/download-2.0.php)
Extract the SDL2-devel-2.*.*-mingw.tar.gz to SDL2-devel-2.*.*-mingw.tar and
then to a normal directory. If You have got 32-bit compiler, copy the
"i686-w64-mingw32", otherwise (64-bit) copy the "x86_64-w64-mingw32" and paste
it to Your's TDM-GCC installation directory.

Asterisk sign is the placeholder for minor and patch version numbers. They can
be vary between.

4. Compile and run.
```
cd [pixufo_directory]
mingw32-make
PixUfo.exe
```

### Linux-based OS (TL:DR for Ubuntu):
```
sudo apt update &&
sudo apt install git gcc g++ make libsdl2-dev &&
git clone https://gitlab.com/mattmaniak/pixufo.git &&
cd pixufo &&
make &&
./PixUfo
```

### Remove a compilation trash
#### GNU/Linux
```
make clean
```
#### Windows
```
mingw32-make clean
```
