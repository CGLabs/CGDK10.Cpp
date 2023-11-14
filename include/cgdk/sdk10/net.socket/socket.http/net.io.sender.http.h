//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                        network socket http classes                        *
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
// net::io::sender::Nstream
//
// 1. net::io::sender::CStream��~
//    1) ���� �Ϲ����� sender�� net::io::Isend_request�� request_send()�Լ��� ȣ����
//       �ش�.
//    2) �ѹ��� ���ۿ� �ѹ��� Overlapped I/O�� �ɾ� send()�� �����ϴ� sender��
//       ���� �Ϲ����̰� �⺻���� sender�̴�. 
//       ������ ���� message�� �뷮���� �Ѳ����� ������ �Ǹ� ������ ���� ��������.
//       ���� message�� �뷮���� �Ѳ����� ȿ�������� �����ϰ� �ʹٸ� Nstream_gather
//       Ŭ������ ����ϱ� �����Ѵ�.
//
// 2. �ٽ��Լ�!
//    1) BOOL send(const buffer& _buffer);
//       �� �״�� ������ �����ϴ� �Լ��̴�. buffer�� ������ message�� �ְ� send()
//       �Լ��� ȣ���ϸ� �� ���۸� �ѱ�� ������ �ȴ�.
//
//-----------------------------------------------------------------------------
class net::io::sender::Nhttp : 
// inherited classes)
	virtual protected			net::io::Isendable,
	virtual protected			net::io::Isender,
	virtual protected			net::io::Isocket,
	virtual public				net::io::statistics::Nsocket
{
public:
	// 1) process send
	virtual	bool				process_send( shared_buffer&& _buffer, std::size_t _count_message, uint64_t _option) override;
};


}