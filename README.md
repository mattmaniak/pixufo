# PixUfo
## Requirements:
- at least a 1024x576 display resolution,
- Windows or GNU/Linux with a graphical user interface.

## Development guide
### Windows:
1. Install the compilation environment choosing "TDM-GCC Recommended, C/C++".
[TDM-GCC](http://tdm-gcc.tdragon.net/)

2. Clone the repository with Git and enter it's directory.

3. Download SDL2 development libraries.
[SDL2-devel-2.0.9-mingw.tar.gz](https://www.libsdl.org/download-2.0.php)
Extract the SDL2-devel-2.0.9-mingw.tar.gz to SDL2-devel-2.0.9-mingw.tar and then
to a normal directory. From extracted folder copy the "SDL2-2.0.9" to the the
game's folder.

4. Compile and run.
```
cd <game directory>
mingw32-make
PixUfo.exe
```

### TL;DR for Linux-based (example commands for Ubuntu):
```
sudo apt update &&
sudo apt install git gcc g++ make libsdl2-dev &&
git clone https://gitlab.com/mattmaniak/pixufo.git &&
cd pixufo &&
make &&
./PixUfo
```

### Removing the compilation trash
```
make clean
```
or
```
mingw32-make clean
```
It will remove the binary file and all object files from the obj/. Note that
currently this directory is created empty in the repository. That's because the
Makefile won't create it.
