/**
 * (c) 2016 Glslang.JS
 * Wrapper made by Alexandro Sanchez Bach.
 */

var glslang = {
    // Return values
    RET_ERROR: 0,
    RET_SUCCESS: 1,
    
    // Shader languages
    EShLangVertex              : 0,  // Vertex
    EShLangTessControl         : 1,  // Tesselation control
    EShLangTessEvaluation      : 2,  // Tesselation evaluation
    EShLangGeometry            : 3,  // Geometry
    EShLangFragment            : 4,  // Fragment
    EShLangCompute             : 5,  // Compute
    
    // Options
    EOptionNone                : 0x0000,
    EOptionIntermediate        : 0x0001,
    EOptionSuppressInfolog     : 0x0002,
    EOptionMemoryLeakMode      : 0x0004,
    EOptionRelaxedErrors       : 0x0008,
    EOptionGiveWarnings        : 0x0010,
    EOptionLinkProgram         : 0x0020,
    EOptionMultiThreaded       : 0x0040,
    EOptionDumpConfig          : 0x0080,
    EOptionDumpReflection      : 0x0100,
    EOptionSuppressWarnings    : 0x0200,
    EOptionDumpVersions        : 0x0400,
    EOptionSpv                 : 0x0800,
    EOptionHumanReadableSpv    : 0x1000,
    EOptionVulkanRules         : 0x2000,
    EOptionDefaultDesktop      : 0x4000,
    EOptionOutputPreprocessed  : 0x8000,
    
    // Messages
    EShMsgDefault              : 0x0000,  // Default is to give all required errors and extra warnings
    EShMsgRelaxedErrors        : 0x0001,  // Be liberal in accepting input
    EShMsgSuppressWarnings     : 0x0002,  // Suppress all warnings, except those required by the specification
    EShMsgAST                  : 0x0004,  // Print the AST intermediate representation
    EShMsgSpvRules             : 0x0008,  // Issue messages for SPIR-V generation
    EShMsgVulkanRules          : 0x0010,  // Issue messages for Vulkan requirements of GLSL for SPIR-V
    EShMsgOnlyPreprocessor     : 0x0020,  // Only print out errors produced by the preprocessor

    /**
     * Glslang compiler
     */
    Compiler: function (lang) {
        this.lang = lang;
    },
};
