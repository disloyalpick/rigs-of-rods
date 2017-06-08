/*
	This source file is part of Rigs of Rods
	Copyright 2013-2017 Petr Ohlidal

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


/// @file   Application.h
/// @author Petr Ohlidal
/// @date   05/2014
/// @brief  Central state/object manager and communications hub.

#pragma once

#include "RoRPrerequisites.h"
#include "Settings.h"

namespace RoR {
namespace App {

enum State
{
    APP_STATE_NONE,               ///< Only valid for GVar 'app_state_pending'. Means no change is requested.
    APP_STATE_BOOTSTRAP,          ///< Initial state
    APP_STATE_MAIN_MENU,
    APP_STATE_CHANGE_MAP,         ///< Enter main menu & immediatelly launch singleplayer map selector.
    APP_STATE_SIMULATION,
    APP_STATE_SHUTDOWN,
    APP_STATE_PRINT_HELP_EXIT,
    APP_STATE_PRINT_VERSION_EXIT,
};

enum MpState
{
    MP_STATE_NONE,      ///< Only valid for GVar 'app_state_pending'. Means no change is requested.
    MP_STATE_DISABLED,  ///< Not connected for whatever reason.
    MP_STATE_CONNECTED,
};

enum SimState
{
    SIM_STATE_NONE,
    SIM_STATE_RUNNING,
    SIM_STATE_PAUSED,
    SIM_STATE_SELECTING,  ///< The selector GUI window is displayed.
    SIM_STATE_EDITOR_MODE ///< Hacky, but whatever... added by Ulteq, 2016
};

enum SimGearboxMode
{
    SIM_GEARBOX_AUTO,          ///< Automatic shift
    SIM_GEARBOX_SEMI_AUTO,     ///< Manual shift - Auto clutch
    SIM_GEARBOX_MANUAL,        ///< Fully Manual: sequential shift
    SIM_GEARBOX_MANUAL_STICK,  ///< Fully manual: stick shift
    SIM_GEARBOX_MANUAL_RANGES, ///< Fully Manual: stick shift with ranges
};

enum GfxShadowType
{
    GFX_SHADOW_TYPE_NONE,
    GFX_SHADOW_TYPE_TEXTURE,
    GFX_SHADOW_TYPE_PSSM
};

enum GfxExtCamMode
{
    GFX_EXTCAM_MODE_NONE,
    GFX_EXTCAM_MODE_STATIC,
    GFX_EXTCAM_MODE_PITCHING,
};

enum GfxTexFilter
{
    GFX_TEXFILTER_NONE,
    GFX_TEXFILTER_BILINEAR,
    GFX_TEXFILTER_TRILINEAR,
    GFX_TEXFILTER_ANISOTROPIC,
};

enum GfxVegetation
{
    GFX_VEGETATION_NONE,
    GFX_VEGETATION_20PERC,
    GFX_VEGETATION_50PERC,
    GFX_VEGETATION_FULL,
};

enum GfxFlaresMode
{
    GFX_FLARES_NONE,                    ///< None (fastest)
    GFX_FLARES_NO_LIGHTSOURCES,         ///< No light sources
    GFX_FLARES_CURR_VEHICLE_HEAD_ONLY,  ///< Only current vehicle, main lights
    GFX_FLARES_ALL_VEHICLES_HEAD_ONLY,  ///< All vehicles, main lights
    GFX_FLARES_ALL_VEHICLES_ALL_LIGHTS, ///< All vehicles, all lights
};

enum GfxWaterMode
{
    GFX_WATER_NONE,       ///< None
    GFX_WATER_BASIC,      ///< Basic (fastest)
    GFX_WATER_REFLECT,    ///< Reflection
    GFX_WATER_FULL_FAST,  ///< Reflection + refraction (speed optimized)
    GFX_WATER_FULL_HQ,    ///< Reflection + refraction (quality optimized)
    GFX_WATER_HYDRAX,     ///< HydraX
};

enum GfxSkyMode
{
    GFX_SKY_SANDSTORM,  ///< Sandstorm (fastest)
    GFX_SKY_CAELUM,     ///< Caelum (best looking, slower)
    GFX_SKY_SKYX,       ///< SkyX (best looking, slower)
};

enum IoInputGrabMode
{
    INPUT_GRAB_NONE,
    INPUT_GRAB_ALL,
    INPUT_GRAB_DYNAMIC,
};

void Init();

// Getters
OgreSubsystem*       GetOgreSubsystem();
Settings&            GetSettings();
ContentManager*      GetContentManager();
OverlayWrapper*      GetOverlayWrapper();
SceneMouse*          GetSceneMouse();
GUIManager*          GetGuiManager();
Console*             GetConsole();
InputEngine*         GetInputEngine();
CacheSystem*         GetCacheSystem();
MainMenu*            GetMainMenu();
RoRFrameListener*    GetSimController();

State                GetActiveAppState       ();
State                GetPendingAppState      ();
std::string const &  GetSimActiveTerrain     ();
std::string const &  GetSimNextTerrain       ();
MpState              GetActiveMpState        ();
MpState              GetPendingMpState       ();
SimState             GetActiveSimState       ();
SimState             GetPendingSimState      ();
std::string const &  GetMpServerHost         ();
std::string const &  GetMpServerPassword     ();
int                  GetMpServerPort         ();
std::string const &  GetMpPlayerName         ();
std::string const &  GetMpPortalUrl          ();
bool                 GetDiagTraceGlobals     ();
std::string const &  GetSysProcessDir        ();
std::string const &  GetSysUserDir           ();
std::string const &  GetSysConfigDir         ();
std::string const &  GetSysCacheDir          ();
std::string const &  GetSysLogsDir           ();
std::string const &  GetSysResourcesDir      ();
bool                 GetIoFFbackEnabled      ();
float                GetIoFFbackCameraGain   ();
float                GetIoFFbackCenterGain   ();
float                GetIoFFbackMasterGain   ();
float                GetIoFFbackStressGain   ();
GfxShadowType        GetGfxShadowType        ();
GfxExtCamMode        GetGfxExternCamMode     ();
GfxTexFilter         GetGfxTexFiltering      ();
GfxVegetation        GetGfxVegetationMode    ();
bool                 GetGfxEnableSunburn     ();
bool                 GetGfxWaterUseWaves     ();
int                  GetGfxParticlesMode     ();
bool                 GetGfxEnableGlow        ();
bool                 GetGfxEnableHdr         ();
bool                 GetGfxEnableVideocams   ();
bool                 GetGfxUseHeathaze       ();
bool                 GetGfxEnvmapEnabled     ();
int                  GetGfxEnvmapRate        ();
int                  GetGfxSkidmarksMode     ();
bool                 GetGfxMinimapDisabled   ();
bool                 GetDiagRigLogNodeImport ();
bool                 GetDiagRigLogNodeStats  ();
bool                 GetDiagRigLogMessages   ();
bool                 GetDiagCollisions       ();
bool                 GetDiagTruckMass        ();
bool                 GetDiagEnvmap           ();
std::string const &  GetAppLanguage          ();
std::string const &  GetAppLocale            ();
bool                 GetAppMultithread       ();
std::string const &  GetAppScreenshotFormat  ();
IoInputGrabMode      GetIoInputGrabMode      ();
bool                 GetIoArcadeControls     ();
float                GetAudioMasterVolume    ();
bool                 GetAudioEnableCreak     ();
std::string const &  GetAudioDeviceName      ();
bool                 GetAudioMenuMusic       ();
bool                 GetSimReplayEnabled     ();
int                  GetSimReplayLength      ();
int                  GetSimReplayStepping    ();
bool                 GetSimPositionStorage   ();
SimGearboxMode       GetSimGearboxMode       ();
GfxFlaresMode        GetGfxFlaresMode        ();
std::string const &  GetSysScreenshotDir     ();
int                  GetIoOutGaugeMode       ();
std::string const &  GetIoOutGaugeIp         ();
int                  GetIoOutGaugePort       ();
float                GetIoOutGaugeDelay      ();
int                  GetIoOutGaugeId         ();
GfxSkyMode           GetGfxSkyMode           ();
GfxWaterMode         GetGfxWaterMode         ();
float                GetGfxSightRange        ();
float                GetGfxFovExternal       ();
float                GetGfxFovInternal       ();
int                  GetGfxFpsLimit          ();
bool                 GetDiagVideoCameras     ();
std::string const &  GetDiagPreselectedTerrain  ();
std::string const &  GetDiagPreselectedVehicle  ();
std::string const &  GetDiagPreselectedVehConfig();
bool                 GetDiagPreselectedVehEnter ();


// Setters
void SetActiveAppState       (State               v);
void SetPendingAppState      (State               v);
void SetSimActiveTerrain     (std::string const & v);
void SetSimNextTerrain       (std::string const & v);
void SetActiveMpState        (MpState             v);
void SetPendingMpState       (MpState             v);
void SetActiveSimState       (SimState            v);
void SetPendingSimState      (SimState            v);
void SetMpServerHost         (std::string const & v);
void SetMpServerPassword     (std::string const & v);
void SetMpServerPort         (int                 v);
void SetMpPlayerName         (std::string const & v);
void SetMpPortalUrl          (std::string const & v);
void SetDiagTraceGlobals     (bool                v);
void SetSysProcessDir        (std::string const & v);
void SetSysUserDir           (std::string const & v);
void SetSysConfigDir         (std::string const & v);
void SetSysCacheDir          (std::string const & v);
void SetSysLogsDir           (std::string const & v);
void SetSysResourcesDir      (std::string const & v);
void SetIoFFbackEnabled      (bool                v);
void SetIoFFbackCameraGain   (float               v);
void SetIoFFbackCenterGain   (float               v);
void SetIoFFbackMasterGain   (float               v);
void SetIoFFbackStressGain   (float               v);
void SetGfxShadowType        (GfxShadowType       v);
void SetGfxExternCamMode     (GfxExtCamMode       v);
void SetGfxTexFiltering      (GfxTexFilter        v);
void SetGfxVegetationMode    (GfxVegetation       v);
void SetGfxEnableSunburn     (bool                v);
void SetGfxWaterUseWaves     (bool                v);
void SetGfxEnableGlow        (bool                v);
void SetGfxEnableHdr         (bool                v);
void SetGfxEnableVideocams   (bool                v);
void SetGfxUseHeathaze       (bool                v);
void SetGfxEnvmapEnabled     (bool                v);
void SetGfxEnvmapRate        (int                 v);
void SetGfxSkidmarksMode     (int                 v);
void SetGfxParticlesMode     (int                 v);
void SetGfxMinimapDisabled   (bool                v);
void SetDiagRigLogNodeImport (bool                v);
void SetDiagRigLogNodeStats  (bool                v);
void SetDiagRigLogMessages   (bool                v);
void SetDiagCollisions       (bool                v);
void SetDiagTruckMass        (bool                v);
void SetDiagEnvmap           (bool                v);
void SetAppLanguage          (std::string const & v);
void SetAppLocale            (std::string const & v);
void SetAppMultithread       (bool                v);
void SetAppScreenshotFormat  (std::string const & v);
void SetIoInputGrabMode      (IoInputGrabMode     v);
void SetIoArcadeControls     (bool                v);
void SetAudioMasterVolume    (float               v);
void SetAudioEnableCreak     (bool                v);
void SetAudioDeviceName      (std::string const & v);
void SetAudioMenuMusic       (bool                v);
void SetSimReplayEnabled     (bool                v);
void SetSimReplayLength      (int                 v);
void SetSimReplayStepping    (int                 v);
void SetSimPositionStorage   (bool                v);
void SetSimGearboxMode       (SimGearboxMode      v);
void SetGfxFlaresMode        (GfxFlaresMode       v);
void SetSysScreenshotDir     (std::string const & v);
void SetIoOutGaugeMode       (int                 v);
void SetIoOutGaugeIp         (std::string const & v);
void SetIoOutGaugePort       (int                 v);
void SetIoOutGaugeDelay      (float               v);
void SetIoOutGaugeId         (int                 v);
void SetGfxSkyMode           (GfxSkyMode          v);
void SetGfxWaterMode         (GfxWaterMode        v);
void SetGfxSightRange        (float               v);
void SetGfxFovExternal       (float               v);
void SetGfxFovInternal       (float               v);
void SetGfxFpsLimit          (int                 v);
void SetDiagVideoCameras     (bool                v);
void SetDiagPreselectedTerrain  (std::string const & v);
void SetDiagPreselectedVehicle  (std::string const & v);
void SetDiagPreselectedVehConfig(std::string const & v);
void SetDiagPreselectedVehEnter (bool                v);

void SetMainMenu             (MainMenu*          obj);
void SetSimController        (RoRFrameListener*  obj);

// Factories
void StartOgreSubsystem();
void ShutdownOgreSubsystem();
void CreateContentManager();
void DestroyContentManager();
void CreateOverlayWrapper();
void DestroyOverlayWrapper();
void CreateSceneMouse();
void DeleteSceneMouse();
void CreateGuiManagerIfNotExists();
void DeleteGuiManagerIfExists();
void CreateInputEngine();
void CreateCacheSystem();

} // namespace Application
} // namespace RoR
