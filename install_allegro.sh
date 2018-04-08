git clone https://github.com/liballeg/allegro5.git 3rd/allegro --depth=1 -b5.2.3.0
cd 3rd/allegro
cmake -DWANT_AUDIO=OFF\
    -DWANT_DEMO=OFF\
    -DWANT_EXAMPLES=OFF\
    -DWANT_IMAGE=OFF\
    -DWANT_NATIVE_IMAGE_LOADER=OFF\
    -DWANT_VIDEO=OFF\
    -DWANT_TESTS=OFF\
    -DWANT_PHYSFS=OFF\
    -DCMAKE_INSTALL_PREFIX=build .
make install -j5
cd ..
