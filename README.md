# CSC212-Project
## Project Summary
Our project utilized sparse matrices using a linked list representation in order to create a recommendation system with a collaborative filtering algorithm. Using a linked list representation of the sparse matrices, we were able to traverse through large data files due to their high sparsity (many zero-valued elements). These data files were representative of real world user input that recommendation systems regularly take in, such as where the system must take into account that not all users have reviewed all the products. Thanks to the efficiency of the linked list representation, we were able to solely focus on the non-zero valued elements by linking each non-zero element location using nodes in order to jump over the zero-valued elements. 

When implementing our recommendation system, we chose to focus on the different average scores of each form of media and cross referenced different user preferences in order to return a valid media recommendation. Each data file contained different movies or tv shows along with users' ratings of each show (1-5). If a user does not rate a show, it means that they have not seen it and therefore it is represented by a zero. Each movie and tv show has their average score calculated from the column of user scores, with each zero rating being skipped over so we do not take in the void rating. We run this multiple times to find the top rating score, along with also finding the lowest average rating score. Using these recommendations, we can connect which shows multiple users all watched and enjoyed. Our recommendation function uses the user's inputs on shows to return the user other shows that are similar to the one they had inputted. This function cross references which users rated which shows highly, so they are more likely to enjoy the same media. The output will return three shows that users that liked their initial show also liked due to their high ratings. 
## Main.cpp Compilation Instructions
- 1. Compile main.cpp, sp_matrix.cpp (e.g g++ main.cpp sp_matrix.cpp)
  2. Run the file with file names in command line arguments (e.g ./sp_matrix test.txt test_2.txt test_3.txt test_4.txt)
  3. each of the files is for a different reason (Files 1 & 2 are for addition and 3 & 4 are for multiplication)
  4. In the file there are multiple std::cin statements to break up the code. Use anything other than a space to get past these.
## Rec_main.cpp Compilation Instructions
- 1. Compile rec_main.cpp, sp_matrix.cpp (e.g g++ main.cpp sp_matrix.cpp)
  2. Run the file with mode and file name in command line arguments (e.g ./sp_matrix 1 test.txt)
  3. Modes are:
     - 1-Print out the data
     - 2-Find the Highest and Lowest Rated Shows
     - 3-Get recommendations based off a liked Show
     - 4-Output a Sparse Matrix to a csv
     - 5-Output a Dense Matrix to a csv
