load("@com_github_grpc_grpc//bazel:grpc_build_system.bzl", "grpc_proto_library")

grpc_proto_library(
    name = "gcs_grpc_proto",
    srcs = [":gcs.proto"],
)

cc_library(
    name = "wrapper",
    hdrs = ["wrapper.h"],
    srcs = ["wrapper.cc"],
    deps = [
        ":gcs_grpc_proto",
        "@google_cloud_cpp//:experimental-storage-grpc",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/status",
        "@com_github_grpc_grpc//:grpc++",
    ],
)

cc_library(
    name = "constants",
    srcs = ["constants.h"],
    deps = [
        "@com_google_absl//absl/strings",
    ],
)

cc_binary(
    name = "wrapper_main",
    srcs = ["wrapper_main.cc"],
    deps = [
        ":wrapper",
        ":constants",
    ],
    visibility = ["//visibility:public"],
)

## TODO Uncomment to test
# cc_test(
#   name = "wrapper_test",
#   srcs = ["wrapper_test.cc"],
#   deps = [
#         "@com_google_googletest//:gtest_main",
#         ":wrapper",
#     ],
# )