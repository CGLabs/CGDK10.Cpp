//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                 tutorials common.ex02 - encoding decoding                 *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                (c) 2003. Cho Sanghyun. All right reserved.                *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************
// 1) standard header file
#if defined(_WIN32)
	#include <conio.h>
#endif

// 2) CGDK header file
#include "cgdk/sdk10/system.object.h"
#include "cgdk/sdk10/system.util.crypt.h"

// 3) header files
#include <iostream>

// 4) namespace
using namespace CGDK;


//-----------------------------------------------------------------------------
//
// tutorial common.ex02 - encoding / decoding
//
//-----------------------------------------------------------------------------
int main()
{
	// ---------------------------------------------------------------------
	// 1. 압축/복원(Compress/Decompress)
	// ---------------------------------------------------------------------
	// 1) zip
	//    - lzw 알고리즘을 사용한 가장 대표적인 비손실 압축알고리즘이다.
	//    - zlib를 사용해 압축과 복원을 한다.
	//    
	{
		// declare) 
		std::string_view data = "Temp test data."sv;

		// trace) 
		std::cout << "original size is "sv << data.size() << '\n';

		// - 압축한다.
		auto buf_compressed = compress::zip(to_buffer_view(data));

		// trace) 
		std::cout << "compressed size is "sv << buf_compressed.size() << '\n';

		// - 압축해제한다.
		auto buf_uncompressed = compress::unzip(buf_compressed);

		// trace) 
		std::cout << "uncompressed size is "sv << buf_uncompressed.size() << '\n';
	}


	// ---------------------------------------------------------------------
	//
	// 2. 암호화/복호화 (Ecryption/Decryption)
	//    - 원본 데이터를 암호화해 원 내용을 알 수 없도록 데이터를 변조하는 것을
	//      말한다.
	//    - 또 변조된 암호화 데이터는 복호화를 거쳐 원문으로 재변조한다.
	//    - 대표적인 방법으로는 ras, AES(DES), pn-code 등이 있으며
	//
	// ---------------------------------------------------------------------

	// 1) rsa
	//    - 일반적으로 공개키 알고리즘 암호화방법으로 유명하다.
	//      암호를 하는 키와 복호화를 하는 키가 서로 달라 복호화 키가 공개되더라도
	//      원암호문을 변조하지 못하는 특성이 있어 다양한 보안 프로토콜에 사용된다.
	//
	//    - 하지만 비교적 AES와 같은 대칭기에 비해 많게는 부하가 1000배 가량 암복호화 처리 비용이
	//      암복호화 처리 비용이 많이 들어 대량의 데이터나 실시간 데이터의 처리에는
	//      잘 사용하지 않으며 인증키나 패스워드와 같은 데이터의 전달이나 저장용으로
	//      많이 사용된다.
	//      또 각종 인증 및 인증서에 사용되는 핵심 알고리즘 중에 하나이다.
	//
	//    - 사용되는 키는 다음과 같이 openssl을 사용해 생성했다.
	//		openssl genrsa -out decryption_key.pem 1024
	//		openssl rsa -in decryption_key.pem -out encryption_key.pem -pubout
	//
	{
		// - 암호화 키 (RSA public key)
		const char* pem_encryption_key =
			"-----BEGIN PUBLIC KEY-----\n"
			"MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDTPh5DvH6YmeLEU1xKg0tk5Zv1\n"
			"M/3yBK2mwUX6cTdBS1A5OeMBZTT8ZZq+pPDSX5WhBPgGVDojJ9DI1W0QT7ELPvi7\n"
			"GVxzT+Fev4hlzIWPRo8YTVBDZ+s06eNrCo8Tj5rG/EZxowA+UZ1Iyc1inAt79wCD\n"
			"7HbVVFHz6PEo3CyC+wIDAQAB\n"
			"-----END PUBLIC KEY-----\n";

		// - 복호화 키 (RSA private key)
		const char* pem_decryption_key =
			"-----BEGIN RSA PRIVATE KEY-----\n"
			"MIICXQIBAAKBgQDTPh5DvH6YmeLEU1xKg0tk5Zv1M/3yBK2mwUX6cTdBS1A5OeMB\n"
			"ZTT8ZZq+pPDSX5WhBPgGVDojJ9DI1W0QT7ELPvi7GVxzT+Fev4hlzIWPRo8YTVBD\n"
			"Z+s06eNrCo8Tj5rG/EZxowA+UZ1Iyc1inAt79wCD7HbVVFHz6PEo3CyC+wIDAQAB\n"
			"AoGBAJE8nUxPFe9PpmT7N3IXsUeOwlqlQ40ZgFctfTKCks32vRKLZTM5ZWO/a9R1\n"
			"zQmnJFZP90NKt6oiHt9mNhVH5V2pGTzOGu0Miz1vPGOBywLkgv4QZUojRNCOeLhj\n"
			"XMFPw8NN6JxI10aqw3BOzTYNFZ5iYkn0PS8oYPLhcfWADkghAkEA8KJhWpBN+JRw\n"
			"IFkQ7YxDwca7cfKv3vHwEo2zGHecq2Hyd6/hZ2Q3WgxAz6HPNZeezESVrV0fqPze\n"
			"qhd16RYz8QJBAOC7RrXlaoETEoxs/9SFz2YjO+zRIMoeC721wLHSiIpwEgV42qPd\n"
			"zGE8KsZRheBvWxt+Hs71mhJBuBuAWl7B4asCQQDWDBr9LA+vZpq2q4NbSsGaxORH\n"
			"39CBSER8vH7q7Lr32BCOVmzyQzrZZrzf9NcUnOIsYXWi2IspDoYiVuwTgiSBAkAC\n"
			"8E//Zu2anH48mdxKkilhI4rQEPgFzJjItUy8xo0Eimyh56+sPuVCTEAe8cf3ZF1j\n"
			"oaWTfUCzhmp66ZXE8XIbAkBcMStOjqtSf4C3VHHmUBUTGi7UnpagIv53QRENIOY5\n"
			"2vcXE73fa++0yiWFSmOWJNuBm5ZbDOirJbmiWG5uXxDZ\n"
			"-----END RSA PRIVATE KEY-----\n";

		// - 원문
		std::string_view original_data = "temp test data."sv;

		// - 암호화를 한다.
		auto buf_encrypted = crypt::encrypt_rsa(crypt::rsa_public_key{ pem_encryption_key }, to_buffer_view(original_data));

		// trace) 
		std::cout << "RSA encrypted code : "sv << buf_encrypted.to_string<char>() << '\n';

		// - 복호화를 한다.
		auto buf_decrypted = crypt::decrypt_rsa(crypt::rsa_private_key{ pem_decryption_key }, buf_encrypted);

		// trace) 
		std::cout << "RSA decrypted code : "sv << buf_decrypted.to_string<char>() << '\n';
	}

	// 2) AES (Advanced Encryption Standard)
	//    - AES('발전된 암호화 표준')은 취약점이 발견된 DES를 대체하기 위해 발표된 
	//      대칭키 암호 알고리즘으로 강력한 보안력과 비교적 빠른 성능을 가지고 있다.
	//      또 블록 암호화 알고리즘으로 여러번 AES를 중복으로 적용해 더 강력한
	//      암호화가 가능하다.
	//    - AES 암호화 알고리즘은 하드웨어 암복호화를 지원해 주기도 한다.
	//    - 이런 특성으로 다양한 분야에 많이 사용하는 알고리즘이긴 하지만
	//      여전히 부하를 무시할 수 없으므로 신중한 사용이 필요하다.
	{
		// - 테스트용 256 bit key 와 128 bit IV 값
		crypt::aes_key key 
		{
			to_buffer_view( "01234567890123456789012345678901"sv),
			to_buffer_view( "0123456789012345"sv)
		};

		// - 원문 & 추가 데이터
		buffer_view plain_text = to_buffer_view("this is CGCII cryption test code and tutorials"sv);

		// - 암호화된 데이터를 저장할 버퍼
		auto cipher_text = alloc_shared_buffer(256) ^ 256;

		// * 암호화한다.
		auto result_crypt = crypt::aes_encrypt(cipher_text, key, plain_text);

		// trace) 
		std::cout << "AES encrypted text : "sv << result_crypt.to_string<char>() << '\n';


		// - 복호화한 데이트를 저장할 버퍼를 할당받는다.
		auto buf_decrypted = alloc_shared_buffer(256) ^ 256;

		// * 복호화한다.
		auto result_decrypt = crypt::aes_decrypt(buf_decrypted, key, result_crypt);

		// trace) 
		std::cout << "AES decrypted text : "sv << result_decrypt.to_string<char>() << '\n';
	}

	// 3) PN-code (Pseudo Noise code)
	//    - 랜덤 알고리즘을 사용해 암호화하는 기법으로 같은 시드값을 주면 
	//      똑같은 순서대로 랜덤 값을 산출하는 랜덤 알고리즘을 사용해 
	//      시드 값을 키로 랜덤값을 순차적으로 발생시켜 원본 데이터에 합성시켜
	//      전송을 함으로써 암호화하는 방법이다.
	//    - 암호키에 해당하는 시드값에 대한 보안만 유지되면 비용이 매우 저렴하면서 
	//      매우 강력한 암호화를 제공하지만
	//    - 순차적 데이터에만 사용할 수 있다는 단점이 있다.
	//      즉 데이터가 유실되거나 블럭단위로 전송되는 데이터의 경우 사용할 수 없다.
	{
		// - encode를 위한 pn_code 객체를 생성한다.
		crypt::pn_code pn_code_encode;

		// - encoder를 초기화를 하고 초기화할 때의 seed_info를 받아낸다.
		auto buf_seed_info = pn_code_encode.initialize_seed();

		// - decode를 위한 pn_code 객체를 생성한다.
		crypt::pn_code pn_code_decode;

		// - encode의 초기화시 얻은 seed 정보를 넣어 decoder를 초기화한다.
		pn_code_decode.initialize_seed(buf_seed_info);


		// - 원문 & 추가 데이터
		buffer_view plain_text = to_buffer_view(std::string_view("this is CGCII cryption test code and tutorials"));

		// - encoder에서 암호화를 합니다.
		auto result_crypt = pn_code_encode.encode(plain_text);

		// trace) 
		std::cout << "pn_code encrypted text : "sv << result_crypt.to_string<char>() << '\n';

		// * decoder에서 복호화한다.
		auto result_decrypt = pn_code_decode.encode(result_crypt);

		// trace) 
		std::cout << "pn_code decrypted text : "sv << result_decrypt.to_string<char>() << '\n';
	}


	// ---------------------------------------------------------------------
	//
	// 3. 에러 검출 코드 및 해시 코드 (EDC and Hashing code)
	//    - 원본 데이터의 변조 여부를 확인할 수 있는 코드를 생성해 채널 상에서
	//      송수신 중 변조가 있는지를 확인하는 코드이다.
	//    - 에러검출 및 해시코드는 원본 데이터를 변조하지는 않는다.
	//    - 대표적으로 CRC, MD5, SHA 코드가 있다.
	// ---------------------------------------------------------------------
	// 1) CRC (Cyclic Redundancy check)
	//    - 데이터의 변조 여부를 확인하는 용도로 많이 사용된다.
	//      비교적 추가 데이터량이 적고 빠르기 때문에 실시간 데이터 처리에 많이 사용된다.
	{
		// - 임시 버퍼를 할당받는다.
		shared_buffer buf_temp = alloc_shared_buffer(100);

		// - 버퍼에 문자열을 넣는다.
		buf_temp.append_text("test string"sv);

		// - 이 버퍼의 crc값을 얻는다.
		auto crc_value = edc::default_crc.get_crc(buf_temp);

		// trace) 
		std::cout << "crc value is "sv << crc_value << '\n';

		// - 이 얻은 crc값을 데이터의 끝에 붙인다.
		buf_temp.append<uint32_t>(crc_value);

		// - 얻은 crc를 끝에 붙힌후 다시 crc값을 얻르면 0이 된다.
		crc_value = edc::default_crc.get_crc(buf_temp);

		// trace) 
		std::cout << "crc value is "sv << crc_value << '\n';

		// check)
		CGASSERT_ERROR(crc_value == 0);
	}

	// 2) MD5 (Message Diegest-5)
	//    - 대규모 원본 데이터 대한 지문(Finger print)값을 만들어 내는 알고리즘으로
	//      크기는 128bit(16byte) 크기의 지문 코드를 만들어 낸다.
	//      원본 데이터의 작은 변화만으로도 MD5는 큰 변화가 일어나 큰 데이트의 동일여부를
	//      판단하는 용도로 많이 사용된다.
	//      MD5는 알고리즘의 결함으로 인해 보안이 필요한 인증 용도로는 많이 사용되지
	//      않으며 파일을 전송하거나 패치서버에서 많이 사용된다.
	//      (인증 용도로는 SHA 알고리즘을 사용하길 권장한다.)
	{
	}

	// 3) SHA-256 (Secure Hash Algorithm-256)
	//    - 기능이나 역할을 MD5와 같으나 보안성이 뛰어난 해시 알고리즘으로 TLS, SSL 등 
	//      많은 보안 프로토콜에 많이 사용된다.
	//    - SHA1가 발표된 이후 이에 대한 취약점이 발견되어 SHA2(SHA-224, SHA-256, SHA-386, SHA-512)를
	//      발표되었다.
	{
		// - 임시 버퍼를 할당받는다.
		shared_buffer buf_temp = alloc_shared_buffer(100);

		// - 버퍼에 문자열을 넣는다.
		buf_temp.append_text("test string"sv);

		auto value_sha256 = crypt::sha256(buf_temp);

		// trace) 
		std::cout << "sha256 value is " << value_sha256.to_string<char>() << '\n';
	}

	// 4) HMAC (Hash based Message Authentication Code)
	//    - 해시 기반 메시지 인증 코드은 해시 알고리즘(MD5, SHA..)를 기반으로 인증을 하기 위한 코드이다.
	//      데이터 처리가 비싸고 복잡한 면이 있어 제한적으로 사용할 필요가 있다.
	//    - 해시 기반 알고리즘은 원래의 데이터를 직접 전달하지 않고 그것의 해시코드만 전달해서 인증이 가능하므로
	//      암호문이 전송중 채널에서 유출될 가능성이 전혀 없는 특성이 있어 인증만을 목적으로 할 경우 많이 사용된다.
	{
		// - 원문 데이터와 키
		buffer_view	buf_source = to_buffer_view("test string"sv);
		buffer_view buf_key	= to_buffer_view("xxfdafdsafs"sv);

		// - HMAC로 해쉬 값을 구한다.
		auto value_sha256 = crypt::hmac_sha256(buf_source, buf_key);

		// - sha256값을 출력한다.
		std::cout << "HMAC-SHA256 value is "sv << value_sha256.to_string<char>() << '\n';
	}

	// 5) bcrypt
	//    - 인증처리에 사용되는 암호의 저장 및 인증 처리에 많이 사용되는 해싱 기반 알고리즘이다.
	{
		// - 암호문
		std::string password = "top_secret"s;

		// - 암호를 해싱한다.
		std::string hashed_password = crypt::bcrypt::generate_hash(password);

		// trace) 
		std::cout << "hash: "sv << hashed_password << std::endl;

		// - 맞는 암호와 비교했을 때
		std::cout << "\"" << password << "\" : "sv << crypt::bcrypt::check_password(password, hashed_password) << std::endl;

		// - 틀린 암호와 비교했을 때
		std::cout << "\"wrong\" : "sv << crypt::bcrypt::check_password("wrong"sv, hashed_password) << std::endl;
	}


	// ---------------------------------------------------------------------
	// 4. 코드 변환 (code encoding)
	// ---------------------------------------------------------------------
	// 1) base64
	//    - base64코드는 이진 데이터를 ASCII 문자 영역의 문자만으로 인코딩하는 것이다.
	//      바이너리 데이터를 문자열로 전송할 때 많이 사용된다.
	{
		// - 임시 버퍼를 할당받는다.
		shared_buffer buf_temp = alloc_shared_buffer(100);

		// - 버퍼에 문자열을 넣는다.
		buf_temp.append_text("test string"sv);

		// - base64로 encoding한다.
		auto str_encoded = crypt::encode_base64(buf_temp);

		// trace)
		std::cout << "base64 encoeded is '"sv << str_encoded << "'\n";

		// - 다시 decode한다.
		auto buf_decoded = crypt::decode_base64(str_encoded);

		// trace)
		std::cout << "base64 encoeded is '"sv << buf_decoded.to_string<char>() << "'\n";
	}


	// return) 
	return	0;
}