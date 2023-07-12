# GCC support can be specified at major, minor, or micro version
# (e.g. 8, 8.2 or 8.2.0).
# See https://hub.docker.com/r/library/gcc/ for all supported GCC
# tags from Docker Hub.
# See https://docs.docker.com/samples/library/gcc/ for more on how to use this image
FROM mcr.microsoft.com/devcontainers/cpp:latest

# These commands copy your files into the specified directory in the image
# and set that as the working location
# COPY . /usr/src/myapp
# WORKDIR /usr/src/myapp

# Install Google Benchmark
#RUN sudo apt-get update && apt-get install libbenchmark-dev -y
CMD ["/workspaces/"]
RUN sudo git clone https://github.com/google/benchmark.git -b v1.8.2 \
    && cd benchmark \
    && cmake -E make_directory "build" \
    && cmake -DBENCHMARK_USE_BUNDLED_GTEST=OFF -DBENCHMARK_ENABLE_GTEST_TESTS=OFF -BENCHMARK_ENABLE_TESTING=OFF -DCMAKE_BUILD_TYPE=Release -S . -B "build" \
    && cmake --build "build" --config Release  --target install

# Install Bazel
#RUN sudo apt-get update && apt-get install libbenchmark-dev -y
CMD ["/workspaces/"]
RUN curl https://bazel.build/bazel-release.pub.gpg | sudo apt-key add - \
    && echo "deb [arch=amd64] https://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list \
    && sudo apt update && sudo apt install bazel

LABEL Name=cpp_utils Version=0.0.1
