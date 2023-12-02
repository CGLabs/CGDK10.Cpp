﻿//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                    for C# Ver 2.0 / Release 2019.12.11                    *
//*                                                                           *
//*                          Group Template Classes                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho sanghyun. sangducks@cgcii.co.kr        *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                (c) 2008 Cho sanghyun. All right reserved.                 *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************
using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace CGDK.server.group
{
	public class Narray<TMEMBER> : 
		Igroup<TMEMBER> 
		where TMEMBER : class
	{
	// constructor/destructor) 
		public Narray(int _max_member = 256)
		{
			m_enable_enter		 = false;
			m_count_member		 = 0;
			m_container_member	 = new Igroupable<TMEMBER>[_max_member];
			m_seat				 = new seat(_max_member);
			m_cs_group			 = new object();
		}
		~Narray()
		{
			leave_all_member();
		}

	// public) 
		//! @brief '멤버 객체'를 입장시킨다. @param _member 입장할 '멤버 객체' @param _buffer 입장할 때 전달할 메시지 @return eRESULT.SUCCESS 성공 @return !eRESULT.SUCCESS 실패
		public eRESULT				enter_member(Igroupable<TMEMBER> _member, sMESSAGE? _msg = null)
		{
			return process_enter_member(_member, _msg);
		}
		//! @brief 모든 '멤버 객체'를 퇴장시킨다.
		public void					leave_all_member(sMESSAGE? _msg = null)
		{
			lock (m_cs_group)
			{
				foreach(Igroupable<TMEMBER> member in m_container_member)
				{
					leave_member(member, _msg);
				}
			}
		}

		//! @brief '멤버 객체'의 갯수를 얻는다. @return 멤버 객체 갯수
		public int					member_count
		{
			get
			{
				lock (m_cs_group)
				{
					return m_count_member;
				}
			}
		}
		//! @brief 남아 있는 '멤버 객체'의 갯수를 얻는다. @return 남은 멤버 객체 갯수
		public int					member_room_count
		{
			get
			{
				lock (m_cs_group)
				{
					return m_container_member.Length-m_count_member;
				}
			}
		}
		//! @brief 최대 '멤버 객체'의 갯수를 얻는다. @return 최대 멤버 객체 갯수
		public int					max_member_count
		{
			set
			{
				lock (m_cs_group)
				{
					_set_max_member_count(value);
				}
			}
			get
			{
				lock (m_cs_group)
				{
					return m_container_member.Length;
				}
			}
		}

		//! @brief 멤버 객체가 꽉 찼는지를 확인한다. @return true 꽉찼다. false 꽉차지 않았다.
		public	bool				is_member_full
		{
			get { return m_count_member >= m_container_member.Length; }
		}							// 꽉차있는가?
		//! @brief 멤버 객체가 하나도 없는지 확인한다. @return true 완전히 비어있다. false 비어있지 않다.
		public	bool				is_member_empty
		{
			get { return m_count_member == 0;}
		}						// 완전히 비어 있는가?
		//! @brief 멤버 객체가 들어갈 여유가 있는가를 확인한다. @return true 최대 인원만큼 꽉찼다. false 들어갈 여유가 있다.
		public	bool				is_member_room
		{
			get { return m_count_member<m_container_member.Length;}
		}							// 더 들어 올 수 있는가?
		//! @brief 멤버 객체가 하나라도 있는가를 확인한다. @return true 비어있지 않다. false 완전히 비어 있다.
		public	bool				is_member_exist
		{
			get { return m_count_member != 0;}
		}                       // 들어 있는 사람이 있는가?

		//! @brief [Member]의 목록
		public override IEnumerable<Igroupable<TMEMBER>> members
		{
			get { return m_container_member as IEnumerable<Igroupable<TMEMBER>>; }
		}
		public override object		group_lock
		{
			get { return m_cs_group; }
		}

	// framework) 
		//! @brief 입장을 허용했을 때 호출되는 함수
		protected virtual void		on_enable_enter() {}
		//! @brief 입장이 금지했을 때 호출되는 함수
		protected virtual void		on_disable_enter() {}
		//! @brief 새로운 멤버가 입장하기 직전 호출되는 함수 @param _member 입장할 '멤버 객체' @param _buffer 입장시 전달할 메시지 @return eRESULT.SUCCESS 입장 성공 @return !eRESULT.SUCCESS 입장 실패
		protected virtual eRESULT	on_member_entering(TMEMBER _member, sMESSAGE? _msg) { return eRESULT.SUCCESS;}
		//! @brief 새로운 멤버가 입장된 후 호출되는 함수 @param _member 입장한 '멤버 객체' @param _buffer 입장시 전달할 메시지
		protected virtual void		on_member_entered(TMEMBER _member, sMESSAGE? _msg) {}
		//! @brief 멤버가 퇴장되기 직전에 호출되는 함수 @param _member 퇴장할 '멤버 객체' @return 전달할 값
		protected virtual ulong		on_member_leaving(TMEMBER _member, sMESSAGE? _msg) { return 0;}
		//! @brief 멤버가 퇴장된 후 호출되는 함수 @param _member 퇴장한 '멤버 객체' @param _result on_member_leaving()의 리턴 함수
		protected virtual void		on_member_leaved(TMEMBER _member, sMESSAGE? _msg, ulong _result) {}

	// implementation)  
		protected override bool		process_enable_enter(bool _enable)
		{
			lock(m_container_member)
			{
				// check) 
				if(m_enable_enter == _enable)
					return false;

				// 1) 값을 설정
				m_enable_enter = _enable;

				// 2) OnOpen을 호출한다.
				if(_enable)
					on_enable_enter();
				else
					on_disable_enter();
			}

			// return) 
			return true;
		}
		protected override bool		process_is_enable_enter()
		{
			lock (m_container_member)
			{
				return m_enable_enter;
			}
		}
		protected eRESULT			process_enter_member(Igroupable<TMEMBER> _member, sMESSAGE? _msg)
		{
			// check) p_Member가 nullptr인가?
			if(_member == null)
				return eRESULT.INVALID_ARGUMENT;

			// check)
			if (_member.member == null)
				throw new System.Exception();

			lock (_member.m_cs_group)
			lock(m_container_member)
			{
				// 1) Member의 Group이 똑같지 않은가?
				if(_member.is_member_of(this) == true)
					return eRESULT.INVALID_MEMBER;

				// check) Enter가능한 상태인가?
				if(m_enable_enter == false)
					return eRESULT.FAIL_DISABLED;

				// 2) 방이 꽉 찼는가?
				if(is_member_full)
					return eRESULT.MEMBER_FULL;

				// 1) on_member_entering()함수를 호출한다.
				var	result = on_member_entering(_member.member, _msg);

				// check)
				if(result != eRESULT.SUCCESS)
					return result;
		
				// 2) 이전 Group에서 떼낸다.
				_member.leave_group();

				lock(m_cs_group)
				{
					// 3) attach한다.
					_attach_member(_member);

					// 4) on_member_entered()함수를 호출한다. 
					try
					{
						_process_member_entered(_member, _msg);
					}
					// Exception) Rollback한다.
					catch(System.Exception /*e*/)
					{
						// - Member를 떼낸다.
						_detach_member(_member);

						// reraise) 
						throw;
					}
				}
			}

			return	eRESULT.SUCCESS;
		}
		protected override void		process_leave_member(Igroupable<TMEMBER> _member, sMESSAGE? _msg)
		{
			// check) _member가 null인가?
			Debug.Assert(_member != null);

			// check)
			if (_member == null)
				return;

			// check)
			if (_member.member == null)
				throw new System.Exception();

			lock (_member.m_cs_group)
			{
				// declare) 
				ulong result = 0;

				lock(m_cs_group)
				{
					// check) _member의 Group이 똑같지 않은가?
					if(_member.is_member_of(this) == false)
						return;

					// 1) List에서 떨어지기 전에 처리해야할 사항들을 처리한다.
					try
					{
						result = _process_member_leaving(_member, _msg);
					}
					// Exception) 
					catch(System.Exception)
					{
					}

					// 2) detach한다.
					_detach_member(_member);
				}

				try
				{
					// 1) Member가 detach되고 난 다음에 해야할 것을 처리한다.
					on_member_leaved(_member.member, _msg, result);
				}
				// Exception) 
				catch(System.Exception)
				{
				}
			}
		}

		private	void				_attach_member(Igroupable<TMEMBER> _member)
		{
			// 1) 숫자를 하나 늘린다.(이걸 제일 먼저 한다.)
			++m_count_member;

			// 2) Seat를 얻는다.
			var seat_index = m_seat.alloc_seat();

			// check) Seat가 -1이면 Seat가 남아 있지 않은 것이므로 그냥 되돌린다.
			Debug.Assert(seat_index >= 0);

			// 3) 값을 읽어온다.
			m_container_member[seat_index] = _member;

			// 4) Seat Info를 Push한다.
			_member._set_member_serial(seat_index);

			// 5) Object을 설정!
			_member._set_group(this);
		}
		private void				_detach_member(Igroupable<TMEMBER> _member)
		{
			// 1) Seat Serial을 잠시 저장해 놓는다.
			var seat_index = _member.member_serial;

			// 2) 값을 읽어온다.
			Igroupable<TMEMBER>	rSeat = m_container_member[seat_index];

			// check) _member와 Seat에 있는 Object가 같은 것이어야 한다.
			Debug.Assert(rSeat == _member);

			// 3) Seat Info를 Pop한다.
			_member._reset_member_serial();

			// 4) _member의 Group을 해제함.(이걸 제일 먼저 한다.)
			_member._reset_group();

			// 5) Seat번호를 돌려준다.
			m_seat.free_seat(seat_index);

			// 6) Socket 숫자를 하나 줄인다.(이걸 제일 마지막에 한다.)
			--m_count_member;
		}
		private void				_process_member_entered(Igroupable<TMEMBER> _member, sMESSAGE? _msg)
		{
			// 1) on_member_entering함수를 호출한다.
			on_member_entered(_member.member, _msg);
		}
		private ulong				_process_member_leaving(Igroupable<TMEMBER> _member, sMESSAGE? _msg)
		{
			// 1) on_member_leaving함수를 호출한다.
			return	on_member_leaving(_member.member, _msg);
		}
		private void				_set_max_member_count(int _max_count)
		{
			var	array_new = new Igroupable<TMEMBER>[_max_count];

			if(m_container_member != null)
			{
				int	i = 0;
				int	count = Math.Min(_max_count, m_container_member.Length);

				for(; i < count; ++i)
				{
					array_new[i] = m_container_member[i];
					m_container_member[i] = null;
				}

				for(; i<m_container_member.Length; ++i)
				{
					m_container_member[i] = null;
				}
			}

			m_container_member = array_new;
			m_seat = new seat(_max_count);
		}
		protected Igroupable<TMEMBER> _get_member(int _index) { return m_container_member[_index];}

	// implementation)  
		protected seat				m_seat;
		protected bool				m_enable_enter;
		protected object			m_cs_group;

		protected Igroupable<TMEMBER>[] m_container_member;
		protected int				m_count_member;
	}
}