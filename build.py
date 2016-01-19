#!/usr/bin/python

# INFORMATION:
# This scripts compiles Glslang and SPIR-V tools to JavaScript

import os
import shutil

EXPORTED_FUNCTIONS = [
	'_gjsInitialize',
	'_gjsFinalize',
	'_gjsCompile',
	'_gjsGetSpirvData',
	'_gjsGetSpirvSize',
	'_gjsGetSpirvDisassembly',
	'_gjsDestruct',
]

def compileGlslang():
	# Fix SPIRV-Tools CMakeLists.txt file
	pathA = "externals/SPIRV-Tools/CMakeLists.txt"
	pathB = "externals/SPIRV-Tools/CMakeLists.txt.bak"
	shutil.copyfile(pathA, pathB)
	with open(pathB, 'rb') as infile, open(pathA, 'wb') as outfile:
		for line in infile:
			line = line.replace('${CMAKE_SYSTEM_NAME}', 'Linux')
			outfile.write(line)

	# CMake
	cmd = 'cmake'
	cmd += os.path.expandvars(' -DCMAKE_TOOLCHAIN_FILE=$EMSCRIPTEN/cmake/Modules/Platform/Emscripten.cmake')
	cmd += ' -DCMAKE_BUILD_TYPE=Release'
	if os.name == 'nt':
		cmd += ' -G \"MinGW Makefiles\"'
	if os.name == 'posix':
		cmd += ' -G \"Unix Makefiles\"'
	os.system(cmd + ' externals/glslang/CMakeLists.txt')
	os.system(cmd + ' externals/SPIRV-Tools/CMakeLists.txt')
	os.system(cmd + ' helper/CMakeLists.txt')

	# Make Glslang
	os.chdir('externals/glslang')
	if os.name == 'nt':
		os.system('mingw32-make')
	if os.name == 'posix':
		os.system('make')
	os.chdir('../..')
	
	# Make SPIRV-Tools
	os.chdir('externals/SPIRV-Tools')
	if os.name == 'nt':
		os.system('mingw32-make')
	if os.name == 'posix':
		os.system('make')
	os.chdir('../..')
	
	# Make Glslang.JS helper
	os.chdir('helper')
	if os.name == 'nt':
		os.system('mingw32-make')
	if os.name == 'posix':
		os.system('make')
	os.chdir('..')

	# Compile static library to JavaScript
	cmd = os.path.expandvars('$EMSCRIPTEN/em++')
	cmd += ' -O1'
	cmd += ' externals/glslang/glslang/libglslang.a'
	cmd += ' externals/glslang/glslang/OSDependent/Unix/libOSDependent.a'
	cmd += ' externals/glslang/OGLCompilersDLL/libOGLCompiler.a'
	cmd += ' externals/glslang/SPIRV/libSPIRV.a'
	cmd += ' externals/SPIRV-Tools/libSPIRV-Tools.a'
	cmd += ' helper/libglslangjs_helper.a'
	cmd += ' -s EXPORTED_FUNCTIONS=\"[\''+ '\', \''.join(EXPORTED_FUNCTIONS) +'\']\"'
	cmd += ' -o src/glslang.out.js'
	os.system(cmd)


if __name__ == "__main__":
	if os.name in ['nt', 'posix']:
		compileGlslang()		
	else:
		print "Your operating system is not supported by this script:"
		print "Please, use Emscripten to compile Glslang manually to src/glslang.out.js"
