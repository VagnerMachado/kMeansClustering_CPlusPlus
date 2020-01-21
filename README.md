# kMeansClustering_CPlusPlus
k Means clustering coded in C++

<pre>

<b>Project 7: K means clustering problem
 
Problem statement: Given a list of 2-D points, and a cluster number, K, the task is to partition the input point set to K clusters such that points within a cluster are closer to the centroid of their own cluster than to the centroids of all other clusters. </b>

Summary of what you need to do in this project: 
1. There are two inputs: a binary image and K, the cluster number.
2. Open the input file
3. Read and extract 2D points from the input binary image; 
   and output the extracted 2D points to outFile1.
4. Close outFile1 then, Re-open outFile1
5. Read the 2D points from outFile1 to do the K-means clustering.
6. During the computation, you will output to outFile2 
   the intermediate clustering results, in 2D format.
7. At the end of the clustering, you will write the clustering result 
to outFile3: a list of 2D points with their labels as triplets, one triplet per text line.
	   
**************************************
Language: C++
**************************************
Soft copy due date: 4/5/2019 Friday before Midnight
	Early submission +1 deadline: 4/2/2019 Tuesday before Midnight 
-1 pt due: 4/6/2019 Saturday before midnight
	After 4/6/2019, -12 pts for all students who did not submit soft copy
	Make sure you submit your soft copy to your TA and cc to Dr. Phillips 

Hard copy due date:   4/9/2019 Tuesday in class, 
-1 pt for late hard copy submission on 4/10/2019 Wednesday(under door A218).
All projects without hard copy after 4/10/2019 will receive 0 pts even you have submit soft copy on time and even if it works.
**************************************

I. Inputs: 
- inFile(argv[1]): a txt file representing a binary image with
	Header information (four integers) 
Note: there are spaces between each integer for easy programming!!

For example: 

8 8 0 1  // 8 rows, 8 columns, min value 0 and max value 1
0 0 1 1 1 0 0 0
0 1 1 1 1 0 0 0
0 0 1 1 0 0 0 0
0 0 0 0 0 0 1 1
0 0 0 0 1 1 1 0
0 0 0 0 1 1 1 0
0 0 0 0 1 1 1 0 

- K (argv[2]) the K for K-means clustering

II. Outputs: 
- outFile1 (use argv[3]): This is the file is the result of 
extracting 2D points from the input file.
	
		For example from the image given in the above:
	 
    		0 2  // the none zero pixel is on row 0 and column 2 
     		0 3  // the none zero pixel is on row 0 and column 3 
    		:	
		:
		:
3 6 // the none zero pixel is on row 3 and column 
3 7 // the none zero pixel is on row 3 and column 
    		:	
		:

- outFile2 (use argv[4]): A series of debugging display in 2D format, one per iteration.  The printing format is as follows: if a pixel(i,j) has a label, displays its label, otherwise, display with a blank. 
(You must write the iteration #)

For example (the clustering results of the input in the above):

*** Result of iteration 1 ****
 
    1 1 1      
  1 1 1 2      
    2 2       
          1 2
        1 2 2 
        1 2 2  
        2 2 2 
:
:

*** Result of iteration 4 ****
 
    1 1 1      
  1 1 1 1      
    1 1       
          2 2
        2 2 2 
        2 2 2  
        2 2 2 

IV. outFile3 (use argv[5]): a txt file representing a list of  
2D points and their labels in the following format:
The first text line is the number of data points follows by the list of 2D points’ x-y coordinates and points’ labels. 

		For example:
		20  	// 20 data points  
		8 8  // 8 rows and 8 columns of an image
    		0 2 1 // the pixel is on row 0 and column 2 with label 1
     		0 3 1 // the pixel is on row 0 and column 3 with label 1
    		:	
		:
		:
3 6 2 // the pixel is on row 3 and column 6 with label 2
3 7 2 // the pixel is on row 3 and column 7 with label 2
    		:	
*******************************
IV. Data structure:
*******************************
- A Kmean class
- A Point class:
- Xcoord (int)
- Ycoord (int)
- Label (int)
- Distance (double) the distance to its own cluster centroid.

- K (int) // K clusters 
- numPts (int) // initialize to 0 
	- pointSet[numPts] (Point) // 1D array of Point class
// to be dynamically allocated during run-time
// initially set all points distance to 99999 a large distance
	- numRows (int) 
	- numCols (int)
	- minVal (int)
	- maxVal (int)

	- imgAry (** int) // a 2D array, size of  numRows by numCols

- Kcentroids[](Point) // 1D array of centroid class
// to be dynamically allocated in class constructor, size of K+1
// we do NOT want to use 0 as cluster label so the cluster label
// will run from 1 to K, therefore, the size of array is K+1
// Distance is set to 0.

	- change (int) // for tracking the label changes, initialize to 0

	- constructor (.. )

	- int extract2DPts(inFile, outFile1) // see algorithm below
// read from inFile and write none zero pixel to 
// outFile1.
- loadPointSet (outFile1, pointSet )
// read each point, p, from outFile1 and store it onto
// the pointSet array.
// initially set p’s Distance to 9999.0 a large distance.
// YOUR SHOULD KNOW HOW TO WRITE THIS METHOD! 				
	- assignLabel (pointSet, K)// see algorithm below
//assign each point a label from 1 to K

	- kMeansClustering (pointSet, K) // see algorithm below

	- computeCentroids (pointSet, Kcentroids ) // see algorithm below
	// Go thru the entire pointSet array only  once
// to compute the centroids of each of the K clusters
// Store the computed centroids in each Kcentroids[label], 
// where label is from 1 to K.

	- DistanceMinLable (pointSet[index], Kcentroids) // see algorithm below
// compute the distance from a point p to each of the K centroids.
// check to see if p’s label need to be change or not.

- computeDist(pt, centroid) 
// Compute the distance from pt to centroid.
// YOUR SHOULD KNOW HOW TO WRITE THIS METHOD!

	- writePtSet (pointSet, outFile3)
		// output numPts to outFile3
     // Output numRows and numCols to outFile3
// write each point, p, in pointSet,
// output p’s Xcoord, Ycoord, and Label and to outFile3
// See format in the above.
// YOUR SHOULD KNOW HOW TO WRITE THIS METHOD!

- Point2Image (pointSet, imgAry) // output to outFile2
// read each point, pointSet[i], write the pointSet[i].Label 
// onto the imgAry. 
    // YOUR SHOULD KNOW HOW TO WRITE THIS METHOD!

- prettyPrint (imgAry, outFile2, iteration)
	// write Caption indicating the number of iteration
// write the imgAry to outFile2 as follows:
		// if imgAry(i,j) > 0 
print imgAry(i,j)
else print one blank space.

// YOUR SHOULD KNOW HOW TO WRITE THIS METHOD!

*******************************
V. main (..)
*******************************
Step 0:  
inFile <- Open the input file argv[]
numRows, numCols, minVal, maxVal<- get from inFile.
imgAry <- Dynamically allocate a 2-D arrays, size numRows X numCols.
outFile1, outFile2, outFile3 <- open from argv[3], argv[4], argv[5] 
K <- from argv[2]
Kcentroids[K] <- Dynamically allocate centroids struct, size of K+1

Step 1: numPts <- extractPts (inFile, outFile_1) // see algorithm below.
  pointSet <- Dynamically allocate the pointSet array, size of numPts  	 
 
Step 2: close outFile1
   reopen outFile1

Step 3: loadPointSet (outFile1, pointSet)
Step 4: kMeansClustering (pointSet, K)
Step 5: writePtSet (pointSet, outFile_3)
Step 6: close all files









*******************************
VI. int extractPts(inFile, outFile1)
*******************************	
Step 0: numPts <- 0
	Step 1: read inFile from left to right and top to bottom
		  Use i, j as index for rows and cols bounded by numRows and numCols
    
Step 2: if p(i, j) > 0
			numPts++
                write i and j to outFile1
Step 3: repeat step 1 and step 2 until EOF inFile
	Step 4: return numPts

*******************************
VI. kMeansClustering (pointSet[], K)
*******************************
Step 0: iteration <- 0
Step 1: assignLable (pointSet, K) // see algorithm below.
Step 2: Point2Image (pointSet, imgAry) 
   printImage (imgAry, outFile2, iteration) 
Step 3: change <- 0
Step 4: computeCentroids (pointSet, Kcentroids) // see algorithm below
Step 5: index <- 0
Step 6: DistanceMinLable (pointSet[index], Kcentroids) 
// see algorithm below
Step 7: index ++ 
Step 8: repeat step 6 to step 7 while index < numPts
Step 9: iteration++
Step 10: repeat step 2 to step 9 until change <= 0

*******************************
VIIII. assignLabel (pointSet, K)
*******************************
Step 0: front <- 0
	  back <- numPts – 1
	  label <- 1

Step 1: pointSet[front]’s label <- label
	   front ++
	   label++
Step 2:  pointSet[back]’s label <- label
	   Back --
	   label++
   
Step 3: if label > K
         label <-1

Step 4: repeat step 1 to step 3 while front <= back






*******************************
VII. computeCentroids (pointSet[], Kcentroids[] ) 
*******************************
Step 0: sumX[] <- dynamically allocate 1-D array, size of K+1
   sumY[] <- dynamically allocate 1-D array, size of K+1
   totalPt[] <- dynamically allocate 1-D array, size of K+1
		// initialize the above 3 1D arrays to 0
 
Step 1: index <- 0
Step 2: label <- pointSet[index].label // get the point’s cluster label
	sumX[label] += pointSet[index].Xcoord
  	sumY[label] += pointSet[index].Ycoord
	totalPt[label] ++

Step 3: index++
Step 4: repeat step 2 to step 3 while index < numPts
step 5: label <- 1
step 6: Kcentroids[label].Xcoord <- (int) (sumX[label]/ totalPt[label]) 
	   Kcentroids[label].Ycoord <- (int) (sumY[label]/ totalPt[label])
Step 7: label ++
Step 8: repeat step 6 to step 7 while label <= K



*******************************
VIII. DistanceMinLable (p, Kcentroids[])
*******************************
Step 0: minDist <- 99999
	  minLabel <- 0
Step 1: label <- 1
Step 2: dist <- computeDist(p, Kcentroids[label])
	   if dist < minDist
            minLabel <- label
		 minDist <-dist
Step 3: label ++
Step 4: repeat step 2 to step 3 while label <= K
Step 5: if p’s Label != minLabel 
		p’s Label <- minLabel
p’s Distance <- minDist
		change++



	
</pre>
