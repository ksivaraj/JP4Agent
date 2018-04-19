//
// Juniper P4 Agent
//
/// @file  BrcmTree.h
/// @brief Brcm Tree Object
//
// Created by Sudheendra Gopinath, March 2018
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

#ifndef __BrcmTree__
#define __BrcmTree__

namespace BRCMHALP {

class BrcmTree;
using BrcmTreePtr = std::shared_ptr<BrcmTree>;
using BrcmTreeWeakPtr = std::weak_ptr<BrcmTree>;

class BrcmTree: public BrcmObjectTemplate<AFIHAL::AfiTree, BrcmTree>
{
    using BrcmObjectTemplate::BrcmObjectTemplate;
public:
    //BrcmTree (const AfiJsonResource &jsonRes) : AfiTree(jsonRes) {}
    //~BrcmTree () {}

    /// 
    /// @brief  Create the hardware state
    /// 
    void _bind() override;
    
    //
    // @brief  Debug
    //
    std::ostream &description (std::ostream &os) const;
    
    friend std::ostream &operator<< (std::ostream &os,
                                     const BrcmTreePtr &BrcmTree) {
        return BrcmTree->description(os);
    }
};

}  // namespace BRCMHALP

#endif // __BrcmTree__