#include "AirDashState.h"
#include "JumpState.h"
#include "Player.h"
#include "HitState.h"
#include "WinState.h"
#include "Input.h"
void AirDashState::Enter()
{
	Owner->SetAnimation(Owner->FindSprite(L"Dash.txt"));
	Tag = AIRDASH;
	DashTime = 0.55f;
	Owner->SetPlaySound(L"ROCK_X5_00126.wav");
}

void AirDashState::Update()
{
	if (Owner->IsPlayerHit())
	{
		if (Owner->IsPlayerCanHit())
		{
			Owner->ChangeState(new HitState);
			return;
		}
	}
	if (Owner->GetPlayerWin())
	{
		Owner->ChangeState(new WinState);
		return;
	}
	Owner->PlayAnimation();
	Owner->PlayDashEffect();
	DashTime -= gSecondPerFrame;
	if (!Owner->GetLeftWallState() && !Owner->GetRightWallState())
	{
		Owner->PlayerDash(500.f);
	}

	if (DashTime < 0.f)
	{
		Owner->ChangeState(new JumpState);
		return;
	}

	if (GameInput.GetKey('X') == KEY_PUSH)
	{
		WaitTime = 0.f;
		Owner->ResetChargeState();
		Owner->SetAnimation(Owner->FindSprite(L"ShootDash.txt"));
		Owner->SpawnBullet();
	}
	else if (GameInput.GetKey('X') == KEY_HOLD)
	{
		Owner->UpdateChargingState();
		if (Owner->GetIsCharge()) 
		{
			Owner->SetAnimation(Owner->FindSprite(L"Dash.txt"));
		}
	}
	else if (GameInput.GetKey('X') == KEY_FREE)
	{

		if (Owner->GetIsCharge())
		{
			Owner->SetAnimation(Owner->FindSprite(L"ShootDash.txt"));
			Owner->SpawnBullet();
			Owner->ResetChargeState();
		}
		else
		{
			WaitTime += gSecondPerFrame;
			if (WaitTime > 0.8f)
			{
				Owner->SetAnimation(Owner->FindSprite(L"Dash.txt"));
			}
		}
	}
}

void AirDashState::Exit()
{
	Owner->SetFallingAnim(); 
	Owner->DashEndEvent();
	Owner = nullptr;
}
