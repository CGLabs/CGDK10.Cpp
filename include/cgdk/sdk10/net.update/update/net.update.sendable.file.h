//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          network update classes                           *
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
// ----------------------------------------------------------------------------
//
// CGDK::update::sendable::folder
//
//
// ----------------------------------------------------------------------------
class CGDK::update::sendable::file :
	virtual public				Isendable
{
//public:
//			bool				Initialize(const _CHAR* _strFileName, const _CHAR* _strPathName=nullptr, CGUPDATEMODE _eMode=CGUPDATEMODE_TRANSFER, uint32_t _BlockSize=32768);
//
//	virtual	CGPTR<ICGNetUpdateSending>	AllocUpdateSending(const _CHAR* _strPath);
//
//			const _STRING&		GetSourceFileName() const				{	return m_strSourceFileName;}
//			const _STRING&		GetDestinationFilePath() const			{	return m_strDestFilePath;}
//			const _STRING&		GetDestinationFileName() const			{	return m_strDestFileName;}
//			void				GetDestinationFullFileName(_STRING& _strPath) const;
//
//	virtual	const _CHAR*		GetName() const							{	return m_strDestFileName.c_str();}
//	virtual	void				SetName(const _CHAR* _strName)			{	m_strDestFileName=_strName;}
//	virtual	uint32_t			GetAttribute(uint32_t _Mask) const		{	return m_FileInfo.dwAttribute & _Mask;}
//	virtual	const edc::md5&		GetMD5() const							{	return m_edcMD5.GetMD5();}
//			CGFILE_INFO&		GetFileInfo()							{	return m_FileInfo;}
//			CCGBuffer			GetFileBlock(int p_indexBlock);
//
//protected:
//			_STRING				m_strSourceFileName;	// File Name(파일 이름)
//			_STRING				m_strDestFilePath;		// 목표 파일 Path
//			_STRING				m_strDestFileName;		// 목표 파일 이름
//
//			bool				m_bUseCompression;		// 파일 압축 여부
//
//			CGFILE_INFO			m_FileInfo;				// File Info(전송될 것.)
//			edc::md5			m_edcMD5;				// MD5 (비교를 위한 것)
//			uint32_t			m_dwMD5Process;			// MD5 Process
//
//			vector<CCGBuffer>	m_vectorBufferBlock;	// File Block
//
//			ATOMIC<int>			m_statisticsSendedByte;
//			ATOMIC<int>			m_statisticsSendedTime;
//
//			bool				ProcessInitializeInstance	(const _CHAR* _strFileName, const _CHAR* _strPathName=nullptr, uint32_t _BlockSize=32768, bool _bCalcuateMD5=false);
//			bool				ProcessInitializeStatic		(const _CHAR* _strFileName, const _CHAR* _strPathName=nullptr, uint32_t _BlockSize=32768);
//			CGHANDLE			ProcessOpenFile				(const _CHAR* _strFileName, const _CHAR* _strPathName=nullptr, uint32_t _BlockSize=32768);
//			CCGBuffer			ProcessReadFileBlock		(CGHANDLE _hFile, int _Offset);
//			void				ProcessCloseFile			(CGHANDLE _hFile);
};
