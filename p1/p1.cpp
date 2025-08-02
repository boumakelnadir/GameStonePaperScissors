#include <iostream>

using namespace std;

enum enWinner{ Player = 1 ,Computer = 2 , Draw = 3 };

enum enRoundChoice { Papper = 1, Stone = 2, Scissors = 3 };

struct stGameResult {
	short GameRound = 0;
	short Player1WonTimes = 0;
	short ComputerWonTimes = 0;
	short DrawTimes = 0;
	enWinner Winner;
	string WinnerName = "";
};

struct stRoundInfo
{
	short GameRound = 0;
	enRoundChoice Player1Choice;
	enRoundChoice ComputerChoice;
	enWinner Winner;
	string WinnerName = "";
};

short HowManyRound(string message)
{
	short howManyRound;

	do
	{
		cout << message << endl;
		cin >> howManyRound;

	} while (howManyRound < 1 || howManyRound > 10);

	return howManyRound;
}

enRoundChoice ReadPlayerChoice()
{
	short PlayerChoice = 1;

	do
	{
		cout << "\nDo You Want Choice [1] Papper , [2] Stone , [3] Scissors : ";
		cin >> PlayerChoice;

	} while (PlayerChoice < 1 || PlayerChoice > 3);

	return (enRoundChoice) PlayerChoice;
}

short RandomNumber(short from, short to)
{
	short RandomNumber = rand() % (to - from + 1) + from ;

	return RandomNumber;
}

enRoundChoice GetComputerChoice()
{
	return (enRoundChoice) RandomNumber(1,3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
		return enWinner::Draw;

	switch (RoundInfo.ComputerChoice)
	{
	case enRoundChoice::Papper:
		if (RoundInfo.Player1Choice == enRoundChoice::Scissors)
			return enWinner::Player;

	case enRoundChoice::Stone:
		if (RoundInfo.Player1Choice == enRoundChoice::Papper)
			return enWinner::Player;

	case enRoundChoice::Scissors:
		if (RoundInfo.Player1Choice == enRoundChoice::Stone)
			return enWinner::Player;
	}
	return enWinner::Computer;
}

string Winner(enWinner Winner)
{
	string arrWinnerName[3] = { "Player", "Computer", "Draw" };
	return arrWinnerName [Winner - 1];
}

enWinner WhoWonTheGame(stGameResult GameResult)
{
	if (GameResult.Player1WonTimes > GameResult.ComputerWonTimes)
		return enWinner::Player;

	else if (GameResult.Player1WonTimes < GameResult.ComputerWonTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

stGameResult FillGameResult(short GameRound, short Player1WonTimes, short ComputerWonTimes,short DrawTimes)
{
	stGameResult GameResult;
	GameResult.GameRound = GameRound;
	GameResult.Player1WonTimes = Player1WonTimes;
	GameResult.ComputerWonTimes = ComputerWonTimes;
	GameResult.DrawTimes = DrawTimes;
	GameResult.Winner = WhoWonTheGame(GameResult);
	GameResult.WinnerName = Winner(GameResult.Winner);

	return GameResult;

}

void SetColorOfScreen(enWinner Winner)
{
	if (Winner == ::Player)
		system("color 2F");
	else if (Winner == ::Computer) {
		system("color 4F");
		cout << "\a";
	}else
		system("color 6F");

}

string GameChoice(enRoundChoice RoundChoice)
{
	string arrGameChoice[3] = { "Papper", "Stone", "Scissors" };
	return arrGameChoice[RoundChoice - 1];
}

void ShowScreenWonRound(stRoundInfo RoundInfo)
{
	cout << "\n----------------------------------------------" << endl;
	cout << "Game Round            : " << RoundInfo.GameRound << endl;
	cout << "Player1 Choice        : " << GameChoice(RoundInfo.Player1Choice) << endl;
	cout << "Computer Choice       : " << GameChoice(RoundInfo.ComputerChoice) << endl;
	cout << "Winner                : " << Winner(RoundInfo.Winner) << endl;
	cout << "----------------------------------------------" << endl;
	
}

stGameResult PlayGame(short HowManyRound)
{
	stRoundInfo RoundInfo;

	short Player1WonTimes = 0, ComputerWonTimes = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRound; GameRound++)
	{
		cout << "--------------Game Round [" << GameRound <<"]---------------" << endl;

		RoundInfo.GameRound = GameRound;
		RoundInfo.Player1Choice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = Winner(RoundInfo.Winner);
		
		if (RoundInfo.Winner == enWinner::Player)
			Player1WonTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWonTimes++;
		else
			DrawTimes++;

		ShowScreenWonRound(RoundInfo);

		SetColorOfScreen(RoundInfo.Winner);

	}
	return FillGameResult(RoundInfo.GameRound, Player1WonTimes, ComputerWonTimes, DrawTimes);
}

string Tabs(short HowManyTabs)
{
	string Tabs = "";
	for (int t = 0; t < HowManyTabs; t++)
	{
		Tabs += "\t";
	}
	return Tabs;
}

void ShowScreenGameOver()
{
	cout << Tabs(2) << "-------------------------------------------------" << endl;
	cout << Tabs(4) << "++ Game Over ++" << endl;
	cout << Tabs(2) << "-------------------------------------------------" << endl;
}

void ShowScreenResultGameOver(stGameResult GameResult)
{
	cout << Tabs(2)<< "Game Rounds           : " << GameResult.GameRound << endl;
	cout << Tabs(2) << "Player1 Won Times     : " << GameResult.Player1WonTimes << endl;
	cout << Tabs(2) << "Computer Won Times    : " << GameResult.ComputerWonTimes<< endl;
	cout << Tabs(2) << "Draw Times	      : " << GameResult.DrawTimes<< endl;
	cout << Tabs(2) << "Winner The Game       : " << GameResult.WinnerName<< endl;
	cout << Tabs(2) << "---------------------------------------------------" << endl;
}

void ResetTheScreen()
{
	system("cls");
	system("color 0F");
}

void StartTheGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetTheScreen();

		stGameResult GameResult = PlayGame(HowManyRound("\nHow Many Round You Want Play [1 - 10 ] : "));
		ShowScreenGameOver();
		ShowScreenResultGameOver(GameResult);



		cout << Tabs(2) << "Do You Want Play Again Y/N : ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');


}

short main()
{
	srand((unsigned)time(0));

	StartTheGame();


	return 0;
}