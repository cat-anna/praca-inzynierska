/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/gui/GUISettings.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once
#ifndef GUISettings_H
#define GUISettings_H

namespace VisApp {
namespace gui {

struct BaseSetting {
	virtual void Save(xml_node out) const = 0;
	virtual void Load(const xml_node in) = 0;
	virtual void SetDefault() { };
	virtual ~BaseSetting() { };
};

typedef std::vector<BaseSetting*> SettingsStore;

template <class REGISTER>
struct AbstractSetting : public BaseSetting {
	AbstractSetting() {
		REGISTER::RegisterSetting(this);
	}
};

template <class TYPE, class INFO, class REGISTER>
struct SettingValue : public AbstractSetting<REGISTER> {
	void set(const TYPE& val) { m_val = val; }
	const TYPE& get() const { return m_val; }

	void SetDefault() { m_val = INFO::Default(); }
	void Save(xml_node out) const { WriteChildText(out, INFO::Name(), m_val); }
	void Load(const xml_node in) { ReadChildText(in, INFO::Name(), m_val, INFO::Default()); }
	SettingValue() { SetDefault(); }

	typedef SettingValue<TYPE, INFO, REGISTER> ThisClass;
	ThisClass& operator=(const TYPE& input) { m_val = input; return *this; }
	operator const TYPE& () const { return m_val; }
protected:
	TYPE m_val;
};

#ifndef _T
#define _T(A) L##A
#endif

template <class GROUP, class INFO>
struct GroupSettingsRegister {
	static void RegisterSetting(BaseSetting *as) { _Store.push_back(as); };

	static void StoreSettings(xml_node out) {
		xml_node node = out.append_child(INFO::Name());
		for(auto &it: _Store) it->Save(node);
	}
	static void LoadSettings(const xml_node in) {
		const xml_node node = in.child(INFO::Name());
		if(node) for(auto &it: _Store) it->Load(node);
	}
private:
	static SettingsStore _Store;
};

template <class GROUP, class INFO>
SettingsStore GroupSettingsRegister<GROUP, INFO>::_Store;

#define Declare_Setting(NAME, TYPE, DEFAULT)\
public:\
	struct Setting_##NAME##_info {\
		static const TYPE& Default() { static const TYPE val = DEFAULT; return val; }\
		static const wchar_t* Name() { return _T(#NAME); }\
		typedef TYPE type_t; \
	};\
	typedef SettingValue<TYPE, Setting_##NAME##_info, CurrentRegister> Setting_##NAME##_type;\
	Setting_##NAME##_type NAME;\

#define Declare_Settings_Group(NAME ,SETTINGS)\
public:\
	struct Group_##NAME##_Info {\
		static const wchar_t *Name() { return _T(#NAME); };\
	};\
	struct Group_##NAME;\
	typedef GroupSettingsRegister<Group_##NAME, Group_##NAME##_Info> Group_##NAME##_Register;\
	struct Group_##NAME : public AbstractSetting<CurrentRegister> {\
		typedef Group_##NAME##_Register CurrentRegister;\
		virtual void Save(xml_node out) const { CurrentRegister::StoreSettings(out); }\
		virtual void Load(const xml_node in) { CurrentRegister::LoadSettings(in); }\
		SETTINGS\
	};\
	Group_##NAME NAME;\

class Settings {
public:
 	~Settings();
	static void DoSave();
	static void DoLoad();

	struct Settings_Info {
		static const wchar_t *Name() { return L"Settings"; };
	};
	typedef GroupSettingsRegister<Settings, Settings_Info> CurrentRegister;

	static Settings& root() { return Instance(); }

	Declare_Settings_Group(DataInspector,
		Declare_Setting(Use, bool, true)
		Declare_Setting(ShowDelay, unsigned, 1000)
	)
/*
	Declare_Settings_Group(t1,
		Declare_Setting(Use, bool, true)
		Declare_Settings_Group(t2,
			Declare_Setting(Use, bool, true)
			Declare_Setting(ShowDelay, unsigned, 1000)
		)
	)
*/
//	Declare_Setting(SettingsAutoSave, bool, true)

private: 
	static Settings& Instance();
	static Settings *_Instance;

	bool m_DataLoaded;

 	Settings();
	void Load();
	void Save();
	 
	Settings(const Settings&);//=delete;
	Settings& operator=(const Settings&);//=delete;
};

#undef Declare_Setting

} //namespace gui 
} //namespace VisApp 

#endif

