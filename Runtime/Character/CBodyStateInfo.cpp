#include "Runtime/Character/CBodyStateInfo.hpp"

#include "Runtime/Character/CBodyController.hpp"
#include "Runtime/World/CActor.hpp"

namespace urde {

CBodyStateInfo::CBodyStateInfo(CActor& actor, EBodyType type) {
  x34_24_changeLocoAtEndOfAnimOnly = false;
  const CPASDatabase& pasDatabase = actor.GetModelData()->GetAnimationData()->GetCharacterInfo().GetPASDatabase();
  for (size_t i = 0; i < pasDatabase.GetNumAnimStates(); ++i) {
    const CPASAnimState* state = pasDatabase.GetAnimStateByIndex(i);
    std::unique_ptr<CBodyState> bs;

    switch (type) {
    case EBodyType::BiPedal:
      bs = SetupBiPedalBodyStates(state->GetStateId(), actor);
      break;
    case EBodyType::Restricted:
    default:
      bs = SetupRestrictedBodyStates(state->GetStateId(), actor);
      break;
    case EBodyType::Flyer:
      bs = SetupFlyerBodyStates(state->GetStateId(), actor);
      break;
    case EBodyType::Pitchable:
      bs = SetupPitchableBodyStates(state->GetStateId(), actor);
      break;
    case EBodyType::WallWalker:
      bs = SetupWallWalkerBodyStates(state->GetStateId(), actor);
      break;
    case EBodyType::NewFlyer:
      bs = SetupNewFlyerBodyStates(state->GetStateId(), actor);
      break;
    case EBodyType::RestrictedFlyer:
      bs = SetupRestrictedFlyerBodyStates(state->GetStateId(), actor);
      break;
    }

    if (bs)
      x0_stateMap[pas::EAnimationState(state->GetStateId())] = std::move(bs);
  }

  x1c_additiveStates.reserve(4);
  x1c_additiveStates.emplace_back(pas::EAnimationState::AdditiveIdle, std::make_unique<CABSIdle>());
  x1c_additiveStates.emplace_back(pas::EAnimationState::AdditiveAim, std::make_unique<CABSAim>());
  x1c_additiveStates.emplace_back(pas::EAnimationState::AdditiveFlinch, std::make_unique<CABSFlinch>());
  x1c_additiveStates.emplace_back(pas::EAnimationState::AdditiveReaction, std::make_unique<CABSReaction>());
}

std::unique_ptr<CBodyState> CBodyStateInfo::SetupRestrictedFlyerBodyStates(pas::EAnimationState stateId, CActor& actor) const {
  switch (stateId) {
  case pas::EAnimationState::Fall:
    return std::make_unique<CBSFall>();
  case pas::EAnimationState::Getup:
    return std::make_unique<CBSGetup>();
  case pas::EAnimationState::LieOnGround:
    return std::make_unique<CBSLieOnGround>(actor);
  case pas::EAnimationState::Step:
    return std::make_unique<CBSStep>();
  case pas::EAnimationState::Death:
    return std::make_unique<CBSDie>();
  case pas::EAnimationState::Locomotion:
    return std::make_unique<CBSRestrictedFlyerLocomotion>(actor);
  case pas::EAnimationState::KnockBack:
    return std::make_unique<CBSKnockBack>();
  case pas::EAnimationState::MeleeAttack:
    return std::make_unique<CBSAttack>();
  case pas::EAnimationState::ProjectileAttack:
    return std::make_unique<CBSProjectileAttack>();
  case pas::EAnimationState::LoopAttack:
    return std::make_unique<CBSLoopAttack>();
  case pas::EAnimationState::Turn:
    return std::make_unique<CBSTurn>();
  case pas::EAnimationState::LoopReaction:
    return std::make_unique<CBSLoopReaction>();
  case pas::EAnimationState::GroundHit:
    return std::make_unique<CBSGroundHit>();
  case pas::EAnimationState::Generate:
    return std::make_unique<CBSGenerate>();
  case pas::EAnimationState::Jump:
    return std::make_unique<CBSJump>();
  case pas::EAnimationState::Hurled:
    return std::make_unique<CBSHurled>();
  case pas::EAnimationState::Slide:
    return std::make_unique<CBSSlide>();
  case pas::EAnimationState::Taunt:
    return std::make_unique<CBSTaunt>();
  case pas::EAnimationState::Scripted:
    return std::make_unique<CBSScripted>();
  default:
    return {};
  }
}

std::unique_ptr<CBodyState> CBodyStateInfo::SetupNewFlyerBodyStates(pas::EAnimationState stateId, CActor& actor) const {
  switch (stateId) {
  case pas::EAnimationState::Fall:
    return std::make_unique<CBSFall>();
  case pas::EAnimationState::Getup:
    return std::make_unique<CBSGetup>();
  case pas::EAnimationState::LieOnGround:
    return std::make_unique<CBSLieOnGround>(actor);
  case pas::EAnimationState::Step:
    return std::make_unique<CBSStep>();
  case pas::EAnimationState::Death:
    return std::make_unique<CBSDie>();
  case pas::EAnimationState::Locomotion:
    return std::make_unique<CBSNewFlyerLocomotion>(actor);
  case pas::EAnimationState::KnockBack:
    return std::make_unique<CBSKnockBack>();
  case pas::EAnimationState::MeleeAttack:
    return std::make_unique<CBSAttack>();
  case pas::EAnimationState::ProjectileAttack:
    return std::make_unique<CBSProjectileAttack>();
  case pas::EAnimationState::LoopAttack:
    return std::make_unique<CBSLoopAttack>();
  case pas::EAnimationState::Turn:
    return std::make_unique<CBSTurn>();
  case pas::EAnimationState::LoopReaction:
    return std::make_unique<CBSLoopReaction>();
  case pas::EAnimationState::GroundHit:
    return std::make_unique<CBSGroundHit>();
  case pas::EAnimationState::Generate:
    return std::make_unique<CBSGenerate>();
  case pas::EAnimationState::Jump:
    return std::make_unique<CBSJump>();
  case pas::EAnimationState::Hurled:
    return std::make_unique<CBSHurled>();
  case pas::EAnimationState::Slide:
    return std::make_unique<CBSSlide>();
  case pas::EAnimationState::Taunt:
    return std::make_unique<CBSTaunt>();
  case pas::EAnimationState::Scripted:
    return std::make_unique<CBSScripted>();
  default:
    return {};
  }
}

std::unique_ptr<CBodyState> CBodyStateInfo::SetupWallWalkerBodyStates(pas::EAnimationState stateId, CActor& actor) const {
  switch (stateId) {
  case pas::EAnimationState::Fall:
    return std::make_unique<CBSFall>();
  case pas::EAnimationState::Getup:
    return std::make_unique<CBSGetup>();
  case pas::EAnimationState::LieOnGround:
    return std::make_unique<CBSLieOnGround>(actor);
  case pas::EAnimationState::Step:
    return std::make_unique<CBSStep>();
  case pas::EAnimationState::Death:
    return std::make_unique<CBSDie>();
  case pas::EAnimationState::Locomotion:
    return std::make_unique<CBSWallWalkerLocomotion>(actor);
  case pas::EAnimationState::KnockBack:
    return std::make_unique<CBSKnockBack>();
  case pas::EAnimationState::MeleeAttack:
    return std::make_unique<CBSAttack>();
  case pas::EAnimationState::ProjectileAttack:
    return std::make_unique<CBSProjectileAttack>();
  case pas::EAnimationState::LoopAttack:
    return std::make_unique<CBSLoopAttack>();
  case pas::EAnimationState::Turn:
    return std::make_unique<CBSFlyerTurn>();
  case pas::EAnimationState::LoopReaction:
    return std::make_unique<CBSLoopReaction>();
  case pas::EAnimationState::GroundHit:
    return std::make_unique<CBSGroundHit>();
  case pas::EAnimationState::Generate:
    return std::make_unique<CBSGenerate>();
  case pas::EAnimationState::Jump:
    return std::make_unique<CBSJump>();
  case pas::EAnimationState::Hurled:
    return std::make_unique<CBSHurled>();
  case pas::EAnimationState::Slide:
    return std::make_unique<CBSSlide>();
  case pas::EAnimationState::Taunt:
    return std::make_unique<CBSTaunt>();
  case pas::EAnimationState::Scripted:
    return std::make_unique<CBSScripted>();
  default:
    return {};
  }
}

std::unique_ptr<CBodyState> CBodyStateInfo::SetupPitchableBodyStates(pas::EAnimationState stateId, CActor& actor) const {
  switch (stateId) {
  case pas::EAnimationState::Fall:
    return std::make_unique<CBSFall>();
  case pas::EAnimationState::Getup:
    return std::make_unique<CBSGetup>();
  case pas::EAnimationState::LieOnGround:
    return std::make_unique<CBSLieOnGround>(actor);
  case pas::EAnimationState::Step:
    return std::make_unique<CBSStep>();
  case pas::EAnimationState::Death:
    return std::make_unique<CBSDie>();
  case pas::EAnimationState::Locomotion:
    return std::make_unique<CBSFlyerLocomotion>(actor, true);
  case pas::EAnimationState::KnockBack:
    return std::make_unique<CBSKnockBack>();
  case pas::EAnimationState::MeleeAttack:
    return std::make_unique<CBSAttack>();
  case pas::EAnimationState::ProjectileAttack:
    return std::make_unique<CBSProjectileAttack>();
  case pas::EAnimationState::LoopAttack:
    return std::make_unique<CBSLoopAttack>();
  case pas::EAnimationState::Turn:
    return std::make_unique<CBSFlyerTurn>();
  case pas::EAnimationState::LoopReaction:
    return std::make_unique<CBSLoopReaction>();
  case pas::EAnimationState::GroundHit:
    return std::make_unique<CBSGroundHit>();
  case pas::EAnimationState::Generate:
    return std::make_unique<CBSGenerate>();
  case pas::EAnimationState::Jump:
    return std::make_unique<CBSJump>();
  case pas::EAnimationState::Hurled:
    return std::make_unique<CBSHurled>();
  case pas::EAnimationState::Slide:
    return std::make_unique<CBSSlide>();
  case pas::EAnimationState::Taunt:
    return std::make_unique<CBSTaunt>();
  case pas::EAnimationState::Scripted:
    return std::make_unique<CBSScripted>();
  default:
    return {};
  }
}

std::unique_ptr<CBodyState> CBodyStateInfo::SetupFlyerBodyStates(pas::EAnimationState stateId, CActor& actor) const {
  switch (stateId) {
  case pas::EAnimationState::Fall:
    return std::make_unique<CBSFall>();
  case pas::EAnimationState::Getup:
    return std::make_unique<CBSGetup>();
  case pas::EAnimationState::LieOnGround:
    return std::make_unique<CBSLieOnGround>(actor);
  case pas::EAnimationState::Step:
    return std::make_unique<CBSStep>();
  case pas::EAnimationState::Death:
    return std::make_unique<CBSDie>();
  case pas::EAnimationState::Locomotion:
    return std::make_unique<CBSFlyerLocomotion>(actor, false);
  case pas::EAnimationState::KnockBack:
    return std::make_unique<CBSKnockBack>();
  case pas::EAnimationState::MeleeAttack:
    return std::make_unique<CBSAttack>();
  case pas::EAnimationState::ProjectileAttack:
    return std::make_unique<CBSProjectileAttack>();
  case pas::EAnimationState::LoopAttack:
    return std::make_unique<CBSLoopAttack>();
  case pas::EAnimationState::Turn:
    return std::make_unique<CBSFlyerTurn>();
  case pas::EAnimationState::LoopReaction:
    return std::make_unique<CBSLoopReaction>();
  case pas::EAnimationState::GroundHit:
    return std::make_unique<CBSGroundHit>();
  case pas::EAnimationState::Generate:
    return std::make_unique<CBSGenerate>();
  case pas::EAnimationState::Jump:
    return std::make_unique<CBSJump>();
  case pas::EAnimationState::Hurled:
    return std::make_unique<CBSHurled>();
  case pas::EAnimationState::Slide:
    return std::make_unique<CBSSlide>();
  case pas::EAnimationState::Taunt:
    return std::make_unique<CBSTaunt>();
  case pas::EAnimationState::Scripted:
    return std::make_unique<CBSScripted>();
  default:
    return {};
  }
}

std::unique_ptr<CBodyState> CBodyStateInfo::SetupRestrictedBodyStates(pas::EAnimationState stateId, CActor& actor) const {
  switch (stateId) {
  case pas::EAnimationState::Fall:
    return std::make_unique<CBSFall>();
  case pas::EAnimationState::Getup:
    return std::make_unique<CBSGetup>();
  case pas::EAnimationState::LieOnGround:
    return std::make_unique<CBSLieOnGround>(actor);
  case pas::EAnimationState::Step:
    return std::make_unique<CBSStep>();
  case pas::EAnimationState::Death:
    return std::make_unique<CBSDie>();
  case pas::EAnimationState::Locomotion:
    return std::make_unique<CBSRestrictedLocomotion>(actor);
  case pas::EAnimationState::KnockBack:
    return std::make_unique<CBSKnockBack>();
  case pas::EAnimationState::MeleeAttack:
    return std::make_unique<CBSAttack>();
  case pas::EAnimationState::ProjectileAttack:
    return std::make_unique<CBSProjectileAttack>();
  case pas::EAnimationState::LoopAttack:
    return std::make_unique<CBSLoopAttack>();
  case pas::EAnimationState::Turn:
    return std::make_unique<CBSTurn>();
  case pas::EAnimationState::LoopReaction:
    return std::make_unique<CBSLoopReaction>();
  case pas::EAnimationState::GroundHit:
    return std::make_unique<CBSGroundHit>();
  case pas::EAnimationState::Generate:
    return std::make_unique<CBSGenerate>();
  case pas::EAnimationState::Jump:
    return std::make_unique<CBSJump>();
  case pas::EAnimationState::Hurled:
    return std::make_unique<CBSHurled>();
  case pas::EAnimationState::Slide:
    return std::make_unique<CBSSlide>();
  case pas::EAnimationState::Taunt:
    return std::make_unique<CBSTaunt>();
  case pas::EAnimationState::Scripted:
    return std::make_unique<CBSScripted>();
  case pas::EAnimationState::Cover:
    return std::make_unique<CBSCover>();
  default:
    return {};
  }
}

std::unique_ptr<CBodyState> CBodyStateInfo::SetupBiPedalBodyStates(pas::EAnimationState stateId, CActor& actor) const {
  switch (stateId) {
  case pas::EAnimationState::Fall:
    return std::make_unique<CBSFall>();
  case pas::EAnimationState::Getup:
    return std::make_unique<CBSGetup>();
  case pas::EAnimationState::LieOnGround:
    return std::make_unique<CBSLieOnGround>(actor);
  case pas::EAnimationState::Step:
    return std::make_unique<CBSStep>();
  case pas::EAnimationState::Death:
    return std::make_unique<CBSDie>();
  case pas::EAnimationState::Locomotion:
    return std::make_unique<CBSBiPedLocomotion>(actor);
  case pas::EAnimationState::KnockBack:
    return std::make_unique<CBSKnockBack>();
  case pas::EAnimationState::MeleeAttack:
    return std::make_unique<CBSAttack>();
  case pas::EAnimationState::ProjectileAttack:
    return std::make_unique<CBSProjectileAttack>();
  case pas::EAnimationState::LoopAttack:
    return std::make_unique<CBSLoopAttack>();
  case pas::EAnimationState::Turn:
    return std::make_unique<CBSTurn>();
  case pas::EAnimationState::LoopReaction:
    return std::make_unique<CBSLoopReaction>();
  case pas::EAnimationState::GroundHit:
    return std::make_unique<CBSGroundHit>();
  case pas::EAnimationState::Generate:
    return std::make_unique<CBSGenerate>();
  case pas::EAnimationState::Jump:
    return std::make_unique<CBSJump>();
  case pas::EAnimationState::Hurled:
    return std::make_unique<CBSHurled>();
  case pas::EAnimationState::Slide:
    return std::make_unique<CBSSlide>();
  case pas::EAnimationState::Taunt:
    return std::make_unique<CBSTaunt>();
  case pas::EAnimationState::Scripted:
    return std::make_unique<CBSScripted>();
  case pas::EAnimationState::Cover:
    return std::make_unique<CBSCover>();
  case pas::EAnimationState::WallHang:
    return std::make_unique<CBSWallHang>();
  default:
    return {};
  }
}

float CBodyStateInfo::GetLocomotionSpeed(pas::ELocomotionAnim anim) const {
  auto search = x0_stateMap.find(pas::EAnimationState::Locomotion);
  if (search != x0_stateMap.cend() && search->second && x18_bodyController) {
    const CBSLocomotion& bs = static_cast<const CBSLocomotion&>(*search->second);
    return bs.GetLocomotionSpeed(x18_bodyController->GetLocomotionType(), anim);
  }
  return 0.f;
}

float CBodyStateInfo::GetMaxSpeed() const {
  float ret = GetLocomotionSpeed(pas::ELocomotionAnim::Run);
  if (std::fabs(ret) < 0.00001f) {
    for (int i = 0; i < 8; ++i) {
      float tmp = GetLocomotionSpeed(pas::ELocomotionAnim(i));
      if (tmp > ret)
        ret = tmp;
    }
  }
  return ret;
}

CBodyState* CBodyStateInfo::GetCurrentState() {
  auto search = x0_stateMap.find(x14_state);
  if (search == x0_stateMap.end())
    return nullptr;
  return search->second.get();
}

const CBodyState* CBodyStateInfo::GetCurrentState() const {
  auto search = x0_stateMap.find(x14_state);
  if (search == x0_stateMap.end())
    return nullptr;
  return search->second.get();
}

void CBodyStateInfo::SetState(pas::EAnimationState s) {
  auto search = x0_stateMap.find(s);
  if (search == x0_stateMap.end())
    return;
  x14_state = s;
}

CAdditiveBodyState* CBodyStateInfo::GetCurrentAdditiveState() {
  for (auto& state : x1c_additiveStates) {
    if (x2c_additiveState == state.first)
      return state.second.get();
  }
  return nullptr;
}

void CBodyStateInfo::SetAdditiveState(pas::EAnimationState s) {
  for (auto& state : x1c_additiveStates) {
    if (s == state.first) {
      x2c_additiveState = s;
      return;
    }
  }
}

bool CBodyStateInfo::ApplyHeadTracking() const {
  if (x14_state == pas::EAnimationState::Invalid)
    return false;
  return GetCurrentState()->ApplyHeadTracking();
}

} // namespace urde
