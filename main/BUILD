load("@rules_cc//cc:defs.bzl", "cc_binary")

load("//rules:variables.bzl", "COPTS")

cc_binary(
    name = "algorithms",
    deps = ["//lib:utility", "//lib:algorithms"],
    srcs = ["algorithms.cpp"],
    copts = COPTS,
)
