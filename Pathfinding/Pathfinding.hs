import Data.List
import Text
import Search

--Create a field with an object in the center and print it to the screen
test_field = Field [(Object 'c' (3, 3))] 10 10

fieldInsert :: Field -> [Object] -> Field
fieldInsert (Field objects w h) objects'= (Field (objects ++ objects') w h)

main = do
    let path = map (Object 'g') (cautiousSearch test_field (5, 0) (6, 6))
    let field = fieldInsert test_field path
    print field
