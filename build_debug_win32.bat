echo "-- Initializing git submodules -- "
git submodule update --init --recursive
md build_debug_win32
cd build_debug_win32
cmake -DCMAKE_GENERATOR_PLATFORM=WIN32 -DCMAKE_BUILD_TYPE=Debug -DBoost_NO_SYSTEM_PATHS=TRUE .. -Wdev
cmake --build . --config Debug
pause