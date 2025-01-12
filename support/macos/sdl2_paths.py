Import("env")
import sys
import os
import glob

if sys.platform.startswith("darwin"):
    sdl_include = glob.glob("/opt/homebrew/Cellar/sdl2/*/include", recursive=True)
    if sdl_include:
        print(f"Found Homebrew SDL include path: {sdl_include[0]}")
        env.Append(
            CPPPATH=sdl_include[0]
        )
    sdl_lib = glob.glob("/opt/homebrew/Cellar/sdl2/**/libSDL2.a", recursive=True)
    if sdl_lib:
        print(f"Found Homebrew SDL lib path: {sdl_lib[0]}")
        env.Append(
            LIBPATH=os.path.dirname(sdl_lib[0])
        )
