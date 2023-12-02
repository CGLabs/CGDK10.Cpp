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
// 1. net::io::receivable::Nstream_crypt��!
//    1) TCP�� send/receive/connect ���� ������ �� �ִ� socket��. 
//    2) �⺻������ ������ ���� Recycleó���� ��� ����.
//    3) �ҷ��� ����ó���� ������ �Ͽ����Ƿ� socket manager�� socket Pool ����
//       �������� �ʴ´�.
//    4) �׷��� ���ſ� ���� �����ӵ��� ũ�� �����Ͽ��� ���� Pending�������� ����
//       Failure�� ���� ���ݴ�.
//
//
// 2. CGDK.net.socket�� �ٽ�! Function�� ��� ����
//    1) ó���Լ��� �⺻���� I/Oó���� ���� ó���Լ����̴�.
//					���������� ���� I/O�� ó���ϱ� ���� �ʿ��� �Լ��鿡 ���ؼ� ������ ���̴�.
//    2) �����Լ���	socket�� �� ������ �����ϴ� �Լ����̴�.
//    3) User�Լ���	�����Ǹ� ���� ������� �Լ��̴�. ���α׷��Ӱ� �� �κе��� ������
//					������ socket�� ���ӿ� �°� ����� �ȴ�.
//
// 3. ���� ����
//  run�� �׻� ���� �ð����� ������ ���� I/O�� ���� ó���� �ݵ��� ���־�� �Ѵ�.
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

	// 2) receive Cryptor�� �ʱ�ȭ�ϴ� �Լ�.(receive Cryptor�� �ʱ�ȭ�ϰ� �ʱ�ȭ ������ ��뿡 ����)
			void				initialize_encoder();

// frameworks)
protected:
	// 1) Criptor�� �����Ҷ� �ҷ����� �Լ�.
	[[nodiscard]] virtual object_ptr<Idecoder> create_decoder() { return (Idecoder*)nullptr;}

	// 2) receive Encrypt�� �����ϴ� �Լ�.
	virtual	void				process_decoding( buffer_view& _buffer);

// implementation) 
protected:
	// 1) reset�Ҷ� ȣ���ϴ� �Լ�.
	virtual	void				process_reset_receivable() override;

	// 2) Completion �Ǿ��� �� ����Ǵ� �Լ�.
	virtual	intptr_t			process_complete_receivable( intptr_t _result, std::size_t _param) override;

protected:
	// 1) receive�� Cryptor
			object_ptr<Idecoder> m_pdecoder; // receive ��ȣȭ��
};


}