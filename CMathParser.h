#ifndef _CMathParser_H
#define _CMathParser_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define CMATHPARSER_MIN_PRECISION     0
#define CMATHPARSER_MAX_PRECISION     32
#define CMATHPARSER_DEFAULT_PRECISION 16
#define CMATHPARSER_MAX_VAR_LENGTH    128

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CMathParser {
private:
	typedef struct _tag_Math_Expression {
		char *Text;
		int Length;
		int Allocated;
	} MATHEXPRESSION, *LPMATHEXPRESSION;

	typedef struct _tag_Math_Inst {
		MATHEXPRESSION Expression;
		bool ForceIntegerMath;
		bool ForceUnsignedMath;
		double RunningTotal;
	} MATHINSTANCE, *LPMATHINSTANCE;

public:
	typedef void(*TDebugTextCallback)(CMathParser* pParser, const char* sText);
	typedef bool (*TVariableSetCallback)(CMathParser* pParser, const char* sVarName, double* dReturnValue);

	enum MathResult {
		ResultFoundNegative = -1,
		ResultOk = 0,
		ResultInfiniteOrNotANumber,
		ResultMissingOperator,
		ResultInvalidOperator,
		ResultInvalidToken,
		ResultIntegerunderflow,
		ResultIntegerOverflow,
		ResultIntegerTextConversionFailed,
		ResultDoubleTextConversionFailed,
		ResultRightValueFailed,
		ResultParenthesesMismatch,
		ResultMemoryAllocationError,
		ResultUndefiendVariable
	};

	typedef struct _tag_Error_Information {
		char* Text;
		MathResult Error;
	} MATHERRORINFO, *LPMATHERRORINFO;

	MathResult Calculate(const char *sExpression, int iExpressionSz, double *dResult);
	MathResult Calculate(const char *sExpression, double *dResult);
	MathResult Calculate(const char *sExpression, int iExpressionSz, int *iResult);
	MathResult Calculate(const char *sExpression, int *iResult);
	MathResult Calculate(const char *sExpression, int iExpressionSz, unsigned int *iResult);
	MathResult Calculate(const char *sExpression, unsigned int *iResult);

	int SmartRound(double dValue, char *sOut, int iMaxOutSz);

	bool IsMathChar(const char cChar);
	bool IsValidChar(const char cChar);
	bool IsValidVariableChar(const char cChar);
	bool IsIntegerExclusive(const char *sOperator);
	int MatchParentheses(const char *sExpression, const int iExpressionSz);
	int DoubleToChar(double dVal, char *sOut, int iMaxOutSz);
	int ModPow(long long base, long long exponent, int modulus);

	CMathParser(short iPrecision);
	CMathParser(void);
	~CMathParser(void);

	short Precision(short iPrecision);
	short Precision(void);

	TVariableSetCallback GetVariableSetCallback(void);
	TVariableSetCallback SetVariableSetCallback(TVariableSetCallback procPtr);

	TDebugTextCallback GetDebugCallback(void);
	TDebugTextCallback SetDebugCallback(TDebugTextCallback procPtr);

	bool DebugMode(bool bDebugMode);
	bool DebugMode(void);
	MATHERRORINFO *LastError(void);

private:
	bool cbDebugMode;
	short ciPrecision;
	MATHERRORINFO LastErrorInfo;
	TVariableSetCallback pVariableSetProc;
	TDebugTextCallback pDebugProc;

	MathResult PerformDoubleOperation(MATHINSTANCE *pInst, double dVal1, const char *sOpr, double dVal2);
	MathResult PerformBooleanOperation(MATHINSTANCE *pInst, int iVal, const char *sOpr);
	MathResult PerformIntOperation(MATHINSTANCE *pInst, int iVal1, const char *sOpr, int iVal2);

	MathResult CalculateSimpleExpression(MATHINSTANCE *pInst, MATHEXPRESSION *pSubExp);
	MathResult CalculateComplexExpression(MATHINSTANCE *pInst);

	MathResult GetLeftNumber(MATHEXPRESSION *pExp, int iStartPos, char *sOutVal, int iMaxSz, int *iOutSz, int *iBegin);
	MathResult GetRightNumber(MATHEXPRESSION *pExp, int iStartPos, char *sOutVal, int iMaxSz, int *iOutSz, int *iEnd);
	MathResult GetSubExpression(MATHINSTANCE *pInst, int *iBegin, int *iEnd);
	MathResult ParseOperator(MATHINSTANCE *pInst, MATHEXPRESSION *pExp, const char *sOp, int iOpPos, int iOpSz);
	MathResult ExecuteNativeMethod(const char* sMethodName, double* dParameters, int iParamCount, double* pOutResult);
	MathResult ParseMethodParameters(const char* sSource, int iSourceSz, int* piRPos, double** pOutParameters, int* piOutParamCount);

	int GetFreestandingNotOperation(MATHEXPRESSION *pExp);
	int GetFirstOrderOperation(MATHEXPRESSION *pExp);
	int GetSecondOrderOperation(MATHEXPRESSION *pExp, int iStartPos);

	MathResult ReplaceValue(MATHEXPRESSION *pExp, int iBegin, int iEnd, const char *sWith, int iWithSz);
	MathResult AllocateExpression(MATHEXPRESSION *pExp, const char *sSource, int iSourceSz);

	int InStr(const char *sSearchFor, const char *sInBuf, const int iBufSz, const int iStartPos);
	bool ReverseString(char *sBuf, int iBufSz);
	bool IsWhiteSpace(const char cChar);
	bool IsNativeMethod(const char* sName);
	bool IsNumeric(const char cIn);
	bool IsNumeric(const char *sText, int iLength);
	bool IsNumeric(const char *sText);
	int TrailingChars(const char *sVal, int iStartPos, const char cChar);

	MathResult SetError(MathResult ErrorCode, const char *sFormat, ...);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
