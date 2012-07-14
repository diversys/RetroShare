#ifndef RSTOKENSERVICE_H
#define RSTOKENSERVICE_H

/*
 * libretroshare/src/retroshare: rsidentity.h
 *
 * RetroShare C++ Interface.
 *
 * Copyright 2012-2012 by Robert Fernie, Christopher Evi-Parker
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License Version 2 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA.
 *
 * Please report all bugs and problems to "retroshare@lunamutt.com".
 *
 */

#include <inttypes.h>
#include <string>
#include <list>

#include "serialiser/rsgxsitems.h"


#define GXS_REQUEST_STATUS_FAILED		0
#define GXS_REQUEST_STATUS_PENDING		1
#define GXS_REQUEST_STATUS_PARTIAL		2
#define GXS_REQUEST_STATUS_FINISHED_INCOMPLETE	3
#define GXS_REQUEST_STATUS_COMPLETE		4
#define GXS_REQUEST_STATUS_DONE			5 // ONCE ALL DATA RETRIEVED.

#define GXS_REQUEST_TYPE_GROUPS			0x00010000
#define GXS_REQUEST_TYPE_MSGS			0x00020000
#define GXS_REQUEST_TYPE_MSGRELATED		0x00040000

/*!
 * This class provides useful generic support for GXS style services.
 * I expect much of this will be incorporated into the base GXS.
 *
 */
class RsTokReqOptions
{
public:
    RsTokReqOptions() { mOptions = 0; mBefore = 0; mAfter = 0; }

    uint32_t mOptions;
    time_t   mBefore;
    time_t   mAfter;
};


/*!
 * A proxy class for requesting generic service data for GXS
 * This seperates the request mechanism from the actual retrieval of data
 */
class RsTokenService
{

public:

    RsTokenService()  { return; }
    virtual ~RsTokenService() { return; }

        /* Data Requests */
    virtual bool requestGroupInfo(uint32_t &token, uint32_t ansType, const RsTokReqOptions &opts, const std::list<std::string> &groupIds) = 0;
    virtual bool requestMsgInfo(uint32_t &token, uint32_t ansType, const RsTokReqOptions &opts, const std::list<std::string> &groupIds) = 0;
    virtual bool requestMsgRelatedInfo(uint32_t &token, uint32_t ansType, const RsTokReqOptions &opts, const std::list<std::string> &msgIds) = 0;
    virtual bool requestGroupSubscribe(uint32_t &token, const std::string &groupId, bool subscribe) = 0;

        /* Poll */
    virtual uint32_t requestStatus(const uint32_t token) = 0;

        /* Cancel Request */
    virtual bool cancelRequest(const uint32_t &token) = 0;



};

#endif // RSTOKENSERVICE_H