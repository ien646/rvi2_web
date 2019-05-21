echo "-- Initializing git submodules -- "
git submodule update --init --recursive
md build_release_win32
cd build_release_win32
cmake -DCMAKE_GENERATOR_PLATFORM=x64 -DCMAKE_BUILD_TYPE=Release -DBoost_NO_SYSTEM_PATHS=TRUE .. -Wdev
cmake --build . --config Release
pause