add_executable(test_mandelbrot mandelbrot.cpp)
target_link_libraries(test_mandelbrot PUBLIC mandelbrot_lib GTest::gtest_main)

enable_testing()

add_test(test_mandelbrot test_mandelbrot)
