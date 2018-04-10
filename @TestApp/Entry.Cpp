#ifndef _ENTRY_CPP
#define _ENTRY_CPP
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Windows.H>
#include <Stdio.H>
#include <Stdlib.H>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../CMathParser.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PrintResult(const char *sExpression, bool bDebugMode)
{
	double dResult = 0;
	CMathParser MP;
	MP.DebugMode(bDebugMode);
	//MP.Precision(10);
	if(MP.Calculate(sExpression, &dResult) != CMathParser::ResultOk)
	{
		printf("Error in Formula.\n");
	}
	else{
		printf("[%s] = %.10f\n", sExpression, dResult);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CheckResult(const char *sExpression, double dExpectedResult)
{
	double dResult = 0;
	CMathParser MP;
	MP.DebugMode(false);
	if(MP.Calculate(sExpression, &dResult) != CMathParser::ResultOk)
	{
		printf("Error in Formula.\n");
	}
	else{
		char *sSuffix = "";
		if(dResult != dExpectedResult)
		{
			printf("[%s] = %.10f %s\n", sExpression, dResult, "(INCORRECT)");
		}
		else {
			printf("%.4f = %.4f %s\n", dResult, dExpectedResult, "(Correct)");
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	CheckResult("9^2*9^2-1", 26);
	CheckResult("!10+10", 10);
	CheckResult("10+!10", 10);
	CheckResult("!10*10", 0);
	CheckResult("10*!10", 0);
	CheckResult("!10>10", 0);
	CheckResult("!10<10", 1);
	CheckResult("10>!10", 1);
	CheckResult("10<!10", 0);
	CheckResult("!(((10 * 10) / 100) - 1)", 1);
	CheckResult("!(((10 * 10) / 100))", 0);
	CheckResult("!2 && !1", 0);
	CheckResult("(!2) && (!1)", 0);
	CheckResult("!1 && !1", 0);
	CheckResult("(!1) && (!1)", 0);
	CheckResult("!2 && !0", 0);
	CheckResult("(!2) && (!0)", 0);
	CheckResult("!0 && !0", 1);
	CheckResult("(!0) && (!0)", 1);
	CheckResult("50 + 50", 100);
	CheckResult("9 * 9", 81);
	CheckResult("+9+-1", 8);
	CheckResult("1+2+3+4+5", 15);
	CheckResult("+1+2+3+4+5", 15);
	CheckResult("1+2+-3+4+5", 9);
	CheckResult("-1+2+3+4+5", 13);
	CheckResult("((6+1)+((((5)))))", 12);
	CheckResult("5-9*(8/5)+69*(89*((-9+9)*9))*9/9+9-9*5/1/2.28+6.8/8.9+(3.2-9.1)*2.2/12.012+5-4*2/3+(9/8)/8", -17.979424908695687);
	CheckResult("!(10*10) > 0", 0);
	CheckResult("!(10*10) < 0", 0);
	CheckResult("0 > !(10*10)", 0);
	CheckResult("0 < !(10*10)", 0);
	CheckResult("!(10*10) > !0", 0);
	CheckResult("!(10*10) < !0", 1);
	CheckResult("!0 > !(10*10)", 1);
	CheckResult("!0 < !(10*10)", 0);
	CheckResult("!(10*10) > !1", 0);
	CheckResult("!(10*10) < !1", 0);
	CheckResult("!1 > !(10*10)", 0);
	CheckResult("!1 < !(10*10)", 0);
	CheckResult("!(10*10/100-1)", 1);
	CheckResult("!10+10-1", 9);
	CheckResult("10+10-!1", 20);

	system("pause");

	/*
	char sBuf[1024 * 5];
	char sMode[10];

	bool bDebug = false;

	strcpy_s(sMode, sizeof(sMode), "I");

	printf("Type: Help for commands and other instructions...\n");
	printf("Otherwise, just enter a mathematical expression and press enter.\n\n");

	while(true)
	{
		printf(">");
		gets_s(sBuf, sizeof(sBuf));

		if(_strcmpi(sBuf, "Help") == 0)
		{
			printf("Commands:\n");
			printf("  Help   Displays this help text.\n");
			printf("  Cls    Clears the screen.\n");
			printf("  Opt    Displays all supported mathematical operators.\n");
			printf("  Mode   Changed math mode between Integer and Decimal.\n");
			printf("  Debug  Enables/Disables mathematical debug information.\n");
			printf("  Exit   Quits the math parser.\n");
			printf("\n\n");
		}
		else if(_strcmpi(sBuf, "Opt") == 0)
		{
			printf("First Order\n");
			printf("  *      Multiplication\n");
			printf("  /      Division\n");
			printf("  %%      Modulation\n");
			printf("\n");

			printf("Second Order\n");
			printf("  +      Addition\n");
			printf("  -      Subtraction\n");
			printf("\n");

			printf("Third Order\n");
			printf("  <>      Logical Not Equal\n");
			printf("  |=      Bitwise Or Equal\n");
			printf("  &=      Bitwise And Equal\n");
			printf("  ^=      Bitwise XOR Equal\n");
			printf("  <=      Logical Less or Equal\n");
			printf("  >=      Greater Greater or Equal\n");
			printf("  !=      Logical Not Equal\n");
			printf("  <<      Bitwise Left Shift\n");
			printf("  >>      Bitwise Right Shift\n");
			printf("  =       Logical Equals\n");
			printf("  >       Logical Greater Than\n");
			printf("  <       Logical Less Than\n");
			printf("  &&      Logical AND\n");
			printf("  ||      Logical OR\n");
			printf("  |       Bitwise OR\n");
			printf("  &       Bitwise AND\n");
			printf("  ^       Exclusive OR\n");
			printf("  !       Logical NOT\n");
		}
		else if(_strcmpi(sBuf, "Cls") == 0)
		{
			system("Cls");
		}
		else if(_strcmpi(sBuf, "Exit") == 0)
		{
			break;
		}
		else if(_strcmpi(sBuf, "Debug") == 0)
		{
			do{
				printf("Debug mode? (Y/N): ");
				gets_s(sBuf, sizeof(sBuf));
			} while(_strcmpi(sBuf, "Y") !=0 && _strcmpi(sBuf, "N") != 0);

			bDebug = (_strcmpi(sBuf, "Y") == 0);
		}
		else if(_strcmpi(sBuf, "Mode") == 0)
		{
			do{
				printf("Integer or Decimal math? (I/D): ");
				gets_s(sMode, sizeof(sMode));
			} while(_strcmpi(sMode, "I") !=0 && _strcmpi(sMode, "D") != 0);
		}
		else {
			if(_strcmpi(sMode, "I") == 0)
			{
				int iResult = 0;
				CMathParser MP;
				MP.DebugMode(bDebug);
				if(MP.Calculate(sBuf, &iResult) != CMathParser::ResultOk)
				{
					printf("Error in Formula.\n");
				}
				else{
					printf(" = %d\n", iResult);
				}
			}
			else if(_strcmpi(sMode, "D") == 0)
			{
				double dResult = 0;
				CMathParser MP;
				MP.DebugMode(bDebug);
				if(MP.Calculate(sBuf, &dResult) != CMathParser::ResultOk)
				{
					printf("Error in Formula.\n");
				}
				else{
					printf(" = %.8f\n", dResult);
				}
			}
		}
	}
	*/

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
