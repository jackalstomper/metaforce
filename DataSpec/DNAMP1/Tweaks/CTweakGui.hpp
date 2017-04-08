#ifndef _DNAMP1_CTWEAKGUI_HPP_
#define _DNAMP1_CTWEAKGUI_HPP_

#include "../../DNACommon/Tweaks/ITweakGui.hpp"

namespace DataSpec
{
namespace DNAMP1
{
struct CTweakGui : ITweakGui
{
    DECL_YAML
    Value<bool> x4_;
    Value<float> x8_mapAlphaInterp;
    Value<float> xc_;
    Value<float> x10_radarXYRadius;
    Value<float> x14_;
    Value<float> x18_;
    Value<float> x1c_;
    Value<float> x20_;
    Value<float> x24_radarZRadius;
    Value<float> x28_radarZCloseRadius;
    atUint32 x2c_ = 0;
    Value<float> x30_;
    Value<float> x34_energyBarFilledSpeed;
    Value<float> x38_energyBarShadowSpeed;
    Value<float> x3c_energyBarDrainDelay;
    Value<bool> x40_energyBarAlwaysResetDelay;
    Value<float> x44_;
    Value<float> x48_;
    Value<float> x4c_;
    Value<float> x50_;
    Value<float> x54_hudDamageLightSpotAngle;
    Value<float> x58_damageLightAngleC;
    Value<float> x5c_damageLightAngleL;
    Value<float> x60_damageLightAngleQ;
    Value<atVec3f> x64_damageLightPreTranslate;
    Value<atVec3f> x70_damageLightCenterTranslate;
    Value<float> x7c_damageLightXfXAngle;
    Value<float> x80_damageLightXfZAngle;
    Value<float> x84_;
    Value<float> x88_;
    Value<float> x8c_;
    Value<float> x90_;
    Value<float> x94_;
    Value<float> x98_;
    Value<float> x9c_;
    Value<float> xa0_;
    Value<float> xa4_;
    Value<atUint32> xa8_hudCamFovTweak;
    Value<atUint32> xac_hudCamYTweak;
    Value<atUint32> xb0_hudCamZTweak;
    Value<float> xb4_;
    Value<float> xb8_;
    Value<float> xbc_;
    Value<float> xc0_beamVisorMenuAnimTime;
    Value<float> xc4_visorBeamMenuItemActiveScale;
    Value<float> xc8_visorBeamMenuItemInactiveScale;
    Value<float> xcc_visorBeamMenuItemTranslate;
    Value<float> xd0_;
    Value<atUint32> xd4_;
    Value<float> xd8_;
    Value<float> xdc_;
    Value<float> xe0_;
    Value<float> xe4_maxThreatEnergy;
    Value<float> xe8_radarScopeCoordRadius;
    Value<float> xec_radarPlayerPaintRadius;
    Value<float> xf0_radarEnemyPaintRadius;
    Value<float> xf4_missileArrowVisTime;
    Value<EHudVisMode> xf8_hudVisMode;
    Value<EHelmetVisMode> xfc_helmetVisMode;
    Value<atUint32> x100_enableAutoMapper;
    Value<atUint32> x104_;
    Value<atUint32> x108_enableTargetingManager;
    Value<atUint32> x10c_enablePlayerVisor;
    Value<float> x110_threatWarningFraction;
    Value<float> x114_missileWarningFraction;
    Value<float> x118_freeLookFadeTime;
    Value<float> x11c_;
    Value<float> x120_;
    Value<float> x124_;
    Value<float> x128_;
    Value<float> x12c_freeLookSfxPitchScale;
    Value<bool> x130_noAbsoluteFreeLookSfxPitch;
    Value<float> x134_;
    Value<float> x138_;
    Value<atUint32> x13c_;
    Value<atUint32> x140_;
    Value<atUint32> x144_;
    Value<atUint32> x148_;
    Value<atUint32> x14c_;
    String<-1> x150_;
    String<-1> x160_;
    String<-1> x170_;
    String<-1> x180_;
    String<-1> x190_;
    Value<float> x1a0_missileWarningPulseTime;
    Value<float> x1a4_;
    Value<float> x1a8_;
    Value<float> x1ac_;
    Value<float> x1b0_;
    Value<float> x1b4_;
    Value<float> x1b8_;
    Value<float> x1bc_;
    Value<float> x1c0_;
    Value<float> x1c4_;
    Value<float> x1c8_;
    Value<bool> x1cc_;
    Value<bool> x1cd_;
    Value<float> x1d0_;
    Value<float> x1d4_;
    Value<float> x1d8_;
    Value<float> x1dc_;
    Value<float> x1e0_;
    Value<float> x1e4_;
    Value<float> x1e8_;
    Value<float> x1ec_;
    Value<float> x1f0_;
    Value<float> x1f4_;
    Value<float> x1f8_;
    Value<float> x1fc_;
    float x200_;
    float x204_xrayBlurScaleLinear = 0.0014f;
    float x208_xrayBlurScaleQuadratic = 0.0000525f;
    Value<float> x20c_;
    Value<float> x210_scanSidesAngle;
    Value<float> x214_scanSidesXScale;
    Value<float> x218_scanSidesPositionEnd;
    Value<float> x21c_;
    Value<float> x220_scanSidesDuration;
    Value<float> x224_scanSidesStartTime;
    float x228_scanSidesEndTime;
    Value<float> x22c_;
    Value<float> x230_;
    Value<float> x234_;
    Value<float> x238_;
    Value<float> x23c_;
    Value<float> x240_;
    Value<float> x244_scanAppearanceOffset;
    Value<float> x248_;
    Value<float> x24c_;
    Value<float> x250_;
    Value<float> x254_ballViewportYReduction;
    Value<float> x258_;
    Value<float> x25c_;
    Value<float> x260_;
    Value<float> x264_;
    Value<float> x268_;
    Value<float> x26c_;
    Value<float> x270_scanSidesPositionStart;
    Value<bool> x274_;
    bool x275_ = true;
    Value<float> x278_wtMgrCharsPerSfx;
    Value<atUint32> x27c_xrayFogMode;
    Value<float> x280_xrayFogNearZ;
    Value<float> x284_xrayFogFarZ;
    DNAColor x288_xrayFogColor;
    Value<float> x28c_thermalVisorLevel;
    DNAColor x290_thermalVisorColor;
    DNAColor x294_;
    DNAColor x298_;
    DNAColor x29c_;
    DNAColor x2a0_;
    DNAColor x2a4_;
    DNAColor x2a8_;
    DNAColor x2ac_;
    DNAColor x2b0_;
    DNAColor x2b4_;
    Value<float> x2b8_;
    Value<float> x2bc_;
    Value<float> x2c0_;
    Value<atUint32> m_scanSpeedsCount;
    Vector<float, DNA_COUNT(m_scanSpeedsCount)> x2c4_scanSpeeds;
    String<-1> x2d0_;
    String<-1> x2e0_;
    String<-1> x2f0_;
    DNAColor x300_;
    DNAColor x304_;
    Value<float> x308_;
    Value<float> x30c_;
    Value<float> x310_;
    String<-1> x314_;
    String<-1> x324_;
    String<-1> x334_;
    DNAColor x344_;
    DNAColor x348_;
    DNAColor x34c_;
    DNAColor x350_;
    DNAColor x354_;
    DNAColor x358_;
    Value<float> x35c_;
    Value<float> x360_;
    Value<float> x364_;

    CTweakGui() = default;
    CTweakGui(athena::io::IStreamReader& r) { this->read(r); }

    float GetMapAlphaInterpolant() const { return x8_mapAlphaInterp; }
    float GetRadarXYRadius() const { return x10_radarXYRadius; }
    float GetRadarZRadius() const { return x24_radarZRadius; }
    float GetRadarZCloseRadius() const { return x28_radarZCloseRadius; }
    float GetEnergyBarFilledSpeed() const { return x34_energyBarFilledSpeed; }
    float GetEnergyBarShadowSpeed() const { return x38_energyBarShadowSpeed; }
    float GetEnergyBarDrainDelay() const { return x3c_energyBarDrainDelay; }
    bool GetEnergyBarAlwaysResetDelay() const { return x40_energyBarAlwaysResetDelay; }
    float GetHudDamageLightSpotAngle() const { return x54_hudDamageLightSpotAngle; }
    float GetDamageLightAngleC() const { return x58_damageLightAngleC; }
    float GetDamageLightAngleL() const { return x5c_damageLightAngleL; }
    float GetDamageLightAngleQ() const { return x60_damageLightAngleQ; }
    atVec3f GetDamageLightPreTranslate() const { return x64_damageLightPreTranslate; }
    atVec3f GetDamageLightCenterTranslate() const { return x70_damageLightCenterTranslate; }
    float GetDamageLightXfXAngle() const { return x7c_damageLightXfXAngle; }
    float GetDamageLightXfZAngle() const { return x80_damageLightXfZAngle; }
    atUint32 GetHudCamFovTweak() const { return xa8_hudCamFovTweak; }
    atUint32 GetHudCamYTweak() const { return xac_hudCamYTweak; }
    atUint32 GetHudCamZTweak() const { return xb0_hudCamZTweak; }
    float GetBeamVisorMenuAnimTime() const { return xc0_beamVisorMenuAnimTime; }
    float GetVisorBeamMenuItemActiveScale() const { return xc4_visorBeamMenuItemActiveScale; }
    float GetVisorBeamMenuItemInactiveScale() const { return xc8_visorBeamMenuItemInactiveScale; }
    float GetVisorBeamMenuItemTranslate() const { return xcc_visorBeamMenuItemTranslate; }
    float GetMaxThreatEnergy() const { return xe4_maxThreatEnergy; }
    float GetRadarScopeCoordRadius() const { return xe8_radarScopeCoordRadius; }
    float GetRadarPlayerPaintRadius() const { return xec_radarPlayerPaintRadius; }
    float GetRadarEnemyPaintRadius() const { return xf0_radarEnemyPaintRadius; }
    float GetMissileArrowVisTime() const { return xf4_missileArrowVisTime; }
    EHudVisMode GetHudVisMode() const { return xf8_hudVisMode; }
    EHelmetVisMode GetHelmetVisMode() const { return xfc_helmetVisMode; }
    atUint32 GetEnableAutoMapper() const { return x100_enableAutoMapper; }
    atUint32 GetEnableTargetingManager() const { return x108_enableTargetingManager; }
    atUint32 GetEnablePlayerVisor() const { return x10c_enablePlayerVisor; }
    float GetThreatWarningFraction() const { return x110_threatWarningFraction; }
    float GetMissileWarningFraction() const { return x114_missileWarningFraction; }
    float GetFreeLookFadeTime() const { return x118_freeLookFadeTime; }
    float GetFreeLookSfxPitchScale() const { return x12c_freeLookSfxPitchScale; }
    bool GetNoAbsoluteFreeLookSfxPitch() const { return x130_noAbsoluteFreeLookSfxPitch; }
    float GetMissileWarningPulseTime() const { return x1a0_missileWarningPulseTime; }
    float GetScanAppearanceOffset() const { return x244_scanAppearanceOffset; }
    float GetBallViewportYReduction() const { return x254_ballViewportYReduction; }
    float GetXrayBlurScaleLinear() const { return x204_xrayBlurScaleLinear; }
    float GetXrayBlurScaleQuadratic() const { return x208_xrayBlurScaleQuadratic; }
    float GetScanSidesAngle() const { return x210_scanSidesAngle; }
    float GetScanSidesXScale() const { return x214_scanSidesXScale; }
    float GetScanSidesPositionEnd() const { return x218_scanSidesPositionEnd; }
    float GetScanSidesDuration() const { return x220_scanSidesDuration; }
    float GetScanSidesStartTime() const { return x224_scanSidesStartTime; }
    float GetScanSidesEndTime() const { return x228_scanSidesEndTime; }
    float GetScanSidesPositionStart() const { return x270_scanSidesPositionStart; }
    float GetWorldTransManagerCharsPerSfx() const { return x278_wtMgrCharsPerSfx; }
    atUint32 GetXRayFogMode() const { return x27c_xrayFogMode; }
    float GetXRayFogNearZ() const { return x280_xrayFogNearZ; }
    float GetXRayFogFarZ() const { return x284_xrayFogFarZ; }
    const zeus::CColor& GetXRayFogColor() const { return x288_xrayFogColor; }
    float GetThermalVisorLevel() const { return x28c_thermalVisorLevel; }
    const zeus::CColor& GetThermalVisorColor() const { return x290_thermalVisorColor; }

    float GetScanSpeed(int idx) const
    {
        if (idx < 0 || idx >= x2c4_scanSpeeds.size())
            return 0.f;
        return x2c4_scanSpeeds[idx];
    }

    void FixupValues()
    {
        xd8_ = zeus::degToRad(xd8_);
        xdc_ = zeus::degToRad(xdc_);

        x200_ = x1f4_ * 0.25f;
        x204_xrayBlurScaleLinear = x1f8_ * 0.25f;
        x208_xrayBlurScaleQuadratic = x1fc_ * 0.25f;

        x210_scanSidesAngle = zeus::degToRad(x210_scanSidesAngle);
        x228_scanSidesEndTime = x220_scanSidesDuration + x224_scanSidesStartTime;

        if (x27c_xrayFogMode == 1)
            x27c_xrayFogMode = 2;
        else if (x27c_xrayFogMode == 2)
            x27c_xrayFogMode = 4;
        else if (x27c_xrayFogMode == 3)
            x27c_xrayFogMode = 5;
        else
            x27c_xrayFogMode = 0;

        x84_ *= 2.0f;
    }
};

}
}

#endif // _DNAMP1_CTWEAKGUI_HPP_
