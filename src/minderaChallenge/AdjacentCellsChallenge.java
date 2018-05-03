package minderaChallenge;
import java.awt.GridBagConstraints;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.lang.reflect.Field;
import java.util.ArrayList;

import org.json.*;

public class AdjacentCellsChallenge {
	
	private static ArrayList<ArrayList<Character>> grid = new ArrayList<ArrayList<Character>>();
	private boolean[][] visitedCells;
	
	

	public static void main(String[] args) {
		
		
		try {
			processFile("100x100.json");
		} catch (IOException e) {
			System.out.println(e.getMessage());
		}
		
		for(ArrayList<Character> list : grid) {
			for(Character c: list) {
				System.out.print(c);
			}
			
			System.out.print('\n');
		}
			
	}
	
	private static void processFile(String fileName) throws IOException {
		
		ArrayList<String> fileContent = readFile(fileName);
		
		for(String content: fileContent) {			
			processLine(content);
		}
	}
	
		
	private static ArrayList<String> readFile(String fileName) throws IOException {
		ArrayList<String> fileLines = new ArrayList<String>();
		
		String line = new String();
		
		BufferedReader reader = new BufferedReader(new FileReader ("./resources/" + fileName));
		
		try {
			while((line = reader.readLine()) != null) {
				fileLines.add(line);
			}
		} finally {
			reader.close();
		}
		
		fileLines.remove(0);
		
		fileLines.remove(fileLines.size() - 1);
		
		return fileLines;
	}
	
	private static void processLine(String line) {
		
		Field field = null;;
		
		try {
			field = String.class.getDeclaredField("value");
		} catch (NoSuchFieldException | SecurityException e) {
			System.out.println(e.getMessage());
		}
	   
		field.setAccessible(true);
		
		ArrayList<Character> lineChars = new ArrayList<Character>();

		try {
			final char[] chars = (char[]) field.get(line);
	       
			final int len = chars.length;
	       
			for (int i = 0; i < len; i++) {
				if (chars[i] == '1' || chars[i] == '0') {
					lineChars.add(chars[i]);
				}
			}
			
			grid.add(lineChars);
	       
		} catch (Exception ex) {
			throw new RuntimeException(ex);
		}
	}
	

}
