#include "Context.hpp"

#include "Platform/SymbolLoader.hpp"

#include <stdexcept>

namespace {

decltype(&glCullFace) gCullFace;
decltype(&glFrontFace) gFrontFace;
decltype(&glHint) gHint;
decltype(&glLineWidth) gLineWidth;
decltype(&glPointSize) gPointSize;
decltype(&glPolygonMode) gPolygonMode;
decltype(&glScissor) gScissor;
decltype(&glTexParameterf) gTexParameterf;
decltype(&glTexParameterfv) gTexParameterfv;
decltype(&glTexParameteri) gTexParameteri;
decltype(&glTexParameteriv) gTexParameteriv;
decltype(&glTexImage1D) gTexImage1D;
decltype(&glTexImage2D) gTexImage2D;
decltype(&glDrawBuffer) gDrawBuffer;
decltype(&glClear) gClear;
decltype(&glClearColor) gClearColor;
decltype(&glClearStencil) gClearStencil;
decltype(&glClearDepth) gClearDepth;
decltype(&glStencilMask) gStencilMask;
decltype(&glColorMask) gColorMask;
decltype(&glDepthMask) gDepthMask;
decltype(&glDisable) gDisable;
decltype(&glEnable) gEnable;
decltype(&glFinish) gFinish;
decltype(&glFlush) gFlush;
decltype(&glBlendFunc) gBlendFunc;
decltype(&glLogicOp) gLogicOp;
decltype(&glStencilFunc) gStencilFunc;
decltype(&glStencilOp) gStencilOp;
decltype(&glDepthFunc) gDepthFunc;
decltype(&glPixelStoref) gPixelStoref;
decltype(&glPixelStorei) gPixelStorei;
decltype(&glReadBuffer) gReadBuffer;
decltype(&glReadPixels) gReadPixels;
decltype(&glGetBooleanv) gGetBooleanv;
decltype(&glGetDoublev) gGetDoublev;
decltype(&glGetError) gGetError;
decltype(&glGetFloatv) gGetFloatv;
decltype(&glGetIntegerv) gGetIntegerv;
decltype(&glGetString) gGetString;
decltype(&glGetTexImage) gGetTexImage;
decltype(&glGetTexParameterfv) gGetTexParameterfv;
decltype(&glGetTexParameteriv) gGetTexParameteriv;
decltype(&glGetTexLevelParameterfv) gGetTexLevelParameterfv;
decltype(&glGetTexLevelParameteriv) gGetTexLevelParameteriv;
decltype(&glIsEnabled) gIsEnabled;
decltype(&glDepthRange) gDepthRange;
decltype(&glViewport) gViewport;
decltype(&glDrawArrays) gDrawArrays;
decltype(&glDrawElements) gDrawElements;
decltype(&glGetPointerv) gGetPointerv;
decltype(&glPolygonOffset) gPolygonOffset;
decltype(&glCopyTexImage1D) gCopyTexImage1D;
decltype(&glCopyTexImage2D) gCopyTexImage2D;
decltype(&glCopyTexSubImage1D) gCopyTexSubImage1D;
decltype(&glCopyTexSubImage2D) gCopyTexSubImage2D;
decltype(&glTexSubImage1D) gTexSubImage1D;
decltype(&glTexSubImage2D) gTexSubImage2D;
decltype(&glBindTexture) gBindTexture;
decltype(&glDeleteTextures) gDeleteTextures;
decltype(&glGenTextures) gGenTextures;
decltype(&glIsTexture) gIsTexture;
decltype(&glBlendColor) gBlendColor;
decltype(&glBlendEquation) gBlendEquation;
decltype(&glDrawRangeElements) gDrawRangeElements;
decltype(&glTexImage3D) gTexImage3D;
decltype(&glTexSubImage3D) gTexSubImage3D;
decltype(&glCopyTexSubImage3D) gCopyTexSubImage3D;
decltype(&glActiveTexture) gActiveTexture;
decltype(&glSampleCoverage) gSampleCoverage;
decltype(&glCompressedTexImage3D) gCompressedTexImage3D;
decltype(&glCompressedTexImage2D) gCompressedTexImage2D;
decltype(&glCompressedTexImage1D) gCompressedTexImage1D;
decltype(&glCompressedTexSubImage3D) gCompressedTexSubImage3D;
decltype(&glCompressedTexSubImage2D) gCompressedTexSubImage2D;
decltype(&glCompressedTexSubImage1D) gCompressedTexSubImage1D;
decltype(&glGetCompressedTexImage) gGetCompressedTexImage;
decltype(&glBlendFuncSeparate) gBlendFuncSeparate;
decltype(&glMultiDrawArrays) gMultiDrawArrays;
decltype(&glMultiDrawElements) gMultiDrawElements;
decltype(&glPointParameterf) gPointParameterf;
decltype(&glPointParameterfv) gPointParameterfv;
decltype(&glPointParameteri) gPointParameteri;
decltype(&glPointParameteriv) gPointParameteriv;
decltype(&glGenQueries) gGenQueries;
decltype(&glDeleteQueries) gDeleteQueries;
decltype(&glIsQuery) gIsQuery;
decltype(&glBeginQuery) gBeginQuery;
decltype(&glEndQuery) gEndQuery;
decltype(&glGetQueryiv) gGetQueryiv;
decltype(&glGetQueryObjectiv) gGetQueryObjectiv;
decltype(&glGetQueryObjectuiv) gGetQueryObjectuiv;
decltype(&glVertexAttribP1ui) gVertexAttribP1ui;
decltype(&glVertexAttribP1uiv) gVertexAttribP1uiv;
decltype(&glVertexAttribP2ui) gVertexAttribP2ui;
decltype(&glVertexAttribP2uiv) gVertexAttribP2uiv;
decltype(&glVertexAttribP3ui) gVertexAttribP3ui;
decltype(&glVertexAttribP3uiv) gVertexAttribP3uiv;
decltype(&glVertexAttribP4ui) gVertexAttribP4ui;
decltype(&glVertexAttribP4uiv) gVertexAttribP4uiv;
decltype(&glBindBuffer) gBindBuffer;
decltype(&glDeleteBuffers) gDeleteBuffers;
decltype(&glGenBuffers) gGenBuffers;
decltype(&glIsBuffer) gIsBuffer;
decltype(&glBufferData) gBufferData;
decltype(&glBufferSubData) gBufferSubData;
decltype(&glGetBufferSubData) gGetBufferSubData;
decltype(&glMapBuffer) gMapBuffer;
decltype(&glUnmapBuffer) gUnmapBuffer;
decltype(&glGetBufferParameteriv) gGetBufferParameteriv;
decltype(&glGetBufferPointerv) gGetBufferPointerv;
decltype(&glBlendEquationSeparate) gBlendEquationSeparate;
decltype(&glDrawBuffers) gDrawBuffers;
decltype(&glStencilOpSeparate) gStencilOpSeparate;
decltype(&glStencilFuncSeparate) gStencilFuncSeparate;
decltype(&glStencilMaskSeparate) gStencilMaskSeparate;
decltype(&glAttachShader) gAttachShader;
decltype(&glBindAttribLocation) gBindAttribLocation;
decltype(&glCompileShader) gCompileShader;
decltype(&glCreateProgram) gCreateProgram;
decltype(&glCreateShader) gCreateShader;
decltype(&glDeleteProgram) gDeleteProgram;
decltype(&glDeleteShader) gDeleteShader;
decltype(&glDetachShader) gDetachShader;
decltype(&glDisableVertexAttribArray) gDisableVertexAttribArray;
decltype(&glEnableVertexAttribArray) gEnableVertexAttribArray;
decltype(&glGetActiveAttrib) gGetActiveAttrib;
decltype(&glGetActiveUniform) gGetActiveUniform;
decltype(&glGetAttachedShaders) gGetAttachedShaders;
decltype(&glGetAttribLocation) gGetAttribLocation;
decltype(&glGetProgramiv) gGetProgramiv;
decltype(&glGetProgramInfoLog) gGetProgramInfoLog;
decltype(&glGetShaderiv) gGetShaderiv;
decltype(&glGetShaderInfoLog) gGetShaderInfoLog;
decltype(&glGetShaderSource) gGetShaderSource;
decltype(&glGetUniformLocation) gGetUniformLocation;
decltype(&glGetUniformfv) gGetUniformfv;
decltype(&glGetUniformiv) gGetUniformiv;
decltype(&glGetVertexAttribdv) gGetVertexAttribdv;
decltype(&glGetVertexAttribfv) gGetVertexAttribfv;
decltype(&glGetVertexAttribiv) gGetVertexAttribiv;
decltype(&glGetVertexAttribPointerv) gGetVertexAttribPointerv;
decltype(&glIsProgram) gIsProgram;
decltype(&glIsShader) gIsShader;
decltype(&glLinkProgram) gLinkProgram;
decltype(&glShaderSource) gShaderSource;
decltype(&glUseProgram) gUseProgram;
decltype(&glUniform1f) gUniform1f;
decltype(&glUniform2f) gUniform2f;
decltype(&glUniform3f) gUniform3f;
decltype(&glUniform4f) gUniform4f;
decltype(&glUniform1i) gUniform1i;
decltype(&glUniform2i) gUniform2i;
decltype(&glUniform3i) gUniform3i;
decltype(&glUniform4i) gUniform4i;
decltype(&glUniform1fv) gUniform1fv;
decltype(&glUniform2fv) gUniform2fv;
decltype(&glUniform3fv) gUniform3fv;
decltype(&glUniform4fv) gUniform4fv;
decltype(&glUniform1iv) gUniform1iv;
decltype(&glUniform2iv) gUniform2iv;
decltype(&glUniform3iv) gUniform3iv;
decltype(&glUniform4iv) gUniform4iv;
decltype(&glUniformMatrix2fv) gUniformMatrix2fv;
decltype(&glUniformMatrix3fv) gUniformMatrix3fv;
decltype(&glUniformMatrix4fv) gUniformMatrix4fv;
decltype(&glValidateProgram) gValidateProgram;
decltype(&glVertexAttrib1d) gVertexAttrib1d;
decltype(&glVertexAttrib1dv) gVertexAttrib1dv;
decltype(&glVertexAttrib1f) gVertexAttrib1f;
decltype(&glVertexAttrib1fv) gVertexAttrib1fv;
decltype(&glVertexAttrib1s) gVertexAttrib1s;
decltype(&glVertexAttrib1sv) gVertexAttrib1sv;
decltype(&glVertexAttrib2d) gVertexAttrib2d;
decltype(&glVertexAttrib2dv) gVertexAttrib2dv;
decltype(&glVertexAttrib2f) gVertexAttrib2f;
decltype(&glVertexAttrib2fv) gVertexAttrib2fv;
decltype(&glVertexAttrib2s) gVertexAttrib2s;
decltype(&glVertexAttrib2sv) gVertexAttrib2sv;
decltype(&glVertexAttrib3d) gVertexAttrib3d;
decltype(&glVertexAttrib3dv) gVertexAttrib3dv;
decltype(&glVertexAttrib3f) gVertexAttrib3f;
decltype(&glVertexAttrib3fv) gVertexAttrib3fv;
decltype(&glVertexAttrib3s) gVertexAttrib3s;
decltype(&glVertexAttrib3sv) gVertexAttrib3sv;
decltype(&glVertexAttrib4Nbv) gVertexAttrib4Nbv;
decltype(&glVertexAttrib4Niv) gVertexAttrib4Niv;
decltype(&glVertexAttrib4Nsv) gVertexAttrib4Nsv;
decltype(&glVertexAttrib4Nub) gVertexAttrib4Nub;
decltype(&glVertexAttrib4Nubv) gVertexAttrib4Nubv;
decltype(&glVertexAttrib4Nuiv) gVertexAttrib4Nuiv;
decltype(&glVertexAttrib4Nusv) gVertexAttrib4Nusv;
decltype(&glVertexAttrib4bv) gVertexAttrib4bv;
decltype(&glVertexAttrib4d) gVertexAttrib4d;
decltype(&glVertexAttrib4dv) gVertexAttrib4dv;
decltype(&glVertexAttrib4f) gVertexAttrib4f;
decltype(&glVertexAttrib4fv) gVertexAttrib4fv;
decltype(&glVertexAttrib4iv) gVertexAttrib4iv;
decltype(&glVertexAttrib4s) gVertexAttrib4s;
decltype(&glVertexAttrib4sv) gVertexAttrib4sv;
decltype(&glVertexAttrib4ubv) gVertexAttrib4ubv;
decltype(&glVertexAttrib4uiv) gVertexAttrib4uiv;
decltype(&glVertexAttrib4usv) gVertexAttrib4usv;
decltype(&glVertexAttribPointer) gVertexAttribPointer;
decltype(&glUniformMatrix2x3fv) gUniformMatrix2x3fv;
decltype(&glUniformMatrix3x2fv) gUniformMatrix3x2fv;
decltype(&glUniformMatrix2x4fv) gUniformMatrix2x4fv;
decltype(&glUniformMatrix4x2fv) gUniformMatrix4x2fv;
decltype(&glUniformMatrix3x4fv) gUniformMatrix3x4fv;
decltype(&glUniformMatrix4x3fv) gUniformMatrix4x3fv;
decltype(&glColorMaski) gColorMaski;
decltype(&glGetBooleani_v) gGetBooleani_v;
decltype(&glGetIntegeri_v) gGetIntegeri_v;
decltype(&glEnablei) gEnablei;
decltype(&glDisablei) gDisablei;
decltype(&glIsEnabledi) gIsEnabledi;
decltype(&glBeginTransformFeedback) gBeginTransformFeedback;
decltype(&glEndTransformFeedback) gEndTransformFeedback;
decltype(&glBindBufferRange) gBindBufferRange;
decltype(&glBindBufferBase) gBindBufferBase;
decltype(&glTransformFeedbackVaryings) gTransformFeedbackVaryings;
decltype(&glGetTransformFeedbackVarying) gGetTransformFeedbackVarying;
decltype(&glClampColor) gClampColor;
decltype(&glBeginConditionalRender) gBeginConditionalRender;
decltype(&glEndConditionalRender) gEndConditionalRender;
decltype(&glVertexAttribIPointer) gVertexAttribIPointer;
decltype(&glGetVertexAttribIiv) gGetVertexAttribIiv;
decltype(&glGetVertexAttribIuiv) gGetVertexAttribIuiv;
decltype(&glVertexAttribI1i) gVertexAttribI1i;
decltype(&glVertexAttribI2i) gVertexAttribI2i;
decltype(&glVertexAttribI3i) gVertexAttribI3i;
decltype(&glVertexAttribI4i) gVertexAttribI4i;
decltype(&glVertexAttribI1ui) gVertexAttribI1ui;
decltype(&glVertexAttribI2ui) gVertexAttribI2ui;
decltype(&glVertexAttribI3ui) gVertexAttribI3ui;
decltype(&glVertexAttribI4ui) gVertexAttribI4ui;
decltype(&glVertexAttribI1iv) gVertexAttribI1iv;
decltype(&glVertexAttribI2iv) gVertexAttribI2iv;
decltype(&glVertexAttribI3iv) gVertexAttribI3iv;
decltype(&glVertexAttribI4iv) gVertexAttribI4iv;
decltype(&glVertexAttribI1uiv) gVertexAttribI1uiv;
decltype(&glVertexAttribI2uiv) gVertexAttribI2uiv;
decltype(&glVertexAttribI3uiv) gVertexAttribI3uiv;
decltype(&glVertexAttribI4uiv) gVertexAttribI4uiv;
decltype(&glVertexAttribI4bv) gVertexAttribI4bv;
decltype(&glVertexAttribI4sv) gVertexAttribI4sv;
decltype(&glVertexAttribI4ubv) gVertexAttribI4ubv;
decltype(&glVertexAttribI4usv) gVertexAttribI4usv;
decltype(&glGetUniformuiv) gGetUniformuiv;
decltype(&glBindFragDataLocation) gBindFragDataLocation;
decltype(&glGetFragDataLocation) gGetFragDataLocation;
decltype(&glUniform1ui) gUniform1ui;
decltype(&glUniform2ui) gUniform2ui;
decltype(&glUniform3ui) gUniform3ui;
decltype(&glUniform4ui) gUniform4ui;
decltype(&glUniform1uiv) gUniform1uiv;
decltype(&glUniform2uiv) gUniform2uiv;
decltype(&glUniform3uiv) gUniform3uiv;
decltype(&glUniform4uiv) gUniform4uiv;
decltype(&glTexParameterIiv) gTexParameterIiv;
decltype(&glTexParameterIuiv) gTexParameterIuiv;
decltype(&glGetTexParameterIiv) gGetTexParameterIiv;
decltype(&glGetTexParameterIuiv) gGetTexParameterIuiv;
decltype(&glClearBufferiv) gClearBufferiv;
decltype(&glClearBufferuiv) gClearBufferuiv;
decltype(&glClearBufferfv) gClearBufferfv;
decltype(&glClearBufferfi) gClearBufferfi;
decltype(&glGetStringi) gGetStringi;
decltype(&glDrawArraysInstanced) gDrawArraysInstanced;
decltype(&glDrawElementsInstanced) gDrawElementsInstanced;
decltype(&glTexBuffer) gTexBuffer;
decltype(&glPrimitiveRestartIndex) gPrimitiveRestartIndex;
decltype(&glGetInteger64i_v) gGetInteger64i_v;
decltype(&glGetBufferParameteri64v) gGetBufferParameteri64v;
decltype(&glFramebufferTexture) gFramebufferTexture;
decltype(&glVertexAttribDivisor) gVertexAttribDivisor;
decltype(&glMinSampleShading) gMinSampleShading;
decltype(&glBlendEquationi) gBlendEquationi;
decltype(&glBlendEquationSeparatei) gBlendEquationSeparatei;
decltype(&glBlendFunci) gBlendFunci;
decltype(&glBlendFuncSeparatei) gBlendFuncSeparatei;
decltype(&glIsRenderbuffer) gIsRenderbuffer;
decltype(&glBindRenderbuffer) gBindRenderbuffer;
decltype(&glDeleteRenderbuffers) gDeleteRenderbuffers;
decltype(&glGenRenderbuffers) gGenRenderbuffers;
decltype(&glRenderbufferStorage) gRenderbufferStorage;
decltype(&glGetRenderbufferParameteriv) gGetRenderbufferParameteriv;
decltype(&glIsFramebuffer) gIsFramebuffer;
decltype(&glBindFramebuffer) gBindFramebuffer;
decltype(&glDeleteFramebuffers) gDeleteFramebuffers;
decltype(&glGenFramebuffers) gGenFramebuffers;
decltype(&glCheckFramebufferStatus) gCheckFramebufferStatus;
decltype(&glFramebufferTexture1D) gFramebufferTexture1D;
decltype(&glFramebufferTexture2D) gFramebufferTexture2D;
decltype(&glFramebufferTexture3D) gFramebufferTexture3D;
decltype(&glFramebufferRenderbuffer) gFramebufferRenderbuffer;
decltype(&glGetFramebufferAttachmentParameteriv) gGetFramebufferAttachmentParameteriv;
decltype(&glGenerateMipmap) gGenerateMipmap;
decltype(&glBlitFramebuffer) gBlitFramebuffer;
decltype(&glRenderbufferStorageMultisample) gRenderbufferStorageMultisample;
decltype(&glFramebufferTextureLayer) gFramebufferTextureLayer;
decltype(&glMapBufferRange) gMapBufferRange;
decltype(&glFlushMappedBufferRange) gFlushMappedBufferRange;
decltype(&glBindVertexArray) gBindVertexArray;
decltype(&glDeleteVertexArrays) gDeleteVertexArrays;
decltype(&glGenVertexArrays) gGenVertexArrays;
decltype(&glIsVertexArray) gIsVertexArray;
decltype(&glGetUniformIndices) gGetUniformIndices;
decltype(&glGetActiveUniformsiv) gGetActiveUniformsiv;
decltype(&glGetActiveUniformName) gGetActiveUniformName;
decltype(&glGetUniformBlockIndex) gGetUniformBlockIndex;
decltype(&glGetActiveUniformBlockiv) gGetActiveUniformBlockiv;
decltype(&glGetActiveUniformBlockName) gGetActiveUniformBlockName;
decltype(&glUniformBlockBinding) gUniformBlockBinding;
decltype(&glCopyBufferSubData) gCopyBufferSubData;
decltype(&glDrawElementsBaseVertex) gDrawElementsBaseVertex;
decltype(&glDrawRangeElementsBaseVertex) gDrawRangeElementsBaseVertex;
decltype(&glDrawElementsInstancedBaseVertex) gDrawElementsInstancedBaseVertex;
decltype(&glMultiDrawElementsBaseVertex) gMultiDrawElementsBaseVertex;
decltype(&glProvokingVertex) gProvokingVertex;
decltype(&glFenceSync) gFenceSync;
decltype(&glIsSync) gIsSync;
decltype(&glDeleteSync) gDeleteSync;
decltype(&glClientWaitSync) gClientWaitSync;
decltype(&glWaitSync) gWaitSync;
decltype(&glGetInteger64v) gGetInteger64v;
decltype(&glGetSynciv) gGetSynciv;
decltype(&glTexImage2DMultisample) gTexImage2DMultisample;
decltype(&glTexImage3DMultisample) gTexImage3DMultisample;
decltype(&glGetMultisamplefv) gGetMultisamplefv;
decltype(&glSampleMaski) gSampleMaski;
decltype(&glBlendEquationiARB) gBlendEquationiARB;
decltype(&glBlendEquationSeparateiARB) gBlendEquationSeparateiARB;
decltype(&glBlendFunciARB) gBlendFunciARB;
decltype(&glBlendFuncSeparateiARB) gBlendFuncSeparateiARB;
decltype(&glMinSampleShadingARB) gMinSampleShadingARB;
decltype(&glNamedStringARB) gNamedStringARB;
decltype(&glDeleteNamedStringARB) gDeleteNamedStringARB;
decltype(&glCompileShaderIncludeARB) gCompileShaderIncludeARB;
decltype(&glIsNamedStringARB) gIsNamedStringARB;
decltype(&glGetNamedStringARB) gGetNamedStringARB;
decltype(&glGetNamedStringivARB) gGetNamedStringivARB;
decltype(&glBindFragDataLocationIndexed) gBindFragDataLocationIndexed;
decltype(&glGetFragDataIndex) gGetFragDataIndex;
decltype(&glGenSamplers) gGenSamplers;
decltype(&glDeleteSamplers) gDeleteSamplers;
decltype(&glIsSampler) gIsSampler;
decltype(&glBindSampler) gBindSampler;
decltype(&glSamplerParameteri) gSamplerParameteri;
decltype(&glSamplerParameteriv) gSamplerParameteriv;
decltype(&glSamplerParameterf) gSamplerParameterf;
decltype(&glSamplerParameterfv) gSamplerParameterfv;
decltype(&glSamplerParameterIiv) gSamplerParameterIiv;
decltype(&glSamplerParameterIuiv) gSamplerParameterIuiv;
decltype(&glGetSamplerParameteriv) gGetSamplerParameteriv;
decltype(&glGetSamplerParameterIiv) gGetSamplerParameterIiv;
decltype(&glGetSamplerParameterfv) gGetSamplerParameterfv;
decltype(&glGetSamplerParameterIuiv) gGetSamplerParameterIuiv;
decltype(&glQueryCounter) gQueryCounter;
decltype(&glGetQueryObjecti64v) gGetQueryObjecti64v;
decltype(&glGetQueryObjectui64v) gGetQueryObjectui64v;
decltype(&glDrawArraysIndirect) gDrawArraysIndirect;
decltype(&glDrawElementsIndirect) gDrawElementsIndirect;
decltype(&glUniform1d) gUniform1d;
decltype(&glUniform2d) gUniform2d;
decltype(&glUniform3d) gUniform3d;
decltype(&glUniform4d) gUniform4d;
decltype(&glUniform1dv) gUniform1dv;
decltype(&glUniform2dv) gUniform2dv;
decltype(&glUniform3dv) gUniform3dv;
decltype(&glUniform4dv) gUniform4dv;
decltype(&glUniformMatrix2dv) gUniformMatrix2dv;
decltype(&glUniformMatrix3dv) gUniformMatrix3dv;
decltype(&glUniformMatrix4dv) gUniformMatrix4dv;
decltype(&glUniformMatrix2x3dv) gUniformMatrix2x3dv;
decltype(&glUniformMatrix2x4dv) gUniformMatrix2x4dv;
decltype(&glUniformMatrix3x2dv) gUniformMatrix3x2dv;
decltype(&glUniformMatrix3x4dv) gUniformMatrix3x4dv;
decltype(&glUniformMatrix4x2dv) gUniformMatrix4x2dv;
decltype(&glUniformMatrix4x3dv) gUniformMatrix4x3dv;
decltype(&glGetUniformdv) gGetUniformdv;
decltype(&glGetSubroutineUniformLocation) gGetSubroutineUniformLocation;
decltype(&glGetSubroutineIndex) gGetSubroutineIndex;
decltype(&glGetActiveSubroutineUniformiv) gGetActiveSubroutineUniformiv;
decltype(&glGetActiveSubroutineUniformName) gGetActiveSubroutineUniformName;
decltype(&glGetActiveSubroutineName) gGetActiveSubroutineName;
decltype(&glUniformSubroutinesuiv) gUniformSubroutinesuiv;
decltype(&glGetUniformSubroutineuiv) gGetUniformSubroutineuiv;
decltype(&glGetProgramStageiv) gGetProgramStageiv;
decltype(&glPatchParameteri) gPatchParameteri;
decltype(&glPatchParameterfv) gPatchParameterfv;
decltype(&glBindTransformFeedback) gBindTransformFeedback;
decltype(&glDeleteTransformFeedbacks) gDeleteTransformFeedbacks;
decltype(&glGenTransformFeedbacks) gGenTransformFeedbacks;
decltype(&glIsTransformFeedback) gIsTransformFeedback;
decltype(&glPauseTransformFeedback) gPauseTransformFeedback;
decltype(&glResumeTransformFeedback) gResumeTransformFeedback;
decltype(&glDrawTransformFeedback) gDrawTransformFeedback;
decltype(&glDrawTransformFeedbackStream) gDrawTransformFeedbackStream;
decltype(&glBeginQueryIndexed) gBeginQueryIndexed;
decltype(&glEndQueryIndexed) gEndQueryIndexed;
decltype(&glGetQueryIndexediv) gGetQueryIndexediv;
decltype(&glReleaseShaderCompiler) gReleaseShaderCompiler;
decltype(&glShaderBinary) gShaderBinary;
decltype(&glGetShaderPrecisionFormat) gGetShaderPrecisionFormat;
decltype(&glDepthRangef) gDepthRangef;
decltype(&glClearDepthf) gClearDepthf;
decltype(&glGetProgramBinary) gGetProgramBinary;
decltype(&glProgramBinary) gProgramBinary;
decltype(&glProgramParameteri) gProgramParameteri;
decltype(&glUseProgramStages) gUseProgramStages;
decltype(&glActiveShaderProgram) gActiveShaderProgram;
decltype(&glCreateShaderProgramv) gCreateShaderProgramv;
decltype(&glBindProgramPipeline) gBindProgramPipeline;
decltype(&glDeleteProgramPipelines) gDeleteProgramPipelines;
decltype(&glGenProgramPipelines) gGenProgramPipelines;
decltype(&glIsProgramPipeline) gIsProgramPipeline;
decltype(&glGetProgramPipelineiv) gGetProgramPipelineiv;
decltype(&glProgramUniform1i) gProgramUniform1i;
decltype(&glProgramUniform1iv) gProgramUniform1iv;
decltype(&glProgramUniform1f) gProgramUniform1f;
decltype(&glProgramUniform1fv) gProgramUniform1fv;
decltype(&glProgramUniform1d) gProgramUniform1d;
decltype(&glProgramUniform1dv) gProgramUniform1dv;
decltype(&glProgramUniform1ui) gProgramUniform1ui;
decltype(&glProgramUniform1uiv) gProgramUniform1uiv;
decltype(&glProgramUniform2i) gProgramUniform2i;
decltype(&glProgramUniform2iv) gProgramUniform2iv;
decltype(&glProgramUniform2f) gProgramUniform2f;
decltype(&glProgramUniform2fv) gProgramUniform2fv;
decltype(&glProgramUniform2d) gProgramUniform2d;
decltype(&glProgramUniform2dv) gProgramUniform2dv;
decltype(&glProgramUniform2ui) gProgramUniform2ui;
decltype(&glProgramUniform2uiv) gProgramUniform2uiv;
decltype(&glProgramUniform3i) gProgramUniform3i;
decltype(&glProgramUniform3iv) gProgramUniform3iv;
decltype(&glProgramUniform3f) gProgramUniform3f;
decltype(&glProgramUniform3fv) gProgramUniform3fv;
decltype(&glProgramUniform3d) gProgramUniform3d;
decltype(&glProgramUniform3dv) gProgramUniform3dv;
decltype(&glProgramUniform3ui) gProgramUniform3ui;
decltype(&glProgramUniform3uiv) gProgramUniform3uiv;
decltype(&glProgramUniform4i) gProgramUniform4i;
decltype(&glProgramUniform4iv) gProgramUniform4iv;
decltype(&glProgramUniform4f) gProgramUniform4f;
decltype(&glProgramUniform4fv) gProgramUniform4fv;
decltype(&glProgramUniform4d) gProgramUniform4d;
decltype(&glProgramUniform4dv) gProgramUniform4dv;
decltype(&glProgramUniform4ui) gProgramUniform4ui;
decltype(&glProgramUniform4uiv) gProgramUniform4uiv;
decltype(&glProgramUniformMatrix2fv) gProgramUniformMatrix2fv;
decltype(&glProgramUniformMatrix3fv) gProgramUniformMatrix3fv;
decltype(&glProgramUniformMatrix4fv) gProgramUniformMatrix4fv;
decltype(&glProgramUniformMatrix2dv) gProgramUniformMatrix2dv;
decltype(&glProgramUniformMatrix3dv) gProgramUniformMatrix3dv;
decltype(&glProgramUniformMatrix4dv) gProgramUniformMatrix4dv;
decltype(&glProgramUniformMatrix2x3fv) gProgramUniformMatrix2x3fv;
decltype(&glProgramUniformMatrix3x2fv) gProgramUniformMatrix3x2fv;
decltype(&glProgramUniformMatrix2x4fv) gProgramUniformMatrix2x4fv;
decltype(&glProgramUniformMatrix4x2fv) gProgramUniformMatrix4x2fv;
decltype(&glProgramUniformMatrix3x4fv) gProgramUniformMatrix3x4fv;
decltype(&glProgramUniformMatrix4x3fv) gProgramUniformMatrix4x3fv;
decltype(&glProgramUniformMatrix2x3dv) gProgramUniformMatrix2x3dv;
decltype(&glProgramUniformMatrix3x2dv) gProgramUniformMatrix3x2dv;
decltype(&glProgramUniformMatrix2x4dv) gProgramUniformMatrix2x4dv;
decltype(&glProgramUniformMatrix4x2dv) gProgramUniformMatrix4x2dv;
decltype(&glProgramUniformMatrix3x4dv) gProgramUniformMatrix3x4dv;
decltype(&glProgramUniformMatrix4x3dv) gProgramUniformMatrix4x3dv;
decltype(&glValidateProgramPipeline) gValidateProgramPipeline;
decltype(&glGetProgramPipelineInfoLog) gGetProgramPipelineInfoLog;
decltype(&glVertexAttribL1d) gVertexAttribL1d;
decltype(&glVertexAttribL2d) gVertexAttribL2d;
decltype(&glVertexAttribL3d) gVertexAttribL3d;
decltype(&glVertexAttribL4d) gVertexAttribL4d;
decltype(&glVertexAttribL1dv) gVertexAttribL1dv;
decltype(&glVertexAttribL2dv) gVertexAttribL2dv;
decltype(&glVertexAttribL3dv) gVertexAttribL3dv;
decltype(&glVertexAttribL4dv) gVertexAttribL4dv;
decltype(&glVertexAttribLPointer) gVertexAttribLPointer;
decltype(&glGetVertexAttribLdv) gGetVertexAttribLdv;
decltype(&glViewportArrayv) gViewportArrayv;
decltype(&glViewportIndexedf) gViewportIndexedf;
decltype(&glViewportIndexedfv) gViewportIndexedfv;
decltype(&glScissorArrayv) gScissorArrayv;
decltype(&glScissorIndexed) gScissorIndexed;
decltype(&glScissorIndexedv) gScissorIndexedv;
decltype(&glDepthRangeArrayv) gDepthRangeArrayv;
decltype(&glDepthRangeIndexed) gDepthRangeIndexed;
decltype(&glGetFloati_v) gGetFloati_v;
decltype(&glGetDoublei_v) gGetDoublei_v;
decltype(&glCreateSyncFromCLeventARB) gCreateSyncFromCLeventARB;
decltype(&glDebugMessageControlARB) gDebugMessageControlARB;
decltype(&glDebugMessageInsertARB) gDebugMessageInsertARB;
decltype(&glDebugMessageCallbackARB) gDebugMessageCallbackARB;
decltype(&glGetDebugMessageLogARB) gGetDebugMessageLogARB;
decltype(&glGetGraphicsResetStatusARB) gGetGraphicsResetStatusARB;
decltype(&glGetnMapdvARB) gGetnMapdvARB;
decltype(&glGetnMapfvARB) gGetnMapfvARB;
decltype(&glGetnMapivARB) gGetnMapivARB;
decltype(&glGetnPixelMapfvARB) gGetnPixelMapfvARB;
decltype(&glGetnPixelMapuivARB) gGetnPixelMapuivARB;
decltype(&glGetnPixelMapusvARB) gGetnPixelMapusvARB;
decltype(&glGetnPolygonStippleARB) gGetnPolygonStippleARB;
decltype(&glGetnColorTableARB) gGetnColorTableARB;
decltype(&glGetnConvolutionFilterARB) gGetnConvolutionFilterARB;
decltype(&glGetnSeparableFilterARB) gGetnSeparableFilterARB;
decltype(&glGetnHistogramARB) gGetnHistogramARB;
decltype(&glGetnMinmaxARB) gGetnMinmaxARB;
decltype(&glGetnTexImageARB) gGetnTexImageARB;
decltype(&glReadnPixelsARB) gReadnPixelsARB;
decltype(&glGetnCompressedTexImageARB) gGetnCompressedTexImageARB;
decltype(&glGetnUniformfvARB) gGetnUniformfvARB;
decltype(&glGetnUniformivARB) gGetnUniformivARB;
decltype(&glGetnUniformuivARB) gGetnUniformuivARB;
decltype(&glGetnUniformdvARB) gGetnUniformdvARB;
decltype(&glDrawArraysInstancedBaseInstance) gDrawArraysInstancedBaseInstance;
decltype(&glDrawElementsInstancedBaseInstance) gDrawElementsInstancedBaseInstance;
decltype(&glDrawElementsInstancedBaseVertexBaseInstance) gDrawElementsInstancedBaseVertexBaseInstance;
decltype(&glDrawTransformFeedbackInstanced) gDrawTransformFeedbackInstanced;
decltype(&glDrawTransformFeedbackStreamInstanced) gDrawTransformFeedbackStreamInstanced;
decltype(&glGetInternalformativ) gGetInternalformativ;
decltype(&glGetActiveAtomicCounterBufferiv) gGetActiveAtomicCounterBufferiv;
decltype(&glBindImageTexture) gBindImageTexture;
decltype(&glMemoryBarrier) gMemoryBarrier;
decltype(&glTexStorage1D) gTexStorage1D;
decltype(&glTexStorage2D) gTexStorage2D;
decltype(&glTexStorage3D) gTexStorage3D;
decltype(&glTextureStorage1DEXT) gTextureStorage1DEXT;
decltype(&glTextureStorage2DEXT) gTextureStorage2DEXT;
decltype(&glTextureStorage3DEXT) gTextureStorage3DEXT;

void checkError()
{
#ifndef NDEBUG
	auto error = gGetError();
	switch (error) {
	case GL_NO_ERROR:
		return;
	case GL_INVALID_ENUM:
		throw std::runtime_error{"OpenGL Error: GL_INVALID_ENUM"};
	case GL_INVALID_VALUE:
		throw std::runtime_error{"OpenGL Error: GL_INVALID_VALUE"};
	case GL_INVALID_OPERATION:
		throw std::runtime_error{"OpenGL Error: GL_INVALID_OPERATION"};
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		throw std::runtime_error{"OpenGL Error: GL_INVALID_FRAMEBUFFER_OPERATION"};
	case GL_OUT_OF_MEMORY:
		throw std::runtime_error{"OpenGL Error: GL_OUT_OF_MEMORY"};
	}
#endif
}

}

namespace Twil {
namespace Gl {
namespace Context {

void initialize(Platform::SymbolLoaderT const & Loader)
{
	Loader.loadGlSymbol(gCullFace, "glCullFace");
	Loader.loadGlSymbol(gFrontFace, "glFrontFace");
	Loader.loadGlSymbol(gHint, "glHint");
	Loader.loadGlSymbol(gLineWidth, "glLineWidth");
	Loader.loadGlSymbol(gPointSize, "glPointSize");
	Loader.loadGlSymbol(gPolygonMode, "glPolygonMode");
	Loader.loadGlSymbol(gScissor, "glScissor");
	Loader.loadGlSymbol(gTexParameterf, "glTexParameterf");
	Loader.loadGlSymbol(gTexParameterfv, "glTexParameterfv");
	Loader.loadGlSymbol(gTexParameteri, "glTexParameteri");
	Loader.loadGlSymbol(gTexParameteriv, "glTexParameteriv");
	Loader.loadGlSymbol(gTexImage1D, "glTexImage1D");
	Loader.loadGlSymbol(gTexImage2D, "glTexImage2D");
	Loader.loadGlSymbol(gDrawBuffer, "glDrawBuffer");
	Loader.loadGlSymbol(gClear, "glClear");
	Loader.loadGlSymbol(gClearColor, "glClearColor");
	Loader.loadGlSymbol(gClearStencil, "glClearStencil");
	Loader.loadGlSymbol(gClearDepth, "glClearDepth");
	Loader.loadGlSymbol(gStencilMask, "glStencilMask");
	Loader.loadGlSymbol(gColorMask, "glColorMask");
	Loader.loadGlSymbol(gDepthMask, "glDepthMask");
	Loader.loadGlSymbol(gDisable, "glDisable");
	Loader.loadGlSymbol(gEnable, "glEnable");
	Loader.loadGlSymbol(gFinish, "glFinish");
	Loader.loadGlSymbol(gFlush, "glFlush");
	Loader.loadGlSymbol(gBlendFunc, "glBlendFunc");
	Loader.loadGlSymbol(gLogicOp, "glLogicOp");
	Loader.loadGlSymbol(gStencilFunc, "glStencilFunc");
	Loader.loadGlSymbol(gStencilOp, "glStencilOp");
	Loader.loadGlSymbol(gDepthFunc, "glDepthFunc");
	Loader.loadGlSymbol(gPixelStoref, "glPixelStoref");
	Loader.loadGlSymbol(gPixelStorei, "glPixelStorei");
	Loader.loadGlSymbol(gReadBuffer, "glReadBuffer");
	Loader.loadGlSymbol(gReadPixels, "glReadPixels");
	Loader.loadGlSymbol(gGetBooleanv, "glGetBooleanv");
	Loader.loadGlSymbol(gGetDoublev, "glGetDoublev");
	Loader.loadGlSymbol(gGetError, "glGetError");
	Loader.loadGlSymbol(gGetFloatv, "glGetFloatv");
	Loader.loadGlSymbol(gGetIntegerv, "glGetIntegerv");
	Loader.loadGlSymbol(gGetString, "glGetString");
	Loader.loadGlSymbol(gGetTexImage, "glGetTexImage");
	Loader.loadGlSymbol(gGetTexParameterfv, "glGetTexParameterfv");
	Loader.loadGlSymbol(gGetTexParameteriv, "glGetTexParameteriv");
	Loader.loadGlSymbol(gGetTexLevelParameterfv, "glGetTexLevelParameterfv");
	Loader.loadGlSymbol(gGetTexLevelParameteriv, "glGetTexLevelParameteriv");
	Loader.loadGlSymbol(gIsEnabled, "glIsEnabled");
	Loader.loadGlSymbol(gDepthRange, "glDepthRange");
	Loader.loadGlSymbol(gViewport, "glViewport");
	Loader.loadGlSymbol(gDrawArrays, "glDrawArrays");
	Loader.loadGlSymbol(gDrawElements, "glDrawElements");
	Loader.loadGlSymbol(gGetPointerv, "glGetPointerv");
	Loader.loadGlSymbol(gPolygonOffset, "glPolygonOffset");
	Loader.loadGlSymbol(gCopyTexImage1D, "glCopyTexImage1D");
	Loader.loadGlSymbol(gCopyTexImage2D, "glCopyTexImage2D");
	Loader.loadGlSymbol(gCopyTexSubImage1D, "glCopyTexSubImage1D");
	Loader.loadGlSymbol(gCopyTexSubImage2D, "glCopyTexSubImage2D");
	Loader.loadGlSymbol(gTexSubImage1D, "glTexSubImage1D");
	Loader.loadGlSymbol(gTexSubImage2D, "glTexSubImage2D");
	Loader.loadGlSymbol(gBindTexture, "glBindTexture");
	Loader.loadGlSymbol(gDeleteTextures, "glDeleteTextures");
	Loader.loadGlSymbol(gGenTextures, "glGenTextures");
	Loader.loadGlSymbol(gIsTexture, "glIsTexture");
	Loader.loadGlArbSymbol(gBlendColor, "glBlendColor");
	Loader.loadGlArbSymbol(gBlendEquation, "glBlendEquation");
	Loader.loadGlArbSymbol(gDrawRangeElements, "glDrawRangeElements");
	Loader.loadGlArbSymbol(gTexImage3D, "glTexImage3D");
	Loader.loadGlArbSymbol(gTexSubImage3D, "glTexSubImage3D");
	Loader.loadGlArbSymbol(gCopyTexSubImage3D, "glCopyTexSubImage3D");
	Loader.loadGlArbSymbol(gActiveTexture, "glActiveTexture");
	Loader.loadGlArbSymbol(gSampleCoverage, "glSampleCoverage");
	Loader.loadGlArbSymbol(gCompressedTexImage3D, "glCompressedTexImage3D");
	Loader.loadGlArbSymbol(gCompressedTexImage2D, "glCompressedTexImage2D");
	Loader.loadGlArbSymbol(gCompressedTexImage1D, "glCompressedTexImage1D");
	Loader.loadGlArbSymbol(gCompressedTexSubImage3D, "glCompressedTexSubImage3D");
	Loader.loadGlArbSymbol(gCompressedTexSubImage2D, "glCompressedTexSubImage2D");
	Loader.loadGlArbSymbol(gCompressedTexSubImage1D, "glCompressedTexSubImage1D");
	Loader.loadGlArbSymbol(gGetCompressedTexImage, "glGetCompressedTexImage");
	Loader.loadGlArbSymbol(gBlendFuncSeparate, "glBlendFuncSeparate");
	Loader.loadGlArbSymbol(gMultiDrawArrays, "glMultiDrawArrays");
	Loader.loadGlArbSymbol(gMultiDrawElements, "glMultiDrawElements");
	Loader.loadGlArbSymbol(gPointParameterf, "glPointParameterf");
	Loader.loadGlArbSymbol(gPointParameterfv, "glPointParameterfv");
	Loader.loadGlArbSymbol(gPointParameteri, "glPointParameteri");
	Loader.loadGlArbSymbol(gPointParameteriv, "glPointParameteriv");
	Loader.loadGlArbSymbol(gGenQueries, "glGenQueries");
	Loader.loadGlArbSymbol(gDeleteQueries, "glDeleteQueries");
	Loader.loadGlArbSymbol(gIsQuery, "glIsQuery");
	Loader.loadGlArbSymbol(gBeginQuery, "glBeginQuery");
	Loader.loadGlArbSymbol(gEndQuery, "glEndQuery");
	Loader.loadGlArbSymbol(gGetQueryiv, "glGetQueryiv");
	Loader.loadGlArbSymbol(gGetQueryObjectiv, "glGetQueryObjectiv");
	Loader.loadGlArbSymbol(gVertexAttribP1ui, "glVertexAttribP1ui");
	Loader.loadGlArbSymbol(gVertexAttribP1uiv, "glVertexAttribP1uiv");
	Loader.loadGlArbSymbol(gVertexAttribP2ui, "glVertexAttribP2ui");
	Loader.loadGlArbSymbol(gVertexAttribP2uiv, "glVertexAttribP2uiv");
	Loader.loadGlArbSymbol(gVertexAttribP3ui, "glVertexAttribP3ui");
	Loader.loadGlArbSymbol(gVertexAttribP3uiv, "glVertexAttribP3uiv");
	Loader.loadGlArbSymbol(gVertexAttribP4ui, "glVertexAttribP4ui");
	Loader.loadGlArbSymbol(gVertexAttribP4uiv, "glVertexAttribP4uiv");
	Loader.loadGlArbSymbol(gGetQueryObjectuiv, "glGetQueryObjectuiv");
	Loader.loadGlArbSymbol(gBindBuffer, "glBindBuffer");
	Loader.loadGlArbSymbol(gDeleteBuffers, "glDeleteBuffers");
	Loader.loadGlArbSymbol(gGenBuffers, "glGenBuffers");
	Loader.loadGlArbSymbol(gIsBuffer, "glIsBuffer");
	Loader.loadGlArbSymbol(gBufferData, "glBufferData");
	Loader.loadGlArbSymbol(gBufferSubData, "glBufferSubData");
	Loader.loadGlArbSymbol(gGetBufferSubData, "glGetBufferSubData");
	Loader.loadGlArbSymbol(gMapBuffer, "glMapBuffer");
	Loader.loadGlArbSymbol(gUnmapBuffer, "glUnmapBuffer");
	Loader.loadGlArbSymbol(gGetBufferParameteriv, "glGetBufferParameteriv");
	Loader.loadGlArbSymbol(gGetBufferPointerv, "glGetBufferPointerv");
	Loader.loadGlArbSymbol(gBlendEquationSeparate, "glBlendEquationSeparate");
	Loader.loadGlArbSymbol(gDrawBuffers, "glDrawBuffers");
	Loader.loadGlArbSymbol(gStencilOpSeparate, "glStencilOpSeparate");
	Loader.loadGlArbSymbol(gStencilFuncSeparate, "glStencilFuncSeparate");
	Loader.loadGlArbSymbol(gStencilMaskSeparate, "glStencilMaskSeparate");
	Loader.loadGlArbSymbol(gAttachShader, "glAttachShader");
	Loader.loadGlArbSymbol(gBindAttribLocation, "glBindAttribLocation");
	Loader.loadGlArbSymbol(gCompileShader, "glCompileShader");
	Loader.loadGlArbSymbol(gCreateProgram, "glCreateProgram");
	Loader.loadGlArbSymbol(gCreateShader, "glCreateShader");
	Loader.loadGlArbSymbol(gDeleteProgram, "glDeleteProgram");
	Loader.loadGlArbSymbol(gDeleteShader, "glDeleteShader");
	Loader.loadGlArbSymbol(gDetachShader, "glDetachShader");
	Loader.loadGlArbSymbol(gDisableVertexAttribArray, "glDisableVertexAttribArray");
	Loader.loadGlArbSymbol(gEnableVertexAttribArray, "glEnableVertexAttribArray");
	Loader.loadGlArbSymbol(gGetActiveAttrib, "glGetActiveAttrib");
	Loader.loadGlArbSymbol(gGetActiveUniform, "glGetActiveUniform");
	Loader.loadGlArbSymbol(gGetAttachedShaders, "glGetAttachedShaders");
	Loader.loadGlArbSymbol(gGetAttribLocation, "glGetAttribLocation");
	Loader.loadGlArbSymbol(gGetProgramiv, "glGetProgramiv");
	Loader.loadGlArbSymbol(gGetProgramInfoLog, "glGetProgramInfoLog");
	Loader.loadGlArbSymbol(gGetShaderiv, "glGetShaderiv");
	Loader.loadGlArbSymbol(gGetShaderInfoLog, "glGetShaderInfoLog");
	Loader.loadGlArbSymbol(gGetShaderSource, "glGetShaderSource");
	Loader.loadGlArbSymbol(gGetUniformLocation, "glGetUniformLocation");
	Loader.loadGlArbSymbol(gGetUniformfv, "glGetUniformfv");
	Loader.loadGlArbSymbol(gGetUniformiv, "glGetUniformiv");
	Loader.loadGlArbSymbol(gGetVertexAttribdv, "glGetVertexAttribdv");
	Loader.loadGlArbSymbol(gGetVertexAttribfv, "glGetVertexAttribfv");
	Loader.loadGlArbSymbol(gGetVertexAttribiv, "glGetVertexAttribiv");
	Loader.loadGlArbSymbol(gGetVertexAttribPointerv, "glGetVertexAttribPointerv");
	Loader.loadGlArbSymbol(gIsProgram, "glIsProgram");
	Loader.loadGlArbSymbol(gIsShader, "glIsShader");
	Loader.loadGlArbSymbol(gLinkProgram, "glLinkProgram");
	Loader.loadGlArbSymbol(gShaderSource, "glShaderSource");
	Loader.loadGlArbSymbol(gUseProgram, "glUseProgram");
	Loader.loadGlArbSymbol(gUniform1f, "glUniform1f");
	Loader.loadGlArbSymbol(gUniform2f, "glUniform2f");
	Loader.loadGlArbSymbol(gUniform3f, "glUniform3f");
	Loader.loadGlArbSymbol(gUniform4f, "glUniform4f");
	Loader.loadGlArbSymbol(gUniform1i, "glUniform1i");
	Loader.loadGlArbSymbol(gUniform2i, "glUniform2i");
	Loader.loadGlArbSymbol(gUniform3i, "glUniform3i");
	Loader.loadGlArbSymbol(gUniform4i, "glUniform4i");
	Loader.loadGlArbSymbol(gUniform1fv, "glUniform1fv");
	Loader.loadGlArbSymbol(gUniform2fv, "glUniform2fv");
	Loader.loadGlArbSymbol(gUniform3fv, "glUniform3fv");
	Loader.loadGlArbSymbol(gUniform4fv, "glUniform4fv");
	Loader.loadGlArbSymbol(gUniform1iv, "glUniform1iv");
	Loader.loadGlArbSymbol(gUniform2iv, "glUniform2iv");
	Loader.loadGlArbSymbol(gUniform3iv, "glUniform3iv");
	Loader.loadGlArbSymbol(gUniform4iv, "glUniform4iv");
	Loader.loadGlArbSymbol(gUniformMatrix2fv, "glUniformMatrix2fv");
	Loader.loadGlArbSymbol(gUniformMatrix3fv, "glUniformMatrix3fv");
	Loader.loadGlArbSymbol(gUniformMatrix4fv, "glUniformMatrix4fv");
	Loader.loadGlArbSymbol(gValidateProgram, "glValidateProgram");
	Loader.loadGlArbSymbol(gVertexAttrib1d, "glVertexAttrib1d");
	Loader.loadGlArbSymbol(gVertexAttrib1dv, "glVertexAttrib1dv");
	Loader.loadGlArbSymbol(gVertexAttrib1f, "glVertexAttrib1f");
	Loader.loadGlArbSymbol(gVertexAttrib1fv, "glVertexAttrib1fv");
	Loader.loadGlArbSymbol(gVertexAttrib1s, "glVertexAttrib1s");
	Loader.loadGlArbSymbol(gVertexAttrib1sv, "glVertexAttrib1sv");
	Loader.loadGlArbSymbol(gVertexAttrib2d, "glVertexAttrib2d");
	Loader.loadGlArbSymbol(gVertexAttrib2dv, "glVertexAttrib2dv");
	Loader.loadGlArbSymbol(gVertexAttrib2f, "glVertexAttrib2f");
	Loader.loadGlArbSymbol(gVertexAttrib2fv, "glVertexAttrib2fv");
	Loader.loadGlArbSymbol(gVertexAttrib2s, "glVertexAttrib2s");
	Loader.loadGlArbSymbol(gVertexAttrib2sv, "glVertexAttrib2sv");
	Loader.loadGlArbSymbol(gVertexAttrib3d, "glVertexAttrib3d");
	Loader.loadGlArbSymbol(gVertexAttrib3dv, "glVertexAttrib3dv");
	Loader.loadGlArbSymbol(gVertexAttrib3f, "glVertexAttrib3f");
	Loader.loadGlArbSymbol(gVertexAttrib3fv, "glVertexAttrib3fv");
	Loader.loadGlArbSymbol(gVertexAttrib3s, "glVertexAttrib3s");
	Loader.loadGlArbSymbol(gVertexAttrib3sv, "glVertexAttrib3sv");
	Loader.loadGlArbSymbol(gVertexAttrib4Nbv, "glVertexAttrib4Nbv");
	Loader.loadGlArbSymbol(gVertexAttrib4Niv, "glVertexAttrib4Niv");
	Loader.loadGlArbSymbol(gVertexAttrib4Nsv, "glVertexAttrib4Nsv");
	Loader.loadGlArbSymbol(gVertexAttrib4Nub, "glVertexAttrib4Nub");
	Loader.loadGlArbSymbol(gVertexAttrib4Nubv, "glVertexAttrib4Nubv");
	Loader.loadGlArbSymbol(gVertexAttrib4Nuiv, "glVertexAttrib4Nuiv");
	Loader.loadGlArbSymbol(gVertexAttrib4Nusv, "glVertexAttrib4Nusv");
	Loader.loadGlArbSymbol(gVertexAttrib4bv, "glVertexAttrib4bv");
	Loader.loadGlArbSymbol(gVertexAttrib4d, "glVertexAttrib4d");
	Loader.loadGlArbSymbol(gVertexAttrib4dv, "glVertexAttrib4dv");
	Loader.loadGlArbSymbol(gVertexAttrib4f, "glVertexAttrib4f");
	Loader.loadGlArbSymbol(gVertexAttrib4fv, "glVertexAttrib4fv");
	Loader.loadGlArbSymbol(gVertexAttrib4iv, "glVertexAttrib4iv");
	Loader.loadGlArbSymbol(gVertexAttrib4s, "glVertexAttrib4s");
	Loader.loadGlArbSymbol(gVertexAttrib4sv, "glVertexAttrib4sv");
	Loader.loadGlArbSymbol(gVertexAttrib4ubv, "glVertexAttrib4ubv");
	Loader.loadGlArbSymbol(gVertexAttrib4uiv, "glVertexAttrib4uiv");
	Loader.loadGlArbSymbol(gVertexAttrib4usv, "glVertexAttrib4usv");
	Loader.loadGlArbSymbol(gVertexAttribPointer, "glVertexAttribPointer");
	Loader.loadGlArbSymbol(gUniformMatrix2x3fv, "glUniformMatrix2x3fv");
	Loader.loadGlArbSymbol(gUniformMatrix3x2fv, "glUniformMatrix3x2fv");
	Loader.loadGlArbSymbol(gUniformMatrix2x4fv, "glUniformMatrix2x4fv");
	Loader.loadGlArbSymbol(gUniformMatrix4x2fv, "glUniformMatrix4x2fv");
	Loader.loadGlArbSymbol(gUniformMatrix3x4fv, "glUniformMatrix3x4fv");
	Loader.loadGlArbSymbol(gUniformMatrix4x3fv, "glUniformMatrix4x3fv");
	Loader.loadGlArbSymbol(gColorMaski, "glColorMaski");
	Loader.loadGlArbSymbol(gGetBooleani_v, "glGetBooleani_v");
	Loader.loadGlArbSymbol(gGetIntegeri_v, "glGetIntegeri_v");
	Loader.loadGlArbSymbol(gEnablei, "glEnablei");
	Loader.loadGlArbSymbol(gDisablei, "glDisablei");
	Loader.loadGlArbSymbol(gIsEnabledi, "glIsEnabledi");
	Loader.loadGlArbSymbol(gBeginTransformFeedback, "glBeginTransformFeedback");
	Loader.loadGlArbSymbol(gEndTransformFeedback, "glEndTransformFeedback");
	Loader.loadGlArbSymbol(gBindBufferRange, "glBindBufferRange");
	Loader.loadGlArbSymbol(gBindBufferBase, "glBindBufferBase");
	Loader.loadGlArbSymbol(gTransformFeedbackVaryings, "glTransformFeedbackVaryings");
	Loader.loadGlArbSymbol(gGetTransformFeedbackVarying, "glGetTransformFeedbackVarying");
	Loader.loadGlArbSymbol(gClampColor, "glClampColor");
	Loader.loadGlArbSymbol(gBeginConditionalRender, "glBeginConditionalRender");
	Loader.loadGlArbSymbol(gEndConditionalRender, "glEndConditionalRender");
	Loader.loadGlArbSymbol(gVertexAttribIPointer, "glVertexAttribIPointer");
	Loader.loadGlArbSymbol(gGetVertexAttribIiv, "glGetVertexAttribIiv");
	Loader.loadGlArbSymbol(gGetVertexAttribIuiv, "glGetVertexAttribIuiv");
	Loader.loadGlArbSymbol(gVertexAttribI1i, "glVertexAttribI1i");
	Loader.loadGlArbSymbol(gVertexAttribI2i, "glVertexAttribI2i");
	Loader.loadGlArbSymbol(gVertexAttribI3i, "glVertexAttribI3i");
	Loader.loadGlArbSymbol(gVertexAttribI4i, "glVertexAttribI4i");
	Loader.loadGlArbSymbol(gVertexAttribI1ui, "glVertexAttribI1ui");
	Loader.loadGlArbSymbol(gVertexAttribI2ui, "glVertexAttribI2ui");
	Loader.loadGlArbSymbol(gVertexAttribI3ui, "glVertexAttribI3ui");
	Loader.loadGlArbSymbol(gVertexAttribI4ui, "glVertexAttribI4ui");
	Loader.loadGlArbSymbol(gVertexAttribI1iv, "glVertexAttribI1iv");
	Loader.loadGlArbSymbol(gVertexAttribI2iv, "glVertexAttribI2iv");
	Loader.loadGlArbSymbol(gVertexAttribI3iv, "glVertexAttribI3iv");
	Loader.loadGlArbSymbol(gVertexAttribI4iv, "glVertexAttribI4iv");
	Loader.loadGlArbSymbol(gVertexAttribI1uiv, "glVertexAttribI1uiv");
	Loader.loadGlArbSymbol(gVertexAttribI2uiv, "glVertexAttribI2uiv");
	Loader.loadGlArbSymbol(gVertexAttribI3uiv, "glVertexAttribI3uiv");
	Loader.loadGlArbSymbol(gVertexAttribI4uiv, "glVertexAttribI4uiv");
	Loader.loadGlArbSymbol(gVertexAttribI4bv, "glVertexAttribI4bv");
	Loader.loadGlArbSymbol(gVertexAttribI4sv, "glVertexAttribI4sv");
	Loader.loadGlArbSymbol(gVertexAttribI4ubv, "glVertexAttribI4ubv");
	Loader.loadGlArbSymbol(gVertexAttribI4usv, "glVertexAttribI4usv");
	Loader.loadGlArbSymbol(gGetUniformuiv, "glGetUniformuiv");
	Loader.loadGlArbSymbol(gBindFragDataLocation, "glBindFragDataLocation");
	Loader.loadGlArbSymbol(gGetFragDataLocation, "glGetFragDataLocation");
	Loader.loadGlArbSymbol(gUniform1ui, "glUniform1ui");
	Loader.loadGlArbSymbol(gUniform2ui, "glUniform2ui");
	Loader.loadGlArbSymbol(gUniform3ui, "glUniform3ui");
	Loader.loadGlArbSymbol(gUniform4ui, "glUniform4ui");
	Loader.loadGlArbSymbol(gUniform1uiv, "glUniform1uiv");
	Loader.loadGlArbSymbol(gUniform2uiv, "glUniform2uiv");
	Loader.loadGlArbSymbol(gUniform3uiv, "glUniform3uiv");
	Loader.loadGlArbSymbol(gUniform4uiv, "glUniform4uiv");
	Loader.loadGlArbSymbol(gTexParameterIiv, "glTexParameterIiv");
	Loader.loadGlArbSymbol(gTexParameterIuiv, "glTexParameterIuiv");
	Loader.loadGlArbSymbol(gGetTexParameterIiv, "glGetTexParameterIiv");
	Loader.loadGlArbSymbol(gGetTexParameterIuiv, "glGetTexParameterIuiv");
	Loader.loadGlArbSymbol(gClearBufferiv, "glClearBufferiv");
	Loader.loadGlArbSymbol(gClearBufferuiv, "glClearBufferuiv");
	Loader.loadGlArbSymbol(gClearBufferfv, "glClearBufferfv");
	Loader.loadGlArbSymbol(gClearBufferfi, "glClearBufferfi");
	Loader.loadGlArbSymbol(gGetStringi, "glGetStringi");
	Loader.loadGlArbSymbol(gDrawArraysInstanced, "glDrawArraysInstanced");
	Loader.loadGlArbSymbol(gDrawElementsInstanced, "glDrawElementsInstanced");
	Loader.loadGlArbSymbol(gTexBuffer, "glTexBuffer");
	Loader.loadGlArbSymbol(gPrimitiveRestartIndex, "glPrimitiveRestartIndex");
	Loader.loadGlArbSymbol(gGetInteger64i_v, "glGetInteger64i_v");
	Loader.loadGlArbSymbol(gGetBufferParameteri64v, "glGetBufferParameteri64v");
	Loader.loadGlArbSymbol(gFramebufferTexture, "glFramebufferTexture");
	Loader.loadGlArbSymbol(gVertexAttribDivisor, "glVertexAttribDivisor");
	Loader.loadGlArbSymbol(gMinSampleShading, "glMinSampleShading");
	Loader.loadGlArbSymbol(gBlendEquationi, "glBlendEquationi");
	Loader.loadGlArbSymbol(gBlendEquationSeparatei, "glBlendEquationSeparatei");
	Loader.loadGlArbSymbol(gBlendFunci, "glBlendFunci");
	Loader.loadGlArbSymbol(gBlendFuncSeparatei, "glBlendFuncSeparatei");
	Loader.loadGlArbSymbol(gIsRenderbuffer, "glIsRenderbuffer");
	Loader.loadGlArbSymbol(gBindRenderbuffer, "glBindRenderbuffer");
	Loader.loadGlArbSymbol(gDeleteRenderbuffers, "glDeleteRenderbuffers");
	Loader.loadGlArbSymbol(gGenRenderbuffers, "glGenRenderbuffers");
	Loader.loadGlArbSymbol(gRenderbufferStorage, "glRenderbufferStorage");
	Loader.loadGlArbSymbol(gGetRenderbufferParameteriv, "glGetRenderbufferParameteriv");
	Loader.loadGlArbSymbol(gIsFramebuffer, "glIsFramebuffer");
	Loader.loadGlArbSymbol(gBindFramebuffer, "glBindFramebuffer");
	Loader.loadGlArbSymbol(gDeleteFramebuffers, "glDeleteFramebuffers");
	Loader.loadGlArbSymbol(gGenFramebuffers, "glGenFramebuffers");
	Loader.loadGlArbSymbol(gCheckFramebufferStatus, "glCheckFramebufferStatus");
	Loader.loadGlArbSymbol(gFramebufferTexture1D, "glFramebufferTexture1D");
	Loader.loadGlArbSymbol(gFramebufferTexture2D, "glFramebufferTexture2D");
	Loader.loadGlArbSymbol(gFramebufferTexture3D, "glFramebufferTexture3D");
	Loader.loadGlArbSymbol(gFramebufferRenderbuffer, "glFramebufferRenderbuffer");
	Loader.loadGlArbSymbol(gGetFramebufferAttachmentParameteriv, "glGetFramebufferAttachmentParameteriv");
	Loader.loadGlArbSymbol(gGenerateMipmap, "glGenerateMipmap");
	Loader.loadGlArbSymbol(gBlitFramebuffer, "glBlitFramebuffer");
	Loader.loadGlArbSymbol(gRenderbufferStorageMultisample, "glRenderbufferStorageMultisample");
	Loader.loadGlArbSymbol(gFramebufferTextureLayer, "glFramebufferTextureLayer");
	Loader.loadGlArbSymbol(gMapBufferRange, "glMapBufferRange");
	Loader.loadGlArbSymbol(gFlushMappedBufferRange, "glFlushMappedBufferRange");
	Loader.loadGlArbSymbol(gBindVertexArray, "glBindVertexArray");
	Loader.loadGlArbSymbol(gDeleteVertexArrays, "glDeleteVertexArrays");
	Loader.loadGlArbSymbol(gGenVertexArrays, "glGenVertexArrays");
	Loader.loadGlArbSymbol(gIsVertexArray, "glIsVertexArray");
	Loader.loadGlArbSymbol(gGetUniformIndices, "glGetUniformIndices");
	Loader.loadGlArbSymbol(gGetActiveUniformsiv, "glGetActiveUniformsiv");
	Loader.loadGlArbSymbol(gGetActiveUniformName, "glGetActiveUniformName");
	Loader.loadGlArbSymbol(gGetUniformBlockIndex, "glGetUniformBlockIndex");
	Loader.loadGlArbSymbol(gGetActiveUniformBlockiv, "glGetActiveUniformBlockiv");
	Loader.loadGlArbSymbol(gGetActiveUniformBlockName, "glGetActiveUniformBlockName");
	Loader.loadGlArbSymbol(gUniformBlockBinding, "glUniformBlockBinding");
	Loader.loadGlArbSymbol(gCopyBufferSubData, "glCopyBufferSubData");
	Loader.loadGlArbSymbol(gDrawElementsBaseVertex, "glDrawElementsBaseVertex");
	Loader.loadGlArbSymbol(gDrawRangeElementsBaseVertex, "glDrawRangeElementsBaseVertex");
	Loader.loadGlArbSymbol(gDrawElementsInstancedBaseVertex, "glDrawElementsInstancedBaseVertex");
	Loader.loadGlArbSymbol(gMultiDrawElementsBaseVertex, "glMultiDrawElementsBaseVertex");
	Loader.loadGlArbSymbol(gProvokingVertex, "glProvokingVertex");
	Loader.loadGlArbSymbol(gFenceSync, "glFenceSync");
	Loader.loadGlArbSymbol(gIsSync, "glIsSync");
	Loader.loadGlArbSymbol(gDeleteSync, "glDeleteSync");
	Loader.loadGlArbSymbol(gClientWaitSync, "glClientWaitSync");
	Loader.loadGlArbSymbol(gWaitSync, "glWaitSync");
	Loader.loadGlArbSymbol(gGetInteger64v, "glGetInteger64v");
	Loader.loadGlArbSymbol(gGetSynciv, "glGetSynciv");
	Loader.loadGlArbSymbol(gTexImage2DMultisample, "glTexImage2DMultisample");
	Loader.loadGlArbSymbol(gTexImage3DMultisample, "glTexImage3DMultisample");
	Loader.loadGlArbSymbol(gGetMultisamplefv, "glGetMultisamplefv");
	Loader.loadGlArbSymbol(gSampleMaski, "glSampleMaski");
	Loader.loadGlArbSymbol(gBlendEquationiARB, "glBlendEquationiARB");
	Loader.loadGlArbSymbol(gBlendEquationSeparateiARB, "glBlendEquationSeparateiARB");
	Loader.loadGlArbSymbol(gBlendFunciARB, "glBlendFunciARB");
	Loader.loadGlArbSymbol(gBlendFuncSeparateiARB, "glBlendFuncSeparateiARB");
	Loader.loadGlArbSymbol(gMinSampleShadingARB, "glMinSampleShadingARB");
	Loader.loadGlArbSymbol(gNamedStringARB, "glNamedStringARB");
	Loader.loadGlArbSymbol(gDeleteNamedStringARB, "glDeleteNamedStringARB");
	Loader.loadGlArbSymbol(gCompileShaderIncludeARB, "glCompileShaderIncludeARB");
	Loader.loadGlArbSymbol(gIsNamedStringARB, "glIsNamedStringARB");
	Loader.loadGlArbSymbol(gGetNamedStringARB, "glGetNamedStringARB");
	Loader.loadGlArbSymbol(gGetNamedStringivARB, "glGetNamedStringivARB");
	Loader.loadGlArbSymbol(gBindFragDataLocationIndexed, "glBindFragDataLocationIndexed");
	Loader.loadGlArbSymbol(gGetFragDataIndex, "glGetFragDataIndex");
	Loader.loadGlArbSymbol(gGenSamplers, "glGenSamplers");
	Loader.loadGlArbSymbol(gDeleteSamplers, "glDeleteSamplers");
	Loader.loadGlArbSymbol(gIsSampler, "glIsSampler");
	Loader.loadGlArbSymbol(gBindSampler, "glBindSampler");
	Loader.loadGlArbSymbol(gSamplerParameteri, "glSamplerParameteri");
	Loader.loadGlArbSymbol(gSamplerParameteriv, "glSamplerParameteriv");
	Loader.loadGlArbSymbol(gSamplerParameterf, "glSamplerParameterf");
	Loader.loadGlArbSymbol(gSamplerParameterfv, "glSamplerParameterfv");
	Loader.loadGlArbSymbol(gSamplerParameterIiv, "glSamplerParameterIiv");
	Loader.loadGlArbSymbol(gSamplerParameterIuiv, "glSamplerParameterIuiv");
	Loader.loadGlArbSymbol(gGetSamplerParameteriv, "glGetSamplerParameteriv");
	Loader.loadGlArbSymbol(gGetSamplerParameterIiv, "glGetSamplerParameterIiv");
	Loader.loadGlArbSymbol(gGetSamplerParameterfv, "glGetSamplerParameterfv");
	Loader.loadGlArbSymbol(gGetSamplerParameterIuiv, "glGetSamplerParameterIuiv");
	Loader.loadGlArbSymbol(gQueryCounter, "glQueryCounter");
	Loader.loadGlArbSymbol(gGetQueryObjecti64v, "glGetQueryObjecti64v");
	Loader.loadGlArbSymbol(gGetQueryObjectui64v, "glGetQueryObjectui64v");
	Loader.loadGlArbSymbol(gDrawArraysIndirect, "glDrawArraysIndirect");
	Loader.loadGlArbSymbol(gDrawElementsIndirect, "glDrawElementsIndirect");
	Loader.loadGlArbSymbol(gUniform1d, "glUniform1d");
	Loader.loadGlArbSymbol(gUniform2d, "glUniform2d");
	Loader.loadGlArbSymbol(gUniform3d, "glUniform3d");
	Loader.loadGlArbSymbol(gUniform4d, "glUniform4d");
	Loader.loadGlArbSymbol(gUniform1dv, "glUniform1dv");
	Loader.loadGlArbSymbol(gUniform2dv, "glUniform2dv");
	Loader.loadGlArbSymbol(gUniform3dv, "glUniform3dv");
	Loader.loadGlArbSymbol(gUniform4dv, "glUniform4dv");
	Loader.loadGlArbSymbol(gUniformMatrix2dv, "glUniformMatrix2dv");
	Loader.loadGlArbSymbol(gUniformMatrix3dv, "glUniformMatrix3dv");
	Loader.loadGlArbSymbol(gUniformMatrix4dv, "glUniformMatrix4dv");
	Loader.loadGlArbSymbol(gUniformMatrix2x3dv, "glUniformMatrix2x3dv");
	Loader.loadGlArbSymbol(gUniformMatrix2x4dv, "glUniformMatrix2x4dv");
	Loader.loadGlArbSymbol(gUniformMatrix3x2dv, "glUniformMatrix3x2dv");
	Loader.loadGlArbSymbol(gUniformMatrix3x4dv, "glUniformMatrix3x4dv");
	Loader.loadGlArbSymbol(gUniformMatrix4x2dv, "glUniformMatrix4x2dv");
	Loader.loadGlArbSymbol(gUniformMatrix4x3dv, "glUniformMatrix4x3dv");
	Loader.loadGlArbSymbol(gGetUniformdv, "glGetUniformdv");
	Loader.loadGlArbSymbol(gGetSubroutineUniformLocation, "glGetSubroutineUniformLocation");
	Loader.loadGlArbSymbol(gGetSubroutineIndex, "glGetSubroutineIndex");
	Loader.loadGlArbSymbol(gGetActiveSubroutineUniformiv, "glGetActiveSubroutineUniformiv");
	Loader.loadGlArbSymbol(gGetActiveSubroutineUniformName, "glGetActiveSubroutineUniformName");
	Loader.loadGlArbSymbol(gGetActiveSubroutineName, "glGetActiveSubroutineName");
	Loader.loadGlArbSymbol(gUniformSubroutinesuiv, "glUniformSubroutinesuiv");
	Loader.loadGlArbSymbol(gGetUniformSubroutineuiv, "glGetUniformSubroutineuiv");
	Loader.loadGlArbSymbol(gGetProgramStageiv, "glGetProgramStageiv");
	Loader.loadGlArbSymbol(gPatchParameteri, "glPatchParameteri");
	Loader.loadGlArbSymbol(gPatchParameterfv, "glPatchParameterfv");
	Loader.loadGlArbSymbol(gBindTransformFeedback, "glBindTransformFeedback");
	Loader.loadGlArbSymbol(gDeleteTransformFeedbacks, "glDeleteTransformFeedbacks");
	Loader.loadGlArbSymbol(gGenTransformFeedbacks, "glGenTransformFeedbacks");
	Loader.loadGlArbSymbol(gIsTransformFeedback, "glIsTransformFeedback");
	Loader.loadGlArbSymbol(gPauseTransformFeedback, "glPauseTransformFeedback");
	Loader.loadGlArbSymbol(gResumeTransformFeedback, "glResumeTransformFeedback");
	Loader.loadGlArbSymbol(gDrawTransformFeedback, "glDrawTransformFeedback");
	Loader.loadGlArbSymbol(gDrawTransformFeedbackStream, "glDrawTransformFeedbackStream");
	Loader.loadGlArbSymbol(gBeginQueryIndexed, "glBeginQueryIndexed");
	Loader.loadGlArbSymbol(gEndQueryIndexed, "glEndQueryIndexed");
	Loader.loadGlArbSymbol(gGetQueryIndexediv, "glGetQueryIndexediv");
	Loader.loadGlArbSymbol(gReleaseShaderCompiler, "glReleaseShaderCompiler");
	Loader.loadGlArbSymbol(gShaderBinary, "glShaderBinary");
	Loader.loadGlArbSymbol(gGetShaderPrecisionFormat, "glGetShaderPrecisionFormat");
	Loader.loadGlArbSymbol(gDepthRangef, "glDepthRangef");
	Loader.loadGlArbSymbol(gClearDepthf, "glClearDepthf");
	Loader.loadGlArbSymbol(gGetProgramBinary, "glGetProgramBinary");
	Loader.loadGlArbSymbol(gProgramBinary, "glProgramBinary");
	Loader.loadGlArbSymbol(gProgramParameteri, "glProgramParameteri");
	Loader.loadGlArbSymbol(gUseProgramStages, "glUseProgramStages");
	Loader.loadGlArbSymbol(gActiveShaderProgram, "glActiveShaderProgram");
	Loader.loadGlArbSymbol(gCreateShaderProgramv, "glCreateShaderProgramv");
	Loader.loadGlArbSymbol(gBindProgramPipeline, "glBindProgramPipeline");
	Loader.loadGlArbSymbol(gDeleteProgramPipelines, "glDeleteProgramPipelines");
	Loader.loadGlArbSymbol(gGenProgramPipelines, "glGenProgramPipelines");
	Loader.loadGlArbSymbol(gIsProgramPipeline, "glIsProgramPipeline");
	Loader.loadGlArbSymbol(gGetProgramPipelineiv, "glGetProgramPipelineiv");
	Loader.loadGlArbSymbol(gProgramUniform1i, "glProgramUniform1i");
	Loader.loadGlArbSymbol(gProgramUniform1iv, "glProgramUniform1iv");
	Loader.loadGlArbSymbol(gProgramUniform1f, "glProgramUniform1f");
	Loader.loadGlArbSymbol(gProgramUniform1fv, "glProgramUniform1fv");
	Loader.loadGlArbSymbol(gProgramUniform1d, "glProgramUniform1d");
	Loader.loadGlArbSymbol(gProgramUniform1dv, "glProgramUniform1dv");
	Loader.loadGlArbSymbol(gProgramUniform1ui, "glProgramUniform1ui");
	Loader.loadGlArbSymbol(gProgramUniform1uiv, "glProgramUniform1uiv");
	Loader.loadGlArbSymbol(gProgramUniform2i, "glProgramUniform2i");
	Loader.loadGlArbSymbol(gProgramUniform2iv, "glProgramUniform2iv");
	Loader.loadGlArbSymbol(gProgramUniform2f, "glProgramUniform2f");
	Loader.loadGlArbSymbol(gProgramUniform2fv, "glProgramUniform2fv");
	Loader.loadGlArbSymbol(gProgramUniform2d, "glProgramUniform2d");
	Loader.loadGlArbSymbol(gProgramUniform2dv, "glProgramUniform2dv");
	Loader.loadGlArbSymbol(gProgramUniform2ui, "glProgramUniform2ui");
	Loader.loadGlArbSymbol(gProgramUniform2uiv, "glProgramUniform2uiv");
	Loader.loadGlArbSymbol(gProgramUniform3i, "glProgramUniform3i");
	Loader.loadGlArbSymbol(gProgramUniform3iv, "glProgramUniform3iv");
	Loader.loadGlArbSymbol(gProgramUniform3f, "glProgramUniform3f");
	Loader.loadGlArbSymbol(gProgramUniform3fv, "glProgramUniform3fv");
	Loader.loadGlArbSymbol(gProgramUniform3d, "glProgramUniform3d");
	Loader.loadGlArbSymbol(gProgramUniform3dv, "glProgramUniform3dv");
	Loader.loadGlArbSymbol(gProgramUniform3ui, "glProgramUniform3ui");
	Loader.loadGlArbSymbol(gProgramUniform3uiv, "glProgramUniform3uiv");
	Loader.loadGlArbSymbol(gProgramUniform4i, "glProgramUniform4i");
	Loader.loadGlArbSymbol(gProgramUniform4iv, "glProgramUniform4iv");
	Loader.loadGlArbSymbol(gProgramUniform4f, "glProgramUniform4f");
	Loader.loadGlArbSymbol(gProgramUniform4fv, "glProgramUniform4fv");
	Loader.loadGlArbSymbol(gProgramUniform4d, "glProgramUniform4d");
	Loader.loadGlArbSymbol(gProgramUniform4dv, "glProgramUniform4dv");
	Loader.loadGlArbSymbol(gProgramUniform4ui, "glProgramUniform4ui");
	Loader.loadGlArbSymbol(gProgramUniform4uiv, "glProgramUniform4uiv");
	Loader.loadGlArbSymbol(gProgramUniformMatrix2fv, "glProgramUniformMatrix2fv");
	Loader.loadGlArbSymbol(gProgramUniformMatrix3fv, "glProgramUniformMatrix3fv");
	Loader.loadGlArbSymbol(gProgramUniformMatrix4fv, "glProgramUniformMatrix4fv");
	Loader.loadGlArbSymbol(gProgramUniformMatrix2dv, "glProgramUniformMatrix2dv");
	Loader.loadGlArbSymbol(gProgramUniformMatrix3dv, "glProgramUniformMatrix3dv");
	Loader.loadGlArbSymbol(gProgramUniformMatrix4dv, "glProgramUniformMatrix4dv");
	Loader.loadGlArbSymbol(gProgramUniformMatrix2x3fv, "glProgramUniformMatrix2x3fv");
	Loader.loadGlArbSymbol(gProgramUniformMatrix3x2fv, "glProgramUniformMatrix3x2fv");
	Loader.loadGlArbSymbol(gProgramUniformMatrix2x4fv, "glProgramUniformMatrix2x4fv");
	Loader.loadGlArbSymbol(gProgramUniformMatrix4x2fv, "glProgramUniformMatrix4x2fv");
	Loader.loadGlArbSymbol(gProgramUniformMatrix3x4fv, "glProgramUniformMatrix3x4fv");
	Loader.loadGlArbSymbol(gProgramUniformMatrix4x3fv, "glProgramUniformMatrix4x3fv");
	Loader.loadGlArbSymbol(gProgramUniformMatrix2x3dv, "glProgramUniformMatrix2x3dv");
	Loader.loadGlArbSymbol(gProgramUniformMatrix3x2dv, "glProgramUniformMatrix3x2dv");
	Loader.loadGlArbSymbol(gProgramUniformMatrix2x4dv, "glProgramUniformMatrix2x4dv");
	Loader.loadGlArbSymbol(gProgramUniformMatrix4x2dv, "glProgramUniformMatrix4x2dv");
	Loader.loadGlArbSymbol(gProgramUniformMatrix3x4dv, "glProgramUniformMatrix3x4dv");
	Loader.loadGlArbSymbol(gProgramUniformMatrix4x3dv, "glProgramUniformMatrix4x3dv");
	Loader.loadGlArbSymbol(gValidateProgramPipeline, "glValidateProgramPipeline");
	Loader.loadGlArbSymbol(gGetProgramPipelineInfoLog, "glGetProgramPipelineInfoLog");
	Loader.loadGlArbSymbol(gVertexAttribL1d, "glVertexAttribL1d");
	Loader.loadGlArbSymbol(gVertexAttribL2d, "glVertexAttribL2d");
	Loader.loadGlArbSymbol(gVertexAttribL3d, "glVertexAttribL3d");
	Loader.loadGlArbSymbol(gVertexAttribL4d, "glVertexAttribL4d");
	Loader.loadGlArbSymbol(gVertexAttribL1dv, "glVertexAttribL1dv");
	Loader.loadGlArbSymbol(gVertexAttribL2dv, "glVertexAttribL2dv");
	Loader.loadGlArbSymbol(gVertexAttribL3dv, "glVertexAttribL3dv");
	Loader.loadGlArbSymbol(gVertexAttribL4dv, "glVertexAttribL4dv");
	Loader.loadGlArbSymbol(gVertexAttribLPointer, "glVertexAttribLPointer");
	Loader.loadGlArbSymbol(gGetVertexAttribLdv, "glGetVertexAttribLdv");
	Loader.loadGlArbSymbol(gViewportArrayv, "glViewportArrayv");
	Loader.loadGlArbSymbol(gViewportIndexedf, "glViewportIndexedf");
	Loader.loadGlArbSymbol(gViewportIndexedfv, "glViewportIndexedfv");
	Loader.loadGlArbSymbol(gScissorArrayv, "glScissorArrayv");
	Loader.loadGlArbSymbol(gScissorIndexed, "glScissorIndexed");
	Loader.loadGlArbSymbol(gScissorIndexedv, "glScissorIndexedv");
	Loader.loadGlArbSymbol(gDepthRangeArrayv, "glDepthRangeArrayv");
	Loader.loadGlArbSymbol(gDepthRangeIndexed, "glDepthRangeIndexed");
	Loader.loadGlArbSymbol(gGetFloati_v, "glGetFloati_v");
	Loader.loadGlArbSymbol(gGetDoublei_v, "glGetDoublei_v");
	Loader.loadGlArbSymbol(gCreateSyncFromCLeventARB, "glCreateSyncFromCLeventARB");
	Loader.loadGlArbSymbol(gDebugMessageControlARB, "glDebugMessageControlARB");
	Loader.loadGlArbSymbol(gDebugMessageInsertARB, "glDebugMessageInsertARB");
	Loader.loadGlArbSymbol(gDebugMessageCallbackARB, "glDebugMessageCallbackARB");
	Loader.loadGlArbSymbol(gGetDebugMessageLogARB, "glGetDebugMessageLogARB");
	Loader.loadGlArbSymbol(gGetGraphicsResetStatusARB, "glGetGraphicsResetStatusARB");
	Loader.loadGlArbSymbol(gGetnMapdvARB, "glGetnMapdvARB");
	Loader.loadGlArbSymbol(gGetnMapfvARB, "glGetnMapfvARB");
	Loader.loadGlArbSymbol(gGetnMapivARB, "glGetnMapivARB");
	Loader.loadGlArbSymbol(gGetnPixelMapfvARB, "glGetnPixelMapfvARB");
	Loader.loadGlArbSymbol(gGetnPixelMapuivARB, "glGetnPixelMapuivARB");
	Loader.loadGlArbSymbol(gGetnPixelMapusvARB, "glGetnPixelMapusvARB");
	Loader.loadGlArbSymbol(gGetnPolygonStippleARB, "glGetnPolygonStippleARB");
	Loader.loadGlArbSymbol(gGetnColorTableARB, "glGetnColorTableARB");
	Loader.loadGlArbSymbol(gGetnConvolutionFilterARB, "glGetnConvolutionFilterARB");
	Loader.loadGlArbSymbol(gGetnSeparableFilterARB, "glGetnSeparableFilterARB");
	Loader.loadGlArbSymbol(gGetnHistogramARB, "glGetnHistogramARB");
	Loader.loadGlArbSymbol(gGetnMinmaxARB, "glGetnMinmaxARB");
	Loader.loadGlArbSymbol(gGetnTexImageARB, "glGetnTexImageARB");
	Loader.loadGlArbSymbol(gReadnPixelsARB, "glReadnPixelsARB");
	Loader.loadGlArbSymbol(gGetnCompressedTexImageARB, "glGetnCompressedTexImageARB");
	Loader.loadGlArbSymbol(gGetnUniformfvARB, "glGetnUniformfvARB");
	Loader.loadGlArbSymbol(gGetnUniformivARB, "glGetnUniformivARB");
	Loader.loadGlArbSymbol(gGetnUniformuivARB, "glGetnUniformuivARB");
	Loader.loadGlArbSymbol(gGetnUniformdvARB, "glGetnUniformdvARB");
	Loader.loadGlArbSymbol(gDrawArraysInstancedBaseInstance, "glDrawArraysInstancedBaseInstance");
	Loader.loadGlArbSymbol(gDrawElementsInstancedBaseInstance, "glDrawElementsInstancedBaseInstance");
	Loader.loadGlArbSymbol(gDrawElementsInstancedBaseVertexBaseInstance, "glDrawElementsInstancedBaseVertexBaseInstance");
	Loader.loadGlArbSymbol(gDrawTransformFeedbackInstanced, "glDrawTransformFeedbackInstanced");
	Loader.loadGlArbSymbol(gDrawTransformFeedbackStreamInstanced, "glDrawTransformFeedbackStreamInstanced");
	Loader.loadGlArbSymbol(gGetInternalformativ, "glGetInternalformativ");
	Loader.loadGlArbSymbol(gGetActiveAtomicCounterBufferiv, "glGetActiveAtomicCounterBufferiv");
	Loader.loadGlArbSymbol(gBindImageTexture, "glBindImageTexture");
	Loader.loadGlArbSymbol(gMemoryBarrier, "glMemoryBarrier");
	Loader.loadGlArbSymbol(gTexStorage1D, "glTexStorage1D");
	Loader.loadGlArbSymbol(gTexStorage2D, "glTexStorage2D");
	Loader.loadGlArbSymbol(gTexStorage3D, "glTexStorage3D");
	Loader.loadGlArbSymbol(gTextureStorage1DEXT, "glTextureStorage1DEXT");
	Loader.loadGlArbSymbol(gTextureStorage2DEXT, "glTextureStorage2DEXT");
	Loader.loadGlArbSymbol(gTextureStorage3DEXT, "glTextureStorage3DEXT");
}

}
}
}

namespace Twil {
namespace Gl {
namespace Procs {

void glCullFace(GLenum mode)
{
	gCullFace(mode);
	checkError();
}

void glFrontFace(GLenum mode)
{
	gFrontFace(mode);
	checkError();
}

void glHint(GLenum target, GLenum mode)
{
	gHint(target, mode);
	checkError();
}

void glLineWidth(GLfloat width)
{
	gLineWidth(width);
	checkError();
}

void glPointSize(GLfloat size)
{
	gPointSize(size);
	checkError();
}

void glPolygonMode(GLenum face, GLenum mode)
{
	gPolygonMode(face, mode);
	checkError();
}

void glScissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
	gScissor(x, y, width, height);
	checkError();
}

void glTexParameterf(GLenum target, GLenum pname, GLfloat param)
{
	gTexParameterf(target, pname, param);
	checkError();
}

void glTexParameterfv(GLenum target, GLenum pname, GLfloat const * params)
{
	gTexParameterfv(target, pname, params);
	checkError();
}

void glTexParameteri(GLenum target, GLenum pname, GLint param)
{
	gTexParameteri(target, pname, param);
	checkError();
}

void glTexParameteriv(GLenum target, GLenum pname, GLint const * params)
{
	gTexParameteriv(target, pname, params);
	checkError();
}

void glTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, GLvoid const * pixels)
{
	gTexImage1D(target, level, internalformat, width, border, format, type, pixels);
	checkError();
}

void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, GLvoid const * pixels)
{
	gTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
	checkError();
}

void glDrawBuffer(GLenum mode)
{
	gDrawBuffer(mode);
	checkError();
}

void glClear(GLbitfield mask)
{
	gClear(mask);
	checkError();
}

void glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	gClearColor(red, green, blue, alpha);
	checkError();
}

void glClearStencil(GLint s)
{
	gClearStencil(s);
	checkError();
}

void glClearDepth(GLclampd depth)
{
	gClearDepth(depth);
	checkError();
}

void glStencilMask(GLuint mask)
{
	gStencilMask(mask);
	checkError();
}

void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	gColorMask(red, green, blue, alpha);
	checkError();
}

void glDepthMask(GLboolean flag)
{
	gDepthMask(flag);
	checkError();
}

void glDisable(GLenum cap)
{
	gDisable(cap);
	checkError();
}

void glEnable(GLenum cap)
{
	gEnable(cap);
	checkError();
}

void glFinish()
{
	gFinish();
	checkError();
}

void glFlush()
{
	gFlush();
	checkError();
}

void glBlendFunc(GLenum sfactor, GLenum dfactor)
{
	gBlendFunc(sfactor, dfactor);
	checkError();
}

void glLogicOp(GLenum opcode)
{
	gLogicOp(opcode);
	checkError();
}

void glStencilFunc(GLenum func, GLint ref, GLuint mask)
{
	gStencilFunc(func, ref, mask);
	checkError();
}

void glStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
{
	gStencilOp(fail, zfail, zpass);
	checkError();
}

void glDepthFunc(GLenum func)
{
	gDepthFunc(func);
	checkError();
}

void glPixelStoref(GLenum pname, GLfloat param)
{
	gPixelStoref(pname, param);
	checkError();
}

void glPixelStorei(GLenum pname, GLint param)
{
	gPixelStorei(pname, param);
	checkError();
}

void glReadBuffer(GLenum mode)
{
	gReadBuffer(mode);
	checkError();
}

void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid * pixels)
{
	gReadPixels(x, y, width, height, format, type, pixels);
	checkError();
}

void glGetBooleanv(GLenum pname, GLboolean * params)
{
	gGetBooleanv(pname, params);
	checkError();
}

void glGetDoublev(GLenum pname, GLdouble * params)
{
	gGetDoublev(pname, params);
	checkError();
}

GLenum glGetError()
{
	auto result = gGetError();
	checkError();
	return result;
}

void glGetFloatv(GLenum pname, GLfloat * params)
{
	gGetFloatv(pname, params);
	checkError();
}

void glGetIntegerv(GLenum pname, GLint * params)
{
	gGetIntegerv(pname, params);
	checkError();
}

GLubyte const * glGetString(GLenum name)
{
	auto result = gGetString(name);
	checkError();
	return result;
}

void glGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLvoid * pixels)
{
	gGetTexImage(target, level, format, type, pixels);
	checkError();
}

void glGetTexParameterfv(GLenum target, GLenum pname, GLfloat * params)
{
	gGetTexParameterfv(target, pname, params);
	checkError();
}

void glGetTexParameteriv(GLenum target, GLenum pname, GLint * params)
{
	gGetTexParameteriv(target, pname, params);
	checkError();
}

void glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat * params)
{
	gGetTexLevelParameterfv(target, level, pname, params);
	checkError();
}

void glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint * params)
{
	gGetTexLevelParameteriv(target, level, pname, params);
	checkError();
}

GLboolean glIsEnabled(GLenum cap)
{
	auto result = gIsEnabled(cap);
	checkError();
	return result;
}

void glDepthRange(GLclampd near, GLclampd far)
{
	gDepthRange(near, far);
	checkError();
}

void glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	gViewport(x, y, width, height);
	checkError();
}

void glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
	gDrawArrays(mode, first, count);
	checkError();
}

void glDrawElements(GLenum mode, GLsizei count, GLenum type, GLvoid const * indices)
{
	gDrawElements(mode, count, type, indices);
	checkError();
}

void glGetPointerv(GLenum pname, GLvoid * * params)
{
	gGetPointerv(pname, params);
	checkError();
}

void glPolygonOffset(GLfloat factor, GLfloat units)
{
	gPolygonOffset(factor, units);
	checkError();
}

void glCopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border)
{
	gCopyTexImage1D(target, level, internalformat, x, y, width, border);
	checkError();
}

void glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
	gCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
	checkError();
}

void glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
{
	gCopyTexSubImage1D(target, level, xoffset, x, y, width);
	checkError();
}

void glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	gCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
	checkError();
}

void glTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, GLvoid const * pixels)
{
	gTexSubImage1D(target, level, xoffset, width, format, type, pixels);
	checkError();
}

void glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid const * pixels)
{
	gTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
	checkError();
}

void glBindTexture(GLenum target, GLuint texture)
{
	gBindTexture(target, texture);
	checkError();
}

void glDeleteTextures(GLsizei n, GLuint const * textures)
{
	gDeleteTextures(n, textures);
	checkError();
}

void glGenTextures(GLsizei n, GLuint * textures)
{
	gGenTextures(n, textures);
	checkError();
}

GLboolean glIsTexture(GLuint texture)
{
	auto result = gIsTexture(texture);
	checkError();
	return result;
}

void glBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	gBlendColor(red, green, blue, alpha);
	checkError();
}

void glBlendEquation(GLenum mode)
{
	gBlendEquation(mode);
	checkError();
}

void glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, GLvoid const * indices)
{
	gDrawRangeElements(mode, start, end, count, type, indices);
	checkError();
}

void glTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, GLvoid const * pixels)
{
	gTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
	checkError();
}

void glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLvoid const * pixels)
{
	gTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
	checkError();
}

void glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	gCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
	checkError();
}

void glActiveTexture(GLenum texture)
{
	gActiveTexture(texture);
	checkError();
}

void glSampleCoverage(GLclampf value, GLboolean invert)
{
	gSampleCoverage(value, invert);
	checkError();
}

void glCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, GLvoid const * data)
{
	gCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
	checkError();
}

void glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, GLvoid const * data)
{
	gCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
	checkError();
}

void glCompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, GLvoid const * data)
{
	gCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);
	checkError();
}

void glCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, GLvoid const * data)
{
	gCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
	checkError();
}

void glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, GLvoid const * data)
{
	gCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
	checkError();
}

void glCompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, GLvoid const * data)
{
	gCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
	checkError();
}

void glGetCompressedTexImage(GLenum target, GLint level, GLvoid * img)
{
	gGetCompressedTexImage(target, level, img);
	checkError();
}

void glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
{
	gBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
	checkError();
}

void glMultiDrawArrays(GLenum mode, GLint const * first, GLsizei const * count, GLsizei primcount)
{
	gMultiDrawArrays(mode, first, count, primcount);
	checkError();
}

void glMultiDrawElements(GLenum mode, GLsizei const * count, GLenum type, GLvoid const * * indices, GLsizei primcount)
{
	gMultiDrawElements(mode, count, type, indices, primcount);
	checkError();
}

void glPointParameterf(GLenum pname, GLfloat param)
{
	gPointParameterf(pname, param);
	checkError();
}

void glPointParameterfv(GLenum pname, GLfloat const * params)
{
	gPointParameterfv(pname, params);
	checkError();
}

void glPointParameteri(GLenum pname, GLint param)
{
	gPointParameteri(pname, param);
	checkError();
}

void glPointParameteriv(GLenum pname, GLint const * params)
{
	gPointParameteriv(pname, params);
	checkError();
}

void glGenQueries(GLsizei n, GLuint * ids)
{
	gGenQueries(n, ids);
	checkError();
}

void glDeleteQueries(GLsizei n, GLuint const * ids)
{
	gDeleteQueries(n, ids);
	checkError();
}

GLboolean glIsQuery(GLuint id)
{
	auto result = gIsQuery(id);
	checkError();
	return result;
}

void glBeginQuery(GLenum target, GLuint id)
{
	gBeginQuery(target, id);
	checkError();
}

void glEndQuery(GLenum target)
{
	gEndQuery(target);
	checkError();
}

void glGetQueryiv(GLenum target, GLenum pname, GLint * params)
{
	gGetQueryiv(target, pname, params);
	checkError();
}

void glGetQueryObjectiv(GLuint id, GLenum pname, GLint * params)
{
	gGetQueryObjectiv(id, pname, params);
	checkError();
}

void glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint * params)
{
	gGetQueryObjectuiv(id, pname, params);
	checkError();
}

void glBindBuffer(GLenum target, GLuint buffer)
{
	gBindBuffer(target, buffer);
	checkError();
}

void glDeleteBuffers(GLsizei n, GLuint const * buffers)
{
	gDeleteBuffers(n, buffers);
	checkError();
}

void glGenBuffers(GLsizei n, GLuint * buffers)
{
	gGenBuffers(n, buffers);
	checkError();
}

GLboolean glIsBuffer(GLuint buffer)
{
	auto result = gIsBuffer(buffer);
	checkError();
	return result;
}

void glBufferData(GLenum target, GLsizeiptr size, GLvoid const * data, GLenum usage)
{
	gBufferData(target, size, data, usage);
	checkError();
}

void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid const * data)
{
	gBufferSubData(target, offset, size, data);
	checkError();
}

void glGetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid * data)
{
	gGetBufferSubData(target, offset, size, data);
	checkError();
}

GLvoid * glMapBuffer(GLenum target, GLenum access)
{
	auto result = gMapBuffer(target, access);
	checkError();
	return result;
}

GLboolean glUnmapBuffer(GLenum target)
{
	auto result = gUnmapBuffer(target);
	checkError();
	return result;
}

void glGetBufferParameteriv(GLenum target, GLenum pname, GLint * params)
{
	gGetBufferParameteriv(target, pname, params);
	checkError();
}

void glGetBufferPointerv(GLenum target, GLenum pname, GLvoid * * params)
{
	gGetBufferPointerv(target, pname, params);
	checkError();
}

void glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
	gBlendEquationSeparate(modeRGB, modeAlpha);
	checkError();
}

void glDrawBuffers(GLsizei n, GLenum const * bufs)
{
	gDrawBuffers(n, bufs);
	checkError();
}

void glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass)
{
	gStencilOpSeparate(face, sfail, dpfail, dppass);
	checkError();
}

void glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
{
	gStencilFuncSeparate(face, func, ref, mask);
	checkError();
}

void glStencilMaskSeparate(GLenum face, GLuint mask)
{
	gStencilMaskSeparate(face, mask);
	checkError();
}

void glAttachShader(GLuint program, GLuint shader)
{
	gAttachShader(program, shader);
	checkError();
}

void glBindAttribLocation(GLuint program, GLuint index, GLchar const * name)
{
	gBindAttribLocation(program, index, name);
	checkError();
}

void glCompileShader(GLuint shader)
{
	gCompileShader(shader);
	checkError();
}

GLuint glCreateProgram()
{
	auto result = gCreateProgram();
	checkError();
	return result;
}

GLuint glCreateShader(GLenum type)
{
	auto result = gCreateShader(type);
	checkError();
	return result;
}

void glDeleteProgram(GLuint program)
{
	gDeleteProgram(program);
	checkError();
}

void glDeleteShader(GLuint shader)
{
	gDeleteShader(shader);
	checkError();
}

void glDetachShader(GLuint program, GLuint shader)
{
	gDetachShader(program, shader);
	checkError();
}

void glDisableVertexAttribArray(GLuint index)
{
	gDisableVertexAttribArray(index);
	checkError();
}

void glEnableVertexAttribArray(GLuint index)
{
	gEnableVertexAttribArray(index);
	checkError();
}

void glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name)
{
	gGetActiveAttrib(program, index, bufSize, length, size, type, name);
	checkError();
}

void glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name)
{
	gGetActiveUniform(program, index, bufSize, length, size, type, name);
	checkError();
}

void glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * obj)
{
	gGetAttachedShaders(program, maxCount, count, obj);
	checkError();
}

GLint glGetAttribLocation(GLuint program, GLchar const * name)
{
	auto result = gGetAttribLocation(program, name);
	checkError();
	return result;
}

void glGetProgramiv(GLuint program, GLenum pname, GLint * params)
{
	gGetProgramiv(program, pname, params);
	checkError();
}

void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
{
	gGetProgramInfoLog(program, bufSize, length, infoLog);
	checkError();
}

void glGetShaderiv(GLuint shader, GLenum pname, GLint * params)
{
	gGetShaderiv(shader, pname, params);
	checkError();
}

void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
{
	gGetShaderInfoLog(shader, bufSize, length, infoLog);
	checkError();
}

void glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source)
{
	gGetShaderSource(shader, bufSize, length, source);
	checkError();
}

GLint glGetUniformLocation(GLuint program, GLchar const * name)
{
	auto result = gGetUniformLocation(program, name);
	checkError();
	return result;
}

void glGetUniformfv(GLuint program, GLint location, GLfloat * params)
{
	gGetUniformfv(program, location, params);
	checkError();
}

void glGetUniformiv(GLuint program, GLint location, GLint * params)
{
	gGetUniformiv(program, location, params);
	checkError();
}

void glGetVertexAttribdv(GLuint index, GLenum pname, GLdouble * params)
{
	gGetVertexAttribdv(index, pname, params);
	checkError();
}

void glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat * params)
{
	gGetVertexAttribfv(index, pname, params);
	checkError();
}

void glGetVertexAttribiv(GLuint index, GLenum pname, GLint * params)
{
	gGetVertexAttribiv(index, pname, params);
	checkError();
}

void glGetVertexAttribPointerv(GLuint index, GLenum pname, GLvoid * * pointer)
{
	gGetVertexAttribPointerv(index, pname, pointer);
	checkError();
}

GLboolean glIsProgram(GLuint program)
{
	auto result = gIsProgram(program);
	checkError();
	return result;
}

GLboolean glIsShader(GLuint shader)
{
	auto result = gIsShader(shader);
	checkError();
	return result;
}

void glLinkProgram(GLuint program)
{
	gLinkProgram(program);
	checkError();
}

void glShaderSource(GLuint shader, GLsizei count, GLchar const * * string, GLint const * length)
{
	gShaderSource(shader, count, string, length);
	checkError();
}

void glUseProgram(GLuint program)
{
	gUseProgram(program);
	checkError();
}

void glUniform1f(GLint location, GLfloat v0)
{
	gUniform1f(location, v0);
	checkError();
}

void glUniform2f(GLint location, GLfloat v0, GLfloat v1)
{
	gUniform2f(location, v0, v1);
	checkError();
}

void glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
	gUniform3f(location, v0, v1, v2);
	checkError();
}

void glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	gUniform4f(location, v0, v1, v2, v3);
	checkError();
}

void glUniform1i(GLint location, GLint v0)
{
	gUniform1i(location, v0);
	checkError();
}

void glUniform2i(GLint location, GLint v0, GLint v1)
{
	gUniform2i(location, v0, v1);
	checkError();
}

void glUniform3i(GLint location, GLint v0, GLint v1, GLint v2)
{
	gUniform3i(location, v0, v1, v2);
	checkError();
}

void glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
	gUniform4i(location, v0, v1, v2, v3);
	checkError();
}

void glUniform1fv(GLint location, GLsizei count, GLfloat const * value)
{
	gUniform1fv(location, count, value);
	checkError();
}

void glUniform2fv(GLint location, GLsizei count, GLfloat const * value)
{
	gUniform2fv(location, count, value);
	checkError();
}

void glUniform3fv(GLint location, GLsizei count, GLfloat const * value)
{
	gUniform3fv(location, count, value);
	checkError();
}

void glUniform4fv(GLint location, GLsizei count, GLfloat const * value)
{
	gUniform4fv(location, count, value);
	checkError();
}

void glUniform1iv(GLint location, GLsizei count, GLint const * value)
{
	gUniform1iv(location, count, value);
	checkError();
}

void glUniform2iv(GLint location, GLsizei count, GLint const * value)
{
	gUniform2iv(location, count, value);
	checkError();
}

void glUniform3iv(GLint location, GLsizei count, GLint const * value)
{
	gUniform3iv(location, count, value);
	checkError();
}

void glUniform4iv(GLint location, GLsizei count, GLint const * value)
{
	gUniform4iv(location, count, value);
	checkError();
}

void glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gUniformMatrix2fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gUniformMatrix3fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gUniformMatrix4fv(location, count, transpose, value);
	checkError();
}

void glValidateProgram(GLuint program)
{
	gValidateProgram(program);
	checkError();
}

void glVertexAttrib1d(GLuint index, GLdouble x)
{
	gVertexAttrib1d(index, x);
	checkError();
}

void glVertexAttrib1dv(GLuint index, GLdouble const * v)
{
	gVertexAttrib1dv(index, v);
	checkError();
}

void glVertexAttrib1f(GLuint index, GLfloat x)
{
	gVertexAttrib1f(index, x);
	checkError();
}

void glVertexAttrib1fv(GLuint index, GLfloat const * v)
{
	gVertexAttrib1fv(index, v);
	checkError();
}

void glVertexAttrib1s(GLuint index, GLshort x)
{
	gVertexAttrib1s(index, x);
	checkError();
}

void glVertexAttrib1sv(GLuint index, GLshort const * v)
{
	gVertexAttrib1sv(index, v);
	checkError();
}

void glVertexAttrib2d(GLuint index, GLdouble x, GLdouble y)
{
	gVertexAttrib2d(index, x, y);
	checkError();
}

void glVertexAttrib2dv(GLuint index, GLdouble const * v)
{
	gVertexAttrib2dv(index, v);
	checkError();
}

void glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y)
{
	gVertexAttrib2f(index, x, y);
	checkError();
}

void glVertexAttrib2fv(GLuint index, GLfloat const * v)
{
	gVertexAttrib2fv(index, v);
	checkError();
}

void glVertexAttrib2s(GLuint index, GLshort x, GLshort y)
{
	gVertexAttrib2s(index, x, y);
	checkError();
}

void glVertexAttrib2sv(GLuint index, GLshort const * v)
{
	gVertexAttrib2sv(index, v);
	checkError();
}

void glVertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z)
{
	gVertexAttrib3d(index, x, y, z);
	checkError();
}

void glVertexAttrib3dv(GLuint index, GLdouble const * v)
{
	gVertexAttrib3dv(index, v);
	checkError();
}

void glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z)
{
	gVertexAttrib3f(index, x, y, z);
	checkError();
}

void glVertexAttrib3fv(GLuint index, GLfloat const * v)
{
	gVertexAttrib3fv(index, v);
	checkError();
}

void glVertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z)
{
	gVertexAttrib3s(index, x, y, z);
	checkError();
}

void glVertexAttrib3sv(GLuint index, GLshort const * v)
{
	gVertexAttrib3sv(index, v);
	checkError();
}

void glVertexAttrib4Nbv(GLuint index, GLbyte const * v)
{
	gVertexAttrib4Nbv(index, v);
	checkError();
}

void glVertexAttrib4Niv(GLuint index, GLint const * v)
{
	gVertexAttrib4Niv(index, v);
	checkError();
}

void glVertexAttrib4Nsv(GLuint index, GLshort const * v)
{
	gVertexAttrib4Nsv(index, v);
	checkError();
}

void glVertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w)
{
	gVertexAttrib4Nub(index, x, y, z, w);
	checkError();
}

void glVertexAttrib4Nubv(GLuint index, GLubyte const * v)
{
	gVertexAttrib4Nubv(index, v);
	checkError();
}

void glVertexAttrib4Nuiv(GLuint index, GLuint const * v)
{
	gVertexAttrib4Nuiv(index, v);
	checkError();
}

void glVertexAttrib4Nusv(GLuint index, GLushort const * v)
{
	gVertexAttrib4Nusv(index, v);
	checkError();
}

void glVertexAttrib4bv(GLuint index, GLbyte const * v)
{
	gVertexAttrib4bv(index, v);
	checkError();
}

void glVertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	gVertexAttrib4d(index, x, y, z, w);
	checkError();
}

void glVertexAttrib4dv(GLuint index, GLdouble const * v)
{
	gVertexAttrib4dv(index, v);
	checkError();
}

void glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	gVertexAttrib4f(index, x, y, z, w);
	checkError();
}

void glVertexAttrib4fv(GLuint index, GLfloat const * v)
{
	gVertexAttrib4fv(index, v);
	checkError();
}

void glVertexAttrib4iv(GLuint index, GLint const * v)
{
	gVertexAttrib4iv(index, v);
	checkError();
}

void glVertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w)
{
	gVertexAttrib4s(index, x, y, z, w);
	checkError();
}

void glVertexAttrib4sv(GLuint index, GLshort const * v)
{
	gVertexAttrib4sv(index, v);
	checkError();
}

void glVertexAttrib4ubv(GLuint index, GLubyte const * v)
{
	gVertexAttrib4ubv(index, v);
	checkError();
}

void glVertexAttrib4uiv(GLuint index, GLuint const * v)
{
	gVertexAttrib4uiv(index, v);
	checkError();
}

void glVertexAttrib4usv(GLuint index, GLushort const * v)
{
	gVertexAttrib4usv(index, v);
	checkError();
}

void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid const * pointer)
{
	gVertexAttribPointer(index, size, type, normalized, stride, pointer);
	checkError();
}

void glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gUniformMatrix2x3fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gUniformMatrix3x2fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gUniformMatrix2x4fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gUniformMatrix4x2fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gUniformMatrix3x4fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gUniformMatrix4x3fv(location, count, transpose, value);
	checkError();
}

void glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a)
{
	gColorMaski(index, r, g, b, a);
	checkError();
}

void glGetBooleani_v(GLenum target, GLuint index, GLboolean * data)
{
	gGetBooleani_v(target, index, data);
	checkError();
}

void glGetIntegeri_v(GLenum target, GLuint index, GLint * data)
{
	gGetIntegeri_v(target, index, data);
	checkError();
}

void glEnablei(GLenum target, GLuint index)
{
	gEnablei(target, index);
	checkError();
}

void glDisablei(GLenum target, GLuint index)
{
	gDisablei(target, index);
	checkError();
}

GLboolean glIsEnabledi(GLenum target, GLuint index)
{
	auto result = gIsEnabledi(target, index);
	checkError();
	return result;
}

void glBeginTransformFeedback(GLenum primitiveMode)
{
	gBeginTransformFeedback(primitiveMode);
	checkError();
}

void glEndTransformFeedback(void)
{
	gEndTransformFeedback();
	checkError();
}

void glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
	gBindBufferRange(target, index, buffer, offset, size);
	checkError();
}

void glBindBufferBase(GLenum target, GLuint index, GLuint buffer)
{
	gBindBufferBase(target, index, buffer);
	checkError();
}

void glTransformFeedbackVaryings(GLuint program, GLsizei count, GLchar const * * varyings, GLenum bufferMode)
{
	gTransformFeedbackVaryings(program, count, varyings, bufferMode);
	checkError();
}

void glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name)
{
	gGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
	checkError();
}

void glClampColor(GLenum target, GLenum clamp)
{
	gClampColor(target, clamp);
	checkError();
}

void glBeginConditionalRender(GLuint id, GLenum mode)
{
	gBeginConditionalRender(id, mode);
	checkError();
}

void glEndConditionalRender(void)
{
	gEndConditionalRender();
	checkError();
}

void glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, GLvoid const * pointer)
{
	gVertexAttribIPointer(index, size, type, stride, pointer);
	checkError();
}

void glGetVertexAttribIiv(GLuint index, GLenum pname, GLint * params)
{
	gGetVertexAttribIiv(index, pname, params);
	checkError();
}

void glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint * params)
{
	gGetVertexAttribIuiv(index, pname, params);
	checkError();
}

void glVertexAttribI1i(GLuint index, GLint x)
{
	gVertexAttribI1i(index, x);
	checkError();
}

void glVertexAttribI2i(GLuint index, GLint x, GLint y)
{
	gVertexAttribI2i(index, x, y);
	checkError();
}

void glVertexAttribI3i(GLuint index, GLint x, GLint y, GLint z)
{
	gVertexAttribI3i(index, x, y, z);
	checkError();
}

void glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w)
{
	gVertexAttribI4i(index, x, y, z, w);
	checkError();
}

void glVertexAttribI1ui(GLuint index, GLuint x)
{
	gVertexAttribI1ui(index, x);
	checkError();
}

void glVertexAttribI2ui(GLuint index, GLuint x, GLuint y)
{
	gVertexAttribI2ui(index, x, y);
	checkError();
}

void glVertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z)
{
	gVertexAttribI3ui(index, x, y, z);
	checkError();
}

void glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)
{
	gVertexAttribI4ui(index, x, y, z, w);
	checkError();
}

void glVertexAttribI1iv(GLuint index, GLint const * v)
{
	gVertexAttribI1iv(index, v);
	checkError();
}

void glVertexAttribI2iv(GLuint index, GLint const * v)
{
	gVertexAttribI2iv(index, v);
	checkError();
}

void glVertexAttribI3iv(GLuint index, GLint const * v)
{
	gVertexAttribI3iv(index, v);
	checkError();
}

void glVertexAttribI4iv(GLuint index, GLint const * v)
{
	gVertexAttribI4iv(index, v);
	checkError();
}

void glVertexAttribI1uiv(GLuint index, GLuint const * v)
{
	gVertexAttribI1uiv(index, v);
	checkError();
}

void glVertexAttribI2uiv(GLuint index, GLuint const * v)
{
	gVertexAttribI2uiv(index, v);
	checkError();
}

void glVertexAttribI3uiv(GLuint index, GLuint const * v)
{
	gVertexAttribI3uiv(index, v);
	checkError();
}

void glVertexAttribI4uiv(GLuint index, GLuint const * v)
{
	gVertexAttribI4uiv(index, v);
	checkError();
}

void glVertexAttribI4bv(GLuint index, GLbyte const * v)
{
	gVertexAttribI4bv(index, v);
	checkError();
}

void glVertexAttribI4sv(GLuint index, GLshort const * v)
{
	gVertexAttribI4sv(index, v);
	checkError();
}

void glVertexAttribI4ubv(GLuint index, GLubyte const * v)
{
	gVertexAttribI4ubv(index, v);
	checkError();
}

void glVertexAttribI4usv(GLuint index, GLushort const * v)
{
	gVertexAttribI4usv(index, v);
	checkError();
}

void glGetUniformuiv(GLuint program, GLint location, GLuint * params)
{
	gGetUniformuiv(program, location, params);
	checkError();
}

void glBindFragDataLocation(GLuint program, GLuint color, GLchar const * name)
{
	gBindFragDataLocation(program, color, name);
	checkError();
}

GLint glGetFragDataLocation(GLuint program, GLchar const * name)
{
	auto result = gGetFragDataLocation(program, name);
	checkError();
	return result;
}

void glUniform1ui(GLint location, GLuint v0)
{
	gUniform1ui(location, v0);
	checkError();
}

void glUniform2ui(GLint location, GLuint v0, GLuint v1)
{
	gUniform2ui(location, v0, v1);
	checkError();
}

void glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2)
{
	gUniform3ui(location, v0, v1, v2);
	checkError();
}

void glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	gUniform4ui(location, v0, v1, v2, v3);
	checkError();
}

void glUniform1uiv(GLint location, GLsizei count, GLuint const * value)
{
	gUniform1uiv(location, count, value);
	checkError();
}

void glUniform2uiv(GLint location, GLsizei count, GLuint const * value)
{
	gUniform2uiv(location, count, value);
	checkError();
}

void glUniform3uiv(GLint location, GLsizei count, GLuint const * value)
{
	gUniform3uiv(location, count, value);
	checkError();
}

void glUniform4uiv(GLint location, GLsizei count, GLuint const * value)
{
	gUniform4uiv(location, count, value);
	checkError();
}

void glTexParameterIiv(GLenum target, GLenum pname, GLint const * params)
{
	gTexParameterIiv(target, pname, params);
	checkError();
}

void glTexParameterIuiv(GLenum target, GLenum pname, GLuint const * params)
{
	gTexParameterIuiv(target, pname, params);
	checkError();
}

void glGetTexParameterIiv(GLenum target, GLenum pname, GLint * params)
{
	gGetTexParameterIiv(target, pname, params);
	checkError();
}

void glGetTexParameterIuiv(GLenum target, GLenum pname, GLuint * params)
{
	gGetTexParameterIuiv(target, pname, params);
	checkError();
}

void glClearBufferiv(GLenum buffer, GLint drawbuffer, GLint const * value)
{
	gClearBufferiv(buffer, drawbuffer, value);
	checkError();
}

void glClearBufferuiv(GLenum buffer, GLint drawbuffer, GLuint const * value)
{
	gClearBufferuiv(buffer, drawbuffer, value);
	checkError();
}

void glClearBufferfv(GLenum buffer, GLint drawbuffer, GLfloat const * value)
{
	gClearBufferfv(buffer, drawbuffer, value);
	checkError();
}

void glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)
{
	gClearBufferfi(buffer, drawbuffer, depth, stencil);
	checkError();
}

GLubyte const * glGetStringi (GLenum name, GLuint index)
{
	auto result = gGetStringi (name, index);
	checkError();
	return result;
}

void glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei primcount)
{
	gDrawArraysInstanced(mode, first, count, primcount);
	checkError();
}

void glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, GLvoid const * indices, GLsizei primcount)
{
	gDrawElementsInstanced(mode, count, type, indices, primcount);
	checkError();
}

void glTexBuffer(GLenum target, GLenum internalformat, GLuint buffer)
{
	gTexBuffer(target, internalformat, buffer);
	checkError();
}

void glPrimitiveRestartIndex(GLuint index)
{
	gPrimitiveRestartIndex(index);
	checkError();
}

void glGetInteger64i_v(GLenum target, GLuint index, GLint64 *data)
{
	gGetInteger64i_v(target, index, data);
	checkError();
}

void glGetBufferParameteri64v(GLenum target, GLenum pname, GLint64 *params)
{
	gGetBufferParameteri64v(target, pname, params);
	checkError();
}

void glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level)
{
	gFramebufferTexture(target, attachment, texture, level);
	checkError();
}

void glVertexAttribDivisor(GLuint index, GLuint divisor)
{
	gVertexAttribDivisor(index, divisor);
	checkError();
}

void glMinSampleShading(GLclampf value)
{
	gMinSampleShading(value);
	checkError();
}

void glBlendEquationi(GLuint buf, GLenum mode)
{
	gBlendEquationi(buf, mode);
	checkError();
}

void glBlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha)
{
	gBlendEquationSeparatei(buf, modeRGB, modeAlpha);
	checkError();
}

void glBlendFunci(GLuint buf, GLenum src, GLenum dst)
{
	gBlendFunci(buf, src, dst);
	checkError();
}

void glBlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
	gBlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
	checkError();
}

GLboolean glIsRenderbuffer(GLuint renderbuffer)
{
	auto result = gIsRenderbuffer(renderbuffer);
	checkError();
	return result;
}

void glBindRenderbuffer(GLenum target, GLuint renderbuffer)
{
	gBindRenderbuffer(target, renderbuffer);
	checkError();
}

void glDeleteRenderbuffers(GLsizei n, GLuint const * renderbuffers)
{
	gDeleteRenderbuffers(n, renderbuffers);
	checkError();
}

void glGenRenderbuffers(GLsizei n, GLuint * renderbuffers)
{
	gGenRenderbuffers(n, renderbuffers);
	checkError();
}

void glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
	gRenderbufferStorage(target, internalformat, width, height);
	checkError();
}

void glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params)
{
	gGetRenderbufferParameteriv(target, pname, params);
	checkError();
}

GLboolean glIsFramebuffer(GLuint framebuffer)
{
	auto result = gIsFramebuffer(framebuffer);
	checkError();
	return result;
}

void glBindFramebuffer(GLenum target, GLuint framebuffer)
{
	gBindFramebuffer(target, framebuffer);
	checkError();
}

void glDeleteFramebuffers(GLsizei n, GLuint const * framebuffers)
{
	gDeleteFramebuffers(n, framebuffers);
	checkError();
}

void glGenFramebuffers(GLsizei n, GLuint * framebuffers)
{
	gGenFramebuffers(n, framebuffers);
	checkError();
}

GLenum glCheckFramebufferStatus(GLenum target)
{
	auto result = gCheckFramebufferStatus(target);
	checkError();
	return result;
}

void glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
	gFramebufferTexture1D(target, attachment, textarget, texture, level);
	checkError();
}

void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
	gFramebufferTexture2D(target, attachment, textarget, texture, level);
	checkError();
}

void glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset)
{
	gFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);
	checkError();
}

void glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
	gFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
	checkError();
}

void glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params)
{
	gGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
	checkError();
}

void glGenerateMipmap(GLenum target)
{
	gGenerateMipmap(target);
	checkError();
}

void glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
{
	gBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
	checkError();
}

void glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
	gRenderbufferStorageMultisample(target, samples, internalformat, width, height);
	checkError();
}

void glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer)
{
	gFramebufferTextureLayer(target, attachment, texture, level, layer);
	checkError();
}

GLvoid * glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)
{
	auto result = gMapBufferRange(target, offset, length, access);
	checkError();
	return result;
}

void glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length)
{
	gFlushMappedBufferRange(target, offset, length);
	checkError();
}

void glBindVertexArray(GLuint array)
{
	gBindVertexArray(array);
	checkError();
}

void glDeleteVertexArrays(GLsizei n, GLuint const * arrays)
{
	gDeleteVertexArrays(n, arrays);
	checkError();
}

void glGenVertexArrays(GLsizei n, GLuint * arrays)
{
	gGenVertexArrays(n, arrays);
	checkError();
}

GLboolean glIsVertexArray(GLuint array)
{
	auto result = gIsVertexArray(array);
	checkError();
	return result;
}

void glGetUniformIndices(GLuint program, GLsizei uniformCount, GLchar const * * uniformNames, GLuint * uniformIndices)
{
	gGetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
	checkError();
}

void glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, GLuint const * uniformIndices, GLenum pname, GLint * params)
{
	gGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);
	checkError();
}

void glGetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName)
{
	gGetActiveUniformName(program, uniformIndex, bufSize, length, uniformName);
	checkError();
}

GLuint glGetUniformBlockIndex(GLuint program, GLchar const * uniformBlockName)
{
	auto result = gGetUniformBlockIndex(program, uniformBlockName);
	checkError();
	return result;
}

void glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params)
{
	gGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
	checkError();
}

void glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName)
{
	gGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
	checkError();
}

void glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)
{
	gUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
	checkError();
}

void glCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
{
	gCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
	checkError();
}

void glDrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, GLvoid const * indices, GLint basevertex)
{
	gDrawElementsBaseVertex(mode, count, type, indices, basevertex);
	checkError();
}

void glDrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, GLvoid const * indices, GLint basevertex)
{
	gDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
	checkError();
}

void glDrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, GLvoid const * indices, GLsizei primcount, GLint basevertex)
{
	gDrawElementsInstancedBaseVertex(mode, count, type, indices, primcount, basevertex);
	checkError();
}

void glMultiDrawElementsBaseVertex(GLenum mode, GLsizei const * count, GLenum type, GLvoid const * * indices, GLsizei primcount, GLint const * basevertex)
{
	gMultiDrawElementsBaseVertex(mode, count, type, indices, primcount, basevertex);
	checkError();
}

void glProvokingVertex(GLenum mode)
{
	gProvokingVertex(mode);
	checkError();
}

GLsync glFenceSync(GLenum condition, GLbitfield flags)
{
	auto result = gFenceSync(condition, flags);
	checkError();
	return result;
}

GLboolean glIsSync(GLsync sync)
{
	auto result = gIsSync(sync);
	checkError();
	return result;
}

void glDeleteSync(GLsync sync)
{
	gDeleteSync(sync);
	checkError();
}

GLenum glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
	auto result = gClientWaitSync(sync, flags, timeout);
	checkError();
	return result;
}

void glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
	gWaitSync(sync, flags, timeout);
	checkError();
}

void glGetInteger64v(GLenum pname, GLint64 *params)
{
	gGetInteger64v(pname, params);
	checkError();
}

void glGetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei * length, GLint * values)
{
	gGetSynciv(sync, pname, bufSize, length, values);
	checkError();
}

void glTexImage2DMultisample(GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
	gTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
	checkError();
}

void glTexImage3DMultisample(GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
	gTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
	checkError();
}

void glGetMultisamplefv(GLenum pname, GLuint index, GLfloat * val)
{
	gGetMultisamplefv(pname, index, val);
	checkError();
}

void glSampleMaski(GLuint index, GLbitfield mask)
{
	gSampleMaski(index, mask);
	checkError();
}

void glBlendEquationiARB(GLuint buf, GLenum mode)
{
	gBlendEquationiARB(buf, mode);
	checkError();
}

void glBlendEquationSeparateiARB(GLuint buf, GLenum modeRGB, GLenum modeAlpha)
{
	gBlendEquationSeparateiARB(buf, modeRGB, modeAlpha);
	checkError();
}

void glBlendFunciARB(GLuint buf, GLenum src, GLenum dst)
{
	gBlendFunciARB(buf, src, dst);
	checkError();
}

void glBlendFuncSeparateiARB(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
	gBlendFuncSeparateiARB(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
	checkError();
}

void glMinSampleShadingARB(GLclampf value)
{
	gMinSampleShadingARB(value);
	checkError();
}

void glNamedStringARB(GLenum type, GLint namelen, GLchar const * name, GLint stringlen, GLchar const * string)
{
	gNamedStringARB(type, namelen, name, stringlen, string);
	checkError();
}

void glDeleteNamedStringARB(GLint namelen, GLchar const * name)
{
	gDeleteNamedStringARB(namelen, name);
	checkError();
}

void glCompileShaderIncludeARB(GLuint shader, GLsizei count, GLchar const * * path, GLint const * length)
{
	gCompileShaderIncludeARB(shader, count, path, length);
	checkError();
}

GLboolean glIsNamedStringARB(GLint namelen, GLchar const * name)
{
	auto result = gIsNamedStringARB(namelen, name);
	checkError();
	return result;
}

void glGetNamedStringARB(GLint namelen, GLchar const * name, GLsizei bufSize, GLint * stringlen, GLchar * string)
{
	gGetNamedStringARB(namelen, name, bufSize, stringlen, string);
	checkError();
}

void glGetNamedStringivARB(GLint namelen, GLchar const * name, GLenum pname, GLint * params)
{
	gGetNamedStringivARB(namelen, name, pname, params);
	checkError();
}

void glBindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, GLchar const * name)
{
	gBindFragDataLocationIndexed(program, colorNumber, index, name);
	checkError();
}

GLint glGetFragDataIndex(GLuint program, GLchar const * name)
{
	auto result = gGetFragDataIndex(program, name);
	checkError();
	return result;
}

void glGenSamplers(GLsizei count, GLuint * samplers)
{
	gGenSamplers(count, samplers);
	checkError();
}

void glDeleteSamplers(GLsizei count, GLuint const * samplers)
{
	gDeleteSamplers(count, samplers);
	checkError();
}

GLboolean glIsSampler(GLuint sampler)
{
	auto result = gIsSampler(sampler);
	checkError();
	return result;
}

void glBindSampler(GLuint unit, GLuint sampler)
{
	gBindSampler(unit, sampler);
	checkError();
}

void glSamplerParameteri(GLuint sampler, GLenum pname, GLint param)
{
	gSamplerParameteri(sampler, pname, param);
	checkError();
}

void glSamplerParameteriv(GLuint sampler, GLenum pname, GLint const * param)
{
	gSamplerParameteriv(sampler, pname, param);
	checkError();
}

void glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param)
{
	gSamplerParameterf(sampler, pname, param);
	checkError();
}

void glSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat const * param)
{
	gSamplerParameterfv(sampler, pname, param);
	checkError();
}

void glSamplerParameterIiv(GLuint sampler, GLenum pname, GLint const * param)
{
	gSamplerParameterIiv(sampler, pname, param);
	checkError();
}

void glSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint const * param)
{
	gSamplerParameterIuiv(sampler, pname, param);
	checkError();
}

void glGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint * params)
{
	gGetSamplerParameteriv(sampler, pname, params);
	checkError();
}

void glGetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint * params)
{
	gGetSamplerParameterIiv(sampler, pname, params);
	checkError();
}

void glGetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat * params)
{
	gGetSamplerParameterfv(sampler, pname, params);
	checkError();
}

void glGetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint * params)
{
	gGetSamplerParameterIuiv(sampler, pname, params);
	checkError();
}

void glQueryCounter(GLuint id, GLenum target)
{
	gQueryCounter(id, target);
	checkError();
}

void glGetQueryObjecti64v(GLuint id, GLenum pname, GLint64 *params)
{
	gGetQueryObjecti64v(id, pname, params);
	checkError();
}

void glGetQueryObjectui64v(GLuint id, GLenum pname, GLuint64 *params)
{
	gGetQueryObjectui64v(id, pname, params);
	checkError();
}

void glVertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	gVertexAttribP1ui(index, type, normalized, value);
	checkError();
}

void glVertexAttribP1uiv(GLuint index, GLenum type, GLboolean normalized, GLuint const * value)
{
	gVertexAttribP1uiv(index, type, normalized, value);
	checkError();
}

void glVertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	gVertexAttribP2ui(index, type, normalized, value);
	checkError();
}

void glVertexAttribP2uiv(GLuint index, GLenum type, GLboolean normalized, GLuint const * value)
{
	gVertexAttribP2uiv(index, type, normalized, value);
	checkError();
}

void glVertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	gVertexAttribP3ui(index, type, normalized, value);
	checkError();
}

void glVertexAttribP3uiv(GLuint index, GLenum type, GLboolean normalized, GLuint const * value)
{
	gVertexAttribP3uiv(index, type, normalized, value);
	checkError();
}

void glVertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	gVertexAttribP4ui(index, type, normalized, value);
	checkError();
}

void glVertexAttribP4uiv(GLuint index, GLenum type, GLboolean normalized, GLuint const * value)
{
	gVertexAttribP4uiv(index, type, normalized, value);
	checkError();
}

void glDrawArraysIndirect(GLenum mode, GLvoid const * indirect)
{
	gDrawArraysIndirect(mode, indirect);
	checkError();
}

void glDrawElementsIndirect(GLenum mode, GLenum type, GLvoid const * indirect)
{
	gDrawElementsIndirect(mode, type, indirect);
	checkError();
}

void glUniform1d(GLint location, GLdouble x)
{
	gUniform1d(location, x);
	checkError();
}

void glUniform2d(GLint location, GLdouble x, GLdouble y)
{
	gUniform2d(location, x, y);
	checkError();
}

void glUniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z)
{
	gUniform3d(location, x, y, z);
	checkError();
}

void glUniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	gUniform4d(location, x, y, z, w);
	checkError();
}

void glUniform1dv(GLint location, GLsizei count, GLdouble const * value)
{
	gUniform1dv(location, count, value);
	checkError();
}

void glUniform2dv(GLint location, GLsizei count, GLdouble const * value)
{
	gUniform2dv(location, count, value);
	checkError();
}

void glUniform3dv(GLint location, GLsizei count, GLdouble const * value)
{
	gUniform3dv(location, count, value);
	checkError();
}

void glUniform4dv(GLint location, GLsizei count, GLdouble const * value)
{
	gUniform4dv(location, count, value);
	checkError();
}

void glUniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gUniformMatrix2dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gUniformMatrix3dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gUniformMatrix4dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gUniformMatrix2x3dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gUniformMatrix2x4dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gUniformMatrix3x2dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gUniformMatrix3x4dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gUniformMatrix4x2dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gUniformMatrix4x3dv(location, count, transpose, value);
	checkError();
}

void glGetUniformdv(GLuint program, GLint location, GLdouble * params)
{
	gGetUniformdv(program, location, params);
	checkError();
}

GLint glGetSubroutineUniformLocation(GLuint program, GLenum shadertype, GLchar const * name)
{
	auto result = gGetSubroutineUniformLocation(program, shadertype, name);
	checkError();
	return result;
}

GLuint glGetSubroutineIndex(GLuint program, GLenum shadertype, GLchar const * name)
{
	auto result = gGetSubroutineIndex(program, shadertype, name);
	checkError();
	return result;
}

void glGetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint * values)
{
	gGetActiveSubroutineUniformiv(program, shadertype, index, pname, values);
	checkError();
}

void glGetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name)
{
	gGetActiveSubroutineUniformName(program, shadertype, index, bufsize, length, name);
	checkError();
}

void glGetActiveSubroutineName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name)
{
	gGetActiveSubroutineName(program, shadertype, index, bufsize, length, name);
	checkError();
}

void glUniformSubroutinesuiv(GLenum shadertype, GLsizei count, GLuint const * indices)
{
	gUniformSubroutinesuiv(shadertype, count, indices);
	checkError();
}

void glGetUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint * params)
{
	gGetUniformSubroutineuiv(shadertype, location, params);
	checkError();
}

void glGetProgramStageiv(GLuint program, GLenum shadertype, GLenum pname, GLint * values)
{
	gGetProgramStageiv(program, shadertype, pname, values);
	checkError();
}

void glPatchParameteri(GLenum pname, GLint value)
{
	gPatchParameteri(pname, value);
	checkError();
}

void glPatchParameterfv(GLenum pname, GLfloat const * values)
{
	gPatchParameterfv(pname, values);
	checkError();
}

void glBindTransformFeedback(GLenum target, GLuint id)
{
	gBindTransformFeedback(target, id);
	checkError();
}

void glDeleteTransformFeedbacks(GLsizei n, GLuint const * ids)
{
	gDeleteTransformFeedbacks(n, ids);
	checkError();
}

void glGenTransformFeedbacks(GLsizei n, GLuint * ids)
{
	gGenTransformFeedbacks(n, ids);
	checkError();
}

GLboolean glIsTransformFeedback(GLuint id)
{
	auto result = gIsTransformFeedback(id);
	checkError();
	return result;
}

void glPauseTransformFeedback(void)
{
	gPauseTransformFeedback();
	checkError();
}

void glResumeTransformFeedback(void)
{
	gResumeTransformFeedback();
	checkError();
}

void glDrawTransformFeedback(GLenum mode, GLuint id)
{
	gDrawTransformFeedback(mode, id);
	checkError();
}

void glDrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream)
{
	gDrawTransformFeedbackStream(mode, id, stream);
	checkError();
}

void glBeginQueryIndexed(GLenum target, GLuint index, GLuint id)
{
	gBeginQueryIndexed(target, index, id);
	checkError();
}

void glEndQueryIndexed(GLenum target, GLuint index)
{
	gEndQueryIndexed(target, index);
	checkError();
}

void glGetQueryIndexediv(GLenum target, GLuint index, GLenum pname, GLint * params)
{
	gGetQueryIndexediv(target, index, pname, params);
	checkError();
}

void glReleaseShaderCompiler(void)
{
	gReleaseShaderCompiler();
	checkError();
}

void glShaderBinary(GLsizei count, GLuint const * shaders, GLenum binaryformat, GLvoid const * binary, GLsizei length)
{
	gShaderBinary(count, shaders, binaryformat, binary, length);
	checkError();
}

void glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision)
{
	gGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
	checkError();
}

void glDepthRangef(GLclampf n, GLclampf f)
{
	gDepthRangef(n, f);
	checkError();
}

void glClearDepthf(GLclampf d)
{
	gClearDepthf(d);
	checkError();
}

void glGetProgramBinary(GLuint program, GLsizei bufSize, GLsizei * length, GLenum * binaryFormat, GLvoid * binary)
{
	gGetProgramBinary(program, bufSize, length, binaryFormat, binary);
	checkError();
}

void glProgramBinary(GLuint program, GLenum binaryFormat, GLvoid const * binary, GLsizei length)
{
	gProgramBinary(program, binaryFormat, binary, length);
	checkError();
}

void glProgramParameteri(GLuint program, GLenum pname, GLint value)
{
	gProgramParameteri(program, pname, value);
	checkError();
}

void glUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program)
{
	gUseProgramStages(pipeline, stages, program);
	checkError();
}

void glActiveShaderProgram(GLuint pipeline, GLuint program)
{
	gActiveShaderProgram(pipeline, program);
	checkError();
}

GLuint glCreateShaderProgramv(GLenum type, GLsizei count, GLchar const * * strings)
{
	auto result = gCreateShaderProgramv(type, count, strings);
	checkError();
	return result;
}

void glBindProgramPipeline(GLuint pipeline)
{
	gBindProgramPipeline(pipeline);
	checkError();
}

void glDeleteProgramPipelines(GLsizei n, GLuint const * pipelines)
{
	gDeleteProgramPipelines(n, pipelines);
	checkError();
}

void glGenProgramPipelines(GLsizei n, GLuint * pipelines)
{
	gGenProgramPipelines(n, pipelines);
	checkError();
}

GLboolean glIsProgramPipeline(GLuint pipeline)
{
	auto result = gIsProgramPipeline(pipeline);
	checkError();
	return result;
}

void glGetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint * params)
{
	gGetProgramPipelineiv(pipeline, pname, params);
	checkError();
}

void glProgramUniform1i(GLuint program, GLint location, GLint v0)
{
	gProgramUniform1i(program, location, v0);
	checkError();
}

void glProgramUniform1iv(GLuint program, GLint location, GLsizei count, GLint const * value)
{
	gProgramUniform1iv(program, location, count, value);
	checkError();
}

void glProgramUniform1f(GLuint program, GLint location, GLfloat v0)
{
	gProgramUniform1f(program, location, v0);
	checkError();
}

void glProgramUniform1fv(GLuint program, GLint location, GLsizei count, GLfloat const * value)
{
	gProgramUniform1fv(program, location, count, value);
	checkError();
}

void glProgramUniform1d(GLuint program, GLint location, GLdouble v0)
{
	gProgramUniform1d(program, location, v0);
	checkError();
}

void glProgramUniform1dv(GLuint program, GLint location, GLsizei count, GLdouble const * value)
{
	gProgramUniform1dv(program, location, count, value);
	checkError();
}

void glProgramUniform1ui(GLuint program, GLint location, GLuint v0)
{
	gProgramUniform1ui(program, location, v0);
	checkError();
}

void glProgramUniform1uiv(GLuint program, GLint location, GLsizei count, GLuint const * value)
{
	gProgramUniform1uiv(program, location, count, value);
	checkError();
}

void glProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1)
{
	gProgramUniform2i(program, location, v0, v1);
	checkError();
}

void glProgramUniform2iv(GLuint program, GLint location, GLsizei count, GLint const * value)
{
	gProgramUniform2iv(program, location, count, value);
	checkError();
}

void glProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1)
{
	gProgramUniform2f(program, location, v0, v1);
	checkError();
}

void glProgramUniform2fv(GLuint program, GLint location, GLsizei count, GLfloat const * value)
{
	gProgramUniform2fv(program, location, count, value);
	checkError();
}

void glProgramUniform2d(GLuint program, GLint location, GLdouble v0, GLdouble v1)
{
	gProgramUniform2d(program, location, v0, v1);
	checkError();
}

void glProgramUniform2dv(GLuint program, GLint location, GLsizei count, GLdouble const * value)
{
	gProgramUniform2dv(program, location, count, value);
	checkError();
}

void glProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1)
{
	gProgramUniform2ui(program, location, v0, v1);
	checkError();
}

void glProgramUniform2uiv(GLuint program, GLint location, GLsizei count, GLuint const * value)
{
	gProgramUniform2uiv(program, location, count, value);
	checkError();
}

void glProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2)
{
	gProgramUniform3i(program, location, v0, v1, v2);
	checkError();
}

void glProgramUniform3iv(GLuint program, GLint location, GLsizei count, GLint const * value)
{
	gProgramUniform3iv(program, location, count, value);
	checkError();
}

void glProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
	gProgramUniform3f(program, location, v0, v1, v2);
	checkError();
}

void glProgramUniform3fv(GLuint program, GLint location, GLsizei count, GLfloat const * value)
{
	gProgramUniform3fv(program, location, count, value);
	checkError();
}

void glProgramUniform3d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2)
{
	gProgramUniform3d(program, location, v0, v1, v2);
	checkError();
}

void glProgramUniform3dv(GLuint program, GLint location, GLsizei count, GLdouble const * value)
{
	gProgramUniform3dv(program, location, count, value);
	checkError();
}

void glProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2)
{
	gProgramUniform3ui(program, location, v0, v1, v2);
	checkError();
}

void glProgramUniform3uiv(GLuint program, GLint location, GLsizei count, GLuint const * value)
{
	gProgramUniform3uiv(program, location, count, value);
	checkError();
}

void glProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
	gProgramUniform4i(program, location, v0, v1, v2, v3);
	checkError();
}

void glProgramUniform4iv(GLuint program, GLint location, GLsizei count, GLint const * value)
{
	gProgramUniform4iv(program, location, count, value);
	checkError();
}

void glProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	gProgramUniform4f(program, location, v0, v1, v2, v3);
	checkError();
}

void glProgramUniform4fv(GLuint program, GLint location, GLsizei count, GLfloat const * value)
{
	gProgramUniform4fv(program, location, count, value);
	checkError();
}

void glProgramUniform4d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3)
{
	gProgramUniform4d(program, location, v0, v1, v2, v3);
	checkError();
}

void glProgramUniform4dv(GLuint program, GLint location, GLsizei count, GLdouble const * value)
{
	gProgramUniform4dv(program, location, count, value);
	checkError();
}

void glProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	gProgramUniform4ui(program, location, v0, v1, v2, v3);
	checkError();
}

void glProgramUniform4uiv(GLuint program, GLint location, GLsizei count, GLuint const * value)
{
	gProgramUniform4uiv(program, location, count, value);
	checkError();
}

void glProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gProgramUniformMatrix2fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gProgramUniformMatrix3fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gProgramUniformMatrix4fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gProgramUniformMatrix2dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gProgramUniformMatrix3dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gProgramUniformMatrix4dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gProgramUniformMatrix2x3fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gProgramUniformMatrix3x2fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gProgramUniformMatrix2x4fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gProgramUniformMatrix4x2fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gProgramUniformMatrix3x4fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gProgramUniformMatrix4x3fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix2x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gProgramUniformMatrix2x3dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix3x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gProgramUniformMatrix3x2dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix2x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gProgramUniformMatrix2x4dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix4x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gProgramUniformMatrix4x2dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix3x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gProgramUniformMatrix3x4dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix4x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gProgramUniformMatrix4x3dv(program, location, count, transpose, value);
	checkError();
}

void glValidateProgramPipeline(GLuint pipeline)
{
	gValidateProgramPipeline(pipeline);
	checkError();
}

void glGetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
{
	gGetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog);
	checkError();
}

void glVertexAttribL1d(GLuint index, GLdouble x)
{
	gVertexAttribL1d(index, x);
	checkError();
}

void glVertexAttribL2d(GLuint index, GLdouble x, GLdouble y)
{
	gVertexAttribL2d(index, x, y);
	checkError();
}

void glVertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z)
{
	gVertexAttribL3d(index, x, y, z);
	checkError();
}

void glVertexAttribL4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	gVertexAttribL4d(index, x, y, z, w);
	checkError();
}

void glVertexAttribL1dv(GLuint index, GLdouble const * v)
{
	gVertexAttribL1dv(index, v);
	checkError();
}

void glVertexAttribL2dv(GLuint index, GLdouble const * v)
{
	gVertexAttribL2dv(index, v);
	checkError();
}

void glVertexAttribL3dv(GLuint index, GLdouble const * v)
{
	gVertexAttribL3dv(index, v);
	checkError();
}

void glVertexAttribL4dv(GLuint index, GLdouble const * v)
{
	gVertexAttribL4dv(index, v);
	checkError();
}

void glVertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, GLvoid const * pointer)
{
	gVertexAttribLPointer(index, size, type, stride, pointer);
	checkError();
}

void glGetVertexAttribLdv(GLuint index, GLenum pname, GLdouble * params)
{
	gGetVertexAttribLdv(index, pname, params);
	checkError();
}

void glViewportArrayv(GLuint first, GLsizei count, GLfloat const * v)
{
	gViewportArrayv(first, count, v);
	checkError();
}

void glViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h)
{
	gViewportIndexedf(index, x, y, w, h);
	checkError();
}

void glViewportIndexedfv(GLuint index, GLfloat const * v)
{
	gViewportIndexedfv(index, v);
	checkError();
}

void glScissorArrayv(GLuint first, GLsizei count, GLint const * v)
{
	gScissorArrayv(first, count, v);
	checkError();
}

void glScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height)
{
	gScissorIndexed(index, left, bottom, width, height);
	checkError();
}

void glScissorIndexedv(GLuint index, GLint const * v)
{
	gScissorIndexedv(index, v);
	checkError();
}

void glDepthRangeArrayv(GLuint first, GLsizei count, GLclampd const * v)
{
	gDepthRangeArrayv(first, count, v);
	checkError();
}

void glDepthRangeIndexed(GLuint index, GLclampd n, GLclampd f)
{
	gDepthRangeIndexed(index, n, f);
	checkError();
}

void glGetFloati_v(GLenum target, GLuint index, GLfloat * data)
{
	gGetFloati_v(target, index, data);
	checkError();
}

void glGetDoublei_v(GLenum target, GLuint index, GLdouble * data)
{
	gGetDoublei_v(target, index, data);
	checkError();
}

GLsync glCreateSyncFromCLeventARB(struct _cl_context * context, struct _cl_event * event, GLbitfield flags)
{
	auto result = gCreateSyncFromCLeventARB(context, event, flags);
	checkError();
	return result;
}

void glDebugMessageControlARB(GLenum source, GLenum type, GLenum severity, GLsizei count, GLuint const * ids, GLboolean enabled)
{
	gDebugMessageControlARB(source, type, severity, count, ids, enabled);
	checkError();
}

void glDebugMessageInsertARB(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const * buf)
{
	gDebugMessageInsertARB(source, type, id, severity, length, buf);
	checkError();
}

void glDebugMessageCallbackARB(GLDEBUGPROCARB callback, GLvoid const * userParam)
{
	gDebugMessageCallbackARB(callback, userParam);
	checkError();
}

GLuint glGetDebugMessageLogARB(GLuint count, GLsizei bufsize, GLenum * sources, GLenum * types, GLuint * ids, GLenum * severities, GLsizei * lengths, GLchar * messageLog)
{
	auto result = gGetDebugMessageLogARB(count, bufsize, sources, types, ids, severities, lengths, messageLog);
	checkError();
	return result;
}

GLenum glGetGraphicsResetStatusARB(void)
{
	auto result = gGetGraphicsResetStatusARB();
	checkError();
	return result;
}

void glGetnMapdvARB(GLenum target, GLenum query, GLsizei bufSize, GLdouble * v)
{
	gGetnMapdvARB(target, query, bufSize, v);
	checkError();
}

void glGetnMapfvARB(GLenum target, GLenum query, GLsizei bufSize, GLfloat * v)
{
	gGetnMapfvARB(target, query, bufSize, v);
	checkError();
}

void glGetnMapivARB(GLenum target, GLenum query, GLsizei bufSize, GLint * v)
{
	gGetnMapivARB(target, query, bufSize, v);
	checkError();
}

void glGetnPixelMapfvARB(GLenum map, GLsizei bufSize, GLfloat * values)
{
	gGetnPixelMapfvARB(map, bufSize, values);
	checkError();
}

void glGetnPixelMapuivARB(GLenum map, GLsizei bufSize, GLuint * values)
{
	gGetnPixelMapuivARB(map, bufSize, values);
	checkError();
}

void glGetnPixelMapusvARB(GLenum map, GLsizei bufSize, GLushort * values)
{
	gGetnPixelMapusvARB(map, bufSize, values);
	checkError();
}

void glGetnPolygonStippleARB(GLsizei bufSize, GLubyte * pattern)
{
	gGetnPolygonStippleARB(bufSize, pattern);
	checkError();
}

void glGetnColorTableARB(GLenum target, GLenum format, GLenum type, GLsizei bufSize, GLvoid * table)
{
	gGetnColorTableARB(target, format, type, bufSize, table);
	checkError();
}

void glGetnConvolutionFilterARB(GLenum target, GLenum format, GLenum type, GLsizei bufSize, GLvoid * image)
{
	gGetnConvolutionFilterARB(target, format, type, bufSize, image);
	checkError();
}

void glGetnSeparableFilterARB(GLenum target, GLenum format, GLenum type, GLsizei rowBufSize, GLvoid * row, GLsizei columnBufSize, GLvoid * column, GLvoid * span)
{
	gGetnSeparableFilterARB(target, format, type, rowBufSize, row, columnBufSize, column, span);
	checkError();
}

void glGetnHistogramARB(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, GLvoid * values)
{
	gGetnHistogramARB(target, reset, format, type, bufSize, values);
	checkError();
}

void glGetnMinmaxARB(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, GLvoid * values)
{
	gGetnMinmaxARB(target, reset, format, type, bufSize, values);
	checkError();
}

void glGetnTexImageARB(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, GLvoid * img)
{
	gGetnTexImageARB(target, level, format, type, bufSize, img);
	checkError();
}

void glReadnPixelsARB(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, GLvoid * data)
{
	gReadnPixelsARB(x, y, width, height, format, type, bufSize, data);
	checkError();
}

void glGetnCompressedTexImageARB(GLenum target, GLint lod, GLsizei bufSize, GLvoid * img)
{
	gGetnCompressedTexImageARB(target, lod, bufSize, img);
	checkError();
}

void glGetnUniformfvARB(GLuint program, GLint location, GLsizei bufSize, GLfloat * params)
{
	gGetnUniformfvARB(program, location, bufSize, params);
	checkError();
}

void glGetnUniformivARB(GLuint program, GLint location, GLsizei bufSize, GLint * params)
{
	gGetnUniformivARB(program, location, bufSize, params);
	checkError();
}

void glGetnUniformuivARB(GLuint program, GLint location, GLsizei bufSize, GLuint * params)
{
	gGetnUniformuivARB(program, location, bufSize, params);
	checkError();
}

void glGetnUniformdvARB(GLuint program, GLint location, GLsizei bufSize, GLdouble * params)
{
	gGetnUniformdvARB(program, location, bufSize, params);
	checkError();
}

void glDrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei primcount, GLuint baseinstance)
{
	gDrawArraysInstancedBaseInstance(mode, first, count, primcount, baseinstance);
	checkError();
}

void glDrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei primcount, GLuint baseinstance)
{
	gDrawElementsInstancedBaseInstance(mode, count, type,  indices, primcount, baseinstance);
	checkError();
}

void glDrawElementsInstancedBaseVertexBaseInstance(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei primcount, GLint basevertex, GLuint baseinstance)
{
	gDrawElementsInstancedBaseVertexBaseInstance(mode, count, type,  indices, primcount, basevertex, baseinstance);
	checkError();
}

void glDrawTransformFeedbackInstanced(GLenum mode, GLuint id, GLsizei primcount)
{
	gDrawTransformFeedbackInstanced(mode, id, primcount);
	checkError();
}

void glDrawTransformFeedbackStreamInstanced(GLenum mode, GLuint id, GLuint stream, GLsizei primcount)
{
	gDrawTransformFeedbackStreamInstanced(mode, id, stream, primcount);
	checkError();
}

void glGetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint * params)
{
	gGetInternalformativ(target, internalformat, pname, bufSize, params);
	checkError();
}

void glGetActiveAtomicCounterBufferiv(GLuint program, GLuint bufferIndex, GLenum pname, GLint * params)
{
	gGetActiveAtomicCounterBufferiv(program, bufferIndex, pname, params);
	checkError();
}

void glBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format)
{
	gBindImageTexture(unit, texture, level, layered, layer, access, format);
	checkError();
}

void glMemoryBarrier(GLbitfield barriers)
{
	gMemoryBarrier(barriers);
	checkError();
}

void glTexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width)
{
	gTexStorage1D(target, levels, internalformat, width);
	checkError();
}

void glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
	gTexStorage2D(target, levels, internalformat, width, height);
	checkError();
}

void glTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
{
	gTexStorage3D(target, levels, internalformat, width, height, depth);
	checkError();
}

void glTextureStorage1DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width)
{
	gTextureStorage1DEXT(texture, target, levels, internalformat, width);
	checkError();
}

void glTextureStorage2DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
	gTextureStorage2DEXT(texture, target, levels, internalformat, width, height);
	checkError();
}

void glTextureStorage3DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
{
	gTextureStorage3DEXT(texture, target, levels, internalformat, width, height, depth);
	checkError();
}

}
}
}
