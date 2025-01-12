Import("env")

env_name = env["PIOENV"]

def coverage_compile_flags(env, node):
    if f"{env_name}/src" in node.get_abspath():
        print(f"NEED COVERAGE FLAGS: {node.get_abspath()}")
        return env.Object(
         node,
         CCFLAGS=env["CCFLAGS"] + ["-fprofile-instr-generate", "-fcoverage-mapping"]
        )
    else:
        return node

env.AddBuildMiddleware(coverage_compile_flags)

env.Append(LINKFLAGS=["-fprofile-instr-generate",
                        "-fcoverage-mapping"])