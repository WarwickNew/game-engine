# Allow directory manangement of source
AUTOMAKE_OPTIONS = subdir-objects
# Use m4 directory (modern best practice)
ACLOCAL_AMFLAGS = -I m4 --install

bin_PROGRAMS = Game

Game_SOURCES = \
			   src/main.cpp \
			   src/Error.h \
			   src/Error.cpp
Game_CPPFLAGS = @sdl2_CFLAGS@ @glew_CFLAGS@ @opengl_CFLAGS@
Game_LDFLAGS = @sdl2_LIBS@ @glew_LIBS@ @opengl_LIBS@
