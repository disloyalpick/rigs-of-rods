/*
    This source file is part of Rigs of Rods
    Copyright 2005-2012 Pierre-Michel Ricordel
    Copyright 2007-2012 Thomas Fischer
    Copyright 2013-2017 Petr Ohlidal & contributors

    For more information, see http://www.rigsofrods.org/

    Rigs of Rods is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3, as
    published by the Free Software Foundation.

    Rigs of Rods is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Rigs of Rods. If not, see <http://www.gnu.org/licenses/>.
*/

/// @file   GUIManager.h
/// @author based on the basemanager code from mygui common

#include "GUIManager.h"

#include "Application.h"
#include "BeamFactory.h"
#include "ContentManager.h"
#include "InputEngine.h"
#include "Language.h"
#include "OgreImGui.h"
#include "OgreSubsystem.h"
#include "RoRWindowEventUtilities.h"
#include "RTTLayer.h"
#include "Settings.h"
#include "TerrainManager.h"

//Managed GUI panels
#include "GUI_FrictionSettings.h"
#include "GUI_GameMainMenu.h"
#include "GUI_GameAbout.h"
#include "GUI_GameConsole.h"
#include "GUI_GamePauseMenu.h"
#include "GUI_GameChatBox.h"
#include "GUI_LoadingWindow.h"
#include "GUI_MessageBox.h"
#include "GUI_MultiplayerSelector.h"
#include "GUI_MultiplayerClientList.h"
#include "GUI_MainSelector.h"
#include "GUI_RigSpawnerReportWindow.h"
#include "GUI_SimUtils.h"
#include "GUI_TextureToolWindow.h"
#include "GUI_TeleportWindow.h"
#include "GUI_TopMenubar.h"
#include "GUI_VehicleDescription.h"

#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>

#define RESOURCE_FILENAME "MyGUI_Core.xml"

namespace RoR {

struct GuiManagerImpl
{
    GuiManagerImpl():
        mygui(nullptr),
        mygui_platform(nullptr)
    {}

    GUI::GameMainMenu           panel_GameMainMenu;
    GUI::GameAbout              panel_GameAbout;
    GUI::GamePauseMenu          panel_GamePauseMenu;
    GUI::SimUtils               panel_SimUtils;
    GUI::gMessageBox            panel_MessageBox;
    GUI::MultiplayerSelector    panel_MultiplayerSelector;
    GUI::MainSelector           panel_MainSelector;
    GUI::GameChatBox            panel_ChatBox;
    GUI::RigSpawnerReportWindow panel_SpawnerReport;
    GUI::VehicleDescription     panel_VehicleDescription;
    GUI::MpClientList           panel_MpClientList;
    GUI::FrictionSettings       panel_FrictionSettings;
    GUI::TextureToolWindow      panel_TextureToolWindow;
    GUI::TeleportWindow         panel_TeleportWindow;
    GUI::LoadingWindow          panel_LoadingWindow;
    GUI::TopMenubar             panel_TopMenubar;
    RoR::Console                panel_GameConsole;

    MyGUI::Gui*                 mygui;
    MyGUI::OgrePlatform*        mygui_platform;
};

void GUIManager::SetVisible_GameMainMenu        (bool v) { m_impl->panel_GameMainMenu       .SetVisible(v); }
void GUIManager::SetVisible_GameAbout           (bool v) { m_impl->panel_GameAbout          .SetVisible(v); }
void GUIManager::SetVisible_MultiplayerSelector (bool v) { m_impl->panel_MultiplayerSelector.SetVisible(v); }
void GUIManager::SetVisible_ChatBox             (bool v) { m_impl->panel_ChatBox            .SetVisible(v); }
void GUIManager::SetVisible_SpawnerReport       (bool v) { m_impl->panel_SpawnerReport      .SetVisible(v); }
void GUIManager::SetVisible_VehicleDescription  (bool v) { m_impl->panel_VehicleDescription .SetVisible(v); }
void GUIManager::SetVisible_MpClientList        (bool v) { m_impl->panel_MpClientList       .SetVisible(v); }
void GUIManager::SetVisible_FrictionSettings    (bool v) { m_impl->panel_FrictionSettings   .SetVisible(v); }
void GUIManager::SetVisible_TextureToolWindow   (bool v) { m_impl->panel_TextureToolWindow  .SetVisible(v); }
void GUIManager::SetVisible_TeleportWindow      (bool v) { m_impl->panel_TeleportWindow     .SetVisible(v); }
void GUIManager::SetVisible_LoadingWindow       (bool v) { m_impl->panel_LoadingWindow      .SetVisible(v); }
void GUIManager::SetVisible_Console             (bool v) { m_impl->panel_GameConsole        .SetVisible(v); }

bool GUIManager::IsVisible_GameMainMenu         () { return m_impl->panel_GameMainMenu       .IsVisible(); }
bool GUIManager::IsVisible_GameAbout            () { return m_impl->panel_GameAbout          .IsVisible(); }
bool GUIManager::IsVisible_MessageBox           () { return m_impl->panel_MessageBox         .IsVisible(); }
bool GUIManager::IsVisible_MultiplayerSelector  () { return m_impl->panel_MultiplayerSelector.IsVisible(); }
bool GUIManager::IsVisible_MainSelector         () { return m_impl->panel_MainSelector       .IsVisible(); }
bool GUIManager::IsVisible_ChatBox              () { return m_impl->panel_ChatBox            .IsVisible(); }
bool GUIManager::IsVisible_SpawnerReport        () { return m_impl->panel_SpawnerReport      .IsVisible(); }
bool GUIManager::IsVisible_VehicleDescription   () { return m_impl->panel_VehicleDescription .IsVisible(); }
bool GUIManager::IsVisible_MpClientList         () { return m_impl->panel_MpClientList       .IsVisible(); }
bool GUIManager::IsVisible_FrictionSettings     () { return m_impl->panel_FrictionSettings   .IsVisible(); }
bool GUIManager::IsVisible_TextureToolWindow    () { return m_impl->panel_TextureToolWindow  .IsVisible(); }
bool GUIManager::IsVisible_TeleportWindow       () { return m_impl->panel_TeleportWindow     .IsVisible(); }
bool GUIManager::IsVisible_LoadingWindow        () { return m_impl->panel_LoadingWindow      .IsVisible(); }
bool GUIManager::IsVisible_Console              () { return m_impl->panel_GameConsole        .IsVisible(); }

// GUI GetInstance*()
Console*                    GUIManager::GetConsole()           { return &m_impl->panel_GameConsole         ; }
GUI::MainSelector*          GUIManager::GetMainSelector()      { return &m_impl->panel_MainSelector        ; }
GUI::LoadingWindow*         GUIManager::GetLoadingWindow()     { return &m_impl->panel_LoadingWindow       ; }
GUI::MpClientList*          GUIManager::GetMpClientList()      { return &m_impl->panel_MpClientList        ; }
GUI::MultiplayerSelector*   GUIManager::GetMpSelector()        { return &m_impl->panel_MultiplayerSelector ; }
GUI::FrictionSettings*      GUIManager::GetFrictionSettings()  { return &m_impl->panel_FrictionSettings    ; }
GUI::SimUtils*              GUIManager::GetSimUtils()          { return &m_impl->panel_SimUtils            ; }
GUI::TopMenubar*            GUIManager::GetTopMenubar()        { return &m_impl->panel_TopMenubar          ; }
GUI::TeleportWindow*        GUIManager::GetTeleport()          { return &m_impl->panel_TeleportWindow      ; }

GUIManager::GUIManager() :
    m_renderwindow_closed(false),
    m_impl(nullptr)
{
    RoR::App::GetOgreSubsystem()->GetOgreRoot()->addFrameListener(this);
    RoRWindowEventUtilities::addWindowEventListener(RoR::App::GetOgreSubsystem()->GetRenderWindow(), this);

    GStr<300> gui_logpath;
    gui_logpath << App::sys_logs_dir.GetActive() << PATH_SLASH << "MyGUI.log";
    auto mygui_platform = new MyGUI::OgrePlatform();
    mygui_platform->initialise(
        RoR::App::GetOgreSubsystem()->GetRenderWindow(), 
        gEnv->sceneManager,
        Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME,
        gui_logpath.GetBuffer()); // use cache resource group so preview images are working
    auto mygui = new MyGUI::Gui();

    // empty init
    mygui->initialise("");

    // add layer factory
    MyGUI::FactoryManager::getInstance().registerFactory<MyGUI::RTTLayer>("Layer");

    // then load the actual config
    MyGUI::ResourceManager::getInstance().load(RESOURCE_FILENAME);

    MyGUI::ResourceManager::getInstance().load(LanguageEngine::getSingleton().getMyGUIFontConfigFilename());

    m_impl = new GuiManagerImpl();
    m_impl->mygui_platform = mygui_platform;
    m_impl->mygui = mygui;

    // move the mouse into the middle of the screen, assuming we start at the top left corner (0,0)
    MyGUI::InputManager::getInstance().injectMouseMove(RoR::App::GetOgreSubsystem()->GetRenderWindow()->getWidth()*0.5f, RoR::App::GetOgreSubsystem()->GetRenderWindow()->getHeight()*0.5f, 0);
    MyGUI::PointerManager::getInstance().setVisible(true);
#ifdef _WIN32
    MyGUI::LanguageManager::getInstance().eventRequestTag = MyGUI::newDelegate(this, &GUIManager::eventRequestTag);
#endif // _WIN32
    windowResized(RoR::App::GetOgreSubsystem()->GetRenderWindow());

    this->SetupImGui();
}

GUIManager::~GUIManager()
{
    delete m_impl;
}

void GUIManager::UnfocusGui()
{
    MyGUI::InputManager::getInstance().resetKeyFocusWidget();
    MyGUI::InputManager::getInstance().resetMouseCaptureWidget();
}

void GUIManager::ShutdownMyGUI()
{
    delete m_impl;

    if (m_impl->mygui)
    {
        m_impl->mygui->shutdown();
        delete m_impl->mygui;
        m_impl->mygui = nullptr;
    }

    if (m_impl->mygui_platform)
    {
        m_impl->mygui_platform->shutdown();
        delete m_impl->mygui_platform;
        m_impl->mygui_platform = nullptr;
    }
}

bool GUIManager::frameStarted(const Ogre::FrameEvent& evt)
{
    if (m_renderwindow_closed) return false;
    if (!m_impl->mygui) return true;


    // now hide the mouse cursor if not used since a long time
    if (getLastMouseMoveTime() > 5000)
    {
        MyGUI::PointerManager::getInstance().setVisible(false);
        //RoR::App::GetGuiManager()->GetTopMenubar()->setVisible(false);
    }

    return true;
}

bool GUIManager::frameEnded(const Ogre::FrameEvent& evt)
{
    return true;
};

void GUIManager::DrawSimulationGui(float dt)
{
    m_impl->panel_SimUtils.framestep(dt);
    if (App::app_state.GetActive() == AppState::SIMULATION)
    {
        m_impl->panel_TopMenubar.Update();

        if (App::sim_state.GetActive() == SimState::PAUSED)
        {
            m_impl->panel_GamePauseMenu.Draw();
        }
    }
};

void GUIManager::PushNotification(Ogre::String Title, Ogre::UTFString text)
{
    m_impl->panel_SimUtils.PushNotification(Title, text);
}

void GUIManager::HideNotification()
{
    m_impl->panel_SimUtils.HideNotificationBox();
}

void GUIManager::SetSimController(RoRFrameListener* sim)
{
    m_impl->panel_GameConsole       .SetSimController(sim);
    m_impl->panel_MpClientList      .SetSimController(sim);
    m_impl->panel_VehicleDescription.SetSimController(sim);
}

void GUIManager::windowResized(Ogre::RenderWindow* rw)
{
    int width = (int)rw->getWidth();
    int height = (int)rw->getHeight();
    setInputViewSize(width, height);

}

void GUIManager::windowClosed(Ogre::RenderWindow* rw)
{
    m_renderwindow_closed = true;
}

void GUIManager::eventRequestTag(const MyGUI::UString& _tag, MyGUI::UString& _result)
{
    _result = MyGUI::LanguageManager::getInstance().getTag(_tag);
}

Ogre::String GUIManager::getRandomWallpaperImage()
{
    using namespace Ogre;
    FileInfoListPtr files = ResourceGroupManager::getSingleton().findResourceFileInfo("Wallpapers", "*.jpg", false);
    if (files.isNull() || files->empty())
    {
        files = ResourceGroupManager::getSingleton().findResourceFileInfo("Wallpapers", "*.png", false);
        if (files.isNull() || files->empty())
            return "";
    }
    srand ( time(NULL) );

    int num = 0;
    for (int i = 0; i<Math::RangeRandom(0, 10); i++)
        num = Math::RangeRandom(0, files->size());

    return files->at(num).filename;
}

void GUIManager::SetSceneManagerForGuiRendering(Ogre::SceneManager* scene_manager)
{
    m_impl->mygui_platform->getRenderManagerPtr()->setSceneManager(scene_manager);
}

void GUIManager::UpdateSimUtils(float dt, Beam *truck)
{
    if (m_impl->panel_SimUtils.IsBaseVisible()) //Better to update only when it's visible.
    {
        m_impl->panel_SimUtils.UpdateStats(dt, truck);
    }
}

void GUIManager::ShowMessageBox(Ogre::String mTitle, Ogre::String mText, bool button1, Ogre::String mButton1, bool AllowClose = false, bool button2 = false, Ogre::String mButton2 = "")
{
    m_impl->panel_MessageBox.ShowMessageBox(mTitle, mText, button1, mButton1, AllowClose, button2, mButton2);
}

void GUIManager::UpdateMessageBox(Ogre::String mTitle, Ogre::String mText, bool button1, Ogre::String mButton1, bool AllowClose = false, bool button2 = false, Ogre::String mButton2 = "", bool IsVisible = true)
{
    m_impl->panel_MessageBox.UpdateMessageBox(mTitle, mText, button1, mButton1, AllowClose, button2, mButton2, IsVisible);
}

int GUIManager::getMessageBoxResult()
{
    return m_impl->panel_MessageBox.getResult();
}

void GUIManager::AddRigLoadingReport(std::string const & vehicle_name, std::string const & text, int num_errors, int num_warnings, int num_other)
{
    m_impl->panel_SpawnerReport.SetRigLoadingReport(vehicle_name, text, num_errors, num_warnings, num_other);
}

void GUIManager::CenterSpawnerReportWindow()
{
    m_impl->panel_SpawnerReport.CenterToScreen();
}

void GUIManager::pushMessageChatBox(Ogre::String txt)
{
    m_impl->panel_ChatBox.pushMsg(txt);
}

void GUIManager::hideGUI(bool hidden)
{
    if (hidden)
    {
        m_impl->panel_SimUtils.HideNotificationBox();
        m_impl->panel_SimUtils.SetFPSBoxVisible(false);
        m_impl->panel_SimUtils.SetTruckInfoBoxVisible(false);
        m_impl->panel_ChatBox.Hide();
    }
    m_impl->panel_SimUtils.DisableNotifications(hidden);
}

void GUIManager::FrictionSettingsUpdateCollisions()
{
    App::GetGuiManager()->GetFrictionSettings()->setCollisions(gEnv->collisions);
}

void GUIManager::SetMouseCursorVisible(bool visible)
{
    this->SupressCursor(!visible);
}

void GUIManager::ReflectGameState()
{
    const auto app_state = App::app_state.GetActive();
    const auto mp_state  = App::mp_state.GetActive();
    if (app_state == AppState::MAIN_MENU)
    {
        m_impl->panel_GameMainMenu       .SetVisible(!m_impl->panel_MainSelector.IsVisible());

        m_impl->panel_ChatBox            .SetVisible(false);
        m_impl->panel_FrictionSettings   .SetVisible(false);
        m_impl->panel_TextureToolWindow  .SetVisible(false);
        m_impl->panel_TeleportWindow     .SetVisible(false);
        m_impl->panel_VehicleDescription .SetVisible(false);
        m_impl->panel_SpawnerReport      .SetVisible(false);
        m_impl->panel_SimUtils           .SetBaseVisible(false);
        m_impl->panel_MpClientList       .SetVisible(mp_state == MpState::CONNECTED);
        return;
    }
    if (app_state == AppState::SIMULATION)
    {
        m_impl->panel_SimUtils           .SetBaseVisible(true);
        m_impl->panel_GameMainMenu       .SetVisible(false);
        return;
    }
}

void GUIManager::NewImGuiFrame(float dt)
{
    // Update screen size
    int left, top, width, height;
    gEnv->mainCamera->getViewport()->getActualDimensions(left, top, width, height); // output params

     // Read keyboard modifiers inputs
    OIS::Keyboard* kb = App::GetInputEngine()->GetOisKeyboard();
    bool ctrl  = kb->isKeyDown(OIS::KC_LCONTROL);
    bool shift = kb->isKeyDown(OIS::KC_LSHIFT);
    bool alt   = kb->isKeyDown(OIS::KC_LMENU);

    // Call IMGUI
    m_imgui.NewFrame(dt, Ogre::Rect(left, top, width, height), ctrl, alt, shift);
}

void GUIManager::SetupImGui()
{
    m_imgui.Init();
    // Colors
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_Text]                  = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled]          = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    style.Colors[ImGuiCol_WindowBg]              = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    style.Colors[ImGuiCol_ChildWindowBg]         = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PopupBg]               = ImVec4(0.05f, 0.05f, 0.10f, 1.00f);
    style.Colors[ImGuiCol_Border]                = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style.Colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_FrameBg]               = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.78f, 0.39f, 0.00f, 0.99f);
    style.Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.90f, 0.65f, 0.65f, 0.98f);
    style.Colors[ImGuiCol_TitleBg]               = ImVec4(0.57f, 0.31f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.40f, 0.40f, 0.80f, 1.00f);
    style.Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.74f, 0.44f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.16f, 0.16f, 0.16f, 0.99f);
    style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.30f, 0.30f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.78f, 0.39f, 0.00f, 0.99f);
    style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(1.00f, 0.50f, 0.00f, 0.99f);
    style.Colors[ImGuiCol_ComboBg]               = ImVec4(0.20f, 0.20f, 0.20f, 0.99f);
    style.Colors[ImGuiCol_CheckMark]             = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab]            = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(1.00f, 0.48f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_Button]                = ImVec4(0.26f, 0.26f, 0.25f, 1.00f);
    style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.78f, 0.39f, 0.00f, 0.98f);
    style.Colors[ImGuiCol_ButtonActive]          = ImVec4(1.00f, 0.48f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_Header]                = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.57f, 0.30f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_HeaderActive]          = ImVec4(0.78f, 0.39f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_Column]                = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    style.Colors[ImGuiCol_ColumnHovered]         = ImVec4(0.70f, 0.60f, 0.60f, 1.00f);
    style.Colors[ImGuiCol_ColumnActive]          = ImVec4(0.90f, 0.70f, 0.70f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(0.22f, 0.22f, 0.21f, 1.00f);
    style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.78f, 0.39f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(1.00f, 0.48f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_CloseButton]           = ImVec4(0.55f, 0.27f, 0.09f, 1.00f);
    style.Colors[ImGuiCol_CloseButtonHovered]    = ImVec4(0.86f, 0.43f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_CloseButtonActive]     = ImVec4(1.00f, 0.48f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotLines]             = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.00f, 0.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_ModalWindowDarkening]  = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    // Styles
    style.WindowPadding         = ImVec2(10.f, 10.f);
    style.FrameRounding         = 2.f;
    style.WindowRounding        = 4.f;
    style.WindowTitleAlign      = ImVec2(0.5f, 0.5f);
    style.ItemSpacing           = ImVec2(5.f, 5.f);
    style.GrabRounding          = 3.f;
    style.ChildWindowRounding   = 4.f;
}

void GUIManager::DrawMainMenuGui()
{
    if (m_impl->panel_GameMainMenu.IsVisible())
    {
        m_impl->panel_GameMainMenu.Draw();
    }
}

} // namespace RoR
