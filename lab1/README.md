# Windows Programming Laboratory Work #1

2	[Initial version](https://github.com/TUM-FAF/WP/tree/master/lab%231).
3	
4	## Title
5	Window. Window handling. Basic window’s form elements
6	
7	## Contents
8	* Win32 API
9	* GIT
10	* Window
11	* Button
12	* Text Input
13	* Text
14	
15	## Prerequisites
16	
17	### IDE and compiler
18	You can use whatever IDE/Text editor/CLI you want, but you'll have to write code by your own.
19	I recommend [CodeBlocks](http://www.codeblocks.org/) as it is cross platform, has a version which contains a compiler, and is less tempting to try drag-n-drop features.
20	
21	#### If you chose CodeBlocks, here is how you start a project with it:
22	* Download. Better choose a version which has compiler. Also it is a good idea to take last stable version (12.11), but it is not mandatory as 8.X is also good one.
23	* Install. After installation it will ask you to choose a default compiler. Do it wisely.
24	* File -> New -> Project -> Win32 GUI project -> Next...
25	* In order to see only GUI window without console, in Project properties, set Build targets -> Type -> GUI Application (project may need a rebuild)
26	
27	#### Using VCS (GIT or SVN) and GitHub
28	You should be familiar with GIT, if not then take a look at [IDE Lab nr.1](https://github.com/TUM-FAF/IDE/blob/master/MIDPS_LAB_1.md).
29	
30	Main purposes of GIT/GitHub are:
31	* Proof of your work
32	* Analyzing your progress and understanding of course
33	* Safe place to keep your work
34	* Delimiting development and ready work
35	
36	By default you have one branch - master. I'll review only work from that branch.
37	
38	Initially master branch should have two files: .gitignore and README.md.
39	* I recommend to copy .gitignore file from [WP Labs master branch](https://github.com/TUM-FAF/WP). Add additional rules in order not to submit unnecessary files to repository.
40	* README.md (can be any other flavoured by GitHub extension) should contain at least the name of course and your name.
41	
42	Later you'll have one folder per laboratory work. Use **lab#X** format (where X is laboratory work number). More about this you can find on [Submission Process page](https://github.com/TUM-FAF/WP/wiki/Submission-Process).
43	
44	Before submission you can use other branches to work on your projects. You can use other branches in order to require help from me or other classmates.
45	
46	### Laboratory work Requirements:
47	  - for _Basic Level_ (grade 5 || 6) you should be able to:
48	    * Create a Windows application
49	    * In the middle of the window should be present the following text: "Done with Pride and Prejudice by student name". Replace student name with your name.
50	    * On windows resize, text should reflow and be in window's middle (vertically and horizontally)
51	  - for _Normal Level_ (grade 7 || 8) you should be able to:
52	    * Realize the tasks from _Basic Level_.
53	    * Add 2 buttons to window: one with default styles, one with custom styles (size, background, text color, font family/size)
54	    * Add 2 text elements to window: one with default styles, one with custom styles (size, background, text color, font family/size)
55	  - for _Advanced Level_ (grade 9 || 10) you should be able to:
56	    * Realize the tasks from _Normal Level_.
57	    * Make elements to interact or change other elements (2 different interactions)  _(ex. on button click, change text element color or position)_
58	    * Change behavior of different window actions (at least 3). For ex.: on clicking close button, move window to a random location on display working space 

60	## References
61	* Programming Windows by Charlez Petzold, 5th edition:
62	  * Section I, Chapter 1
63	  * Section I, Chapter 2
64	  * Section I, Chapter 3
65	  * Section I, Chapter 4
66	  * Section I, Chapter 9
