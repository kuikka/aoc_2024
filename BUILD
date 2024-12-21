cc_library(
    name = "parser",
    hdrs = [ "src/parser.hpp" ],
    includes = [ "src" ],
    deps = [ 
        "//libs/third-party/fmt-11:fmt-11",
    ],
)

cc_binary(
    name = "day3",
    srcs = [ "src/day3.cpp"],
    deps = [ 
        "//libs/third-party/fmt-11:fmt-11",
        ":parser"
    ],
)

cc_test(
    name = "test_day3",
    srcs = [ "tests/test_day3.cpp"],
    deps = [
        ":parser",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
    data = [ "inputs/day3.txt" ]
)

cc_test(
    name = "test_day4",
    srcs = [ "tests/test_day4.cpp"],
    deps = [
        "@googletest//:gtest",
        "@googletest//:gtest_main",
        "//libs/third-party/fmt-11:fmt-11",
    ],
    data = [ "inputs/day4.txt" ]
)