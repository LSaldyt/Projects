module Text where

type Point     = (Int, Int)
type Path      = [(Int, Int)]
data Object    = Object Char Point
data Field     = Field {objects :: [Object], width :: Int, height :: Int}
data Direction = North | East | South | West

instance Show Field where
  show field = [if x == (width field) then '\n' else snd (findObject (x, y) (objects field)) | y <- [0..(height field)], x <- [0..(width field)]]
instance Show Object where
  show (Object c _) = show c

instance Eq Object where
  (==) (Object _ pos1) (Object _ pos2) = (==) pos1 pos2

instance Ord Object where
  compare (Object _ pos1) (Object _ pos2) = compare pos1 pos2

findObject _ [] = (False, '-')
findObject (x, y) ((Object c (x', y')):os) = if (x == x' && y == y') then (True, c) else findObject (x, y) os


qsort :: (Ord a) => [a] -> [a]
qsort [] = []
qsort (x:xs) =
  let smallerSorted = qsort [a | a <- xs, a <= x]
      biggerSorted  = qsort [a | a <- xs, a > x]
  in smallerSorted ++ [x] ++ biggerSorted

findObject' _ [] = False
findObject' (x, y) ((Object _ (x', y')):os) = if (x == x' && y == y') then True else findObject' (x, y) os
