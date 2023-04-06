const std = @import("std");
//const Builder = @import("std").build.Builder;

pub fn build(b: *std.Build) void {
    const optimize = b.standardOptimizeOption(.{});
    const lib = b.addSharedLibrary(.{
        .name = "engine",
        .target = .{},
        .root_source_file = .{ .path = "engine/engine.zig" },
        .optimize = optimize,
    });
    lib.install();
}
