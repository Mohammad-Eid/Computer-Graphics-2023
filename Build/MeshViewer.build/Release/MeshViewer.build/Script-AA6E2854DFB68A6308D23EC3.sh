#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/mohammadeid/Documents/GitHub/computer-graphics-2023-muhammad-sliman/Build
  /Applications/CMake.app/Contents/bin/cmake -E copy /Users/mohammadeid/Documents/GitHub/computer-graphics-2023-muhammad-sliman/Viewer/shaders/fshader.glsl /Users/mohammadeid/Documents/GitHub/computer-graphics-2023-muhammad-sliman/Viewer/shaders/vshader.glsl /Users/mohammadeid/Documents/GitHub/computer-graphics-2023-muhammad-sliman/Build/bin/Debug
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/mohammadeid/Documents/GitHub/computer-graphics-2023-muhammad-sliman/Build
  /Applications/CMake.app/Contents/bin/cmake -E copy /Users/mohammadeid/Documents/GitHub/computer-graphics-2023-muhammad-sliman/Viewer/shaders/fshader.glsl /Users/mohammadeid/Documents/GitHub/computer-graphics-2023-muhammad-sliman/Viewer/shaders/vshader.glsl /Users/mohammadeid/Documents/GitHub/computer-graphics-2023-muhammad-sliman/Build/bin/Release
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/mohammadeid/Documents/GitHub/computer-graphics-2023-muhammad-sliman/Build
  /Applications/CMake.app/Contents/bin/cmake -E copy /Users/mohammadeid/Documents/GitHub/computer-graphics-2023-muhammad-sliman/Viewer/shaders/fshader.glsl /Users/mohammadeid/Documents/GitHub/computer-graphics-2023-muhammad-sliman/Viewer/shaders/vshader.glsl /Users/mohammadeid/Documents/GitHub/computer-graphics-2023-muhammad-sliman/Build/bin/MinSizeRel
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/mohammadeid/Documents/GitHub/computer-graphics-2023-muhammad-sliman/Build
  /Applications/CMake.app/Contents/bin/cmake -E copy /Users/mohammadeid/Documents/GitHub/computer-graphics-2023-muhammad-sliman/Viewer/shaders/fshader.glsl /Users/mohammadeid/Documents/GitHub/computer-graphics-2023-muhammad-sliman/Viewer/shaders/vshader.glsl /Users/mohammadeid/Documents/GitHub/computer-graphics-2023-muhammad-sliman/Build/bin/RelWithDebInfo
fi

