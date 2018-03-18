/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Project/FileHeaders.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/

#pragma once
#ifndef BinaryHeaders_H
#define BinaryHeaders_H

namespace VisApp {
namespace Project {
namespace BinFiles { 
namespace Headers {

#define VISAPP_DATAFILE_EXTENSION	L".vdf"
	
#pragma pack(push, 1)

struct Signatures {
	enum {
		Primary				= 'MEMV',
	};
};

struct Versions {
	enum {
		v0				= 0,
	};
};

struct SecondaryHeaderTypes {
	enum {
		NoSecondaryHeader	= 0,
		RawDataHeader,
	};
};

struct PrimaryHeader {
	unsigned __int32 Signature;
	unsigned __int32 Version;
	unsigned __int16 SecondaryHeaderType;

	unsigned __int16 ReservedShort;
	unsigned __int32 Reserved; //for 16bytes boundary and future use;

	PrimaryHeader() {
		Signature = Signatures::Primary;
		Version = Versions::v0;
		SecondaryHeaderType = SecondaryHeaderTypes::NoSecondaryHeader;
		Reserved = 0;
		ReservedShort = 0;
	}

	bool IsValid() {
		return Version == Versions::v0 && Signature == Signatures::Primary;
	};
};

struct RawDataHeader {
	//no signature
	unsigned __int64 DataSize;
	unsigned __int32 DataCRC;//currently not used
	unsigned __int32 Reserved; //for 16bytes boundary and future use;

	RawDataHeader() {
		DataSize = 0;
		DataCRC = 0;
		Reserved = 0;
	}
};

struct RawFileHeader : public PrimaryHeader, public RawDataHeader {
	RawFileHeader() {
		SecondaryHeaderType = SecondaryHeaderTypes::RawDataHeader;
	}
};

#pragma pack (pop)

} //namespace Headers
} //namespace BinFiles
} //namespace Project
} //namespace VisApp

#endif
