#include "ViewManager.hpp"
#include "Specter/Control.hpp"
#include "Specter/Space.hpp"
#include "SplashScreen.hpp"
#include "locale/locale.hpp"
#include "ResourceOutliner.hpp"

using YAMLNode = Athena::io::YAMLNode;

namespace RUDE
{

Specter::View* ViewManager::BuildSpaceViews(RUDE::Space* space)
{
    m_rootSpaceView = space->buildSpaceView(m_viewResources);
    return m_rootSpaceView;
}

Specter::RootView* ViewManager::SetupRootView()
{
    m_rootView.reset(new Specter::RootView(*this, m_viewResources, m_mainWindow.get()));
    m_rootView->setBackground(Zeus::CColor::skBlack);
    return m_rootView.get();
}

SplashScreen* ViewManager::SetupSplashView()
{
    m_splash.reset(new SplashScreen(*this, m_viewResources));
    if (!m_showSplash)
        m_splash->close(true);
    return m_splash.get();
}

void ViewManager::SetupEditorView()
{
    SplitSpace* split = new SplitSpace(*this);
    split->setSpaceSlot(0, std::make_unique<ResourceOutliner>(*this));
    split->setSpaceSlot(1, std::make_unique<ResourceOutliner>(*this));
    m_rootSpace.reset(split);

    std::vector<Specter::View*>& cViews = m_rootView->accessContentViews();
    cViews.clear();
    cViews.push_back(BuildSpaceViews(m_rootSpace.get()));
    cViews.push_back(m_splash.get());
    m_rootView->updateSize();
}

void ViewManager::SetupEditorView(ConfigReader& r)
{
    m_rootSpace.reset(Space::NewSpaceFromConfigStream(*this, r));
    std::vector<Specter::View*>& cViews = m_rootView->accessContentViews();
    cViews.clear();
    cViews.push_back(BuildSpaceViews(m_rootSpace.get()));
    cViews.push_back(m_splash.get());
    m_rootView->updateSize();
}

void ViewManager::SaveEditorView(ConfigWriter& w)
{
    if (!m_rootSpace)
        return;
    m_rootSpace->saveState(w);
}

void ViewManager::DismissSplash()
{
    if (!m_showSplash)
        return;
    m_showSplash = false;
    m_splash->close();
}

ViewManager::ViewManager(HECL::Runtime::FileStoreManager& fileMgr, HECL::CVarManager& cvarMgr)
: m_fileStoreManager(fileMgr), m_cvarManager(cvarMgr), m_projManager(*this),
  m_fontCache(fileMgr), m_translator(RUDE::SystemLocaleOrEnglish())
{}

ViewManager::~ViewManager() {}

void ViewManager::pushRecentProject(const HECL::SystemString& path)
{
    m_recentProjects.push_back(path);
}

void ViewManager::pushRecentFile(const HECL::SystemString& path)
{
    m_recentFiles.push_back(path);
}

void ViewManager::init(boo::IApplication* app)
{
    m_mainWindow = std::unique_ptr<boo::IWindow>(app->newWindow(_S("RUDE")));
    m_mainWindow->showWindow();
    m_mainWindow->setWaitCursor(true);

    float pixelFactor = 1.0;

    boo::IGraphicsDataFactory* gf = m_mainWindow->getMainContextDataFactory();
    m_viewResources.init(gf, &m_fontCache, Specter::ThemeData(), pixelFactor);
    m_viewResources.prepFontCacheAsync(m_mainWindow.get());
    Specter::RootView* root = SetupRootView();
    m_showSplash = true;
    root->accessContentViews().push_back(SetupSplashView());
    root->updateSize();

    m_mainWindow->setWaitCursor(false);
}

bool ViewManager::proc()
{
    boo::IGraphicsCommandQueue* gfxQ = m_mainWindow->getCommandQueue();
    if (m_rootView->isDestroyed())
        return false;

    if (m_updatePf)
    {
        m_viewResources.resetPixelFactor(m_reqPf);
        Specter::RootView* root = SetupRootView();
        std::vector<Specter::View*>& cViews = root->accessContentViews();
        if (m_rootSpace)
            cViews.push_back(BuildSpaceViews(m_rootSpace.get()));
        cViews.push_back(SetupSplashView());
        root->updateSize();
        m_updatePf = false;
    }

    m_rootView->dispatchEvents();
    if (m_rootSpace)
        m_rootSpace->think();
    if (m_splash)
        m_splash->think();

    ++m_editorFrames;
    if (m_rootSpaceView && m_editorFrames <= 30)
        m_rootSpaceView->setMultiplyColor(Zeus::CColor::lerp({1,1,1,0}, {1,1,1,1}, m_editorFrames / 30.0));

    m_rootView->draw(gfxQ);
    gfxQ->execute();
    m_mainWindow->waitForRetrace();

    return true;
}

void ViewManager::stop()
{
    m_mainWindow->getCommandQueue()->stopRenderer();
}

}

