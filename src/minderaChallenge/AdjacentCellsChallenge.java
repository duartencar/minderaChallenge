package minderaChallenge;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.Collections;

public class AdjacentCellsChallenge {
	
	private static ArrayList<ArrayList<Character>> grid = new ArrayList<ArrayList<Character>>();
	private static boolean[][] visitedCells;
	private static Integer[] coordinates = new Integer[2];
	private static ArrayList<Integer[]> exploredCells = new ArrayList<Integer[]>();
	private static ArrayList<ArrayList<Integer[]>> groups = new ArrayList<ArrayList<Integer[]>>();
	private static boolean exploring = false;
	
	

	public static void main(String[] args) {
		
		long startTime = System.currentTimeMillis();
		
		try {
			processFile("10000x10000.json");
		} catch (IOException e) {
			System.out.println(e.getMessage());
		}
		
		long endTime = System.currentTimeMillis();

		long duration = (endTime - startTime);
		
		System.out.println("Read " + grid.size() * grid.get(0).size() + " grid elements in " + 1.0 * duration / 1000 + " seconds.");
			
		updateVisited();
		
		startTime = System.currentTimeMillis();
		findGroups();
		endTime = System.currentTimeMillis();
		
		duration = (endTime - startTime);
		
		System.out.println("Gathered groups in " + 1.0 * duration / 1000 + " seconds.");
		
		//printGroups();
	}
	
	private static void findGroups() {
		
		for(int y = 0; y < grid.size(); y++) {
			for(int x = 0; x < grid.get(0).size(); x++) {
				
				if(!visitedCells[y][x] && grid.get(y).get(x) == '1') {
					exploring = true;
					explore(y,x);
					
					if(exploredCells.size() > 1) {
						groups.add((ArrayList<Integer[]>) exploredCells.clone());
					}
					
					exploredCells.clear();
					
					exploring = false;
				}
			}
		}
	}
	
	private static void printCoord(Integer[] coords) {
		System.out.format("[%d,%d]", coords[0], coords[1]);
	}
	
	private static void printGroup(int groupIndex) {
		
		System.out.print("[ ");
		
		for(int i = 0; i < groups.get(groupIndex).size(); i++) {
			printCoord(groups.get(groupIndex).get(i));
			
			if(i != groups.get(groupIndex).size() - 1) {
				System.out.print(", ");
			}
		}
		
		System.out.print(" ]\n");
	}
	
	private static void printGroups() {
		
		for(int i = 0; i < groups.size(); i++) {
			Collections.reverse(groups.get(i));
			printGroup(i);
		}
	}
	
	private static void explore(int y, int x) {
		visitedCells[y][x] = true;
		
		boolean hasNeighboor = false;
		
		if(y+1 < grid.size() && grid.get(y+1).get(x) == '1') {
			if(!visitedCells[y+1][x]) {
				explore(y+1, x);
			}
			
			hasNeighboor = true;
		}
		if(y-1 > 0 && grid.get(y-1).get(x) == '1') {
			if(!visitedCells[y-1][x]) {
				explore(y-1, x);
			}
			
			hasNeighboor = true;
		}
		if(x-1 > 0 && grid.get(y).get(x-1) == '1') {
			if(!visitedCells[y][x-1]) {
				explore(y, x-1);
			}
			
			hasNeighboor = true;
		}
		if(x+1 < grid.get(y).size() && grid.get(y).get(x+1) == '1') {
			if(!visitedCells[y][x+1]) {
				explore(y, x+1);
			}
			
			hasNeighboor = true;
		}
		
		if(hasNeighboor) {
			coordinates[0] = y;
			coordinates[1] = x;
			exploredCells.add(coordinates.clone());
		}
	}
	
	
	private static void updateVisited() {
		visitedCells = new boolean [grid.size()][grid.get(0).size()];
		
		for(boolean[] line : visitedCells) {
			for(boolean element : line) {
				element = false;
			}
		}
	}
	
	private static void processFile(String fileName) throws IOException {
		
		ArrayList<String> fileContent = readFile(fileName);
		
		while(!fileContent.isEmpty()) {			
			processLine(fileContent.get(0));
			fileContent.remove(0);
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
