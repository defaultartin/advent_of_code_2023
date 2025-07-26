const std = @import("std");

fn isArrayZero(arr: []const i32) bool {
    for (arr) |element| {
        if (element != 0) {
            return false;
        }
    }
    return true;
}

fn getNextValue(arr: []const i32) !i32 {
    if (isArrayZero(arr)) {
        return 0;
    }
    var last: i32 = arr[arr.len - 1];

    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();

    const allocator = gpa.allocator();

    var diffs = try allocator.alloc(i32, arr.len - 1);
    defer allocator.free(diffs);

    for (1..arr.len) |i| {
        const diff = arr[i] - arr[i - 1];
        diffs[i - 1] = diff;
    }
    last += try getNextValue(diffs);

    return last;
}

fn getFirstValue(arr: []const i32) !i32 {
    if (isArrayZero(arr)) {
        return 0;
    }
    var first: i32 = arr[0];

    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();

    const allocator = gpa.allocator();

    var diffs = try allocator.alloc(i32, arr.len - 1);
    defer allocator.free(diffs);

    for (1..arr.len) |i| {
        const diff = arr[i] - arr[i - 1];
        diffs[i - 1] = diff;
    }
    first -= try getFirstValue(diffs);

    return first;
}

pub fn main() !void {
    var file = try std.fs.cwd().openFile("input.txt", .{});
    defer file.close();

    var bufReader = std.io.bufferedReader(file.reader());
    var inStream = bufReader.reader();

    var part1: i32 = 0;
    var part2: i32 = 0;

    var buf: [1024]u8 = undefined;
    while (try inStream.readUntilDelimiterOrEof(&buf, '\n')) |line| {
        var strs = std.mem.splitScalar(u8, line, ' ');
        var count: u8 = 0;
        while (strs.next()) |_| {
            count += 1;
        }

        var gpa = std.heap.GeneralPurposeAllocator(.{}){};
        defer _ = gpa.deinit();

        const allocator = gpa.allocator();

        var nums = try allocator.alloc(i32, count);
        defer allocator.free(nums);

        strs = std.mem.splitScalar(u8, line, ' ');
        var i: u8 = 0;
        while (strs.next()) |n| {
            nums[i] = try std.fmt.parseInt(i32, n, 10);
            i += 1;
        }
        part1 += try getNextValue(nums);
        part2 += try getFirstValue(nums);
    }

    std.debug.print("Part 1: {d}\n", .{part1});
    std.debug.print("Part 2: {d}\n", .{part2});
}