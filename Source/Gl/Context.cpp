#include "Context.hpp"

#include "Platform/SymbolLoader.hpp"

#include <stdexcept>

namespace {

struct GlProcsT
{
	decltype(&glCullFace) CullFace;
	decltype(&glFrontFace) FrontFace;
	decltype(&glHint) Hint;
	decltype(&glLineWidth) LineWidth;
	decltype(&glPointSize) PointSize;
	decltype(&glPolygonMode) PolygonMode;
	decltype(&glScissor) Scissor;
	decltype(&glTexParameterf) TexParameterf;
	decltype(&glTexParameterfv) TexParameterfv;
	decltype(&glTexParameteri) TexParameteri;
	decltype(&glTexParameteriv) TexParameteriv;
	decltype(&glTexImage1D) TexImage1D;
	decltype(&glTexImage2D) TexImage2D;
	decltype(&glDrawBuffer) DrawBuffer;
	decltype(&glClear) Clear;
	decltype(&glClearColor) ClearColor;
	decltype(&glClearStencil) ClearStencil;
	decltype(&glClearDepth) ClearDepth;
	decltype(&glStencilMask) StencilMask;
	decltype(&glColorMask) ColorMask;
	decltype(&glDepthMask) DepthMask;
	decltype(&glDisable) Disable;
	decltype(&glEnable) Enable;
	decltype(&glFinish) Finish;
	decltype(&glFlush) Flush;
	decltype(&glBlendFunc) BlendFunc;
	decltype(&glLogicOp) LogicOp;
	decltype(&glStencilFunc) StencilFunc;
	decltype(&glStencilOp) StencilOp;
	decltype(&glDepthFunc) DepthFunc;
	decltype(&glPixelStoref) PixelStoref;
	decltype(&glPixelStorei) PixelStorei;
	decltype(&glReadBuffer) ReadBuffer;
	decltype(&glReadPixels) ReadPixels;
	decltype(&glGetBooleanv) GetBooleanv;
	decltype(&glGetDoublev) GetDoublev;
	decltype(&glGetError) GetError;
	decltype(&glGetFloatv) GetFloatv;
	decltype(&glGetIntegerv) GetIntegerv;
	decltype(&glGetString) GetString;
	decltype(&glGetTexImage) GetTexImage;
	decltype(&glGetTexParameterfv) GetTexParameterfv;
	decltype(&glGetTexParameteriv) GetTexParameteriv;
	decltype(&glGetTexLevelParameterfv) GetTexLevelParameterfv;
	decltype(&glGetTexLevelParameteriv) GetTexLevelParameteriv;
	decltype(&glIsEnabled) IsEnabled;
	decltype(&glDepthRange) DepthRange;
	decltype(&glViewport) Viewport;
	decltype(&glDrawArrays) DrawArrays;
	decltype(&glDrawElements) DrawElements;
	decltype(&glGetPointerv) GetPointerv;
	decltype(&glPolygonOffset) PolygonOffset;
	decltype(&glCopyTexImage1D) CopyTexImage1D;
	decltype(&glCopyTexImage2D) CopyTexImage2D;
	decltype(&glCopyTexSubImage1D) CopyTexSubImage1D;
	decltype(&glCopyTexSubImage2D) CopyTexSubImage2D;
	decltype(&glTexSubImage1D) TexSubImage1D;
	decltype(&glTexSubImage2D) TexSubImage2D;
	decltype(&glBindTexture) BindTexture;
	decltype(&glDeleteTextures) DeleteTextures;
	decltype(&glGenTextures) GenTextures;
	decltype(&glIsTexture) IsTexture;
	decltype(&glBlendColor) BlendColor;
	decltype(&glBlendEquation) BlendEquation;
	decltype(&glDrawRangeElements) DrawRangeElements;
	decltype(&glTexImage3D) TexImage3D;
	decltype(&glTexSubImage3D) TexSubImage3D;
	decltype(&glCopyTexSubImage3D) CopyTexSubImage3D;
	decltype(&glActiveTexture) ActiveTexture;
	decltype(&glSampleCoverage) SampleCoverage;
	decltype(&glCompressedTexImage3D) CompressedTexImage3D;
	decltype(&glCompressedTexImage2D) CompressedTexImage2D;
	decltype(&glCompressedTexImage1D) CompressedTexImage1D;
	decltype(&glCompressedTexSubImage3D) CompressedTexSubImage3D;
	decltype(&glCompressedTexSubImage2D) CompressedTexSubImage2D;
	decltype(&glCompressedTexSubImage1D) CompressedTexSubImage1D;
	decltype(&glGetCompressedTexImage) GetCompressedTexImage;
	decltype(&glBlendFuncSeparate) BlendFuncSeparate;
	decltype(&glMultiDrawArrays) MultiDrawArrays;
	decltype(&glMultiDrawElements) MultiDrawElements;
	decltype(&glPointParameterf) PointParameterf;
	decltype(&glPointParameterfv) PointParameterfv;
	decltype(&glPointParameteri) PointParameteri;
	decltype(&glPointParameteriv) PointParameteriv;
	decltype(&glGenQueries) GenQueries;
	decltype(&glDeleteQueries) DeleteQueries;
	decltype(&glIsQuery) IsQuery;
	decltype(&glBeginQuery) BeginQuery;
	decltype(&glEndQuery) EndQuery;
	decltype(&glGetQueryiv) GetQueryiv;
	decltype(&glGetQueryObjectiv) GetQueryObjectiv;
	decltype(&glGetQueryObjectuiv) GetQueryObjectuiv;
	decltype(&glVertexAttribP1ui) VertexAttribP1ui;
	decltype(&glVertexAttribP1uiv) VertexAttribP1uiv;
	decltype(&glVertexAttribP2ui) VertexAttribP2ui;
	decltype(&glVertexAttribP2uiv) VertexAttribP2uiv;
	decltype(&glVertexAttribP3ui) VertexAttribP3ui;
	decltype(&glVertexAttribP3uiv) VertexAttribP3uiv;
	decltype(&glVertexAttribP4ui) VertexAttribP4ui;
	decltype(&glVertexAttribP4uiv) VertexAttribP4uiv;
	decltype(&glBindBuffer) BindBuffer;
	decltype(&glDeleteBuffers) DeleteBuffers;
	decltype(&glGenBuffers) GenBuffers;
	decltype(&glIsBuffer) IsBuffer;
	decltype(&glBufferData) BufferData;
	decltype(&glBufferSubData) BufferSubData;
	decltype(&glGetBufferSubData) GetBufferSubData;
	decltype(&glMapBuffer) MapBuffer;
	decltype(&glUnmapBuffer) UnmapBuffer;
	decltype(&glGetBufferParameteriv) GetBufferParameteriv;
	decltype(&glGetBufferPointerv) GetBufferPointerv;
	decltype(&glBlendEquationSeparate) BlendEquationSeparate;
	decltype(&glDrawBuffers) DrawBuffers;
	decltype(&glStencilOpSeparate) StencilOpSeparate;
	decltype(&glStencilFuncSeparate) StencilFuncSeparate;
	decltype(&glStencilMaskSeparate) StencilMaskSeparate;
	decltype(&glAttachShader) AttachShader;
	decltype(&glBindAttribLocation) BindAttribLocation;
	decltype(&glCompileShader) CompileShader;
	decltype(&glCreateProgram) CreateProgram;
	decltype(&glCreateShader) CreateShader;
	decltype(&glDeleteProgram) DeleteProgram;
	decltype(&glDeleteShader) DeleteShader;
	decltype(&glDetachShader) DetachShader;
	decltype(&glDisableVertexAttribArray) DisableVertexAttribArray;
	decltype(&glEnableVertexAttribArray) EnableVertexAttribArray;
	decltype(&glGetActiveAttrib) GetActiveAttrib;
	decltype(&glGetActiveUniform) GetActiveUniform;
	decltype(&glGetAttachedShaders) GetAttachedShaders;
	decltype(&glGetAttribLocation) GetAttribLocation;
	decltype(&glGetProgramiv) GetProgramiv;
	decltype(&glGetProgramInfoLog) GetProgramInfoLog;
	decltype(&glGetShaderiv) GetShaderiv;
	decltype(&glGetShaderInfoLog) GetShaderInfoLog;
	decltype(&glGetShaderSource) GetShaderSource;
	decltype(&glGetUniformLocation) GetUniformLocation;
	decltype(&glGetUniformfv) GetUniformfv;
	decltype(&glGetUniformiv) GetUniformiv;
	decltype(&glGetVertexAttribdv) GetVertexAttribdv;
	decltype(&glGetVertexAttribfv) GetVertexAttribfv;
	decltype(&glGetVertexAttribiv) GetVertexAttribiv;
	decltype(&glGetVertexAttribPointerv) GetVertexAttribPointerv;
	decltype(&glIsProgram) IsProgram;
	decltype(&glIsShader) IsShader;
	decltype(&glLinkProgram) LinkProgram;
	decltype(&glShaderSource) ShaderSource;
	decltype(&glUseProgram) UseProgram;
	decltype(&glUniform1f) Uniform1f;
	decltype(&glUniform2f) Uniform2f;
	decltype(&glUniform3f) Uniform3f;
	decltype(&glUniform4f) Uniform4f;
	decltype(&glUniform1i) Uniform1i;
	decltype(&glUniform2i) Uniform2i;
	decltype(&glUniform3i) Uniform3i;
	decltype(&glUniform4i) Uniform4i;
	decltype(&glUniform1fv) Uniform1fv;
	decltype(&glUniform2fv) Uniform2fv;
	decltype(&glUniform3fv) Uniform3fv;
	decltype(&glUniform4fv) Uniform4fv;
	decltype(&glUniform1iv) Uniform1iv;
	decltype(&glUniform2iv) Uniform2iv;
	decltype(&glUniform3iv) Uniform3iv;
	decltype(&glUniform4iv) Uniform4iv;
	decltype(&glUniformMatrix2fv) UniformMatrix2fv;
	decltype(&glUniformMatrix3fv) UniformMatrix3fv;
	decltype(&glUniformMatrix4fv) UniformMatrix4fv;
	decltype(&glValidateProgram) ValidateProgram;
	decltype(&glVertexAttrib1d) VertexAttrib1d;
	decltype(&glVertexAttrib1dv) VertexAttrib1dv;
	decltype(&glVertexAttrib1f) VertexAttrib1f;
	decltype(&glVertexAttrib1fv) VertexAttrib1fv;
	decltype(&glVertexAttrib1s) VertexAttrib1s;
	decltype(&glVertexAttrib1sv) VertexAttrib1sv;
	decltype(&glVertexAttrib2d) VertexAttrib2d;
	decltype(&glVertexAttrib2dv) VertexAttrib2dv;
	decltype(&glVertexAttrib2f) VertexAttrib2f;
	decltype(&glVertexAttrib2fv) VertexAttrib2fv;
	decltype(&glVertexAttrib2s) VertexAttrib2s;
	decltype(&glVertexAttrib2sv) VertexAttrib2sv;
	decltype(&glVertexAttrib3d) VertexAttrib3d;
	decltype(&glVertexAttrib3dv) VertexAttrib3dv;
	decltype(&glVertexAttrib3f) VertexAttrib3f;
	decltype(&glVertexAttrib3fv) VertexAttrib3fv;
	decltype(&glVertexAttrib3s) VertexAttrib3s;
	decltype(&glVertexAttrib3sv) VertexAttrib3sv;
	decltype(&glVertexAttrib4Nbv) VertexAttrib4Nbv;
	decltype(&glVertexAttrib4Niv) VertexAttrib4Niv;
	decltype(&glVertexAttrib4Nsv) VertexAttrib4Nsv;
	decltype(&glVertexAttrib4Nub) VertexAttrib4Nub;
	decltype(&glVertexAttrib4Nubv) VertexAttrib4Nubv;
	decltype(&glVertexAttrib4Nuiv) VertexAttrib4Nuiv;
	decltype(&glVertexAttrib4Nusv) VertexAttrib4Nusv;
	decltype(&glVertexAttrib4bv) VertexAttrib4bv;
	decltype(&glVertexAttrib4d) VertexAttrib4d;
	decltype(&glVertexAttrib4dv) VertexAttrib4dv;
	decltype(&glVertexAttrib4f) VertexAttrib4f;
	decltype(&glVertexAttrib4fv) VertexAttrib4fv;
	decltype(&glVertexAttrib4iv) VertexAttrib4iv;
	decltype(&glVertexAttrib4s) VertexAttrib4s;
	decltype(&glVertexAttrib4sv) VertexAttrib4sv;
	decltype(&glVertexAttrib4ubv) VertexAttrib4ubv;
	decltype(&glVertexAttrib4uiv) VertexAttrib4uiv;
	decltype(&glVertexAttrib4usv) VertexAttrib4usv;
	decltype(&glVertexAttribPointer) VertexAttribPointer;
	decltype(&glUniformMatrix2x3fv) UniformMatrix2x3fv;
	decltype(&glUniformMatrix3x2fv) UniformMatrix3x2fv;
	decltype(&glUniformMatrix2x4fv) UniformMatrix2x4fv;
	decltype(&glUniformMatrix4x2fv) UniformMatrix4x2fv;
	decltype(&glUniformMatrix3x4fv) UniformMatrix3x4fv;
	decltype(&glUniformMatrix4x3fv) UniformMatrix4x3fv;
	decltype(&glColorMaski) ColorMaski;
	decltype(&glGetBooleani_v) GetBooleani_v;
	decltype(&glGetIntegeri_v) GetIntegeri_v;
	decltype(&glEnablei) Enablei;
	decltype(&glDisablei) Disablei;
	decltype(&glIsEnabledi) IsEnabledi;
	decltype(&glBeginTransformFeedback) BeginTransformFeedback;
	decltype(&glEndTransformFeedback) EndTransformFeedback;
	decltype(&glBindBufferRange) BindBufferRange;
	decltype(&glBindBufferBase) BindBufferBase;
	decltype(&glTransformFeedbackVaryings) TransformFeedbackVaryings;
	decltype(&glGetTransformFeedbackVarying) GetTransformFeedbackVarying;
	decltype(&glClampColor) ClampColor;
	decltype(&glBeginConditionalRender) BeginConditionalRender;
	decltype(&glEndConditionalRender) EndConditionalRender;
	decltype(&glVertexAttribIPointer) VertexAttribIPointer;
	decltype(&glGetVertexAttribIiv) GetVertexAttribIiv;
	decltype(&glGetVertexAttribIuiv) GetVertexAttribIuiv;
	decltype(&glVertexAttribI1i) VertexAttribI1i;
	decltype(&glVertexAttribI2i) VertexAttribI2i;
	decltype(&glVertexAttribI3i) VertexAttribI3i;
	decltype(&glVertexAttribI4i) VertexAttribI4i;
	decltype(&glVertexAttribI1ui) VertexAttribI1ui;
	decltype(&glVertexAttribI2ui) VertexAttribI2ui;
	decltype(&glVertexAttribI3ui) VertexAttribI3ui;
	decltype(&glVertexAttribI4ui) VertexAttribI4ui;
	decltype(&glVertexAttribI1iv) VertexAttribI1iv;
	decltype(&glVertexAttribI2iv) VertexAttribI2iv;
	decltype(&glVertexAttribI3iv) VertexAttribI3iv;
	decltype(&glVertexAttribI4iv) VertexAttribI4iv;
	decltype(&glVertexAttribI1uiv) VertexAttribI1uiv;
	decltype(&glVertexAttribI2uiv) VertexAttribI2uiv;
	decltype(&glVertexAttribI3uiv) VertexAttribI3uiv;
	decltype(&glVertexAttribI4uiv) VertexAttribI4uiv;
	decltype(&glVertexAttribI4bv) VertexAttribI4bv;
	decltype(&glVertexAttribI4sv) VertexAttribI4sv;
	decltype(&glVertexAttribI4ubv) VertexAttribI4ubv;
	decltype(&glVertexAttribI4usv) VertexAttribI4usv;
	decltype(&glGetUniformuiv) GetUniformuiv;
	decltype(&glBindFragDataLocation) BindFragDataLocation;
	decltype(&glGetFragDataLocation) GetFragDataLocation;
	decltype(&glUniform1ui) Uniform1ui;
	decltype(&glUniform2ui) Uniform2ui;
	decltype(&glUniform3ui) Uniform3ui;
	decltype(&glUniform4ui) Uniform4ui;
	decltype(&glUniform1uiv) Uniform1uiv;
	decltype(&glUniform2uiv) Uniform2uiv;
	decltype(&glUniform3uiv) Uniform3uiv;
	decltype(&glUniform4uiv) Uniform4uiv;
	decltype(&glTexParameterIiv) TexParameterIiv;
	decltype(&glTexParameterIuiv) TexParameterIuiv;
	decltype(&glGetTexParameterIiv) GetTexParameterIiv;
	decltype(&glGetTexParameterIuiv) GetTexParameterIuiv;
	decltype(&glClearBufferiv) ClearBufferiv;
	decltype(&glClearBufferuiv) ClearBufferuiv;
	decltype(&glClearBufferfv) ClearBufferfv;
	decltype(&glClearBufferfi) ClearBufferfi;
	decltype(&glGetStringi) GetStringi;
	decltype(&glDrawArraysInstanced) DrawArraysInstanced;
	decltype(&glDrawElementsInstanced) DrawElementsInstanced;
	decltype(&glTexBuffer) TexBuffer;
	decltype(&glPrimitiveRestartIndex) PrimitiveRestartIndex;
	decltype(&glGetInteger64i_v) GetInteger64i_v;
	decltype(&glGetBufferParameteri64v) GetBufferParameteri64v;
	decltype(&glFramebufferTexture) FramebufferTexture;
	decltype(&glVertexAttribDivisor) VertexAttribDivisor;
	decltype(&glMinSampleShading) MinSampleShading;
	decltype(&glBlendEquationi) BlendEquationi;
	decltype(&glBlendEquationSeparatei) BlendEquationSeparatei;
	decltype(&glBlendFunci) BlendFunci;
	decltype(&glBlendFuncSeparatei) BlendFuncSeparatei;
	decltype(&glIsRenderbuffer) IsRenderbuffer;
	decltype(&glBindRenderbuffer) BindRenderbuffer;
	decltype(&glDeleteRenderbuffers) DeleteRenderbuffers;
	decltype(&glGenRenderbuffers) GenRenderbuffers;
	decltype(&glRenderbufferStorage) RenderbufferStorage;
	decltype(&glGetRenderbufferParameteriv) GetRenderbufferParameteriv;
	decltype(&glIsFramebuffer) IsFramebuffer;
	decltype(&glBindFramebuffer) BindFramebuffer;
	decltype(&glDeleteFramebuffers) DeleteFramebuffers;
	decltype(&glGenFramebuffers) GenFramebuffers;
	decltype(&glCheckFramebufferStatus) CheckFramebufferStatus;
	decltype(&glFramebufferTexture1D) FramebufferTexture1D;
	decltype(&glFramebufferTexture2D) FramebufferTexture2D;
	decltype(&glFramebufferTexture3D) FramebufferTexture3D;
	decltype(&glFramebufferRenderbuffer) FramebufferRenderbuffer;
	decltype(&glGetFramebufferAttachmentParameteriv) GetFramebufferAttachmentParameteriv;
	decltype(&glGenerateMipmap) GenerateMipmap;
	decltype(&glBlitFramebuffer) BlitFramebuffer;
	decltype(&glRenderbufferStorageMultisample) RenderbufferStorageMultisample;
	decltype(&glFramebufferTextureLayer) FramebufferTextureLayer;
	decltype(&glMapBufferRange) MapBufferRange;
	decltype(&glFlushMappedBufferRange) FlushMappedBufferRange;
	decltype(&glBindVertexArray) BindVertexArray;
	decltype(&glDeleteVertexArrays) DeleteVertexArrays;
	decltype(&glGenVertexArrays) GenVertexArrays;
	decltype(&glIsVertexArray) IsVertexArray;
	decltype(&glGetUniformIndices) GetUniformIndices;
	decltype(&glGetActiveUniformsiv) GetActiveUniformsiv;
	decltype(&glGetActiveUniformName) GetActiveUniformName;
	decltype(&glGetUniformBlockIndex) GetUniformBlockIndex;
	decltype(&glGetActiveUniformBlockiv) GetActiveUniformBlockiv;
	decltype(&glGetActiveUniformBlockName) GetActiveUniformBlockName;
	decltype(&glUniformBlockBinding) UniformBlockBinding;
	decltype(&glCopyBufferSubData) CopyBufferSubData;
	decltype(&glDrawElementsBaseVertex) DrawElementsBaseVertex;
	decltype(&glDrawRangeElementsBaseVertex) DrawRangeElementsBaseVertex;
	decltype(&glDrawElementsInstancedBaseVertex) DrawElementsInstancedBaseVertex;
	decltype(&glMultiDrawElementsBaseVertex) MultiDrawElementsBaseVertex;
	decltype(&glProvokingVertex) ProvokingVertex;
	decltype(&glFenceSync) FenceSync;
	decltype(&glIsSync) IsSync;
	decltype(&glDeleteSync) DeleteSync;
	decltype(&glClientWaitSync) ClientWaitSync;
	decltype(&glWaitSync) WaitSync;
	decltype(&glGetInteger64v) GetInteger64v;
	decltype(&glGetSynciv) GetSynciv;
	decltype(&glTexImage2DMultisample) TexImage2DMultisample;
	decltype(&glTexImage3DMultisample) TexImage3DMultisample;
	decltype(&glGetMultisamplefv) GetMultisamplefv;
	decltype(&glSampleMaski) SampleMaski;
	decltype(&glBlendEquationiARB) BlendEquationiARB;
	decltype(&glBlendEquationSeparateiARB) BlendEquationSeparateiARB;
	decltype(&glBlendFunciARB) BlendFunciARB;
	decltype(&glBlendFuncSeparateiARB) BlendFuncSeparateiARB;
	decltype(&glMinSampleShadingARB) MinSampleShadingARB;
	decltype(&glNamedStringARB) NamedStringARB;
	decltype(&glDeleteNamedStringARB) DeleteNamedStringARB;
	decltype(&glCompileShaderIncludeARB) CompileShaderIncludeARB;
	decltype(&glIsNamedStringARB) IsNamedStringARB;
	decltype(&glGetNamedStringARB) GetNamedStringARB;
	decltype(&glGetNamedStringivARB) GetNamedStringivARB;
	decltype(&glBindFragDataLocationIndexed) BindFragDataLocationIndexed;
	decltype(&glGetFragDataIndex) GetFragDataIndex;
	decltype(&glGenSamplers) GenSamplers;
	decltype(&glDeleteSamplers) DeleteSamplers;
	decltype(&glIsSampler) IsSampler;
	decltype(&glBindSampler) BindSampler;
	decltype(&glSamplerParameteri) SamplerParameteri;
	decltype(&glSamplerParameteriv) SamplerParameteriv;
	decltype(&glSamplerParameterf) SamplerParameterf;
	decltype(&glSamplerParameterfv) SamplerParameterfv;
	decltype(&glSamplerParameterIiv) SamplerParameterIiv;
	decltype(&glSamplerParameterIuiv) SamplerParameterIuiv;
	decltype(&glGetSamplerParameteriv) GetSamplerParameteriv;
	decltype(&glGetSamplerParameterIiv) GetSamplerParameterIiv;
	decltype(&glGetSamplerParameterfv) GetSamplerParameterfv;
	decltype(&glGetSamplerParameterIuiv) GetSamplerParameterIuiv;
	decltype(&glQueryCounter) QueryCounter;
	decltype(&glGetQueryObjecti64v) GetQueryObjecti64v;
	decltype(&glGetQueryObjectui64v) GetQueryObjectui64v;
	decltype(&glDrawArraysIndirect) DrawArraysIndirect;
	decltype(&glDrawElementsIndirect) DrawElementsIndirect;
	decltype(&glUniform1d) Uniform1d;
	decltype(&glUniform2d) Uniform2d;
	decltype(&glUniform3d) Uniform3d;
	decltype(&glUniform4d) Uniform4d;
	decltype(&glUniform1dv) Uniform1dv;
	decltype(&glUniform2dv) Uniform2dv;
	decltype(&glUniform3dv) Uniform3dv;
	decltype(&glUniform4dv) Uniform4dv;
	decltype(&glUniformMatrix2dv) UniformMatrix2dv;
	decltype(&glUniformMatrix3dv) UniformMatrix3dv;
	decltype(&glUniformMatrix4dv) UniformMatrix4dv;
	decltype(&glUniformMatrix2x3dv) UniformMatrix2x3dv;
	decltype(&glUniformMatrix2x4dv) UniformMatrix2x4dv;
	decltype(&glUniformMatrix3x2dv) UniformMatrix3x2dv;
	decltype(&glUniformMatrix3x4dv) UniformMatrix3x4dv;
	decltype(&glUniformMatrix4x2dv) UniformMatrix4x2dv;
	decltype(&glUniformMatrix4x3dv) UniformMatrix4x3dv;
	decltype(&glGetUniformdv) GetUniformdv;
	decltype(&glGetSubroutineUniformLocation) GetSubroutineUniformLocation;
	decltype(&glGetSubroutineIndex) GetSubroutineIndex;
	decltype(&glGetActiveSubroutineUniformiv) GetActiveSubroutineUniformiv;
	decltype(&glGetActiveSubroutineUniformName) GetActiveSubroutineUniformName;
	decltype(&glGetActiveSubroutineName) GetActiveSubroutineName;
	decltype(&glUniformSubroutinesuiv) UniformSubroutinesuiv;
	decltype(&glGetUniformSubroutineuiv) GetUniformSubroutineuiv;
	decltype(&glGetProgramStageiv) GetProgramStageiv;
	decltype(&glPatchParameteri) PatchParameteri;
	decltype(&glPatchParameterfv) PatchParameterfv;
	decltype(&glBindTransformFeedback) BindTransformFeedback;
	decltype(&glDeleteTransformFeedbacks) DeleteTransformFeedbacks;
	decltype(&glGenTransformFeedbacks) GenTransformFeedbacks;
	decltype(&glIsTransformFeedback) IsTransformFeedback;
	decltype(&glPauseTransformFeedback) PauseTransformFeedback;
	decltype(&glResumeTransformFeedback) ResumeTransformFeedback;
	decltype(&glDrawTransformFeedback) DrawTransformFeedback;
	decltype(&glDrawTransformFeedbackStream) DrawTransformFeedbackStream;
	decltype(&glBeginQueryIndexed) BeginQueryIndexed;
	decltype(&glEndQueryIndexed) EndQueryIndexed;
	decltype(&glGetQueryIndexediv) GetQueryIndexediv;
	decltype(&glReleaseShaderCompiler) ReleaseShaderCompiler;
	decltype(&glShaderBinary) ShaderBinary;
	decltype(&glGetShaderPrecisionFormat) GetShaderPrecisionFormat;
	decltype(&glDepthRangef) DepthRangef;
	decltype(&glClearDepthf) ClearDepthf;
	decltype(&glGetProgramBinary) GetProgramBinary;
	decltype(&glProgramBinary) ProgramBinary;
	decltype(&glProgramParameteri) ProgramParameteri;
	decltype(&glUseProgramStages) UseProgramStages;
	decltype(&glActiveShaderProgram) ActiveShaderProgram;
	decltype(&glCreateShaderProgramv) CreateShaderProgramv;
	decltype(&glBindProgramPipeline) BindProgramPipeline;
	decltype(&glDeleteProgramPipelines) DeleteProgramPipelines;
	decltype(&glGenProgramPipelines) GenProgramPipelines;
	decltype(&glIsProgramPipeline) IsProgramPipeline;
	decltype(&glGetProgramPipelineiv) GetProgramPipelineiv;
	decltype(&glProgramUniform1i) ProgramUniform1i;
	decltype(&glProgramUniform1iv) ProgramUniform1iv;
	decltype(&glProgramUniform1f) ProgramUniform1f;
	decltype(&glProgramUniform1fv) ProgramUniform1fv;
	decltype(&glProgramUniform1d) ProgramUniform1d;
	decltype(&glProgramUniform1dv) ProgramUniform1dv;
	decltype(&glProgramUniform1ui) ProgramUniform1ui;
	decltype(&glProgramUniform1uiv) ProgramUniform1uiv;
	decltype(&glProgramUniform2i) ProgramUniform2i;
	decltype(&glProgramUniform2iv) ProgramUniform2iv;
	decltype(&glProgramUniform2f) ProgramUniform2f;
	decltype(&glProgramUniform2fv) ProgramUniform2fv;
	decltype(&glProgramUniform2d) ProgramUniform2d;
	decltype(&glProgramUniform2dv) ProgramUniform2dv;
	decltype(&glProgramUniform2ui) ProgramUniform2ui;
	decltype(&glProgramUniform2uiv) ProgramUniform2uiv;
	decltype(&glProgramUniform3i) ProgramUniform3i;
	decltype(&glProgramUniform3iv) ProgramUniform3iv;
	decltype(&glProgramUniform3f) ProgramUniform3f;
	decltype(&glProgramUniform3fv) ProgramUniform3fv;
	decltype(&glProgramUniform3d) ProgramUniform3d;
	decltype(&glProgramUniform3dv) ProgramUniform3dv;
	decltype(&glProgramUniform3ui) ProgramUniform3ui;
	decltype(&glProgramUniform3uiv) ProgramUniform3uiv;
	decltype(&glProgramUniform4i) ProgramUniform4i;
	decltype(&glProgramUniform4iv) ProgramUniform4iv;
	decltype(&glProgramUniform4f) ProgramUniform4f;
	decltype(&glProgramUniform4fv) ProgramUniform4fv;
	decltype(&glProgramUniform4d) ProgramUniform4d;
	decltype(&glProgramUniform4dv) ProgramUniform4dv;
	decltype(&glProgramUniform4ui) ProgramUniform4ui;
	decltype(&glProgramUniform4uiv) ProgramUniform4uiv;
	decltype(&glProgramUniformMatrix2fv) ProgramUniformMatrix2fv;
	decltype(&glProgramUniformMatrix3fv) ProgramUniformMatrix3fv;
	decltype(&glProgramUniformMatrix4fv) ProgramUniformMatrix4fv;
	decltype(&glProgramUniformMatrix2dv) ProgramUniformMatrix2dv;
	decltype(&glProgramUniformMatrix3dv) ProgramUniformMatrix3dv;
	decltype(&glProgramUniformMatrix4dv) ProgramUniformMatrix4dv;
	decltype(&glProgramUniformMatrix2x3fv) ProgramUniformMatrix2x3fv;
	decltype(&glProgramUniformMatrix3x2fv) ProgramUniformMatrix3x2fv;
	decltype(&glProgramUniformMatrix2x4fv) ProgramUniformMatrix2x4fv;
	decltype(&glProgramUniformMatrix4x2fv) ProgramUniformMatrix4x2fv;
	decltype(&glProgramUniformMatrix3x4fv) ProgramUniformMatrix3x4fv;
	decltype(&glProgramUniformMatrix4x3fv) ProgramUniformMatrix4x3fv;
	decltype(&glProgramUniformMatrix2x3dv) ProgramUniformMatrix2x3dv;
	decltype(&glProgramUniformMatrix3x2dv) ProgramUniformMatrix3x2dv;
	decltype(&glProgramUniformMatrix2x4dv) ProgramUniformMatrix2x4dv;
	decltype(&glProgramUniformMatrix4x2dv) ProgramUniformMatrix4x2dv;
	decltype(&glProgramUniformMatrix3x4dv) ProgramUniformMatrix3x4dv;
	decltype(&glProgramUniformMatrix4x3dv) ProgramUniformMatrix4x3dv;
	decltype(&glValidateProgramPipeline) ValidateProgramPipeline;
	decltype(&glGetProgramPipelineInfoLog) GetProgramPipelineInfoLog;
	decltype(&glVertexAttribL1d) VertexAttribL1d;
	decltype(&glVertexAttribL2d) VertexAttribL2d;
	decltype(&glVertexAttribL3d) VertexAttribL3d;
	decltype(&glVertexAttribL4d) VertexAttribL4d;
	decltype(&glVertexAttribL1dv) VertexAttribL1dv;
	decltype(&glVertexAttribL2dv) VertexAttribL2dv;
	decltype(&glVertexAttribL3dv) VertexAttribL3dv;
	decltype(&glVertexAttribL4dv) VertexAttribL4dv;
	decltype(&glVertexAttribLPointer) VertexAttribLPointer;
	decltype(&glGetVertexAttribLdv) GetVertexAttribLdv;
	decltype(&glViewportArrayv) ViewportArrayv;
	decltype(&glViewportIndexedf) ViewportIndexedf;
	decltype(&glViewportIndexedfv) ViewportIndexedfv;
	decltype(&glScissorArrayv) ScissorArrayv;
	decltype(&glScissorIndexed) ScissorIndexed;
	decltype(&glScissorIndexedv) ScissorIndexedv;
	decltype(&glDepthRangeArrayv) DepthRangeArrayv;
	decltype(&glDepthRangeIndexed) DepthRangeIndexed;
	decltype(&glGetFloati_v) GetFloati_v;
	decltype(&glGetDoublei_v) GetDoublei_v;
	decltype(&glCreateSyncFromCLeventARB) CreateSyncFromCLeventARB;
	decltype(&glDebugMessageControlARB) DebugMessageControlARB;
	decltype(&glDebugMessageInsertARB) DebugMessageInsertARB;
	decltype(&glDebugMessageCallbackARB) DebugMessageCallbackARB;
	decltype(&glGetDebugMessageLogARB) GetDebugMessageLogARB;
	decltype(&glGetGraphicsResetStatusARB) GetGraphicsResetStatusARB;
	decltype(&glGetnMapdvARB) GetnMapdvARB;
	decltype(&glGetnMapfvARB) GetnMapfvARB;
	decltype(&glGetnMapivARB) GetnMapivARB;
	decltype(&glGetnPixelMapfvARB) GetnPixelMapfvARB;
	decltype(&glGetnPixelMapuivARB) GetnPixelMapuivARB;
	decltype(&glGetnPixelMapusvARB) GetnPixelMapusvARB;
	decltype(&glGetnPolygonStippleARB) GetnPolygonStippleARB;
	decltype(&glGetnColorTableARB) GetnColorTableARB;
	decltype(&glGetnConvolutionFilterARB) GetnConvolutionFilterARB;
	decltype(&glGetnSeparableFilterARB) GetnSeparableFilterARB;
	decltype(&glGetnHistogramARB) GetnHistogramARB;
	decltype(&glGetnMinmaxARB) GetnMinmaxARB;
	decltype(&glGetnTexImageARB) GetnTexImageARB;
	decltype(&glReadnPixelsARB) ReadnPixelsARB;
	decltype(&glGetnCompressedTexImageARB) GetnCompressedTexImageARB;
	decltype(&glGetnUniformfvARB) GetnUniformfvARB;
	decltype(&glGetnUniformivARB) GetnUniformivARB;
	decltype(&glGetnUniformuivARB) GetnUniformuivARB;
	decltype(&glGetnUniformdvARB) GetnUniformdvARB;
	decltype(&glDrawArraysInstancedBaseInstance) DrawArraysInstancedBaseInstance;
	decltype(&glDrawElementsInstancedBaseInstance) DrawElementsInstancedBaseInstance;
	decltype(&glDrawElementsInstancedBaseVertexBaseInstance) DrawElementsInstancedBaseVertexBaseInstance;
	decltype(&glDrawTransformFeedbackInstanced) DrawTransformFeedbackInstanced;
	decltype(&glDrawTransformFeedbackStreamInstanced) DrawTransformFeedbackStreamInstanced;
	decltype(&glGetInternalformativ) GetInternalformativ;
	decltype(&glGetActiveAtomicCounterBufferiv) GetActiveAtomicCounterBufferiv;
	decltype(&glBindImageTexture) BindImageTexture;
	decltype(&glMemoryBarrier) MemoryBarrier;
	decltype(&glTexStorage1D) TexStorage1D;
	decltype(&glTexStorage2D) TexStorage2D;
	decltype(&glTexStorage3D) TexStorage3D;
	decltype(&glTextureStorage1DEXT) TextureStorage1DEXT;
	decltype(&glTextureStorage2DEXT) TextureStorage2DEXT;
	decltype(&glTextureStorage3DEXT) TextureStorage3DEXT;
};

GlProcsT gGlProcs;

void checkError()
{
#ifndef NDEBUG
	auto error = gGlProcs.GetError();
	switch (error) {
	case GL_NO_ERROR:
		return;
	case GL_INVALID_ENUM:
		throw std::runtime_error("OpenGL Error: GL_INVALID_ENUM");
	case GL_INVALID_VALUE:
		throw std::runtime_error("OpenGL Error: GL_INVALID_VALUE");
	case GL_INVALID_OPERATION:
		throw std::runtime_error("OpenGL Error: GL_INVALID_OPERATION");
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		throw std::runtime_error("OpenGL Error: GL_INVALID_FRAMEBUFFER_OPERATION");
	case GL_OUT_OF_MEMORY:
		throw std::runtime_error("OpenGL Error: GL_OUT_OF_MEMORY");
	}
#endif
}

}

namespace Twil {
namespace Gl {
namespace Context {

void initialize(Platform::SymbolLoaderT const & Loader)
{
	Loader.loadGlSymbol(gGlProcs.CullFace, "glCullFace");
	Loader.loadGlSymbol(gGlProcs.FrontFace, "glFrontFace");
	Loader.loadGlSymbol(gGlProcs.Hint, "glHint");
	Loader.loadGlSymbol(gGlProcs.LineWidth, "glLineWidth");
	Loader.loadGlSymbol(gGlProcs.PointSize, "glPointSize");
	Loader.loadGlSymbol(gGlProcs.PolygonMode, "glPolygonMode");
	Loader.loadGlSymbol(gGlProcs.Scissor, "glScissor");
	Loader.loadGlSymbol(gGlProcs.TexParameterf, "glTexParameterf");
	Loader.loadGlSymbol(gGlProcs.TexParameterfv, "glTexParameterfv");
	Loader.loadGlSymbol(gGlProcs.TexParameteri, "glTexParameteri");
	Loader.loadGlSymbol(gGlProcs.TexParameteriv, "glTexParameteriv");
	Loader.loadGlSymbol(gGlProcs.TexImage1D, "glTexImage1D");
	Loader.loadGlSymbol(gGlProcs.TexImage2D, "glTexImage2D");
	Loader.loadGlSymbol(gGlProcs.DrawBuffer, "glDrawBuffer");
	Loader.loadGlSymbol(gGlProcs.Clear, "glClear");
	Loader.loadGlSymbol(gGlProcs.ClearColor, "glClearColor");
	Loader.loadGlSymbol(gGlProcs.ClearStencil, "glClearStencil");
	Loader.loadGlSymbol(gGlProcs.ClearDepth, "glClearDepth");
	Loader.loadGlSymbol(gGlProcs.StencilMask, "glStencilMask");
	Loader.loadGlSymbol(gGlProcs.ColorMask, "glColorMask");
	Loader.loadGlSymbol(gGlProcs.DepthMask, "glDepthMask");
	Loader.loadGlSymbol(gGlProcs.Disable, "glDisable");
	Loader.loadGlSymbol(gGlProcs.Enable, "glEnable");
	Loader.loadGlSymbol(gGlProcs.Finish, "glFinish");
	Loader.loadGlSymbol(gGlProcs.Flush, "glFlush");
	Loader.loadGlSymbol(gGlProcs.BlendFunc, "glBlendFunc");
	Loader.loadGlSymbol(gGlProcs.LogicOp, "glLogicOp");
	Loader.loadGlSymbol(gGlProcs.StencilFunc, "glStencilFunc");
	Loader.loadGlSymbol(gGlProcs.StencilOp, "glStencilOp");
	Loader.loadGlSymbol(gGlProcs.DepthFunc, "glDepthFunc");
	Loader.loadGlSymbol(gGlProcs.PixelStoref, "glPixelStoref");
	Loader.loadGlSymbol(gGlProcs.PixelStorei, "glPixelStorei");
	Loader.loadGlSymbol(gGlProcs.ReadBuffer, "glReadBuffer");
	Loader.loadGlSymbol(gGlProcs.ReadPixels, "glReadPixels");
	Loader.loadGlSymbol(gGlProcs.GetBooleanv, "glGetBooleanv");
	Loader.loadGlSymbol(gGlProcs.GetDoublev, "glGetDoublev");
	Loader.loadGlSymbol(gGlProcs.GetError, "glGetError");
	Loader.loadGlSymbol(gGlProcs.GetFloatv, "glGetFloatv");
	Loader.loadGlSymbol(gGlProcs.GetIntegerv, "glGetIntegerv");
	Loader.loadGlSymbol(gGlProcs.GetString, "glGetString");
	Loader.loadGlSymbol(gGlProcs.GetTexImage, "glGetTexImage");
	Loader.loadGlSymbol(gGlProcs.GetTexParameterfv, "glGetTexParameterfv");
	Loader.loadGlSymbol(gGlProcs.GetTexParameteriv, "glGetTexParameteriv");
	Loader.loadGlSymbol(gGlProcs.GetTexLevelParameterfv, "glGetTexLevelParameterfv");
	Loader.loadGlSymbol(gGlProcs.GetTexLevelParameteriv, "glGetTexLevelParameteriv");
	Loader.loadGlSymbol(gGlProcs.IsEnabled, "glIsEnabled");
	Loader.loadGlSymbol(gGlProcs.DepthRange, "glDepthRange");
	Loader.loadGlSymbol(gGlProcs.Viewport, "glViewport");
	Loader.loadGlSymbol(gGlProcs.DrawArrays, "glDrawArrays");
	Loader.loadGlSymbol(gGlProcs.DrawElements, "glDrawElements");
	Loader.loadGlSymbol(gGlProcs.GetPointerv, "glGetPointerv");
	Loader.loadGlSymbol(gGlProcs.PolygonOffset, "glPolygonOffset");
	Loader.loadGlSymbol(gGlProcs.CopyTexImage1D, "glCopyTexImage1D");
	Loader.loadGlSymbol(gGlProcs.CopyTexImage2D, "glCopyTexImage2D");
	Loader.loadGlSymbol(gGlProcs.CopyTexSubImage1D, "glCopyTexSubImage1D");
	Loader.loadGlSymbol(gGlProcs.CopyTexSubImage2D, "glCopyTexSubImage2D");
	Loader.loadGlSymbol(gGlProcs.TexSubImage1D, "glTexSubImage1D");
	Loader.loadGlSymbol(gGlProcs.TexSubImage2D, "glTexSubImage2D");
	Loader.loadGlSymbol(gGlProcs.BindTexture, "glBindTexture");
	Loader.loadGlSymbol(gGlProcs.DeleteTextures, "glDeleteTextures");
	Loader.loadGlSymbol(gGlProcs.GenTextures, "glGenTextures");
	Loader.loadGlSymbol(gGlProcs.IsTexture, "glIsTexture");
	Loader.loadGlArbSymbol(gGlProcs.BlendColor, "glBlendColor");
	Loader.loadGlArbSymbol(gGlProcs.BlendEquation, "glBlendEquation");
	Loader.loadGlArbSymbol(gGlProcs.DrawRangeElements, "glDrawRangeElements");
	Loader.loadGlArbSymbol(gGlProcs.TexImage3D, "glTexImage3D");
	Loader.loadGlArbSymbol(gGlProcs.TexSubImage3D, "glTexSubImage3D");
	Loader.loadGlArbSymbol(gGlProcs.CopyTexSubImage3D, "glCopyTexSubImage3D");
	Loader.loadGlArbSymbol(gGlProcs.ActiveTexture, "glActiveTexture");
	Loader.loadGlArbSymbol(gGlProcs.SampleCoverage, "glSampleCoverage");
	Loader.loadGlArbSymbol(gGlProcs.CompressedTexImage3D, "glCompressedTexImage3D");
	Loader.loadGlArbSymbol(gGlProcs.CompressedTexImage2D, "glCompressedTexImage2D");
	Loader.loadGlArbSymbol(gGlProcs.CompressedTexImage1D, "glCompressedTexImage1D");
	Loader.loadGlArbSymbol(gGlProcs.CompressedTexSubImage3D, "glCompressedTexSubImage3D");
	Loader.loadGlArbSymbol(gGlProcs.CompressedTexSubImage2D, "glCompressedTexSubImage2D");
	Loader.loadGlArbSymbol(gGlProcs.CompressedTexSubImage1D, "glCompressedTexSubImage1D");
	Loader.loadGlArbSymbol(gGlProcs.GetCompressedTexImage, "glGetCompressedTexImage");
	Loader.loadGlArbSymbol(gGlProcs.BlendFuncSeparate, "glBlendFuncSeparate");
	Loader.loadGlArbSymbol(gGlProcs.MultiDrawArrays, "glMultiDrawArrays");
	Loader.loadGlArbSymbol(gGlProcs.MultiDrawElements, "glMultiDrawElements");
	Loader.loadGlArbSymbol(gGlProcs.PointParameterf, "glPointParameterf");
	Loader.loadGlArbSymbol(gGlProcs.PointParameterfv, "glPointParameterfv");
	Loader.loadGlArbSymbol(gGlProcs.PointParameteri, "glPointParameteri");
	Loader.loadGlArbSymbol(gGlProcs.PointParameteriv, "glPointParameteriv");
	Loader.loadGlArbSymbol(gGlProcs.GenQueries, "glGenQueries");
	Loader.loadGlArbSymbol(gGlProcs.DeleteQueries, "glDeleteQueries");
	Loader.loadGlArbSymbol(gGlProcs.IsQuery, "glIsQuery");
	Loader.loadGlArbSymbol(gGlProcs.BeginQuery, "glBeginQuery");
	Loader.loadGlArbSymbol(gGlProcs.EndQuery, "glEndQuery");
	Loader.loadGlArbSymbol(gGlProcs.GetQueryiv, "glGetQueryiv");
	Loader.loadGlArbSymbol(gGlProcs.GetQueryObjectiv, "glGetQueryObjectiv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribP1ui, "glVertexAttribP1ui");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribP1uiv, "glVertexAttribP1uiv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribP2ui, "glVertexAttribP2ui");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribP2uiv, "glVertexAttribP2uiv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribP3ui, "glVertexAttribP3ui");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribP3uiv, "glVertexAttribP3uiv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribP4ui, "glVertexAttribP4ui");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribP4uiv, "glVertexAttribP4uiv");
	Loader.loadGlArbSymbol(gGlProcs.GetQueryObjectuiv, "glGetQueryObjectuiv");
	Loader.loadGlArbSymbol(gGlProcs.BindBuffer, "glBindBuffer");
	Loader.loadGlArbSymbol(gGlProcs.DeleteBuffers, "glDeleteBuffers");
	Loader.loadGlArbSymbol(gGlProcs.GenBuffers, "glGenBuffers");
	Loader.loadGlArbSymbol(gGlProcs.IsBuffer, "glIsBuffer");
	Loader.loadGlArbSymbol(gGlProcs.BufferData, "glBufferData");
	Loader.loadGlArbSymbol(gGlProcs.BufferSubData, "glBufferSubData");
	Loader.loadGlArbSymbol(gGlProcs.GetBufferSubData, "glGetBufferSubData");
	Loader.loadGlArbSymbol(gGlProcs.MapBuffer, "glMapBuffer");
	Loader.loadGlArbSymbol(gGlProcs.UnmapBuffer, "glUnmapBuffer");
	Loader.loadGlArbSymbol(gGlProcs.GetBufferParameteriv, "glGetBufferParameteriv");
	Loader.loadGlArbSymbol(gGlProcs.GetBufferPointerv, "glGetBufferPointerv");
	Loader.loadGlArbSymbol(gGlProcs.BlendEquationSeparate, "glBlendEquationSeparate");
	Loader.loadGlArbSymbol(gGlProcs.DrawBuffers, "glDrawBuffers");
	Loader.loadGlArbSymbol(gGlProcs.StencilOpSeparate, "glStencilOpSeparate");
	Loader.loadGlArbSymbol(gGlProcs.StencilFuncSeparate, "glStencilFuncSeparate");
	Loader.loadGlArbSymbol(gGlProcs.StencilMaskSeparate, "glStencilMaskSeparate");
	Loader.loadGlArbSymbol(gGlProcs.AttachShader, "glAttachShader");
	Loader.loadGlArbSymbol(gGlProcs.BindAttribLocation, "glBindAttribLocation");
	Loader.loadGlArbSymbol(gGlProcs.CompileShader, "glCompileShader");
	Loader.loadGlArbSymbol(gGlProcs.CreateProgram, "glCreateProgram");
	Loader.loadGlArbSymbol(gGlProcs.CreateShader, "glCreateShader");
	Loader.loadGlArbSymbol(gGlProcs.DeleteProgram, "glDeleteProgram");
	Loader.loadGlArbSymbol(gGlProcs.DeleteShader, "glDeleteShader");
	Loader.loadGlArbSymbol(gGlProcs.DetachShader, "glDetachShader");
	Loader.loadGlArbSymbol(gGlProcs.DisableVertexAttribArray, "glDisableVertexAttribArray");
	Loader.loadGlArbSymbol(gGlProcs.EnableVertexAttribArray, "glEnableVertexAttribArray");
	Loader.loadGlArbSymbol(gGlProcs.GetActiveAttrib, "glGetActiveAttrib");
	Loader.loadGlArbSymbol(gGlProcs.GetActiveUniform, "glGetActiveUniform");
	Loader.loadGlArbSymbol(gGlProcs.GetAttachedShaders, "glGetAttachedShaders");
	Loader.loadGlArbSymbol(gGlProcs.GetAttribLocation, "glGetAttribLocation");
	Loader.loadGlArbSymbol(gGlProcs.GetProgramiv, "glGetProgramiv");
	Loader.loadGlArbSymbol(gGlProcs.GetProgramInfoLog, "glGetProgramInfoLog");
	Loader.loadGlArbSymbol(gGlProcs.GetShaderiv, "glGetShaderiv");
	Loader.loadGlArbSymbol(gGlProcs.GetShaderInfoLog, "glGetShaderInfoLog");
	Loader.loadGlArbSymbol(gGlProcs.GetShaderSource, "glGetShaderSource");
	Loader.loadGlArbSymbol(gGlProcs.GetUniformLocation, "glGetUniformLocation");
	Loader.loadGlArbSymbol(gGlProcs.GetUniformfv, "glGetUniformfv");
	Loader.loadGlArbSymbol(gGlProcs.GetUniformiv, "glGetUniformiv");
	Loader.loadGlArbSymbol(gGlProcs.GetVertexAttribdv, "glGetVertexAttribdv");
	Loader.loadGlArbSymbol(gGlProcs.GetVertexAttribfv, "glGetVertexAttribfv");
	Loader.loadGlArbSymbol(gGlProcs.GetVertexAttribiv, "glGetVertexAttribiv");
	Loader.loadGlArbSymbol(gGlProcs.GetVertexAttribPointerv, "glGetVertexAttribPointerv");
	Loader.loadGlArbSymbol(gGlProcs.IsProgram, "glIsProgram");
	Loader.loadGlArbSymbol(gGlProcs.IsShader, "glIsShader");
	Loader.loadGlArbSymbol(gGlProcs.LinkProgram, "glLinkProgram");
	Loader.loadGlArbSymbol(gGlProcs.ShaderSource, "glShaderSource");
	Loader.loadGlArbSymbol(gGlProcs.UseProgram, "glUseProgram");
	Loader.loadGlArbSymbol(gGlProcs.Uniform1f, "glUniform1f");
	Loader.loadGlArbSymbol(gGlProcs.Uniform2f, "glUniform2f");
	Loader.loadGlArbSymbol(gGlProcs.Uniform3f, "glUniform3f");
	Loader.loadGlArbSymbol(gGlProcs.Uniform4f, "glUniform4f");
	Loader.loadGlArbSymbol(gGlProcs.Uniform1i, "glUniform1i");
	Loader.loadGlArbSymbol(gGlProcs.Uniform2i, "glUniform2i");
	Loader.loadGlArbSymbol(gGlProcs.Uniform3i, "glUniform3i");
	Loader.loadGlArbSymbol(gGlProcs.Uniform4i, "glUniform4i");
	Loader.loadGlArbSymbol(gGlProcs.Uniform1fv, "glUniform1fv");
	Loader.loadGlArbSymbol(gGlProcs.Uniform2fv, "glUniform2fv");
	Loader.loadGlArbSymbol(gGlProcs.Uniform3fv, "glUniform3fv");
	Loader.loadGlArbSymbol(gGlProcs.Uniform4fv, "glUniform4fv");
	Loader.loadGlArbSymbol(gGlProcs.Uniform1iv, "glUniform1iv");
	Loader.loadGlArbSymbol(gGlProcs.Uniform2iv, "glUniform2iv");
	Loader.loadGlArbSymbol(gGlProcs.Uniform3iv, "glUniform3iv");
	Loader.loadGlArbSymbol(gGlProcs.Uniform4iv, "glUniform4iv");
	Loader.loadGlArbSymbol(gGlProcs.UniformMatrix2fv, "glUniformMatrix2fv");
	Loader.loadGlArbSymbol(gGlProcs.UniformMatrix3fv, "glUniformMatrix3fv");
	Loader.loadGlArbSymbol(gGlProcs.UniformMatrix4fv, "glUniformMatrix4fv");
	Loader.loadGlArbSymbol(gGlProcs.ValidateProgram, "glValidateProgram");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib1d, "glVertexAttrib1d");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib1dv, "glVertexAttrib1dv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib1f, "glVertexAttrib1f");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib1fv, "glVertexAttrib1fv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib1s, "glVertexAttrib1s");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib1sv, "glVertexAttrib1sv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib2d, "glVertexAttrib2d");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib2dv, "glVertexAttrib2dv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib2f, "glVertexAttrib2f");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib2fv, "glVertexAttrib2fv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib2s, "glVertexAttrib2s");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib2sv, "glVertexAttrib2sv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib3d, "glVertexAttrib3d");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib3dv, "glVertexAttrib3dv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib3f, "glVertexAttrib3f");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib3fv, "glVertexAttrib3fv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib3s, "glVertexAttrib3s");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib3sv, "glVertexAttrib3sv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib4Nbv, "glVertexAttrib4Nbv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib4Niv, "glVertexAttrib4Niv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib4Nsv, "glVertexAttrib4Nsv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib4Nub, "glVertexAttrib4Nub");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib4Nubv, "glVertexAttrib4Nubv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib4Nuiv, "glVertexAttrib4Nuiv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib4Nusv, "glVertexAttrib4Nusv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib4bv, "glVertexAttrib4bv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib4d, "glVertexAttrib4d");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib4dv, "glVertexAttrib4dv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib4f, "glVertexAttrib4f");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib4fv, "glVertexAttrib4fv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib4iv, "glVertexAttrib4iv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib4s, "glVertexAttrib4s");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib4sv, "glVertexAttrib4sv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib4ubv, "glVertexAttrib4ubv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib4uiv, "glVertexAttrib4uiv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttrib4usv, "glVertexAttrib4usv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribPointer, "glVertexAttribPointer");
	Loader.loadGlArbSymbol(gGlProcs.UniformMatrix2x3fv, "glUniformMatrix2x3fv");
	Loader.loadGlArbSymbol(gGlProcs.UniformMatrix3x2fv, "glUniformMatrix3x2fv");
	Loader.loadGlArbSymbol(gGlProcs.UniformMatrix2x4fv, "glUniformMatrix2x4fv");
	Loader.loadGlArbSymbol(gGlProcs.UniformMatrix4x2fv, "glUniformMatrix4x2fv");
	Loader.loadGlArbSymbol(gGlProcs.UniformMatrix3x4fv, "glUniformMatrix3x4fv");
	Loader.loadGlArbSymbol(gGlProcs.UniformMatrix4x3fv, "glUniformMatrix4x3fv");
	Loader.loadGlArbSymbol(gGlProcs.ColorMaski, "glColorMaski");
	Loader.loadGlArbSymbol(gGlProcs.GetBooleani_v, "glGetBooleani_v");
	Loader.loadGlArbSymbol(gGlProcs.GetIntegeri_v, "glGetIntegeri_v");
	Loader.loadGlArbSymbol(gGlProcs.Enablei, "glEnablei");
	Loader.loadGlArbSymbol(gGlProcs.Disablei, "glDisablei");
	Loader.loadGlArbSymbol(gGlProcs.IsEnabledi, "glIsEnabledi");
	Loader.loadGlArbSymbol(gGlProcs.BeginTransformFeedback, "glBeginTransformFeedback");
	Loader.loadGlArbSymbol(gGlProcs.EndTransformFeedback, "glEndTransformFeedback");
	Loader.loadGlArbSymbol(gGlProcs.BindBufferRange, "glBindBufferRange");
	Loader.loadGlArbSymbol(gGlProcs.BindBufferBase, "glBindBufferBase");
	Loader.loadGlArbSymbol(gGlProcs.TransformFeedbackVaryings, "glTransformFeedbackVaryings");
	Loader.loadGlArbSymbol(gGlProcs.GetTransformFeedbackVarying, "glGetTransformFeedbackVarying");
	Loader.loadGlArbSymbol(gGlProcs.ClampColor, "glClampColor");
	Loader.loadGlArbSymbol(gGlProcs.BeginConditionalRender, "glBeginConditionalRender");
	Loader.loadGlArbSymbol(gGlProcs.EndConditionalRender, "glEndConditionalRender");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribIPointer, "glVertexAttribIPointer");
	Loader.loadGlArbSymbol(gGlProcs.GetVertexAttribIiv, "glGetVertexAttribIiv");
	Loader.loadGlArbSymbol(gGlProcs.GetVertexAttribIuiv, "glGetVertexAttribIuiv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribI1i, "glVertexAttribI1i");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribI2i, "glVertexAttribI2i");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribI3i, "glVertexAttribI3i");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribI4i, "glVertexAttribI4i");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribI1ui, "glVertexAttribI1ui");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribI2ui, "glVertexAttribI2ui");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribI3ui, "glVertexAttribI3ui");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribI4ui, "glVertexAttribI4ui");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribI1iv, "glVertexAttribI1iv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribI2iv, "glVertexAttribI2iv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribI3iv, "glVertexAttribI3iv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribI4iv, "glVertexAttribI4iv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribI1uiv, "glVertexAttribI1uiv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribI2uiv, "glVertexAttribI2uiv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribI3uiv, "glVertexAttribI3uiv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribI4uiv, "glVertexAttribI4uiv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribI4bv, "glVertexAttribI4bv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribI4sv, "glVertexAttribI4sv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribI4ubv, "glVertexAttribI4ubv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribI4usv, "glVertexAttribI4usv");
	Loader.loadGlArbSymbol(gGlProcs.GetUniformuiv, "glGetUniformuiv");
	Loader.loadGlArbSymbol(gGlProcs.BindFragDataLocation, "glBindFragDataLocation");
	Loader.loadGlArbSymbol(gGlProcs.GetFragDataLocation, "glGetFragDataLocation");
	Loader.loadGlArbSymbol(gGlProcs.Uniform1ui, "glUniform1ui");
	Loader.loadGlArbSymbol(gGlProcs.Uniform2ui, "glUniform2ui");
	Loader.loadGlArbSymbol(gGlProcs.Uniform3ui, "glUniform3ui");
	Loader.loadGlArbSymbol(gGlProcs.Uniform4ui, "glUniform4ui");
	Loader.loadGlArbSymbol(gGlProcs.Uniform1uiv, "glUniform1uiv");
	Loader.loadGlArbSymbol(gGlProcs.Uniform2uiv, "glUniform2uiv");
	Loader.loadGlArbSymbol(gGlProcs.Uniform3uiv, "glUniform3uiv");
	Loader.loadGlArbSymbol(gGlProcs.Uniform4uiv, "glUniform4uiv");
	Loader.loadGlArbSymbol(gGlProcs.TexParameterIiv, "glTexParameterIiv");
	Loader.loadGlArbSymbol(gGlProcs.TexParameterIuiv, "glTexParameterIuiv");
	Loader.loadGlArbSymbol(gGlProcs.GetTexParameterIiv, "glGetTexParameterIiv");
	Loader.loadGlArbSymbol(gGlProcs.GetTexParameterIuiv, "glGetTexParameterIuiv");
	Loader.loadGlArbSymbol(gGlProcs.ClearBufferiv, "glClearBufferiv");
	Loader.loadGlArbSymbol(gGlProcs.ClearBufferuiv, "glClearBufferuiv");
	Loader.loadGlArbSymbol(gGlProcs.ClearBufferfv, "glClearBufferfv");
	Loader.loadGlArbSymbol(gGlProcs.ClearBufferfi, "glClearBufferfi");
	Loader.loadGlArbSymbol(gGlProcs.GetStringi, "glGetStringi");
	Loader.loadGlArbSymbol(gGlProcs.DrawArraysInstanced, "glDrawArraysInstanced");
	Loader.loadGlArbSymbol(gGlProcs.DrawElementsInstanced, "glDrawElementsInstanced");
	Loader.loadGlArbSymbol(gGlProcs.TexBuffer, "glTexBuffer");
	Loader.loadGlArbSymbol(gGlProcs.PrimitiveRestartIndex, "glPrimitiveRestartIndex");
	Loader.loadGlArbSymbol(gGlProcs.GetInteger64i_v, "glGetInteger64i_v");
	Loader.loadGlArbSymbol(gGlProcs.GetBufferParameteri64v, "glGetBufferParameteri64v");
	Loader.loadGlArbSymbol(gGlProcs.FramebufferTexture, "glFramebufferTexture");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribDivisor, "glVertexAttribDivisor");
	Loader.loadGlArbSymbol(gGlProcs.MinSampleShading, "glMinSampleShading");
	Loader.loadGlArbSymbol(gGlProcs.BlendEquationi, "glBlendEquationi");
	Loader.loadGlArbSymbol(gGlProcs.BlendEquationSeparatei, "glBlendEquationSeparatei");
	Loader.loadGlArbSymbol(gGlProcs.BlendFunci, "glBlendFunci");
	Loader.loadGlArbSymbol(gGlProcs.BlendFuncSeparatei, "glBlendFuncSeparatei");
	Loader.loadGlArbSymbol(gGlProcs.IsRenderbuffer, "glIsRenderbuffer");
	Loader.loadGlArbSymbol(gGlProcs.BindRenderbuffer, "glBindRenderbuffer");
	Loader.loadGlArbSymbol(gGlProcs.DeleteRenderbuffers, "glDeleteRenderbuffers");
	Loader.loadGlArbSymbol(gGlProcs.GenRenderbuffers, "glGenRenderbuffers");
	Loader.loadGlArbSymbol(gGlProcs.RenderbufferStorage, "glRenderbufferStorage");
	Loader.loadGlArbSymbol(gGlProcs.GetRenderbufferParameteriv, "glGetRenderbufferParameteriv");
	Loader.loadGlArbSymbol(gGlProcs.IsFramebuffer, "glIsFramebuffer");
	Loader.loadGlArbSymbol(gGlProcs.BindFramebuffer, "glBindFramebuffer");
	Loader.loadGlArbSymbol(gGlProcs.DeleteFramebuffers, "glDeleteFramebuffers");
	Loader.loadGlArbSymbol(gGlProcs.GenFramebuffers, "glGenFramebuffers");
	Loader.loadGlArbSymbol(gGlProcs.CheckFramebufferStatus, "glCheckFramebufferStatus");
	Loader.loadGlArbSymbol(gGlProcs.FramebufferTexture1D, "glFramebufferTexture1D");
	Loader.loadGlArbSymbol(gGlProcs.FramebufferTexture2D, "glFramebufferTexture2D");
	Loader.loadGlArbSymbol(gGlProcs.FramebufferTexture3D, "glFramebufferTexture3D");
	Loader.loadGlArbSymbol(gGlProcs.FramebufferRenderbuffer, "glFramebufferRenderbuffer");
	Loader.loadGlArbSymbol(gGlProcs.GetFramebufferAttachmentParameteriv, "glGetFramebufferAttachmentParameteriv");
	Loader.loadGlArbSymbol(gGlProcs.GenerateMipmap, "glGenerateMipmap");
	Loader.loadGlArbSymbol(gGlProcs.BlitFramebuffer, "glBlitFramebuffer");
	Loader.loadGlArbSymbol(gGlProcs.RenderbufferStorageMultisample, "glRenderbufferStorageMultisample");
	Loader.loadGlArbSymbol(gGlProcs.FramebufferTextureLayer, "glFramebufferTextureLayer");
	Loader.loadGlArbSymbol(gGlProcs.MapBufferRange, "glMapBufferRange");
	Loader.loadGlArbSymbol(gGlProcs.FlushMappedBufferRange, "glFlushMappedBufferRange");
	Loader.loadGlArbSymbol(gGlProcs.BindVertexArray, "glBindVertexArray");
	Loader.loadGlArbSymbol(gGlProcs.DeleteVertexArrays, "glDeleteVertexArrays");
	Loader.loadGlArbSymbol(gGlProcs.GenVertexArrays, "glGenVertexArrays");
	Loader.loadGlArbSymbol(gGlProcs.IsVertexArray, "glIsVertexArray");
	Loader.loadGlArbSymbol(gGlProcs.GetUniformIndices, "glGetUniformIndices");
	Loader.loadGlArbSymbol(gGlProcs.GetActiveUniformsiv, "glGetActiveUniformsiv");
	Loader.loadGlArbSymbol(gGlProcs.GetActiveUniformName, "glGetActiveUniformName");
	Loader.loadGlArbSymbol(gGlProcs.GetUniformBlockIndex, "glGetUniformBlockIndex");
	Loader.loadGlArbSymbol(gGlProcs.GetActiveUniformBlockiv, "glGetActiveUniformBlockiv");
	Loader.loadGlArbSymbol(gGlProcs.GetActiveUniformBlockName, "glGetActiveUniformBlockName");
	Loader.loadGlArbSymbol(gGlProcs.UniformBlockBinding, "glUniformBlockBinding");
	Loader.loadGlArbSymbol(gGlProcs.CopyBufferSubData, "glCopyBufferSubData");
	Loader.loadGlArbSymbol(gGlProcs.DrawElementsBaseVertex, "glDrawElementsBaseVertex");
	Loader.loadGlArbSymbol(gGlProcs.DrawRangeElementsBaseVertex, "glDrawRangeElementsBaseVertex");
	Loader.loadGlArbSymbol(gGlProcs.DrawElementsInstancedBaseVertex, "glDrawElementsInstancedBaseVertex");
	Loader.loadGlArbSymbol(gGlProcs.MultiDrawElementsBaseVertex, "glMultiDrawElementsBaseVertex");
	Loader.loadGlArbSymbol(gGlProcs.ProvokingVertex, "glProvokingVertex");
	Loader.loadGlArbSymbol(gGlProcs.FenceSync, "glFenceSync");
	Loader.loadGlArbSymbol(gGlProcs.IsSync, "glIsSync");
	Loader.loadGlArbSymbol(gGlProcs.DeleteSync, "glDeleteSync");
	Loader.loadGlArbSymbol(gGlProcs.ClientWaitSync, "glClientWaitSync");
	Loader.loadGlArbSymbol(gGlProcs.WaitSync, "glWaitSync");
	Loader.loadGlArbSymbol(gGlProcs.GetInteger64v, "glGetInteger64v");
	Loader.loadGlArbSymbol(gGlProcs.GetSynciv, "glGetSynciv");
	Loader.loadGlArbSymbol(gGlProcs.TexImage2DMultisample, "glTexImage2DMultisample");
	Loader.loadGlArbSymbol(gGlProcs.TexImage3DMultisample, "glTexImage3DMultisample");
	Loader.loadGlArbSymbol(gGlProcs.GetMultisamplefv, "glGetMultisamplefv");
	Loader.loadGlArbSymbol(gGlProcs.SampleMaski, "glSampleMaski");
	Loader.loadGlArbSymbol(gGlProcs.BlendEquationiARB, "glBlendEquationiARB");
	Loader.loadGlArbSymbol(gGlProcs.BlendEquationSeparateiARB, "glBlendEquationSeparateiARB");
	Loader.loadGlArbSymbol(gGlProcs.BlendFunciARB, "glBlendFunciARB");
	Loader.loadGlArbSymbol(gGlProcs.BlendFuncSeparateiARB, "glBlendFuncSeparateiARB");
	Loader.loadGlArbSymbol(gGlProcs.MinSampleShadingARB, "glMinSampleShadingARB");
	Loader.loadGlArbSymbol(gGlProcs.NamedStringARB, "glNamedStringARB");
	Loader.loadGlArbSymbol(gGlProcs.DeleteNamedStringARB, "glDeleteNamedStringARB");
	Loader.loadGlArbSymbol(gGlProcs.CompileShaderIncludeARB, "glCompileShaderIncludeARB");
	Loader.loadGlArbSymbol(gGlProcs.IsNamedStringARB, "glIsNamedStringARB");
	Loader.loadGlArbSymbol(gGlProcs.GetNamedStringARB, "glGetNamedStringARB");
	Loader.loadGlArbSymbol(gGlProcs.GetNamedStringivARB, "glGetNamedStringivARB");
	Loader.loadGlArbSymbol(gGlProcs.BindFragDataLocationIndexed, "glBindFragDataLocationIndexed");
	Loader.loadGlArbSymbol(gGlProcs.GetFragDataIndex, "glGetFragDataIndex");
	Loader.loadGlArbSymbol(gGlProcs.GenSamplers, "glGenSamplers");
	Loader.loadGlArbSymbol(gGlProcs.DeleteSamplers, "glDeleteSamplers");
	Loader.loadGlArbSymbol(gGlProcs.IsSampler, "glIsSampler");
	Loader.loadGlArbSymbol(gGlProcs.BindSampler, "glBindSampler");
	Loader.loadGlArbSymbol(gGlProcs.SamplerParameteri, "glSamplerParameteri");
	Loader.loadGlArbSymbol(gGlProcs.SamplerParameteriv, "glSamplerParameteriv");
	Loader.loadGlArbSymbol(gGlProcs.SamplerParameterf, "glSamplerParameterf");
	Loader.loadGlArbSymbol(gGlProcs.SamplerParameterfv, "glSamplerParameterfv");
	Loader.loadGlArbSymbol(gGlProcs.SamplerParameterIiv, "glSamplerParameterIiv");
	Loader.loadGlArbSymbol(gGlProcs.SamplerParameterIuiv, "glSamplerParameterIuiv");
	Loader.loadGlArbSymbol(gGlProcs.GetSamplerParameteriv, "glGetSamplerParameteriv");
	Loader.loadGlArbSymbol(gGlProcs.GetSamplerParameterIiv, "glGetSamplerParameterIiv");
	Loader.loadGlArbSymbol(gGlProcs.GetSamplerParameterfv, "glGetSamplerParameterfv");
	Loader.loadGlArbSymbol(gGlProcs.GetSamplerParameterIuiv, "glGetSamplerParameterIuiv");
	Loader.loadGlArbSymbol(gGlProcs.QueryCounter, "glQueryCounter");
	Loader.loadGlArbSymbol(gGlProcs.GetQueryObjecti64v, "glGetQueryObjecti64v");
	Loader.loadGlArbSymbol(gGlProcs.GetQueryObjectui64v, "glGetQueryObjectui64v");
	Loader.loadGlArbSymbol(gGlProcs.DrawArraysIndirect, "glDrawArraysIndirect");
	Loader.loadGlArbSymbol(gGlProcs.DrawElementsIndirect, "glDrawElementsIndirect");
	Loader.loadGlArbSymbol(gGlProcs.Uniform1d, "glUniform1d");
	Loader.loadGlArbSymbol(gGlProcs.Uniform2d, "glUniform2d");
	Loader.loadGlArbSymbol(gGlProcs.Uniform3d, "glUniform3d");
	Loader.loadGlArbSymbol(gGlProcs.Uniform4d, "glUniform4d");
	Loader.loadGlArbSymbol(gGlProcs.Uniform1dv, "glUniform1dv");
	Loader.loadGlArbSymbol(gGlProcs.Uniform2dv, "glUniform2dv");
	Loader.loadGlArbSymbol(gGlProcs.Uniform3dv, "glUniform3dv");
	Loader.loadGlArbSymbol(gGlProcs.Uniform4dv, "glUniform4dv");
	Loader.loadGlArbSymbol(gGlProcs.UniformMatrix2dv, "glUniformMatrix2dv");
	Loader.loadGlArbSymbol(gGlProcs.UniformMatrix3dv, "glUniformMatrix3dv");
	Loader.loadGlArbSymbol(gGlProcs.UniformMatrix4dv, "glUniformMatrix4dv");
	Loader.loadGlArbSymbol(gGlProcs.UniformMatrix2x3dv, "glUniformMatrix2x3dv");
	Loader.loadGlArbSymbol(gGlProcs.UniformMatrix2x4dv, "glUniformMatrix2x4dv");
	Loader.loadGlArbSymbol(gGlProcs.UniformMatrix3x2dv, "glUniformMatrix3x2dv");
	Loader.loadGlArbSymbol(gGlProcs.UniformMatrix3x4dv, "glUniformMatrix3x4dv");
	Loader.loadGlArbSymbol(gGlProcs.UniformMatrix4x2dv, "glUniformMatrix4x2dv");
	Loader.loadGlArbSymbol(gGlProcs.UniformMatrix4x3dv, "glUniformMatrix4x3dv");
	Loader.loadGlArbSymbol(gGlProcs.GetUniformdv, "glGetUniformdv");
	Loader.loadGlArbSymbol(gGlProcs.GetSubroutineUniformLocation, "glGetSubroutineUniformLocation");
	Loader.loadGlArbSymbol(gGlProcs.GetSubroutineIndex, "glGetSubroutineIndex");
	Loader.loadGlArbSymbol(gGlProcs.GetActiveSubroutineUniformiv, "glGetActiveSubroutineUniformiv");
	Loader.loadGlArbSymbol(gGlProcs.GetActiveSubroutineUniformName, "glGetActiveSubroutineUniformName");
	Loader.loadGlArbSymbol(gGlProcs.GetActiveSubroutineName, "glGetActiveSubroutineName");
	Loader.loadGlArbSymbol(gGlProcs.UniformSubroutinesuiv, "glUniformSubroutinesuiv");
	Loader.loadGlArbSymbol(gGlProcs.GetUniformSubroutineuiv, "glGetUniformSubroutineuiv");
	Loader.loadGlArbSymbol(gGlProcs.GetProgramStageiv, "glGetProgramStageiv");
	Loader.loadGlArbSymbol(gGlProcs.PatchParameteri, "glPatchParameteri");
	Loader.loadGlArbSymbol(gGlProcs.PatchParameterfv, "glPatchParameterfv");
	Loader.loadGlArbSymbol(gGlProcs.BindTransformFeedback, "glBindTransformFeedback");
	Loader.loadGlArbSymbol(gGlProcs.DeleteTransformFeedbacks, "glDeleteTransformFeedbacks");
	Loader.loadGlArbSymbol(gGlProcs.GenTransformFeedbacks, "glGenTransformFeedbacks");
	Loader.loadGlArbSymbol(gGlProcs.IsTransformFeedback, "glIsTransformFeedback");
	Loader.loadGlArbSymbol(gGlProcs.PauseTransformFeedback, "glPauseTransformFeedback");
	Loader.loadGlArbSymbol(gGlProcs.ResumeTransformFeedback, "glResumeTransformFeedback");
	Loader.loadGlArbSymbol(gGlProcs.DrawTransformFeedback, "glDrawTransformFeedback");
	Loader.loadGlArbSymbol(gGlProcs.DrawTransformFeedbackStream, "glDrawTransformFeedbackStream");
	Loader.loadGlArbSymbol(gGlProcs.BeginQueryIndexed, "glBeginQueryIndexed");
	Loader.loadGlArbSymbol(gGlProcs.EndQueryIndexed, "glEndQueryIndexed");
	Loader.loadGlArbSymbol(gGlProcs.GetQueryIndexediv, "glGetQueryIndexediv");
	Loader.loadGlArbSymbol(gGlProcs.ReleaseShaderCompiler, "glReleaseShaderCompiler");
	Loader.loadGlArbSymbol(gGlProcs.ShaderBinary, "glShaderBinary");
	Loader.loadGlArbSymbol(gGlProcs.GetShaderPrecisionFormat, "glGetShaderPrecisionFormat");
	Loader.loadGlArbSymbol(gGlProcs.DepthRangef, "glDepthRangef");
	Loader.loadGlArbSymbol(gGlProcs.ClearDepthf, "glClearDepthf");
	Loader.loadGlArbSymbol(gGlProcs.GetProgramBinary, "glGetProgramBinary");
	Loader.loadGlArbSymbol(gGlProcs.ProgramBinary, "glProgramBinary");
	Loader.loadGlArbSymbol(gGlProcs.ProgramParameteri, "glProgramParameteri");
	Loader.loadGlArbSymbol(gGlProcs.UseProgramStages, "glUseProgramStages");
	Loader.loadGlArbSymbol(gGlProcs.ActiveShaderProgram, "glActiveShaderProgram");
	Loader.loadGlArbSymbol(gGlProcs.CreateShaderProgramv, "glCreateShaderProgramv");
	Loader.loadGlArbSymbol(gGlProcs.BindProgramPipeline, "glBindProgramPipeline");
	Loader.loadGlArbSymbol(gGlProcs.DeleteProgramPipelines, "glDeleteProgramPipelines");
	Loader.loadGlArbSymbol(gGlProcs.GenProgramPipelines, "glGenProgramPipelines");
	Loader.loadGlArbSymbol(gGlProcs.IsProgramPipeline, "glIsProgramPipeline");
	Loader.loadGlArbSymbol(gGlProcs.GetProgramPipelineiv, "glGetProgramPipelineiv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform1i, "glProgramUniform1i");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform1iv, "glProgramUniform1iv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform1f, "glProgramUniform1f");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform1fv, "glProgramUniform1fv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform1d, "glProgramUniform1d");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform1dv, "glProgramUniform1dv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform1ui, "glProgramUniform1ui");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform1uiv, "glProgramUniform1uiv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform2i, "glProgramUniform2i");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform2iv, "glProgramUniform2iv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform2f, "glProgramUniform2f");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform2fv, "glProgramUniform2fv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform2d, "glProgramUniform2d");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform2dv, "glProgramUniform2dv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform2ui, "glProgramUniform2ui");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform2uiv, "glProgramUniform2uiv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform3i, "glProgramUniform3i");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform3iv, "glProgramUniform3iv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform3f, "glProgramUniform3f");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform3fv, "glProgramUniform3fv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform3d, "glProgramUniform3d");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform3dv, "glProgramUniform3dv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform3ui, "glProgramUniform3ui");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform3uiv, "glProgramUniform3uiv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform4i, "glProgramUniform4i");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform4iv, "glProgramUniform4iv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform4f, "glProgramUniform4f");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform4fv, "glProgramUniform4fv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform4d, "glProgramUniform4d");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform4dv, "glProgramUniform4dv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform4ui, "glProgramUniform4ui");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniform4uiv, "glProgramUniform4uiv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniformMatrix2fv, "glProgramUniformMatrix2fv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniformMatrix3fv, "glProgramUniformMatrix3fv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniformMatrix4fv, "glProgramUniformMatrix4fv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniformMatrix2dv, "glProgramUniformMatrix2dv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniformMatrix3dv, "glProgramUniformMatrix3dv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniformMatrix4dv, "glProgramUniformMatrix4dv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniformMatrix2x3fv, "glProgramUniformMatrix2x3fv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniformMatrix3x2fv, "glProgramUniformMatrix3x2fv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniformMatrix2x4fv, "glProgramUniformMatrix2x4fv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniformMatrix4x2fv, "glProgramUniformMatrix4x2fv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniformMatrix3x4fv, "glProgramUniformMatrix3x4fv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniformMatrix4x3fv, "glProgramUniformMatrix4x3fv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniformMatrix2x3dv, "glProgramUniformMatrix2x3dv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniformMatrix3x2dv, "glProgramUniformMatrix3x2dv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniformMatrix2x4dv, "glProgramUniformMatrix2x4dv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniformMatrix4x2dv, "glProgramUniformMatrix4x2dv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniformMatrix3x4dv, "glProgramUniformMatrix3x4dv");
	Loader.loadGlArbSymbol(gGlProcs.ProgramUniformMatrix4x3dv, "glProgramUniformMatrix4x3dv");
	Loader.loadGlArbSymbol(gGlProcs.ValidateProgramPipeline, "glValidateProgramPipeline");
	Loader.loadGlArbSymbol(gGlProcs.GetProgramPipelineInfoLog, "glGetProgramPipelineInfoLog");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribL1d, "glVertexAttribL1d");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribL2d, "glVertexAttribL2d");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribL3d, "glVertexAttribL3d");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribL4d, "glVertexAttribL4d");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribL1dv, "glVertexAttribL1dv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribL2dv, "glVertexAttribL2dv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribL3dv, "glVertexAttribL3dv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribL4dv, "glVertexAttribL4dv");
	Loader.loadGlArbSymbol(gGlProcs.VertexAttribLPointer, "glVertexAttribLPointer");
	Loader.loadGlArbSymbol(gGlProcs.GetVertexAttribLdv, "glGetVertexAttribLdv");
	Loader.loadGlArbSymbol(gGlProcs.ViewportArrayv, "glViewportArrayv");
	Loader.loadGlArbSymbol(gGlProcs.ViewportIndexedf, "glViewportIndexedf");
	Loader.loadGlArbSymbol(gGlProcs.ViewportIndexedfv, "glViewportIndexedfv");
	Loader.loadGlArbSymbol(gGlProcs.ScissorArrayv, "glScissorArrayv");
	Loader.loadGlArbSymbol(gGlProcs.ScissorIndexed, "glScissorIndexed");
	Loader.loadGlArbSymbol(gGlProcs.ScissorIndexedv, "glScissorIndexedv");
	Loader.loadGlArbSymbol(gGlProcs.DepthRangeArrayv, "glDepthRangeArrayv");
	Loader.loadGlArbSymbol(gGlProcs.DepthRangeIndexed, "glDepthRangeIndexed");
	Loader.loadGlArbSymbol(gGlProcs.GetFloati_v, "glGetFloati_v");
	Loader.loadGlArbSymbol(gGlProcs.GetDoublei_v, "glGetDoublei_v");
	Loader.loadGlArbSymbol(gGlProcs.CreateSyncFromCLeventARB, "glCreateSyncFromCLeventARB");
	Loader.loadGlArbSymbol(gGlProcs.DebugMessageControlARB, "glDebugMessageControlARB");
	Loader.loadGlArbSymbol(gGlProcs.DebugMessageInsertARB, "glDebugMessageInsertARB");
	Loader.loadGlArbSymbol(gGlProcs.DebugMessageCallbackARB, "glDebugMessageCallbackARB");
	Loader.loadGlArbSymbol(gGlProcs.GetDebugMessageLogARB, "glGetDebugMessageLogARB");
	Loader.loadGlArbSymbol(gGlProcs.GetGraphicsResetStatusARB, "glGetGraphicsResetStatusARB");
	Loader.loadGlArbSymbol(gGlProcs.GetnMapdvARB, "glGetnMapdvARB");
	Loader.loadGlArbSymbol(gGlProcs.GetnMapfvARB, "glGetnMapfvARB");
	Loader.loadGlArbSymbol(gGlProcs.GetnMapivARB, "glGetnMapivARB");
	Loader.loadGlArbSymbol(gGlProcs.GetnPixelMapfvARB, "glGetnPixelMapfvARB");
	Loader.loadGlArbSymbol(gGlProcs.GetnPixelMapuivARB, "glGetnPixelMapuivARB");
	Loader.loadGlArbSymbol(gGlProcs.GetnPixelMapusvARB, "glGetnPixelMapusvARB");
	Loader.loadGlArbSymbol(gGlProcs.GetnPolygonStippleARB, "glGetnPolygonStippleARB");
	Loader.loadGlArbSymbol(gGlProcs.GetnColorTableARB, "glGetnColorTableARB");
	Loader.loadGlArbSymbol(gGlProcs.GetnConvolutionFilterARB, "glGetnConvolutionFilterARB");
	Loader.loadGlArbSymbol(gGlProcs.GetnSeparableFilterARB, "glGetnSeparableFilterARB");
	Loader.loadGlArbSymbol(gGlProcs.GetnHistogramARB, "glGetnHistogramARB");
	Loader.loadGlArbSymbol(gGlProcs.GetnMinmaxARB, "glGetnMinmaxARB");
	Loader.loadGlArbSymbol(gGlProcs.GetnTexImageARB, "glGetnTexImageARB");
	Loader.loadGlArbSymbol(gGlProcs.ReadnPixelsARB, "glReadnPixelsARB");
	Loader.loadGlArbSymbol(gGlProcs.GetnCompressedTexImageARB, "glGetnCompressedTexImageARB");
	Loader.loadGlArbSymbol(gGlProcs.GetnUniformfvARB, "glGetnUniformfvARB");
	Loader.loadGlArbSymbol(gGlProcs.GetnUniformivARB, "glGetnUniformivARB");
	Loader.loadGlArbSymbol(gGlProcs.GetnUniformuivARB, "glGetnUniformuivARB");
	Loader.loadGlArbSymbol(gGlProcs.GetnUniformdvARB, "glGetnUniformdvARB");
	Loader.loadGlArbSymbol(gGlProcs.DrawArraysInstancedBaseInstance, "glDrawArraysInstancedBaseInstance");
	Loader.loadGlArbSymbol(gGlProcs.DrawElementsInstancedBaseInstance, "glDrawElementsInstancedBaseInstance");
	Loader.loadGlArbSymbol(gGlProcs.DrawElementsInstancedBaseVertexBaseInstance, "glDrawElementsInstancedBaseVertexBaseInstance");
	Loader.loadGlArbSymbol(gGlProcs.DrawTransformFeedbackInstanced, "glDrawTransformFeedbackInstanced");
	Loader.loadGlArbSymbol(gGlProcs.DrawTransformFeedbackStreamInstanced, "glDrawTransformFeedbackStreamInstanced");
	Loader.loadGlArbSymbol(gGlProcs.GetInternalformativ, "glGetInternalformativ");
	Loader.loadGlArbSymbol(gGlProcs.GetActiveAtomicCounterBufferiv, "glGetActiveAtomicCounterBufferiv");
	Loader.loadGlArbSymbol(gGlProcs.BindImageTexture, "glBindImageTexture");
	Loader.loadGlArbSymbol(gGlProcs.MemoryBarrier, "glMemoryBarrier");
	Loader.loadGlArbSymbol(gGlProcs.TexStorage1D, "glTexStorage1D");
	Loader.loadGlArbSymbol(gGlProcs.TexStorage2D, "glTexStorage2D");
	Loader.loadGlArbSymbol(gGlProcs.TexStorage3D, "glTexStorage3D");
	Loader.loadGlArbSymbol(gGlProcs.TextureStorage1DEXT, "glTextureStorage1DEXT");
	Loader.loadGlArbSymbol(gGlProcs.TextureStorage2DEXT, "glTextureStorage2DEXT");
	Loader.loadGlArbSymbol(gGlProcs.TextureStorage3DEXT, "glTextureStorage3DEXT");
}
}

}
}

extern "C" {

void glCullFace(GLenum mode)
{
	gGlProcs.CullFace(mode);
	checkError();
}

void glFrontFace(GLenum mode)
{
	gGlProcs.FrontFace(mode);
	checkError();
}

void glHint(GLenum target, GLenum mode)
{
	gGlProcs.Hint(target, mode);
	checkError();
}

void glLineWidth(GLfloat width)
{
	gGlProcs.LineWidth(width);
	checkError();
}

void glPointSize(GLfloat size)
{
	gGlProcs.PointSize(size);
	checkError();
}

void glPolygonMode(GLenum face, GLenum mode)
{
	gGlProcs.PolygonMode(face, mode);
	checkError();
}

void glScissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
	gGlProcs.Scissor(x, y, width, height);
	checkError();
}

void glTexParameterf(GLenum target, GLenum pname, GLfloat param)
{
	gGlProcs.TexParameterf(target, pname, param);
	checkError();
}

void glTexParameterfv(GLenum target, GLenum pname, GLfloat const * params)
{
	gGlProcs.TexParameterfv(target, pname, params);
	checkError();
}

void glTexParameteri(GLenum target, GLenum pname, GLint param)
{
	gGlProcs.TexParameteri(target, pname, param);
	checkError();
}

void glTexParameteriv(GLenum target, GLenum pname, GLint const * params)
{
	gGlProcs.TexParameteriv(target, pname, params);
	checkError();
}

void glTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, GLvoid const * pixels)
{
	gGlProcs.TexImage1D(target, level, internalformat, width, border, format, type, pixels);
	checkError();
}

void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, GLvoid const * pixels)
{
	gGlProcs.TexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
	checkError();
}

void glDrawBuffer(GLenum mode)
{
	gGlProcs.DrawBuffer(mode);
	checkError();
}

void glClear(GLbitfield mask)
{
	gGlProcs.Clear(mask);
	checkError();
}

void glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	gGlProcs.ClearColor(red, green, blue, alpha);
	checkError();
}

void glClearStencil(GLint s)
{
	gGlProcs.ClearStencil(s);
	checkError();
}

void glClearDepth(GLclampd depth)
{
	gGlProcs.ClearDepth(depth);
	checkError();
}

void glStencilMask(GLuint mask)
{
	gGlProcs.StencilMask(mask);
	checkError();
}

void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	gGlProcs.ColorMask(red, green, blue, alpha);
	checkError();
}

void glDepthMask(GLboolean flag)
{
	gGlProcs.DepthMask(flag);
	checkError();
}

void glDisable(GLenum cap)
{
	gGlProcs.Disable(cap);
	checkError();
}

void glEnable(GLenum cap)
{
	gGlProcs.Enable(cap);
	checkError();
}

void glFinish()
{
	gGlProcs.Finish();
	checkError();
}

void glFlush()
{
	gGlProcs.Flush();
	checkError();
}

void glBlendFunc(GLenum sfactor, GLenum dfactor)
{
	gGlProcs.BlendFunc(sfactor, dfactor);
	checkError();
}

void glLogicOp(GLenum opcode)
{
	gGlProcs.LogicOp(opcode);
	checkError();
}

void glStencilFunc(GLenum func, GLint ref, GLuint mask)
{
	gGlProcs.StencilFunc(func, ref, mask);
	checkError();
}

void glStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
{
	gGlProcs.StencilOp(fail, zfail, zpass);
	checkError();
}

void glDepthFunc(GLenum func)
{
	gGlProcs.DepthFunc(func);
	checkError();
}

void glPixelStoref(GLenum pname, GLfloat param)
{
	gGlProcs.PixelStoref(pname, param);
	checkError();
}

void glPixelStorei(GLenum pname, GLint param)
{
	gGlProcs.PixelStorei(pname, param);
	checkError();
}

void glReadBuffer(GLenum mode)
{
	gGlProcs.ReadBuffer(mode);
	checkError();
}

void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid * pixels)
{
	gGlProcs.ReadPixels(x, y, width, height, format, type, pixels);
	checkError();
}

void glGetBooleanv(GLenum pname, GLboolean * params)
{
	gGlProcs.GetBooleanv(pname, params);
	checkError();
}

void glGetDoublev(GLenum pname, GLdouble * params)
{
	gGlProcs.GetDoublev(pname, params);
	checkError();
}

GLenum glGetError()
{
	auto result = gGlProcs.GetError();
	checkError();
	return result;
}

void glGetFloatv(GLenum pname, GLfloat * params)
{
	gGlProcs.GetFloatv(pname, params);
	checkError();
}

void glGetIntegerv(GLenum pname, GLint * params)
{
	gGlProcs.GetIntegerv(pname, params);
	checkError();
}

GLubyte const * glGetString(GLenum name)
{
	auto result = gGlProcs.GetString(name);
	checkError();
	return result;
}

void glGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLvoid * pixels)
{
	gGlProcs.GetTexImage(target, level, format, type, pixels);
	checkError();
}

void glGetTexParameterfv(GLenum target, GLenum pname, GLfloat * params)
{
	gGlProcs.GetTexParameterfv(target, pname, params);
	checkError();
}

void glGetTexParameteriv(GLenum target, GLenum pname, GLint * params)
{
	gGlProcs.GetTexParameteriv(target, pname, params);
	checkError();
}

void glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat * params)
{
	gGlProcs.GetTexLevelParameterfv(target, level, pname, params);
	checkError();
}

void glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint * params)
{
	gGlProcs.GetTexLevelParameteriv(target, level, pname, params);
	checkError();
}

GLboolean glIsEnabled(GLenum cap)
{
	auto result = gGlProcs.IsEnabled(cap);
	checkError();
	return result;
}

void glDepthRange(GLclampd near, GLclampd far)
{
	gGlProcs.DepthRange(near, far);
	checkError();
}

void glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	gGlProcs.Viewport(x, y, width, height);
	checkError();
}

void glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
	gGlProcs.DrawArrays(mode, first, count);
	checkError();
}

void glDrawElements(GLenum mode, GLsizei count, GLenum type, GLvoid const * indices)
{
	gGlProcs.DrawElements(mode, count, type, indices);
	checkError();
}

void glGetPointerv(GLenum pname, GLvoid * * params)
{
	gGlProcs.GetPointerv(pname, params);
	checkError();
}

void glPolygonOffset(GLfloat factor, GLfloat units)
{
	gGlProcs.PolygonOffset(factor, units);
	checkError();
}

void glCopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border)
{
	gGlProcs.CopyTexImage1D(target, level, internalformat, x, y, width, border);
	checkError();
}

void glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
	gGlProcs.CopyTexImage2D(target, level, internalformat, x, y, width, height, border);
	checkError();
}

void glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
{
	gGlProcs.CopyTexSubImage1D(target, level, xoffset, x, y, width);
	checkError();
}

void glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	gGlProcs.CopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
	checkError();
}

void glTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, GLvoid const * pixels)
{
	gGlProcs.TexSubImage1D(target, level, xoffset, width, format, type, pixels);
	checkError();
}

void glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid const * pixels)
{
	gGlProcs.TexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
	checkError();
}

void glBindTexture(GLenum target, GLuint texture)
{
	gGlProcs.BindTexture(target, texture);
	checkError();
}

void glDeleteTextures(GLsizei n, GLuint const * textures)
{
	gGlProcs.DeleteTextures(n, textures);
	checkError();
}

void glGenTextures(GLsizei n, GLuint * textures)
{
	gGlProcs.GenTextures(n, textures);
	checkError();
}

GLboolean glIsTexture(GLuint texture)
{
	auto result = gGlProcs.IsTexture(texture);
	checkError();
	return result;
}

void glBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	gGlProcs.BlendColor(red, green, blue, alpha);
	checkError();
}

void glBlendEquation(GLenum mode)
{
	gGlProcs.BlendEquation(mode);
	checkError();
}

void glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, GLvoid const * indices)
{
	gGlProcs.DrawRangeElements(mode, start, end, count, type, indices);
	checkError();
}

void glTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, GLvoid const * pixels)
{
	gGlProcs.TexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
	checkError();
}

void glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLvoid const * pixels)
{
	gGlProcs.TexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
	checkError();
}

void glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	gGlProcs.CopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
	checkError();
}

void glActiveTexture(GLenum texture)
{
	gGlProcs.ActiveTexture(texture);
	checkError();
}

void glSampleCoverage(GLclampf value, GLboolean invert)
{
	gGlProcs.SampleCoverage(value, invert);
	checkError();
}

void glCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, GLvoid const * data)
{
	gGlProcs.CompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
	checkError();
}

void glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, GLvoid const * data)
{
	gGlProcs.CompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
	checkError();
}

void glCompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, GLvoid const * data)
{
	gGlProcs.CompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);
	checkError();
}

void glCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, GLvoid const * data)
{
	gGlProcs.CompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
	checkError();
}

void glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, GLvoid const * data)
{
	gGlProcs.CompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
	checkError();
}

void glCompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, GLvoid const * data)
{
	gGlProcs.CompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
	checkError();
}

void glGetCompressedTexImage(GLenum target, GLint level, GLvoid * img)
{
	gGlProcs.GetCompressedTexImage(target, level, img);
	checkError();
}

void glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
{
	gGlProcs.BlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
	checkError();
}

void glMultiDrawArrays(GLenum mode, GLint const * first, GLsizei const * count, GLsizei primcount)
{
	gGlProcs.MultiDrawArrays(mode, first, count, primcount);
	checkError();
}

void glMultiDrawElements(GLenum mode, GLsizei const * count, GLenum type, GLvoid const * * indices, GLsizei primcount)
{
	gGlProcs.MultiDrawElements(mode, count, type, indices, primcount);
	checkError();
}

void glPointParameterf(GLenum pname, GLfloat param)
{
	gGlProcs.PointParameterf(pname, param);
	checkError();
}

void glPointParameterfv(GLenum pname, GLfloat const * params)
{
	gGlProcs.PointParameterfv(pname, params);
	checkError();
}

void glPointParameteri(GLenum pname, GLint param)
{
	gGlProcs.PointParameteri(pname, param);
	checkError();
}

void glPointParameteriv(GLenum pname, GLint const * params)
{
	gGlProcs.PointParameteriv(pname, params);
	checkError();
}

void glGenQueries(GLsizei n, GLuint * ids)
{
	gGlProcs.GenQueries(n, ids);
	checkError();
}

void glDeleteQueries(GLsizei n, GLuint const * ids)
{
	gGlProcs.DeleteQueries(n, ids);
	checkError();
}

GLboolean glIsQuery(GLuint id)
{
	auto result = gGlProcs.IsQuery(id);
	checkError();
	return result;
}

void glBeginQuery(GLenum target, GLuint id)
{
	gGlProcs.BeginQuery(target, id);
	checkError();
}

void glEndQuery(GLenum target)
{
	gGlProcs.EndQuery(target);
	checkError();
}

void glGetQueryiv(GLenum target, GLenum pname, GLint * params)
{
	gGlProcs.GetQueryiv(target, pname, params);
	checkError();
}

void glGetQueryObjectiv(GLuint id, GLenum pname, GLint * params)
{
	gGlProcs.GetQueryObjectiv(id, pname, params);
	checkError();
}

void glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint * params)
{
	gGlProcs.GetQueryObjectuiv(id, pname, params);
	checkError();
}

void glBindBuffer(GLenum target, GLuint buffer)
{
	gGlProcs.BindBuffer(target, buffer);
	checkError();
}

void glDeleteBuffers(GLsizei n, GLuint const * buffers)
{
	gGlProcs.DeleteBuffers(n, buffers);
	checkError();
}

void glGenBuffers(GLsizei n, GLuint * buffers)
{
	gGlProcs.GenBuffers(n, buffers);
	checkError();
}

GLboolean glIsBuffer(GLuint buffer)
{
	auto result = gGlProcs.IsBuffer(buffer);
	checkError();
	return result;
}

void glBufferData(GLenum target, GLsizeiptr size, GLvoid const * data, GLenum usage)
{
	gGlProcs.BufferData(target, size, data, usage);
	checkError();
}

void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid const * data)
{
	gGlProcs.BufferSubData(target, offset, size, data);
	checkError();
}

void glGetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid * data)
{
	gGlProcs.GetBufferSubData(target, offset, size, data);
	checkError();
}

GLvoid * glMapBuffer(GLenum target, GLenum access)
{
	auto result = gGlProcs.MapBuffer(target, access);
	checkError();
	return result;
}

GLboolean glUnmapBuffer(GLenum target)
{
	auto result = gGlProcs.UnmapBuffer(target);
	checkError();
	return result;
}

void glGetBufferParameteriv(GLenum target, GLenum pname, GLint * params)
{
	gGlProcs.GetBufferParameteriv(target, pname, params);
	checkError();
}

void glGetBufferPointerv(GLenum target, GLenum pname, GLvoid * * params)
{
	gGlProcs.GetBufferPointerv(target, pname, params);
	checkError();
}

void glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
	gGlProcs.BlendEquationSeparate(modeRGB, modeAlpha);
	checkError();
}

void glDrawBuffers(GLsizei n, GLenum const * bufs)
{
	gGlProcs.DrawBuffers(n, bufs);
	checkError();
}

void glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass)
{
	gGlProcs.StencilOpSeparate(face, sfail, dpfail, dppass);
	checkError();
}

void glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
{
	gGlProcs.StencilFuncSeparate(face, func, ref, mask);
	checkError();
}

void glStencilMaskSeparate(GLenum face, GLuint mask)
{
	gGlProcs.StencilMaskSeparate(face, mask);
	checkError();
}

void glAttachShader(GLuint program, GLuint shader)
{
	gGlProcs.AttachShader(program, shader);
	checkError();
}

void glBindAttribLocation(GLuint program, GLuint index, GLchar const * name)
{
	gGlProcs.BindAttribLocation(program, index, name);
	checkError();
}

void glCompileShader(GLuint shader)
{
	gGlProcs.CompileShader(shader);
	checkError();
}

GLuint glCreateProgram()
{
	auto result = gGlProcs.CreateProgram();
	checkError();
	return result;
}

GLuint glCreateShader(GLenum type)
{
	auto result = gGlProcs.CreateShader(type);
	checkError();
	return result;
}

void glDeleteProgram(GLuint program)
{
	gGlProcs.DeleteProgram(program);
	checkError();
}

void glDeleteShader(GLuint shader)
{
	gGlProcs.DeleteShader(shader);
	checkError();
}

void glDetachShader(GLuint program, GLuint shader)
{
	gGlProcs.DetachShader(program, shader);
	checkError();
}

void glDisableVertexAttribArray(GLuint index)
{
	gGlProcs.DisableVertexAttribArray(index);
	checkError();
}

void glEnableVertexAttribArray(GLuint index)
{
	gGlProcs.EnableVertexAttribArray(index);
	checkError();
}

void glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name)
{
	gGlProcs.GetActiveAttrib(program, index, bufSize, length, size, type, name);
	checkError();
}

void glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name)
{
	gGlProcs.GetActiveUniform(program, index, bufSize, length, size, type, name);
	checkError();
}

void glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * obj)
{
	gGlProcs.GetAttachedShaders(program, maxCount, count, obj);
	checkError();
}

GLint glGetAttribLocation(GLuint program, GLchar const * name)
{
	auto result = gGlProcs.GetAttribLocation(program, name);
	checkError();
	return result;
}

void glGetProgramiv(GLuint program, GLenum pname, GLint * params)
{
	gGlProcs.GetProgramiv(program, pname, params);
	checkError();
}

void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
{
	gGlProcs.GetProgramInfoLog(program, bufSize, length, infoLog);
	checkError();
}

void glGetShaderiv(GLuint shader, GLenum pname, GLint * params)
{
	gGlProcs.GetShaderiv(shader, pname, params);
	checkError();
}

void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
{
	gGlProcs.GetShaderInfoLog(shader, bufSize, length, infoLog);
	checkError();
}

void glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source)
{
	gGlProcs.GetShaderSource(shader, bufSize, length, source);
	checkError();
}

GLint glGetUniformLocation(GLuint program, GLchar const * name)
{
	auto result = gGlProcs.GetUniformLocation(program, name);
	checkError();
	return result;
}

void glGetUniformfv(GLuint program, GLint location, GLfloat * params)
{
	gGlProcs.GetUniformfv(program, location, params);
	checkError();
}

void glGetUniformiv(GLuint program, GLint location, GLint * params)
{
	gGlProcs.GetUniformiv(program, location, params);
	checkError();
}

void glGetVertexAttribdv(GLuint index, GLenum pname, GLdouble * params)
{
	gGlProcs.GetVertexAttribdv(index, pname, params);
	checkError();
}

void glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat * params)
{
	gGlProcs.GetVertexAttribfv(index, pname, params);
	checkError();
}

void glGetVertexAttribiv(GLuint index, GLenum pname, GLint * params)
{
	gGlProcs.GetVertexAttribiv(index, pname, params);
	checkError();
}

void glGetVertexAttribPointerv(GLuint index, GLenum pname, GLvoid * * pointer)
{
	gGlProcs.GetVertexAttribPointerv(index, pname, pointer);
	checkError();
}

GLboolean glIsProgram(GLuint program)
{
	auto result = gGlProcs.IsProgram(program);
	checkError();
	return result;
}

GLboolean glIsShader(GLuint shader)
{
	auto result = gGlProcs.IsShader(shader);
	checkError();
	return result;
}

void glLinkProgram(GLuint program)
{
	gGlProcs.LinkProgram(program);
	checkError();
}

void glShaderSource(GLuint shader, GLsizei count, GLchar const * * string, GLint const * length)
{
	gGlProcs.ShaderSource(shader, count, string, length);
	checkError();
}

void glUseProgram(GLuint program)
{
	gGlProcs.UseProgram(program);
	checkError();
}

void glUniform1f(GLint location, GLfloat v0)
{
	gGlProcs.Uniform1f(location, v0);
	checkError();
}

void glUniform2f(GLint location, GLfloat v0, GLfloat v1)
{
	gGlProcs.Uniform2f(location, v0, v1);
	checkError();
}

void glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
	gGlProcs.Uniform3f(location, v0, v1, v2);
	checkError();
}

void glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	gGlProcs.Uniform4f(location, v0, v1, v2, v3);
	checkError();
}

void glUniform1i(GLint location, GLint v0)
{
	gGlProcs.Uniform1i(location, v0);
	checkError();
}

void glUniform2i(GLint location, GLint v0, GLint v1)
{
	gGlProcs.Uniform2i(location, v0, v1);
	checkError();
}

void glUniform3i(GLint location, GLint v0, GLint v1, GLint v2)
{
	gGlProcs.Uniform3i(location, v0, v1, v2);
	checkError();
}

void glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
	gGlProcs.Uniform4i(location, v0, v1, v2, v3);
	checkError();
}

void glUniform1fv(GLint location, GLsizei count, GLfloat const * value)
{
	gGlProcs.Uniform1fv(location, count, value);
	checkError();
}

void glUniform2fv(GLint location, GLsizei count, GLfloat const * value)
{
	gGlProcs.Uniform2fv(location, count, value);
	checkError();
}

void glUniform3fv(GLint location, GLsizei count, GLfloat const * value)
{
	gGlProcs.Uniform3fv(location, count, value);
	checkError();
}

void glUniform4fv(GLint location, GLsizei count, GLfloat const * value)
{
	gGlProcs.Uniform4fv(location, count, value);
	checkError();
}

void glUniform1iv(GLint location, GLsizei count, GLint const * value)
{
	gGlProcs.Uniform1iv(location, count, value);
	checkError();
}

void glUniform2iv(GLint location, GLsizei count, GLint const * value)
{
	gGlProcs.Uniform2iv(location, count, value);
	checkError();
}

void glUniform3iv(GLint location, GLsizei count, GLint const * value)
{
	gGlProcs.Uniform3iv(location, count, value);
	checkError();
}

void glUniform4iv(GLint location, GLsizei count, GLint const * value)
{
	gGlProcs.Uniform4iv(location, count, value);
	checkError();
}

void glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gGlProcs.UniformMatrix2fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gGlProcs.UniformMatrix3fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gGlProcs.UniformMatrix4fv(location, count, transpose, value);
	checkError();
}

void glValidateProgram(GLuint program)
{
	gGlProcs.ValidateProgram(program);
	checkError();
}

void glVertexAttrib1d(GLuint index, GLdouble x)
{
	gGlProcs.VertexAttrib1d(index, x);
	checkError();
}

void glVertexAttrib1dv(GLuint index, GLdouble const * v)
{
	gGlProcs.VertexAttrib1dv(index, v);
	checkError();
}

void glVertexAttrib1f(GLuint index, GLfloat x)
{
	gGlProcs.VertexAttrib1f(index, x);
	checkError();
}

void glVertexAttrib1fv(GLuint index, GLfloat const * v)
{
	gGlProcs.VertexAttrib1fv(index, v);
	checkError();
}

void glVertexAttrib1s(GLuint index, GLshort x)
{
	gGlProcs.VertexAttrib1s(index, x);
	checkError();
}

void glVertexAttrib1sv(GLuint index, GLshort const * v)
{
	gGlProcs.VertexAttrib1sv(index, v);
	checkError();
}

void glVertexAttrib2d(GLuint index, GLdouble x, GLdouble y)
{
	gGlProcs.VertexAttrib2d(index, x, y);
	checkError();
}

void glVertexAttrib2dv(GLuint index, GLdouble const * v)
{
	gGlProcs.VertexAttrib2dv(index, v);
	checkError();
}

void glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y)
{
	gGlProcs.VertexAttrib2f(index, x, y);
	checkError();
}

void glVertexAttrib2fv(GLuint index, GLfloat const * v)
{
	gGlProcs.VertexAttrib2fv(index, v);
	checkError();
}

void glVertexAttrib2s(GLuint index, GLshort x, GLshort y)
{
	gGlProcs.VertexAttrib2s(index, x, y);
	checkError();
}

void glVertexAttrib2sv(GLuint index, GLshort const * v)
{
	gGlProcs.VertexAttrib2sv(index, v);
	checkError();
}

void glVertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z)
{
	gGlProcs.VertexAttrib3d(index, x, y, z);
	checkError();
}

void glVertexAttrib3dv(GLuint index, GLdouble const * v)
{
	gGlProcs.VertexAttrib3dv(index, v);
	checkError();
}

void glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z)
{
	gGlProcs.VertexAttrib3f(index, x, y, z);
	checkError();
}

void glVertexAttrib3fv(GLuint index, GLfloat const * v)
{
	gGlProcs.VertexAttrib3fv(index, v);
	checkError();
}

void glVertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z)
{
	gGlProcs.VertexAttrib3s(index, x, y, z);
	checkError();
}

void glVertexAttrib3sv(GLuint index, GLshort const * v)
{
	gGlProcs.VertexAttrib3sv(index, v);
	checkError();
}

void glVertexAttrib4Nbv(GLuint index, GLbyte const * v)
{
	gGlProcs.VertexAttrib4Nbv(index, v);
	checkError();
}

void glVertexAttrib4Niv(GLuint index, GLint const * v)
{
	gGlProcs.VertexAttrib4Niv(index, v);
	checkError();
}

void glVertexAttrib4Nsv(GLuint index, GLshort const * v)
{
	gGlProcs.VertexAttrib4Nsv(index, v);
	checkError();
}

void glVertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w)
{
	gGlProcs.VertexAttrib4Nub(index, x, y, z, w);
	checkError();
}

void glVertexAttrib4Nubv(GLuint index, GLubyte const * v)
{
	gGlProcs.VertexAttrib4Nubv(index, v);
	checkError();
}

void glVertexAttrib4Nuiv(GLuint index, GLuint const * v)
{
	gGlProcs.VertexAttrib4Nuiv(index, v);
	checkError();
}

void glVertexAttrib4Nusv(GLuint index, GLushort const * v)
{
	gGlProcs.VertexAttrib4Nusv(index, v);
	checkError();
}

void glVertexAttrib4bv(GLuint index, GLbyte const * v)
{
	gGlProcs.VertexAttrib4bv(index, v);
	checkError();
}

void glVertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	gGlProcs.VertexAttrib4d(index, x, y, z, w);
	checkError();
}

void glVertexAttrib4dv(GLuint index, GLdouble const * v)
{
	gGlProcs.VertexAttrib4dv(index, v);
	checkError();
}

void glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	gGlProcs.VertexAttrib4f(index, x, y, z, w);
	checkError();
}

void glVertexAttrib4fv(GLuint index, GLfloat const * v)
{
	gGlProcs.VertexAttrib4fv(index, v);
	checkError();
}

void glVertexAttrib4iv(GLuint index, GLint const * v)
{
	gGlProcs.VertexAttrib4iv(index, v);
	checkError();
}

void glVertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w)
{
	gGlProcs.VertexAttrib4s(index, x, y, z, w);
	checkError();
}

void glVertexAttrib4sv(GLuint index, GLshort const * v)
{
	gGlProcs.VertexAttrib4sv(index, v);
	checkError();
}

void glVertexAttrib4ubv(GLuint index, GLubyte const * v)
{
	gGlProcs.VertexAttrib4ubv(index, v);
	checkError();
}

void glVertexAttrib4uiv(GLuint index, GLuint const * v)
{
	gGlProcs.VertexAttrib4uiv(index, v);
	checkError();
}

void glVertexAttrib4usv(GLuint index, GLushort const * v)
{
	gGlProcs.VertexAttrib4usv(index, v);
	checkError();
}

void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid const * pointer)
{
	gGlProcs.VertexAttribPointer(index, size, type, normalized, stride, pointer);
	checkError();
}

void glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gGlProcs.UniformMatrix2x3fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gGlProcs.UniformMatrix3x2fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gGlProcs.UniformMatrix2x4fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gGlProcs.UniformMatrix4x2fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gGlProcs.UniformMatrix3x4fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gGlProcs.UniformMatrix4x3fv(location, count, transpose, value);
	checkError();
}

void glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a)
{
	gGlProcs.ColorMaski(index, r, g, b, a);
	checkError();
}

void glGetBooleani_v(GLenum target, GLuint index, GLboolean * data)
{
	gGlProcs.GetBooleani_v(target, index, data);
	checkError();
}

void glGetIntegeri_v(GLenum target, GLuint index, GLint * data)
{
	gGlProcs.GetIntegeri_v(target, index, data);
	checkError();
}

void glEnablei(GLenum target, GLuint index)
{
	gGlProcs.Enablei(target, index);
	checkError();
}

void glDisablei(GLenum target, GLuint index)
{
	gGlProcs.Disablei(target, index);
	checkError();
}

GLboolean glIsEnabledi(GLenum target, GLuint index)
{
	auto result = gGlProcs.IsEnabledi(target, index);
	checkError();
	return result;
}

void glBeginTransformFeedback(GLenum primitiveMode)
{
	gGlProcs.BeginTransformFeedback(primitiveMode);
	checkError();
}

void glEndTransformFeedback(void)
{
	gGlProcs.EndTransformFeedback();
	checkError();
}

void glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
	gGlProcs.BindBufferRange(target, index, buffer, offset, size);
	checkError();
}

void glBindBufferBase(GLenum target, GLuint index, GLuint buffer)
{
	gGlProcs.BindBufferBase(target, index, buffer);
	checkError();
}

void glTransformFeedbackVaryings(GLuint program, GLsizei count, GLchar const * * varyings, GLenum bufferMode)
{
	gGlProcs.TransformFeedbackVaryings(program, count, varyings, bufferMode);
	checkError();
}

void glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name)
{
	gGlProcs.GetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
	checkError();
}

void glClampColor(GLenum target, GLenum clamp)
{
	gGlProcs.ClampColor(target, clamp);
	checkError();
}

void glBeginConditionalRender(GLuint id, GLenum mode)
{
	gGlProcs.BeginConditionalRender(id, mode);
	checkError();
}

void glEndConditionalRender(void)
{
	gGlProcs.EndConditionalRender();
	checkError();
}

void glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, GLvoid const * pointer)
{
	gGlProcs.VertexAttribIPointer(index, size, type, stride, pointer);
	checkError();
}

void glGetVertexAttribIiv(GLuint index, GLenum pname, GLint * params)
{
	gGlProcs.GetVertexAttribIiv(index, pname, params);
	checkError();
}

void glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint * params)
{
	gGlProcs.GetVertexAttribIuiv(index, pname, params);
	checkError();
}

void glVertexAttribI1i(GLuint index, GLint x)
{
	gGlProcs.VertexAttribI1i(index, x);
	checkError();
}

void glVertexAttribI2i(GLuint index, GLint x, GLint y)
{
	gGlProcs.VertexAttribI2i(index, x, y);
	checkError();
}

void glVertexAttribI3i(GLuint index, GLint x, GLint y, GLint z)
{
	gGlProcs.VertexAttribI3i(index, x, y, z);
	checkError();
}

void glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w)
{
	gGlProcs.VertexAttribI4i(index, x, y, z, w);
	checkError();
}

void glVertexAttribI1ui(GLuint index, GLuint x)
{
	gGlProcs.VertexAttribI1ui(index, x);
	checkError();
}

void glVertexAttribI2ui(GLuint index, GLuint x, GLuint y)
{
	gGlProcs.VertexAttribI2ui(index, x, y);
	checkError();
}

void glVertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z)
{
	gGlProcs.VertexAttribI3ui(index, x, y, z);
	checkError();
}

void glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)
{
	gGlProcs.VertexAttribI4ui(index, x, y, z, w);
	checkError();
}

void glVertexAttribI1iv(GLuint index, GLint const * v)
{
	gGlProcs.VertexAttribI1iv(index, v);
	checkError();
}

void glVertexAttribI2iv(GLuint index, GLint const * v)
{
	gGlProcs.VertexAttribI2iv(index, v);
	checkError();
}

void glVertexAttribI3iv(GLuint index, GLint const * v)
{
	gGlProcs.VertexAttribI3iv(index, v);
	checkError();
}

void glVertexAttribI4iv(GLuint index, GLint const * v)
{
	gGlProcs.VertexAttribI4iv(index, v);
	checkError();
}

void glVertexAttribI1uiv(GLuint index, GLuint const * v)
{
	gGlProcs.VertexAttribI1uiv(index, v);
	checkError();
}

void glVertexAttribI2uiv(GLuint index, GLuint const * v)
{
	gGlProcs.VertexAttribI2uiv(index, v);
	checkError();
}

void glVertexAttribI3uiv(GLuint index, GLuint const * v)
{
	gGlProcs.VertexAttribI3uiv(index, v);
	checkError();
}

void glVertexAttribI4uiv(GLuint index, GLuint const * v)
{
	gGlProcs.VertexAttribI4uiv(index, v);
	checkError();
}

void glVertexAttribI4bv(GLuint index, GLbyte const * v)
{
	gGlProcs.VertexAttribI4bv(index, v);
	checkError();
}

void glVertexAttribI4sv(GLuint index, GLshort const * v)
{
	gGlProcs.VertexAttribI4sv(index, v);
	checkError();
}

void glVertexAttribI4ubv(GLuint index, GLubyte const * v)
{
	gGlProcs.VertexAttribI4ubv(index, v);
	checkError();
}

void glVertexAttribI4usv(GLuint index, GLushort const * v)
{
	gGlProcs.VertexAttribI4usv(index, v);
	checkError();
}

void glGetUniformuiv(GLuint program, GLint location, GLuint * params)
{
	gGlProcs.GetUniformuiv(program, location, params);
	checkError();
}

void glBindFragDataLocation(GLuint program, GLuint color, GLchar const * name)
{
	gGlProcs.BindFragDataLocation(program, color, name);
	checkError();
}

GLint glGetFragDataLocation(GLuint program, GLchar const * name)
{
	auto result = gGlProcs.GetFragDataLocation(program, name);
	checkError();
	return result;
}

void glUniform1ui(GLint location, GLuint v0)
{
	gGlProcs.Uniform1ui(location, v0);
	checkError();
}

void glUniform2ui(GLint location, GLuint v0, GLuint v1)
{
	gGlProcs.Uniform2ui(location, v0, v1);
	checkError();
}

void glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2)
{
	gGlProcs.Uniform3ui(location, v0, v1, v2);
	checkError();
}

void glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	gGlProcs.Uniform4ui(location, v0, v1, v2, v3);
	checkError();
}

void glUniform1uiv(GLint location, GLsizei count, GLuint const * value)
{
	gGlProcs.Uniform1uiv(location, count, value);
	checkError();
}

void glUniform2uiv(GLint location, GLsizei count, GLuint const * value)
{
	gGlProcs.Uniform2uiv(location, count, value);
	checkError();
}

void glUniform3uiv(GLint location, GLsizei count, GLuint const * value)
{
	gGlProcs.Uniform3uiv(location, count, value);
	checkError();
}

void glUniform4uiv(GLint location, GLsizei count, GLuint const * value)
{
	gGlProcs.Uniform4uiv(location, count, value);
	checkError();
}

void glTexParameterIiv(GLenum target, GLenum pname, GLint const * params)
{
	gGlProcs.TexParameterIiv(target, pname, params);
	checkError();
}

void glTexParameterIuiv(GLenum target, GLenum pname, GLuint const * params)
{
	gGlProcs.TexParameterIuiv(target, pname, params);
	checkError();
}

void glGetTexParameterIiv(GLenum target, GLenum pname, GLint * params)
{
	gGlProcs.GetTexParameterIiv(target, pname, params);
	checkError();
}

void glGetTexParameterIuiv(GLenum target, GLenum pname, GLuint * params)
{
	gGlProcs.GetTexParameterIuiv(target, pname, params);
	checkError();
}

void glClearBufferiv(GLenum buffer, GLint drawbuffer, GLint const * value)
{
	gGlProcs.ClearBufferiv(buffer, drawbuffer, value);
	checkError();
}

void glClearBufferuiv(GLenum buffer, GLint drawbuffer, GLuint const * value)
{
	gGlProcs.ClearBufferuiv(buffer, drawbuffer, value);
	checkError();
}

void glClearBufferfv(GLenum buffer, GLint drawbuffer, GLfloat const * value)
{
	gGlProcs.ClearBufferfv(buffer, drawbuffer, value);
	checkError();
}

void glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)
{
	gGlProcs.ClearBufferfi(buffer, drawbuffer, depth, stencil);
	checkError();
}

GLubyte const * glGetStringi (GLenum name, GLuint index)
{
	auto result = gGlProcs.GetStringi (name, index);
	checkError();
	return result;
}

void glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei primcount)
{
	gGlProcs.DrawArraysInstanced(mode, first, count, primcount);
	checkError();
}

void glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, GLvoid const * indices, GLsizei primcount)
{
	gGlProcs.DrawElementsInstanced(mode, count, type, indices, primcount);
	checkError();
}

void glTexBuffer(GLenum target, GLenum internalformat, GLuint buffer)
{
	gGlProcs.TexBuffer(target, internalformat, buffer);
	checkError();
}

void glPrimitiveRestartIndex(GLuint index)
{
	gGlProcs.PrimitiveRestartIndex(index);
	checkError();
}

void glGetInteger64i_v(GLenum target, GLuint index, GLint64 *data)
{
	gGlProcs.GetInteger64i_v(target, index, data);
	checkError();
}

void glGetBufferParameteri64v(GLenum target, GLenum pname, GLint64 *params)
{
	gGlProcs.GetBufferParameteri64v(target, pname, params);
	checkError();
}

void glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level)
{
	gGlProcs.FramebufferTexture(target, attachment, texture, level);
	checkError();
}

void glVertexAttribDivisor(GLuint index, GLuint divisor)
{
	gGlProcs.VertexAttribDivisor(index, divisor);
	checkError();
}

void glMinSampleShading(GLclampf value)
{
	gGlProcs.MinSampleShading(value);
	checkError();
}

void glBlendEquationi(GLuint buf, GLenum mode)
{
	gGlProcs.BlendEquationi(buf, mode);
	checkError();
}

void glBlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha)
{
	gGlProcs.BlendEquationSeparatei(buf, modeRGB, modeAlpha);
	checkError();
}

void glBlendFunci(GLuint buf, GLenum src, GLenum dst)
{
	gGlProcs.BlendFunci(buf, src, dst);
	checkError();
}

void glBlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
	gGlProcs.BlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
	checkError();
}

GLboolean glIsRenderbuffer(GLuint renderbuffer)
{
	auto result = gGlProcs.IsRenderbuffer(renderbuffer);
	checkError();
	return result;
}

void glBindRenderbuffer(GLenum target, GLuint renderbuffer)
{
	gGlProcs.BindRenderbuffer(target, renderbuffer);
	checkError();
}

void glDeleteRenderbuffers(GLsizei n, GLuint const * renderbuffers)
{
	gGlProcs.DeleteRenderbuffers(n, renderbuffers);
	checkError();
}

void glGenRenderbuffers(GLsizei n, GLuint * renderbuffers)
{
	gGlProcs.GenRenderbuffers(n, renderbuffers);
	checkError();
}

void glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
	gGlProcs.RenderbufferStorage(target, internalformat, width, height);
	checkError();
}

void glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params)
{
	gGlProcs.GetRenderbufferParameteriv(target, pname, params);
	checkError();
}

GLboolean glIsFramebuffer(GLuint framebuffer)
{
	auto result = gGlProcs.IsFramebuffer(framebuffer);
	checkError();
	return result;
}

void glBindFramebuffer(GLenum target, GLuint framebuffer)
{
	gGlProcs.BindFramebuffer(target, framebuffer);
	checkError();
}

void glDeleteFramebuffers(GLsizei n, GLuint const * framebuffers)
{
	gGlProcs.DeleteFramebuffers(n, framebuffers);
	checkError();
}

void glGenFramebuffers(GLsizei n, GLuint * framebuffers)
{
	gGlProcs.GenFramebuffers(n, framebuffers);
	checkError();
}

GLenum glCheckFramebufferStatus(GLenum target)
{
	auto result = gGlProcs.CheckFramebufferStatus(target);
	checkError();
	return result;
}

void glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
	gGlProcs.FramebufferTexture1D(target, attachment, textarget, texture, level);
	checkError();
}

void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
	gGlProcs.FramebufferTexture2D(target, attachment, textarget, texture, level);
	checkError();
}

void glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset)
{
	gGlProcs.FramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);
	checkError();
}

void glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
	gGlProcs.FramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
	checkError();
}

void glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params)
{
	gGlProcs.GetFramebufferAttachmentParameteriv(target, attachment, pname, params);
	checkError();
}

void glGenerateMipmap(GLenum target)
{
	gGlProcs.GenerateMipmap(target);
	checkError();
}

void glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
{
	gGlProcs.BlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
	checkError();
}

void glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
	gGlProcs.RenderbufferStorageMultisample(target, samples, internalformat, width, height);
	checkError();
}

void glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer)
{
	gGlProcs.FramebufferTextureLayer(target, attachment, texture, level, layer);
	checkError();
}

GLvoid * glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)
{
	auto result = gGlProcs.MapBufferRange(target, offset, length, access);
	checkError();
	return result;
}

void glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length)
{
	gGlProcs.FlushMappedBufferRange(target, offset, length);
	checkError();
}

void glBindVertexArray(GLuint array)
{
	gGlProcs.BindVertexArray(array);
	checkError();
}

void glDeleteVertexArrays(GLsizei n, GLuint const * arrays)
{
	gGlProcs.DeleteVertexArrays(n, arrays);
	checkError();
}

void glGenVertexArrays(GLsizei n, GLuint * arrays)
{
	gGlProcs.GenVertexArrays(n, arrays);
	checkError();
}

GLboolean glIsVertexArray(GLuint array)
{
	auto result = gGlProcs.IsVertexArray(array);
	checkError();
	return result;
}

void glGetUniformIndices(GLuint program, GLsizei uniformCount, GLchar const * * uniformNames, GLuint * uniformIndices)
{
	gGlProcs.GetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
	checkError();
}

void glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, GLuint const * uniformIndices, GLenum pname, GLint * params)
{
	gGlProcs.GetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);
	checkError();
}

void glGetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName)
{
	gGlProcs.GetActiveUniformName(program, uniformIndex, bufSize, length, uniformName);
	checkError();
}

GLuint glGetUniformBlockIndex(GLuint program, GLchar const * uniformBlockName)
{
	auto result = gGlProcs.GetUniformBlockIndex(program, uniformBlockName);
	checkError();
	return result;
}

void glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params)
{
	gGlProcs.GetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
	checkError();
}

void glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName)
{
	gGlProcs.GetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
	checkError();
}

void glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)
{
	gGlProcs.UniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
	checkError();
}

void glCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
{
	gGlProcs.CopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
	checkError();
}

void glDrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, GLvoid const * indices, GLint basevertex)
{
	gGlProcs.DrawElementsBaseVertex(mode, count, type, indices, basevertex);
	checkError();
}

void glDrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, GLvoid const * indices, GLint basevertex)
{
	gGlProcs.DrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
	checkError();
}

void glDrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, GLvoid const * indices, GLsizei primcount, GLint basevertex)
{
	gGlProcs.DrawElementsInstancedBaseVertex(mode, count, type, indices, primcount, basevertex);
	checkError();
}

void glMultiDrawElementsBaseVertex(GLenum mode, GLsizei const * count, GLenum type, GLvoid const * * indices, GLsizei primcount, GLint const * basevertex)
{
	gGlProcs.MultiDrawElementsBaseVertex(mode, count, type, indices, primcount, basevertex);
	checkError();
}

void glProvokingVertex(GLenum mode)
{
	gGlProcs.ProvokingVertex(mode);
	checkError();
}

GLsync glFenceSync(GLenum condition, GLbitfield flags)
{
	auto result = gGlProcs.FenceSync(condition, flags);
	checkError();
	return result;
}

GLboolean glIsSync(GLsync sync)
{
	auto result = gGlProcs.IsSync(sync);
	checkError();
	return result;
}

void glDeleteSync(GLsync sync)
{
	gGlProcs.DeleteSync(sync);
	checkError();
}

GLenum glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
	auto result = gGlProcs.ClientWaitSync(sync, flags, timeout);
	checkError();
	return result;
}

void glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
	gGlProcs.WaitSync(sync, flags, timeout);
	checkError();
}

void glGetInteger64v(GLenum pname, GLint64 *params)
{
	gGlProcs.GetInteger64v(pname, params);
	checkError();
}

void glGetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei * length, GLint * values)
{
	gGlProcs.GetSynciv(sync, pname, bufSize, length, values);
	checkError();
}

void glTexImage2DMultisample(GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
	gGlProcs.TexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
	checkError();
}

void glTexImage3DMultisample(GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
	gGlProcs.TexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
	checkError();
}

void glGetMultisamplefv(GLenum pname, GLuint index, GLfloat * val)
{
	gGlProcs.GetMultisamplefv(pname, index, val);
	checkError();
}

void glSampleMaski(GLuint index, GLbitfield mask)
{
	gGlProcs.SampleMaski(index, mask);
	checkError();
}

void glBlendEquationiARB(GLuint buf, GLenum mode)
{
	gGlProcs.BlendEquationiARB(buf, mode);
	checkError();
}

void glBlendEquationSeparateiARB(GLuint buf, GLenum modeRGB, GLenum modeAlpha)
{
	gGlProcs.BlendEquationSeparateiARB(buf, modeRGB, modeAlpha);
	checkError();
}

void glBlendFunciARB(GLuint buf, GLenum src, GLenum dst)
{
	gGlProcs.BlendFunciARB(buf, src, dst);
	checkError();
}

void glBlendFuncSeparateiARB(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
	gGlProcs.BlendFuncSeparateiARB(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
	checkError();
}

void glMinSampleShadingARB(GLclampf value)
{
	gGlProcs.MinSampleShadingARB(value);
	checkError();
}

void glNamedStringARB(GLenum type, GLint namelen, GLchar const * name, GLint stringlen, GLchar const * string)
{
	gGlProcs.NamedStringARB(type, namelen, name, stringlen, string);
	checkError();
}

void glDeleteNamedStringARB(GLint namelen, GLchar const * name)
{
	gGlProcs.DeleteNamedStringARB(namelen, name);
	checkError();
}

void glCompileShaderIncludeARB(GLuint shader, GLsizei count, GLchar const * * path, GLint const * length)
{
	gGlProcs.CompileShaderIncludeARB(shader, count, path, length);
	checkError();
}

GLboolean glIsNamedStringARB(GLint namelen, GLchar const * name)
{
	auto result = gGlProcs.IsNamedStringARB(namelen, name);
	checkError();
	return result;
}

void glGetNamedStringARB(GLint namelen, GLchar const * name, GLsizei bufSize, GLint * stringlen, GLchar * string)
{
	gGlProcs.GetNamedStringARB(namelen, name, bufSize, stringlen, string);
	checkError();
}

void glGetNamedStringivARB(GLint namelen, GLchar const * name, GLenum pname, GLint * params)
{
	gGlProcs.GetNamedStringivARB(namelen, name, pname, params);
	checkError();
}

void glBindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, GLchar const * name)
{
	gGlProcs.BindFragDataLocationIndexed(program, colorNumber, index, name);
	checkError();
}

GLint glGetFragDataIndex(GLuint program, GLchar const * name)
{
	auto result = gGlProcs.GetFragDataIndex(program, name);
	checkError();
	return result;
}

void glGenSamplers(GLsizei count, GLuint * samplers)
{
	gGlProcs.GenSamplers(count, samplers);
	checkError();
}

void glDeleteSamplers(GLsizei count, GLuint const * samplers)
{
	gGlProcs.DeleteSamplers(count, samplers);
	checkError();
}

GLboolean glIsSampler(GLuint sampler)
{
	auto result = gGlProcs.IsSampler(sampler);
	checkError();
	return result;
}

void glBindSampler(GLuint unit, GLuint sampler)
{
	gGlProcs.BindSampler(unit, sampler);
	checkError();
}

void glSamplerParameteri(GLuint sampler, GLenum pname, GLint param)
{
	gGlProcs.SamplerParameteri(sampler, pname, param);
	checkError();
}

void glSamplerParameteriv(GLuint sampler, GLenum pname, GLint const * param)
{
	gGlProcs.SamplerParameteriv(sampler, pname, param);
	checkError();
}

void glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param)
{
	gGlProcs.SamplerParameterf(sampler, pname, param);
	checkError();
}

void glSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat const * param)
{
	gGlProcs.SamplerParameterfv(sampler, pname, param);
	checkError();
}

void glSamplerParameterIiv(GLuint sampler, GLenum pname, GLint const * param)
{
	gGlProcs.SamplerParameterIiv(sampler, pname, param);
	checkError();
}

void glSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint const * param)
{
	gGlProcs.SamplerParameterIuiv(sampler, pname, param);
	checkError();
}

void glGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint * params)
{
	gGlProcs.GetSamplerParameteriv(sampler, pname, params);
	checkError();
}

void glGetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint * params)
{
	gGlProcs.GetSamplerParameterIiv(sampler, pname, params);
	checkError();
}

void glGetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat * params)
{
	gGlProcs.GetSamplerParameterfv(sampler, pname, params);
	checkError();
}

void glGetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint * params)
{
	gGlProcs.GetSamplerParameterIuiv(sampler, pname, params);
	checkError();
}

void glQueryCounter(GLuint id, GLenum target)
{
	gGlProcs.QueryCounter(id, target);
	checkError();
}

void glGetQueryObjecti64v(GLuint id, GLenum pname, GLint64 *params)
{
	gGlProcs.GetQueryObjecti64v(id, pname, params);
	checkError();
}

void glGetQueryObjectui64v(GLuint id, GLenum pname, GLuint64 *params)
{
	gGlProcs.GetQueryObjectui64v(id, pname, params);
	checkError();
}

void glVertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	gGlProcs.VertexAttribP1ui(index, type, normalized, value);
	checkError();
}

void glVertexAttribP1uiv(GLuint index, GLenum type, GLboolean normalized, GLuint const * value)
{
	gGlProcs.VertexAttribP1uiv(index, type, normalized, value);
	checkError();
}

void glVertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	gGlProcs.VertexAttribP2ui(index, type, normalized, value);
	checkError();
}

void glVertexAttribP2uiv(GLuint index, GLenum type, GLboolean normalized, GLuint const * value)
{
	gGlProcs.VertexAttribP2uiv(index, type, normalized, value);
	checkError();
}

void glVertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	gGlProcs.VertexAttribP3ui(index, type, normalized, value);
	checkError();
}

void glVertexAttribP3uiv(GLuint index, GLenum type, GLboolean normalized, GLuint const * value)
{
	gGlProcs.VertexAttribP3uiv(index, type, normalized, value);
	checkError();
}

void glVertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	gGlProcs.VertexAttribP4ui(index, type, normalized, value);
	checkError();
}

void glVertexAttribP4uiv(GLuint index, GLenum type, GLboolean normalized, GLuint const * value)
{
	gGlProcs.VertexAttribP4uiv(index, type, normalized, value);
	checkError();
}

void glDrawArraysIndirect(GLenum mode, GLvoid const * indirect)
{
	gGlProcs.DrawArraysIndirect(mode, indirect);
	checkError();
}

void glDrawElementsIndirect(GLenum mode, GLenum type, GLvoid const * indirect)
{
	gGlProcs.DrawElementsIndirect(mode, type, indirect);
	checkError();
}

void glUniform1d(GLint location, GLdouble x)
{
	gGlProcs.Uniform1d(location, x);
	checkError();
}

void glUniform2d(GLint location, GLdouble x, GLdouble y)
{
	gGlProcs.Uniform2d(location, x, y);
	checkError();
}

void glUniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z)
{
	gGlProcs.Uniform3d(location, x, y, z);
	checkError();
}

void glUniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	gGlProcs.Uniform4d(location, x, y, z, w);
	checkError();
}

void glUniform1dv(GLint location, GLsizei count, GLdouble const * value)
{
	gGlProcs.Uniform1dv(location, count, value);
	checkError();
}

void glUniform2dv(GLint location, GLsizei count, GLdouble const * value)
{
	gGlProcs.Uniform2dv(location, count, value);
	checkError();
}

void glUniform3dv(GLint location, GLsizei count, GLdouble const * value)
{
	gGlProcs.Uniform3dv(location, count, value);
	checkError();
}

void glUniform4dv(GLint location, GLsizei count, GLdouble const * value)
{
	gGlProcs.Uniform4dv(location, count, value);
	checkError();
}

void glUniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gGlProcs.UniformMatrix2dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gGlProcs.UniformMatrix3dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gGlProcs.UniformMatrix4dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gGlProcs.UniformMatrix2x3dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gGlProcs.UniformMatrix2x4dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gGlProcs.UniformMatrix3x2dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gGlProcs.UniformMatrix3x4dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gGlProcs.UniformMatrix4x2dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gGlProcs.UniformMatrix4x3dv(location, count, transpose, value);
	checkError();
}

void glGetUniformdv(GLuint program, GLint location, GLdouble * params)
{
	gGlProcs.GetUniformdv(program, location, params);
	checkError();
}

GLint glGetSubroutineUniformLocation(GLuint program, GLenum shadertype, GLchar const * name)
{
	auto result = gGlProcs.GetSubroutineUniformLocation(program, shadertype, name);
	checkError();
	return result;
}

GLuint glGetSubroutineIndex(GLuint program, GLenum shadertype, GLchar const * name)
{
	auto result = gGlProcs.GetSubroutineIndex(program, shadertype, name);
	checkError();
	return result;
}

void glGetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint * values)
{
	gGlProcs.GetActiveSubroutineUniformiv(program, shadertype, index, pname, values);
	checkError();
}

void glGetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name)
{
	gGlProcs.GetActiveSubroutineUniformName(program, shadertype, index, bufsize, length, name);
	checkError();
}

void glGetActiveSubroutineName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name)
{
	gGlProcs.GetActiveSubroutineName(program, shadertype, index, bufsize, length, name);
	checkError();
}

void glUniformSubroutinesuiv(GLenum shadertype, GLsizei count, GLuint const * indices)
{
	gGlProcs.UniformSubroutinesuiv(shadertype, count, indices);
	checkError();
}

void glGetUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint * params)
{
	gGlProcs.GetUniformSubroutineuiv(shadertype, location, params);
	checkError();
}

void glGetProgramStageiv(GLuint program, GLenum shadertype, GLenum pname, GLint * values)
{
	gGlProcs.GetProgramStageiv(program, shadertype, pname, values);
	checkError();
}

void glPatchParameteri(GLenum pname, GLint value)
{
	gGlProcs.PatchParameteri(pname, value);
	checkError();
}

void glPatchParameterfv(GLenum pname, GLfloat const * values)
{
	gGlProcs.PatchParameterfv(pname, values);
	checkError();
}

void glBindTransformFeedback(GLenum target, GLuint id)
{
	gGlProcs.BindTransformFeedback(target, id);
	checkError();
}

void glDeleteTransformFeedbacks(GLsizei n, GLuint const * ids)
{
	gGlProcs.DeleteTransformFeedbacks(n, ids);
	checkError();
}

void glGenTransformFeedbacks(GLsizei n, GLuint * ids)
{
	gGlProcs.GenTransformFeedbacks(n, ids);
	checkError();
}

GLboolean glIsTransformFeedback(GLuint id)
{
	auto result = gGlProcs.IsTransformFeedback(id);
	checkError();
	return result;
}

void glPauseTransformFeedback(void)
{
	gGlProcs.PauseTransformFeedback();
	checkError();
}

void glResumeTransformFeedback(void)
{
	gGlProcs.ResumeTransformFeedback();
	checkError();
}

void glDrawTransformFeedback(GLenum mode, GLuint id)
{
	gGlProcs.DrawTransformFeedback(mode, id);
	checkError();
}

void glDrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream)
{
	gGlProcs.DrawTransformFeedbackStream(mode, id, stream);
	checkError();
}

void glBeginQueryIndexed(GLenum target, GLuint index, GLuint id)
{
	gGlProcs.BeginQueryIndexed(target, index, id);
	checkError();
}

void glEndQueryIndexed(GLenum target, GLuint index)
{
	gGlProcs.EndQueryIndexed(target, index);
	checkError();
}

void glGetQueryIndexediv(GLenum target, GLuint index, GLenum pname, GLint * params)
{
	gGlProcs.GetQueryIndexediv(target, index, pname, params);
	checkError();
}

void glReleaseShaderCompiler(void)
{
	gGlProcs.ReleaseShaderCompiler();
	checkError();
}

void glShaderBinary(GLsizei count, GLuint const * shaders, GLenum binaryformat, GLvoid const * binary, GLsizei length)
{
	gGlProcs.ShaderBinary(count, shaders, binaryformat, binary, length);
	checkError();
}

void glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision)
{
	gGlProcs.GetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
	checkError();
}

void glDepthRangef(GLclampf n, GLclampf f)
{
	gGlProcs.DepthRangef(n, f);
	checkError();
}

void glClearDepthf(GLclampf d)
{
	gGlProcs.ClearDepthf(d);
	checkError();
}

void glGetProgramBinary(GLuint program, GLsizei bufSize, GLsizei * length, GLenum * binaryFormat, GLvoid * binary)
{
	gGlProcs.GetProgramBinary(program, bufSize, length, binaryFormat, binary);
	checkError();
}

void glProgramBinary(GLuint program, GLenum binaryFormat, GLvoid const * binary, GLsizei length)
{
	gGlProcs.ProgramBinary(program, binaryFormat, binary, length);
	checkError();
}

void glProgramParameteri(GLuint program, GLenum pname, GLint value)
{
	gGlProcs.ProgramParameteri(program, pname, value);
	checkError();
}

void glUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program)
{
	gGlProcs.UseProgramStages(pipeline, stages, program);
	checkError();
}

void glActiveShaderProgram(GLuint pipeline, GLuint program)
{
	gGlProcs.ActiveShaderProgram(pipeline, program);
	checkError();
}

GLuint glCreateShaderProgramv(GLenum type, GLsizei count, GLchar const * * strings)
{
	auto result = gGlProcs.CreateShaderProgramv(type, count, strings);
	checkError();
	return result;
}

void glBindProgramPipeline(GLuint pipeline)
{
	gGlProcs.BindProgramPipeline(pipeline);
	checkError();
}

void glDeleteProgramPipelines(GLsizei n, GLuint const * pipelines)
{
	gGlProcs.DeleteProgramPipelines(n, pipelines);
	checkError();
}

void glGenProgramPipelines(GLsizei n, GLuint * pipelines)
{
	gGlProcs.GenProgramPipelines(n, pipelines);
	checkError();
}

GLboolean glIsProgramPipeline(GLuint pipeline)
{
	auto result = gGlProcs.IsProgramPipeline(pipeline);
	checkError();
	return result;
}

void glGetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint * params)
{
	gGlProcs.GetProgramPipelineiv(pipeline, pname, params);
	checkError();
}

void glProgramUniform1i(GLuint program, GLint location, GLint v0)
{
	gGlProcs.ProgramUniform1i(program, location, v0);
	checkError();
}

void glProgramUniform1iv(GLuint program, GLint location, GLsizei count, GLint const * value)
{
	gGlProcs.ProgramUniform1iv(program, location, count, value);
	checkError();
}

void glProgramUniform1f(GLuint program, GLint location, GLfloat v0)
{
	gGlProcs.ProgramUniform1f(program, location, v0);
	checkError();
}

void glProgramUniform1fv(GLuint program, GLint location, GLsizei count, GLfloat const * value)
{
	gGlProcs.ProgramUniform1fv(program, location, count, value);
	checkError();
}

void glProgramUniform1d(GLuint program, GLint location, GLdouble v0)
{
	gGlProcs.ProgramUniform1d(program, location, v0);
	checkError();
}

void glProgramUniform1dv(GLuint program, GLint location, GLsizei count, GLdouble const * value)
{
	gGlProcs.ProgramUniform1dv(program, location, count, value);
	checkError();
}

void glProgramUniform1ui(GLuint program, GLint location, GLuint v0)
{
	gGlProcs.ProgramUniform1ui(program, location, v0);
	checkError();
}

void glProgramUniform1uiv(GLuint program, GLint location, GLsizei count, GLuint const * value)
{
	gGlProcs.ProgramUniform1uiv(program, location, count, value);
	checkError();
}

void glProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1)
{
	gGlProcs.ProgramUniform2i(program, location, v0, v1);
	checkError();
}

void glProgramUniform2iv(GLuint program, GLint location, GLsizei count, GLint const * value)
{
	gGlProcs.ProgramUniform2iv(program, location, count, value);
	checkError();
}

void glProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1)
{
	gGlProcs.ProgramUniform2f(program, location, v0, v1);
	checkError();
}

void glProgramUniform2fv(GLuint program, GLint location, GLsizei count, GLfloat const * value)
{
	gGlProcs.ProgramUniform2fv(program, location, count, value);
	checkError();
}

void glProgramUniform2d(GLuint program, GLint location, GLdouble v0, GLdouble v1)
{
	gGlProcs.ProgramUniform2d(program, location, v0, v1);
	checkError();
}

void glProgramUniform2dv(GLuint program, GLint location, GLsizei count, GLdouble const * value)
{
	gGlProcs.ProgramUniform2dv(program, location, count, value);
	checkError();
}

void glProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1)
{
	gGlProcs.ProgramUniform2ui(program, location, v0, v1);
	checkError();
}

void glProgramUniform2uiv(GLuint program, GLint location, GLsizei count, GLuint const * value)
{
	gGlProcs.ProgramUniform2uiv(program, location, count, value);
	checkError();
}

void glProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2)
{
	gGlProcs.ProgramUniform3i(program, location, v0, v1, v2);
	checkError();
}

void glProgramUniform3iv(GLuint program, GLint location, GLsizei count, GLint const * value)
{
	gGlProcs.ProgramUniform3iv(program, location, count, value);
	checkError();
}

void glProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
	gGlProcs.ProgramUniform3f(program, location, v0, v1, v2);
	checkError();
}

void glProgramUniform3fv(GLuint program, GLint location, GLsizei count, GLfloat const * value)
{
	gGlProcs.ProgramUniform3fv(program, location, count, value);
	checkError();
}

void glProgramUniform3d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2)
{
	gGlProcs.ProgramUniform3d(program, location, v0, v1, v2);
	checkError();
}

void glProgramUniform3dv(GLuint program, GLint location, GLsizei count, GLdouble const * value)
{
	gGlProcs.ProgramUniform3dv(program, location, count, value);
	checkError();
}

void glProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2)
{
	gGlProcs.ProgramUniform3ui(program, location, v0, v1, v2);
	checkError();
}

void glProgramUniform3uiv(GLuint program, GLint location, GLsizei count, GLuint const * value)
{
	gGlProcs.ProgramUniform3uiv(program, location, count, value);
	checkError();
}

void glProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
	gGlProcs.ProgramUniform4i(program, location, v0, v1, v2, v3);
	checkError();
}

void glProgramUniform4iv(GLuint program, GLint location, GLsizei count, GLint const * value)
{
	gGlProcs.ProgramUniform4iv(program, location, count, value);
	checkError();
}

void glProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	gGlProcs.ProgramUniform4f(program, location, v0, v1, v2, v3);
	checkError();
}

void glProgramUniform4fv(GLuint program, GLint location, GLsizei count, GLfloat const * value)
{
	gGlProcs.ProgramUniform4fv(program, location, count, value);
	checkError();
}

void glProgramUniform4d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3)
{
	gGlProcs.ProgramUniform4d(program, location, v0, v1, v2, v3);
	checkError();
}

void glProgramUniform4dv(GLuint program, GLint location, GLsizei count, GLdouble const * value)
{
	gGlProcs.ProgramUniform4dv(program, location, count, value);
	checkError();
}

void glProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	gGlProcs.ProgramUniform4ui(program, location, v0, v1, v2, v3);
	checkError();
}

void glProgramUniform4uiv(GLuint program, GLint location, GLsizei count, GLuint const * value)
{
	gGlProcs.ProgramUniform4uiv(program, location, count, value);
	checkError();
}

void glProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gGlProcs.ProgramUniformMatrix2fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gGlProcs.ProgramUniformMatrix3fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gGlProcs.ProgramUniformMatrix4fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gGlProcs.ProgramUniformMatrix2dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gGlProcs.ProgramUniformMatrix3dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gGlProcs.ProgramUniformMatrix4dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gGlProcs.ProgramUniformMatrix2x3fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gGlProcs.ProgramUniformMatrix3x2fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gGlProcs.ProgramUniformMatrix2x4fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gGlProcs.ProgramUniformMatrix4x2fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gGlProcs.ProgramUniformMatrix3x4fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gGlProcs.ProgramUniformMatrix4x3fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix2x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gGlProcs.ProgramUniformMatrix2x3dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix3x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gGlProcs.ProgramUniformMatrix3x2dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix2x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gGlProcs.ProgramUniformMatrix2x4dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix4x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gGlProcs.ProgramUniformMatrix4x2dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix3x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gGlProcs.ProgramUniformMatrix3x4dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix4x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gGlProcs.ProgramUniformMatrix4x3dv(program, location, count, transpose, value);
	checkError();
}

void glValidateProgramPipeline(GLuint pipeline)
{
	gGlProcs.ValidateProgramPipeline(pipeline);
	checkError();
}

void glGetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
{
	gGlProcs.GetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog);
	checkError();
}

void glVertexAttribL1d(GLuint index, GLdouble x)
{
	gGlProcs.VertexAttribL1d(index, x);
	checkError();
}

void glVertexAttribL2d(GLuint index, GLdouble x, GLdouble y)
{
	gGlProcs.VertexAttribL2d(index, x, y);
	checkError();
}

void glVertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z)
{
	gGlProcs.VertexAttribL3d(index, x, y, z);
	checkError();
}

void glVertexAttribL4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	gGlProcs.VertexAttribL4d(index, x, y, z, w);
	checkError();
}

void glVertexAttribL1dv(GLuint index, GLdouble const * v)
{
	gGlProcs.VertexAttribL1dv(index, v);
	checkError();
}

void glVertexAttribL2dv(GLuint index, GLdouble const * v)
{
	gGlProcs.VertexAttribL2dv(index, v);
	checkError();
}

void glVertexAttribL3dv(GLuint index, GLdouble const * v)
{
	gGlProcs.VertexAttribL3dv(index, v);
	checkError();
}

void glVertexAttribL4dv(GLuint index, GLdouble const * v)
{
	gGlProcs.VertexAttribL4dv(index, v);
	checkError();
}

void glVertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, GLvoid const * pointer)
{
	gGlProcs.VertexAttribLPointer(index, size, type, stride, pointer);
	checkError();
}

void glGetVertexAttribLdv(GLuint index, GLenum pname, GLdouble * params)
{
	gGlProcs.GetVertexAttribLdv(index, pname, params);
	checkError();
}

void glViewportArrayv(GLuint first, GLsizei count, GLfloat const * v)
{
	gGlProcs.ViewportArrayv(first, count, v);
	checkError();
}

void glViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h)
{
	gGlProcs.ViewportIndexedf(index, x, y, w, h);
	checkError();
}

void glViewportIndexedfv(GLuint index, GLfloat const * v)
{
	gGlProcs.ViewportIndexedfv(index, v);
	checkError();
}

void glScissorArrayv(GLuint first, GLsizei count, GLint const * v)
{
	gGlProcs.ScissorArrayv(first, count, v);
	checkError();
}

void glScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height)
{
	gGlProcs.ScissorIndexed(index, left, bottom, width, height);
	checkError();
}

void glScissorIndexedv(GLuint index, GLint const * v)
{
	gGlProcs.ScissorIndexedv(index, v);
	checkError();
}

void glDepthRangeArrayv(GLuint first, GLsizei count, GLclampd const * v)
{
	gGlProcs.DepthRangeArrayv(first, count, v);
	checkError();
}

void glDepthRangeIndexed(GLuint index, GLclampd n, GLclampd f)
{
	gGlProcs.DepthRangeIndexed(index, n, f);
	checkError();
}

void glGetFloati_v(GLenum target, GLuint index, GLfloat * data)
{
	gGlProcs.GetFloati_v(target, index, data);
	checkError();
}

void glGetDoublei_v(GLenum target, GLuint index, GLdouble * data)
{
	gGlProcs.GetDoublei_v(target, index, data);
	checkError();
}

GLsync glCreateSyncFromCLeventARB(struct _cl_context * context, struct _cl_event * event, GLbitfield flags)
{
	auto result = gGlProcs.CreateSyncFromCLeventARB(context, event, flags);
	checkError();
	return result;
}

void glDebugMessageControlARB(GLenum source, GLenum type, GLenum severity, GLsizei count, GLuint const * ids, GLboolean enabled)
{
	gGlProcs.DebugMessageControlARB(source, type, severity, count, ids, enabled);
	checkError();
}

void glDebugMessageInsertARB(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const * buf)
{
	gGlProcs.DebugMessageInsertARB(source, type, id, severity, length, buf);
	checkError();
}

void glDebugMessageCallbackARB(GLDEBUGPROCARB callback, GLvoid const * userParam)
{
	gGlProcs.DebugMessageCallbackARB(callback, userParam);
	checkError();
}

GLuint glGetDebugMessageLogARB(GLuint count, GLsizei bufsize, GLenum * sources, GLenum * types, GLuint * ids, GLenum * severities, GLsizei * lengths, GLchar * messageLog)
{
	auto result = gGlProcs.GetDebugMessageLogARB(count, bufsize, sources, types, ids, severities, lengths, messageLog);
	checkError();
	return result;
}

GLenum glGetGraphicsResetStatusARB(void)
{
	auto result = gGlProcs.GetGraphicsResetStatusARB();
	checkError();
	return result;
}

void glGetnMapdvARB(GLenum target, GLenum query, GLsizei bufSize, GLdouble * v)
{
	gGlProcs.GetnMapdvARB(target, query, bufSize, v);
	checkError();
}

void glGetnMapfvARB(GLenum target, GLenum query, GLsizei bufSize, GLfloat * v)
{
	gGlProcs.GetnMapfvARB(target, query, bufSize, v);
	checkError();
}

void glGetnMapivARB(GLenum target, GLenum query, GLsizei bufSize, GLint * v)
{
	gGlProcs.GetnMapivARB(target, query, bufSize, v);
	checkError();
}

void glGetnPixelMapfvARB(GLenum map, GLsizei bufSize, GLfloat * values)
{
	gGlProcs.GetnPixelMapfvARB(map, bufSize, values);
	checkError();
}

void glGetnPixelMapuivARB(GLenum map, GLsizei bufSize, GLuint * values)
{
	gGlProcs.GetnPixelMapuivARB(map, bufSize, values);
	checkError();
}

void glGetnPixelMapusvARB(GLenum map, GLsizei bufSize, GLushort * values)
{
	gGlProcs.GetnPixelMapusvARB(map, bufSize, values);
	checkError();
}

void glGetnPolygonStippleARB(GLsizei bufSize, GLubyte * pattern)
{
	gGlProcs.GetnPolygonStippleARB(bufSize, pattern);
	checkError();
}

void glGetnColorTableARB(GLenum target, GLenum format, GLenum type, GLsizei bufSize, GLvoid * table)
{
	gGlProcs.GetnColorTableARB(target, format, type, bufSize, table);
	checkError();
}

void glGetnConvolutionFilterARB(GLenum target, GLenum format, GLenum type, GLsizei bufSize, GLvoid * image)
{
	gGlProcs.GetnConvolutionFilterARB(target, format, type, bufSize, image);
	checkError();
}

void glGetnSeparableFilterARB(GLenum target, GLenum format, GLenum type, GLsizei rowBufSize, GLvoid * row, GLsizei columnBufSize, GLvoid * column, GLvoid * span)
{
	gGlProcs.GetnSeparableFilterARB(target, format, type, rowBufSize, row, columnBufSize, column, span);
	checkError();
}

void glGetnHistogramARB(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, GLvoid * values)
{
	gGlProcs.GetnHistogramARB(target, reset, format, type, bufSize, values);
	checkError();
}

void glGetnMinmaxARB(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, GLvoid * values)
{
	gGlProcs.GetnMinmaxARB(target, reset, format, type, bufSize, values);
	checkError();
}

void glGetnTexImageARB(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, GLvoid * img)
{
	gGlProcs.GetnTexImageARB(target, level, format, type, bufSize, img);
	checkError();
}

void glReadnPixelsARB(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, GLvoid * data)
{
	gGlProcs.ReadnPixelsARB(x, y, width, height, format, type, bufSize, data);
	checkError();
}

void glGetnCompressedTexImageARB(GLenum target, GLint lod, GLsizei bufSize, GLvoid * img)
{
	gGlProcs.GetnCompressedTexImageARB(target, lod, bufSize, img);
	checkError();
}

void glGetnUniformfvARB(GLuint program, GLint location, GLsizei bufSize, GLfloat * params)
{
	gGlProcs.GetnUniformfvARB(program, location, bufSize, params);
	checkError();
}

void glGetnUniformivARB(GLuint program, GLint location, GLsizei bufSize, GLint * params)
{
	gGlProcs.GetnUniformivARB(program, location, bufSize, params);
	checkError();
}

void glGetnUniformuivARB(GLuint program, GLint location, GLsizei bufSize, GLuint * params)
{
	gGlProcs.GetnUniformuivARB(program, location, bufSize, params);
	checkError();
}

void glGetnUniformdvARB(GLuint program, GLint location, GLsizei bufSize, GLdouble * params)
{
	gGlProcs.GetnUniformdvARB(program, location, bufSize, params);
	checkError();
}

void glDrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei primcount, GLuint baseinstance)
{
	gGlProcs.DrawArraysInstancedBaseInstance(mode, first, count, primcount, baseinstance);
	checkError();
}

void glDrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei primcount, GLuint baseinstance)
{
	gGlProcs.DrawElementsInstancedBaseInstance(mode, count, type,  indices, primcount, baseinstance);
	checkError();
}

void glDrawElementsInstancedBaseVertexBaseInstance(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei primcount, GLint basevertex, GLuint baseinstance)
{
	gGlProcs.DrawElementsInstancedBaseVertexBaseInstance(mode, count, type,  indices, primcount, basevertex, baseinstance);
	checkError();
}

void glDrawTransformFeedbackInstanced(GLenum mode, GLuint id, GLsizei primcount)
{
	gGlProcs.DrawTransformFeedbackInstanced(mode, id, primcount);
	checkError();
}

void glDrawTransformFeedbackStreamInstanced(GLenum mode, GLuint id, GLuint stream, GLsizei primcount)
{
	gGlProcs.DrawTransformFeedbackStreamInstanced(mode, id, stream, primcount);
	checkError();
}

void glGetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint * params)
{
	gGlProcs.GetInternalformativ(target, internalformat, pname, bufSize, params);
	checkError();
}

void glGetActiveAtomicCounterBufferiv(GLuint program, GLuint bufferIndex, GLenum pname, GLint * params)
{
	gGlProcs.GetActiveAtomicCounterBufferiv(program, bufferIndex, pname, params);
	checkError();
}

void glBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format)
{
	gGlProcs.BindImageTexture(unit, texture, level, layered, layer, access, format);
	checkError();
}

void glMemoryBarrier(GLbitfield barriers)
{
	gGlProcs.MemoryBarrier(barriers);
	checkError();
}

void glTexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width)
{
	gGlProcs.TexStorage1D(target, levels, internalformat, width);
	checkError();
}

void glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
	gGlProcs.TexStorage2D(target, levels, internalformat, width, height);
	checkError();
}

void glTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
{
	gGlProcs.TexStorage3D(target, levels, internalformat, width, height, depth);
	checkError();
}

void glTextureStorage1DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width)
{
	gGlProcs.TextureStorage1DEXT(texture, target, levels, internalformat, width);
	checkError();
}

void glTextureStorage2DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
	gGlProcs.TextureStorage2DEXT(texture, target, levels, internalformat, width, height);
	checkError();
}

void glTextureStorage3DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
{
	gGlProcs.TextureStorage3DEXT(texture, target, levels, internalformat, width, height, depth);
	checkError();
}

}
