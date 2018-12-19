# PixUfo
## Requirements:
- at least HD display,
- Windows or Linux-based system.

## TL:DR; guide to the development:
### Windows:
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
cd pixufo/game
mingw32-make
pixufo.exe
```

### GNU/Linux with GUI (commands for Ubuntu):
1. Install needed tools.
```
apt update && apt install gcc g++ make sdl2
```
2. Clone the repository.
```
git clone https://gitlab.com/mattmaniak/pixufo.git
```
3. Dive in, compile and run.
```
cd pixufo/game
make
./pixufo
```
