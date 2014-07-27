import System.IO     


main = do
    putStrLn $ show $ take 100 [x | x <- [2..], isPrime x]

isPrime :: Int -> Bool
isPrime x = not $ any (\y -> x `mod` y == 0) lst
            where lst = 2 : [3,5..ceiling $ toRational (sqrt $ fromIntegral x)] 
