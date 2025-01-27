#pragma once
#include "struct_field.h"
#include <memory>

#define SET_STRUCT_FIELD(inst, field, data) inst.##field = data

struct SettlementDetailInfo
{
	std::string clientid;
	double price;
	int volume;
	double amount;

	void set_field(const std::string& key, const std::string& value)
	{
		auto it = fieldptrs_.find(key);
		if (it != fieldptrs_.end())
		{
			it->second->set_value(value, *this);
		}
		else
		{
			std::cout << "not find field: " << key;
		}
	}

	void print_field()
	{
		for (const auto& value : fieldptrs_)
		{
			std::cout << value.first << ":" << value.second->get_value(*this) << std::endl;
		}
	}

private:
	static std::map<std::string, std::unique_ptr<StructFieldBase<SettlementDetailInfo> > > init_fieldptrs();
	const static std::map<std::string, std::unique_ptr<StructFieldBase<SettlementDetailInfo> > > fieldptrs_;
};

std::map<std::string, std::unique_ptr<StructFieldBase<SettlementDetailInfo> > > SettlementDetailInfo::init_fieldptrs()
{
	std::map<std::string, std::unique_ptr<StructFieldBase<SettlementDetailInfo> > > tmp;
	tmp["clientid"] = std::unique_ptr<StructFieldBase<SettlementDetailInfo> >(new StructField<SettlementDetailInfo, std::string SettlementDetailInfo::*>(&SettlementDetailInfo::clientid));
	tmp["price"] = std::unique_ptr<StructFieldBase<SettlementDetailInfo> >(new StructField<SettlementDetailInfo, double SettlementDetailInfo::*>(&SettlementDetailInfo::price));
	tmp["volume"] = std::unique_ptr<StructFieldBase<SettlementDetailInfo> >(new StructField<SettlementDetailInfo, int SettlementDetailInfo::*>(&SettlementDetailInfo::volume));
	tmp["amount"] = std::unique_ptr<StructFieldBase<SettlementDetailInfo> >(new StructField<SettlementDetailInfo, double SettlementDetailInfo::*>(&SettlementDetailInfo::amount));
	return tmp;
}
const std::map<std::string, std::unique_ptr<StructFieldBase<SettlementDetailInfo> > > SettlementDetailInfo::fieldptrs_ = SettlementDetailInfo::init_fieldptrs();


class TestStructField
{
public:
	void test()
	{
		std::map<std::string, std::string> datas;
		datas["clientid"] = "one";
		datas["price"] = "3.14";
		datas["volume"] = "789";
		datas["amount"] = "4556.90";

		SettlementDetailInfo info;
		for (const auto& data : datas)
		{
			info.set_field(data.first, data.second);
		}

		info.print_field();
	}
};