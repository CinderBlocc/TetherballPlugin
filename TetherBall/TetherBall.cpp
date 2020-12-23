#include "TetherBall.h"
#include "bakkesmod\wrappers\includes.h"

BAKKESMOD_PLUGIN(TetherBall, "Tetherball plugin", "1.0", PLUGINTYPE_FREEPLAY)


void TetherBall::onLoad()
{
	gameWrapper->HookEvent("Function Engine.GameViewportClient.Tick", std::bind(&TetherBall::CheckSwap, this));
}
void TetherBall::onUnload() {}

void TetherBall::CheckSwap()
{
	ServerWrapper server = GetCurrentGameState();
	if(server.IsNull()) return;
    GameSettingPlaylistWrapper GSPW = server.GetPlaylist();
    if(GSPW.memory_address == NULL) return;
    if(!gameWrapper->IsInFreeplay() && GSPW.GetPlaylistId() != 24) return; //Only work in freeplay or LAN matches
	BallWrapper ball = server.GetBall();
	if(ball.IsNull()) return;

    if(gameWrapper->GetCurrentMap() != "LethTetherball") return;

	if(ball.GetLocation().Y > 0) ball.SetHitTeamNum(0);
	if(ball.GetLocation().Y < 0) ball.SetHitTeamNum(1);
}

ServerWrapper TetherBall::GetCurrentGameState()
{
	if(gameWrapper->IsInReplay())
		return gameWrapper->GetGameEventAsReplay().memory_address;
	else if(gameWrapper->IsInOnlineGame())
		return gameWrapper->GetOnlineGame();
	else
		return gameWrapper->GetGameEventAsServer();
}