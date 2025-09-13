const std = @import("std");

const cpp_flags: []const []const u8 = &.{
    "-std=c++23",
    "-Wall",
    "-Werror",
    "-Wextra",
    "-pedantic",
};

pub fn build(b: *std.Build) !void {
    defer _ = @import("cdb").addStep(b, "cdb");

    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const libcx_mod = b.addModule("libcx", .{
        .target = target,
        .optimize = optimize,
        .link_libc = true,
    });

    var libcxSourceFiles: std.ArrayListUnmanaged([]const u8) = .empty;
    try libcxSourceFiles.appendSlice(
        b.allocator,
        &.{
            "alloc.cpp",
            "arena.cpp",
            "math.cpp",
            "program.cpp",

            "io.cpp",
            "file.cpp",
        },
    );

    switch (target.result.os.tag) {
        .windows => {
            try libcxSourceFiles.appendSlice(b.allocator, &.{
                "windows/time.cpp",
                "windows/thread.cpp",
                "windows/program.cpp",

                "windows/io.cpp",
                "windows/io/file.cpp",
                "windows/io/dir.cpp",
            });

            if (optimize == .Debug) {
                libcx_mod.linkSystemLibrary("dbghelp", .{});
            }
        },
        else => @panic("Unsupported OS"),
    }

    libcx_mod.addCSourceFiles(.{
        .root = b.path("src"),
        .files = libcxSourceFiles.items,
        .flags = cpp_flags ++ .{
            "-fno-exceptions",
            "-fno-rtti",
        },
    });
    libcx_mod.addIncludePath(b.path("src"));
    libcx_mod.addIncludePath(b.path("include"));

    const libcx = b.addLibrary(.{ .name = "libcx", .root_module = libcx_mod });
    libcx.installHeadersDirectory(b.path("include/cx"), "cx", .{});

    b.installArtifact(libcx);

    const libcx_tests = b.addExecutable(.{
        .name = "libcx_tests",
        .root_module = b.addModule("libcx_tests", .{
            .target = target,
            .optimize = optimize,
        }),
    });

    libcx_tests.addCSourceFiles(.{
        .root = b.path("tests"),
        .files = &.{
            "arena.cpp",
            "alloc.cpp",
            "mem.cpp",
            "array_list.cpp",
            "time.cpp",
            "math.cpp",
            "either.cpp",
            "io.cpp",
        },
        .flags = cpp_flags ++ .{
            "-include",
            "tests/pch.h",
        },
    });
    libcx_tests.linkLibrary(libcx);

    const catch2 = b.lazyDependency("catch2", .{
        .target = target,
        .optimize = optimize,
    }) orelse return;
    libcx_tests.linkLibrary(catch2.artifact("Catch2"));
    libcx_tests.linkLibrary(catch2.artifact("Catch2WithMain"));

    b.installArtifact(libcx_tests);

    const run_tests = b.addRunArtifact(libcx_tests);

    const test_step = b.step("test", "Run unit tests");
    test_step.dependOn(&run_tests.step);
}
