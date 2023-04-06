const std = @import("std");

export fn run_zig() void {
    const stdout = std.io.getStdOut().writer();
    stdout.print("Hello, {s}!\n", .{"world"}) catch unreachable;
}
