#include "REX/W32/D3DCOMPILER.h"

REX_W32_IMPORT(std::int32_t, D3DCompile, const void*, std::size_t, const char*, const REX::W32::D3D_SHADER_MACRO*, REX::W32::ID3DInclude*, const char*, const char*, std::uint32_t, std::uint32_t, REX::W32::ID3DBlob**, REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DCompile2, const void*, std::size_t, const char*, const REX::W32::D3D_SHADER_MACRO*, REX::W32::ID3DInclude*, const char*, const char*, std::uint32_t, std::uint32_t, std::uint32_t, const void*, std::size_t, REX::W32::ID3DBlob**, REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DCompileFromFile, const wchar_t*, const REX::W32::D3D_SHADER_MACRO*, REX::W32::ID3DInclude*, const char*, const char*, std::uint32_t, std::uint32_t, REX::W32::ID3DBlob**, REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DCompressShaders, std::uint32_t, REX::W32::D3D_SHADER_DATA*, std::uint32_t, REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DCreateBlob, std::size_t, REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DCreateFunctionLinkingGraph, std::uint32_t, REX::W32::ID3D11FunctionLinkingGraph**);
REX_W32_IMPORT(std::int32_t, D3DCreateLinker, REX::W32::ID3D11Linker**);
REX_W32_IMPORT(std::int32_t, D3DDecompressShaders, const void*, std::size_t, std::uint32_t, std::uint32_t, std::uint32_t*, std::uint32_t, REX::W32::ID3DBlob**, std::uint32_t*);
REX_W32_IMPORT(std::int32_t, D3DDisassemble, const void*, std::size_t, std::uint32_t, const char*, REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DDisassemble10Effect, REX::W32::ID3D10Effect*, std::uint32_t, REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DDisassembleRegion, const void*, std::size_t, std::uint32_t, const char*, std::size_t, std::size_t, std::size_t*, REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DGetBlobPart, const void*, std::size_t, REX::W32::D3D_BLOB_PART, std::uint32_t a_flags, REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DGetDebugInfo, const void*, std::size_t, REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DGetInputSignatureBlob, const void*, std::size_t, REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DGetInputAndOutputSignatureBlob, const void*, std::size_t, REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DGetOutputSignatureBlob, const void*, std::size_t, REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DGetTraceInstructionOffsets, const void*, std::size_t, std::uint32_t, std::size_t, std::size_t, std::size_t*, std::size_t*);
REX_W32_IMPORT(std::int32_t, D3DLoadModule, const void*, std::size_t, REX::W32::ID3D11Module**);
REX_W32_IMPORT(std::int32_t, D3DPreprocess, const void*, std::size_t, const char*, const REX::W32::D3D_SHADER_MACRO*, REX::W32::ID3DInclude*, REX::W32::ID3DBlob**, REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DReadFileToBlob, const wchar_t*, REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DReflect, const void*, std::size_t, const REX::W32::IID&, void**);
REX_W32_IMPORT(std::int32_t, D3DReflectLibrary, const void*, std::size_t, const REX::W32::IID&, void**);
REX_W32_IMPORT(std::int32_t, D3DSetBlobPart, const void*, std::size_t, REX::W32::D3D_BLOB_PART, std::uint32_t, const void*, std::size_t, REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DStripShader, const void*, std::size_t, std::uint32_t, REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DWriteBlobToFile, REX::W32::ID3DBlob*, const wchar_t*, REX::W32::BOOL);

namespace REX::W32
{
	HRESULT D3DCompile(const void* a_srcData, std::size_t a_srcDataSize, const char* a_sourceName, const D3D_SHADER_MACRO* a_defines, ID3DInclude* a_include, const char* a_entrypoint, const char* a_target, std::uint32_t a_flags1, std::uint32_t a_flags2, ID3DBlob** a_code, ID3DBlob** a_errorMsgs)
	{
		return ::W32_IMPL_D3DCompile(a_srcData, a_srcDataSize, a_sourceName, a_defines, a_include, a_entrypoint, a_target, a_flags1, a_flags2, a_code, a_errorMsgs);
	}

	HRESULT D3DCompile2(const void* a_srcData, std::size_t a_srcDataSize, const char* a_sourceName, const D3D_SHADER_MACRO* a_defines, ID3DInclude* a_include, const char* a_entrypoint, const char* a_target, std::uint32_t a_flags1, std::uint32_t a_flags2, std::uint32_t a_secondaryDataFlags, const void* a_secondaryData, std::size_t a_secondaryDataSize, ID3DBlob** a_code, ID3DBlob** a_errorMsgs)
	{
		return ::W32_IMPL_D3DCompile2(a_srcData, a_srcDataSize, a_sourceName, a_defines, a_include, a_entrypoint, a_target, a_flags1, a_flags2, a_secondaryDataFlags, a_secondaryData, a_secondaryDataSize, a_code, a_errorMsgs);
	}

	HRESULT D3DCompileFromFile(const wchar_t* a_fileName, const D3D_SHADER_MACRO* a_defines, ID3DInclude* a_include, const char* a_entrypoint, const char* a_target, std::uint32_t a_flags1, std::uint32_t a_flags2, ID3DBlob** a_code, ID3DBlob** a_errorMsgs)
	{
		return ::W32_IMPL_D3DCompileFromFile(a_fileName, a_defines, a_include, a_entrypoint, a_target, a_flags1, a_flags2, a_code, a_errorMsgs);
	}

	HRESULT D3DCompressShaders(std::uint32_t a_numShaders, D3D_SHADER_DATA* a_shaderData, std::uint32_t a_flags, ID3DBlob** a_compressedData)
	{
		return ::W32_IMPL_D3DCompressShaders(a_numShaders, a_shaderData, a_flags, a_compressedData);
	}

	HRESULT D3DCreateBlob(std::size_t a_size, ID3DBlob** a_blob)
	{
		return ::W32_IMPL_D3DCreateBlob(a_size, a_blob);
	}

	HRESULT D3DCreateFunctionLinkingGraph(std::uint32_t a_flags, ID3D11FunctionLinkingGraph** a_functionLinkingGraph)
	{
		return ::W32_IMPL_D3DCreateFunctionLinkingGraph(a_flags, a_functionLinkingGraph);
	}

	HRESULT D3DCreateLinker(ID3D11Linker** a_linker)
	{
		return ::W32_IMPL_D3DCreateLinker(a_linker);
	}

	HRESULT D3DDecompressShaders(const void* a_srcData, std::size_t a_srcDataSize, std::uint32_t a_numShaders, std::uint32_t a_startIndex, std::uint32_t* a_indices, std::uint32_t a_flags, ID3DBlob** a_shaders, std::uint32_t* a_totalShaders)
	{
		return ::W32_IMPL_D3DDecompressShaders(a_srcData, a_srcDataSize, a_numShaders, a_startIndex, a_indices, a_flags, a_shaders, a_totalShaders);
	}

	HRESULT D3DDisassemble(const void* a_srcData, std::size_t a_srcDataSize, std::uint32_t a_flags, const char* a_comments, ID3DBlob** a_disassembly)
	{
		return ::W32_IMPL_D3DDisassemble(a_srcData, a_srcDataSize, a_flags, a_comments, a_disassembly);
	}

	HRESULT D3DDisassemble10Effect(ID3D10Effect* a_effect, std::uint32_t a_flags, ID3DBlob** a_disassembly)
	{
		return ::W32_IMPL_D3DDisassemble10Effect(a_effect, a_flags, a_disassembly);
	}

	HRESULT D3DDisassembleRegion(const void* a_srcData, std::size_t a_srcDataSize, std::uint32_t a_flags, const char* a_comments, std::size_t a_startByteOffset, std::size_t a_numInsts, std::size_t* a_finishByteOffset, ID3DBlob** a_disassembly)
	{
		return ::W32_IMPL_D3DDisassembleRegion(a_srcData, a_srcDataSize, a_flags, a_comments, a_startByteOffset, a_numInsts, a_finishByteOffset, a_disassembly);
	}

	HRESULT D3DGetBlobPart(const void* a_srcData, std::size_t a_srcDataSize, D3D_BLOB_PART a_partType, std::uint32_t a_flags, ID3DBlob** a_part)
	{
		return ::W32_IMPL_D3DGetBlobPart(a_srcData, a_srcDataSize, a_partType, a_flags, a_part);
	}

	HRESULT D3DGetDebugInfo(const void* a_srcData, std::size_t a_srcDataSize, ID3DBlob** a_debugInfo)
	{
		return ::W32_IMPL_D3DGetDebugInfo(a_srcData, a_srcDataSize, a_debugInfo);
	}

	HRESULT D3DGetInputSignatureBlob(const void* a_srcData, std::size_t a_srcDataSize, ID3DBlob** a_signatureBlob)
	{
		return ::W32_IMPL_D3DGetInputSignatureBlob(a_srcData, a_srcDataSize, a_signatureBlob);
	}

	HRESULT D3DGetInputAndOutputSignatureBlob(const void* a_srcData, std::size_t a_srcDataSize, ID3DBlob** a_signatureBlob)
	{
		return ::W32_IMPL_D3DGetInputAndOutputSignatureBlob(a_srcData, a_srcDataSize, a_signatureBlob);
	}

	HRESULT D3DGetOutputSignatureBlob(const void* a_srcData, std::size_t a_srcDataSize, ID3DBlob** a_signatureBlob)
	{
		return ::W32_IMPL_D3DGetOutputSignatureBlob(a_srcData, a_srcDataSize, a_signatureBlob);
	}

	HRESULT D3DGetTraceInstructionOffsets(const void* a_srcData, std::size_t a_srcDataSize, std::uint32_t a_flags, std::size_t a_startInstIndex, std::size_t a_numInsts, std::size_t* a_offsets, std::size_t* a_totalInsts)
	{
		return ::W32_IMPL_D3DGetTraceInstructionOffsets(a_srcData, a_srcDataSize, a_flags, a_startInstIndex, a_numInsts, a_offsets, a_totalInsts);
	}

	HRESULT D3DLoadModule(const void* a_srcData, std::size_t a_srcDataSize, ID3D11Module** a_module)
	{
		return ::W32_IMPL_D3DLoadModule(a_srcData, a_srcDataSize, a_module);
	}

	HRESULT D3DPreprocess(const void* a_srcData, std::size_t a_srcDataSize, const char* a_sourceName, const D3D_SHADER_MACRO* a_defines, ID3DInclude* a_include, ID3DBlob** a_codeText, ID3DBlob** a_errorMsgs)
	{
		return ::W32_IMPL_D3DPreprocess(a_srcData, a_srcDataSize, a_sourceName, a_defines, a_include, a_codeText, a_errorMsgs);
	}

	HRESULT D3DReadFileToBlob(const wchar_t* a_fileName, ID3DBlob** a_contents)
	{
		return ::W32_IMPL_D3DReadFileToBlob(a_fileName, a_contents);
	}

	HRESULT D3DReflect(const void* a_srcData, std::size_t a_srcDataSize, const IID& a_iid, void** a_reflector)
	{
		return ::W32_IMPL_D3DReflect(a_srcData, a_srcDataSize, a_iid, a_reflector);
	}

	HRESULT D3DReflectLibrary(const void* a_srcData, std::size_t a_srcDataSize, const IID& a_iid, void** a_reflector)
	{
		return ::W32_IMPL_D3DReflectLibrary(a_srcData, a_srcDataSize, a_iid, a_reflector);
	}

	HRESULT D3DSetBlobPart(const void* a_srcData, std::size_t a_srcDataSize, D3D_BLOB_PART a_partType, std::uint32_t a_flags, const void* a_part, std::size_t a_partSize, ID3DBlob** a_newShader)
	{
		return ::W32_IMPL_D3DSetBlobPart(a_srcData, a_srcDataSize, a_partType, a_flags, a_part, a_partSize, a_newShader);
	}

	HRESULT D3DStripShader(const void* a_srcData, std::size_t a_srcDataSize, std::uint32_t a_stripFlags, ID3DBlob** a_strippedBlob)
	{
		return ::W32_IMPL_D3DStripShader(a_srcData, a_srcDataSize, a_stripFlags, a_strippedBlob);
	}

	HRESULT D3DWriteBlobToFile(ID3DBlob* a_blob, const wchar_t* a_fileName, bool a_overwrite)
	{
		return ::W32_IMPL_D3DWriteBlobToFile(a_blob, a_fileName, static_cast<REX::W32::BOOL>(a_overwrite));
	}
}
