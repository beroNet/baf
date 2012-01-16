/*
 * suppserv.h
 *
 * Copyright (C) 2006, Nadi Sarrar
 * Nadi Sarrar <nadi@beronet.com>
 *
 * Portions of this file are based on the mISDN sources
 * by Karsten Keil.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */
#include "asn1.h"
#ifndef __SUPPSERV_H__
#define __SUPPSERV_H__

#include <asm/types.h>
/*
 * Structs for Facility Messages
 */

enum FacFunction {
	Fac_None 				= 0xffff,
	
	Fac_ReturnResult			= 0xff02,
	Fac_ReturnError				= 0xff03,
	Fac_Reject				= 0xff04,
 
	Fac_CCBS		 		= 0xee02,
	
	Fac_GetSupportedServices		= 0x0000,
	Fac_Listen				= 0x0001,
 	Fac_MCID				= 0x0003,
	Fac_Suspend				= 0x0004,
	Fac_Resume 				= 0x0005,
	Fac_ECTExecute				= 0x0006,
	Fac_CFActivate 				= 0x0009,
	Fac_CFDeactivate 			= 0x000a,
	Fac_CFInterrogateParameters		= 0x000b,
	Fac_CFInterrogateNumbers	        = 0x000c,
	Fac_CD					= 0x000d,
	Fac_DNDQ				= 0x0037,
	Fac_CRerouting 				= 0x000e,
	Fac_AOCDCurrency 			= 0x0021,
	Fac_AOCDChargingUnit 	        	= 0x0022,
};

// typedef enum {
// 	GeneralP     = 0,
// 	InvokeP      = 1,
// 	ReturnResultP= 2,
// 	ReturnErrorP = 3,
// } asn1Problem;


struct FacListen {
	__u32 NotificationMask;
};

struct FacSuspend {
	__s8  CallIdentity[16];
};

struct FacResume {
	__s8  CallIdentity[16];
};

struct FacCFActivate {
	__u16 invokeId;
	__u32 Handle;
	__u16 Procedure;
	__u16 BasicService;
	__u16 NoReplyTimer;
	__s8  ServedUserNumber[16];
	__s8  ForwardedToNumber[16];
	__s8  ForwardedToSubaddress[16];
};

struct FacCFDeactivate {
	__u16 invokeId;
	__u32 Handle;
	__u16 Procedure;
	__u16 BasicService;
	__s8  ServedUserNumber[16];
};

struct FacCDeflection {
	__u16 invokeId;
	__u16 PresentationAllowed;
	__s8  DeflectedToNumber[16];
	__s8  DeflectedToSubaddress[16];
};

struct FacCRerouting {
	//__u16 PresentationAllowed;
	__s8  DeflectedFromNumber[16];
	__s8  DeflectedToSubaddress[16];
};


struct FacDNDQ {
	__u16 Id;
};

#define FacCFInterrogateParameters FacCFDeactivate

struct FacCFInterrogateNumbers {
	__u32 Handle;
};

struct FacAOCDChargingUnit {
	__u16 chargeNotAvailable;
	__u16 freeOfCharge;
	__s32 recordedUnits;
	__s32 typeOfChargingInfo;
	__s32 billingId;
};

struct FacAOCDCurrency {
	__u16 chargeNotAvailable;
	__u16 freeOfCharge;
	__u8  currency[11];
	__s32 currencyAmount;
	__s32 multiplier;
	__s32 typeOfChargingInfo;
	__s32 billingId;
};

struct FacReturnResult {
	__u16 invokeId;
};

struct FacReturnError {
	__u16 invokeId;
	__u16 errorValue;
	char  error[80];
};

struct FacReject {
	__u16 invokeId;
	asn1Problem problem;
	__u16 problemValue;
};

struct FacCCBS {
	__u16 type;
	__u16 invokeId;
	__u16 operation;
	__u16 callLinkageId;
	__u16 reference;
};

struct FacMCID {
	__u16 invokeId;
};

struct FacECTExecute {
	__u16 invokeId;
};

struct FacParm {
	enum FacFunction Function;
	union {
		struct FacReturnResult Result;
		struct FacReturnError Error;
		struct FacReject Reject;

		struct FacCCBS CCBS;

		struct FacListen Listen;
		struct FacSuspend Suspend;
		struct FacResume Resume;
		struct FacCFActivate CFActivate;
		struct FacCFDeactivate CFDeactivate;
		struct FacCFInterrogateParameters CFInterrogateParameters;
		struct FacCFInterrogateNumbers CFInterrogateNumbers;
		struct FacCDeflection CDeflection;
		struct FacCRerouting CRerouting;
		struct FacDNDQ DNDQ;
		struct FacAOCDChargingUnit AOCDchu;
		struct FacAOCDCurrency AOCDcur;
		struct FacMCID MCID;
		struct FacECTExecute ECTExecute;
	} u;
};

/*
 * encodeFac (__u8 *dest, struct FacParm *fac)
 *
 * encode the facility (fac) into the buffer (dest)
 *
 * parameter:
 * dest  - destination buffer
 * fac   - facility to encode
 *
 * returns:
 *    length of the encoded facility, or -1 on error
 */
int encodeFac (__u8 *dest, struct FacParm *fac);

/*
 * decodeFac (__u8 *src, struct FacParm *fac)
 *
 * decode the facility (src) and write the result to (fac)
 *
 * parameter:
 * src   - encoded facility
 * fac   - where to store the result
 *
 * returns:
 *    0 on success, -1 on error
 */
int decodeFac (__u8 *src, struct FacParm *fac);

#endif
