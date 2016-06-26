module Search where

import Text
import qualified Data.Map as Map
import Data.List

data WeightedNode = WeightedNode Point Double

instance Eq WeightedNode where
 (==) (WeightedNode _ value1) (WeightedNode _ value2) = (==) value1 value2

instance Ord WeightedNode where
  compare (WeightedNode _ value1) (WeightedNode _ value2) = compare value1 value2

isValid field point = (not . fst $ findObject point (objects field))

getAdjacentAtDepth :: Int -> Point -> [Point]
getAdjacentAtDepth depth (posx, posy) = [(x, y) | x <- [posx-depth..posx+depth], y <- [posy-depth..posy+depth]]

getRawAdjacent (x, y) = [(x + 1, y    ), (x - 1, y    ),
                         (x    , y + 1), (x    , y - 1),
                         (x + 1, y + 1), (x - 1, y + 1),
                         (x + 1, y - 1), (x - 1, y - 1)]

getAdjacentWithin :: Field -> Point -> [Point]
getAdjacentWithin field (x, y) = filter check $ getRawAdjacent (x, y)
   where check (x', y') = (x' < (width field)
                        && x' >= 0
                        && y' < (height field)
                        && y' >= 0
                        && isValid field (x', y'))

getObstaclesWithin :: Field -> Point -> [Point]
getObstaclesWithin field (x, y) = filter check $ getRawAdjacent (x, y)
  where check (x', y') = (x' < (width field)
                       && x' >= 0
                       && y' < (height field)
                       && y' >= 0
                       && not (isValid field (x', y')))


getDistance :: Point -> Point -> Double
getDistance (x, y) (x', y') = sqrt (squareOfDifference x x' + squareOfDifference y y')
 where squareOfDifference a b = ((realToFrac a) - (realToFrac b)) ^ 2


type RankFunction = (Field -> Point -> Point -> WeightedNode)
type PointGraph = Map.Map Point [Point]

inverse num = 1.0 / num
comp' n f = foldr (.) id (replicate n f)

sigmoid :: Double -> Double
sigmoid x = x / (sqrt (1.0 + x ^ 2))

search :: RankFunction -> [Point] -> Field -> Point -> Point -> Path
search rank seen field start end
  | start == end = []
  | otherwise    = case ranked_nodes of
    [] -> []
    ns -> let (WeightedNode next _) = (last ns)
          in next : (search (rank) (next:seen) field next end)
  where ranked_nodes  = qsort $ [] ++ (map (rank field end) validAdjacent)
        validAdjacent = filter ((flip notElem) seen) $ getAdjacentWithin field start

--Generic definition of a rank function
rank :: WeighFunction -> Field -> Point -> Point -> WeightedNode
rank by field end node = WeightedNode node $ by field end node

type WeighFunction = Field -> Point -> Point -> Double

byDistance :: WeighFunction
byDistance _ end node = sigmoid (inverse (getDistance node end))

byLocalObstructions :: WeighFunction
byLocalObstructions field _ node = sigmoid . inverse $ numAdjacent
  where numAdjacent = realToFrac . length $ getObstaclesWithin field node

byObstructions :: Int -> WeighFunction --Need a better way to get adjacent nodes of depth n!
byObstructions depth field _ node = numObstacles
  where numObstacles = realToFrac . length . getUniqueObstacles $ getAdjacentAtDepth depth node
        getUniqueObstacles = nub . map (getObstaclesWithin field)


rankByDistance :: RankFunction
rankByDistance = rank byDistance

rankByDistanceAndLocalObstructions :: RankFunction
rankByDistanceAndLocalObstructions = rank weighFunc
  where weighFunc = (\f e n -> byDistance f e n / byLocalObstructions f e n)

rankByDistanceAndObstructions :: Int -> RankFunction
rankByDistanceAndObstructions depth = rank weighFunc
  where weighFunc = (\f e n -> byDistance f e n / byObstructions depth f e n)

greedySearch = search rankByDistance []

cautiousGreedySearch = search (rankByDistanceAndLocalObstructions) []

cautiousSearch = search (rankByDistanceAndObstructions 2) []
