module Syntax where

import           Text.ParserCombinators.Parsec.Expr
import           Text.ParserCombinators.Parsec.Language
import qualified Text.ParserCombinators.Parsec.Token    as Token
import           Text.Parsec

languageDef =
   emptyDef { Token.commentStart    = "{-"
            , Token.commentEnd      = "-}"
            , Token.commentLine     = "--"
            , Token.identStart      = letter
            , Token.identLetter     = alphaNum
            , Token.reservedNames   = ["true", "false", "if", "then", "else", "print", "return", "integrate", "derivate"]
            , Token.reservedOpNames = ["+", "-", "*", "/", "=", "and", "or", "not"
                                     , "<", ">", "<=", ">=", "==", ":", "sin", "cos", "tan", "log10", "ln"]
             }

lexer = Token.makeTokenParser languageDef

identifier = Token.identifier lexer -- parses an identifier
reserved   = Token.reserved   lexer -- parses a reserved name
reservedOp = Token.reservedOp lexer -- parses an operator
parens     = Token.parens     lexer -- parses surrounding parenthesis:
integer    = Token.integer    lexer -- parses an integer
semi       = Token.semi       lexer -- parses a semicolon
whiteSpace = Token.whiteSpace lexer -- parses whitespace

functions = [Prefix (reservedOp "sin" >> return (Function Sin)),
             Prefix (reservedOp "cos" >> return (Function Cos)),
             Prefix (reservedOp "tan" >> return (Function Tan)),
             Prefix (reservedOp "sec" >> return (Function Sec)),
             Prefix (reservedOp "csc" >> return (Function Csc)),
             Prefix (reservedOp "cot" >> return (Function Cot)),
             Prefix (reservedOp "ln"  >> return (Function (Log (Fractional 2.7)))),
             Prefix (reservedOp "log10" >> return (Function (Log (Constant 10))))]

operators = [ [Prefix  (reservedOp "-"  >> return (Neg))],
              functions
            , [Infix  (reservedOp "^"   >> return (BinaryExpression Exponent)) AssocLeft,
               Infix  (reservedOp "*"   >> return (BinaryExpression Multiply)) AssocLeft,
               Infix  (reservedOp "/"   >> return (BinaryExpression Divide  )) AssocLeft]
            , [Infix  (reservedOp "+"   >> return (BinaryExpression Add     )) AssocLeft,
               Infix  (reservedOp "-"   >> return (BinaryExpression Subtract)) AssocLeft]
            , [Infix  (reservedOp "="   >> return (Equality)) AssocLeft]
             ]

--Calculation

data Expression = Variable   String
                | Constant   Integer
                | Fractional Double
                | Neg        Expression
                | Equality   Expression Expression
                | BinaryExpression BinaryOperator Expression Expression
                | Function LibraryFunction Expression
                  deriving (Eq, Show)

data BinaryOperator = Add
                    | Subtract
                    | Multiply
                    | Divide
                    | Exponent
                      deriving (Eq, Show)

type Base = Expression

data LibraryFunction = Log Base
                     | Sin
                     | Cos
                     | Tan
                     | Sec
                     | Csc
                     | Cot
                     | Root Base
                     deriving (Eq, Show)

--AST

data Statement = Assignment          String Statement
               | FunctionCall        Statement [Integer]
               | DerivateStatement   Statement
               | IntegrateStatement  Statement
               | SolveStatement      Expression
               | Identifier          String
               | Calculation         Expression
               | None
                 deriving (Eq, Show)
