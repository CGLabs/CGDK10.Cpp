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
// 1. net::io::sendable::CTCP��!
//    1) TCP�� send�� �ѹ��� send�� �ѹ��� Overlapped I/O�� �ɾ �����ϴ� 
//       sendable�̴�.
//    2) �ѹ��� send�� �ѹ��� Overlapped I/O�� ���� ������ ������ �����Ͽ� send
//       �󵵰� ���� socket������ ���� ������ ����.
//    3) ������ send�� �󵵰� ���� socket������ ���� I/O�� ������ ������ ������
//       �� �����Ƿ� �󵵰� ���� send�� �����ϴ� socket������ �� sendable���
//       send Gathering�� �����ϴ� TCPGathering�� ����ϵ��� ���Ѵ�.
//    4) ��κ��� Server socket�̳� Client socket�� ��� �� ������ sendable��
//       ����ϴ�.
//
//
// 2. net::io::sendable::CTCP�� �ٽ�! Function�� ��� ����
//    1) send()		buffer�� �����Ѵ�.
//
//    2) on_sended() send�� �Ϸ�Ǿ��� �� ȣ��Ǵ� �Լ��̴�. send�� �Ϸ�Ǿ���
//                  �� ó���ؾ��� ������ ���� ��� �� �Լ��� �������Ѵ�.
//
//-----------------------------------------------------------------------------
class net::io::sendable::Ntcp_crypt :
	public						net::io::sendable::tcp::Ndefault
{
protected:
	virtual	~Ntcp_crypt() noexcept {}

public:
	[[nodiscard]] auto			get_encoder() const noexcept { return this->m_pencoder;}
			void				set_encoder( Iencoder* _pcrypt) { this->m_pencoder = _pcrypt;}
			void				reset_encoder() { this->m_pencoder.reset();}

protected:
	// 1) send�� �� �θ��� �Լ�.
	virtual	bool				process_sendable( const buffer_view _buffer, object_ptr<Ireferenceable>&& _powner, std::size_t _count_message, const net::sockaddr& _paddress) override;
			bool				process_initialize_encoder( const shared_buffer& _buffer);
	virtual	void				process_reset_sendable() noexcept override;

	// 4) encoder�� �����Ҷ� �ҷ����� �Լ�.
	//    - ���Լ����� Encoder�� �����ؼ� Pointer�� return���ش�.
	//    - �⺻�����δ� Encoder�� nullptr�̴�.
	virtual	object_ptr<Iencoder> process_create_encoder( eCRYPTION_TYPE _type);

protected:
			class executable_send_buffer;
			object_ptr<Iencoder> m_pencoder;
};


}