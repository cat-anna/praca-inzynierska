/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/D2Mapper/NormalizationConfig.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

namespace NormConfig {
	struct NormInfo {
		const wchar_t *Name;
		const wchar_t *Description;
		bool Sections;
	};

	struct NormConf {
		const OutMode Alogrithm;
		const NormalizeMode Normalization;
		const NormInfo &Info;
		VisApp::Types::DataType::TypeFilter AllowedTypes;

		NormConf(OutMode algo, NormalizeMode Norm, const NormInfo &inf);
	};

	struct NormConfTable {
		typedef std::vector<NormConf> NormConfVector;
		static const NormConfVector& Get();
		static const NormConf* Find(OutMode algo, NormalizeMode norm) {
			for(auto &it: Get()) 
				if(it.Alogrithm == algo && it.Normalization == norm)
					return &it;
			return 0;
		}
	protected:
		static NormConfVector _table;
	};
}