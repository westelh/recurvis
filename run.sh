#!/bin/sh
gradle build
DYLD_LIBRARY_PATH="./3rd/allegro/build/lib:./build/libs/allegro_wrapper/shared/release/" build/exe/main/release/main
