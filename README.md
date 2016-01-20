Glslang.js
==========
[![Last Release](https://img.shields.io/badge/version-1.0.0-brightgreen.svg?style=flat)](https://github.com/AlexAltea/glslang.js/releases)

Real-time GLSL to SPIR-V translator. Powered by [Glslang](https://www.opengl.org/sdk/tools/glslang/) and Khronos' [SPIR-V Tools](https://github.com/KhronosGroup/SPIRV-Tools).

Compiled into JavaScript via [Emscripten](https://github.com/kripken/emscripten).

## Installation
To install the Glslang.js install in your web application, include it with:
```html
<script src="glslang.min.js"></script>
```
or installer through the Bower command:
```
bower install glslangjs
```

## Usage                                                      
```javascript
// Input: GLSL source code and shader type
var type = glslang.EShLangFragment;
var source = `
    #version 150
    out vec4 finalColor
    void main() {
        finalColor = vec4(1.0, 1.0, 1.0, 1.0);
    }`;

// Initialize Glslang
glslang.initialize();

// Compile shader
var shader = new glslang.Shader(type, source);

// Output: SPIR-V binary and disassembly
var binary = shader.data();
var disassembly = shader.disasm();

// Delete shader
shader.delete();

// Finalize Glslang
glslang.finalize();
```

## Building
To build the Glslang.js library, clone the *master* branch of this repository, and do the following:

1. Initialize the *Glslang* and *SPIR-V Tools* submodules: `git submodule update --init`.

2. Install the development and client dependencies with: `npm install` and `bower install`.

3. Install the lastest [Python 2.x (64-bit)](https://www.python.org/downloads/), [CMake](http://www.cmake.org/download/) and the [Emscripten SDK](http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html). Follow the respective instructions and make sure all environment variables are configured correctly. Under Windows [MinGW](http://www.mingw.org/) (specifically *mingw32-make*) is required.

4. Finally, build the source with: `grunt build`.
