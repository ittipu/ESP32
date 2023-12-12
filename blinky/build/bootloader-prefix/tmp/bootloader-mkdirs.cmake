# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/kamruzzaman/esp/esp-idf/components/bootloader/subproject"
  "/home/kamruzzaman/tipu/Excercise/ESP32/blinky/build/bootloader"
  "/home/kamruzzaman/tipu/Excercise/ESP32/blinky/build/bootloader-prefix"
  "/home/kamruzzaman/tipu/Excercise/ESP32/blinky/build/bootloader-prefix/tmp"
  "/home/kamruzzaman/tipu/Excercise/ESP32/blinky/build/bootloader-prefix/src/bootloader-stamp"
  "/home/kamruzzaman/tipu/Excercise/ESP32/blinky/build/bootloader-prefix/src"
  "/home/kamruzzaman/tipu/Excercise/ESP32/blinky/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/kamruzzaman/tipu/Excercise/ESP32/blinky/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/kamruzzaman/tipu/Excercise/ESP32/blinky/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
