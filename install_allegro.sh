git clone https://github.com/liballeg/allegro5.git --depth=1 -b5.2.3.0
cd allegro5
cmake -DWANT_AUDIO=OFF\
    -DWANT_DEMO=OFF\
    -DWANT_EXAMPLES=OFF\
    -DWANT_IMAGE=OFF\
    -DWANT_NATIVE_IMAGE_LOADER=OFF\
    -DWANT_VIDEO=OFF\
    -DWANT_TESTS=OFF\
    -DWANT_PHYSFS=OFF .
make -j5
cd ..
