//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                         Server Security Controls                          *
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

#pragma once

namespace CGDK
{
//-----------------------------------------------------------------------------
//
// net::io::receivable::Nstream_crypt
//
// 1. net::io::receivable::Nstream_crypt란!
//    1) TCP의 send/receive/connect 등을 수행할 수 있는 socket임. 
//    2) 기본적으로 재사용을 위한 Recycle처리가 들어 있음.
//    3) 소량의 연결처리를 전제로 하였으므로 socket manager와 socket Pool 등은
//       지원하지 않는다.
//    4) 그래도 과거에 비해 반응속도가 크게 증가하였고 각종 Pending현상으로 인한
//       Failure를 거의 없앴다.
//
//
// 2. CGDK.net.socket의 핵심! Function의 기능 설명
//    1) 처리함수들 기본적인 I/O처리를 위한 처리함수들이다.
//					내부적으로 각종 I/O를 처리하기 위해 필요한 함수들에 대해서 정의한 것이다.
//    2) 진행함수들	socket의 각 동작을 정의하는 함수들이다.
//    3) User함수들	재정의를 위해 만들어진 함수이다. 프로그래머가 이 부분들을 재정의
//					함을써 socket을 게임에 맞게 만들게 된다.
//
// 3. 주의 사항
//  run을 항상 일정 시간마다 실행을 시켜 I/O에 대한 처리를 반듯이 해주어야 한다.
//
//-----------------------------------------------------------------------------
class net::io::receivable::Nstream_crypt :
// inherited classes)
	public						net::io::receivable::Nstream,
	virtual public				net::io::Isender
{
 // public)
public:
	// 1) ReceiveCryptor
	[[nodiscard]] auto			get_decoder() const { return m_pdecoder;}
			void				set_decoder( Idecoder* _pdecoder) { m_pdecoder=_pdecoder;}
			void				reset_decoder() { m_pdecoder.reset();}

	// 2) receive Cryptor를 초기화하는 함수.(receive Cryptor를 초기화하고 초기화 정보를 상대에 보냄)
			void				initialize_encoder();

// frameworks)
protected:
	// 1) Criptor를 생성할때 불려지는 함수.
	[[nodiscard]] virtual object_ptr<Idecoder> create_decoder() { return (Idecoder*)nullptr;}

	// 2) receive Encrypt를 수행하는 함수.
	virtual	void				process_decoding( buffer_view& _buffer);

// implementation) 
protected:
	// 1) reset할때 호출하는 함수.
	virtual	void				process_reset_receivable() override;

	// 2) Completion 되었을 때 수행되는 함수.
	virtual	intptr_t			process_complete_receivable( intptr_t _result, std::size_t _param) override;

protected:
	// 1) receive용 Cryptor
			object_ptr<Idecoder> m_pdecoder; // receive 복호화기
};


}