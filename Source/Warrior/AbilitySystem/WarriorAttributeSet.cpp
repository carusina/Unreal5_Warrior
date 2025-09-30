// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WarriorAttributeSet.h"
#include "GameplayEffectExtension.h"

#include "WarriorDebugHelper.h"

UWarriorAttributeSet::UWarriorAttributeSet()
{
	InitCurrentHealth(1.0f);
	InitMaxHealth(1.0f);
	InitCurrentRage(1.0f);
	InitMaxRage(1.0f);
	InitAttackPower(1.0f);
	InitDefensePower(1.0f);
}

void UWarriorAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.0f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);
	}

	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 0.0f, GetMaxRage());

		SetCurrentRage(NewCurrentRage);
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();

		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.0f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);

		const FString DebugString = FString::Printf(TEXT("Old Heath: %f, Damage Done: %f, NewCurrentHealth: %f"),
													OldHealth, DamageDone, NewCurrentHealth);

		Debug::Print(DebugString, FColor::Green);
		
		// TODO: Notify the UI
		
		if (NewCurrentHealth == 0.0f)
		{
			// TODO: Handle Character Death
		}
	}
}
