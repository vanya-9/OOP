Запуск тестов
cd lab 1
git clone https://github.com/google/googletest.git -b release-1.12.1
cd googletest
mkdir build
cd build
cmake .. -DBUILD_GMOCK=OFF
make
cd ../..
g++ -std=c++17 CircularBuffer_tets.cpp CircularBuffer.cpp googletest/build/lib/libgtest.a googletest/build/lib/libgtest_main.a -lpthread -I googletest/googletest/include && ./a.out

Отчет
g++ -std=c++17 CircularBuffer_tets.cpp CircularBuffer.cpp googletest/build/lib/libgtest.a googletest/build/lib/libgtest_main.a --coverage -lpthread -I googletest/googletest/include && ./a.out -lgtest
lcov -t "gcd" -o gcd.info -c -d . --ignore-errors inconsistent
genhtml -o report gcd.info --ignore-errors inconsistent
report/index.html
