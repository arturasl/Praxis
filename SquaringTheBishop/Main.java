// http://programmingpraxis.com/2011/05/03/squaring-the-bishop/
// dictionary from: http://icon.shef.ac.uk/Moby/mwords.html

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;
import java.util.Collections;


class Trie {
    class TrieData {
        private TrieData[] nextData = new TrieData['Z' - 'A' + 1];
        private String strWord = null;

        public boolean isEnd() {
            return strWord != null;
        }
        public String getWord() {
            return strWord;
        }
        public void setEnd(String str) {
            strWord = str;
        }
        public TrieData getDataAt(int nPos) {
            return nextData[nPos];
        }
        public void insertDataAt(int nPos, TrieData data) {
            nextData[nPos] = data;
        }
    }

    TrieData first = new TrieData();

    public void Add(String str) {
        TrieData tmp = first;
        str = str.toUpperCase().trim();
        int nPos = 0;

        for (int i = 0; i < str.length(); ++i) {
            nPos = str.charAt(i) - 'A';

            if (tmp.getDataAt(nPos) == null) {
                tmp.insertDataAt(nPos, new TrieData());
            }

            tmp = tmp.getDataAt(nPos);
        }

        tmp.setEnd(str);
    }

    public List<String> getAllStartingWith(TrieData data) {
        List<String> lstItems = new LinkedList<String>();
        List<TrieData> lstStack = new LinkedList<TrieData>();
        TrieData tmp = null;

        lstStack.add(data);

        if (data == null) {
            return lstItems;
        }

        while (!lstStack.isEmpty()) {
            tmp = lstStack.remove(0);

            if (tmp.isEnd()) {
                lstItems.add(tmp.getWord());
            }

            for (int i = 0; i < 'Z' - 'A' + 1; ++i) {
                if (tmp.getDataAt(i) != null) {
                    lstStack.add(tmp.getDataAt(i));
                }
            }
        }

        return lstItems;
    }

    public TrieData findWithPrefix(String strPrefix) {
        TrieData tmp = first;

        strPrefix = strPrefix.toUpperCase().trim();

        int nPos = 0;

        for (int i = 0; i < strPrefix.length(); ++i) {
            nPos = strPrefix.charAt(i) - 'A';

            if (tmp.getDataAt(nPos) == null) {
                return null;
            }

            tmp = tmp.getDataAt(nPos);
        }

        return tmp;
    }
}

class StringSquare {
    private String[] square;
    private int nMaxRow = 0;

    StringSquare(int nRows) {
        square = new String[nRows];
    }

    public String getStringAt(int nRow) {
        return square[nRow];
    }
    public void appendString(String str) {
        square[nMaxRow++] = str;
    }
    public int getFilledSize() {
        return nMaxRow;
    }
    @Override
    public String toString() {
        if (getFilledSize() == 0) {
            return "";
        }

        String strReturn = "[ " + square[0];

        for (int i = 1; i < getFilledSize(); ++i) {
            strReturn += ", " + square[i];
        }

        return strReturn + " ]";
    }
}

public class Main {
    public static void main(String [] args) throws Exception {
        String strMakeSquareFor = args[0].toUpperCase().trim();

        BufferedReader reader = new BufferedReader(new FileReader(new File("113809of.fic")));
        String strLine = null;
        Trie trie = new Trie();

        while ((strLine = reader.readLine()) != null) {
            if (strLine.length() == strMakeSquareFor.length()) {
                trie.Add(strLine);
            }
        }

        reader.close();
        LinkedList<StringSquare> lstMain = new LinkedList<StringSquare>();
        LinkedList<StringSquare> lstSecondary = null;

        StringSquare squareTmp = new StringSquare(strMakeSquareFor.length());
        squareTmp.appendString(strMakeSquareFor);
        lstMain.add(squareTmp);

        String strPrefix = null;

        for (int i = 1; i <= strMakeSquareFor.length() - 1; ++i) {
            lstSecondary = new LinkedList<StringSquare>();

            for (StringSquare squareCurrent : lstMain) {
                strPrefix = "";

                for (int j = 0; j < i; ++j) {
                    strPrefix += squareCurrent.getStringAt(j).charAt(i);
                }

                for (String str : trie.getAllStartingWith(trie.findWithPrefix(strPrefix))) {
                    squareTmp = new StringSquare(strMakeSquareFor.length());

                    for (int k = 0; k < squareCurrent.getFilledSize(); ++k) {
                        squareTmp.appendString(squareCurrent.getStringAt(k));
                    }

                    squareTmp.appendString(str);
                    lstSecondary.add(squareTmp);
                }
            }

            lstMain = lstSecondary;
        }

        System.out.println(lstMain.toString());
        System.out.println(lstMain.size());
    }
}
