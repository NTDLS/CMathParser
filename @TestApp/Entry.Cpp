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

bool VariableCallback(CMathParser* pParser, const char* sVarName, double* dReturnValue)
{
	if (_strcmpi(sVarName, "Cars") == 0)
	{
		*dReturnValue = 100;
	}
	else if (_strcmpi(sVarName, "Busses") == 0)
	{
		*dReturnValue = 200;
	}
	else if (_strcmpi(sVarName, "Trains") == 0)
	{
		*dReturnValue = 300;
	}
	else
	{
		return false; //We didn't have a variable by that name.
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CheckResult(const char *sExpression, double dExpectedResult)
{
	double dResult = 0;
	CMathParser MP;
	MP.DebugMode(false);

	MP.SetVariableSetCallback(&VariableCallback);

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
	CheckResult("sin(0.314000)", 0.3088655200);
	CheckResult("cos(0.314000)", 0.9511057200);
	CheckResult("tan(0.314000)", 0.3247436300);
	CheckResult("sinh(0.250000)", 0.2526123200);
	CheckResult("cosh(0.250000)", 1.0314131000);
	CheckResult("tanh(0.250000)", 0.2449186600);
	CheckResult("log(6.250000)", 1.8325814600);
	CheckResult("log10(6.250000)", 0.7958800200);
	CheckResult("exp(6.250000)", 518.0128246700);

	CheckResult("floor(100.500)", 100);
	CheckResult("ceil(100.500)", 101);
	CheckResult("sqrt(65)", 8.0622577500);
	CheckResult("pow(2,10)", 1024);
	CheckResult("modPow(12345, 1024, 10)", 5.00);

	CheckResult("NOT((100 / 100) - 1)", 1);
	CheckResult("NOT(0)", 1);
	CheckResult("NOT(1)", 0);

	CheckResult("avg(1,2,3,4,5,6,7,8,9,10)", 5.5);
	CheckResult("sum(10,10,10,10,10)", 50);
	CheckResult("cos(Cars)", 0.8623188700);
	CheckResult("tan(Cars)", -0.5872139200);
	CheckResult("atan(Cars)", 1.5607966600);
	CheckResult("sin(Cars)", -0.5063656400);
	CheckResult("abs(-Cars)", 100.0000000000);

	CheckResult("10 + sum(20 + 30, sum(10, sum(10,10,10) + 10)) + 50", 160);
	CheckResult("10 + sum(20 + 30, 40) + 50", 150);

	CheckResult("10 * Cars", 1000);
	CheckResult("10 * Busses", 2000);
	CheckResult("10 * Trains", 3000);

	CheckResult("10 * Cars * 10", 10000);
	CheckResult("10 * Busses * 10", 20000);
	CheckResult("10 * Trains * 10", 30000);

	CheckResult("(10 * Cars)", 1000);
	CheckResult("(10 * Busses)", 2000);
	CheckResult("(10 * Trains)", 3000);

	CheckResult("10 + ((10 * Cars) * 10)", 10010);
	CheckResult("10 + ((10 * Busses) * 10)", 20010);
	CheckResult("10 + ((10 * Trains) * 10)", 30010);

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
