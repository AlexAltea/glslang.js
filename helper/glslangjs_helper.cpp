/**
 * (c) 2016 Alexandro Sanchez Bach. All rights reserved.
 * Released under GPL v2 license. Read LICENSE for more details.
 */

#include "../externals/glslang/glslang/Include/ResourceLimits.h"
#include "../externals/glslang/glslang/Include/ShHandle.h"
#include "../externals/glslang/glslang/MachineIndependent/localintermediate.h"
#include "../externals/glslang/glslang/Public/ShaderLang.h"
#include "../externals/glslang/glslang/Public/ShaderLang.h"
#include "../externals/glslang/SPIRV/GlslangToSpv.h"
#include "../externals/SPIRV-Tools/include/libspirv/libspirv.h"

#include <iostream>
#include <vector>

TBuiltInResource resources;

struct TObject {
    std::vector<unsigned int> words;
    spv_text text;

    ~TObject() {
        spvTextDestroy(text);
    }
};


#ifdef __cplusplus
extern "C" {
#endif

bool gjsInitialize();
void gjsFinalize();
TObject* gjsCompile(const char* source, EShLanguage stage, int options, EShMessages messages);
const void* gjsGetSpirvData(const TObject* spirv);
size_t gjsGetSpirvSize(const TObject* spirv);
const char* gjsGetSpirvDisassembly(TObject* spirv);
void gjsDestruct(TObject* spirv);

#ifdef __cplusplus
}  // end extern "C"
#endif

bool gjsInitialize() {
    if (!glslang::InitializeProcess()) {
        return false;
    }

    // Default configuration
    resources.maxLights = 32;
    resources.maxClipPlanes = 6;
    resources.maxTextureUnits = 32;
    resources.maxTextureCoords = 32;
    resources.maxVertexAttribs = 64;
    resources.maxVertexUniformComponents = 4096;
    resources.maxVaryingFloats = 64;
    resources.maxVertexTextureImageUnits = 32;
    resources.maxCombinedTextureImageUnits = 80;
    resources.maxTextureImageUnits = 32;
    resources.maxFragmentUniformComponents = 4096;
    resources.maxDrawBuffers = 32;
    resources.maxVertexUniformVectors = 128;
    resources.maxVaryingVectors = 8;
    resources.maxFragmentUniformVectors = 16;
    resources.maxVertexOutputVectors = 16;
    resources.maxFragmentInputVectors = 15;
    resources.minProgramTexelOffset = -8;
    resources.maxProgramTexelOffset = 7;
    resources.maxClipDistances = 8;
    resources.maxComputeWorkGroupCountX = 65535;
    resources.maxComputeWorkGroupCountY = 65535;
    resources.maxComputeWorkGroupCountZ = 65535;
    resources.maxComputeWorkGroupSizeX = 1024;
    resources.maxComputeWorkGroupSizeY = 1024;
    resources.maxComputeWorkGroupSizeZ = 64;
    resources.maxComputeUniformComponents = 1024;
    resources.maxComputeTextureImageUnits = 16;
    resources.maxComputeImageUniforms = 8;
    resources.maxComputeAtomicCounters = 8;
    resources.maxComputeAtomicCounterBuffers = 1;
    resources.maxVaryingComponents = 60; 
    resources.maxVertexOutputComponents = 64;
    resources.maxGeometryInputComponents = 64;
    resources.maxGeometryOutputComponents = 128;
    resources.maxFragmentInputComponents = 128;
    resources.maxImageUnits = 8;
    resources.maxCombinedImageUnitsAndFragmentOutputs = 8;
    resources.maxCombinedShaderOutputResources = 8;
    resources.maxImageSamples = 0;
    resources.maxVertexImageUniforms = 0;
    resources.maxTessControlImageUniforms = 0;
    resources.maxTessEvaluationImageUniforms = 0;
    resources.maxGeometryImageUniforms = 0;
    resources.maxFragmentImageUniforms = 8;
    resources.maxCombinedImageUniforms = 8;
    resources.maxGeometryTextureImageUnits = 16;
    resources.maxGeometryOutputVertices = 256;
    resources.maxGeometryTotalOutputComponents = 1024;
    resources.maxGeometryUniformComponents = 1024;
    resources.maxGeometryVaryingComponents = 64;
    resources.maxTessControlInputComponents = 128;
    resources.maxTessControlOutputComponents = 128;
    resources.maxTessControlTextureImageUnits = 16;
    resources.maxTessControlUniformComponents = 1024;
    resources.maxTessControlTotalOutputComponents = 4096;
    resources.maxTessEvaluationInputComponents = 128;
    resources.maxTessEvaluationOutputComponents = 128;
    resources.maxTessEvaluationTextureImageUnits = 16;
    resources.maxTessEvaluationUniformComponents = 1024;
    resources.maxTessPatchComponents = 120;
    resources.maxPatchVertices = 32;
    resources.maxTessGenLevel = 64;
    resources.maxViewports = 16;
    resources.maxVertexAtomicCounters = 0;
    resources.maxTessControlAtomicCounters = 0;
    resources.maxTessEvaluationAtomicCounters = 0;
    resources.maxGeometryAtomicCounters = 0;
    resources.maxFragmentAtomicCounters = 8;
    resources.maxCombinedAtomicCounters = 8;
    resources.maxAtomicCounterBindings = 1;
    resources.maxVertexAtomicCounterBuffers = 0;
    resources.maxTessControlAtomicCounterBuffers = 0;
    resources.maxTessEvaluationAtomicCounterBuffers = 0;
    resources.maxGeometryAtomicCounterBuffers = 0;
    resources.maxFragmentAtomicCounterBuffers = 1;
    resources.maxCombinedAtomicCounterBuffers = 1;
    resources.maxAtomicCounterBufferSize = 16384;
    resources.maxTransformFeedbackBuffers = 4;
    resources.maxTransformFeedbackInterleavedComponents = 64;
    resources.maxCullDistances = 8;
    resources.maxCombinedClipAndCullDistances = 8;
    resources.maxSamples = 4;
    resources.limits.nonInductiveForLoops = 1;
    resources.limits.whileLoops = 1;
    resources.limits.doWhileLoops = 1;
    resources.limits.generalUniformIndexing = 1;
    resources.limits.generalAttributeMatrixVectorIndexing = 1;
    resources.limits.generalVaryingIndexing = 1;
    resources.limits.generalSamplerIndexing = 1;
    resources.limits.generalVariableIndexing = 1;
    resources.limits.generalConstantMatrixVectorIndexing = 1;

    return true;
}

void gjsFinalize() {
    glslang::FinalizeProcess();
}

TObject* gjsCompile(const char* source, EShLanguage stage, int options, EShMessages messages) {
    glslang::TProgram* program = new glslang::TProgram();
    glslang::TShader* shader = new glslang::TShader(stage);

    // Parse GLSL
    shader->setStrings(&source, 1);
    if (!shader->parse(&resources, 110, false, messages)) {
        return nullptr;
    }
    program->addShader(shader);
    program->link(messages);

    // Emit SPIR-V
    TObject* spirv = new TObject();
    glslang::GlslangToSpv(*program->getIntermediate(stage), spirv->words);
    delete program;
    delete shader;

    return spirv;
}

const void* gjsGetSpirvData(const TObject* spirv) {
    return spirv->words.data();
}

size_t gjsGetSpirvSize(const TObject* spirv) {
    return spirv->words.size() * sizeof(unsigned int);
}

const char* gjsGetSpirvDisassembly(TObject* spirv) {
    const std::vector<unsigned int>& contents = spirv->words;
    uint32_t options = SPV_BINARY_TO_TEXT_OPTION_NONE;
    spv_text& text = spirv->text;
    spv_context context = spvContextCreate();
    spv_diagnostic diagnostic = nullptr;

    spv_result_t error = spvBinaryToText(context, contents.data(), contents.size(), options, &text, &diagnostic);
    if (error) {
        return nullptr;
    }
    return text->str;
}

void gjsDestruct(TObject* spirv) {
    delete spirv;
}
