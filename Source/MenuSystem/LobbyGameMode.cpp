// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

#define FUNC_NAME    *FString(__func__)
#define ADD_ON_SCREEN_DEBUG_MESSAGE(TimeFloat, Color, OnlineSessionString)	\
		if (GEngine) \
		{ \
		GEngine->AddOnScreenDebugMessage( \
			-1, \
			TimeFloat, \
			Color, \
			FString::Printf(TEXT("%s : %s"), FUNC_NAME, *OnlineSessionString) \
		); \
		}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GameState)
	{
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
		ADD_ON_SCREEN_DEBUG_MESSAGE(5.f, FColor::Yellow, FString::Printf(TEXT("Joined Players Num = %d"), NumberOfPlayers));

		APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>();
		if (PlayerState)
		{
			FString PlayerName = PlayerState->GetPlayerName();
			ADD_ON_SCREEN_DEBUG_MESSAGE(5.f, FColor::Cyan, FString::Printf(TEXT("%s has joined the game."), *PlayerName));
		}

	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	APlayerState* PlayerState = Exiting->GetPlayerState<APlayerState>();
	if (PlayerState)
	{
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
		ADD_ON_SCREEN_DEBUG_MESSAGE(5.f, FColor::Yellow, FString::Printf(TEXT("Joined Players Num = %d"), NumberOfPlayers - 1));

		FString PlayerName = PlayerState->GetPlayerName();
		ADD_ON_SCREEN_DEBUG_MESSAGE(5.f, FColor::Cyan, FString::Printf(TEXT("%s has exited the game."), *PlayerName));
	}
}
