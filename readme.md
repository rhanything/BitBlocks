# BIT BLOCKS!
 *ACADEMIC SFML/C++ GAME*

This is an academic project of a game developed using basic concurrently programming concepts with c++ and SFML lib.


# How to run

 - Windows:<br/>

 -->First, you should to makes [download of SFML Lib](https://www.sfml-dev.org/download/sfml/2.3.2/); <br/>
 -->After, open solution file and [configure (like this link)](https://www.sfml-dev.org/tutorials/2.5/start-cb.php) the project build settings on [CodeBlocks](http://www.codeblocks.org/downloads) IDE; <br/>
 --> Make build/run; <br/>
<br/>
 - Linux:
 
	Install gcc and dev tools : <br/>
	<code>$ sudo apt-get update</code>  <br/>
	<code>$ sudo apt-get install build-essential manpages-dev</code> <br/>
	
	Install SFML lib: <br/>
	 <code>$ sudo apt-get install libsfml-dev</code> <br/>
	 
	 Clone this project in your workspace and enter in directory <br/>
	<code>$ git clone [project-link]</code> <br/>
	<code>$ cd  BitBlocks/</code> <br/>
	
	Compile and run project: <br/>
	<code>$ g++ -c BitBlocks3/*.cpp -std=c++11</code> <br/>
	<code>$ g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system Edge.o GamePhysics.o GameScreen.o GameStatus.o Player.o Timer.o</code>  <br/>
	<code>$ ./sfml-app</code> <br/>
    <br />
    obs.: To restart when game's over, press spacebar.

```
