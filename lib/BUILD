load("@rules_cc//cc:defs.bzl", "cc_library")

load("//rules:variables.bzl", "COPTS")

cc_library(
    name = "algorithms",
    hdrs = glob(["algorithms/*.hpp"]),
    includes = ["include"],
    strip_include_prefix = "algorithms",
    visibility = ["//main:__pkg__"],
    copts = COPTS,
)

cc_library(
    name = "utility",
    hdrs = glob(["utility/*.hpp"]),
    includes = ["include"],
    strip_include_prefix = "utility",
    visibility = ["//main:__pkg__"],
    copts = COPTS,
)