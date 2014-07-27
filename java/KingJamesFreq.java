/**
 * Sample program to compare programming languages for my own edification.
 *
 * This program reads the KJV bible (from a fixed location) and computes the
 * word frequency, printing the number of occurrences and frequency of the top
 * 25 words.
 *
 * Current Java version: 1.7
 */

import java.io.*;
import java.util.*;


public class KingJamesFreq
{
    public static final int TOP_N = 25;

    public static void main(String[] args) throws IOException
    {
        Map<String, Integer> freqMap = new HashMap<>();
        try (FileReader fr = new FileReader("../data/kingjames.txt");
             BufferedReader br = new BufferedReader(fr))
        {
            String line;
            while ((line = br.readLine()) != null) {
                addFreqs(line, freqMap);
            }
        }

        printFreqs(freqMap);
    }

    private static void addFreqs(String line, Map<String, Integer> freqMap)
    {
        for (String tok: line.replace("\\s+", " ").toLowerCase().split("\\s+")) {
            Integer current = freqMap.get(tok);
            freqMap.put(tok, current == null ? 1 : current+1);
        }
    }

    private static void printFreqs(Map<String, Integer> freqMap)
    {
        System.out.println(String.format("Top %s words in the King James Bible", TOP_N));

        int totalWords = 0;
        for (Integer freq: freqMap.values()) {
            totalWords += freq;
        }
        System.out.println(String.format(
            "(Total words: %,10d; %,d distinct words", 
            totalWords, freqMap.size()
        ));

        List<Map.Entry<String, Integer>> entries = new ArrayList<>(freqMap.entrySet());

        Collections.sort(entries, new Comparator<Map.Entry<String, Integer>>() {
            @Override public int compare(Map.Entry<String, Integer> e1,
                                         Map.Entry<String, Integer> e2)
            {
                return e2.getValue().compareTo(e1.getValue());
            }
        });
        for (Map.Entry<String, Integer> e: entries.subList(0, TOP_N)) {
            System.out.println(String.format(
                "%-10s %,8d (%,.1f%%", 
                e.getKey(),
                e.getValue(),
                ((double)e.getValue())/totalWords * 100.0
            ));
        }
    }
}
