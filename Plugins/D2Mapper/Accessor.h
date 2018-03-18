/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/D2Mapper/Accessor.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once

namespace Accessor {

	namespace Types = VisApp::Types;

	template <class OUT_t, class POS_TYPE>
	struct Getter {
		typedef OUT_t OutType_t;
		typedef POS_TYPE Location_t;

		struct BaseGetter {
			virtual ~BaseGetter(){};
			virtual OUT_t get(const POS_TYPE&) = 0;
		};

		template <class Normalizer>
		struct NormalizerDispatch {
			static BaseGetter* Do(ConfigData & config) {
				auto ch = config.SrcDataPtr.Channel;
				return Types::DataType::DispatchTypeTemplate<GetterInstance, BaseGetter, ConfigData &>(ch->GetType(), config);
			}

			template <Types::VariableType VT, Types::DataDimiension DD>
			struct GetterInstance : BaseGetter {
				typedef typename VisApp::Interface::ChannelMemory<VT, DD> Mem_t;
				Normalizer norm;
				Mem_t Memory;
				GetterInstance(ConfigData & config): BaseGetter(),
					Memory(config.SrcDataPtr.Channel->GetMemory<VT, DD>()){
					norm.init(Memory, config);
				}
				virtual OUT_t get(const POS_TYPE& pos) {
					auto &itm = Memory.at(pos);
					return Normalize::caster<OUT_t>::cast(norm.call(itm));
				}
			};
		};

		BaseGetter *norm;

		void SetSource(ConfigData &config) {
			using namespace Normalize;
			switch (config.Normalization) {
			case NormalizeMode::DirectValue: 
				norm = NormalizerDispatch<Normalize::DirectValue>::Do(config);
				break;

			case NormalizeMode::Length:
				norm = NormalizerDispatch<Normalize::Length>::Do(config);
				break;

			case NormalizeMode::VectorNormalize:
				norm = NormalizerDispatch<Normalize::Vector>::Do(config);
				break;

		/*	case NormalizeMode::VectorNormalizeSections:
				norm = new NormalizerDispatch<Normalize::VectorEx<Sectionizer<>>>(config);
				break;*/

			case NormalizeMode::LengthMinMax:
				norm = NormalizerDispatch<LengthMinMax<MinMaxNormalize<>>>::Do(config);
				break;
			case NormalizeMode::LengthMinMaxSections:
				norm = NormalizerDispatch<LengthMinMax<MinMaxSections<>>>::Do(config);
				break;

			case NormalizeMode::ValuesMinMax:
				norm = NormalizerDispatch<ValuesMinMax<MinMaxNormalize<>>>::Do(config);
				break;
			case NormalizeMode::ValuesMinMaxSections:
				norm = NormalizerDispatch<ValuesMinMax<MinMaxSections<>>>::Do(config);
				break;

			default:
				throw "unsupported normalize mode";
			}
		}

		Getter() {
			norm = 0;
		}

		~Getter() {
			delete norm;
		}

		OUT_t operator () (const POS_TYPE& p) {
			return norm->get(p);
		}
	};
}
