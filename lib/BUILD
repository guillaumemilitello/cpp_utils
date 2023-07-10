load("@rules_cc//cc:defs.bzl", "cc_library")

load("//rules:variables.bzl", "COPTS")

cc_library(
    name = "algorithms",
    hdrs = ["algorithms/searching.hpp"],
    includes = ["include"],
    strip_include_prefix = "algorithms",
    visibility = ["//main:__pkg__"],
    copts = COPTS,
)

cc_library(
    name = "utility",
    hdrs = ["utility/stream.hpp"],
    includes = ["include"],
    strip_include_prefix = "utility",
    visibility = ["//main:__pkg__"],
    copts = COPTS,
)