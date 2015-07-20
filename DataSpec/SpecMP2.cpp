#include <utility>

#include "SpecBase.hpp"
#include "DNAMP2/DNAMP2.hpp"

namespace Retro
{

static LogVisor::LogModule Log("Retro::SpecMP2");
extern HECL::Database::DataSpecEntry SpecEntMP2;

struct SpecMP2 : SpecBase
{
    bool checkStandaloneID(const char* id) const
    {
        if (!memcmp(id, "G2M", 3))
            return true;
        return false;
    }

    bool doMP2 = false;
    std::vector<const NOD::DiscBase::IPartition::Node*> m_nonPaks;
    std::vector<DNAMP2::PAKBridge> m_paks;
    std::map<std::string, DNAMP2::PAKBridge*, CaseInsensitiveCompare> m_orderedPaks;

    void buildPaks(HECL::Database::Project& project,
                   NOD::DiscBase::IPartition::Node& root,
                   const std::vector<HECL::SystemString>& args,
                   ExtractReport& rep)
    {
        m_nonPaks.clear();
        m_paks.clear();
        for (const NOD::DiscBase::IPartition::Node& child : root)
        {
            bool isPak = false;
            const std::string& name = child.getName();
            std::string lowerName = name;
            std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), tolower);
            if (name.size() > 4)
            {
                std::string::iterator extit = lowerName.end() - 4;
                if (!std::string(extit, lowerName.end()).compare(".pak"))
                {
                    /* This is a pak */
                    isPak = true;
                    std::string lowerBase(lowerName.begin(), extit);

                    /* Needs filter */
                    bool good = true;
                    if (args.size())
                    {
                        good = false;
                        if (!lowerName.compare(0, 7, "metroid"))
                        {
                            HECL::SystemChar idxChar = lowerName[7];
                            for (const HECL::SystemString& arg : args)
                            {
                                if (arg.size() == 1 && iswdigit(arg[0]))
                                    if (arg[0] == idxChar)
                                        good = true;
                            }
                        }
                        else
                            good = true;

                        if (!good)
                        {
                            for (const HECL::SystemString& arg : args)
                            {
#if HECL_UCS2
                                std::string lowerArg = HECL::WideToUTF8(arg);
#else
                                std::string lowerArg = arg;
#endif
                                std::transform(lowerArg.begin(), lowerArg.end(), lowerArg.begin(), tolower);
                                if (!lowerArg.compare(0, lowerBase.size(), lowerBase))
                                    good = true;
                            }
                        }
                    }

                    if (good)
                        m_paks.emplace_back(project, child);
                }
            }

            if (!isPak)
                m_nonPaks.push_back(&child);
        }

        /* Sort PAKs alphabetically */
        m_orderedPaks.clear();
        for (DNAMP2::PAKBridge& dpak : m_paks)
            m_orderedPaks[dpak.getName()] = &dpak;

        /* Assemble extract report */
        for (const std::pair<std::string, DNAMP2::PAKBridge*>& item : m_orderedPaks)
        {
            rep.childOpts.emplace_back();
            ExtractReport& childRep = rep.childOpts.back();
            childRep.name = item.first;
            childRep.desc = item.second->getLevelString();
        }
    }

    bool checkFromStandaloneDisc(HECL::Database::Project& project,
                                 NOD::DiscBase& disc,
                                 const HECL::SystemString& regstr,
                                 const std::vector<HECL::SystemString>& args,
                                 std::vector<ExtractReport>& reps)
    {
        doMP2 = true;
        NOD::DiscGCN::IPartition* partition = disc.getDataPartition();
        std::unique_ptr<uint8_t[]> dolBuf = partition->getDOLBuf();
        const char* buildInfo = (char*)memmem(dolBuf.get(), partition->getDOLSize(), "MetroidBuildInfo", 16) + 19;

        /* Root Report */
        reps.emplace_back();
        ExtractReport& rep = reps.back();
        rep.name = _S("MP2");
        rep.desc = _S("Metroid Prime 2 ") + regstr;
        if (buildInfo)
        {
            std::string buildStr(buildInfo);
            HECL::SystemStringView buildView(buildStr);
            rep.desc += _S(" (") + buildView + _S(")");
        }

        /* Iterate PAKs and build level options */
        NOD::DiscBase::IPartition::Node& root = partition->getFSTRoot();
        buildPaks(project, root, args, rep);

        return true;
    }

    bool checkFromTrilogyDisc(HECL::Database::Project& project,
                              NOD::DiscBase& disc,
                              const HECL::SystemString& regstr,
                              const std::vector<HECL::SystemString>& args,
                              std::vector<ExtractReport>& reps)
    {
        std::vector<HECL::SystemString> mp2args;
        if (args.size())
        {
            /* Needs filter */
            for (const HECL::SystemString& arg : args)
            {
                HECL::SystemString lowerArg = arg;
                HECL::ToLower(lowerArg);
                if (!lowerArg.compare(0, 3, "mp2"))
                {
                    doMP2 = true;
                    size_t slashPos = arg.find(_S('/'));
                    if (slashPos == HECL::SystemString::npos)
                        slashPos = arg.find(_S('\\'));
                    if (slashPos != HECL::SystemString::npos)
                        mp2args.emplace_back(HECL::SystemString(arg.begin() + slashPos + 1, arg.end()));
                }
            }
        }
        else
            doMP2 = true;

        if (!doMP2)
            return true;

        NOD::DiscGCN::IPartition* partition = disc.getDataPartition();
        NOD::DiscBase::IPartition::Node& root = partition->getFSTRoot();
        NOD::DiscBase::IPartition::Node::DirectoryIterator dolIt = root.find("rs5mp2_p.dol");
        if (dolIt == root.end())
            return false;

        std::unique_ptr<uint8_t[]> dolBuf = dolIt->getBuf();
        const char* buildInfo = (char*)memmem(dolBuf.get(), dolIt->size(), "MetroidBuildInfo", 16) + 19;

        /* Root Report */
        reps.emplace_back();
        ExtractReport& rep = reps.back();
        rep.name = _S("MP2");
        rep.desc = _S("Metroid Prime 2 ") + regstr;
        if (buildInfo)
        {
            std::string buildStr(buildInfo);
            HECL::SystemStringView buildView(buildStr);
            rep.desc += _S(" (") + buildView + _S(")");
        }

        /* Iterate PAKs and build level options */
        NOD::DiscBase::IPartition::Node::DirectoryIterator mp2It = root.find("MP2");
        if (mp2It == root.end())
            return false;
        buildPaks(project, *mp2It, mp2args, rep);

        return true;
    }

    bool extractFromDisc(HECL::Database::Project& project, NOD::DiscBase&, bool force,
                         FExtractProgress progress)
    {
        if (!doMP2)
            return true;

        HECL::ProjectPath mp2WorkPath(project.getProjectRootPath(), "MP2");
        mp2WorkPath.makeDir();
        progress(_S("MP2 Root"), 2, 0.0);
        int prog = 0;
        for (const NOD::DiscBase::IPartition::Node* node : m_nonPaks)
        {
            node->extractToDirectory(mp2WorkPath.getAbsolutePath(), force);
            progress(_S("MP2 Root"), 2, prog++ / (float)m_nonPaks.size());
        }
        progress(_S("MP2 Root"), 2, 1.0);

        const HECL::ProjectPath& cookPath = project.getProjectCookedPath(SpecEntMP2);
        cookPath.makeDir();
        HECL::ProjectPath mp2CookPath(cookPath, "MP2");
        mp2CookPath.makeDir();

        int compIdx = 3;
        prog = 0;
        for (DNAMP2::PAKBridge& pak : m_paks)
        {
            const std::string& name = pak.getName();
            HECL::SystemStringView sysName(name);

            std::string::const_iterator extit = name.end() - 4;
            std::string baseName(name.begin(), extit);

            HECL::ProjectPath pakWorkPath(mp2WorkPath, baseName);
            pakWorkPath.makeDir();
            HECL::ProjectPath pakCookPath(mp2CookPath, baseName);
            pakCookPath.makeDir();

            progress(sysName.sys_str().c_str(), compIdx, 0.0);
            pak.extractResources(pakWorkPath, pakCookPath, force,
                                 [&progress, &sysName, &compIdx](float factor)
            {
                progress(sysName.sys_str().c_str(), compIdx, factor);
            });
            progress(sysName.sys_str().c_str(), compIdx++, 1.0);
        }

        return true;
    }

    bool checkFromProject(HECL::Database::Project& proj)
    {
    }
    bool readFromProject(HECL::Database::Project& proj)
    {
    }

    bool visitGameObjects(std::function<bool(const HECL::Database::ObjectBase&)>)
    {
    }
    struct LevelSpec : public ILevelSpec
    {
        bool visitLevelObjects(std::function<bool(const HECL::Database::ObjectBase&)>)
        {
        }
        struct AreaSpec : public IAreaSpec
        {
            bool visitAreaObjects(std::function<bool(const HECL::Database::ObjectBase&)>)
            {
            }
        };
        bool visitAreas(std::function<bool(const IAreaSpec&)>)
        {
        }
    };
    bool visitLevels(std::function<bool(const ILevelSpec&)>)
    {
    }
};

HECL::Database::DataSpecEntry SpecEntMP2
(
    _S("MP2"),
    _S("Data specification for original Metroid Prime 2 engine"),
    [](HECL::Database::DataSpecTool tool) -> HECL::Database::IDataSpec* {return new struct SpecMP2;}
);

}
