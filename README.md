# PixUfo
## Requirements:
- at least a HD display (?),
- Windows or Linux-based system.

## TL:DR; guide to the development:
### Windows: (WIP)
1. Download and install the environment.
[MinGW](mingw.org)

2. Add the environment variable PATH with the value: C:\MinGW\bin or extend this
one with Your current MinGW installation path.

3. Open the cmd.exe and install needed tools.
```
mingw-get install gcc g++ make
```
4. Clone the repository with Git.

5. Dive in, compile and run.
```
cd pixufo
mingw32-make -f makefile.win
pixufo.exe
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
