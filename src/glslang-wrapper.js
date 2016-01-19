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
    
    // Messages
    EShMsgDefault              : 0x0000,  // Default is to give all required errors and extra warnings
    EShMsgRelaxedErrors        : 0x0001,  // Be liberal in accepting input
    EShMsgSuppressWarnings     : 0x0002,  // Suppress all warnings, except those required by the specification
    EShMsgAST                  : 0x0004,  // Print the AST intermediate representation
    EShMsgSpvRules             : 0x0008,  // Issue messages for SPIR-V generation
    EShMsgVulkanRules          : 0x0010,  // Issue messages for Vulkan requirements of GLSL for SPIR-V
    EShMsgOnlyPreprocessor     : 0x0020,  // Only print out errors produced by the preprocessor

    initialize: function () {
        var success = Module.ccall('gjsInitialize');
        if (!success) {
            console.error('Glslang.js: Function gjsInitialize failed');
        }
    },

    finalize: function () {
        Module.ccall('gjsFinalize');
    },

    Shader: function (type, source) {
        this.type = type;
        this.source = source;
        this.handle = 0;
        
        this.delete = function () {
            Module.ccall('gjsDestruct', 'void', ['pointer'], [this.handle]);
        };

        this.data = function () {
            var data = Module.ccall('gjsGetSpirvData', 'number', ['pointer'], [this.handle]);
            var size = Module.ccall('gjsGetSpirvSize', 'number', ['pointer'], [this.handle]);
            var buffer = new Uint8Array(Module.HEAPU8.buffer, data, size);
            return buffer;
        };

        this.disasm = function () {
            var string = Module.ccall('gjsGetSpirvDisassembly', 'string', ['pointer'], [this.handle]);
            return string;
        };

        // Constructor
        var options = 0;
        var messages = glslang.EShMsgSpvRules | glslang.EShMsgVulkanRules;
        this.handle = Module.ccall('gjsCompile', 'pointer', ['string', 'number', 'number', 'number'], [source, type, options, messages]);
        if (!this.handle) {
            console.log("Glslang.JS: Could not compile shader");
        }
    }
};
