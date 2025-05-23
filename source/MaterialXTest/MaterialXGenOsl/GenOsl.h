//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#ifndef GENOSL_H
#define GENOSL_H

#include <MaterialXTest/External/Catch/catch.hpp>
#include <MaterialXTest/MaterialXGenShader/GenShaderUtil.h>

#include <MaterialXGenOsl/OslShaderGenerator.h>

namespace mx = MaterialX;

class OslShaderGeneratorTester : public GenShaderUtil::ShaderGeneratorTester
{
  public:
    using ParentClass = GenShaderUtil::ShaderGeneratorTester;

    OslShaderGeneratorTester(mx::ShaderGeneratorPtr shaderGenerator, const std::vector<mx::FilePath>& testRootPaths,
                             const mx::FileSearchPath& searchPath, const mx::FilePath& logFilePath, bool writeShadersToDisk) :
        GenShaderUtil::ShaderGeneratorTester(shaderGenerator, testRootPaths, searchPath, logFilePath, writeShadersToDisk)
    {}

    void setTestStages() override
    {
        _testStages.push_back(mx::Stage::PIXEL);
    }

    // Ignore trying to create shader code for lightshaders
    void addSkipNodeDefs() override
    {
        _skipNodeDefs.insert("ND_point_light");
        _skipNodeDefs.insert("ND_spot_light");
        _skipNodeDefs.insert("ND_directional_light");
        ParentClass::addSkipNodeDefs();
    }

    // Arnold specific files are ignored in vanilla osl target
    void addSkipLibraryFiles() override
    {
        _skipLibraryFiles.insert( "pbrlib_genosl_arnold_impl.mtlx" );
    }

    void addSkipFiles() override
    {
        _skipFiles.insert("standard_surface_onyx_hextiled.mtlx");
        _skipFiles.insert("hextiled.mtlx");
    }

    // Ignore light shaders in the document for OSL
    void findLights(mx::DocumentPtr /*doc*/, std::vector<mx::NodePtr>& lights) override
    {
        lights.clear();
    }

    // No direct lighting to register for OSL
    void registerLights(mx::DocumentPtr /*doc*/, const std::vector<mx::NodePtr>& /*lights*/, mx::GenContext& /*context*/) override
    {
    }

  protected:
    void getImplementationWhiteList(mx::StringSet& whiteList) override
    {
        whiteList =
        {
            "displacementshader", "volumeshader",
            "IM_constant_", "IM_dot_", "IM_angle", "IM_geompropvalue", "IM_geompropvalueuniform"
        };
        ShaderGeneratorTester::getImplementationWhiteList(whiteList);
    }
};

#endif // GENOSL_H
