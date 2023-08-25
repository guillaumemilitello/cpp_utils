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
    name = "concurrency",
    hdrs = glob(["concurrency/*.hpp"]),
    includes = ["include"],
    strip_include_prefix = "concurrency",
    visibility = ["//main:__pkg__"],
    copts = COPTS,
)

cc_library(
    name = "data_structures",
    hdrs = glob(["data_structures/*.hpp"]),
    includes = ["include"],
    strip_include_prefix = "data_structures",
    visibility = ["//main:__pkg__"],
    copts = COPTS,
)

cc_library(
    name = "memory",
    hdrs = glob(["memory/*.hpp"]),
    includes = ["include"],
    strip_include_prefix = "memory",
    visibility = ["//main:__pkg__"],
    copts = COPTS,
)

cc_library(
    name = "others",
    hdrs = glob(["others/*.hpp"]),
    includes = ["include"],
    strip_include_prefix = "others",
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