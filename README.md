    ██╗███╗   ██╗███████╗███████╗ ██████╗██████╗  ██████╗ ██╗     ██╗     
    ██║████╗  ██║██╔════╝██╔════╝██╔════╝██╔══██╗██╔═══██╗██║     ██║     
    ██║██╔██╗ ██║█████╗  ███████╗██║     ██████╔╝██║   ██║██║     ██║     
    ██║██║╚██╗██║██╔══╝  ╚════██║██║     ██╔══██╗██║   ██║██║     ██║     
    ██║██║ ╚████║██║     ███████║╚██████╗██║  ██║╚██████╔╝███████╗███████╗
    ╚═╝╚═╝  ╚═══╝╚═╝     ╚══════╝ ╚═════╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚══════╝
                                                                      
    			 ██████╗ ██████╗ ███╗   ███╗██╗ ██████╗                               
    			██╔════╝██╔═══██╗████╗ ████║██║██╔════╝                               
    			██║     ██║   ██║██╔████╔██║██║██║                                    
    			██║     ██║   ██║██║╚██╔╝██║██║██║                                    
    			╚██████╗╚██████╔╝██║ ╚═╝ ██║██║╚██████╗                               
    			 ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚═╝ ╚═════╝  by Sourec                           
Amazing ASCII art courtesy of http://patorjk.com/software/taag/
(as if I could make something like this on my own!)

##About
Infscroll-Comic is a lightweight graphics application that allows for
multiple panels to be stiched together in any way that the comic
author chooses. The reader can then navigate through the panels using
the transitions that the author specifies. When you hit an arrow key
to transition to another panel, Inf-scroll-Comic will automatically
transition to the designated panel while automatically handeling for
zoom.

##Instructions
Place the Infscroll-Comic executable in the comic resource directory.
Comic resources typically include a file titled "Comic.xml" and a
a series of images (individual panels), which may or may not be in
a folder (the comic author configures this). If a window pops up and
quickly disappears, you either set the files up wrong (check sysLog.txt)
or the comic author has done something wrong (sned sysLog.txt to
him/her). A sample comic has already been prepared with a pre-written
Comic.xml and a few images from XKCD time and a picture of Tux, to
demonstrate scaling.

If the window pops up and there's an image on the screen, 
congratulations! It worked! You can now navigate through the comic. 
Press the arrow keys and see what happens! Anything that happens from 
here on out is a result of what the comic AUTHOR has done. The author 
can make comics that loop, go back and forth, zoom to incredible levels, 
or are just a straight line. There's also a (very) experimental
fullscreen feature that can be toggled by pressing 'F'. 

##Making your own comic
Making your own comic is as easy as writing to a regular text document.
This guide assumes you already have all the panels for your comic
drawn, that you know how you want panels arranged, and that you have
an understanding of 2D Cartesian coordinate plane operations.

To start, you'll need to create a Comic.xml file. Simply create a
normal .txt file (applications that can do it include Notepad, Notepad++
gedit, emacs, and vim) and change the file extension (the bit after the
period) to .xml instead of .txt. You can then open this file with any
text editor, although word processors like LibreOffice Writer and MS 
Word are not advised. 

First, add the following to the Comic.xml file:

<Comics>
</Comics>

Everything from here on out will be put BETWEEN these. Next comes the
process of creating each individual panel. Here's a general template for
a single panel:

	<panel name="name">
		<filename str="filename"></filename>
		<position x="0" y="0"></position>
		<vel value="5"></vel>
		<root enabled="false"></root>
		<blank enabled="false"></blank>
		<dirs>
			<up nextComic="null"></up>
			<down nextComic="null"></down>
			<left nextComic="null"></left>
			<right nextComic="null"></right>
		</dirs>
	</panel>

The first line (`<panel name="name">`) contains the name of your panel. Name
it anything you want, but you'll need to remember it for later. Replace the
word "name" (the one within the quotes) with the name of the panel.

The second line contains the filename of the panel. Supported image file
types are BMP, GIF, JPEG, LBM, PCX, PNG, PNM, TGA, TIFF, WEBP, XCF, XPM, 
and XV. If your images are within a folder, write the path to the image.
So, if there's a folder called "img" right next to the Infscroll-Comic
executable and it has a file called "RickAstley001.png", the filename would
be "img/RickAstley001.png". Replace the word "filename" in quotes (next to
str=) with the filename.

The next line (position) involves a bit of math. This is the position of
your panel on the X,Y (Cartesian) coordinate plane. Keep in mind that the
coordinates you give are for the TOP LEFT of the image. Also note that
in the world of computer graphics (and thus this program), the Y axis is
inverted, i.e. down is POSITIVE and up is NEGATIVE. Replace the numbers
within quote with the coordinates you want.

The "vel" line sets the rate at which transitions TO this panel are made.
This isn't on a scale of some sort, it's in pixels per frame at 60 frames
per second, but it gets a bit strange when taking scaling into account. The
best thing to do is experiment around with this value to find what works for 
you.

The "root" line tells the program whether this program is the starting comic
or not. If set to "true", the program starts off with the viewer looking at
this panel. If set to "false", the viewer does NOT start off looking at the
panel, and must transition to it. You should only have one of these set. If
there are multiples, the program will use the last root panel specified. If
there are no roots,  the program will exit immediately.

The "blank" line has somewhat more advanced usage. It'll be covered later,
so don't worry about it just yet - just set it to "false".

The next four lines specify transitions. This is where you, the author, get
to decide what happens when you press an arrow key button. Each line is named
after an arrow key. The value after it (after nextComic=) is the name of the
panel to transition to when the corresponding key is pressed. To set a panel,
enter the name of the panel you want to transition to, which is specified on
the first line. If you don't want a transition in this direction, put "null"
in place of a comic name.

Here's an example panel setup:

	<panel name="firstPanel">
		<filename str="panel001.png"></filename>
		<position x="3" y="7"></position>
		<vel value="4"></vel>
		<root enabled="true"></root>
		<blank enabled="false"></blank>
		<dirs>
			<up nextComic="null"></up>
			<down nextComic="someotherpanel"></down>
			<left nextComic="thisisanotherpaneltoo"></left>
			<right nextComic="null"></right>
		</dirs>
	</panel>

This setup is for a panel named firstPanel with filename "panel001.png",
located at 3,7 that is transitioned to with a velocity of 4. It's also a
root panel. When up is hit, it doesn't transition. When down is
hit, it transitions to "someotherpanel". When left is hit, it transitions to
"thisisanotherpaneltoo" and when right is hit it doesn't transition.

That's it! You can string multiple panels together like this to form a
complete comic in any arrangement of your choosing. For a working exampleof
this, see the example Comic.xml file in either of the Infscroll-Comic zip
files.

###How to Make a Frame:
What if you want to view multiple panels at once? Sure, you could lump them
into one image, but what if you wanted special behavior that goes beyond
that? A frame is just an empty panel, a spot for the viewer to transition
to and zoom in on while still offering all the other features of a panel.
Frames are quite straightforward to make. 

First, change the "blank" line to "true". This instructs Infscroll-comic
to NOT render this frame. Because of this, you can ignore the bit about
the filename - Infscroll-Comic won't even attempt to load a file if you
set "blank" to "true".

Next, you'll need to add in a line right above <dirs> - it looks like this:

	<dims width="800" height="600"></dims>

Because Infscroll-Comic isn't loading a real image anymore, you need to
specify a width and a height - in the example, the size is 800x600. This
lets you mess with the view, so you can encompass multiple panels at once.
Dont' be afraid to set the size to values way larger than any panel on the
screen - Infscroll-Comic will automatically scale everything on the screen
to compensate.

##Technical Stuff
Infscroll_Comic is written in C++ and uses the SDL2 library for graphics
and input. The code should be cross-platform, but you may need to
change some #includes depending on your IDE's configuration, or
whatever you plan on using to compile it. At bare minimum, you'll
probably need additional linker settings of `-lSDL2main -lSDL2
 -lSDL2_image`. If you're using mingw, you might also need -lmingw32.
