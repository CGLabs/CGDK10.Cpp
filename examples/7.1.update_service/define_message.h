// ----------------------------------------------------------------------------
//
// message definitions
//
// ----------------------------------------------------------------------------
#pragma once


struct sREQUEST_UPDATE
{
	CGDK::update::sUPDATE_VERSION version_now;
	CGDK::update::sUPDATE_VERSION version_request;
};