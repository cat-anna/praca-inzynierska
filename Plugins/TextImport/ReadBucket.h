/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/TextImport/ReadBucket.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

class ReadBucket {
public:
	typedef std::vector<float_t> LineVector;
	typedef std::vector<LineVector> BucketVector;

	ReadBucket(unsigned MaxSize, unsigned LineReserve = 10): m_Bucket(MaxSize), m_MaxSize(MaxSize) { 
		for(auto it = m_Bucket.begin(), jt = m_Bucket.end(); it != jt; ++it)
			it->resize(LineReserve);
	}

	LineVector& GetLine(unsigned line) { return m_Bucket[line]; }
	size_t GetBucketSize() const { return m_Bucket.size(); }
	 
	BucketVector& GetBucket() { return m_Bucket; }
	unsigned MaxSize() const { return m_MaxSize; }
private:
	BucketVector m_Bucket;
	unsigned m_MaxSize;
};
