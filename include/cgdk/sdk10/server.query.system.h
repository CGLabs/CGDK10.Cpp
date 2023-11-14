//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                         Server DB System Classes                          *
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
// Prototype
// ----------------------------------------------------------------------------
#define	CGSERVERDB_SYSTEM_TEMPLATES


// ----------------------------------------------------------------------------
// head File
// ----------------------------------------------------------------------------
// 1) BaseClasses
#include "CGServerQueryClasses.h"

// 2) Definitions

// 3) Base & Interfaces
#include "Server/ServerQuery/CGServerQuerySystemClasses/CGServerQuerySystemRequestor.h"

// 4) Requestor Batch
#include "Server/ServerQuery/CGServerQuerySystemClasses/CGServerQuerySystemRequestorBatch.h"
#include "Server/ServerQuery/CGServerQuerySystemClasses/CGServerQuerySystemRequestorBatchWait.h"
#include "Server/ServerQuery/CGServerQuerySystemClasses/CGServerQuerySystemRequestorBatchDispatch.h"
#include "Server/ServerQuery/CGServerQuerySystemClasses/CGServerQuerySystemRequestorBatchLambda.h"

// 5) Requestor Concurrent
#include "Server/ServerQuery/CGServerQuerySystemClasses/CGServerQuerySystemRequestorConcurrent.h"
#include "Server/ServerQuery/CGServerQuerySystemClasses/CGServerQuerySystemRequestorConcurrentWait.h"
#include "Server/ServerQuery/CGServerQuerySystemClasses/CGServerQuerySystemRequestorConcurrentDispatch.h"
#include "Server/ServerQuery/CGServerQuerySystemClasses/CGServerQuerySystemRequestorConcurrentLambda.h"

// 6) Requestor Queue
#include "Server/ServerQuery/CGServerQuerySystemClasses/CGServerQuerySystemRequestorQueue.h"
