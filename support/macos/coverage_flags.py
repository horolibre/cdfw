Import("env")

env.Append(LINKFLAGS=["-fprofile-instr-generate",
                        "-fcoverage-mapping"])