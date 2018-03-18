/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/D2Mapper/Processor.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once
#pragma unmanaged 

using namespace VisApp::Plugins;

#include <VisApp\include\Tools\Normalize.h>
#include <VisApp\include\Tools\Planes.h>
#include <VisApp\include\Tools\Color.h>
using namespace VisApp::Tools;

enum class OutMode {
	Map, 
	Isolines,
};

enum class NormalizeMode {
	DirectValue,

	Length,
	LengthSections,

	VectorNormalize,
//	VectorNormalizeSections,

	LengthMinMax,
	LengthMinMaxSections,

	ValuesMinMax,
	ValuesMinMaxSections,
};

enum class ColorSelectionMode {
	None,
	Continous,
	Random,
};

typedef std::function<void(float pos, float max)> ProcessorUpdateFun;

struct ConfigData {
	OutMode Mode;
	NormalizeMode Normalization; 
	ColorSelectionMode ColorMode;

	VisApp::Types::DataType SrcDataType;

	unsigned SectionCount;

	fvec3 PositionDelta;
	uvec3 InputDataSize;
	uvec3 OutputDataSize;

	VisApp::Interface::DataPointer SrcDataPtr;

	unsigned Subdivs;

	index_t InputSize() const { return InputDataSize[0] * InputDataSize[1] * InputDataSize[2]; }
	index_t InputPos(const Math::uvec3 &pos) const { return pos[0] + (pos[1] + pos[2] * InputDataSize[1]) * InputDataSize[0]; }
	index_t InputPos(const Math::uvec2 &pos) const { return pos[0] + pos[1] * InputDataSize[0]; }
	
	index_t OutputSize() const { return OutputDataSize[0] * OutputDataSize[1] * OutputDataSize[2]; }
	index_t OutputPos(const Math::uvec3 &pos) const { return pos[0] + (pos[1] + pos[2] * OutputDataSize[1]) * OutputDataSize[0]; }
	index_t OutputPos(const Math::uvec2 &pos) const { return pos[0] + pos[1] * OutputDataSize[0]; }

	ProcessorUpdateFun UpdateFun;

	enum class Flags {

	};
	bool TestFlag(Flags f) const { return (m_Flags & (1 << (unsigned)f)) > 0; }
	void SetFlag(Flags f)  { m_Flags |= (1 << (unsigned)f); }
	void SetFlag(Flags f, bool val)  { if(val) SetFlag(f); else ClearFlag(f); }
	void ClearFlag(Flags f)  { m_Flags &= ~(1 << (unsigned)f); }

	ConfigData() {
		m_Flags = 0;
		Normalization = NormalizeMode::DirectValue;
		ColorMode = ColorSelectionMode::None;
		Subdivs = 1;
		SectionCount = 10;
	}

//conf geters
	unsigned GetSectionCount() const { return SectionCount; }
	const VisApp::Interface::iDataChannel *GetDataChannel() const { return SrcDataPtr.Channel; }
private:
	unsigned m_Flags;
};

#include "Accessor.h"
#include "NormalizationConfig.h"

class Processor : public ProcessPlugin {
public: 
	Processor();
	virtual ~Processor();

	CLIGuiHandler* GetCLIGuiHandler();

	ConfigData& GetConfig() { return m_Config; }

	void UpdateConfig();
protected:
	ConfigData m_Config;
protected:
	virtual void BeforeRun();
	virtual void AfterRun();
	virtual void Run();
	virtual void OnExecute();
	virtual void StoreRuntimeConfig(xml_node out) const { }
	virtual void LoadRuntimeConfig(const xml_node in) { }
private:
	std::auto_ptr<CLIGuiHandler> m_GuiHandler;
};

