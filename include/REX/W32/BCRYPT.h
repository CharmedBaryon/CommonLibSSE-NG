#pragma once

#include "REX/W32/BASE.h"

namespace REX::W32
{
	using BCRYPT_HANDLE = void*;
	using BCRYPT_ALG_HANDLE = void*;
	using BCRYPT_KEY_HANDLE = void*;
	using BCRYPT_HASH_HANDLE = void*;
	using BCRYPT_SECRET_HANDLE = void*;

	// algorithms
	inline constexpr auto BCRYPT_RSA_ALGORITHM{ L"RSA" };
	inline constexpr auto BCRYPT_RSA_SIGN_ALGORITHM{ L"RSA_SIGN" };
	inline constexpr auto BCRYPT_DH_ALGORITHM{ L"DH" };
	inline constexpr auto BCRYPT_DSA_ALGORITHM{ L"DSA" };
	inline constexpr auto BCRYPT_RC2_ALGORITHM{ L"RC2" };
	inline constexpr auto BCRYPT_RC4_ALGORITHM{ L"RC4" };
	inline constexpr auto BCRYPT_AES_ALGORITHM{ L"AES" };
	inline constexpr auto BCRYPT_DES_ALGORITHM{ L"DES" };
	inline constexpr auto BCRYPT_DESX_ALGORITHM{ L"DESX" };
	inline constexpr auto BCRYPT_3DES_ALGORITHM{ L"3DES" };
	inline constexpr auto BCRYPT_3DES_112_ALGORITHM{ L"3DES_112" };
	inline constexpr auto BCRYPT_MD2_ALGORITHM{ L"MD2" };
	inline constexpr auto BCRYPT_MD4_ALGORITHM{ L"MD4" };
	inline constexpr auto BCRYPT_MD5_ALGORITHM{ L"MD5" };
	inline constexpr auto BCRYPT_SHA1_ALGORITHM{ L"SHA1" };
	inline constexpr auto BCRYPT_SHA256_ALGORITHM{ L"SHA256" };
	inline constexpr auto BCRYPT_SHA384_ALGORITHM{ L"SHA384" };
	inline constexpr auto BCRYPT_SHA512_ALGORITHM{ L"SHA512" };
	inline constexpr auto BCRYPT_AES_GMAC_ALGORITHM{ L"AES-GMAC" };
	inline constexpr auto BCRYPT_AES_CMAC_ALGORITHM{ L"AES-CMAC" };
	inline constexpr auto BCRYPT_ECDSA_P256_ALGORITHM{ L"ECDSA_P256" };
	inline constexpr auto BCRYPT_ECDSA_P384_ALGORITHM{ L"ECDSA_P384" };
	inline constexpr auto BCRYPT_ECDSA_P521_ALGORITHM{ L"ECDSA_P521" };
	inline constexpr auto BCRYPT_ECDH_P256_ALGORITHM{ L"ECDH_P256" };
	inline constexpr auto BCRYPT_ECDH_P384_ALGORITHM{ L"ECDH_P384" };
	inline constexpr auto BCRYPT_ECDH_P521_ALGORITHM{ L"ECDH_P521" };
	inline constexpr auto BCRYPT_RNG_ALGORITHM{ L"RNG" };
	inline constexpr auto BCRYPT_RNG_FIPS186_DSA_ALGORITHM{ L"FIPS186DSARNG" };
	inline constexpr auto BCRYPT_RNG_DUAL_EC_ALGORITHM{ L"DUALECRNG" };

	// properties
	inline constexpr auto BCRYPT_OBJECT_LENGTH{ L"ObjectLength" };
	inline constexpr auto BCRYPT_ALGORITHM_NAME{ L"AlgorithmName" };
	inline constexpr auto BCRYPT_PROVIDER_HANDLE{ L"ProviderHandle" };
	inline constexpr auto BCRYPT_CHAINING_MODE{ L"ChainingMode" };
	inline constexpr auto BCRYPT_BLOCK_LENGTH{ L"BlockLength" };
	inline constexpr auto BCRYPT_KEY_LENGTH{ L"KeyLength" };
	inline constexpr auto BCRYPT_KEY_OBJECT_LENGTH{ L"KeyObjectLength" };
	inline constexpr auto BCRYPT_KEY_STRENGTH{ L"KeyStrength" };
	inline constexpr auto BCRYPT_KEY_LENGTHS{ L"KeyLengths" };
	inline constexpr auto BCRYPT_BLOCK_SIZE_LIST{ L"BlockSizeList" };
	inline constexpr auto BCRYPT_EFFECTIVE_KEY_LENGTH{ L"EffectiveKeyLength" };
	inline constexpr auto BCRYPT_HASH_LENGTH{ L"HashDigestLength" };
	inline constexpr auto BCRYPT_HASH_OID_LIST{ L"HashOIDList" };
	inline constexpr auto BCRYPT_PADDING_SCHEMES{ L"PaddingSchemes" };
	inline constexpr auto BCRYPT_SIGNATURE_LENGTH{ L"SignatureLength" };
	inline constexpr auto BCRYPT_HASH_BLOCK_LENGTH{ L"HashBlockLength" };
	inline constexpr auto BCRYPT_AUTH_TAG_LENGTH{ L"AuthTagLength" };
}

namespace REX::W32
{
	NTSTATUS BCryptOpenAlgorithmProvider(BCRYPT_ALG_HANDLE* a_algorithm, const wchar_t* a_id, const wchar_t* a_impl = nullptr, std::uint32_t a_flags = 0);
	NTSTATUS BCryptCloseAlgorithmProvider(BCRYPT_ALG_HANDLE a_algorithm, std::uint32_t a_flags = 0);
	NTSTATUS BCryptCreateHash(BCRYPT_ALG_HANDLE a_algorithm, BCRYPT_HASH_HANDLE* a_hash, std::uint8_t* a_hashObject = nullptr, std::uint32_t a_hashObjectSize = 0, std::uint8_t* a_secret = nullptr, std::uint32_t a_secretSize = 0, std::uint32_t a_flags = 0);
	NTSTATUS BCryptDestroyHash(BCRYPT_HASH_HANDLE a_hash);
	NTSTATUS BCryptFinishHash(BCRYPT_HASH_HANDLE a_hash, std::uint8_t* a_output, std::uint32_t a_outputSize, std::uint32_t a_flags = 0);
	NTSTATUS BCryptGetProperty(BCRYPT_HANDLE a_object, const wchar_t* a_property, std::uint8_t* a_output, std::uint32_t a_outputSize, std::uint32_t* a_result, std::uint32_t a_flags = 0);
	NTSTATUS BCryptHashData(BCRYPT_HASH_HANDLE a_hash, std::uint8_t* a_input, std::uint32_t a_inputSize, std::uint32_t a_flags = 0);
}
