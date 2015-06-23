// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/FileSystem.cpp
//! @brief     Implements class FileSystem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FileSystem.h"
#include "BAConfigure.h"
#include "Exceptions.h"
#include <boost/filesystem.hpp>


std::string Utils::FileSystem::m_argv0_path = std::string();
std::string Utils::FileSystem::m_reference_data_dir = std::string();

void Utils::FileSystem::SetArgvPath(const std::string& argv0)
{
    m_argv0_path = argv0;
}

std::string Utils::FileSystem::GetArgvPath()
{
    return m_argv0_path;
}


//! Returns path to the current (working) directory.

std::string Utils::FileSystem::GetWorkingPath()
{
    return boost::filesystem::current_path().string();
}

//! Returns path to BornAgain home directory.

std::string Utils::FileSystem::GetHomePath()
{
    throw NotImplementedException("Utils::FileSystem::GetHomePath()-> Not implemented anymore...");
    return std::string();
}

std::string Utils::FileSystem::GetPathToExecutable(const std::string& argv0)
{
    std::string result = boost::filesystem::canonical( argv0.c_str() ).parent_path().string();
    return result;
}


std::string Utils::FileSystem::GetPathToData(const std::string& rel_data_path, const std::string& argv0)
{
//#ifdef _WIN32
//    // windows build place executable in additional sub-directory 'release'
//    std::string result = (boost::filesystem::canonical( argv0.c_str() ).parent_path() / boost::filesystem::path("../") / boost::filesystem::path(rel_data_path)).string();
//#else
    std::string result = (boost::filesystem::canonical( argv0.c_str() ).parent_path() / boost::filesystem::path(rel_data_path)).string();
//#endif
    return result;
}

//! Returns file extension.

std::string Utils::FileSystem::GetFileExtension(const std::string& name)
{
    return boost::filesystem::extension(name.c_str());
}

//! Does name contain *.gz extension?

bool Utils::FileSystem::isGZipped(const std::string& name)
{
    static const std::string gzip_extension(".gz");
    if ( Utils::FileSystem::GetFileExtension(name) == gzip_extension)
        return true;
    return false;
}

//! Returns file main extension (without .gz).

std::string Utils::FileSystem::GetFileMainExtension(const std::string& name)
{
    if( !isGZipped(name) ) {
        return Utils::FileSystem::GetFileExtension(name);
    } else {
        std::string stripped_name = name.substr(0, name.size()-3);
        return Utils::FileSystem::GetFileExtension(stripped_name);
    }
}

std::string Utils::FileSystem::GetFileMainName(const std::string &name)
{
    if( !isGZipped(name) ) {
        return Utils::FileSystem::GetFileExtension(name);
    } else {
        std::string stripped_name = name.substr(0, name.size()-3);
        return stripped_name;
    }
}


std::string Utils::FileSystem::GetSourceDir()
{
#ifdef BORNAGAIN_SOURCE_DIR
    return std::string(BORNAGAIN_SOURCE_DIR );
#else
    throw LogicErrorException("Utils::FileSystem::GetSourceDir() -> Error. Not configured.");
#endif
}

std::string Utils::FileSystem::GetInstallDir()
{
#ifdef BORNAGAIN_INSTALL_DIR
    return std::string(BORNAGAIN_INSTALL_DIR);
#else
    throw LogicErrorException("Utils::FileSystem::GetInstallDir() -> Error. Not configured.");
#endif
}

std::string Utils::FileSystem::GetReferenceDataDir()
{
    if(m_reference_data_dir.empty()) {
        return GetSourceDir() + std::string("/Tests/ReferenceData/BornAgain/");
    } else {
        return m_reference_data_dir;
    }
}


bool Utils::FileSystem::CreateDirectory(const std::string &dir_name)
{
    boost::filesystem::path dir(dir_name);
    return boost::filesystem::create_directory(dir);
}

std::string Utils::FileSystem::GetJoinPath(const std::string &spath1, const std::string &spath2)
{
    boost::filesystem::path path1(spath1);
    boost::filesystem::path path2(spath2);
    boost::filesystem::path full_path = path1 / path2;

    return full_path.string();
}

