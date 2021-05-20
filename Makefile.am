# Allow directory manangement of source
AUTOMAKE_OPTIONS = subdir-objects
# Use m4 directory (modern best practice)
ACLOCAL_AMFLAGS = -I m4 --install

bin_PROGRAMS = Game

dist_pkgdata_DATA = \
			  data/shaders/vertex.glsl \
			  data/shaders/fragment.glsl \
			  data/container.jpg

Game_SOURCES = \
			   src/main.cpp \
			   src/Error.h \
			   src/Error.cpp \
			   src/ShaderLoader.h \
			   src/ShaderLoader.cpp


# Generate final path locations based on configuration at compile time
CLEANFILES = config_file_paths.h
DISTCLEANFILES = config_file_paths.h
BUILT_SOURCES = config_file_paths.h
config_file_paths.h:
	echo '#define DATADIR "$(pkgdatadir)"' >$@

Game_CPPFLAGS = @sdl2_CFLAGS@ \
				@glew_CFLAGS@ \
				@opengl_CFLAGS@ \
				@glm_CFLAGS@ \
				@sdl2_image_CFLAGS@

Game_LDFLAGS = @sdl2_LIBS@ \
			   @glew_LIBS@ \
			   @opengl_LIBS@ \
			   @glm_LIBS@ \
			   @sdl2_image_LIBS@
