import qualified Data.Map as Map
import Data.Either
import Text.ParserCombinators.Parsec hiding (State)
import Control.Monad
import Control.Monad.State

data Object = Object [String] [String] deriving (Show)

consObjs (Object is1 cs1) (Object is2 cs2) = (Object (is1 ++ is2) (cs1 ++ cs2))

type KnowledgeBase = Map.Map String Object

main = getLine >>= (run Map.empty)

run :: KnowledgeBase -> String -> IO ()
run kbase line = case parse statement "" line of

    Right (Right (s, o)) -> do
    
        let newKbase = (runState (add s o) kbase)
        getLine >>= (run $ snd newKbase)
        
    Right (Left q) -> do
        putStrLn $ answer kbase q
        getLine >>= (run kbase)

    Left _       -> getLine >>= (run kbase)
      
characteristicOf :: KnowledgeBase -> String -> String -> Bool
characteristicOf kbase char atom = case Map.lookup atom kbase of
                        Just (Object is cs) -> (or $ map (characteristicOf kbase char) is) || char `elem` cs
                        Nothing -> False
                        
inheritanceOf :: KnowledgeBase -> String -> String -> Bool
inheritanceOf kbase inherit atom = case Map.lookup atom kbase of
                        Just (Object is cs) -> (or $ map (inheritanceOf kbase inherit) is) || inherit `elem` is
                        Nothing -> False
      
type Answer = String

answer :: KnowledgeBase -> Question -> Answer
answer kbase (Question isC key val) = if found then "Yes"
                                               else "No"
    where found = if isC then characteristicOf kbase val key
                         else inheritanceOf    kbase val key
    
      
add :: String -> Object -> State KnowledgeBase ()
add s o = do
    kbase <- get
    put $ check kbase s o
    where check kbase s o = case Map.lookup s kbase of
                        Just oldO  -> Map.insert s (oldO `consObjs` o) kbase
                        Nothing    -> Map.insert s o kbase
    
data Question = Question Bool String String
type Input = Either Question (String, Object)
    
question :: GenParser Char st Input
question = try askI
        <|> askC
        <?> "Parse Error"
        
    where askI = do
            is
            space
            first <- word
            space
            a 
            space
            second <- word
            char '?'
            return $ Left $ Question False first second
            
          askC = do
            is
            space
            first  <- word
            space
            second <- word
            char '?'
            return $ Left $ Question True first second
            
statement = try inheritance
        <|> try characteristic
        <|> question
        <?> fail "Invalid Statement"
        
characteristic :: GenParser Char st Input
characteristic = do
    first <- word
    space
    is
    space
    second <- word
    return $ Right $ (first, (Object [] [second]))
    
inheritance :: GenParser Char st Input
inheritance = do
    first <- word
    space
    is
    space
    a
    space
    second <- word
    return $ Right $ (first, (Object [second] []))
    
word = many $ noneOf " ?"

parseWords :: GenParser Char st [String]
parseWords = sepBy word (char ' ')
    
parseAnd :: GenParser Char st String
parseAnd  = string " and "
    
is   = string "is"
a :: GenParser Char st Char
a    = char 'a'