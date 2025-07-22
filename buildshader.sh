mkdir build/shader -p
./build/external/vulkansdk/x86_64/bin/glslc src/shader/shader.frag -o build/shader/frag.spv
./build/external/vulkansdk/x86_64/bin/glslc src/shader/shader.vert -o build/shader/vert.spv