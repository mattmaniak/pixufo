# PixUfo
## Requirements:
- at least a 1024x768 display,
- Windows or GNU/Linux with a graphical user interface.

## Development guide
### Windows:
1. Install the compilation environment as TDM-GCC Recommended, C/C++
[TDM-GCC](http://tdm-gcc.tdragon.net/)

2. Clone the repository with Git and enter it's directory.

3. Download SDL2 development files.
[SDL2-devel-2.0.9-mingw.tar.gz](https://www.libsdl.org/download-2.0.php)
Extract them and put the "SDL2-2.0.9" in the game's root folder.

6. Compile and run.
```
mingw32-make -f Makefile.win
PixUfo.exe
```

### GNU/Linux with GUI (commands for Ubuntu):
1. Install needed tools.
```
sudo apt update && sudo apt install gcc g++ make libsdl2-dev
```
2. Clone the repository.
```
git clone https://gitlab.com/mattmaniak/pixufo.git
```
3. Dive in, compile and run.
```
cd pixufo
make
./PixUfo
```
### Removing the compilation trash.
```
make clean
```
It will remove the binary file and all object files from the obj/. Note that
currently this directory is created empty in the repository. That's because the
Makefile won't create it.
