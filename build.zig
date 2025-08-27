const std = @import("std");

const cpp_flags: []const []const u8 = &.{
    "-std=c++23",
    "-Wall",
    "-Werror",
    "-Wextra",
    "-pedantic",
};

pub fn build(b: *std.Build) void {
    defer _ = @import("cdb").addStep(b, "cdb");

    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const libcx_mod = b.addModule("libcx", .{
        .target = target,
        .optimize = optimize,
        .link_libc = true,
    });

    var libcxSourceFiles: std.ArrayListUnmanaged([]const u8) = .empty;
    libcxSourceFiles.appendSlice(b.allocator, &.{
        "src/alloc.cpp",
        "src/arena.cpp",
        "src/math.cpp",
    }) catch @panic("OOM");

    switch (target.result.os.tag) {
        .windows => {
            libcxSourceFiles.appendSlice(b.allocator, &.{
                "src/windows/time.cpp",
                "src/windows/thread.cpp",
            }) catch @panic("OOM");
        },
        .linux => {
            @panic("TODO");
        },
        else => @panic("Unsupported OS"),
    }

    libcx_mod.addCSourceFiles(.{
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
        .files = &.{
            "tests/arena.cpp",
            "tests/alloc.cpp",
            "tests/mem.cpp",
            "tests/array_list.cpp",
            "tests/time.cpp",
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
