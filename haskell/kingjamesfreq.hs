-- Sample program to compare programming languages for my own edification.
-- 
-- This program reads the KJV bible (from a fixed location) and computes the
-- word frequency, printing the number of occurrences and frequency of the top
-- 25 words.

import qualified Data.Map as Map  
import Data.Char
import Data.List
import System.IO     
    
main = do     
    contents <- readFile "../data/kingjames.txt"
    oFreqList $ Map.toList (calcFreqs (words contents))
    return 1

calcFreqs :: [String] -> Map.Map String Int
calcFreqs words = foldl' (\acc word -> incFreq word acc) Map.empty words

incFreq :: String -> Map.Map String Int -> Map.Map String Int
incFreq word freqMap = Map.insertWith (+) (map toLower word) 1 freqMap

oFreqList :: [(String, Int)] -> IO ()
oFreqList lst = do
    let totalWords = sum $ map snd lst
    mapM_ (oFreq totalWords) (take 25 $ sortBy (\a b -> compare (snd b) (snd a)) lst) 

oFreq :: Int -> (String, Int) -> IO ()
oFreq totalWords (fWord, freq) = do
    putStrLn $ fWord ++ " " ++ show freq ++ " " ++ show (fromIntegral(freq) / fromIntegral(totalWords) * 100.0)
