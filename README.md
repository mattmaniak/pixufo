# PixUfo
## Requirements:
- HD display resolution,
- 64-bit OS: Windows or GNU/Linux with the graphical user interface,
- [development-only] g++ (gcc with libstdc++) with version >= 4.8.1.

## Development guide
### Windows (example for cmd.exe - 64-bit only for now):
1. Install the compilation environment choosing "TDM-GCC Recommended, C/C++".
[TDM-GCC](http://tdm-gcc.tdragon.net/)

2. Clone the repository with Git and enter it's directory.

3. Download SDL2 development libraries.
[SDL2-devel-2.0.*-mingw.tar.gz](https://www.libsdl.org/download-2.0.php)
[SDL2_ttf-devel-2.0.*-mingw.tar.gz](https://www.libsdl.org/projects/SDL_ttf/)
Extract the SDL2-devel-2.0.*-mingw.tar.gz to SDL2-devel-2.*.*-mingw.tar and
then to a normal directory. Copy the "x86_64-w64-mingw32" and paste it to Your's
TDM-GCC-64 installation directory.

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
sudo apt install git gcc g++ make libsdl2-dev libsdl2-ttf-dev &&
git clone https://gitlab.com/mattmaniak/pixufo.git &&
cd pixufo &&
make &&
./PixUfo
```

### Remove object files
#### GNU/Linux
```
make clean
```
#### Windows
```
mingw32-make clean
```
