typedef struct
{
    char* name; /* Command name*/
    int opcode; /* Command opcode */
    int funct; /* Command function code */
    int numOfOpreand; /* Number of operands expected with command */
    unsigned int srcImidiateadAdress : 1;
    unsigned int srcDirectAddress : 1;
    unsigned int srcRelativeAddress : 1;
    unsigned int srcDirectRegAdress : 1;
    unsigned int destImidiateAddress : 1;
    unsigned int destDirectAddress : 1;
    unsigned int destRelativeAddress : 1;
    unsigned int destDirectRegAdress : 1;

} commandsType;

typedef enum
{
	immediateNum,
	SymbolOperand
	RealativeOperand,
	RegisterOperand
} operandType;

typedef struct
{
	operandType type; /* Type of operand */
	union 
	{
		int immediateNum; /* Number for immediate addres */
		char* Symbol; /* If there is a symbol in the operand */
		char numOfRegister; /* Number of register in operand - for register type */
	} operandValue; /* What inside the operand */
} operand;




/*
 struct of a command  with all the deatils
 */
typedef struct
{
    int numOfCommand; /* number of the command from the commandsTypes */
	operand firstOperand; /* origin operand */
	operand secondOperand; /* destination operand */
	int address; /* the address of command */
} command;
