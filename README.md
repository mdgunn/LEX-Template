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
- Compatible with sandbox mode and the Game Launcher.
- Customize the menu's color, text, logo, and fonts in a xml script!
- Includes various useful scripts.
- Comes with prefabs of all objects so you can now just drag and drop various LE objects such as lights and decals.
- New icons for the engine's objects along with some for the templates pivot scripts.
- A batch file to delete bak files.
- And much more to come!!


### How To Install ###

This is designed to work as a project template with the editors Project Manager. 

1) Clone, or copy the "LEX Template" folder to your ../Steam\steamapps\common\Leadwerks Game Engine\Templates directory. 

2) Start up Leadwerks. Then go File->Project Manager. When in the manager, click New.

3) You'll see "LEX Template" as one of the selections. Select it, and then press OK.

4) Within a few seconds, your project should be ready!


### Setting up with Visual Studio (Windows) ###

I could not get this to work correctly; so upon making the new template, open the soultion and add everything under the Source folder to the project. Hopefully this will be fixed soon.


### Setting up with Code::Blocks (GNU/Linux) ###

Since my other machine died on me, I can't compile anything for Linux anymore. However, I'm sure the code will still work as most of the code was written in Code::Blocks at the time. If you're a Linux user, a pull request regarding this support would be appreciated!


### Wrap up ###

Well here's my 3 months of work, and I'm happy to see it stable for other people's use. Feel free to fork, clone, or commit pull requests. I'm sure I might have did something that could be better, just let me know. :)
