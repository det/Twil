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

void glCullFace(std::uint32_t mode)
{
	gCullFace(mode);
	checkError();
}

void glFrontFace(std::uint32_t mode)
{
	gFrontFace(mode);
	checkError();
}

void glHint(std::uint32_t target, std::uint32_t mode)
{
	gHint(target, mode);
	checkError();
}

void glLineWidth(float width)
{
	gLineWidth(width);
	checkError();
}

void glPointSize(float size)
{
	gPointSize(size);
	checkError();
}

void glPolygonMode(std::uint32_t face, std::uint32_t mode)
{
	gPolygonMode(face, mode);
	checkError();
}

void glScissor(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height)
{
	gScissor(x, y, width, height);
	checkError();
}

void glTexParameterf(std::uint32_t target, std::uint32_t pname, float param)
{
	gTexParameterf(target, pname, param);
	checkError();
}

void glTexParameterfv(std::uint32_t target, std::uint32_t pname, float const * params)
{
	gTexParameterfv(target, pname, params);
	checkError();
}

void glTexParameteri(std::uint32_t target, std::uint32_t pname, std::int32_t param)
{
	gTexParameteri(target, pname, param);
	checkError();
}

void glTexParameteriv(std::uint32_t target, std::uint32_t pname, std::int32_t const * params)
{
	gTexParameteriv(target, pname, params);
	checkError();
}

void glTexImage1D(std::uint32_t target, std::int32_t level, std::int32_t internalformat, std::int32_t width, std::int32_t border, std::uint32_t format, std::uint32_t type, void const * pixels)
{
	gTexImage1D(target, level, internalformat, width, border, format, type, pixels);
	checkError();
}

void glTexImage2D(std::uint32_t target, std::int32_t level, std::int32_t internalformat, std::int32_t width, std::int32_t height, std::int32_t border, std::uint32_t format, std::uint32_t type, void const * pixels)
{
	gTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
	checkError();
}

void glDrawBuffer(std::uint32_t mode)
{
	gDrawBuffer(mode);
	checkError();
}

void glClear(std::uint32_t mask)
{
	gClear(mask);
	checkError();
}

void glClearColor(float red, float green, float blue, float alpha)
{
	gClearColor(red, green, blue, alpha);
	checkError();
}

void glClearStencil(std::int32_t s)
{
	gClearStencil(s);
	checkError();
}

void glClearDepth(double depth)
{
	gClearDepth(depth);
	checkError();
}

void glStencilMask(std::uint32_t mask)
{
	gStencilMask(mask);
	checkError();
}

void glColorMask(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha)
{
	gColorMask(red, green, blue, alpha);
	checkError();
}

void glDepthMask(std::uint8_t flag)
{
	gDepthMask(flag);
	checkError();
}

void glDisable(std::uint32_t cap)
{
	gDisable(cap);
	checkError();
}

void glEnable(std::uint32_t cap)
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

void glBlendFunc(std::uint32_t sfactor, std::uint32_t dfactor)
{
	gBlendFunc(sfactor, dfactor);
	checkError();
}

void glLogicOp(std::uint32_t opcode)
{
	gLogicOp(opcode);
	checkError();
}

void glStencilFunc(std::uint32_t func, std::int32_t ref, std::uint32_t mask)
{
	gStencilFunc(func, ref, mask);
	checkError();
}

void glStencilOp(std::uint32_t fail, std::uint32_t zfail, std::uint32_t zpass)
{
	gStencilOp(fail, zfail, zpass);
	checkError();
}

void glDepthFunc(std::uint32_t func)
{
	gDepthFunc(func);
	checkError();
}

void glPixelStoref(std::uint32_t pname, float param)
{
	gPixelStoref(pname, param);
	checkError();
}

void glPixelStorei(std::uint32_t pname, std::int32_t param)
{
	gPixelStorei(pname, param);
	checkError();
}

void glReadBuffer(std::uint32_t mode)
{
	gReadBuffer(mode);
	checkError();
}

void glReadPixels(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, std::uint32_t format, std::uint32_t type, void * pixels)
{
	gReadPixels(x, y, width, height, format, type, pixels);
	checkError();
}

void glGetBooleanv(std::uint32_t pname, std::uint8_t * params)
{
	gGetBooleanv(pname, params);
	checkError();
}

void glGetDoublev(std::uint32_t pname, double * params)
{
	gGetDoublev(pname, params);
	checkError();
}

std::uint32_t glGetError()
{
	auto result = gGetError();
	checkError();
	return result;
}

void glGetFloatv(std::uint32_t pname, float * params)
{
	gGetFloatv(pname, params);
	checkError();
}

void glGetIntegerv(std::uint32_t pname, std::int32_t * params)
{
	gGetIntegerv(pname, params);
	checkError();
}

std::uint8_t const * glGetString(std::uint32_t name)
{
	auto result = gGetString(name);
	checkError();
	return result;
}

void glGetTexImage(std::uint32_t target, std::int32_t level, std::uint32_t format, std::uint32_t type, void * pixels)
{
	gGetTexImage(target, level, format, type, pixels);
	checkError();
}

void glGetTexParameterfv(std::uint32_t target, std::uint32_t pname, float * params)
{
	gGetTexParameterfv(target, pname, params);
	checkError();
}

void glGetTexParameteriv(std::uint32_t target, std::uint32_t pname, std::int32_t * params)
{
	gGetTexParameteriv(target, pname, params);
	checkError();
}

void glGetTexLevelParameterfv(std::uint32_t target, std::int32_t level, std::uint32_t pname, float * params)
{
	gGetTexLevelParameterfv(target, level, pname, params);
	checkError();
}

void glGetTexLevelParameteriv(std::uint32_t target, std::int32_t level, std::uint32_t pname, std::int32_t * params)
{
	gGetTexLevelParameteriv(target, level, pname, params);
	checkError();
}

std::uint8_t glIsEnabled(std::uint32_t cap)
{
	auto result = gIsEnabled(cap);
	checkError();
	return result;
}

void glDepthRange(double near, double far)
{
	gDepthRange(near, far);
	checkError();
}

void glViewport(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height)
{
	gViewport(x, y, width, height);
	checkError();
}

void glDrawArrays(std::uint32_t mode, std::int32_t first, std::int32_t count)
{
	gDrawArrays(mode, first, count);
	checkError();
}

void glDrawElements(std::uint32_t mode, std::int32_t count, std::uint32_t type, void const * indices)
{
	gDrawElements(mode, count, type, indices);
	checkError();
}

void glGetPointerv(std::uint32_t pname, void * * params)
{
	gGetPointerv(pname, params);
	checkError();
}

void glPolygonOffset(float factor, float units)
{
	gPolygonOffset(factor, units);
	checkError();
}

void glCopyTexImage1D(std::uint32_t target, std::int32_t level, std::uint32_t internalformat, std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t border)
{
	gCopyTexImage1D(target, level, internalformat, x, y, width, border);
	checkError();
}

void glCopyTexImage2D(std::uint32_t target, std::int32_t level, std::uint32_t internalformat, std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, std::int32_t border)
{
	gCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
	checkError();
}

void glCopyTexSubImage1D(std::uint32_t target, std::int32_t level, std::int32_t xoffset, std::int32_t x, std::int32_t y, std::int32_t width)
{
	gCopyTexSubImage1D(target, level, xoffset, x, y, width);
	checkError();
}

void glCopyTexSubImage2D(std::uint32_t target, std::int32_t level, std::int32_t xoffset, std::int32_t yoffset, std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height)
{
	gCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
	checkError();
}

void glTexSubImage1D(std::uint32_t target, std::int32_t level, std::int32_t xoffset, std::int32_t width, std::uint32_t format, std::uint32_t type, void const * pixels)
{
	gTexSubImage1D(target, level, xoffset, width, format, type, pixels);
	checkError();
}

void glTexSubImage2D(std::uint32_t target, std::int32_t level, std::int32_t xoffset, std::int32_t yoffset, std::int32_t width, std::int32_t height, std::uint32_t format, std::uint32_t type, void const * pixels)
{
	gTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
	checkError();
}

void glBindTexture(std::uint32_t target, std::uint32_t texture)
{
	gBindTexture(target, texture);
	checkError();
}

void glDeleteTextures(std::int32_t n, std::uint32_t const * textures)
{
	gDeleteTextures(n, textures);
	checkError();
}

void glGenTextures(std::int32_t n, std::uint32_t * textures)
{
	gGenTextures(n, textures);
	checkError();
}

std::uint8_t glIsTexture(std::uint32_t texture)
{
	auto result = gIsTexture(texture);
	checkError();
	return result;
}

void glBlendColor(float red, float green, float blue, float alpha)
{
	gBlendColor(red, green, blue, alpha);
	checkError();
}

void glBlendEquation(std::uint32_t mode)
{
	gBlendEquation(mode);
	checkError();
}

void glDrawRangeElements(std::uint32_t mode, std::uint32_t start, std::uint32_t end, std::int32_t count, std::uint32_t type, void const * indices)
{
	gDrawRangeElements(mode, start, end, count, type, indices);
	checkError();
}

void glTexImage3D(std::uint32_t target, std::int32_t level, std::int32_t internalformat, std::int32_t width, std::int32_t height, std::int32_t depth, std::int32_t border, std::uint32_t format, std::uint32_t type, void const * pixels)
{
	gTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
	checkError();
}

void glTexSubImage3D(std::uint32_t target, std::int32_t level, std::int32_t xoffset, std::int32_t yoffset, std::int32_t zoffset, std::int32_t width, std::int32_t height, std::int32_t depth, std::uint32_t format, std::uint32_t type, void const * pixels)
{
	gTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
	checkError();
}

void glCopyTexSubImage3D(std::uint32_t target, std::int32_t level, std::int32_t xoffset, std::int32_t yoffset, std::int32_t zoffset, std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height)
{
	gCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
	checkError();
}

void glActiveTexture(std::uint32_t texture)
{
	gActiveTexture(texture);
	checkError();
}

void glSampleCoverage(float value, std::uint8_t invert)
{
	gSampleCoverage(value, invert);
	checkError();
}

void glCompressedTexImage3D(std::uint32_t target, std::int32_t level, std::uint32_t internalformat, std::int32_t width, std::int32_t height, std::int32_t depth, std::int32_t border, std::int32_t imageSize, void const * data)
{
	gCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
	checkError();
}

void glCompressedTexImage2D(std::uint32_t target, std::int32_t level, std::uint32_t internalformat, std::int32_t width, std::int32_t height, std::int32_t border, std::int32_t imageSize, void const * data)
{
	gCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
	checkError();
}

void glCompressedTexImage1D(std::uint32_t target, std::int32_t level, std::uint32_t internalformat, std::int32_t width, std::int32_t border, std::int32_t imageSize, void const * data)
{
	gCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);
	checkError();
}

void glCompressedTexSubImage3D(std::uint32_t target, std::int32_t level, std::int32_t xoffset, std::int32_t yoffset, std::int32_t zoffset, std::int32_t width, std::int32_t height, std::int32_t depth, std::uint32_t format, std::int32_t imageSize, void const * data)
{
	gCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
	checkError();
}

void glCompressedTexSubImage2D(std::uint32_t target, std::int32_t level, std::int32_t xoffset, std::int32_t yoffset, std::int32_t width, std::int32_t height, std::uint32_t format, std::int32_t imageSize, void const * data)
{
	gCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
	checkError();
}

void glCompressedTexSubImage1D(std::uint32_t target, std::int32_t level, std::int32_t xoffset, std::int32_t width, std::uint32_t format, std::int32_t imageSize, void const * data)
{
	gCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
	checkError();
}

void glGetCompressedTexImage(std::uint32_t target, std::int32_t level, void * img)
{
	gGetCompressedTexImage(target, level, img);
	checkError();
}

void glBlendFuncSeparate(std::uint32_t sfactorRGB, std::uint32_t dfactorRGB, std::uint32_t sfactorAlpha, std::uint32_t dfactorAlpha)
{
	gBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
	checkError();
}

void glMultiDrawArrays(std::uint32_t mode, std::int32_t const * first, std::int32_t const * count, std::int32_t primcount)
{
	gMultiDrawArrays(mode, first, count, primcount);
	checkError();
}

void glMultiDrawElements(std::uint32_t mode, std::int32_t const * count, std::uint32_t type, void const * * indices, std::int32_t primcount)
{
	gMultiDrawElements(mode, count, type, indices, primcount);
	checkError();
}

void glPointParameterf(std::uint32_t pname, float param)
{
	gPointParameterf(pname, param);
	checkError();
}

void glPointParameterfv(std::uint32_t pname, float const * params)
{
	gPointParameterfv(pname, params);
	checkError();
}

void glPointParameteri(std::uint32_t pname, std::int32_t param)
{
	gPointParameteri(pname, param);
	checkError();
}

void glPointParameteriv(std::uint32_t pname, std::int32_t const * params)
{
	gPointParameteriv(pname, params);
	checkError();
}

void glGenQueries(std::int32_t n, std::uint32_t * ids)
{
	gGenQueries(n, ids);
	checkError();
}

void glDeleteQueries(std::int32_t n, std::uint32_t const * ids)
{
	gDeleteQueries(n, ids);
	checkError();
}

std::uint8_t glIsQuery(std::uint32_t id)
{
	auto result = gIsQuery(id);
	checkError();
	return result;
}

void glBeginQuery(std::uint32_t target, std::uint32_t id)
{
	gBeginQuery(target, id);
	checkError();
}

void glEndQuery(std::uint32_t target)
{
	gEndQuery(target);
	checkError();
}

void glGetQueryiv(std::uint32_t target, std::uint32_t pname, std::int32_t * params)
{
	gGetQueryiv(target, pname, params);
	checkError();
}

void glGetQueryObjectiv(std::uint32_t id, std::uint32_t pname, std::int32_t * params)
{
	gGetQueryObjectiv(id, pname, params);
	checkError();
}

void glGetQueryObjectuiv(std::uint32_t id, std::uint32_t pname, std::uint32_t * params)
{
	gGetQueryObjectuiv(id, pname, params);
	checkError();
}

void glBindBuffer(std::uint32_t target, std::uint32_t buffer)
{
	gBindBuffer(target, buffer);
	checkError();
}

void glDeleteBuffers(std::int32_t n, std::uint32_t const * buffers)
{
	gDeleteBuffers(n, buffers);
	checkError();
}

void glGenBuffers(std::int32_t n, std::uint32_t * buffers)
{
	gGenBuffers(n, buffers);
	checkError();
}

std::uint8_t glIsBuffer(std::uint32_t buffer)
{
	auto result = gIsBuffer(buffer);
	checkError();
	return result;
}

void glBufferData(std::uint32_t target, std::ptrdiff_t size, void const * data, std::uint32_t usage)
{
	gBufferData(target, size, data, usage);
	checkError();
}

void glBufferSubData(std::uint32_t target, std::ptrdiff_t offset, std::ptrdiff_t size, void const * data)
{
	gBufferSubData(target, offset, size, data);
	checkError();
}

void glGetBufferSubData(std::uint32_t target, std::ptrdiff_t offset, std::ptrdiff_t size, void * data)
{
	gGetBufferSubData(target, offset, size, data);
	checkError();
}

void * glMapBuffer(std::uint32_t target, std::uint32_t access)
{
	auto result = gMapBuffer(target, access);
	checkError();
	return result;
}

std::uint8_t glUnmapBuffer(std::uint32_t target)
{
	auto result = gUnmapBuffer(target);
	checkError();
	return result;
}

void glGetBufferParameteriv(std::uint32_t target, std::uint32_t pname, std::int32_t * params)
{
	gGetBufferParameteriv(target, pname, params);
	checkError();
}

void glGetBufferPointerv(std::uint32_t target, std::uint32_t pname, void * * params)
{
	gGetBufferPointerv(target, pname, params);
	checkError();
}

void glBlendEquationSeparate(std::uint32_t modeRGB, std::uint32_t modeAlpha)
{
	gBlendEquationSeparate(modeRGB, modeAlpha);
	checkError();
}

void glDrawBuffers(std::int32_t n, std::uint32_t const * bufs)
{
	gDrawBuffers(n, bufs);
	checkError();
}

void glStencilOpSeparate(std::uint32_t face, std::uint32_t sfail, std::uint32_t dpfail, std::uint32_t dppass)
{
	gStencilOpSeparate(face, sfail, dpfail, dppass);
	checkError();
}

void glStencilFuncSeparate(std::uint32_t face, std::uint32_t func, std::int32_t ref, std::uint32_t mask)
{
	gStencilFuncSeparate(face, func, ref, mask);
	checkError();
}

void glStencilMaskSeparate(std::uint32_t face, std::uint32_t mask)
{
	gStencilMaskSeparate(face, mask);
	checkError();
}

void glAttachShader(std::uint32_t program, std::uint32_t shader)
{
	gAttachShader(program, shader);
	checkError();
}

void glBindAttribLocation(std::uint32_t program, std::uint32_t index, char const * name)
{
	gBindAttribLocation(program, index, name);
	checkError();
}

void glCompileShader(std::uint32_t shader)
{
	gCompileShader(shader);
	checkError();
}

std::uint32_t glCreateProgram()
{
	auto result = gCreateProgram();
	checkError();
	return result;
}

std::uint32_t glCreateShader(std::uint32_t type)
{
	auto result = gCreateShader(type);
	checkError();
	return result;
}

void glDeleteProgram(std::uint32_t program)
{
	gDeleteProgram(program);
	checkError();
}

void glDeleteShader(std::uint32_t shader)
{
	gDeleteShader(shader);
	checkError();
}

void glDetachShader(std::uint32_t program, std::uint32_t shader)
{
	gDetachShader(program, shader);
	checkError();
}

void glDisableVertexAttribArray(std::uint32_t index)
{
	gDisableVertexAttribArray(index);
	checkError();
}

void glEnableVertexAttribArray(std::uint32_t index)
{
	gEnableVertexAttribArray(index);
	checkError();
}

void glGetActiveAttrib(std::uint32_t program, std::uint32_t index, std::int32_t bufSize, std::int32_t * length, std::int32_t * size, std::uint32_t * type, char * name)
{
	gGetActiveAttrib(program, index, bufSize, length, size, type, name);
	checkError();
}

void glGetActiveUniform(std::uint32_t program, std::uint32_t index, std::int32_t bufSize, std::int32_t * length, std::int32_t * size, std::uint32_t * type, char * name)
{
	gGetActiveUniform(program, index, bufSize, length, size, type, name);
	checkError();
}

void glGetAttachedShaders(std::uint32_t program, std::int32_t maxCount, std::int32_t * count, std::uint32_t * obj)
{
	gGetAttachedShaders(program, maxCount, count, obj);
	checkError();
}

std::int32_t glGetAttribLocation(std::uint32_t program, char const * name)
{
	auto result = gGetAttribLocation(program, name);
	checkError();
	return result;
}

void glGetProgramiv(std::uint32_t program, std::uint32_t pname, std::int32_t * params)
{
	gGetProgramiv(program, pname, params);
	checkError();
}

void glGetProgramInfoLog(std::uint32_t program, std::int32_t bufSize, std::int32_t * length, char * infoLog)
{
	gGetProgramInfoLog(program, bufSize, length, infoLog);
	checkError();
}

void glGetShaderiv(std::uint32_t shader, std::uint32_t pname, std::int32_t * params)
{
	gGetShaderiv(shader, pname, params);
	checkError();
}

void glGetShaderInfoLog(std::uint32_t shader, std::int32_t bufSize, std::int32_t * length, char * infoLog)
{
	gGetShaderInfoLog(shader, bufSize, length, infoLog);
	checkError();
}

void glGetShaderSource(std::uint32_t shader, std::int32_t bufSize, std::int32_t * length, char * source)
{
	gGetShaderSource(shader, bufSize, length, source);
	checkError();
}

std::int32_t glGetUniformLocation(std::uint32_t program, char const * name)
{
	auto result = gGetUniformLocation(program, name);
	checkError();
	return result;
}

void glGetUniformfv(std::uint32_t program, std::int32_t location, float * params)
{
	gGetUniformfv(program, location, params);
	checkError();
}

void glGetUniformiv(std::uint32_t program, std::int32_t location, std::int32_t * params)
{
	gGetUniformiv(program, location, params);
	checkError();
}

void glGetVertexAttribdv(std::uint32_t index, std::uint32_t pname, double * params)
{
	gGetVertexAttribdv(index, pname, params);
	checkError();
}

void glGetVertexAttribfv(std::uint32_t index, std::uint32_t pname, float * params)
{
	gGetVertexAttribfv(index, pname, params);
	checkError();
}

void glGetVertexAttribiv(std::uint32_t index, std::uint32_t pname, std::int32_t * params)
{
	gGetVertexAttribiv(index, pname, params);
	checkError();
}

void glGetVertexAttribPointerv(std::uint32_t index, std::uint32_t pname, void * * pointer)
{
	gGetVertexAttribPointerv(index, pname, pointer);
	checkError();
}

std::uint8_t glIsProgram(std::uint32_t program)
{
	auto result = gIsProgram(program);
	checkError();
	return result;
}

std::uint8_t glIsShader(std::uint32_t shader)
{
	auto result = gIsShader(shader);
	checkError();
	return result;
}

void glLinkProgram(std::uint32_t program)
{
	gLinkProgram(program);
	checkError();
}

void glShaderSource(std::uint32_t shader, std::int32_t count, char const * * string, std::int32_t const * length)
{
	gShaderSource(shader, count, string, length);
	checkError();
}

void glUseProgram(std::uint32_t program)
{
	gUseProgram(program);
	checkError();
}

void glUniform1f(std::int32_t location, float v0)
{
	gUniform1f(location, v0);
	checkError();
}

void glUniform2f(std::int32_t location, float v0, float v1)
{
	gUniform2f(location, v0, v1);
	checkError();
}

void glUniform3f(std::int32_t location, float v0, float v1, float v2)
{
	gUniform3f(location, v0, v1, v2);
	checkError();
}

void glUniform4f(std::int32_t location, float v0, float v1, float v2, float v3)
{
	gUniform4f(location, v0, v1, v2, v3);
	checkError();
}

void glUniform1i(std::int32_t location, std::int32_t v0)
{
	gUniform1i(location, v0);
	checkError();
}

void glUniform2i(std::int32_t location, std::int32_t v0, std::int32_t v1)
{
	gUniform2i(location, v0, v1);
	checkError();
}

void glUniform3i(std::int32_t location, std::int32_t v0, std::int32_t v1, std::int32_t v2)
{
	gUniform3i(location, v0, v1, v2);
	checkError();
}

void glUniform4i(std::int32_t location, std::int32_t v0, std::int32_t v1, std::int32_t v2, std::int32_t v3)
{
	gUniform4i(location, v0, v1, v2, v3);
	checkError();
}

void glUniform1fv(std::int32_t location, std::int32_t count, float const * value)
{
	gUniform1fv(location, count, value);
	checkError();
}

void glUniform2fv(std::int32_t location, std::int32_t count, float const * value)
{
	gUniform2fv(location, count, value);
	checkError();
}

void glUniform3fv(std::int32_t location, std::int32_t count, float const * value)
{
	gUniform3fv(location, count, value);
	checkError();
}

void glUniform4fv(std::int32_t location, std::int32_t count, float const * value)
{
	gUniform4fv(location, count, value);
	checkError();
}

void glUniform1iv(std::int32_t location, std::int32_t count, std::int32_t const * value)
{
	gUniform1iv(location, count, value);
	checkError();
}

void glUniform2iv(std::int32_t location, std::int32_t count, std::int32_t const * value)
{
	gUniform2iv(location, count, value);
	checkError();
}

void glUniform3iv(std::int32_t location, std::int32_t count, std::int32_t const * value)
{
	gUniform3iv(location, count, value);
	checkError();
}

void glUniform4iv(std::int32_t location, std::int32_t count, std::int32_t const * value)
{
	gUniform4iv(location, count, value);
	checkError();
}

void glUniformMatrix2fv(std::int32_t location, std::int32_t count, std::uint8_t transpose, float const * value)
{
	gUniformMatrix2fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix3fv(std::int32_t location, std::int32_t count, std::uint8_t transpose, float const * value)
{
	gUniformMatrix3fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix4fv(std::int32_t location, std::int32_t count, std::uint8_t transpose, float const * value)
{
	gUniformMatrix4fv(location, count, transpose, value);
	checkError();
}

void glValidateProgram(std::uint32_t program)
{
	gValidateProgram(program);
	checkError();
}

void glVertexAttrib1d(std::uint32_t index, double x)
{
	gVertexAttrib1d(index, x);
	checkError();
}

void glVertexAttrib1dv(std::uint32_t index, double const * v)
{
	gVertexAttrib1dv(index, v);
	checkError();
}

void glVertexAttrib1f(std::uint32_t index, float x)
{
	gVertexAttrib1f(index, x);
	checkError();
}

void glVertexAttrib1fv(std::uint32_t index, float const * v)
{
	gVertexAttrib1fv(index, v);
	checkError();
}

void glVertexAttrib1s(std::uint32_t index, std::int16_t x)
{
	gVertexAttrib1s(index, x);
	checkError();
}

void glVertexAttrib1sv(std::uint32_t index, std::int16_t const * v)
{
	gVertexAttrib1sv(index, v);
	checkError();
}

void glVertexAttrib2d(std::uint32_t index, double x, double y)
{
	gVertexAttrib2d(index, x, y);
	checkError();
}

void glVertexAttrib2dv(std::uint32_t index, double const * v)
{
	gVertexAttrib2dv(index, v);
	checkError();
}

void glVertexAttrib2f(std::uint32_t index, float x, float y)
{
	gVertexAttrib2f(index, x, y);
	checkError();
}

void glVertexAttrib2fv(std::uint32_t index, float const * v)
{
	gVertexAttrib2fv(index, v);
	checkError();
}

void glVertexAttrib2s(std::uint32_t index, std::int16_t x, std::int16_t y)
{
	gVertexAttrib2s(index, x, y);
	checkError();
}

void glVertexAttrib2sv(std::uint32_t index, std::int16_t const * v)
{
	gVertexAttrib2sv(index, v);
	checkError();
}

void glVertexAttrib3d(std::uint32_t index, double x, double y, double z)
{
	gVertexAttrib3d(index, x, y, z);
	checkError();
}

void glVertexAttrib3dv(std::uint32_t index, double const * v)
{
	gVertexAttrib3dv(index, v);
	checkError();
}

void glVertexAttrib3f(std::uint32_t index, float x, float y, float z)
{
	gVertexAttrib3f(index, x, y, z);
	checkError();
}

void glVertexAttrib3fv(std::uint32_t index, float const * v)
{
	gVertexAttrib3fv(index, v);
	checkError();
}

void glVertexAttrib3s(std::uint32_t index, std::int16_t x, std::int16_t y, std::int16_t z)
{
	gVertexAttrib3s(index, x, y, z);
	checkError();
}

void glVertexAttrib3sv(std::uint32_t index, std::int16_t const * v)
{
	gVertexAttrib3sv(index, v);
	checkError();
}

void glVertexAttrib4Nbv(std::uint32_t index, std::int8_t const * v)
{
	gVertexAttrib4Nbv(index, v);
	checkError();
}

void glVertexAttrib4Niv(std::uint32_t index, std::int32_t const * v)
{
	gVertexAttrib4Niv(index, v);
	checkError();
}

void glVertexAttrib4Nsv(std::uint32_t index, std::int16_t const * v)
{
	gVertexAttrib4Nsv(index, v);
	checkError();
}

void glVertexAttrib4Nub(std::uint32_t index, std::uint8_t x, std::uint8_t y, std::uint8_t z, std::uint8_t w)
{
	gVertexAttrib4Nub(index, x, y, z, w);
	checkError();
}

void glVertexAttrib4Nubv(std::uint32_t index, std::uint8_t const * v)
{
	gVertexAttrib4Nubv(index, v);
	checkError();
}

void glVertexAttrib4Nuiv(std::uint32_t index, std::uint32_t const * v)
{
	gVertexAttrib4Nuiv(index, v);
	checkError();
}

void glVertexAttrib4Nusv(std::uint32_t index, std::uint16_t const * v)
{
	gVertexAttrib4Nusv(index, v);
	checkError();
}

void glVertexAttrib4bv(std::uint32_t index, std::int8_t const * v)
{
	gVertexAttrib4bv(index, v);
	checkError();
}

void glVertexAttrib4d(std::uint32_t index, double x, double y, double z, double w)
{
	gVertexAttrib4d(index, x, y, z, w);
	checkError();
}

void glVertexAttrib4dv(std::uint32_t index, double const * v)
{
	gVertexAttrib4dv(index, v);
	checkError();
}

void glVertexAttrib4f(std::uint32_t index, float x, float y, float z, float w)
{
	gVertexAttrib4f(index, x, y, z, w);
	checkError();
}

void glVertexAttrib4fv(std::uint32_t index, float const * v)
{
	gVertexAttrib4fv(index, v);
	checkError();
}

void glVertexAttrib4iv(std::uint32_t index, std::int32_t const * v)
{
	gVertexAttrib4iv(index, v);
	checkError();
}

void glVertexAttrib4s(std::uint32_t index, std::int16_t x, std::int16_t y, std::int16_t z, std::int16_t w)
{
	gVertexAttrib4s(index, x, y, z, w);
	checkError();
}

void glVertexAttrib4sv(std::uint32_t index, std::int16_t const * v)
{
	gVertexAttrib4sv(index, v);
	checkError();
}

void glVertexAttrib4ubv(std::uint32_t index, std::uint8_t const * v)
{
	gVertexAttrib4ubv(index, v);
	checkError();
}

void glVertexAttrib4uiv(std::uint32_t index, std::uint32_t const * v)
{
	gVertexAttrib4uiv(index, v);
	checkError();
}

void glVertexAttrib4usv(std::uint32_t index, std::uint16_t const * v)
{
	gVertexAttrib4usv(index, v);
	checkError();
}

void glVertexAttribPointer(std::uint32_t index, std::int32_t size, std::uint32_t type, std::uint8_t normalized, std::int32_t stride, void const * pointer)
{
	gVertexAttribPointer(index, size, type, normalized, stride, pointer);
	checkError();
}

void glUniformMatrix2x3fv(std::int32_t location, std::int32_t count, std::uint8_t transpose, float const * value)
{
	gUniformMatrix2x3fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix3x2fv(std::int32_t location, std::int32_t count, std::uint8_t transpose, float const * value)
{
	gUniformMatrix3x2fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix2x4fv(std::int32_t location, std::int32_t count, std::uint8_t transpose, float const * value)
{
	gUniformMatrix2x4fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix4x2fv(std::int32_t location, std::int32_t count, std::uint8_t transpose, float const * value)
{
	gUniformMatrix4x2fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix3x4fv(std::int32_t location, std::int32_t count, std::uint8_t transpose, float const * value)
{
	gUniformMatrix3x4fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix4x3fv(std::int32_t location, std::int32_t count, std::uint8_t transpose, float const * value)
{
	gUniformMatrix4x3fv(location, count, transpose, value);
	checkError();
}

void glColorMaski(std::uint32_t index, std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
	gColorMaski(index, r, g, b, a);
	checkError();
}

void glGetBooleani_v(std::uint32_t target, std::uint32_t index, std::uint8_t * data)
{
	gGetBooleani_v(target, index, data);
	checkError();
}

void glGetIntegeri_v(std::uint32_t target, std::uint32_t index, std::int32_t * data)
{
	gGetIntegeri_v(target, index, data);
	checkError();
}

void glEnablei(std::uint32_t target, std::uint32_t index)
{
	gEnablei(target, index);
	checkError();
}

void glDisablei(std::uint32_t target, std::uint32_t index)
{
	gDisablei(target, index);
	checkError();
}

std::uint8_t glIsEnabledi(std::uint32_t target, std::uint32_t index)
{
	auto result = gIsEnabledi(target, index);
	checkError();
	return result;
}

void glBeginTransformFeedback(std::uint32_t primitiveMode)
{
	gBeginTransformFeedback(primitiveMode);
	checkError();
}

void glEndTransformFeedback(void)
{
	gEndTransformFeedback();
	checkError();
}

void glBindBufferRange(std::uint32_t target, std::uint32_t index, std::uint32_t buffer, std::ptrdiff_t offset, std::ptrdiff_t size)
{
	gBindBufferRange(target, index, buffer, offset, size);
	checkError();
}

void glBindBufferBase(std::uint32_t target, std::uint32_t index, std::uint32_t buffer)
{
	gBindBufferBase(target, index, buffer);
	checkError();
}

void glTransformFeedbackVaryings(std::uint32_t program, std::int32_t count, char const * * varyings, std::uint32_t bufferMode)
{
	gTransformFeedbackVaryings(program, count, varyings, bufferMode);
	checkError();
}

void glGetTransformFeedbackVarying(std::uint32_t program, std::uint32_t index, std::int32_t bufSize, std::int32_t * length, std::int32_t * size, std::uint32_t * type, char * name)
{
	gGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
	checkError();
}

void glClampColor(std::uint32_t target, std::uint32_t clamp)
{
	gClampColor(target, clamp);
	checkError();
}

void glBeginConditionalRender(std::uint32_t id, std::uint32_t mode)
{
	gBeginConditionalRender(id, mode);
	checkError();
}

void glEndConditionalRender(void)
{
	gEndConditionalRender();
	checkError();
}

void glVertexAttribIPointer(std::uint32_t index, std::int32_t size, std::uint32_t type, std::int32_t stride, void const * pointer)
{
	gVertexAttribIPointer(index, size, type, stride, pointer);
	checkError();
}

void glGetVertexAttribIiv(std::uint32_t index, std::uint32_t pname, std::int32_t * params)
{
	gGetVertexAttribIiv(index, pname, params);
	checkError();
}

void glGetVertexAttribIuiv(std::uint32_t index, std::uint32_t pname, std::uint32_t * params)
{
	gGetVertexAttribIuiv(index, pname, params);
	checkError();
}

void glVertexAttribI1i(std::uint32_t index, std::int32_t x)
{
	gVertexAttribI1i(index, x);
	checkError();
}

void glVertexAttribI2i(std::uint32_t index, std::int32_t x, std::int32_t y)
{
	gVertexAttribI2i(index, x, y);
	checkError();
}

void glVertexAttribI3i(std::uint32_t index, std::int32_t x, std::int32_t y, std::int32_t z)
{
	gVertexAttribI3i(index, x, y, z);
	checkError();
}

void glVertexAttribI4i(std::uint32_t index, std::int32_t x, std::int32_t y, std::int32_t z, std::int32_t w)
{
	gVertexAttribI4i(index, x, y, z, w);
	checkError();
}

void glVertexAttribI1ui(std::uint32_t index, std::uint32_t x)
{
	gVertexAttribI1ui(index, x);
	checkError();
}

void glVertexAttribI2ui(std::uint32_t index, std::uint32_t x, std::uint32_t y)
{
	gVertexAttribI2ui(index, x, y);
	checkError();
}

void glVertexAttribI3ui(std::uint32_t index, std::uint32_t x, std::uint32_t y, std::uint32_t z)
{
	gVertexAttribI3ui(index, x, y, z);
	checkError();
}

void glVertexAttribI4ui(std::uint32_t index, std::uint32_t x, std::uint32_t y, std::uint32_t z, std::uint32_t w)
{
	gVertexAttribI4ui(index, x, y, z, w);
	checkError();
}

void glVertexAttribI1iv(std::uint32_t index, std::int32_t const * v)
{
	gVertexAttribI1iv(index, v);
	checkError();
}

void glVertexAttribI2iv(std::uint32_t index, std::int32_t const * v)
{
	gVertexAttribI2iv(index, v);
	checkError();
}

void glVertexAttribI3iv(std::uint32_t index, std::int32_t const * v)
{
	gVertexAttribI3iv(index, v);
	checkError();
}

void glVertexAttribI4iv(std::uint32_t index, std::int32_t const * v)
{
	gVertexAttribI4iv(index, v);
	checkError();
}

void glVertexAttribI1uiv(std::uint32_t index, std::uint32_t const * v)
{
	gVertexAttribI1uiv(index, v);
	checkError();
}

void glVertexAttribI2uiv(std::uint32_t index, std::uint32_t const * v)
{
	gVertexAttribI2uiv(index, v);
	checkError();
}

void glVertexAttribI3uiv(std::uint32_t index, std::uint32_t const * v)
{
	gVertexAttribI3uiv(index, v);
	checkError();
}

void glVertexAttribI4uiv(std::uint32_t index, std::uint32_t const * v)
{
	gVertexAttribI4uiv(index, v);
	checkError();
}

void glVertexAttribI4bv(std::uint32_t index, std::int8_t const * v)
{
	gVertexAttribI4bv(index, v);
	checkError();
}

void glVertexAttribI4sv(std::uint32_t index, std::int16_t const * v)
{
	gVertexAttribI4sv(index, v);
	checkError();
}

void glVertexAttribI4ubv(std::uint32_t index, std::uint8_t const * v)
{
	gVertexAttribI4ubv(index, v);
	checkError();
}

void glVertexAttribI4usv(std::uint32_t index, std::uint16_t const * v)
{
	gVertexAttribI4usv(index, v);
	checkError();
}

void glGetUniformuiv(std::uint32_t program, std::int32_t location, std::uint32_t * params)
{
	gGetUniformuiv(program, location, params);
	checkError();
}

void glBindFragDataLocation(std::uint32_t program, std::uint32_t color, char const * name)
{
	gBindFragDataLocation(program, color, name);
	checkError();
}

std::int32_t glGetFragDataLocation(std::uint32_t program, char const * name)
{
	auto result = gGetFragDataLocation(program, name);
	checkError();
	return result;
}

void glUniform1ui(std::int32_t location, std::uint32_t v0)
{
	gUniform1ui(location, v0);
	checkError();
}

void glUniform2ui(std::int32_t location, std::uint32_t v0, std::uint32_t v1)
{
	gUniform2ui(location, v0, v1);
	checkError();
}

void glUniform3ui(std::int32_t location, std::uint32_t v0, std::uint32_t v1, std::uint32_t v2)
{
	gUniform3ui(location, v0, v1, v2);
	checkError();
}

void glUniform4ui(std::int32_t location, std::uint32_t v0, std::uint32_t v1, std::uint32_t v2, std::uint32_t v3)
{
	gUniform4ui(location, v0, v1, v2, v3);
	checkError();
}

void glUniform1uiv(std::int32_t location, std::int32_t count, std::uint32_t const * value)
{
	gUniform1uiv(location, count, value);
	checkError();
}

void glUniform2uiv(std::int32_t location, std::int32_t count, std::uint32_t const * value)
{
	gUniform2uiv(location, count, value);
	checkError();
}

void glUniform3uiv(std::int32_t location, std::int32_t count, std::uint32_t const * value)
{
	gUniform3uiv(location, count, value);
	checkError();
}

void glUniform4uiv(std::int32_t location, std::int32_t count, std::uint32_t const * value)
{
	gUniform4uiv(location, count, value);
	checkError();
}

void glTexParameterIiv(std::uint32_t target, std::uint32_t pname, std::int32_t const * params)
{
	gTexParameterIiv(target, pname, params);
	checkError();
}

void glTexParameterIuiv(std::uint32_t target, std::uint32_t pname, std::uint32_t const * params)
{
	gTexParameterIuiv(target, pname, params);
	checkError();
}

void glGetTexParameterIiv(std::uint32_t target, std::uint32_t pname, std::int32_t * params)
{
	gGetTexParameterIiv(target, pname, params);
	checkError();
}

void glGetTexParameterIuiv(std::uint32_t target, std::uint32_t pname, std::uint32_t * params)
{
	gGetTexParameterIuiv(target, pname, params);
	checkError();
}

void glClearBufferiv(std::uint32_t buffer, std::int32_t drawbuffer, std::int32_t const * value)
{
	gClearBufferiv(buffer, drawbuffer, value);
	checkError();
}

void glClearBufferuiv(std::uint32_t buffer, std::int32_t drawbuffer, std::uint32_t const * value)
{
	gClearBufferuiv(buffer, drawbuffer, value);
	checkError();
}

void glClearBufferfv(std::uint32_t buffer, std::int32_t drawbuffer, float const * value)
{
	gClearBufferfv(buffer, drawbuffer, value);
	checkError();
}

void glClearBufferfi(std::uint32_t buffer, std::int32_t drawbuffer, float depth, std::int32_t stencil)
{
	gClearBufferfi(buffer, drawbuffer, depth, stencil);
	checkError();
}

std::uint8_t const * glGetStringi (std::uint32_t name, std::uint32_t index)
{
	auto result = gGetStringi (name, index);
	checkError();
	return result;
}

void glDrawArraysInstanced(std::uint32_t mode, std::int32_t first, std::int32_t count, std::int32_t primcount)
{
	gDrawArraysInstanced(mode, first, count, primcount);
	checkError();
}

void glDrawElementsInstanced(std::uint32_t mode, std::int32_t count, std::uint32_t type, void const * indices, std::int32_t primcount)
{
	gDrawElementsInstanced(mode, count, type, indices, primcount);
	checkError();
}

void glTexBuffer(std::uint32_t target, std::uint32_t internalformat, std::uint32_t buffer)
{
	gTexBuffer(target, internalformat, buffer);
	checkError();
}

void glPrimitiveRestartIndex(std::uint32_t index)
{
	gPrimitiveRestartIndex(index);
	checkError();
}

void glGetInteger64i_v(std::uint32_t target, std::uint32_t index, std::int64_t *data)
{
	gGetInteger64i_v(target, index, data);
	checkError();
}

void glGetBufferParameteri64v(std::uint32_t target, std::uint32_t pname, std::int64_t *params)
{
	gGetBufferParameteri64v(target, pname, params);
	checkError();
}

void glFramebufferTexture(std::uint32_t target, std::uint32_t attachment, std::uint32_t texture, std::int32_t level)
{
	gFramebufferTexture(target, attachment, texture, level);
	checkError();
}

void glVertexAttribDivisor(std::uint32_t index, std::uint32_t divisor)
{
	gVertexAttribDivisor(index, divisor);
	checkError();
}

void glMinSampleShading(float value)
{
	gMinSampleShading(value);
	checkError();
}

void glBlendEquationi(std::uint32_t buf, std::uint32_t mode)
{
	gBlendEquationi(buf, mode);
	checkError();
}

void glBlendEquationSeparatei(std::uint32_t buf, std::uint32_t modeRGB, std::uint32_t modeAlpha)
{
	gBlendEquationSeparatei(buf, modeRGB, modeAlpha);
	checkError();
}

void glBlendFunci(std::uint32_t buf, std::uint32_t src, std::uint32_t dst)
{
	gBlendFunci(buf, src, dst);
	checkError();
}

void glBlendFuncSeparatei(std::uint32_t buf, std::uint32_t srcRGB, std::uint32_t dstRGB, std::uint32_t srcAlpha, std::uint32_t dstAlpha)
{
	gBlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
	checkError();
}

std::uint8_t glIsRenderbuffer(std::uint32_t renderbuffer)
{
	auto result = gIsRenderbuffer(renderbuffer);
	checkError();
	return result;
}

void glBindRenderbuffer(std::uint32_t target, std::uint32_t renderbuffer)
{
	gBindRenderbuffer(target, renderbuffer);
	checkError();
}

void glDeleteRenderbuffers(std::int32_t n, std::uint32_t const * renderbuffers)
{
	gDeleteRenderbuffers(n, renderbuffers);
	checkError();
}

void glGenRenderbuffers(std::int32_t n, std::uint32_t * renderbuffers)
{
	gGenRenderbuffers(n, renderbuffers);
	checkError();
}

void glRenderbufferStorage(std::uint32_t target, std::uint32_t internalformat, std::int32_t width, std::int32_t height)
{
	gRenderbufferStorage(target, internalformat, width, height);
	checkError();
}

void glGetRenderbufferParameteriv(std::uint32_t target, std::uint32_t pname, std::int32_t * params)
{
	gGetRenderbufferParameteriv(target, pname, params);
	checkError();
}

std::uint8_t glIsFramebuffer(std::uint32_t framebuffer)
{
	auto result = gIsFramebuffer(framebuffer);
	checkError();
	return result;
}

void glBindFramebuffer(std::uint32_t target, std::uint32_t framebuffer)
{
	gBindFramebuffer(target, framebuffer);
	checkError();
}

void glDeleteFramebuffers(std::int32_t n, std::uint32_t const * framebuffers)
{
	gDeleteFramebuffers(n, framebuffers);
	checkError();
}

void glGenFramebuffers(std::int32_t n, std::uint32_t * framebuffers)
{
	gGenFramebuffers(n, framebuffers);
	checkError();
}

std::uint32_t glCheckFramebufferStatus(std::uint32_t target)
{
	auto result = gCheckFramebufferStatus(target);
	checkError();
	return result;
}

void glFramebufferTexture1D(std::uint32_t target, std::uint32_t attachment, std::uint32_t textarget, std::uint32_t texture, std::int32_t level)
{
	gFramebufferTexture1D(target, attachment, textarget, texture, level);
	checkError();
}

void glFramebufferTexture2D(std::uint32_t target, std::uint32_t attachment, std::uint32_t textarget, std::uint32_t texture, std::int32_t level)
{
	gFramebufferTexture2D(target, attachment, textarget, texture, level);
	checkError();
}

void glFramebufferTexture3D(std::uint32_t target, std::uint32_t attachment, std::uint32_t textarget, std::uint32_t texture, std::int32_t level, std::int32_t zoffset)
{
	gFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);
	checkError();
}

void glFramebufferRenderbuffer(std::uint32_t target, std::uint32_t attachment, std::uint32_t renderbuffertarget, std::uint32_t renderbuffer)
{
	gFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
	checkError();
}

void glGetFramebufferAttachmentParameteriv(std::uint32_t target, std::uint32_t attachment, std::uint32_t pname, std::int32_t * params)
{
	gGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
	checkError();
}

void glGenerateMipmap(std::uint32_t target)
{
	gGenerateMipmap(target);
	checkError();
}

void glBlitFramebuffer(std::int32_t srcX0, std::int32_t srcY0, std::int32_t srcX1, std::int32_t srcY1, std::int32_t dstX0, std::int32_t dstY0, std::int32_t dstX1, std::int32_t dstY1, std::uint32_t mask, std::uint32_t filter)
{
	gBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
	checkError();
}

void glRenderbufferStorageMultisample(std::uint32_t target, std::int32_t samples, std::uint32_t internalformat, std::int32_t width, std::int32_t height)
{
	gRenderbufferStorageMultisample(target, samples, internalformat, width, height);
	checkError();
}

void glFramebufferTextureLayer(std::uint32_t target, std::uint32_t attachment, std::uint32_t texture, std::int32_t level, std::int32_t layer)
{
	gFramebufferTextureLayer(target, attachment, texture, level, layer);
	checkError();
}

void * glMapBufferRange(std::uint32_t target, std::ptrdiff_t offset, std::ptrdiff_t length, std::uint32_t access)
{
	auto result = gMapBufferRange(target, offset, length, access);
	checkError();
	return result;
}

void glFlushMappedBufferRange(std::uint32_t target, std::ptrdiff_t offset, std::ptrdiff_t length)
{
	gFlushMappedBufferRange(target, offset, length);
	checkError();
}

void glBindVertexArray(std::uint32_t array)
{
	gBindVertexArray(array);
	checkError();
}

void glDeleteVertexArrays(std::int32_t n, std::uint32_t const * arrays)
{
	gDeleteVertexArrays(n, arrays);
	checkError();
}

void glGenVertexArrays(std::int32_t n, std::uint32_t * arrays)
{
	gGenVertexArrays(n, arrays);
	checkError();
}

std::uint8_t glIsVertexArray(std::uint32_t array)
{
	auto result = gIsVertexArray(array);
	checkError();
	return result;
}

void glGetUniformIndices(std::uint32_t program, std::int32_t uniformCount, char const * * uniformNames, std::uint32_t * uniformIndices)
{
	gGetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
	checkError();
}

void glGetActiveUniformsiv(std::uint32_t program, std::int32_t uniformCount, std::uint32_t const * uniformIndices, std::uint32_t pname, std::int32_t * params)
{
	gGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);
	checkError();
}

void glGetActiveUniformName(std::uint32_t program, std::uint32_t uniformIndex, std::int32_t bufSize, std::int32_t * length, char * uniformName)
{
	gGetActiveUniformName(program, uniformIndex, bufSize, length, uniformName);
	checkError();
}

std::uint32_t glGetUniformBlockIndex(std::uint32_t program, char const * uniformBlockName)
{
	auto result = gGetUniformBlockIndex(program, uniformBlockName);
	checkError();
	return result;
}

void glGetActiveUniformBlockiv(std::uint32_t program, std::uint32_t uniformBlockIndex, std::uint32_t pname, std::int32_t * params)
{
	gGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
	checkError();
}

void glGetActiveUniformBlockName(std::uint32_t program, std::uint32_t uniformBlockIndex, std::int32_t bufSize, std::int32_t * length, char * uniformBlockName)
{
	gGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
	checkError();
}

void glUniformBlockBinding(std::uint32_t program, std::uint32_t uniformBlockIndex, std::uint32_t uniformBlockBinding)
{
	gUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
	checkError();
}

void glCopyBufferSubData(std::uint32_t readTarget, std::uint32_t writeTarget, std::ptrdiff_t readOffset, std::ptrdiff_t writeOffset, std::ptrdiff_t size)
{
	gCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
	checkError();
}

void glDrawElementsBaseVertex(std::uint32_t mode, std::int32_t count, std::uint32_t type, void const * indices, std::int32_t basevertex)
{
	gDrawElementsBaseVertex(mode, count, type, indices, basevertex);
	checkError();
}

void glDrawRangeElementsBaseVertex(std::uint32_t mode, std::uint32_t start, std::uint32_t end, std::int32_t count, std::uint32_t type, void const * indices, std::int32_t basevertex)
{
	gDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
	checkError();
}

void glDrawElementsInstancedBaseVertex(std::uint32_t mode, std::int32_t count, std::uint32_t type, void const * indices, std::int32_t primcount, std::int32_t basevertex)
{
	gDrawElementsInstancedBaseVertex(mode, count, type, indices, primcount, basevertex);
	checkError();
}

void glMultiDrawElementsBaseVertex(std::uint32_t mode, std::int32_t const * count, std::uint32_t type, void const * * indices, std::int32_t primcount, std::int32_t const * basevertex)
{
	gMultiDrawElementsBaseVertex(mode, count, type, indices, primcount, basevertex);
	checkError();
}

void glProvokingVertex(std::uint32_t mode)
{
	gProvokingVertex(mode);
	checkError();
}

GLsync glFenceSync(std::uint32_t condition, std::uint32_t flags)
{
	auto result = gFenceSync(condition, flags);
	checkError();
	return result;
}

std::uint8_t glIsSync(GLsync sync)
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

std::uint32_t glClientWaitSync(GLsync sync, std::uint32_t flags, std::uint64_t timeout)
{
	auto result = gClientWaitSync(sync, flags, timeout);
	checkError();
	return result;
}

void glWaitSync(GLsync sync, std::uint32_t flags, std::uint64_t timeout)
{
	gWaitSync(sync, flags, timeout);
	checkError();
}

void glGetInteger64v(std::uint32_t pname, std::int64_t *params)
{
	gGetInteger64v(pname, params);
	checkError();
}

void glGetSynciv(GLsync sync, std::uint32_t pname, std::int32_t bufSize, std::int32_t * length, std::int32_t * values)
{
	gGetSynciv(sync, pname, bufSize, length, values);
	checkError();
}

void glTexImage2DMultisample(std::uint32_t target, std::int32_t samples, std::int32_t internalformat, std::int32_t width, std::int32_t height, std::uint8_t fixedsamplelocations)
{
	gTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
	checkError();
}

void glTexImage3DMultisample(std::uint32_t target, std::int32_t samples, std::int32_t internalformat, std::int32_t width, std::int32_t height, std::int32_t depth, std::uint8_t fixedsamplelocations)
{
	gTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
	checkError();
}

void glGetMultisamplefv(std::uint32_t pname, std::uint32_t index, float * val)
{
	gGetMultisamplefv(pname, index, val);
	checkError();
}

void glSampleMaski(std::uint32_t index, std::uint32_t mask)
{
	gSampleMaski(index, mask);
	checkError();
}

void glBlendEquationiARB(std::uint32_t buf, std::uint32_t mode)
{
	gBlendEquationiARB(buf, mode);
	checkError();
}

void glBlendEquationSeparateiARB(std::uint32_t buf, std::uint32_t modeRGB, std::uint32_t modeAlpha)
{
	gBlendEquationSeparateiARB(buf, modeRGB, modeAlpha);
	checkError();
}

void glBlendFunciARB(std::uint32_t buf, std::uint32_t src, std::uint32_t dst)
{
	gBlendFunciARB(buf, src, dst);
	checkError();
}

void glBlendFuncSeparateiARB(std::uint32_t buf, std::uint32_t srcRGB, std::uint32_t dstRGB, std::uint32_t srcAlpha, std::uint32_t dstAlpha)
{
	gBlendFuncSeparateiARB(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
	checkError();
}

void glMinSampleShadingARB(float value)
{
	gMinSampleShadingARB(value);
	checkError();
}

void glNamedStringARB(std::uint32_t type, std::int32_t namelen, char const * name, std::int32_t stringlen, char const * string)
{
	gNamedStringARB(type, namelen, name, stringlen, string);
	checkError();
}

void glDeleteNamedStringARB(std::int32_t namelen, char const * name)
{
	gDeleteNamedStringARB(namelen, name);
	checkError();
}

void glCompileShaderIncludeARB(std::uint32_t shader, std::int32_t count, char const * * path, std::int32_t const * length)
{
	gCompileShaderIncludeARB(shader, count, path, length);
	checkError();
}

std::uint8_t glIsNamedStringARB(std::int32_t namelen, char const * name)
{
	auto result = gIsNamedStringARB(namelen, name);
	checkError();
	return result;
}

void glGetNamedStringARB(std::int32_t namelen, char const * name, std::int32_t bufSize, std::int32_t * stringlen, char * string)
{
	gGetNamedStringARB(namelen, name, bufSize, stringlen, string);
	checkError();
}

void glGetNamedStringivARB(std::int32_t namelen, char const * name, std::uint32_t pname, std::int32_t * params)
{
	gGetNamedStringivARB(namelen, name, pname, params);
	checkError();
}

void glBindFragDataLocationIndexed(std::uint32_t program, std::uint32_t colorNumber, std::uint32_t index, char const * name)
{
	gBindFragDataLocationIndexed(program, colorNumber, index, name);
	checkError();
}

std::int32_t glGetFragDataIndex(std::uint32_t program, char const * name)
{
	auto result = gGetFragDataIndex(program, name);
	checkError();
	return result;
}

void glGenSamplers(std::int32_t count, std::uint32_t * samplers)
{
	gGenSamplers(count, samplers);
	checkError();
}

void glDeleteSamplers(std::int32_t count, std::uint32_t const * samplers)
{
	gDeleteSamplers(count, samplers);
	checkError();
}

std::uint8_t glIsSampler(std::uint32_t sampler)
{
	auto result = gIsSampler(sampler);
	checkError();
	return result;
}

void glBindSampler(std::uint32_t unit, std::uint32_t sampler)
{
	gBindSampler(unit, sampler);
	checkError();
}

void glSamplerParameteri(std::uint32_t sampler, std::uint32_t pname, std::int32_t param)
{
	gSamplerParameteri(sampler, pname, param);
	checkError();
}

void glSamplerParameteriv(std::uint32_t sampler, std::uint32_t pname, std::int32_t const * param)
{
	gSamplerParameteriv(sampler, pname, param);
	checkError();
}

void glSamplerParameterf(std::uint32_t sampler, std::uint32_t pname, float param)
{
	gSamplerParameterf(sampler, pname, param);
	checkError();
}

void glSamplerParameterfv(std::uint32_t sampler, std::uint32_t pname, float const * param)
{
	gSamplerParameterfv(sampler, pname, param);
	checkError();
}

void glSamplerParameterIiv(std::uint32_t sampler, std::uint32_t pname, std::int32_t const * param)
{
	gSamplerParameterIiv(sampler, pname, param);
	checkError();
}

void glSamplerParameterIuiv(std::uint32_t sampler, std::uint32_t pname, std::uint32_t const * param)
{
	gSamplerParameterIuiv(sampler, pname, param);
	checkError();
}

void glGetSamplerParameteriv(std::uint32_t sampler, std::uint32_t pname, std::int32_t * params)
{
	gGetSamplerParameteriv(sampler, pname, params);
	checkError();
}

void glGetSamplerParameterIiv(std::uint32_t sampler, std::uint32_t pname, std::int32_t * params)
{
	gGetSamplerParameterIiv(sampler, pname, params);
	checkError();
}

void glGetSamplerParameterfv(std::uint32_t sampler, std::uint32_t pname, float * params)
{
	gGetSamplerParameterfv(sampler, pname, params);
	checkError();
}

void glGetSamplerParameterIuiv(std::uint32_t sampler, std::uint32_t pname, std::uint32_t * params)
{
	gGetSamplerParameterIuiv(sampler, pname, params);
	checkError();
}

void glQueryCounter(std::uint32_t id, std::uint32_t target)
{
	gQueryCounter(id, target);
	checkError();
}

void glGetQueryObjecti64v(std::uint32_t id, std::uint32_t pname, std::int64_t *params)
{
	gGetQueryObjecti64v(id, pname, params);
	checkError();
}

void glGetQueryObjectui64v(std::uint32_t id, std::uint32_t pname, std::uint64_t *params)
{
	gGetQueryObjectui64v(id, pname, params);
	checkError();
}

void glVertexAttribP1ui(std::uint32_t index, std::uint32_t type, std::uint8_t normalized, std::uint32_t value)
{
	gVertexAttribP1ui(index, type, normalized, value);
	checkError();
}

void glVertexAttribP1uiv(std::uint32_t index, std::uint32_t type, std::uint8_t normalized, std::uint32_t const * value)
{
	gVertexAttribP1uiv(index, type, normalized, value);
	checkError();
}

void glVertexAttribP2ui(std::uint32_t index, std::uint32_t type, std::uint8_t normalized, std::uint32_t value)
{
	gVertexAttribP2ui(index, type, normalized, value);
	checkError();
}

void glVertexAttribP2uiv(std::uint32_t index, std::uint32_t type, std::uint8_t normalized, std::uint32_t const * value)
{
	gVertexAttribP2uiv(index, type, normalized, value);
	checkError();
}

void glVertexAttribP3ui(std::uint32_t index, std::uint32_t type, std::uint8_t normalized, std::uint32_t value)
{
	gVertexAttribP3ui(index, type, normalized, value);
	checkError();
}

void glVertexAttribP3uiv(std::uint32_t index, std::uint32_t type, std::uint8_t normalized, std::uint32_t const * value)
{
	gVertexAttribP3uiv(index, type, normalized, value);
	checkError();
}

void glVertexAttribP4ui(std::uint32_t index, std::uint32_t type, std::uint8_t normalized, std::uint32_t value)
{
	gVertexAttribP4ui(index, type, normalized, value);
	checkError();
}

void glVertexAttribP4uiv(std::uint32_t index, std::uint32_t type, std::uint8_t normalized, std::uint32_t const * value)
{
	gVertexAttribP4uiv(index, type, normalized, value);
	checkError();
}

void glDrawArraysIndirect(std::uint32_t mode, void const * indirect)
{
	gDrawArraysIndirect(mode, indirect);
	checkError();
}

void glDrawElementsIndirect(std::uint32_t mode, std::uint32_t type, void const * indirect)
{
	gDrawElementsIndirect(mode, type, indirect);
	checkError();
}

void glUniform1d(std::int32_t location, double x)
{
	gUniform1d(location, x);
	checkError();
}

void glUniform2d(std::int32_t location, double x, double y)
{
	gUniform2d(location, x, y);
	checkError();
}

void glUniform3d(std::int32_t location, double x, double y, double z)
{
	gUniform3d(location, x, y, z);
	checkError();
}

void glUniform4d(std::int32_t location, double x, double y, double z, double w)
{
	gUniform4d(location, x, y, z, w);
	checkError();
}

void glUniform1dv(std::int32_t location, std::int32_t count, double const * value)
{
	gUniform1dv(location, count, value);
	checkError();
}

void glUniform2dv(std::int32_t location, std::int32_t count, double const * value)
{
	gUniform2dv(location, count, value);
	checkError();
}

void glUniform3dv(std::int32_t location, std::int32_t count, double const * value)
{
	gUniform3dv(location, count, value);
	checkError();
}

void glUniform4dv(std::int32_t location, std::int32_t count, double const * value)
{
	gUniform4dv(location, count, value);
	checkError();
}

void glUniformMatrix2dv(std::int32_t location, std::int32_t count, std::uint8_t transpose, double const * value)
{
	gUniformMatrix2dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix3dv(std::int32_t location, std::int32_t count, std::uint8_t transpose, double const * value)
{
	gUniformMatrix3dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix4dv(std::int32_t location, std::int32_t count, std::uint8_t transpose, double const * value)
{
	gUniformMatrix4dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix2x3dv(std::int32_t location, std::int32_t count, std::uint8_t transpose, double const * value)
{
	gUniformMatrix2x3dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix2x4dv(std::int32_t location, std::int32_t count, std::uint8_t transpose, double const * value)
{
	gUniformMatrix2x4dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix3x2dv(std::int32_t location, std::int32_t count, std::uint8_t transpose, double const * value)
{
	gUniformMatrix3x2dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix3x4dv(std::int32_t location, std::int32_t count, std::uint8_t transpose, double const * value)
{
	gUniformMatrix3x4dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix4x2dv(std::int32_t location, std::int32_t count, std::uint8_t transpose, double const * value)
{
	gUniformMatrix4x2dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix4x3dv(std::int32_t location, std::int32_t count, std::uint8_t transpose, double const * value)
{
	gUniformMatrix4x3dv(location, count, transpose, value);
	checkError();
}

void glGetUniformdv(std::uint32_t program, std::int32_t location, double * params)
{
	gGetUniformdv(program, location, params);
	checkError();
}

std::int32_t glGetSubroutineUniformLocation(std::uint32_t program, std::uint32_t shadertype, char const * name)
{
	auto result = gGetSubroutineUniformLocation(program, shadertype, name);
	checkError();
	return result;
}

std::uint32_t glGetSubroutineIndex(std::uint32_t program, std::uint32_t shadertype, char const * name)
{
	auto result = gGetSubroutineIndex(program, shadertype, name);
	checkError();
	return result;
}

void glGetActiveSubroutineUniformiv(std::uint32_t program, std::uint32_t shadertype, std::uint32_t index, std::uint32_t pname, std::int32_t * values)
{
	gGetActiveSubroutineUniformiv(program, shadertype, index, pname, values);
	checkError();
}

void glGetActiveSubroutineUniformName(std::uint32_t program, std::uint32_t shadertype, std::uint32_t index, std::int32_t bufsize, std::int32_t * length, char * name)
{
	gGetActiveSubroutineUniformName(program, shadertype, index, bufsize, length, name);
	checkError();
}

void glGetActiveSubroutineName(std::uint32_t program, std::uint32_t shadertype, std::uint32_t index, std::int32_t bufsize, std::int32_t * length, char * name)
{
	gGetActiveSubroutineName(program, shadertype, index, bufsize, length, name);
	checkError();
}

void glUniformSubroutinesuiv(std::uint32_t shadertype, std::int32_t count, std::uint32_t const * indices)
{
	gUniformSubroutinesuiv(shadertype, count, indices);
	checkError();
}

void glGetUniformSubroutineuiv(std::uint32_t shadertype, std::int32_t location, std::uint32_t * params)
{
	gGetUniformSubroutineuiv(shadertype, location, params);
	checkError();
}

void glGetProgramStageiv(std::uint32_t program, std::uint32_t shadertype, std::uint32_t pname, std::int32_t * values)
{
	gGetProgramStageiv(program, shadertype, pname, values);
	checkError();
}

void glPatchParameteri(std::uint32_t pname, std::int32_t value)
{
	gPatchParameteri(pname, value);
	checkError();
}

void glPatchParameterfv(std::uint32_t pname, float const * values)
{
	gPatchParameterfv(pname, values);
	checkError();
}

void glBindTransformFeedback(std::uint32_t target, std::uint32_t id)
{
	gBindTransformFeedback(target, id);
	checkError();
}

void glDeleteTransformFeedbacks(std::int32_t n, std::uint32_t const * ids)
{
	gDeleteTransformFeedbacks(n, ids);
	checkError();
}

void glGenTransformFeedbacks(std::int32_t n, std::uint32_t * ids)
{
	gGenTransformFeedbacks(n, ids);
	checkError();
}

std::uint8_t glIsTransformFeedback(std::uint32_t id)
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

void glDrawTransformFeedback(std::uint32_t mode, std::uint32_t id)
{
	gDrawTransformFeedback(mode, id);
	checkError();
}

void glDrawTransformFeedbackStream(std::uint32_t mode, std::uint32_t id, std::uint32_t stream)
{
	gDrawTransformFeedbackStream(mode, id, stream);
	checkError();
}

void glBeginQueryIndexed(std::uint32_t target, std::uint32_t index, std::uint32_t id)
{
	gBeginQueryIndexed(target, index, id);
	checkError();
}

void glEndQueryIndexed(std::uint32_t target, std::uint32_t index)
{
	gEndQueryIndexed(target, index);
	checkError();
}

void glGetQueryIndexediv(std::uint32_t target, std::uint32_t index, std::uint32_t pname, std::int32_t * params)
{
	gGetQueryIndexediv(target, index, pname, params);
	checkError();
}

void glReleaseShaderCompiler(void)
{
	gReleaseShaderCompiler();
	checkError();
}

void glShaderBinary(std::int32_t count, std::uint32_t const * shaders, std::uint32_t binaryformat, void const * binary, std::int32_t length)
{
	gShaderBinary(count, shaders, binaryformat, binary, length);
	checkError();
}

void glGetShaderPrecisionFormat(std::uint32_t shadertype, std::uint32_t precisiontype, std::int32_t * range, std::int32_t * precision)
{
	gGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
	checkError();
}

void glDepthRangef(float n, float f)
{
	gDepthRangef(n, f);
	checkError();
}

void glClearDepthf(float d)
{
	gClearDepthf(d);
	checkError();
}

void glGetProgramBinary(std::uint32_t program, std::int32_t bufSize, std::int32_t * length, std::uint32_t * binaryFormat, void * binary)
{
	gGetProgramBinary(program, bufSize, length, binaryFormat, binary);
	checkError();
}

void glProgramBinary(std::uint32_t program, std::uint32_t binaryFormat, void const * binary, std::int32_t length)
{
	gProgramBinary(program, binaryFormat, binary, length);
	checkError();
}

void glProgramParameteri(std::uint32_t program, std::uint32_t pname, std::int32_t value)
{
	gProgramParameteri(program, pname, value);
	checkError();
}

void glUseProgramStages(std::uint32_t pipeline, std::uint32_t stages, std::uint32_t program)
{
	gUseProgramStages(pipeline, stages, program);
	checkError();
}

void glActiveShaderProgram(std::uint32_t pipeline, std::uint32_t program)
{
	gActiveShaderProgram(pipeline, program);
	checkError();
}

std::uint32_t glCreateShaderProgramv(std::uint32_t type, std::int32_t count, char const * * strings)
{
	auto result = gCreateShaderProgramv(type, count, strings);
	checkError();
	return result;
}

void glBindProgramPipeline(std::uint32_t pipeline)
{
	gBindProgramPipeline(pipeline);
	checkError();
}

void glDeleteProgramPipelines(std::int32_t n, std::uint32_t const * pipelines)
{
	gDeleteProgramPipelines(n, pipelines);
	checkError();
}

void glGenProgramPipelines(std::int32_t n, std::uint32_t * pipelines)
{
	gGenProgramPipelines(n, pipelines);
	checkError();
}

std::uint8_t glIsProgramPipeline(std::uint32_t pipeline)
{
	auto result = gIsProgramPipeline(pipeline);
	checkError();
	return result;
}

void glGetProgramPipelineiv(std::uint32_t pipeline, std::uint32_t pname, std::int32_t * params)
{
	gGetProgramPipelineiv(pipeline, pname, params);
	checkError();
}

void glProgramUniform1i(std::uint32_t program, std::int32_t location, std::int32_t v0)
{
	gProgramUniform1i(program, location, v0);
	checkError();
}

void glProgramUniform1iv(std::uint32_t program, std::int32_t location, std::int32_t count, std::int32_t const * value)
{
	gProgramUniform1iv(program, location, count, value);
	checkError();
}

void glProgramUniform1f(std::uint32_t program, std::int32_t location, float v0)
{
	gProgramUniform1f(program, location, v0);
	checkError();
}

void glProgramUniform1fv(std::uint32_t program, std::int32_t location, std::int32_t count, float const * value)
{
	gProgramUniform1fv(program, location, count, value);
	checkError();
}

void glProgramUniform1d(std::uint32_t program, std::int32_t location, double v0)
{
	gProgramUniform1d(program, location, v0);
	checkError();
}

void glProgramUniform1dv(std::uint32_t program, std::int32_t location, std::int32_t count, double const * value)
{
	gProgramUniform1dv(program, location, count, value);
	checkError();
}

void glProgramUniform1ui(std::uint32_t program, std::int32_t location, std::uint32_t v0)
{
	gProgramUniform1ui(program, location, v0);
	checkError();
}

void glProgramUniform1uiv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint32_t const * value)
{
	gProgramUniform1uiv(program, location, count, value);
	checkError();
}

void glProgramUniform2i(std::uint32_t program, std::int32_t location, std::int32_t v0, std::int32_t v1)
{
	gProgramUniform2i(program, location, v0, v1);
	checkError();
}

void glProgramUniform2iv(std::uint32_t program, std::int32_t location, std::int32_t count, std::int32_t const * value)
{
	gProgramUniform2iv(program, location, count, value);
	checkError();
}

void glProgramUniform2f(std::uint32_t program, std::int32_t location, float v0, float v1)
{
	gProgramUniform2f(program, location, v0, v1);
	checkError();
}

void glProgramUniform2fv(std::uint32_t program, std::int32_t location, std::int32_t count, float const * value)
{
	gProgramUniform2fv(program, location, count, value);
	checkError();
}

void glProgramUniform2d(std::uint32_t program, std::int32_t location, double v0, double v1)
{
	gProgramUniform2d(program, location, v0, v1);
	checkError();
}

void glProgramUniform2dv(std::uint32_t program, std::int32_t location, std::int32_t count, double const * value)
{
	gProgramUniform2dv(program, location, count, value);
	checkError();
}

void glProgramUniform2ui(std::uint32_t program, std::int32_t location, std::uint32_t v0, std::uint32_t v1)
{
	gProgramUniform2ui(program, location, v0, v1);
	checkError();
}

void glProgramUniform2uiv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint32_t const * value)
{
	gProgramUniform2uiv(program, location, count, value);
	checkError();
}

void glProgramUniform3i(std::uint32_t program, std::int32_t location, std::int32_t v0, std::int32_t v1, std::int32_t v2)
{
	gProgramUniform3i(program, location, v0, v1, v2);
	checkError();
}

void glProgramUniform3iv(std::uint32_t program, std::int32_t location, std::int32_t count, std::int32_t const * value)
{
	gProgramUniform3iv(program, location, count, value);
	checkError();
}

void glProgramUniform3f(std::uint32_t program, std::int32_t location, float v0, float v1, float v2)
{
	gProgramUniform3f(program, location, v0, v1, v2);
	checkError();
}

void glProgramUniform3fv(std::uint32_t program, std::int32_t location, std::int32_t count, float const * value)
{
	gProgramUniform3fv(program, location, count, value);
	checkError();
}

void glProgramUniform3d(std::uint32_t program, std::int32_t location, double v0, double v1, double v2)
{
	gProgramUniform3d(program, location, v0, v1, v2);
	checkError();
}

void glProgramUniform3dv(std::uint32_t program, std::int32_t location, std::int32_t count, double const * value)
{
	gProgramUniform3dv(program, location, count, value);
	checkError();
}

void glProgramUniform3ui(std::uint32_t program, std::int32_t location, std::uint32_t v0, std::uint32_t v1, std::uint32_t v2)
{
	gProgramUniform3ui(program, location, v0, v1, v2);
	checkError();
}

void glProgramUniform3uiv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint32_t const * value)
{
	gProgramUniform3uiv(program, location, count, value);
	checkError();
}

void glProgramUniform4i(std::uint32_t program, std::int32_t location, std::int32_t v0, std::int32_t v1, std::int32_t v2, std::int32_t v3)
{
	gProgramUniform4i(program, location, v0, v1, v2, v3);
	checkError();
}

void glProgramUniform4iv(std::uint32_t program, std::int32_t location, std::int32_t count, std::int32_t const * value)
{
	gProgramUniform4iv(program, location, count, value);
	checkError();
}

void glProgramUniform4f(std::uint32_t program, std::int32_t location, float v0, float v1, float v2, float v3)
{
	gProgramUniform4f(program, location, v0, v1, v2, v3);
	checkError();
}

void glProgramUniform4fv(std::uint32_t program, std::int32_t location, std::int32_t count, float const * value)
{
	gProgramUniform4fv(program, location, count, value);
	checkError();
}

void glProgramUniform4d(std::uint32_t program, std::int32_t location, double v0, double v1, double v2, double v3)
{
	gProgramUniform4d(program, location, v0, v1, v2, v3);
	checkError();
}

void glProgramUniform4dv(std::uint32_t program, std::int32_t location, std::int32_t count, double const * value)
{
	gProgramUniform4dv(program, location, count, value);
	checkError();
}

void glProgramUniform4ui(std::uint32_t program, std::int32_t location, std::uint32_t v0, std::uint32_t v1, std::uint32_t v2, std::uint32_t v3)
{
	gProgramUniform4ui(program, location, v0, v1, v2, v3);
	checkError();
}

void glProgramUniform4uiv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint32_t const * value)
{
	gProgramUniform4uiv(program, location, count, value);
	checkError();
}

void glProgramUniformMatrix2fv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, float const * value)
{
	gProgramUniformMatrix2fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix3fv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, float const * value)
{
	gProgramUniformMatrix3fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix4fv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, float const * value)
{
	gProgramUniformMatrix4fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix2dv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, double const * value)
{
	gProgramUniformMatrix2dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix3dv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, double const * value)
{
	gProgramUniformMatrix3dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix4dv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, double const * value)
{
	gProgramUniformMatrix4dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix2x3fv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, float const * value)
{
	gProgramUniformMatrix2x3fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix3x2fv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, float const * value)
{
	gProgramUniformMatrix3x2fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix2x4fv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, float const * value)
{
	gProgramUniformMatrix2x4fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix4x2fv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, float const * value)
{
	gProgramUniformMatrix4x2fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix3x4fv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, float const * value)
{
	gProgramUniformMatrix3x4fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix4x3fv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, float const * value)
{
	gProgramUniformMatrix4x3fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix2x3dv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, double const * value)
{
	gProgramUniformMatrix2x3dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix3x2dv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, double const * value)
{
	gProgramUniformMatrix3x2dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix2x4dv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, double const * value)
{
	gProgramUniformMatrix2x4dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix4x2dv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, double const * value)
{
	gProgramUniformMatrix4x2dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix3x4dv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, double const * value)
{
	gProgramUniformMatrix3x4dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix4x3dv(std::uint32_t program, std::int32_t location, std::int32_t count, std::uint8_t transpose, double const * value)
{
	gProgramUniformMatrix4x3dv(program, location, count, transpose, value);
	checkError();
}

void glValidateProgramPipeline(std::uint32_t pipeline)
{
	gValidateProgramPipeline(pipeline);
	checkError();
}

void glGetProgramPipelineInfoLog(std::uint32_t pipeline, std::int32_t bufSize, std::int32_t * length, char * infoLog)
{
	gGetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog);
	checkError();
}

void glVertexAttribL1d(std::uint32_t index, double x)
{
	gVertexAttribL1d(index, x);
	checkError();
}

void glVertexAttribL2d(std::uint32_t index, double x, double y)
{
	gVertexAttribL2d(index, x, y);
	checkError();
}

void glVertexAttribL3d(std::uint32_t index, double x, double y, double z)
{
	gVertexAttribL3d(index, x, y, z);
	checkError();
}

void glVertexAttribL4d(std::uint32_t index, double x, double y, double z, double w)
{
	gVertexAttribL4d(index, x, y, z, w);
	checkError();
}

void glVertexAttribL1dv(std::uint32_t index, double const * v)
{
	gVertexAttribL1dv(index, v);
	checkError();
}

void glVertexAttribL2dv(std::uint32_t index, double const * v)
{
	gVertexAttribL2dv(index, v);
	checkError();
}

void glVertexAttribL3dv(std::uint32_t index, double const * v)
{
	gVertexAttribL3dv(index, v);
	checkError();
}

void glVertexAttribL4dv(std::uint32_t index, double const * v)
{
	gVertexAttribL4dv(index, v);
	checkError();
}

void glVertexAttribLPointer(std::uint32_t index, std::int32_t size, std::uint32_t type, std::int32_t stride, void const * pointer)
{
	gVertexAttribLPointer(index, size, type, stride, pointer);
	checkError();
}

void glGetVertexAttribLdv(std::uint32_t index, std::uint32_t pname, double * params)
{
	gGetVertexAttribLdv(index, pname, params);
	checkError();
}

void glViewportArrayv(std::uint32_t first, std::int32_t count, float const * v)
{
	gViewportArrayv(first, count, v);
	checkError();
}

void glViewportIndexedf(std::uint32_t index, float x, float y, float w, float h)
{
	gViewportIndexedf(index, x, y, w, h);
	checkError();
}

void glViewportIndexedfv(std::uint32_t index, float const * v)
{
	gViewportIndexedfv(index, v);
	checkError();
}

void glScissorArrayv(std::uint32_t first, std::int32_t count, std::int32_t const * v)
{
	gScissorArrayv(first, count, v);
	checkError();
}

void glScissorIndexed(std::uint32_t index, std::int32_t left, std::int32_t bottom, std::int32_t width, std::int32_t height)
{
	gScissorIndexed(index, left, bottom, width, height);
	checkError();
}

void glScissorIndexedv(std::uint32_t index, std::int32_t const * v)
{
	gScissorIndexedv(index, v);
	checkError();
}

void glDepthRangeArrayv(std::uint32_t first, std::int32_t count, double const * v)
{
	gDepthRangeArrayv(first, count, v);
	checkError();
}

void glDepthRangeIndexed(std::uint32_t index, double n, double f)
{
	gDepthRangeIndexed(index, n, f);
	checkError();
}

void glGetFloati_v(std::uint32_t target, std::uint32_t index, float * data)
{
	gGetFloati_v(target, index, data);
	checkError();
}

void glGetDoublei_v(std::uint32_t target, std::uint32_t index, double * data)
{
	gGetDoublei_v(target, index, data);
	checkError();
}

GLsync glCreateSyncFromCLeventARB(struct _cl_context * context, struct _cl_event * event, std::uint32_t flags)
{
	auto result = gCreateSyncFromCLeventARB(context, event, flags);
	checkError();
	return result;
}

void glDebugMessageControlARB(std::uint32_t source, std::uint32_t type, std::uint32_t severity, std::int32_t count, std::uint32_t const * ids, std::uint8_t enabled)
{
	gDebugMessageControlARB(source, type, severity, count, ids, enabled);
	checkError();
}

void glDebugMessageInsertARB(std::uint32_t source, std::uint32_t type, std::uint32_t id, std::uint32_t severity, std::int32_t length, char const * buf)
{
	gDebugMessageInsertARB(source, type, id, severity, length, buf);
	checkError();
}

void glDebugMessageCallbackARB(GLDEBUGPROCARB callback, void const * userParam)
{
	gDebugMessageCallbackARB(callback, userParam);
	checkError();
}

std::uint32_t glGetDebugMessageLogARB(std::uint32_t count, std::int32_t bufsize, std::uint32_t * sources, std::uint32_t * types, std::uint32_t * ids, std::uint32_t * severities, std::int32_t * lengths, char * messageLog)
{
	auto result = gGetDebugMessageLogARB(count, bufsize, sources, types, ids, severities, lengths, messageLog);
	checkError();
	return result;
}

std::uint32_t glGetGraphicsResetStatusARB(void)
{
	auto result = gGetGraphicsResetStatusARB();
	checkError();
	return result;
}

void glGetnMapdvARB(std::uint32_t target, std::uint32_t query, std::int32_t bufSize, double * v)
{
	gGetnMapdvARB(target, query, bufSize, v);
	checkError();
}

void glGetnMapfvARB(std::uint32_t target, std::uint32_t query, std::int32_t bufSize, float * v)
{
	gGetnMapfvARB(target, query, bufSize, v);
	checkError();
}

void glGetnMapivARB(std::uint32_t target, std::uint32_t query, std::int32_t bufSize, std::int32_t * v)
{
	gGetnMapivARB(target, query, bufSize, v);
	checkError();
}

void glGetnPixelMapfvARB(std::uint32_t map, std::int32_t bufSize, float * values)
{
	gGetnPixelMapfvARB(map, bufSize, values);
	checkError();
}

void glGetnPixelMapuivARB(std::uint32_t map, std::int32_t bufSize, std::uint32_t * values)
{
	gGetnPixelMapuivARB(map, bufSize, values);
	checkError();
}

void glGetnPixelMapusvARB(std::uint32_t map, std::int32_t bufSize, std::uint16_t * values)
{
	gGetnPixelMapusvARB(map, bufSize, values);
	checkError();
}

void glGetnPolygonStippleARB(std::int32_t bufSize, std::uint8_t * pattern)
{
	gGetnPolygonStippleARB(bufSize, pattern);
	checkError();
}

void glGetnColorTableARB(std::uint32_t target, std::uint32_t format, std::uint32_t type, std::int32_t bufSize, void * table)
{
	gGetnColorTableARB(target, format, type, bufSize, table);
	checkError();
}

void glGetnConvolutionFilterARB(std::uint32_t target, std::uint32_t format, std::uint32_t type, std::int32_t bufSize, void * image)
{
	gGetnConvolutionFilterARB(target, format, type, bufSize, image);
	checkError();
}

void glGetnSeparableFilterARB(std::uint32_t target, std::uint32_t format, std::uint32_t type, std::int32_t rowBufSize, void * row, std::int32_t columnBufSize, void * column, void * span)
{
	gGetnSeparableFilterARB(target, format, type, rowBufSize, row, columnBufSize, column, span);
	checkError();
}

void glGetnHistogramARB(std::uint32_t target, std::uint8_t reset, std::uint32_t format, std::uint32_t type, std::int32_t bufSize, void * values)
{
	gGetnHistogramARB(target, reset, format, type, bufSize, values);
	checkError();
}

void glGetnMinmaxARB(std::uint32_t target, std::uint8_t reset, std::uint32_t format, std::uint32_t type, std::int32_t bufSize, void * values)
{
	gGetnMinmaxARB(target, reset, format, type, bufSize, values);
	checkError();
}

void glGetnTexImageARB(std::uint32_t target, std::int32_t level, std::uint32_t format, std::uint32_t type, std::int32_t bufSize, void * img)
{
	gGetnTexImageARB(target, level, format, type, bufSize, img);
	checkError();
}

void glReadnPixelsARB(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, std::uint32_t format, std::uint32_t type, std::int32_t bufSize, void * data)
{
	gReadnPixelsARB(x, y, width, height, format, type, bufSize, data);
	checkError();
}

void glGetnCompressedTexImageARB(std::uint32_t target, std::int32_t lod, std::int32_t bufSize, void * img)
{
	gGetnCompressedTexImageARB(target, lod, bufSize, img);
	checkError();
}

void glGetnUniformfvARB(std::uint32_t program, std::int32_t location, std::int32_t bufSize, float * params)
{
	gGetnUniformfvARB(program, location, bufSize, params);
	checkError();
}

void glGetnUniformivARB(std::uint32_t program, std::int32_t location, std::int32_t bufSize, std::int32_t * params)
{
	gGetnUniformivARB(program, location, bufSize, params);
	checkError();
}

void glGetnUniformuivARB(std::uint32_t program, std::int32_t location, std::int32_t bufSize, std::uint32_t * params)
{
	gGetnUniformuivARB(program, location, bufSize, params);
	checkError();
}

void glGetnUniformdvARB(std::uint32_t program, std::int32_t location, std::int32_t bufSize, double * params)
{
	gGetnUniformdvARB(program, location, bufSize, params);
	checkError();
}

void glDrawArraysInstancedBaseInstance(std::uint32_t mode, std::int32_t first, std::int32_t count, std::int32_t primcount, std::uint32_t baseinstance)
{
	gDrawArraysInstancedBaseInstance(mode, first, count, primcount, baseinstance);
	checkError();
}

void glDrawElementsInstancedBaseInstance(std::uint32_t mode, std::int32_t count, std::uint32_t type, const void *indices, std::int32_t primcount, std::uint32_t baseinstance)
{
	gDrawElementsInstancedBaseInstance(mode, count, type,  indices, primcount, baseinstance);
	checkError();
}

void glDrawElementsInstancedBaseVertexBaseInstance(std::uint32_t mode, std::int32_t count, std::uint32_t type, const void *indices, std::int32_t primcount, std::int32_t basevertex, std::uint32_t baseinstance)
{
	gDrawElementsInstancedBaseVertexBaseInstance(mode, count, type,  indices, primcount, basevertex, baseinstance);
	checkError();
}

void glDrawTransformFeedbackInstanced(std::uint32_t mode, std::uint32_t id, std::int32_t primcount)
{
	gDrawTransformFeedbackInstanced(mode, id, primcount);
	checkError();
}

void glDrawTransformFeedbackStreamInstanced(std::uint32_t mode, std::uint32_t id, std::uint32_t stream, std::int32_t primcount)
{
	gDrawTransformFeedbackStreamInstanced(mode, id, stream, primcount);
	checkError();
}

void glGetInternalformativ(std::uint32_t target, std::uint32_t internalformat, std::uint32_t pname, std::int32_t bufSize, std::int32_t * params)
{
	gGetInternalformativ(target, internalformat, pname, bufSize, params);
	checkError();
}

void glGetActiveAtomicCounterBufferiv(std::uint32_t program, std::uint32_t bufferIndex, std::uint32_t pname, std::int32_t * params)
{
	gGetActiveAtomicCounterBufferiv(program, bufferIndex, pname, params);
	checkError();
}

void glBindImageTexture(std::uint32_t unit, std::uint32_t texture, std::int32_t level, std::uint8_t layered, std::int32_t layer, std::uint32_t access, std::uint32_t format)
{
	gBindImageTexture(unit, texture, level, layered, layer, access, format);
	checkError();
}

void glMemoryBarrier(std::uint32_t barriers)
{
	gMemoryBarrier(barriers);
	checkError();
}

void glTexStorage1D(std::uint32_t target, std::int32_t levels, std::uint32_t internalformat, std::int32_t width)
{
	gTexStorage1D(target, levels, internalformat, width);
	checkError();
}

void glTexStorage2D(std::uint32_t target, std::int32_t levels, std::uint32_t internalformat, std::int32_t width, std::int32_t height)
{
	gTexStorage2D(target, levels, internalformat, width, height);
	checkError();
}

void glTexStorage3D(std::uint32_t target, std::int32_t levels, std::uint32_t internalformat, std::int32_t width, std::int32_t height, std::int32_t depth)
{
	gTexStorage3D(target, levels, internalformat, width, height, depth);
	checkError();
}

void glTextureStorage1DEXT(std::uint32_t texture, std::uint32_t target, std::int32_t levels, std::uint32_t internalformat, std::int32_t width)
{
	gTextureStorage1DEXT(texture, target, levels, internalformat, width);
	checkError();
}

void glTextureStorage2DEXT(std::uint32_t texture, std::uint32_t target, std::int32_t levels, std::uint32_t internalformat, std::int32_t width, std::int32_t height)
{
	gTextureStorage2DEXT(texture, target, levels, internalformat, width, height);
	checkError();
}

void glTextureStorage3DEXT(std::uint32_t texture, std::uint32_t target, std::int32_t levels, std::uint32_t internalformat, std::int32_t width, std::int32_t height, std::int32_t depth)
{
	gTextureStorage3DEXT(texture, target, levels, internalformat, width, height, depth);
	checkError();
}

}
}
}
