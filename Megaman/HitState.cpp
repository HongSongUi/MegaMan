#include "HitState.h"
#include "JumpState.h"
#include "IdleState.h"
#include "DeathState.h"
#include "WinState.h"
#include "Player.h"
void HitState::Enter()
{
	HitTimer = 0.25f;
	Tag = HIT;
	Owner->SetAnimation(Owner->FindSprite(L"HurtC.txt"));
	Owner->SetHitStartEvent();
	Owner->SetPlaySound(L"ROCK_X5_00142.wav");
	if (Owner->GetIsCharge())
	{
		Owner->ResetChargeState();
	}
}

void HitState::Update()
{
	if (Owner->IsPlayerDeath())
	{
		Owner->ChangeState(new DeathState);
		return;
	}
	if (Owner->GetPlayerWin())
	{
		Owner->ChangeState(new WinState);
		return;
	}
	Owner->PlayAnimation();
	HitTimer -= gSecondPerFrame;
	if (HitTimer < 0.f)
	{
		//StateTag Prev = Owner->GetPrevState();
		if (Owner->GetIsGround() == false)
		{
			Owner->ChangeState(new JumpState());
			return;
		}
		else
		{
			Owner->ChangeState(new IdleState);
		}
	}
}

void HitState::Exit()
{
	Owner->ResetAnimIndex();
	Owner->HitEndEvent();
}
