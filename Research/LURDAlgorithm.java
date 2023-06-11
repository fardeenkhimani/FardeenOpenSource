/**
 * This Algorithm qucikly and efficiently finds the nearest 1 to a given 0 in a 2D array
 * of 1's and 0's.
 *
 * A is the 2D obstacle array map, x and y are the x and y coordinates of the Target "0"
 *
 * To use the algorithm, enter your 2D array in which you want to search, as well as the
 * row and column of the 0 or "target" for which you want to find the nearest 1 in you array
 *
 * Here's an example:
 *
 * If your array looks like this:
 * 			0	0	0	0	0	0
 * 			0	0	1	1	1	0
 * 			0	1	1	1	1	0
 * 			0	1	1	1	0	0
 * 			0	0	1  [1]	0	0
 * 			0	0	0	0  [T]	0
 *
 * 	The nearest 1 to your chosen 0 or "T"
 * 	is the one in the 4th row and 3rd column
 *
 * 	Bigger Picture:
 * 	This algorithm's application is used to find the distance
 * 	of a human to a convex surface or obstacle quickly.
 * 	You can imagine if a drone was flying overhead a soldier and
 * 	wanted to label buildings and other soldiers' as 1's and the soldier
 * 	as the chosen 0 or "T/Target", it would need a algorithm to quickly calculate
 * 	the soldier's distance to all of his/her surrounding obstacles.
 *
 *
 * */
import java.lang.Math;

public class LURDAlgo {
	static int i = 0;
	static int j = 0;
	static int x;
	static int y;
	static int[][] array;
	static double distance;
	static double newDistance;
	static String answer;
	static boolean checkEnd = false;
	static boolean malLeft = false;
	static boolean malUp = false;
	static boolean malRight = false;
	static boolean malDown = false;
	static int finishCounter = 0;

	public static String lurd(int arr[][], int row, int col) {
		x = row;
		y = col;
		array = arr;
		//indexing into the leftmost, uppermost 1:
		while (array[i][j] != 1) {
			if (i < array.length-1) {
				i++;
			} else {
				j++;
				i = 0;
			}
		}
		distance = Math.pow(Math.pow((x-i),2) + Math.pow((y-j),2),(0.5));

		for (int z = 0; z < (array.length) * (array[0].length); z++) {
			if (checkEnd) {
				return answer;
			} else {
				if (!malLeft) {
					left();
					//System.out.println(j);
				} if (!malUp) {
					up();
					//System.out.println(i);
				} if (!malRight) {
					right();
					//System.out.println(i);
				} if (!malDown) {
					down();
					//System.out.println(i);
				}
				//System.out.println(i);
				answer = checkEnd();


			}

			//System.out.println(finishCounter);
		}
		return "not found";
	}

		//LURD Algorithm:


		static void left() {
			newDistance = Math.pow(Math.pow((x-(i-1)),2) + Math.pow((y-j),2),(0.5));
			//System.out.println(j);
			//System.out.println(newDistance);
			if (array[i-1][j] == 0 || i-1 < 0) {
				;

			} else if (newDistance > distance) {
				malLeft = true;
			} else {
				distance = newDistance;
				finishCounter += 1;
				i = i-1;
			}




		}


		static void up() {

				newDistance = Math.pow(Math.pow((x-(i)),2) + Math.pow((y-(j-1)),2),(0.5));
				if (array[i][j-1] == 0 || j-1 < 0) {
					;
				} else if (newDistance > distance) {
					malUp = true;

				} else {
					distance = newDistance;
					finishCounter += 1;
					j = j-1;

				}




		}

		static void right() {

				newDistance = Math.pow(Math.pow((x-(i+1)),2) + Math.pow((y-j),2),(0.5));
				if (array[i+1][j] == 0 || i+1 > array.length -1 ) {
					;
				} else if (newDistance > distance) {
						malRight = true;

				} else {
						distance = newDistance;
						finishCounter += 1;
						i = i+1;

				}



		}
		static void down() {

				newDistance = Math.pow(Math.pow((x-(i)),2) + Math.pow((y-(j+1)),2),(0.5));
				if (array[i][j+1] == 0 || j+1 > array[0].length - 1) {
					;
				} else if (newDistance > distance) {
						malDown = true;

				} else {
						distance = newDistance;
						finishCounter += 1;
						j = j+1;

				}



		}
		static String checkEnd() {
			boolean leftCheck =  false;
			boolean rightCheck =  false;
			boolean downCheck = false;
			boolean upCheck = false;
			//System.out.println(i);

			if (Math.pow(Math.pow((x-(i-1)),2) + Math.pow((y-j),2),(0.5)) > distance || array[i-1][j] == 0 || i < 0) {
				leftCheck = true;
			}
			if (Math.pow(Math.pow((x-(i)),2) + Math.pow((y-(j-1)),2),(0.5)) > distance || array[i][j-1] == 0 || j < 0) {
				upCheck = true;
			}
			if (Math.pow(Math.pow((x-(i+1)),2) + Math.pow((y-j),2),(0.5)) > distance || array[i+1][j] == 0 || i > array.length - 1) {
				rightCheck = true;
			}
			if (Math.pow(Math.pow((x-(i)),2) + Math.pow((y-(j+1)),2),(0.5)) > distance || array[i][j+1] == 0 || j > array[0].length - 1) {
				downCheck = true;
			}
			if (leftCheck && upCheck && rightCheck && downCheck) {
				checkEnd = true;
				return "row = "+i+", column = "+j+" (0 indexed)";
			} else {
				return " ";
			}
			//return 0;
		}




	//For Public Algo Use:
	public static void main(String args[]) {
		// 0 0 0 0
		// 0 1 1 1
		// 0 1 0 0
		// 0 1 1 0
		// 0 0 0 0
		int Arr[][] = {{0,0,0,0},
					   {0,1,1,1},
					   {0,1,0,0},
					   {0,1,0,0},
					   {0,0,0,0}};

		String ans = lurd(Arr, 4, 3);
		System.out.println(ans);
		System.out.println("Distance from Target to Nearest 1: " + distance);


	}

}
