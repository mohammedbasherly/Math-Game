#include <iostream>

using namespace std;

enum enLevel { Easy = 1, Med = 2, Hard = 3, MixLevel = 4 };
enum enOpType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOpType = 5 };

struct stQuestion
{
	short NumberOfQuestion = 0;
	enLevel QuestionLevel;
	enOpType QuestionOpType;
	int Number1 = 0;
	int Number2 = 0;
	int Result = 0;
	int PlayerAnswer = 0;
	bool isAnswerCorrect = false;
};
struct stQuizzInfo
{
	stQuestion Questions[10];
	short NumberOfQuestions = 0;
	enLevel Level;
	enOpType OpType;
	short NumberOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;
	bool isPass = false;
};

int readIntNumberInRange(string msg, int from, int to)
{
	int num;

	do
	{
		cout << msg;
		cin >> num;
	} while (num < from || num > to);

	return num;
}

enLevel readQuizLevel()
{
	string msg = "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
	return (enLevel)readIntNumberInRange(msg, 1, 4);
}

enOpType readQuizOpType()
{
	string msg = "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
	return (enOpType)readIntNumberInRange(msg, 1, 5);
}

int randomNumber(int from, int to)
{
	return rand() % (to - from + 1) + from;
}

enLevel getQuestionLevel(enLevel level)
{
	if (level == enLevel::MixLevel)
		return (enLevel)randomNumber(1, 3);
	return level;
}

enOpType getQuestionOpType(enOpType opType)
{
	if (opType == enOpType::MixOpType)
		return (enOpType)randomNumber(1, 4);
	return opType;
}

int getNumberAccordingToLevel(enLevel level)
{
	switch (level)
	{
	case Easy:
		return randomNumber(1, 9);
	case Med:
		return randomNumber(10, 50);
	case Hard:
		return randomNumber(50, 100);
	default:
		return randomNumber(1, 9);
	}
}

int calculateQuestion(enOpType opType, int number1, int number2)
{
	switch (opType)
	{
	case Add:
		return number1 + number2;
	case Sub:
		return number1 - number2;
	case Mul:
		return number1 * number2;
	case Div:
		return number1 / number2;
	default:
		return -1;
	}
}

string getOpTypeSymbol(enOpType opType)
{
	switch (opType)
	{
	case Add:
		return "+";
	case Sub:
		return "-";
	case Mul:
		return "x";
	case Div:
		return "/";
	default:
		return "Mix";
	}
}

int readIntNumber(string msg)
{
	int num;

	cout << msg;
	cin >> num;

	return num;
}

int askQuestion(stQuestion question, short NumberOfQuestions)
{
	int result = 0;

	cout << "Question [" << question.NumberOfQuestion << "/" << NumberOfQuestions << "]\n";
	cout << question.Number1 << endl;
	cout << getOpTypeSymbol(question.QuestionOpType) << " ";
	cout << question.Number2 << endl;
	cout << "_________\n";
	result = readIntNumber("Answer: ");

	return result;
}

bool isYourAnswerCorrect(int rightAnswer, int yourAnswer)
{
	return rightAnswer == yourAnswer;
}

void createAndAnswerQuestion(stQuestion& question, short questionNumber, enLevel level, enOpType opType, short numberOfQuestions)
{
	question.NumberOfQuestion = questionNumber;
	question.QuestionLevel = getQuestionLevel(level);
	question.QuestionOpType = getQuestionOpType(opType);
	question.Number1 = getNumberAccordingToLevel(question.QuestionLevel);
	question.Number2 = getNumberAccordingToLevel(question.QuestionLevel);
	question.Result = calculateQuestion(question.QuestionOpType, question.Number1, question.Number2);
	question.PlayerAnswer = askQuestion(question, numberOfQuestions);
	question.isAnswerCorrect = isYourAnswerCorrect(question.Result, question.PlayerAnswer);
}

void setScreenColor(bool isPass)
{
	if (isPass)
		system("color 27");
	else
		system("color 47");
}

void showQuestionResult(bool isAnswerCorrect, int rightAnswer, int yourAnswer)
{
	setScreenColor(isAnswerCorrect);
	if (isAnswerCorrect)
		cout << "Right Answer :)\n";
	else
	{
		cout << "Wrong Answer :(\n";
		cout << "The right answer is: " << rightAnswer << endl;
	}
}

void createAndAnswerQuestions(stQuizzInfo& quizInfo)
{
	cout << endl;
	for (short i = 1; i <= quizInfo.NumberOfQuestions; i++)
	{
		createAndAnswerQuestion(quizInfo.Questions[i - 1], i, quizInfo.Level, quizInfo.OpType, quizInfo.NumberOfQuestions);

		showQuestionResult(quizInfo.Questions[i - 1].isAnswerCorrect, quizInfo.Questions[i - 1].Result, quizInfo.Questions[i - 1].PlayerAnswer);

		if (isYourAnswerCorrect(quizInfo.Questions[i - 1].Result, quizInfo.Questions[i - 1].PlayerAnswer))
			quizInfo.NumberOfRightAnswers++;
		else
			quizInfo.NumberOfWrongAnswers++;

		cout << endl;
	}
}

string tabs(short numberOfTabs)
{
	string tabs = "";
	for (int i = 0; i < numberOfTabs; i++)
		tabs += "\t";

	return tabs;
}

bool isQuizPassed(int numberOfRightAnswers, int numberOfWrongAnswers)
{
	return numberOfRightAnswers >= numberOfWrongAnswers;
}

stQuizzInfo playGame(short numberOfQuestions)
{
	stQuizzInfo quizInfo;
	quizInfo.NumberOfQuestions = numberOfQuestions;
	quizInfo.Level = readQuizLevel();
	quizInfo.OpType = readQuizOpType();
	createAndAnswerQuestions(quizInfo);
	quizInfo.isPass = isQuizPassed(quizInfo.NumberOfRightAnswers, quizInfo.NumberOfWrongAnswers);

	return quizInfo;
}

string getPassOrFailText(bool isPass)
{
	if (isPass)
		return "Pass";

	return "Fail";
}

string getQuizLevelText(enLevel level)
{
	switch (level)
	{
	case Easy:
		return "Easy";
	case Med:
		return "Medium";
	case Hard:
		return "Hard";
	default:
		return "Mix";
	}
}

void showQuizResults(stQuizzInfo quizInfo)
{
	setScreenColor(quizInfo.isPass);
	cout << tabs(2) << "________________________________\n\n";
	cout << tabs(2) << "  Final Result is " << getPassOrFailText(quizInfo.isPass) << endl;
	cout << tabs(2) << "________________________________\n";
	cout << tabs(2) << " Number of Questions    : " << quizInfo.NumberOfQuestions << endl;
	cout << tabs(2) << " Questions Level        : " << getQuizLevelText(quizInfo.Level) << endl;
	cout << tabs(2) << " Operation Type         : " << getOpTypeSymbol(quizInfo.OpType) << endl;
	cout << tabs(2) << " Number Of Right Answers: " << quizInfo.NumberOfRightAnswers << endl;
	cout << tabs(2) << " Number Of Wrong Answers: " << quizInfo.NumberOfWrongAnswers << endl;
	cout << tabs(2) << "________________________________\n";
}

void resetScreen()
{
	system("cls");
	system("color 0F");
}

void startGame()
{
	char playAgain = 'y';

	do
	{
		resetScreen();
		stQuizzInfo quiz = playGame(readIntNumberInRange("How many Question you want?\nQuestions: ", 1, 10));
		showQuizResults(quiz);

		cout << "\nDo you want to play again? [y/n\? ";
		cin >> playAgain;
	} while (playAgain == 'y' || playAgain == 'Y');
}

int main()
{
	srand((unsigned)time(NULL));

	startGame();

	return 0;
}
