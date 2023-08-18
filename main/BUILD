load("@rules_cc//cc:defs.bzl", "cc_binary")

load("//rules:variables.bzl", "COPTS")

cc_binary(
    name = "algorithms",
    deps = [
        "//lib:utility",
        "//lib:algorithms",
        "@benchmark//:lib"
    ],
    srcs = ["algorithms.cpp"],
    copts = COPTS,
)

cc_binary(
    name = "concurrency",
    deps = ["//lib:utility", "//lib:concurrency"],
    srcs = ["concurrency.cpp"],
    copts = COPTS,
)

cc_binary(
    name = "data_structures",
    deps = ["//lib:utility", "//lib:data_structures"],
    srcs = ["data_structures.cpp"],
    copts = COPTS,
)

cc_binary(
    name = "memory",
    srcs = ["memory.cpp"],
    deps = ["//lib:utility", "//lib:memory"],
    copts = COPTS,
)

cc_binary(
    name = "coroutines",
    srcs = ["coroutines.cpp"],
    copts = [
        "-std=c++20",
        "-Werror",
        "-fcoroutines",
    ]
)