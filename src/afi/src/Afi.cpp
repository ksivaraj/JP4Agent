//
// Juniper P4 Agent
//
/// @file  Afi.cpp
/// @brief Afi
//
// Created by Sandesh Kumar Sodhi, January 2018
// Copyright (c) [2018] Juniper Networks, Inc. All rights reserved.
//
// All rights reserved.
//
// Notice and Disclaimer: This code is licensed to you under the Apache
// License 2.0 (the "License"). You may not use this code except in compliance
// with the License. This code is not an official Juniper product. You can
// obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
// Third-Party Code: This code may depend on other components under separate
// copyright notice and license terms. Your use of the source code for those
// components is subject to the terms and conditions of the respective license
// as noted in the Third-Party source code file.
//

#include "Afi.h"

namespace AFIHAL {

bool 
Afi::handleAfiJsonObject(const Json::Value &cfg_obj)
{
    Log(DEBUG) << "___ AFI::handleAfiJsonObject ___\n";

	// TBD: Revisit: on stack
	AfiJsonResource res(cfg_obj["afi-object-type"].asString(),
						cfg_obj["afi-object-id"].asUInt64(),
						cfg_obj["afi-object-name"].asString(),
						cfg_obj["afi-object"].asString());
	
	//   
	// Create Afi Object
	//   
	AfiObjectPtr afiObj = _afiDevice->handleDMObject(res);

	//   
	// If we didn't create a object, we fail the operation
	//   
	if (afiObj == nullptr) {
        Log(ERROR) << "Error creating afi object";
		return false;
	}

    return true;
}

bool 
Afi::handlePipelineConfig(const Json::Value &cfg_root)
{
    Log(DEBUG) << "____ AFI:: handlePipelineConfig ____\n";
    for (Json::Value::ArrayIndex i = 0; i != cfg_root.size(); i++) {
        const Json::Value &cfg_obj = cfg_root[i];
        auto status = handleAfiJsonObject(cfg_obj);
        if (true != status) {
            Log(ERROR) << "Error handling afi json object";
            return status;
        }
    }

    return true;
}

bool 
Afi::addEntry(const std::string &keystr, int pLen)
{
    Log(DEBUG) << "____ AFI::addEntry ____\n";
    Log(DEBUG) << "keystr : " << keystr;
    Log(DEBUG) << "pLen   : " << pLen;

    Json::Value afiTreeEntryJsonObject;

    afiTreeEntryJsonObject["afi-object-type"] = "afi-tree-entry";

    std::string afi_object_name = "entry1";
    afiTreeEntryJsonObject["afi-object-name"] = afi_object_name;
    afiTreeEntryJsonObject["afi-object-id"] = 1233456;

    juniper::afi_tree_entry::AfiTreeEntry afiTreeEntry;

    ::ywrapper::StringValue *entry_name = new ::ywrapper::StringValue();
    entry_name->set_value("entry1");
    afiTreeEntry.set_allocated_name(entry_name);

    ::ywrapper::StringValue *parent_name = new ::ywrapper::StringValue();
    parent_name->set_value("ipv4_lpm");
    afiTreeEntry.set_allocated_parent_name(parent_name);

    ::ywrapper::StringValue *target_afi_object = new ::ywrapper::StringValue();
    target_afi_object->set_value("etherencap1");
    afiTreeEntry.set_allocated_target_afi_object(target_afi_object);

    ::ywrapper::StringValue *prefix_bytes = new ::ywrapper::StringValue();
    //prefix_bytes->set_value("10.10.10.10/16");
    prefix_bytes->set_value(keystr);
    afiTreeEntry.set_allocated_prefix_bytes(prefix_bytes);

    ::ywrapper::UintValue *prefix_length = new ::ywrapper::UintValue();
    prefix_length->set_value(pLen);
    afiTreeEntry.set_allocated_prefix_length(prefix_length);

    int tree_size = afiTreeEntry.ByteSize();
    char* array = new char[tree_size];
    std::cout << "tree_size: " << tree_size << std::endl;
    afiTreeEntry.SerializeToArray(array, tree_size);

    std::string encoded = base64_encode(array, (unsigned int)tree_size);
    std::cout << "encoded: " << encoded << std::endl << std::endl;

    afiTreeEntryJsonObject["afi-object"] = encoded;

	auto status = handleAfiJsonObject(afiTreeEntryJsonObject);
	if (true != status) {
		Log(ERROR) << "Error handling afi tree entry json object";
		return status;
	}

    return true;
}
 
}  // namespace AFIHAL
