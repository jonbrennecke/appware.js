# general vars
cxx = clang
cxxflags = -std=c++11 -Wall -pedantic
objcflags = -lobjc -framework Cocoa
objcsrc = ./src/view.mm
cxxsrc = ./src/index.cpp
src = $(objcsrc) $(cxxsrc)
arch = -arch x86_64

_inc = 

# -Os -gdwarf-2 -mmacosx-version-min=10.7 -arch x86_64 -Wall -Wendif-labels -W -Wno-unused-parameter -stdlib=libc++ -fno-rtti -fno-exceptions -fno-threadsafe-statics -Wall -std=c++11 -framework Cocoa -fobjc-arc -MMD -MF ./Release/.deps/Release/obj.target/appware/src/view.o.d.raw -c -o Release/obj.target/appware/src/view.o ../

# node version and folder
node-gyp-dir = /Users/jon/.node-gyp/
node-ver = 0.10.32

# v8
v8flags = '-D_DARWIN_USE_64_BIT_INODE=1' '-D_LARGEFILE_SOURCE' '-D_FILE_OFFSET_BITS=64' '-DBUILDING_NODE_EXTENSION'
v8-dir = $(node-gyp-dir)/$(node-ver)
_inc += $(v8-dir)/src $(v8-dir)/deps/uv/include $(v8-dir)/deps/v8/include

_lib =

inc = $(addprefix -I,$(_inc))
lib = $(addprefix -L,$(_lib))


# ************************************************************************


all:
	$(cxx) $(arch) $(v8flags) $(cxxflags) $(objcflags) $(inc) $(lib) $(src)
