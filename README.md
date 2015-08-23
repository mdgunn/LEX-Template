# Leadwerks Extended Executable Template #

The Leadwerks Extended Executable Template is a third-party, and unoffical template for the Leadwerks Game Engine. It's aimed towards people who wish to create stand-alone games with things like a menu, adjustable settings, along with that logic being out of the way. Users can still write their games with lua script, while also being able to communicate to the application.

The Template comes with various scripts, materials, models, along with the full source code in-case you wish to edit the menu further than the xml script, or build your game with C++.

### Features ###

- 3.6 Ready!
- A working Menu UI with background map support.
- A built in loading screen system with the ability to have maps call their own loading screens.
- A operating in-game options panel.
- Upon first boot, the users screen resoultion and default values will saved to a settings file.
- Although the application uses the settings file, you can still override any settings property with launch options.
- Able to communicate with the app via lua scripts.
- A lua side way to precache models and prefabs to prevent a lag spike when spawning models in-game.
- Compatible with sandbox mode and the Game Launcher.
- Customize colors, text, the logo, and fonts in one xml script!
- Includes various useful scripts.
- Includes three new model shaders.
- Added a Check to see if the window is active. It will pause the game if alt-tabbed or another window is in front.
- Comes with prefabs of all objects so you can now just drag and drop various LE objects such as lights and decals.
- New icons for the engine's objects along with some for the templates pivot scripts.
- A batch file to delete bak files.
- And much more to come!!


### How To Install ###

This is designed to work as a project template with the editors Project Manager. 

1) Clone, or copy the "LEX Template" folder to your ../Steam/steamapps/common/Leadwerks Game Engine/Templates directory. 

2) Start up Leadwerks. Then go File->Project Manager. When in the manager, click New.

3) You'll see "LEX Template" as one of the selections. Select it, and then press OK.

4) Within a few seconds, your project should be ready!

5) The project will generate some bak files due to conflicts with the Common (Base) template. With Windows, under the Tools directory, you'll see a batch called "Cleanup.bat". Use it to cleanup unwanted bak files after creating the project, or during development.

### The Three Builds ###

There are 3 build modes. Debug, Release and Retail. Debug and Release are your ususal LE builds, but the retail build is the executable you ship with. The Retail build is the $PROJECT_NAME.exe, while the normal Release build is $PROJECT_NAME.dev.exe. The diffrence between Release and Retail is that Retail build disables the console box, and does not register the abort key (Used to force quit incase of a endless loop or memory leak, defaultly set to the End key). Use the _RETAIL preprocessor to create a Retail build.

NOTE: Although the console box is disabled in Retail builds, you'll still beable to view the console log in the Script Editor. You should use the Release build ($PROJECT_NAME.dev.exe) for playtesting, this way if something happens, you can view the console at any time. It should also be noted that a retail build was only built for lua only users so they had it. C++ coders can override $PROJECT_NAME.exe with the normal Release build. 

### Setting up with Visual Studio (Windows) ###

I could not get the sln to copy with the new files included. So upon making the new template, open the soultion and add everything under the Source folder to the project. Hopefully this will be fixed soon.

### Setting up with Code::Blocks (GNU/Linux) ###

Since my other machine died on me, I can't compile anything for Linux anymore. However, I'm sure the code will still work as most of the code was written in Code::Blocks at the time. If you're a Linux user, a pull request regarding this support would be appreciated!


### Wrap up ###

Well here's my 3 months of work, and I'm happy to see it stable for other people's use. Feel free to fork, clone, or commit pull requests. I'm sure I might have did something that could be better, just let me know. :)
