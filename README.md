Movie Database Management System
================================

Overview
--------

This project implements a specialized dictionary for managing user-specific data on watched films. The primary data structure utilized is a trie, comprising binary trees, to efficiently organize user IDs. Each user ID in the trie points to a Binary Search Tree (BST), which stores the watched movies associated with that user. The project is structured in two phases: the Trie manages user IDs, and the BSTs associated with each Trie node store the watched movies for individual users.

Specialized Two-Phase Structure
-------------------------------

The project follows a specialized two-phase structure:

1.  **Trie Phase:** Manages and organizes user IDs efficiently.
2.  **BST Phase:** Organizes and retrieves watched movies for individual users.

Trie Class
----------

### TrieNode

Represents a node in the trie with an array of children, a character (keyChar), a flag for the end of a key (isEndOfKey), and a pointer to associated data (data). Supports up to 128 children to accommodate alphanumeric characters.

### Trie Methods

1.  `Trie()`: Initializes a new trie with a root node.
2.  `~Trie()`: Destructor for proper memory cleanup.
3.  `void findStartingWith(std::string prefix, std::vector<T*> &results)`: Efficient search for keys starting with a specified prefix.
4.  `void wildcardSearch(const std::string &wildcardKey, std::vector<T*> &results)`: Search for keys matching a wildcard pattern.
5.  `T* search(std::string username)`: Searches for a specific key (username) in the trie.
6.  `Trie &insert(const string &username)`: Inserts a new key (username) into the trie.
7.  `void remove(std::string username)`: Removes a specific key (username) from the trie.
8.  `void print(const std::string &primaryKey)`: Prints the entire trie or specific keys.
9.  `void deleteTrieNode(TrieNode* node)`: Recursive function for proper memory cleanup.

BST Class
---------

### TreeNode

Represents a node in the Binary Search Tree (BST) with a key, associated data, and pointers to left and right child nodes.

### BST Methods

1.  `BST()`: Default constructor.
2.  `~BST()`: Destructor for resource cleanup.
3.  `TreeNode* getRoot()`: Returns a pointer to the root node.
4.  `bool isEmpty()`: Checks if the tree is empty.
5.  `BST& insert(const std::string key, const T& value)`: Inserts a new node with key and value.
6.  `bool search(std::string key) const`: Searches for a node with a specified key.
7.  `void remove(std::string key)`: Removes a node with a specified key.
8.  `BST<T>* merge(BST<T>* bst)`: Merges nodes from two BSTs into a new BST.
9.  `BST<T>* intersection(BST<T>* bst)`: Creates a new BST representing the intersection of two BSTs.
10.  `std::vector<TreeNode> tree2vector(TreeNode* root)`: Converts BST nodes into a vector.
11.  `void print()`: Displays the tree nodes hierarchically.

Movie Class
-----------

Represents a movie with attributes such as movie name, year, and rating.

### Movie Methods

1.  `Movie()`: Default constructor, initializes with default values.
2.  `Movie(std::string movieName, int year, float rating)`: Constructor with provided values.
3.  `Movie(const Movie& movie)`: Copy constructor for creating a new Movie object from an existing one.
4.  `std::string getMovieName() const`: Getter for movie name.
5.  `int getYear() const`: Getter for movie year.
6.  `float getRating() const`: Getter for movie rating.
7.  `bool operator==(const Movie &obj)`: Equality comparison for movies.

User Class
----------

Represents a user with a username and a Binary Search Tree (BST) to store watched movies.

### User Methods

1.  `User()`: Default constructor, initializes with an empty username and an empty BST for movies.
2.  `User(std::string username)`: Constructor with a provided username, initializes with an empty BST for movies.
3.  `std::string getUsername()`: Getter for the username.
4.  `BST<Movie>* getMovies()`: Getter for the BST storing watched movies.
5.  `void addMovie(std::string movieName, Movie movie)`: Adds a movie to the user's collection.
6.  `void removeMovie(Movie movie)`: Removes a movie from the user's collection.
7.  `void searchMovie(Movie movie)`: Searches for a movie in the user's collection.
8.  `void printMovies()`: Prints the movies in the user's collection.
9.  `BST<Movie>* merge(BST<Movie> bst)`: Merges movies with another BST into a new BST.
10.  `BST<Movie>* intersection(BST<Movie> bst)`: Calculates the intersection of movies with another BST.

UserInterface Class And Usage
-------------------

Manages user interactions and provides methods to add/remove users, add/remove watched movies, find users, and more.

### UserInterface Methods

1.  `void addUser(std::string username)`: Inserts a new user with the given username into the trie data structure.
```cpp
`UserInterface ui; ui.addUser("alice_smith");`
```
2.  `void removeUser(std::string username)`: Removes a user with a given username from the collection.
```cpp
`ui.removeUser("bob_jones");`
```
3.  `void addWatchedMovie(std::string username, Movie movie)`: Adds a watched movie to a user identified by the given username.
```cpp
`ui.addWatchedMovie("alice_smith", watchedMovie);`
```
4.  `void removeWatchedMovie(std::string username, Movie movie)`: Removes a specified movie from a user's watched list.
```cpp
ui.removeWatchedMovie("alice_smith", movieToRemove);
```
5.  `User* findUser(std::string username)`: Locates and returns a User object based on a specified username.
```cpp
User* requestedUser = ui.findUsersStartingWith("al");`
```
6.  `BST<Movie>* getWatchedMovies(std::string username)`: Returns a BST containing the movies watched by a user.
```cpp
BST<Movie>* watchedMovies = ui.getWatchedMovies("alice_smith");
```
7.  `BST<Movie>* mergeWatchedMovies(std::string username1, std::string username2)`: Merges movies of two users into a new BST.
```cpp
BST<Movie>* mergedMovies = ui.mergeWatchedMovies("alice_smith", "bob_jones");
```
8.  `BST<Movie>* intersectionWatchedMovies(std::string username1, std::string username2)`: Calculates the intersection of watched movies between two users.
```cpp
BST<Movie>* intersectionMovies = ui.intersectionWatchedMovies("alice_smith", "bob_jones");
```
9.  `std::vector<User> findUsersStartingWith(std::string prefix)`: Searches for users with usernames starting with a specified prefix.
10.  `std::vector<User> findUsersContains(std::string infix)`: Locates users with usernames containing a specified infix.
11.  `std::vector<User> findUsersEndingWith(std::string suffix)`: Locates users with usernames ending in a specified suffix.
```cpp
// Prefix Search
std::vector<User> foundUsersPrefix = ui.findUsersStartingWith("al");

// Infix Search
std::vector<User> foundUsersInfix = ui.findUsersContains("ice")

// Suffix Search
std::vector<User> foundUsersSuffix = ui.findUsersEndingWith("smith")
```
12.  `void printUsers()`: Prints details of all users managed by the collection.
```cpp
ui.printUsers()
```
13.  `void printWatchedMovies(std::string username)`: Displays the watched movies of a specific user identified by their username.
```cpp
ui.printWatchedMovies("alice_smith")
```
