// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ModularPawn.h"
#include "Teams/D1TeamAgentInterface.h"

#include "LyraPawn.generated.h"

class AController;
class UObject;
struct FFrame;

/**
 * ALyraPawn
 */
UCLASS()
class D1GAME_API ALyraPawn : public AModularPawn, public ID1TeamAgentInterface
{
	GENERATED_BODY()

public:

	ALyraPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~AActor interface
	virtual void PreInitializeComponents() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End of AActor interface

	//~APawn interface
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	//~End of APawn interface

	//~ID1TeamAgentInterface interface
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual FOnD1TeamIndexChangedDelegate* GetOnTeamIndexChangedDelegate() override;
	//~End of ID1TeamAgentInterface interface

protected:
	// Called to determine what happens to the team ID when possession ends
	virtual FGenericTeamId DetermineNewTeamAfterPossessionEnds(FGenericTeamId OldTeamID) const
	{
		// This could be changed to return, e.g., OldTeamID if you want to keep it assigned afterwards, or return an ID for some neutral faction, or etc...
		return FGenericTeamId::NoTeam;
	}

private:
	UFUNCTION()
	void OnControllerChangedTeam(UObject* TeamAgent, int32 OldTeam, int32 NewTeam);

private:
	UPROPERTY(ReplicatedUsing = OnRep_MyTeamID)
	FGenericTeamId MyTeamID;

	UPROPERTY()
	FOnD1TeamIndexChangedDelegate OnTeamChangedDelegate;

private:
	UFUNCTION()
	void OnRep_MyTeamID(FGenericTeamId OldTeamID);
};
