/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/Plugins/TextImport/TextImport.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "TextImport.h"
#include "FileReader.h"
#include "CLIGuiHandler.h"
#pragma unmanaged

TextImportPlugin::TextImportPlugin(): 
		ImportPlugin(),
		m_CollumnSeparator(';'),
		//m_DecimalSeparator('.'),
		m_ImportFlags(0) {
	SetFlag(ImportFlags::FirstLineHaveSize, true);
	SetFlag(ImportFlags::IgonoreFollowingSeparator, true);

	m_XYZMap[static_cast<index_t>(Mapping::X)] = 0;
	m_XYZMap[static_cast<index_t>(Mapping::Y)] = 1;
	m_XYZMap[static_cast<index_t>(Mapping::Z)] = 2;

	m_CoordVars = SharedVariableDesciptor(new VariableDescriptor());
	m_CoordVars->Type = VisApp::Types::DataType::D3Integer();
	m_CoordVars->DoImport = false;
	m_CoordVars->Name = L"Wspó³rzêdne";
	m_CoordVars->FirstValueID = 0;
	m_Variables.push_back(m_CoordVars);
}

TextImportPlugin::~TextImportPlugin() {
}

void TextImportPlugin::AddVariable(const wchar_t *name, VisApp::Types::DataType type) {
	VariableDescriptor dbgcolumn;
	//= new VariableDescriptor();
//	dbgcolumn->Type = type;
//	dbgcolumn->DoImport = true;
	dbgcolumn.Name = name;
//	GetVariables().push_back(SharedVariableDesciptor(dbgcolumn));
}

void TextImportPlugin::SaveCollumSettings(xml_node out) const {
	for(auto &it: m_Variables) {
		auto var = out.append_child(L"Variable");

		var.append_child(L"Name").text() = it->Name.c_str();

		auto sett = var.append_child(L"Settings");
		sett.append_attribute(L"FirstValueID") = it->FirstValueID;
		sett.append_attribute(L"DoImport") = it->DoImport;

		if(it.get() == m_CoordVars.get()) {
			sett.append_attribute(L"IsCoords") = true;
		}

		it->Type.Save(var.append_child(L"Type"));
	}
}

void TextImportPlugin::LoadCollumnSettings(const xml_node in) {
	m_Variables.clear();
	m_CoordVars.reset();

	for(auto var = in.child(L"Variable"); var; var = var.next_sibling(L"Variable")) {
		
		auto v = SharedVariableDesciptor(new VariableDescriptor());;
		m_Variables.push_back(v);
		v->Name = var.child(L"Name").text().as_string();

		auto sett = var.child(L"Settings");
		v->FirstValueID = sett.attribute(L"FirstValueID").as_uint();
		v->DoImport = sett.attribute(L"DoImport").as_bool(true);
		if(sett.attribute(L"IsCoords").as_bool(false)) {
			m_CoordVars = v;
			v->DoImport = false;
		}

		v->Type.Load(var.child(L"Type"));
	}
}

CLIGuiHandler* TextImportPlugin::GetCLIGuiHandler() {
	if(!m_GuiHandler.get())
		m_GuiHandler.reset(new GuiHandler(this));
	return m_GuiHandler.get();
}

bool TextImportPlugin::CheckFlag(ImportFlags flag) const {
	return (m_ImportFlags & (1 << static_cast<unsigned>(flag))) > 0;
}

void TextImportPlugin::SetFlag(ImportFlags flag, bool status) {
	unsigned mask = 1 << static_cast<unsigned>(flag);
	if(status) m_ImportFlags |= mask;
	else m_ImportFlags &= ~mask;
}

void TextImportPlugin::SetSourceFile(const std::wstring &file) {
	ImportPlugin::SetSourceFile(file);
}

void TextImportPlugin::ReadDataSize(FileReader &reader, ReadBucket::LineVector* out) {
	if(!out) {
		ReadBucket::LineVector linev;
		linev.reserve(10);
		reader.DoReadLine(linev);
	} else
		reader.DoReadLine(*out);
}

PreprocessResult TextImportPlugin::PreprocessFile() {
	if(!CheckFile())
		return SetPreporcessResult(PreprocessResult::FileNotFound);

	//const unsigned SampleSize = 100;

	try {
		std::ifstream file(GetSrcFile(), std::ios::in);
		if(!file)
			throw PreprocessResult::FileNotFound;
	//TODO!!!!	
	/*	std::vector<std::string> lines;
		lines.resize(SampleSize);
		//read file
		for(unsigned i = 0; i < SampleSize; ++i) {
			std::string line;
			std::getline(file, line);
			lines[i].swap(line);
		}
		*/

		//dumb detect collumn separator
		{
			file.seekg(0);
			std::string line;
			std::getline(file, line);
			std::vector<char> separators;
			for(auto &it: line) {
				if(isdigit(it)) continue;
				separators.push_back(it);
			}
			std::sort(separators.begin(), separators.end());
			separators.erase(std::unique(separators.begin(), separators.end()), separators.end());
			separators.push_back('\0');
			auto findsep = [&separators](char sep) -> bool {
				return strchr(&separators[0], sep) != NULL;
			};

			switch(separators.size() - 1) {
			case 0: 
				//?
				break;
			case 1:
				if(separators[0] != '.') {
					m_CollumnSeparator = separators[0];
				} else {
					// One Dot to rule them all, One Dot to find them,
					// One Dot to bring them all and in the darkness bind them.
					m_CollumnSeparator = '\0';
				}
				break;
			default:
				//TODO: do sth
				break;
			}
		}

		//dumb read size
		if(CheckFlag(ImportFlags::FirstLineHaveSize)) {
			file.seekg(0);
			LineImportSettings LineSettings;
			LineSettings.CollumnSeparator = m_CollumnSeparator;

			FileReader reader;
			reader.SetInputStream(&file);
			reader.SetLineSettings(LineSettings);
			ReadBucket::LineVector linev;
			linev.resize(10);
			ReadDataSize(reader, &linev);

			if(m_CoordVars) {
				const float_t *CoordBeg = &linev[0] + m_CoordVars->FirstValueID;

				Math::uvec3 s(1, 1, 1);
				switch (m_CoordVars->Type.Dimiension) {
				case DataDimiension::d3:
					s[2] = static_cast<index_t>(CoordBeg[GetMapping(Mapping::Z)]);
					if(s[2] == 0.0f) {
						m_CoordVars->Type.Dimiension = DataDimiension::d2;
						s[2] = 1.0f;
					}
				case DataDimiension::d2:
					s[1] = static_cast<index_t>(CoordBeg[GetMapping(Mapping::Y)]);
					if(s[1] == 0.0f) {
						m_CoordVars->Type.Dimiension = DataDimiension::d1;
						s[1] = 1.0f;
					}
				case DataDimiension::d1:
					s[0] = static_cast<index_t>(CoordBeg[GetMapping(Mapping::X)]);
				}

				SetDataSize(s);
			}
		}

		throw PreprocessResult::Ok;
	}
	catch (PreprocessResult err) {
		return SetPreporcessResult(err);
	}
	catch(...) {
		return SetPreporcessResult(PreprocessResult::UnknownError);
	}
}

void TextImportPlugin::OnExecute() {
	m_Project = VisApp::Interface::iProjectMgt::GetInstance()->GetProject(GetProjectName());
	if(!m_Project) {
		//TODO: throw some error!
	}
	auto store = m_Project->GetDataStore();
	m_OutSeries = store->AddSeries(GetSeriesName(), GetDataSize3());
	if(!m_OutSeries) {
		//TODO: throw some error!
	}
	for(auto &it: m_Variables)
		if(it->DoImport)
			if(!(it->DataChannel = m_OutSeries->AddChannel(it->Name, it->Type))) {
				//TODO: make some error!
			}
};

unsigned TextImportPlugin::ResetVariableIds() {
	index_t index = 0;
	for(auto &it: m_Variables) {
		it->FirstValueID = index;
		index += it->Type.ValuesCount();
	}
	return index;
}

unsigned TextImportPlugin::GetVariableCount() const {
	index_t index = 0;
	for(auto &it: m_Variables) {
		index += it->Type.ValuesCount();
	}
	return index;
}
struct ImportData {
	LineImportSettings LineSettings;
	ImportStructure Data;
	FileReader Reader;
	std::ifstream File;
 
	ImportData() { }
	~ImportData() {
		for(auto &it: Data) delete it;
		File.close();
	}
};

void TextImportPlugin::BeforeRun() {
	ImportPlugin::BeforeRun();
	ResetVariableIds();
	m_Import = new ImportData();
	m_Import->LineSettings.CollumnSeparator = m_CollumnSeparator;

	for(auto &it: m_Variables) {
		if(it->DoImport)
			m_Import->Data.push_back(it->CreateImportTable());
	}

	m_Import->File.open(GetSrcFile(), std::ios::in);
	m_Import->Reader.SetInputStream(&m_Import->File);
	m_Import->Reader.SetLineSettings(m_Import->LineSettings);
}

void TextImportPlugin::Run() {
	ImportPlugin::Run();

	FileReader &Reader = m_Import->Reader;
	ImportStructure &Data = m_Import->Data;
	ReadBucket Bucket(10000, GetVariableCount());

	if(CheckFlag(ImportFlags::FirstLineHaveSize)) {
		ReadDataSize(Reader, 0);
	}

	if(m_CoordVars) {//preconditions to run, but not to fail
//		Reader.Begin();
		m_OutSeries->SetStatus(VisApp::Interface::iDataSeries::eSeriesStatus::Importing);
		while(!Reader.Finished()) {
			CheckInstance();
			if(Reader.DoReadBucket(Bucket) < 1) break;

			Math::uvec3 pos(0, 0, 0);

		//	for(auto &i: Bucket.GetBucket()) {
			auto &bucket = Bucket.GetBucket();
			int bucketlen = bucket.size();
//#pragma omp parallel for num_threads(2)
			for(int n = 0; n < bucketlen; ++n) {
				auto &i = bucket[n];
				const float_t *Values = &i[0];
				const float_t *CoordBeg = Values + m_CoordVars->FirstValueID;
#define GetMapping(A) ((index_t)(A))
				switch (m_CoordVars->Type.Dimiension) {
				case DataDimiension::d3:
					pos[2] = static_cast<index_t>(CoordBeg[GetMapping(Mapping::Z)]);
				case DataDimiension::d2:
					pos[1] = static_cast<index_t>(CoordBeg[GetMapping(Mapping::Y)]);
				case DataDimiension::d1:
					pos[0] = static_cast<index_t>(CoordBeg[GetMapping(Mapping::X)]);
				}
#undef GetMapping
				for(auto &it: Data) {
					auto *vd = it->GetDescriptor();
					it->PutValue(pos, Values + vd->FirstValueID, vd->Type.ValuesCount());
				}
			}
			GetExec()->SetProgress(Reader.FilePos() / (float)GetFileSize());//m_FileReader->FileProgress());
		}
	}
	GetExec()->SetProgress(1);
}

void TextImportPlugin::AfterRun() {
	ImportPlugin::AfterRun();
	delete m_Import;
	m_OutSeries->SetStatus(VisApp::Interface::iDataSeries::eSeriesStatus::Ok);
}
