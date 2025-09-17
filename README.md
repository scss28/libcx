# libcx
Minimalistic template library for C++, meant to be used as a replacement for the STL. Takes inspiration from standard libraries of modern low-level languages such as Zig or Rust.

## Getting started
### build.zig <sub>(recommended)</sub>

#### Prerequisites
- Zig (0.15.1)

#### Building
```
zig build
```
> **Tip:** Run `zig build --help` to see available options.

#### Testing
```
zig build test
```

#### Using the library in your project
First make a folder, create a `build.zig` inside and paste-in the code below:
```Rust
const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe_mod = b.createModule(.{
        .target = target,
        .optimize = optimize,
    });

    exe_mod.addCSourceFiles(.{
        .root = b.path("src"),
        // Add new C++ files here.   <------------- IMPORTANT
        .files = &.{
            "main.cpp",
        },
        .flags = &.{"-std=c++23"},
    });

    const libcx = b.dependency("libcx", .{ .target = target, .optimize = optimize });
    exe_mod.linkLibrary(libcx.artifact("libcx"));

    const exe = b.addExecutable(.{
        .name = "a_very_amazing_application",
        .root_module = exe_mod,
    });

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());

    const run_step = b.step("run", "Run the application");
    run_step.dependOn(&run_cmd.step);
}
```

Then run `zig fetch --save git+https://github.com/scss28/libcx` to get the library.
> *This should also create `build.zig.zon` which contains project specific information.*

Once the library gets fetched, create a `src/main.cpp` file and you're done! \
Use `zig build` to build and `zig build run` to run.

### CMake
> ⚠️ **Warning:** This option is not actively updated and may stop working at any point in time.

#### Prerequisites
- C++ (version 23) compiler.
- CMake

#### Building
Generate the project files:
```
mkdir build
cd build
cmake ..
```
Then `cmake build .`

## Documentation
Currently the documentation may only be generated using `doxygen`.

## TODO

### cx
- [ ] Stack traces for cx::panic (include/cx/program.h).

### cx::io
- [ ] Format printing to files. 
    - [ ] cx::fmt namespace providing formatting integers, floats etc.
    - [ ] Writer struct?

### cx::math
- [ ] math::Matrix implementation.
