#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/mohammadeid/Documents/GitHub/computer-graphics-2023-muhammad-sliman/Build
  make -f /Users/mohammadeid/Documents/GitHub/computer-graphics-2023-muhammad-sliman/Build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/mohammadeid/Documents/GitHub/computer-graphics-2023-muhammad-sliman/Build
  make -f /Users/mohammadeid/Documents/GitHub/computer-graphics-2023-muhammad-sliman/Build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/mohammadeid/Documents/GitHub/computer-graphics-2023-muhammad-sliman/Build
  make -f /Users/mohammadeid/Documents/GitHub/computer-graphics-2023-muhammad-sliman/Build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/mohammadeid/Documents/GitHub/computer-graphics-2023-muhammad-sliman/Build
  make -f /Users/mohammadeid/Documents/GitHub/computer-graphics-2023-muhammad-sliman/Build/CMakeScripts/ReRunCMake.make
fi

