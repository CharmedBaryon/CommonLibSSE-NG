#include "REX/W32/ADVAPI32.h"
#include "REX/W32/BCRYPT.h"
#include "REX/W32/D3D11.h"
#include "REX/W32/D3DCOMPILER.h"
#include "REX/W32/DBGHELP.h"
#include "REX/W32/DXGI.h"
#include "REX/W32/KERNEL32.h"
#include "REX/W32/NT.h"
#include "REX/W32/OLE32.h"
#include "REX/W32/SHELL32.h"
#include "REX/W32/USER32.h"
#include "REX/W32/VERSION.h"

// ADVAPI32

REX_W32_IMPORT(std::int32_t, RegGetValueA, REX::W32::HKEY, const char*, const char*, std::uint32_t, std::uint32_t*, void*, std::uint32_t*);
REX_W32_IMPORT(std::int32_t, RegGetValueW, REX::W32::HKEY, const wchar_t*, const wchar_t*, std::uint32_t, std::uint32_t*, void*, std::uint32_t*);

namespace REX::W32
{
	std::int32_t RegGetValueA(HKEY a_key, const char* a_subKey, const char* a_value, std::uint32_t a_flags, std::uint32_t* a_type, void* a_data, std::uint32_t* a_dataLen)
	{
		return ::W32_IMPL_RegGetValueA(a_key, a_subKey, a_value, a_flags, a_type, a_data, a_dataLen);
	}

	std::int32_t RegGetValueW(HKEY a_key, const wchar_t* a_subKey, const wchar_t* a_value, std::uint32_t a_flags, std::uint32_t* a_type, void* a_data, std::uint32_t* a_dataLen)
	{
		return ::W32_IMPL_RegGetValueW(a_key, a_subKey, a_value, a_flags, a_type, a_data, a_dataLen);
	}
}

// BCRYPT

REX_W32_IMPORT(REX::W32::NTSTATUS, BCryptOpenAlgorithmProvider, REX::W32::BCRYPT_ALG_HANDLE*, const wchar_t*, const wchar_t*, std::uint32_t);
REX_W32_IMPORT(REX::W32::NTSTATUS, BCryptCloseAlgorithmProvider, REX::W32::BCRYPT_ALG_HANDLE, std::uint32_t);
REX_W32_IMPORT(REX::W32::NTSTATUS, BCryptCreateHash, REX::W32::BCRYPT_ALG_HANDLE, BCRYPT_HASH_HANDLE*, std::uint8_t*, std::uint32_t, std::uint8_t*, std::uint32_t, std::uint32_t);
REX_W32_IMPORT(REX::W32::NTSTATUS, BCryptDestroyHash, REX::W32::BCRYPT_HASH_HANDLE);
REX_W32_IMPORT(REX::W32::NTSTATUS, BCryptFinishHash, REX::W32::BCRYPT_HASH_HANDLE, std::uint8_t*, std::uint32_t, std::uint32_t);
REX_W32_IMPORT(REX::W32::NTSTATUS, BCryptGetProperty, REX::W32::BCRYPT_HANDLE, const wchar_t*, std::uint8_t*, std::uint32_t, std::uint32_t*, std::uint32_t);
REX_W32_IMPORT(REX::W32::NTSTATUS, BCryptHashData, REX::W32::BCRYPT_HASH_HANDLE, std::uint8_t*, std::uint32_t, std::uint32_t);

namespace REX::W32
{
	NTSTATUS BCryptOpenAlgorithmProvider(BCRYPT_ALG_HANDLE* a_algorithm, const wchar_t* a_id, const wchar_t* a_impl, std::uint32_t a_flags)
	{
		return ::W32_IMPL_BCryptOpenAlgorithmProvider(a_algorithm, a_id, a_impl, a_flags);
	}

	NTSTATUS BCryptCloseAlgorithmProvider(BCRYPT_ALG_HANDLE a_algorithm, std::uint32_t a_flags)
	{
		return ::W32_IMPL_BCryptCloseAlgorithmProvider(a_algorithm, a_flags);
	}

	NTSTATUS BCryptCreateHash(BCRYPT_ALG_HANDLE a_algorithm, BCRYPT_HASH_HANDLE* a_hash, std::uint8_t* a_hashObject, std::uint32_t a_hashObjectSize, std::uint8_t* a_secret, std::uint32_t a_secretSize, std::uint32_t a_flags)
	{
		return ::W32_IMPL_BCryptCreateHash(a_algorithm, a_hash, a_hashObject, a_hashObjectSize, a_secret, a_secretSize, a_flags);
	}

	NTSTATUS BCryptDestroyHash(BCRYPT_HASH_HANDLE a_hash)
	{
		return ::W32_IMPL_BCryptDestroyHash(a_hash);
	}

	NTSTATUS BCryptFinishHash(BCRYPT_HASH_HANDLE a_hash, std::uint8_t* a_output, std::uint32_t a_outputSize, std::uint32_t a_flags)
	{
		return ::W32_IMPL_BCryptFinishHash(a_hash, a_output, a_outputSize, a_flags);
	}

	NTSTATUS BCryptGetProperty(BCRYPT_HANDLE a_object, const wchar_t* a_property, std::uint8_t* a_output, std::uint32_t a_outputSize, std::uint32_t* a_result, std::uint32_t a_flags)
	{
		return ::W32_IMPL_BCryptGetProperty(a_object, a_property, a_output, a_outputSize, a_result, a_flags);
	}

	NTSTATUS BCryptHashData(BCRYPT_HASH_HANDLE a_hash, std::uint8_t* a_input, std::uint32_t a_inputSize, std::uint32_t a_flags)
	{
		return ::W32_IMPL_BCryptHashData(a_hash, a_input, a_inputSize, a_flags);
	}
}

// D3D11

REX_W32_IMPORT(std::int32_t, D3D11CreateDevice, REX::W32::IDXGIAdapter*, REX::W32::D3D_DRIVER_TYPE, REX::W32::HMODULE, std::uint32_t, const REX::W32::D3D_FEATURE_LEVEL*, std::uint32_t, std::uint32_t, REX::W32::ID3D11Device**, REX::W32::D3D_FEATURE_LEVEL*, REX::W32::ID3D11DeviceContext**);
REX_W32_IMPORT(std::int32_t, D3D11CreateDeviceAndSwapChain, REX::W32::IDXGIAdapter*, REX::W32::D3D_DRIVER_TYPE, REX::W32::HMODULE, std::uint32_t, const REX::W32::D3D_FEATURE_LEVEL*, std::uint32_t, std::uint32_t, const REX::W32::DXGI_SWAP_CHAIN_DESC*, REX::W32::IDXGISwapChain**, REX::W32::ID3D11Device**, REX::W32::D3D_FEATURE_LEVEL*, REX::W32::ID3D11DeviceContext**);

namespace REX::W32
{
	HRESULT D3D11CreateDevice(IDXGIAdapter* a_adapter, D3D_DRIVER_TYPE a_driverType, HMODULE a_software, std::uint32_t a_flags, const D3D_FEATURE_LEVEL* a_pFeatureLevels, std::uint32_t a_featureLevels, std::uint32_t a_sdkVersion, ID3D11Device** a_device, D3D_FEATURE_LEVEL* a_pFeatureLevel, ID3D11DeviceContext** a_immediateContext) noexcept
	{
		return ::W32_IMPL_D3D11CreateDevice(a_adapter, a_driverType, a_software, a_flags, a_pFeatureLevels, a_featureLevels, a_sdkVersion, a_device, a_pFeatureLevel, a_immediateContext);
	}

	HRESULT D3D11CreateDeviceAndSwapChain(IDXGIAdapter* a_adapter, D3D_DRIVER_TYPE a_driverType, HMODULE a_software, std::uint32_t a_flags, const D3D_FEATURE_LEVEL* a_pFeatureLevels, std::uint32_t a_featureLevels, std::uint32_t a_sdkVersion, const DXGI_SWAP_CHAIN_DESC* a_swapChainDesc, IDXGISwapChain** a_swapChain, ID3D11Device** a_device, D3D_FEATURE_LEVEL* a_pFeatureLevel, ID3D11DeviceContext** a_immediateContext) noexcept
	{
		return ::W32_IMPL_D3D11CreateDeviceAndSwapChain(a_adapter, a_driverType, a_software, a_flags, a_pFeatureLevels, a_featureLevels, a_sdkVersion, a_swapChainDesc, a_swapChain, a_device, a_pFeatureLevel, a_immediateContext);
	}
}

// D3DCOMPILER

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

// DBGHELP

REX_W32_IMPORT(std::uint32_t, UnDecorateSymbolName, const char*, char*, std::uint32_t, std::uint32_t);
REX_W32_IMPORT(std::uint32_t, UnDecorateSymbolNameW, const wchar_t*, wchar_t*, std::uint32_t, std::uint32_t);

namespace REX::W32
{
	std::uint32_t UnDecorateSymbolName(const char* a_name, char* a_buf, std::uint32_t a_bufLen, std::uint32_t a_flags) noexcept
	{
		return ::W32_IMPL_UnDecorateSymbolName(a_name, a_buf, a_bufLen, a_flags);
	}

	std::uint32_t UnDecorateSymbolNameW(const wchar_t* a_name, wchar_t* a_buf, std::uint32_t a_bufLen, std::uint32_t a_flags) noexcept
	{
		return ::W32_IMPL_UnDecorateSymbolNameW(a_name, a_buf, a_bufLen, a_flags);
	}
}

// DXGI

REX_W32_IMPORT(std::int32_t, CreateDXGIFactory, const IID&, void**);
REX_W32_IMPORT(std::int32_t, CreateDXGIFactory1, const IID&, void**);

namespace REX::W32
{
	HRESULT CreateDXGIFactory(const IID& a_iid, void** a_factory) noexcept
	{
		return ::W32_IMPL_CreateDXGIFactory(a_iid, a_factory);
	}

	HRESULT CreateDXGIFactory1(const IID& a_iid, void** a_factory) noexcept
	{
		return ::W32_IMPL_CreateDXGIFactory1(a_iid, a_factory);
	}
}

// KERNEL32

REX_W32_IMPORT(REX::W32::BOOL, CloseHandle, REX::W32::HANDLE);
REX_W32_IMPORT(REX::W32::HANDLE, CreateFileA, const char*, std::uint32_t, std::uint32_t, REX::W32::SECURITY_ATTRIBUTES*, std::uint32_t, std::uint32_t, REX::W32::HANDLE);
REX_W32_IMPORT(REX::W32::HANDLE, CreateFileW, const wchar_t*, std::uint32_t, std::uint32_t, REX::W32::SECURITY_ATTRIBUTES*, std::uint32_t, std::uint32_t, REX::W32::HANDLE);
REX_W32_IMPORT(REX::W32::HANDLE, CreateFileMappingA, REX::W32::HANDLE, REX::W32::SECURITY_ATTRIBUTES*, std::uint32_t, std::uint32_t, std::uint32_t, const char*);
REX_W32_IMPORT(REX::W32::HANDLE, CreateFileMappingW, REX::W32::HANDLE, REX::W32::SECURITY_ATTRIBUTES*, std::uint32_t, std::uint32_t, std::uint32_t, const wchar_t*);
REX_W32_IMPORT(REX::W32::BOOL, CreateProcessA, const char*, char*, REX::W32::SECURITY_ATTRIBUTES*, REX::W32::SECURITY_ATTRIBUTES*, REX::W32::BOOL, std::uint32_t, void*, const char*, REX::W32::STARTUPINFOA*, REX::W32::PROCESS_INFORMATION*);
REX_W32_IMPORT(REX::W32::BOOL, CreateProcessW, const wchar_t*, wchar_t*, REX::W32::SECURITY_ATTRIBUTES*, REX::W32::SECURITY_ATTRIBUTES*, REX::W32::BOOL, std::uint32_t, void*, const wchar_t*, REX::W32::STARTUPINFOW*, REX::W32::PROCESS_INFORMATION*);
REX_W32_IMPORT(REX::W32::HANDLE, CreateRemoteThread, REX::W32::HANDLE, REX::W32::SECURITY_ATTRIBUTES*, std::size_t, REX::W32::THREAD_START_ROUTINE*, void*, std::uint32_t, std::uint32_t*);
REX_W32_IMPORT(REX::W32::HANDLE, CreateSemaphoreA, REX::W32::SECURITY_ATTRIBUTES*, std::int32_t, std::int32_t, const char*);
REX_W32_IMPORT(REX::W32::HANDLE, CreateThread, REX::W32::SECURITY_ATTRIBUTES*, std::size_t, REX::W32::THREAD_START_ROUTINE*, void*, std::uint32_t, std::uint32_t*);
REX_W32_IMPORT(void, DeleteCriticalSection, REX::W32::CRITICAL_SECTION*);
REX_W32_IMPORT(void, EnterCriticalSection, REX::W32::CRITICAL_SECTION*);
REX_W32_IMPORT(std::uint32_t, ExpandEnvironmentStringsA, const char*, char*, std::uint32_t);
REX_W32_IMPORT(std::uint32_t, ExpandEnvironmentStringsW, const wchar_t*, wchar_t*, std::uint32_t);
REX_W32_IMPORT(REX::W32::BOOL, FindClose, REX::W32::HANDLE);
REX_W32_IMPORT(REX::W32::HANDLE, FindFirstFileA, const char*, REX::W32::WIN32_FIND_DATAA*);
REX_W32_IMPORT(REX::W32::HANDLE, FindFirstFileW, const wchar_t*, REX::W32::WIN32_FIND_DATAW*);
REX_W32_IMPORT(REX::W32::BOOL, FindNextFileA, REX::W32::HANDLE, REX::W32::WIN32_FIND_DATAA*);
REX_W32_IMPORT(REX::W32::BOOL, FindNextFileW, REX::W32::HANDLE, REX::W32::WIN32_FIND_DATAW*);
REX_W32_IMPORT(REX::W32::BOOL, FlushInstructionCache, REX::W32::HANDLE, const void*, std::size_t);
REX_W32_IMPORT(REX::W32::BOOL, FreeLibrary, REX::W32::HMODULE);
REX_W32_IMPORT(REX::W32::BOOL, GetComputerNameA, char*, std::uint32_t*);
REX_W32_IMPORT(REX::W32::BOOL, GetComputerNameW, wchar_t*, std::uint32_t*);
REX_W32_IMPORT(std::uint32_t, GetCurrentDirectoryA, std::uint32_t, char*);
REX_W32_IMPORT(std::uint32_t, GetCurrentDirectoryW, std::uint32_t, wchar_t*);
REX_W32_IMPORT(REX::W32::HANDLE, GetCurrentProcess);
REX_W32_IMPORT(std::uint32_t, GetCurrentThreadId);
REX_W32_IMPORT(std::uint32_t, GetEnvironmentVariableA, const char*, char*, std::uint32_t);
REX_W32_IMPORT(std::uint32_t, GetEnvironmentVariableW, const wchar_t*, wchar_t*, std::uint32_t);
REX_W32_IMPORT(REX::W32::BOOL, GetFileSizeEx, REX::W32::HANDLE, REX::W32::LARGE_INTEGER*);
REX_W32_IMPORT(std::uint32_t, GetLastError);
REX_W32_IMPORT(std::uint32_t, GetModuleFileNameA, REX::W32::HMODULE, char*, std::uint32_t);
REX_W32_IMPORT(std::uint32_t, GetModuleFileNameW, REX::W32::HMODULE, wchar_t*, std::uint32_t);
REX_W32_IMPORT(REX::W32::HMODULE, GetModuleHandleA, const char*);
REX_W32_IMPORT(REX::W32::HMODULE, GetModuleHandleW, const wchar_t*);
REX_W32_IMPORT(std::uint32_t, GetPrivateProfileIntA, const char*, const char*, std::int32_t, const char*);
REX_W32_IMPORT(std::uint32_t, GetPrivateProfileIntW, const wchar_t*, const wchar_t*, std::int32_t, const wchar_t*);
REX_W32_IMPORT(std::uint32_t, GetPrivateProfileStringA, const char*, const char*, const char*, char*, std::uint32_t, const char*);
REX_W32_IMPORT(std::uint32_t, GetPrivateProfileStringW, const wchar_t*, const wchar_t*, const wchar_t*, wchar_t*, std::uint32_t, const wchar_t*);
REX_W32_IMPORT(void*, GetProcAddress, REX::W32::HMODULE, const char*);
REX_W32_IMPORT(void, GetSystemInfo, REX::W32::SYSTEM_INFO*);
REX_W32_IMPORT(REX::W32::BOOL, InitializeCriticalSectionAndSpinCount, REX::W32::CRITICAL_SECTION*, std::uint32_t);
REX_W32_IMPORT(REX::W32::BOOL, IsDebuggerPresent);
REX_W32_IMPORT(std::int32_t, LCMapStringEx, const wchar_t*, std::uint32_t, const wchar_t*, std::int32_t, wchar_t*, std::int32_t, REX::W32::NLSVERSIONINFO*, void*, std::intptr_t);
REX_W32_IMPORT(void, LeaveCriticalSection, REX::W32::CRITICAL_SECTION*);
REX_W32_IMPORT(REX::W32::HMODULE, LoadLibraryA, const char*);
REX_W32_IMPORT(REX::W32::HMODULE, LoadLibraryW, const wchar_t*);
REX_W32_IMPORT(void*, MapViewOfFile, REX::W32::HANDLE, std::uint32_t, std::uint32_t, std::uint32_t, std::size_t);
REX_W32_IMPORT(void*, MapViewOfFileEx, REX::W32::HANDLE, std::uint32_t, std::uint32_t, std::uint32_t, std::size_t, void*);
REX_W32_IMPORT(std::int32_t, MultiByteToWideChar, std::uint32_t, std::uint32_t, const char*, std::int32_t, wchar_t*, std::int32_t);
REX_W32_IMPORT(REX::W32::HANDLE, OpenFileMappingA, std::uint32_t, REX::W32::BOOL, const char*);
REX_W32_IMPORT(REX::W32::HANDLE, OpenFileMappingW, std::uint32_t, REX::W32::BOOL, const wchar_t*);
REX_W32_IMPORT(void, OutputDebugStringA, const char*);
REX_W32_IMPORT(void, OutputDebugStringW, const wchar_t*);
REX_W32_IMPORT(REX::W32::BOOL, QueryPerformanceCounter, std::int64_t*);
REX_W32_IMPORT(REX::W32::BOOL, QueryPerformanceFrequency, std::int64_t*);
REX_W32_IMPORT(std::uint32_t, ResumeThread, REX::W32::HANDLE);
REX_W32_IMPORT(REX::W32::BOOL, SetEnvironmentVariableA, const char*, const char*);
REX_W32_IMPORT(REX::W32::BOOL, SetEnvironmentVariableW, const wchar_t*, const wchar_t*);
REX_W32_IMPORT(void, Sleep, std::uint32_t);
REX_W32_IMPORT(REX::W32::BOOL, TerminateProcess, REX::W32::HANDLE, std::uint32_t);
REX_W32_IMPORT(void*, TlsGetValue, std::uint32_t);
REX_W32_IMPORT(REX::W32::BOOL, TlsSetValue, std::uint32_t, void*);
REX_W32_IMPORT(REX::W32::BOOL, UnmapViewOfFile, const void*);
REX_W32_IMPORT(void*, VirtualAlloc, void*, std::size_t, std::uint32_t, std::uint32_t);
REX_W32_IMPORT(void*, VirtualAllocEx, REX::W32::HANDLE, void*, std::size_t, std::uint32_t, std::uint32_t);
REX_W32_IMPORT(REX::W32::BOOL, VirtualFree, void*, std::size_t, std::uint32_t);
REX_W32_IMPORT(REX::W32::BOOL, VirtualFreeEx, REX::W32::HANDLE, void*, std::size_t, std::uint32_t);
REX_W32_IMPORT(REX::W32::BOOL, VirtualProtect, void*, std::size_t, std::uint32_t, std::uint32_t*);
REX_W32_IMPORT(REX::W32::BOOL, VirtualProtectEx, REX::W32::HANDLE, void*, std::size_t, std::uint32_t, std::uint32_t*);
REX_W32_IMPORT(std::size_t, VirtualQuery, const void*, MEMORY_BASIC_INFORMATION*, std::size_t);
REX_W32_IMPORT(std::size_t, VirtualQueryEx, REX::W32::HANDLE, const void*, MEMORY_BASIC_INFORMATION*, std::size_t);
REX_W32_IMPORT(std::uint32_t, WaitForSingleObject, REX::W32::HANDLE, std::uint32_t);
REX_W32_IMPORT(std::uint32_t, WaitForSingleObjectEx, REX::W32::HANDLE, std::uint32_t, REX::W32::BOOL);
REX_W32_IMPORT(std::int32_t, WideCharToMultiByte, std::uint32_t, std::uint32_t, const wchar_t*, std::int32_t, char*, std::int32_t, const char*, std::int32_t*);
REX_W32_IMPORT(REX::W32::BOOL, WriteProcessMemory, REX::W32::HANDLE, void*, const void*, std::size_t, std::size_t*);

extern "C" REX::W32::IMAGE_DOS_HEADER __ImageBase;

namespace REX::W32
{
	bool CloseHandle(HANDLE a_handle) noexcept
	{
		return ::W32_IMPL_CloseHandle(a_handle);
	}

	HANDLE CreateFileA(const char* a_fileName, std::uint32_t a_desiredAccess, std::uint32_t a_shareMode, SECURITY_ATTRIBUTES* a_attributes, std::uint32_t a_creationDisposition, std::uint32_t a_flags, HANDLE a_templateFile)
	{
		return ::W32_IMPL_CreateFileA(a_fileName, a_desiredAccess, a_shareMode, a_attributes, a_creationDisposition, a_flags, a_templateFile);
	}

	HANDLE CreateFileW(const wchar_t* a_fileName, std::uint32_t a_desiredAccess, std::uint32_t a_shareMode, SECURITY_ATTRIBUTES* a_attributes, std::uint32_t a_creationDisposition, std::uint32_t a_flags, HANDLE a_templateFile) noexcept
	{
		return ::W32_IMPL_CreateFileW(a_fileName, a_desiredAccess, a_shareMode, a_attributes, a_creationDisposition, a_flags, a_templateFile);
	}

	HANDLE CreateFileMappingA(HANDLE a_file, SECURITY_ATTRIBUTES* a_attributes, std::uint32_t a_protect, std::uint32_t a_maxSizeHigh, std::uint32_t a_maxSizeLow, const char* a_name) noexcept
	{
		return ::W32_IMPL_CreateFileMappingA(a_file, a_attributes, a_protect, a_maxSizeHigh, a_maxSizeLow, a_name);
	}

	HANDLE CreateFileMappingW(HANDLE a_file, SECURITY_ATTRIBUTES* a_attributes, std::uint32_t a_protect, std::uint32_t a_maxSizeHigh, std::uint32_t a_maxSizeLow, const wchar_t* a_name) noexcept
	{
		return ::W32_IMPL_CreateFileMappingW(a_file, a_attributes, a_protect, a_maxSizeHigh, a_maxSizeLow, a_name);
	}

	bool CreateProcessA(const char* a_name, char* a_cmd, SECURITY_ATTRIBUTES* a_procAttr, SECURITY_ATTRIBUTES* a_threadAttr, bool a_inheritHandles, std::uint32_t a_flags, void* a_env, const char* a_curDir, STARTUPINFOA* a_startInfo, PROCESS_INFORMATION* a_procInfo) noexcept
	{
		return ::W32_IMPL_CreateProcessA(a_name, a_cmd, a_procAttr, a_threadAttr, a_inheritHandles, a_flags, a_env, a_curDir, a_startInfo, a_procInfo);
	}

	bool CreateProcessW(const wchar_t* a_name, wchar_t* a_cmd, SECURITY_ATTRIBUTES* a_procAttr, SECURITY_ATTRIBUTES* a_threadAttr, bool a_inheritHandles, std::uint32_t a_flags, void* a_env, const wchar_t* a_curDir, STARTUPINFOW* a_startInfo, PROCESS_INFORMATION* a_procInfo) noexcept
	{
		return ::W32_IMPL_CreateProcessW(a_name, a_cmd, a_procAttr, a_threadAttr, a_inheritHandles, a_flags, a_env, a_curDir, a_startInfo, a_procInfo);
	}

	HANDLE CreateRemoteThread(HANDLE a_process, SECURITY_ATTRIBUTES* a_threadAttr, std::size_t a_stackSize, THREAD_START_ROUTINE* a_startAddr, void* a_param, std::uint32_t a_flags, std::uint32_t* a_threadID) noexcept
	{
		return ::W32_IMPL_CreateRemoteThread(a_process, a_threadAttr, a_stackSize, a_startAddr, a_param, a_flags, a_threadID);
	}

	HANDLE CreateSemaphoreA(SECURITY_ATTRIBUTES* a_semaphoreAttr, std::int32_t a_initCount, std::int32_t a_maxCount, const char* a_name)
	{
		return ::W32_IMPL_CreateSemaphoreA(a_semaphoreAttr, a_initCount, a_maxCount, a_name);
	}

	HANDLE CreateThread(SECURITY_ATTRIBUTES* a_threadAttr, std::size_t a_stackSize, THREAD_START_ROUTINE* a_startAddr, void* a_param, std::uint32_t a_flags, std::uint32_t* a_threadID) noexcept
	{
		return ::W32_IMPL_CreateThread(a_threadAttr, a_stackSize, a_startAddr, a_param, a_flags, a_threadID);
	}

	void DeleteCriticalSection(CRITICAL_SECTION* a_criticalSection)
	{
		::W32_IMPL_DeleteCriticalSection(a_criticalSection);
	}

	void EnterCriticalSection(CRITICAL_SECTION* a_criticalSection)
	{
		::W32_IMPL_EnterCriticalSection(a_criticalSection);
	}

	std::uint32_t ExpandEnvironmentStringsA(const char* a_src, char* a_dst, std::uint32_t a_dstLen) noexcept
	{
		return ::W32_IMPL_ExpandEnvironmentStringsA(a_src, a_dst, a_dstLen);
	}

	std::uint32_t ExpandEnvironmentStringsW(const wchar_t* a_src, wchar_t* a_dst, std::uint32_t a_dstLen) noexcept
	{
		return ::W32_IMPL_ExpandEnvironmentStringsW(a_src, a_dst, a_dstLen);
	}

	bool FindClose(HANDLE a_file) noexcept
	{
		return ::W32_IMPL_FindClose(a_file);
	}

	HANDLE FindFirstFileA(const char* a_name, WIN32_FIND_DATAA* a_data) noexcept
	{
		return ::W32_IMPL_FindFirstFileA(a_name, a_data);
	}

	HANDLE FindFirstFileW(const wchar_t* a_name, WIN32_FIND_DATAW* a_data) noexcept
	{
		return ::W32_IMPL_FindFirstFileW(a_name, a_data);
	}

	bool FindNextFileA(HANDLE a_file, WIN32_FIND_DATAA* a_data) noexcept
	{
		return ::W32_IMPL_FindNextFileA(a_file, a_data);
	}

	bool FindNextFileW(HANDLE a_file, WIN32_FIND_DATAW* a_data) noexcept
	{
		return ::W32_IMPL_FindNextFileW(a_file, a_data);
	}

	bool FlushInstructionCache(HANDLE a_process, const void* a_baseAddr, std::size_t a_size) noexcept
	{
		return ::W32_IMPL_FlushInstructionCache(a_process, a_baseAddr, a_size);
	}

	bool FreeLibrary(HMODULE a_module) noexcept
	{
		return ::W32_IMPL_FreeLibrary(a_module);
	}

	bool GetComputerNameA(char* a_buffer, std::uint32_t* a_size) noexcept
	{
		return ::W32_IMPL_GetComputerNameA(a_buffer, a_size);
	}

	bool GetComputerNameW(wchar_t* a_buffer, std::uint32_t* a_size) noexcept
	{
		return ::W32_IMPL_GetComputerNameW(a_buffer, a_size);
	}

	std::uint32_t GetCurrentDirectoryA(std::uint32_t a_size, char* a_buffer) noexcept
	{
		return ::W32_IMPL_GetCurrentDirectoryA(a_size, a_buffer);
	}

	std::uint32_t GetCurrentDirectoryW(std::uint32_t a_size, wchar_t* a_buffer) noexcept
	{
		return ::W32_IMPL_GetCurrentDirectoryW(a_size, a_buffer);
	}

	HMODULE GetCurrentModule() noexcept
	{
		return reinterpret_cast<HMODULE>(std::addressof(__ImageBase));
	}

	HANDLE GetCurrentProcess() noexcept
	{
		return ::W32_IMPL_GetCurrentProcess();
	}

	std::uint32_t GetCurrentThreadId() noexcept
	{
		return ::W32_IMPL_GetCurrentThreadId();
	}

	std::uint32_t GetEnvironmentVariableA(const char* a_name, char* a_buf, std::uint32_t a_bufLen) noexcept
	{
		return ::W32_IMPL_GetEnvironmentVariableA(a_name, a_buf, a_bufLen);
	}

	std::uint32_t GetEnvironmentVariableW(const wchar_t* a_name, wchar_t* a_buf, std::uint32_t a_bufLen) noexcept
	{
		return ::W32_IMPL_GetEnvironmentVariableW(a_name, a_buf, a_bufLen);
	}

	bool GetFileSizeEx(HANDLE a_file, LARGE_INTEGER* a_fileSize) noexcept
	{
		return ::W32_IMPL_GetFileSizeEx(a_file, a_fileSize);
	}

	std::uint32_t GetLastError() noexcept
	{
		return ::W32_IMPL_GetLastError();
	}

	std::uint32_t GetModuleFileNameA(HMODULE a_module, char* a_name, std::uint32_t a_nameLen) noexcept
	{
		return ::W32_IMPL_GetModuleFileNameA(a_module, a_name, a_nameLen);
	}

	std::uint32_t GetModuleFileNameW(HMODULE a_module, wchar_t* a_name, std::uint32_t a_nameLen) noexcept
	{
		return ::W32_IMPL_GetModuleFileNameW(a_module, a_name, a_nameLen);
	}

	HMODULE GetModuleHandleA(const char* a_name) noexcept
	{
		return ::W32_IMPL_GetModuleHandleA(a_name);
	}

	HMODULE GetModuleHandleW(const wchar_t* a_name) noexcept
	{
		return ::W32_IMPL_GetModuleHandleW(a_name);
	}

	std::uint32_t GetPrivateProfileIntA(const char* a_app, const char* a_key, std::int32_t a_default, const char* a_name) noexcept
	{
		return ::W32_IMPL_GetPrivateProfileIntA(a_app, a_key, a_default, a_name);
	}

	std::uint32_t GetPrivateProfileIntW(const wchar_t* a_app, const wchar_t* a_key, std::int32_t a_default, const wchar_t* a_name) noexcept
	{
		return ::W32_IMPL_GetPrivateProfileIntW(a_app, a_key, a_default, a_name);
	}

	std::uint32_t GetPrivateProfileStringA(const char* a_app, const char* a_key, const char* a_default, char* a_buf, std::uint32_t a_bufLen, const char* a_name) noexcept
	{
		return ::W32_IMPL_GetPrivateProfileStringA(a_app, a_key, a_default, a_buf, a_bufLen, a_name);
	}

	std::uint32_t GetPrivateProfileStringW(const wchar_t* a_app, const wchar_t* a_key, const wchar_t* a_default, wchar_t* a_buf, std::uint32_t a_bufLen, const wchar_t* a_name) noexcept
	{
		return ::W32_IMPL_GetPrivateProfileStringW(a_app, a_key, a_default, a_buf, a_bufLen, a_name);
	}

	void* GetProcAddress(HMODULE a_module, const char* a_name) noexcept
	{
		return ::W32_IMPL_GetProcAddress(a_module, a_name);
	}

	void GetSystemInfo(SYSTEM_INFO* a_info) noexcept
	{
		return ::W32_IMPL_GetSystemInfo(a_info);
	}

	bool IMAGE_SNAP_BY_ORDINAL64(std::uint64_t a_ordinal) noexcept
	{
		return (a_ordinal & IMAGE_ORDINAL_FLAG64) != 0;
	}

	IMAGE_SECTION_HEADER* IMAGE_FIRST_SECTION(const IMAGE_NT_HEADERS64* a_header) noexcept
	{
		constexpr auto opt = __builtin_offsetof(IMAGE_NT_HEADERS64, optionalHeader);
		const auto     optSize = a_header->fileHeader.optionalHeaderSize;
		const auto     section = reinterpret_cast<std::uintptr_t>(a_header) + opt + optSize;
		return reinterpret_cast<IMAGE_SECTION_HEADER*>(section);
	}

	bool InitializeCriticalSectionAndSpinCount(CRITICAL_SECTION* a_criticalSection, std::uint32_t a_spinCount)
	{
		return ::W32_IMPL_InitializeCriticalSectionAndSpinCount(a_criticalSection, a_spinCount);
	}

	std::uint32_t InterlockedCompareExchange(volatile std::uint32_t* a_target, std::uint32_t a_value, std::uint32_t a_compare) noexcept
	{
		return _InterlockedCompareExchange((volatile long*)a_target, a_value, a_compare);
	}

	std::uint64_t InterlockedCompareExchange64(volatile std::uint64_t* a_target, std::uint64_t a_value, std::uint64_t a_compare) noexcept
	{
		return _InterlockedCompareExchange64((volatile long long*)a_target, a_value, a_compare);
	}

	std::uint32_t InterlockedDecrement(volatile std::uint32_t* a_target) noexcept
	{
		return _InterlockedDecrement((volatile long*)a_target);
	}

	std::uint64_t InterlockedDecrement64(volatile std::uint64_t* a_target) noexcept
	{
		return _InterlockedDecrement64((volatile long long*)a_target);
	}

	std::uint32_t InterlockedExchange(volatile std::uint32_t* a_target, std::uint32_t a_value) noexcept
	{
		return _InterlockedExchange((volatile long*)a_target, a_value);
	}

	std::uint64_t InterlockedExchange64(volatile std::uint64_t* a_target, std::uint64_t a_value) noexcept
	{
		return _InterlockedExchange64((volatile long long*)a_target, a_value);
	}

	std::uint32_t InterlockedIncrement(volatile std::uint32_t* a_target) noexcept
	{
		return _InterlockedIncrement((volatile long*)a_target);
	}

	std::uint64_t InterlockedIncrement64(volatile std::uint64_t* a_target) noexcept
	{
		return _InterlockedIncrement64((volatile long long*)a_target);
	}

	bool IsDebuggerPresent() noexcept
	{
		return ::W32_IMPL_IsDebuggerPresent();
	}

	std::int32_t LCMapStringEx(const wchar_t* a_locale, std::uint32_t a_flags, const wchar_t* a_src, std::int32_t a_srcLen, wchar_t* a_dst, std::int32_t a_dstLen, NLSVERSIONINFO* a_info, void* a_reserved, std::intptr_t a_sortHandle) noexcept
	{
		return ::W32_IMPL_LCMapStringEx(a_locale, a_flags, a_src, a_srcLen, a_dst, a_dstLen, a_info, a_reserved, a_sortHandle);
	}

	void LeaveCriticalSection(CRITICAL_SECTION* a_criticalSection)
	{
		::W32_IMPL_LeaveCriticalSection(a_criticalSection);
	}

	HMODULE LoadLibraryA(const char* a_name) noexcept
	{
		return ::W32_IMPL_LoadLibraryA(a_name);
	}

	HMODULE LoadLibraryW(const wchar_t* a_name) noexcept
	{
		return ::W32_IMPL_LoadLibraryW(a_name);
	}

	void* MapViewOfFile(HANDLE a_object, std::uint32_t a_desiredAccess, std::uint32_t a_fileOffsetHi, std::uint32_t a_fileOffsetLo, std::size_t a_numBytes) noexcept
	{
		return ::W32_IMPL_MapViewOfFile(a_object, a_desiredAccess, a_fileOffsetHi, a_fileOffsetLo, a_numBytes);
	}

	void* MapViewOfFileEx(HANDLE a_object, std::uint32_t a_desiredAccess, std::uint32_t a_fileOffsetHi, std::uint32_t a_fileOffsetLo, std::size_t a_numBytes, void* a_baseAddr) noexcept
	{
		return ::W32_IMPL_MapViewOfFileEx(a_object, a_desiredAccess, a_fileOffsetHi, a_fileOffsetLo, a_numBytes, a_baseAddr);
	}

	std::int32_t MultiByteToWideChar(std::uint32_t a_codePage, std::uint32_t a_flags, const char* a_src, std::int32_t a_srcLen, wchar_t* a_dst, std::int32_t a_dstLen) noexcept
	{
		return ::W32_IMPL_MultiByteToWideChar(a_codePage, a_flags, a_src, a_srcLen, a_dst, a_dstLen);
	}

	HANDLE OpenFileMappingA(std::uint32_t a_desiredAccess, bool a_inheritHandle, const char* a_name) noexcept
	{
		return ::W32_IMPL_OpenFileMappingA(a_desiredAccess, a_inheritHandle, a_name);
	}

	HANDLE OpenFileMappingW(std::uint32_t a_desiredAccess, bool a_inheritHandle, const wchar_t* a_name) noexcept
	{
		return ::W32_IMPL_OpenFileMappingW(a_desiredAccess, a_inheritHandle, a_name);
	}

	void OutputDebugStringA(const char* a_str) noexcept
	{
		::W32_IMPL_OutputDebugStringA(a_str);
	}

	void OutputDebugStringW(const wchar_t* a_str) noexcept
	{
		::W32_IMPL_OutputDebugStringW(a_str);
	}

	bool QueryPerformanceCounter(std::int64_t* a_counter) noexcept
	{
		return ::W32_IMPL_QueryPerformanceCounter(a_counter);
	}

	bool QueryPerformanceFrequency(std::int64_t* a_frequency) noexcept
	{
		return ::W32_IMPL_QueryPerformanceFrequency(a_frequency);
	}

	std::uint32_t ResumeThread(HANDLE a_handle) noexcept
	{
		return ::W32_IMPL_ResumeThread(a_handle);
	}

	bool SetEnvironmentVariableA(const char* a_name, const char* a_value) noexcept
	{
		return ::W32_IMPL_SetEnvironmentVariableA(a_name, a_value);
	}

	bool SetEnvironmentVariableW(const wchar_t* a_name, const wchar_t* a_value) noexcept
	{
		return ::W32_IMPL_SetEnvironmentVariableW(a_name, a_value);
	}

	void Sleep(std::uint32_t a_milliseconds) noexcept
	{
		::W32_IMPL_Sleep(a_milliseconds);
	}

	bool TerminateProcess(HANDLE a_process, std::uint32_t a_exitCode) noexcept
	{
		return ::W32_IMPL_TerminateProcess(a_process, a_exitCode);
	}

	void* TlsGetValue(std::uint32_t a_index) noexcept
	{
		return ::W32_IMPL_TlsGetValue(a_index);
	}

	bool TlsSetValue(std::uint32_t a_index, void* a_value) noexcept
	{
		return ::W32_IMPL_TlsSetValue(a_index, a_value);
	}

	bool UnmapViewOfFile(const void* a_baseAddress) noexcept
	{
		return ::W32_IMPL_UnmapViewOfFile(a_baseAddress);
	}

	void* VirtualAlloc(void* a_address, std::size_t a_size, std::uint32_t a_type, std::uint32_t a_protect) noexcept
	{
		return ::W32_IMPL_VirtualAlloc(a_address, a_size, a_type, a_protect);
	}

	void* VirtualAllocEx(HANDLE a_process, void* a_address, std::size_t a_size, std::uint32_t a_type, std::uint32_t a_protect) noexcept
	{
		return ::W32_IMPL_VirtualAllocEx(a_process, a_address, a_size, a_type, a_protect);
	}

	bool VirtualFree(void* a_address, std::size_t a_size, std::uint32_t a_type) noexcept
	{
		return ::W32_IMPL_VirtualFree(a_address, a_size, a_type);
	}

	bool VirtualFreeEx(HANDLE a_process, void* a_address, std::size_t a_size, std::uint32_t a_type) noexcept
	{
		return ::W32_IMPL_VirtualFreeEx(a_process, a_address, a_size, a_type);
	}

	bool VirtualProtect(void* a_address, std::size_t a_size, std::uint32_t a_newProtect, std::uint32_t* a_oldProtect) noexcept
	{
		return ::W32_IMPL_VirtualProtect(a_address, a_size, a_newProtect, a_oldProtect);
	}

	bool VirtualProtectEx(HANDLE a_process, void* a_address, std::size_t a_size, std::uint32_t a_newProtect, std::uint32_t* a_oldProtect) noexcept
	{
		return ::W32_IMPL_VirtualProtectEx(a_process, a_address, a_size, a_newProtect, a_oldProtect);
	}

	std::size_t VirtualQuery(const void* a_address, MEMORY_BASIC_INFORMATION* a_buf, std::size_t a_bufLen) noexcept
	{
		return ::W32_IMPL_VirtualQuery(a_address, a_buf, a_bufLen);
	}

	std::size_t VirtualQueryEx(HANDLE a_process, const void* a_address, MEMORY_BASIC_INFORMATION* a_buf, std::size_t a_bufLen) noexcept
	{
		return ::W32_IMPL_VirtualQueryEx(a_process, a_address, a_buf, a_bufLen);
	}

	std::uint32_t WaitForSingleObject(HANDLE a_handle, std::uint32_t a_milliseconds) noexcept
	{
		return ::W32_IMPL_WaitForSingleObject(a_handle, a_milliseconds);
	}

	std::uint32_t WaitForSingleObjectEx(HANDLE a_handle, std::uint32_t a_milliseconds, bool a_alertable) noexcept
	{
		return ::W32_IMPL_WaitForSingleObjectEx(a_handle, a_milliseconds, a_alertable);
	}

	std::int32_t WideCharToMultiByte(std::uint32_t a_codePage, std::uint32_t a_flags, const wchar_t* a_src, std::int32_t a_srcLen, char* a_dst, std::int32_t a_dstLen, const char* a_default, std::int32_t* a_defaultLen)
	{
		return ::W32_IMPL_WideCharToMultiByte(a_codePage, a_flags, a_src, a_srcLen, a_dst, a_dstLen, a_default, a_defaultLen);
	}

	bool WriteProcessMemory(HANDLE a_process, void* a_address, const void* a_buf, std::size_t a_bufLen, std::size_t* a_bufWritten) noexcept
	{
		return ::W32_IMPL_WriteProcessMemory(a_process, a_address, a_buf, a_bufLen, a_bufWritten);
	}
}

// NT
namespace REX::W32
{
	TEB* NtCurrentTeb() noexcept
	{
		return reinterpret_cast<TEB*>(__readgsqword(offsetof(NT_TIB, self)));
	}
}

// OLE32

REX_W32_IMPORT(void, CoTaskMemFree, void*);

namespace REX::W32
{
	void CoTaskMemFree(void* a_block) noexcept
	{
		::W32_IMPL_CoTaskMemFree(a_block);
	}
}

// SHELL32

REX_W32_IMPORT(std::int32_t, SHGetKnownFolderPath, const REX::W32::GUID&, std::uint32_t, void*, wchar_t**);

namespace REX::W32
{
	std::int32_t SHGetKnownFolderPath(const GUID& a_id, std::uint32_t a_flags, void* a_token, wchar_t** a_path) noexcept
	{
		return ::W32_IMPL_SHGetKnownFolderPath(a_id, a_flags, a_token, a_path);
	}
}

// USER32

REX_W32_IMPORT(REX::W32::BOOL, GetClientRect, REX::W32::HWND, REX::W32::RECT*);
REX_W32_IMPORT(std::int32_t, GetKeyNameTextA, std::int32_t, char*, std::int32_t);
REX_W32_IMPORT(std::int32_t, GetKeyNameTextW, std::int32_t, wchar_t*, std::int32_t);
REX_W32_IMPORT(std::int16_t, GetKeyState, std::int32_t);
REX_W32_IMPORT(REX::W32::BOOL, GetWindowRect, REX::W32::HWND, REX::W32::RECT*);
REX_W32_IMPORT(std::int32_t, MessageBoxA, REX::W32::HWND, const char*, const char*, std::uint32_t);
REX_W32_IMPORT(std::int32_t, MessageBoxW, REX::W32::HWND, const wchar_t*, const wchar_t*, std::uint32_t);
REX_W32_IMPORT(std::intptr_t, SetWindowLongPtrA, REX::W32::HWND, std::int32_t, std::intptr_t);
REX_W32_IMPORT(std::int32_t, ShowCursor, REX::W32::BOOL);

namespace REX::W32
{
	bool GetClientRect(HWND a_wnd, RECT* a_rect) noexcept
	{
		return ::W32_IMPL_GetClientRect(a_wnd, a_rect);
	}

	std::int32_t GetKeyNameTextA(std::int32_t a_param, char* a_buf, std::int32_t a_bufLen) noexcept
	{
		return ::W32_IMPL_GetKeyNameTextA(a_param, a_buf, a_bufLen);
	}

	std::int32_t GetKeyNameTextW(std::int32_t a_param, wchar_t* a_buf, std::int32_t a_bufLen) noexcept
	{
		return ::W32_IMPL_GetKeyNameTextW(a_param, a_buf, a_bufLen);
	}

	std::int16_t GetKeyState(std::int32_t a_key) noexcept
	{
		return ::W32_IMPL_GetKeyState(a_key);
	}

	bool GetWindowRect(HWND a_wnd, RECT* a_rect) noexcept
	{
		return ::W32_IMPL_GetWindowRect(a_wnd, a_rect);
	}

	std::int32_t MessageBoxA(HWND a_wnd, const char* a_text, const char* a_caption, std::uint32_t a_type) noexcept
	{
		return ::W32_IMPL_MessageBoxA(a_wnd, a_text, a_caption, a_type);
	}

	std::int32_t MessageBoxW(HWND a_wnd, const wchar_t* a_text, const wchar_t* a_caption, std::uint32_t a_type) noexcept
	{
		return ::W32_IMPL_MessageBoxW(a_wnd, a_text, a_caption, a_type);
	}

	std::intptr_t SetWindowLongPtrA(HWND a_wnd, std::int32_t a_index, std::intptr_t a_newPtr) noexcept
	{
		return ::W32_IMPL_SetWindowLongPtrA(a_wnd, a_index, a_newPtr);
	}

	std::int32_t ShowCursor(bool a_show) noexcept
	{
		return ::W32_IMPL_ShowCursor(a_show);
	}
}

// VERSION

REX_W32_IMPORT(REX::W32::BOOL, GetFileVersionInfoA, const char*, std::uint32_t, std::uint32_t, void*);
REX_W32_IMPORT(REX::W32::BOOL, GetFileVersionInfoW, const wchar_t*, std::uint32_t, std::uint32_t, void*);
REX_W32_IMPORT(std::uint32_t, GetFileVersionInfoSizeA, const char*, std::uint32_t*);
//REX_W32_IMPORT(std::uint32_t, GetFileVersionInfoSizeExA, std::uint32_t, const char*, std::uint32_t*);
REX_W32_IMPORT(std::uint32_t, GetFileVersionInfoSizeExW, std::uint32_t, const wchar_t*, std::uint32_t*);
REX_W32_IMPORT(std::uint32_t, GetFileVersionInfoSizeW, const wchar_t*, std::uint32_t*);
REX_W32_IMPORT(REX::W32::BOOL, VerQueryValueA, const void*, const char*, void**, std::uint32_t*);
REX_W32_IMPORT(REX::W32::BOOL, VerQueryValueW, const void*, const wchar_t*, void**, std::uint32_t*);

namespace REX::W32
{
	bool GetFileVersionInfoA(const char* a_name, std::uint32_t a_handle, std::uint32_t a_dataLen, void* a_data) noexcept
	{
		return ::W32_IMPL_GetFileVersionInfoA(a_name, a_handle, a_dataLen, a_data);
	}

	std::uint32_t GetFileVersionInfoSizeA(const char* a_name, std::uint32_t* a_handle) noexcept
	{
		return ::W32_IMPL_GetFileVersionInfoSizeA(a_name, a_handle);
	}

	/*
	std::uint32_t GetFileVersionInfoSizeExA(std::uint32_t a_flags, const char* a_name, std::uint32_t* a_handle) noexcept
	{
	    return ::W32_IMPL_GetFileVersionInfoSizeExA(a_flags, a_name, a_handle);
	}
	*/

	std::uint32_t GetFileVersionInfoSizeExW(std::uint32_t a_flags, const wchar_t* a_name, std::uint32_t* a_handle) noexcept
	{
		return ::W32_IMPL_GetFileVersionInfoSizeExW(a_flags, a_name, a_handle);
	}

	std::uint32_t GetFileVersionInfoSizeW(const wchar_t* a_name, std::uint32_t* a_handle) noexcept
	{
		return ::W32_IMPL_GetFileVersionInfoSizeW(a_name, a_handle);
	}

	bool GetFileVersionInfoW(const wchar_t* a_name, std::uint32_t a_handle, std::uint32_t a_dataLen, void* a_data) noexcept
	{
		return ::W32_IMPL_GetFileVersionInfoW(a_name, a_handle, a_dataLen, a_data);
	}

	bool VerQueryValueA(const void* a_block, const char* a_subBlock, void** a_buf, std::uint32_t* a_bufLen) noexcept
	{
		return ::W32_IMPL_VerQueryValueA(a_block, a_subBlock, a_buf, a_bufLen);
	}

	bool VerQueryValueW(const void* a_block, const wchar_t* a_subBlock, void** a_buf, std::uint32_t* a_bufLen) noexcept
	{
		return ::W32_IMPL_VerQueryValueW(a_block, a_subBlock, a_buf, a_bufLen);
	}
}
