
CFLAGS = -std=c99 -D_DEFAULT_SOURCE
INCLUDE_PATHS = -isystem$(RAYLIB_PATH)/src \
                -isystem$(RAYLIB_PATH)/src/external

# On Raspberry Pi, you also need to specify where to find some header files
# that are in different locations. These header files are used by Raylib.
INCLUDE_PATHS += -I/opt/vc/include
INCLUDE_PATHS += -I/opt/vc/include/interface/vmcs_host/linux
INCLUDE_PATHS += -I/opt/vc/include/interface/vcos/pthreads
# Tell the compiler where to find libraylib.a
LDFLAGS = -L$RAYLIB_PATH/src
LDFLAGS += -L/opt/vc/lib  # needed on Raspberry Pi

# # On Desktop Linux
# LDLIBS = -lraylib -lm -lpthread -ldl -lrt -lX11

# On Raspberry Pi
LDLIBS = -lraylib -lm -lpthread -lGLESv2 -lEGL -lvcos -lvchiq_arm -lgbm -ldrm


CC = gcc

INCLUDE_PATHS=-I../raylib-5.5/src -L../raylib-5.5/src -lraylib

all:raylibtest
#-lvcos -lvchiq_arm
raylibtest: main.c
	gcc -o raylibtest main.c -I../raylib-5.5/src -I/opt/vc/include -L../raylib-5.5/src -L/opt/vc/lib -lraylib -lm -lpthread -lGLESv2 -lEGL -lgbm -ldrm
#$(CC) -o raylibtest main.c $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS)
#$(CC) $(INCLUDE_PATHS) -o main.c main