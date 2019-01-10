# PixUfo
## Requirements:
- at least a HD display (?),
- Windows or Linux-based system.

## TL:DR; guide to the development:
### Windows: (WIP)
1. Download and install the environment.
[tdm-gcc](http://tdm-gcc.tdragon.net/)
Tested only on 64-bit machine/gcc version!

2. Install it with: gcc, g++ and mingw32-make (all should be checked by default).

3. Check PATH environment variable and add if not exists with the value: C:\TDM-GCC-64\bin or extend this
one with Your current TDM64 installation path.

4. Clone the repository with Git and enter it's directory.

5. Download SDL2 development files.
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
make -f makefile.nix
./pixufo
```
