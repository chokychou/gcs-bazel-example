# Generate sha256:
#   shasum -a 256 *.tar.gz
workspace(name = "news-app-project")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Fetch the Google Cloud C++ libraries.
#       https://github.com/googleapis/google-cloud-cpp
http_archive(
    name = "google_cloud_cpp",
    sha256 = "371d01b03c7e2604d671b8fa1c86710abe3b524a78bc2705a6bb4de715696755",
    strip_prefix = "google-cloud-cpp-2.14.0",
    url = "https://github.com/googleapis/google-cloud-cpp/archive/v2.14.0.tar.gz",
)

# And load indirect dependencies due to
#       https://github.com/bazelbuild/bazel/issues/1943
load("@google_cloud_cpp//bazel:google_cloud_cpp_deps.bzl", "google_cloud_cpp_deps")

google_cloud_cpp_deps()

load("@com_google_googleapis//:repository_rules.bzl", "switched_rules_by_language")

switched_rules_by_language(
    name = "com_google_googleapis_imports",
    cc = True,
    python = True,
    grpc = True,
)

# Import grpc rules.
#       https://github.com/grpc/grpc
http_archive(
    name = "com_github_grpc_grpc",
    sha256 = "931f07db9d48cff6a6007c1033ba6d691fe655bea2765444bc1ad974dfc840aa",
    strip_prefix = "grpc-1.56.2",
    urls = ["https://github.com/grpc/grpc/archive/v1.56.2.tar.gz"],
)

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

grpc_deps()

load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")

grpc_extra_deps()

load("@com_github_grpc_grpc//bazel:grpc_python_deps.bzl", "grpc_python_deps")

grpc_python_deps()


# GoogleTest/GoogleMock framework. Used by most unit-tests.
#       https://github.com/google/googletest
http_archive(
  name = "com_google_googletest",  # 2023-08-02T16:45:10Z
  sha256 = "c4f675500e09da97fd5a2b9c3fdadf48de858a036db565d52e6835c96eeea147",
  strip_prefix = "googletest-843976e4f582ccb76cf87e0f128585324335779b",
  # Keep this URL in sync with ABSL_GOOGLETEST_COMMIT in ci/cmake_common.sh.
  urls = ["https://github.com/google/googletest/archive/843976e4f582ccb76cf87e0f128585324335779b.zip"],
)

# RE2 (the regular expression library used by GoogleTest)
#       https://github.com/google/re2
http_archive(
    name = "com_googlesource_code_re2",  # 2023-03-17T11:36:51Z
    sha256 = "cb8b5312a65f2598954545a76e8bce913f35fbb3a21a5c88797a4448e9f9b9d9",
    strip_prefix = "re2-578843a516fd1da7084ae46209a75f3613b6065e",
    urls = ["https://github.com/google/re2/archive/578843a516fd1da7084ae46209a75f3613b6065e.zip"],
)

# Google benchmark.
#       https://github.com/google/benchmark
http_archive(
    name = "com_github_google_benchmark",  # 2023-08-01T07:47:09Z
    sha256 = "db1e39ee71dc38aa7e57ed007f2c8b3bb59e13656435974781a9dc0617d75cc9",
    strip_prefix = "benchmark-02a354f3f323ae8256948e1dc77ddcb1dfc297da",
    urls = ["https://github.com/google/benchmark/archive/02a354f3f323ae8256948e1dc77ddcb1dfc297da.zip"],
)

# Bazel Skylib.
#       https://github.com/bazelbuild/bazel-skylib
http_archive(
  name = "bazel_skylib",  # 2023-05-31T19:24:07Z
  sha256 = "08c0386f45821ce246bbbf77503c973246ed6ee5c3463e41efc197fa9bc3a7f4",
  strip_prefix = "bazel-skylib-288731ef9f7f688932bd50e704a91a45ec185f9b",
  urls = ["https://github.com/bazelbuild/bazel-skylib/archive/288731ef9f7f688932bd50e704a91a45ec185f9b.zip"],
)

# Cpp absl package.
#       https://github.com/abseil/abseil-cpp
http_archive(
  name = "com_google_absl",
  urls = ["https://github.com/abseil/abseil-cpp/archive/98eb410c93ad059f9bba1bf43f5bb916fc92a5ea.zip"],
  strip_prefix = "abseil-cpp-98eb410c93ad059f9bba1bf43f5bb916fc92a5ea",
)
