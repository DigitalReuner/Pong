mkdir build/shader
./extern/vulkansdk/x86_64/bin/glslc src/shader/shader.frag -o build/shader/frag.spv
./extern/vulkansdk/x86_64/bin/glslc src/shader/shader.vert -o build/shader/vert.spv