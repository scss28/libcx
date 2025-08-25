const std = @import("std");

const cpp_flags: []const []const u8 = &.{
    "-std=c++23",
    "-Wall",
    "-Werror",
    "-Wextra",
    "-pedantic",
};

var artifacts: [2]*std.Build.Step.Compile = undefined;

pub fn build(b: *std.Build) void {
    defer _ = @import("cdb").addStep(b, "cdb");

    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const mod = b.addModule("libcx", .{
        .target = target,
        .optimize = optimize,
        .link_libc = true,
    });

    mod.addCSourceFiles(.{
        .files = &.{
            "src/alloc.cpp",
            "src/arena.cpp",
        },
        .flags = cpp_flags ++ .{
            "-fno-exceptions",
            "-fno-rtti",
        },
    });
    mod.addIncludePath(b.path("src"));
    mod.addIncludePath(b.path("include"));

    const lib = b.addLibrary(.{ .name = "libcx", .root_module = mod });
    lib.installHeadersDirectory(b.path("include/std"), "std", .{});

    b.installArtifact(lib);

    const tests = b.addExecutable(.{
        .name = "tests",
        .target = target,
        .optimize = optimize,
    });

    tests.addCSourceFiles(.{
        .files = &.{
            "tests/arena.cpp",
            "tests/alloc.cpp",
        },
        .flags = cpp_flags ++ .{ "-include", "tests/pch.h" },
    });
    tests.linkLibrary(lib);

    const catch2 = b.lazyDependency("catch2", .{
        .target = target,
        .optimize = optimize,
    }) orelse return;
    tests.linkLibrary(catch2.artifact("Catch2"));
    tests.linkLibrary(catch2.artifact("Catch2WithMain"));

    b.installArtifact(tests);

    const run_tests = b.addRunArtifact(tests);

    const test_step = b.step("test", "Run unit tests");
    test_step.dependOn(&run_tests.step);
}
