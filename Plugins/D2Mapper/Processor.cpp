/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/D2Mapper/Processor.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "Processor.h"
#include "ProcessorConfigForm.h"

#pragma unmanaged

namespace Math = VisApp::Math;
namespace Types = VisApp::Types;

Processor::Processor() {
}

Processor::~Processor() {
}

CLIGuiHandler* Processor::GetCLIGuiHandler() {
	UpdateConfig();
	if(!m_Config.SrcDataPtr.IsOk()) return 0;
	if(!m_GuiHandler.get())
		m_GuiHandler.reset(new D2Mapper::GuiHandler(this));
	return m_GuiHandler.get();
}

void Processor::BeforeRun() {
	ProcessPlugin::BeforeRun();
}

void Processor::AfterRun() {
	ProcessPlugin::AfterRun();
}

void Processor::UpdateConfig() {
	m_Config.SrcDataPtr = GetDataSource().Translate();
	m_Config.SrcDataPtr.Channel->GetSize(m_Config.InputDataSize);
	m_Config.PositionDelta = Math::fvec3(m_Config.InputDataSize) /= 2.0f;
	m_Config.OutputDataSize = m_Config.InputDataSize * m_Config.Subdivs;
	m_Config.SrcDataType = m_Config.SrcDataPtr.Channel->GetType();

	m_Config.UpdateFun = [this](float a, float b) {
		GetExec()->SetProgress(a / b);
	};
}

void Processor::Run() {
	ProcessPlugin::Run();
	UpdateConfig();
#if 0
	Math::uvec3 size;
	DataSrc.Channel->GetSize(size);

	auto Data = DataSrc.Channel->GetMemory<Types::VariableType::Integer, Types::DataDimiension::d1>();
	auto layer = DataSrc.Project->GetDataStore()->CreateInternalLayer(this, GetOutputName());
	auto constructor = layer->GetLayerConstructor();
	if(!constructor) {
		//sth bad has happen
		throw false;
	} 

	switch (m_Mode) {
	case OutMode::Map:
		break;
	case OutMode::Isolines:
		break;
	default:
		MakeError("Wrong work mode!");
	}

	layer->AddDataSoure(DataSrc.Channel);
#endif
}

void Processor::OnExecute() {
	ProcessPlugin::OnExecute();
}