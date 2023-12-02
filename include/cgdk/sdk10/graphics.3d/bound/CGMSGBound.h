//*****************************************************************************
//*                                                                           *
//*                      Cho SangHyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                           CG 3D Object Classes                            *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// 1. CG3DBounding::CAABB
//
//-----------------------------------------------------------------------------
#define	CGMESSAGE_COLLISION					(CGMESSAGE_GRAPHICS+4)
#define	CGMESSAGE_CULLING_VIEW				(CGMESSAGE_GRAPHICS+5)
#define	CGMESSAGE_CULLING_OCCULUSION		(CGMESSAGE_GRAPHICS+6)
#define	CGMESSAGE_PICKING					(CGMESSAGE_GRAPHICS+7)

struct CGMSG_IBOUNDING : public CGMSG
{
public:
	CGMSG_IBOUNDING() : CGMSG()	{}
	CGMSG_IBOUNDING(DWORD p_dwMsg) : CGMSG(p_dwMsg)	{}

public:
	virtual	BOUNDINGSTATUS	CheckBounding(ICG3DBounding* p_pBounding) PURE;
};

struct CGMSG_BOUNDING : public CGMSG_IBOUNDING
{
public:
	// Definitions)
	struct OBJECT
	{
	public:
		CGPTR<ICG3DBounding>	pBound;
		INTERSECT_INFO			posBound[2];
	};

public:
	CGMSG_BOUNDING() : CGMSG_IBOUNDING()	{}
	CGMSG_BOUNDING(DWORD p_dwMsg) : CGMSG_IBOUNDING(p_dwMsg)	{}

public:
	virtual	bool			QueueBounding(OBJECT& p_rObject) PURE;

public:
	// 1) Segment...
			CGPTR<ICG3DBounding>	pboundingSource;
};


struct CGMSG_BOUNDING_LIST : public CGMSG_BOUNDING
{
public:
	CGMSG_BOUNDING_LIST() : CGMSG_BOUNDING()	{}
	CGMSG_BOUNDING_LIST(DWORD p_dwMsg) : CGMSG_BOUNDING(p_dwMsg)	{}

public:
	virtual	BOUNDINGSTATUS	CheckBounding(ICG3DBounding* p_pBounding);
	virtual	bool			QueueBounding(OBJECT& p_rObject);

public:
			bool			exist() const			{	return !listSelected.empty();}
			bool			empty() const			{	return listSelected.empty();}

public:
			list<OBJECT>	listSelected;
};


struct CGMSG_BOUNDING_SEGMENT : public CGMSG_IBOUNDING
{
public:
	// Definitions)
	struct OBJECT
	{
	public:
		CGPTR<ICG3DBounding>	pBound;
		INTERSECT_INFO			posBound[2];
	};

public:
	CGMSG_BOUNDING_SEGMENT() : CGMSG_IBOUNDING()	{}
	CGMSG_BOUNDING_SEGMENT(DWORD p_dwMsg) : CGMSG_IBOUNDING(p_dwMsg)	{}

public:
	virtual	bool			QueueBounding(OBJECT& p_rObject) PURE;

public:
	// 1) Segment...
			CG3D::SEGMENT	segmentSource;
};

struct CGMSG_BOUNDING_SEGMENT_LIST : public CGMSG_BOUNDING_SEGMENT
{
public:
			bool			exist() const			{	return !listSelected.empty();}
			bool			empty() const			{	return listSelected.empty();}

public:
	virtual	BOUNDINGSTATUS	CheckBounding(ICG3DBounding* p_pBounding);
	virtual	bool			QueueBounding(OBJECT& p_rObject);

public:
			list<OBJECT>	listSelected;
public:
	CGMSG_BOUNDING_SEGMENT_LIST() : CGMSG_BOUNDING_SEGMENT(CGMESSAGE_PICKING)	{}
	CGMSG_BOUNDING_SEGMENT_LIST(DWORD p_dwMsg) : CGMSG_BOUNDING_SEGMENT(p_dwMsg)	{}
};

struct CGMSG_BOUNDING_SEGMENT_SINGLE : public CGMSG_BOUNDING_SEGMENT
{
public:
			bool			exist() const			{	return !Selected.pBound.empty();}
			bool			empty() const			{	return Selected.pBound.empty();}

public:
	virtual	bool			QueueBounding(OBJECT& p_rObject);

public:
			OBJECT			Selected;
public:
	CGMSG_BOUNDING_SEGMENT_SINGLE() : CGMSG_BOUNDING_SEGMENT(CGMESSAGE_PICKING)	{	Selected.posBound[0].fT=FLT_MAX; Selected.posBound[1].fT=-FLT_MAX;}
	CGMSG_BOUNDING_SEGMENT_SINGLE(DWORD p_dwMsg) : CGMSG_BOUNDING_SEGMENT(p_dwMsg)	{	Selected.posBound[0].fT=FLT_MAX; Selected.posBound[1].fT=-FLT_MAX;}
};

struct CGMSG_BOUNDING_SEGMENT_SINGLE_NEAREST : public CGMSG_BOUNDING_SEGMENT_SINGLE
{
public:
	virtual	BOUNDINGSTATUS	CheckBounding(ICG3DBounding* p_pBounding);

public:
	CGMSG_BOUNDING_SEGMENT_SINGLE_NEAREST() : CGMSG_BOUNDING_SEGMENT_SINGLE(CGMESSAGE_PICKING)	{}
	CGMSG_BOUNDING_SEGMENT_SINGLE_NEAREST(DWORD p_dwMsg) : CGMSG_BOUNDING_SEGMENT_SINGLE(p_dwMsg)	{}
};
	
struct CGMSG_BOUNDING_SEGMENT_SINGLE_PICKING : public CGMSG_BOUNDING_SEGMENT_SINGLE
{
public:
	virtual	BOUNDINGSTATUS	CheckBounding(ICG3DBounding* p_pBounding);

public:
	CGMSG_BOUNDING_SEGMENT_SINGLE_PICKING() : CGMSG_BOUNDING_SEGMENT_SINGLE(CGMESSAGE_PICKING)	{}
	CGMSG_BOUNDING_SEGMENT_SINGLE_PICKING(DWORD p_dwMsg) : CGMSG_BOUNDING_SEGMENT_SINGLE(p_dwMsg)	{}
};
