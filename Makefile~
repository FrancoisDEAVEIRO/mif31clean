
all: bin

CC = g++
ifeq ($(OS),Windows_NT)
	CFLAGS = 	-W -Wall -g -std=c++11 \
				-Isrc \
				-Iextern/SDL2_mingw/SDL2-2.0.3/include \
				-Iextern/SDL2_mingw/SDL2-2.0.3/include/SDL2 \
				-Iextern/SDL2_mingw/SDL2_image-2.0.0/i686-w64-mingw32/include \
				-Iextern/SDL2_mingw/SDL2_image-2.0.0/i686-w64-mingw32/include/SDL2 \
				-Iextern/SDL2_mingw/SDL2_ttf-2.0.12/i686-w64-mingw32/include \
				-Iextern/SDL2_mingw/SDL2_ttf-2.0.12/i686-w64-mingw32/include/SDL2
	LDFLAGS =   -L/usr/lib \
				-Lbin \
				extern/SDL2_mingw/libmingw32.a \
				extern/SDL2_mingw/SDL2-2.0.3/i686-w64-mingw32/lib/libSDL2main.a \
				extern/SDL2_mingw/SDL2-2.0.3/i686-w64-mingw32/lib/libSDL2.dll.a \
				extern/SDL2_mingw/SDL2_image-2.0.0/i686-w64-mingw32/lib/libSDL2_image.dll.a \
				extern/SDL2_mingw/SDL2_ttf-2.0.12/i686-w64-mingw32/lib/libSDL2_ttf.dll.a
else
UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	CFLAGS = 	-W -Wall -g -std=c++11 \
				-Isrc \
				-Iextern/SDL2_mac/SDL2.framework/Versions/A/Headers/ \
				-Iextern/SDL2_mac/SDL2.framework/Versions/A/Headers/SDL2 \
				-Iextern/SDL2_mac/SDL2_image.framework/Versions/A/Headers \
				-Iextern/SDL2_mac/SDL2_ttf.framework/Versions/A/Headers
	LDFLAGS =   -L/usr/lib \
				-Lbin \
				extern/SDL2_mac/SDL2.framework/Versions/A/SDL2 \
				extern/SDL2_mac/SDL2_image.framework/Versions/A/SDL2_image \
				extern/SDL2_mac/SDL2_ttf.framework/Versions/A/SDL2_ttf \
				-rpath @executable_path/../extern/SDL2_mac \
				#-lSDL2 -lSDL2_ttf -lSDL2_image
else
	CFLAGS = 	-W -Wall -g -std=c++11 \
				-Isrc \
				-I/usr/include/SDL2
	LDFLAGS =   -L/usr/lib -lSDL2 -lSDL2_ttf -lSDL2_image
endif
endif

GRAPIC_OBJS = src/Grapic.cpp src/Grapic_func.cpp
EXEC_RUN = bin/demo ; bin/myprog ; bin/particles ; bin/tetris ; bin/fluid ; bin/simpleDrawing ; bin/pacman
EXEC = $(EXEC_RUN:;=)

bin: $(EXEC)

test: bin
	$(EXEC_RUN)

bin/demo: apps/demo/main_demo.cpp $(GRAPIC_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

bin/myprog: apps/myprog/main_myprog.cpp $(GRAPIC_OBJS) tools/createFile.cpp
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

bin/particles: apps/particles/main_particles.cpp $(GRAPIC_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

bin/tetris: apps/tetris/main_tetris.cpp $(GRAPIC_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

bin/fluid: apps/fluid/main_fluid.cpp $(GRAPIC_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

bin/simpleDrawing: apps/simpleDrawing/main_simpleDrawing.cpp $(GRAPIC_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

bin/pacman: apps/pacman/main_pacman.cpp $(GRAPIC_OBJS) apps/pacman/Jeu.cpp apps/pacman/Terrain.cpp apps/pacman/Pacman.cpp
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

bin/%: apps/%/main_%.cpp $(GRAPIC_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf bin/*.exe $(EXEC)

doc: doc/* doc/images/* src/* FORCE
	cd doc ; doxygen

zip: version doc bin/remove_correction.exe
	script/make_zip.sh

version: FORCE
	sh script/inc_version.sh

web: version zip doc
	/c/Program\ Files\ \(x86\)/WinSCP/winscp.com -script=script/scp_script_toWeb.txt
	
FORCE:

bin/remove_correction.exe: script/remove_correction.cpp
	g++ -Wall script/remove_correction.cpp -o bin/remove_correction.exe
